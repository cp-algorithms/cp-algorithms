#!/usr/bin/env python3
"""Publish article previews into a checkout of gh-pages; never push Git refs."""

import argparse
import hashlib
import html
import json
import posixpath
import re
import shutil
from pathlib import Path, PurePosixPath
from urllib.parse import quote, unquote, urlsplit, urlunsplit


REGISTRY = Path("preview/index.json")
ASSETS = Path("preview/assets")
GLOBAL_INPUTS = {
    "src/navigation.md", "mkdocs.yml", "hooks.py", "scripts/install-mkdocs.sh",
    ".github/workflows/build.yml",
}


def article_path(value):
    path = PurePosixPath(value)
    if path.is_absolute() or ".." in path.parts or path.suffix != ".html":
        raise ValueError(f"Invalid article path: {value}")
    return path.as_posix()


def preview_path(article, number):
    stem = Path(article_path(article)).with_suffix("")
    if stem.parts[0] == "main" or stem.parts[0].isdigit() or (stem.parts[0] == "preview" and len(stem.parts) > 1):
        raise ValueError(f"Article overlaps a publication directory: {article}")
    return stem / "preview" / str(number) / "index.html"


def url(path):
    return "/" + quote(PurePosixPath(path).as_posix(), safe="/")


def preview_url(article, number):
    return url(preview_path(article, number).parent) + "/"


def registry(site):
    path = site / REGISTRY
    return json.loads(path.read_text()) if path.exists() else {}


def write_registry(site, entries):
    path = site / REGISTRY
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(entries, indent=2, sort_keys=True) + "\n")


def remove_pages(site, entry, number):
    for article in entry.get("pages", {}):
        path = site / preview_path(article, number)
        path.unlink(missing_ok=True)
        parent = path.parent
        while parent != site and parent.is_dir() and not any(parent.iterdir()):
            parent.rmdir()
            parent = parent.parent
    hub = site / "preview" / str(number)
    if hub.exists():
        shutil.rmtree(hub)


def collect_assets(site, entries):
    used = {entry.get("assets") for entry in entries.values()}
    root = site / ASSETS
    if root.exists():
        for path in root.iterdir():
            if re.fullmatch(r"[0-9a-f]{64}", path.name) and path.name not in used:
                shutil.rmtree(path)


def remove(site, number):
    entries = registry(site)
    entry = entries.pop(str(number), None)
    if entry is not None:
        remove_pages(site, entry, number)
        write_registry(site, entries)
        collect_assets(site, entries)
    # Previews published before this layout used a top-level PR directory.
    legacy = site / str(number)
    if legacy.exists():
        shutil.rmtree(legacy)


def selected_articles(changed, files):
    global_change = any(
        name in GLOBAL_INPUTS
        or name.startswith("plugins/")
        or (name.startswith("src/") and not name.endswith(".md"))
        for name in changed
    )
    if global_change:
        return sorted(name for name in files if name.endswith(".html") and name != "404.html")
    articles = set()
    for name in changed:
        if name == "CONTRIBUTING.md":
            articles.add("contrib.html")
        elif name.startswith("src/") and name.endswith(".md"):
            articles.add(name[4:-3] + ".html")
    # Deleted articles have no rendered page.
    return sorted(articles & files.keys())


def asset_files(files):
    # Search uses the existing main mirror. Feeds and sitemaps are not assets:
    # their timestamps would otherwise invalidate a bundle on every build.
    return {
        name: path for name, path in files.items()
        if not name.endswith(".html")
        and not name.startswith("search/")
        and not name.startswith(("sitemap.", "feed_rss_"))
    }


def asset_digest(assets):
    digest = hashlib.sha256()
    for name, path in sorted(assets.items()):
        digest.update(name.encode() + b"\0")
        digest.update(hashlib.sha256(path.read_bytes()).digest())
    return digest.hexdigest()


def rewrite_page(source, article, pages, assets, bundle, number, main_prefix, has_main):
    from bs4 import BeautifulSoup

    soup = BeautifulSoup(source, "html.parser")

    def rewrite(value):
        parts = urlsplit(value)
        if parts.scheme or parts.netloc or not parts.path:
            return value
        path = posixpath.normpath(posixpath.join("/", posixpath.dirname(article), unquote(parts.path))).lstrip("/")
        if not path:
            path = "index.html"
        elif parts.path.endswith("/"):
            path += "/index.html"
        if path in pages:
            target = pages[path]
        elif path in assets:
            target = url(ASSETS / bundle / path)
        else:
            target = main_prefix + quote(path, safe="/")
        return urlunsplit(("", "", target, parts.query, parts.fragment))

    for tag in soup.find_all(True):
        for attribute in ("href", "src", "poster", "action", "data-src", "xlink:href"):
            if tag.has_attr(attribute):
                tag[attribute] = rewrite(tag[attribute])
        if tag.has_attr("srcset") and "data:" not in tag["srcset"]:
            candidates = []
            for candidate in tag["srcset"].split(","):
                if not candidate.strip():
                    continue
                value, *descriptor = candidate.strip().split()
                candidates.append(" ".join([rewrite(value), *descriptor]))
            tag["srcset"] = ", ".join(candidates)
        if tag.has_attr("style"):
            tag["style"] = re.sub(
                r"url\(['\"]?([^)'\"]+)['\"]?\)",
                lambda m: f'url("{rewrite(m[1])}")', tag["style"],
            )
        if tag.name == "meta" and tag.get("http-equiv", "").lower() == "refresh":
            tag["content"] = re.sub(r"(?i)(url=)(.+)$", lambda m: m[1] + rewrite(m[2]), tag["content"])

    config = soup.find("script", id="__config")
    if config and config.string:
        settings = json.loads(config.string)
        # Material resolves the search index relative to this directory URL.
        settings["base"] = main_prefix
        if settings.get("search"):
            settings["search"] = rewrite(settings["search"])
        config.string = json.dumps(settings)

    if soup.head is None:
        soup.insert(0, soup.new_tag("head"))
    for tag in soup.head.find_all("meta", attrs={"name": re.compile(r"^(robots|googlebot)$", re.I)}):
        tag.decompose()
    soup.head.append(soup.new_tag("meta", attrs={"name": "robots", "content": "noindex"}))
    soup.head.append(soup.new_tag("link", rel="stylesheet", href="/preview/selector.css"))
    soup.head.append(soup.new_tag("script", src="/preview/selector.js", defer=""))
    main_option = f'<option value="{main_prefix}{quote(article, safe="/")}">Main</option>' if has_main else ""
    toolbar = BeautifulSoup(
        '<aside class="article-preview" aria-label="Article preview">'
        f'<a href="https://github.com/cp-algorithms/cp-algorithms/pull/{number}">PR #{number}</a>'
        '<label>Version <select aria-label="Article version" '
        f'data-article="{html.escape(article, quote=True)}" data-pr="{number}">'
        + main_option +
        f'<option value="{pages[article]}" selected>PR #{number}</option>'
        '</select></label></aside>', "html.parser",
    ).aside
    content = soup.find("article") or soup.body
    if content:
        content.insert(0, toolbar)
    return str(soup)


def publish(build, site, number, changed, main_prefix="/main/"):
    build, site = build.resolve(), site.resolve()
    if build == site or build in site.parents or site in build.parents:
        raise ValueError("Build and publication directories must not overlap")
    if not main_prefix.startswith("/") or main_prefix.startswith("//") or "?" in main_prefix or "#" in main_prefix:
        raise ValueError("Main prefix must be a local absolute URL path")
    main_prefix = main_prefix.rstrip("/") + "/"
    paths = list(build.rglob("*"))
    if any(path.is_symlink() for path in paths):
        raise ValueError("Build artifacts must not contain symlinks")
    files = {
        path.relative_to(build).as_posix(): path for path in paths
        if path.is_file() and not any(part.startswith(".") for part in path.relative_to(build).parts)
    }
    selected = selected_articles(changed, files)
    pages = {article: preview_url(article, number) for article in selected}
    assets = asset_files(files) if pages else {}
    bundle = asset_digest(assets) if assets else None
    # Parse and rewrite all pages before replacing an earlier preview.
    rendered = {
        article: rewrite_page(
            files[article].read_text(), article, pages, assets, bundle, number, main_prefix,
            (site / main_prefix.lstrip("/") / article).is_file(),
        )
        for article in selected
    }
    entries = registry(site)
    if str(number) in entries:
        remove_pages(site, entries[str(number)], number)
    if bundle:
        destination = site / ASSETS / bundle
        if not destination.exists():
            for name, source in assets.items():
                target = destination / name
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copyfile(source, target)
    for article, content in rendered.items():
        target = site / preview_path(article, number)
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(content)
    entries[str(number)] = {"pages": pages, "assets": bundle}
    write_registry(site, entries)
    for extension in ("js", "css"):
        shutil.copyfile(Path(__file__).with_name(f"preview-selector.{extension}"), site / "preview" / f"selector.{extension}")
    links = "".join(f'<li><a href="{target}">{html.escape(article)}</a></li>' for article, target in pages.items())
    hub = site / "preview" / str(number) / "index.html"
    hub.parent.mkdir(parents=True, exist_ok=True)
    hub.write_text(
        '<!doctype html><html lang="en"><head><meta charset="utf-8">'
        '<meta name="robots" content="noindex"><meta name="viewport" content="width=device-width">'
        f'<title>PR #{number} previews</title></head><body><h1>PR #{number}</h1>'
        + (f'<ul>{links}</ul>' if pages else '<p>This PR has no changed article pages.</p>')
        + '</body></html>\n'
    )
    legacy = site / str(number)
    if legacy.exists():
        shutil.rmtree(legacy)
    collect_assets(site, entries)
    print(f"Published {len(pages)} article previews at /preview/{number}/")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("operation", choices=("publish", "remove"))
    parser.add_argument("--site", type=Path, required=True)
    parser.add_argument("--pr", type=int, required=True)
    parser.add_argument("--build", type=Path)
    parser.add_argument("--files", type=Path, help="JSON array of GitHub PR-file API pages (gh --paginate --slurp)")
    parser.add_argument("--main-prefix", default="/main/")
    args = parser.parse_args()
    if args.pr <= 0:
        parser.error("PR number must be positive")
    if args.operation == "remove":
        remove(args.site.resolve(), args.pr)
    else:
        if args.build is None or args.files is None:
            parser.error("publish requires --build and --files")
        changed = [item["filename"] for page in json.loads(args.files.read_text()) for item in page]
        publish(args.build, args.site, args.pr, changed, args.main_prefix)


if __name__ == "__main__":
    main()
