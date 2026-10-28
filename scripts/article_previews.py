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
    "mkdocs.yml", "hooks.py", "scripts/install-mkdocs.sh",
    ".github/workflows/build.yml",
}


def article_path(value):
    path = PurePosixPath(value)
    if path.is_absolute() or ".." in path.parts or path.suffix != ".html":
        raise ValueError(f"Invalid article path: {value}")
    return path.as_posix()


def preview_path(article, number):
    if str(number) != "main" and not re.fullmatch(r"[1-9][0-9]*", str(number)):
        raise ValueError("Version must be main or a positive PR number")
    return Path(str(number)) / article_path(article)


def url(path, prefix="/"):
    return prefix + quote(PurePosixPath(path).as_posix(), safe="/")


def preview_url(article, number, prefix="/"):
    return url(preview_path(article, number), prefix)


def preview_prefix(site_url, main_url):
    """Reject deployments that would put untrusted previews on a trusted origin."""
    def origin(value):
        parts = urlsplit(value)
        local = parts.hostname in ("localhost", "127.0.0.1", "::1")
        if (parts.scheme != "https" and not (local and parts.scheme == "http")) or not parts.hostname:
            raise ValueError("Publication URLs must use HTTPS (HTTP is allowed for localhost tests)")
        if parts.username or parts.password or parts.query or parts.fragment or any(c.isspace() for c in value):
            raise ValueError("Publication URLs must not contain credentials, queries, or fragments")
        if unquote(parts.path).startswith("//") or "\\" in unquote(parts.path) or ".." in PurePosixPath(unquote(parts.path)).parts:
            raise ValueError("Publication URLs must not contain path traversal")
        return parts.scheme, parts.hostname, parts.port or (443 if parts.scheme == "https" else 80)

    preview_origin, main_origin = origin(site_url), origin(main_url)
    if preview_origin == main_origin or preview_origin[1] in ("cp-algorithms.com", "www.cp-algorithms.com"):
        raise ValueError("Previews must use a different origin from production")
    return quote(unquote(urlsplit(site_url).path.rstrip("/")), safe="/") + "/"


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
    if not re.fullmatch(r"[1-9][0-9]*", str(number)):
        raise ValueError("Only PR versions can be removed")
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


def shared_changes(changed):
    return sorted(
        name for name in changed if
        name in GLOBAL_INPUTS
        or name.startswith("plugins/")
        or (name.startswith("src/") and not name.endswith(".md"))
    )


def changed_articles(changed, files):
    articles = set()
    for name in changed:
        if name == "README.md":
            articles.add("index.html")
        elif name == "CONTRIBUTING.md":
            articles.add("contrib.html")
        elif name.startswith("src/") and name.endswith(".md") and name != "src/navigation.md":
            articles.add(name[4:-3] + ".html")
    # Deleted articles have no rendered page.
    return sorted(articles & files.keys())


def selected_articles(changed, files):
    if shared_changes(changed):
        return sorted(name for name in files if name.endswith(".html") and name != "404.html" and not name.startswith("overrides/"))
    articles = changed_articles(changed, files)
    # Selected articles already contain the updated sidebar. Navigation-only
    # changes need just one representative page to review it.
    if not articles and "src/navigation.md" in changed and "index.html" in files:
        return ["index.html"]
    return articles


def review_index(number, pages, changed, shared, main_pages, main_prefix, revision, site_url="", prefix="/"):
    """Give reviewers one entry point, with directly edited pages first."""
    pr_url = f"https://github.com/cp-algorithms/cp-algorithms/pull/{number}"
    navigation_only = set(pages) == {"index.html"} and not changed and not shared
    scope = (
        f"All {len(pages)} pages are previewed because shared site files changed."
        if shared else f"This preview contains {len(pages)} changed page{'s' if len(pages) != 1 else ''}."
    ) if pages else "There are no changed articles with rendered preview pages."
    if navigation_only:
        scope = "Navigation changed; the home page is previewed so you can review the updated sidebar."

    def table(articles):
        rows = []
        for article in articles:
            main = f'<a href="{main_prefix}{quote(article, safe="/")}">Main</a>' if article in main_pages else "New page"
            rows.append(
                f'<tr><th scope="row"><code>{html.escape(article)}</code></th>'
                f'<td><a href="{pages[article]}">Preview</a></td><td>{main}</td></tr>'
            )
        return '<table><thead><tr><th>Page</th><th>PR version</th><th>Main version</th></tr></thead><tbody>' + "".join(rows) + '</tbody></table>'

    content = f'<h1>Preview for PR #{number}</h1><p><a href="{pr_url}">View pull request</a></p>'
    if revision:
        content += f'<p>Built from <a href="https://github.com/cp-algorithms/cp-algorithms/commit/{revision}"><code>{revision[:7]}</code></a>.</p>'
    content += f'<p>{scope}</p>'
    if shared:
        content += '<p>Shared changes: ' + ", ".join(f'<code>{html.escape(name)}</code>' for name in shared) + '.</p>'
    if changed:
        content += '<h2>Changed pages</h2>' + table(changed)
    remaining = sorted(pages.keys() - set(changed))
    if remaining:
        if "index.html" in pages:
            label = "Preview navigation on the home page" if navigation_only else "Browse the site preview"
            content += f'<p><a href="{pages["index.html"]}">{label}</a></p>'
        if not navigation_only:
            content += f'<details><summary>All other page previews ({len(remaining)})</summary>{table(remaining)}</details>'
    if pages:
        content += '<p>Links to unchanged articles and search results open the Main preview.</p>'
    document = (
        '<!doctype html><html lang="en"><head><meta charset="utf-8">'
        '<meta name="robots" content="noindex"><meta name="viewport" content="width=device-width, initial-scale=1">'
        f'<title>Preview for PR #{number}</title><link rel="stylesheet" href="{url("preview/selector.css", prefix)}">'
        f'</head><body class="preview-index"><main>{content}</main></body></html>\n'
    )
    review_url = site_url.rstrip("/") + f"/preview/{number}/" if site_url else f"/preview/{number}/"
    summary = f"### Article previews\n\n[Review PR #{number} previews]({review_url})\n\n{scope}\n"
    if revision:
        summary += f"\nBuilt from `{revision[:7]}`.\n"
    return document, summary


def asset_files(files):
    # Search uses the Main preview. Feeds and sitemaps are not assets:
    # their timestamps would otherwise invalidate a bundle on every build.
    return {
        name: path for name, path in files.items()
        if not name.endswith(".html")
        and not name.startswith("search/")
        and not name.startswith(("sitemap.", "feed_rss_", "feed_json_"))
    }


def asset_digest(assets):
    digest = hashlib.sha256()
    for name, path in sorted(assets.items()):
        digest.update(name.encode() + b"\0")
        digest.update(hashlib.sha256(path.read_bytes()).digest())
    return digest.hexdigest()


def rewrite_page(source, article, pages, assets, bundle, number, main_prefix, has_main, prefix="/"):
    from bs4 import BeautifulSoup

    soup = BeautifulSoup(source, "html.parser")
    # Preview feeds are not published or advertised for indexing.
    for feed in soup.find_all("link", type="application/rss+xml"):
        feed.decompose()
    for feed in soup.find_all("a", href=re.compile(r"(^|/)feed_rss_[^/]+\.xml$")):
        feed.decompose()

    def rewrite(value, site_link=False):
        parts = urlsplit(value)
        # README uses absolute article links and is included in the home page.
        # Rewrite those anchors too, while preserving canonical metadata.
        if site_link and parts.scheme in ("", "http", "https") and parts.netloc == "cp-algorithms.com":
            parts = parts._replace(scheme="", netloc="")
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
            target = url(ASSETS / bundle / path, prefix)
        else:
            target = main_prefix + quote(path, safe="/")
        return urlunsplit(("", "", target, parts.query, parts.fragment))

    for tag in soup.find_all(True):
        for attribute in ("href", "src", "poster", "action", "data-src", "xlink:href"):
            if tag.has_attr(attribute):
                tag[attribute] = rewrite(tag[attribute], site_link=tag.name == "a" and attribute == "href")
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
    soup.head.append(soup.new_tag("link", rel="stylesheet", href=url("preview/selector.css", prefix)))
    soup.head.append(soup.new_tag("script", src=url("preview/selector.js", prefix), defer=""))
    is_main = str(number) == "main"
    main_option = f'<option value="{main_prefix}{quote(article, safe="/")}">Main</option>' if has_main and not is_main else ""
    source_link = (
        '<a href="https://github.com/cp-algorithms/cp-algorithms/tree/main">Main</a>' if is_main else
        f'<a href="https://github.com/cp-algorithms/cp-algorithms/pull/{number}">PR #{number}</a>'
    )
    review_link = "" if is_main else f'<a href="{url(f"preview/{number}", prefix)}/">Review pages</a>'
    version_label = "Main" if is_main else f"PR #{number}"
    toolbar = BeautifulSoup(
        '<aside class="article-preview" aria-label="Article preview">'
        + source_link + review_link +
        '<label>Version <select aria-label="Article version" '
        f'data-article="{html.escape(article, quote=True)}" data-pr="{number}" '
        f'data-index="{url(REGISTRY, prefix)}">'
        + main_option +
        f'<option value="{pages[article]}" selected>{version_label}</option>'
        '</select></label></aside>', "html.parser",
    ).aside
    content = soup.find("article") or soup.body
    if content:
        content.insert(0, toolbar)
    return str(soup)


def publish(build, site, number, changed, revision="", site_url="", production_url="https://cp-algorithms.com/"):
    build, site = build.resolve(), site.resolve()
    if build == site or build in site.parents or site in build.parents:
        raise ValueError("Build and publication directories must not overlap")
    prefix = preview_prefix(site_url, production_url) if site_url else "/"
    preview_path("index.html", number)  # Validate before changing any files.
    is_main = str(number) == "main"
    entries = registry(site)
    if site_url and not is_main and "main" not in entries:
        raise ValueError("Publish the Main preview before publishing PRs")
    main_prefix = prefix + "main/"
    if revision and not re.fullmatch(r"[0-9a-f]{40}", revision):
        raise ValueError("Revision must be a full Git commit SHA")
    paths = list(build.rglob("*"))
    if any(path.is_symlink() for path in paths):
        raise ValueError("Build artifacts must not contain symlinks")
    files = {
        path.relative_to(build).as_posix(): path for path in paths
        if path.is_file() and not any(part.startswith(".") for part in path.relative_to(build).parts)
    }
    selected = selected_articles(["mkdocs.yml"] if is_main else changed, files)
    pages = {article: preview_url(article, number, prefix) for article in selected}
    main_pages = (
        set(entries["main"]["pages"]) if "main" in entries else
        {article for article in selected if (site / "main" / article).is_file()}
    )
    review, summary = review_index(
        number, pages, changed_articles(changed, files), shared_changes(changed), main_pages, main_prefix, revision, site_url, prefix,
    )
    assets = asset_files(files) if pages else {}
    bundle = asset_digest(assets) if assets else None
    # Parse and rewrite all pages before replacing an earlier preview.
    rendered = {
        article: rewrite_page(
            files[article].read_text(), article, pages, assets, bundle, number, main_prefix,
            article in main_pages, prefix,
        )
        for article in selected
    }
    search_index = (build / "search/search_index.json").read_bytes() if is_main else None
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
    (site / ".nojekyll").touch()
    for extension in ("js", "css"):
        shutil.copyfile(Path(__file__).with_name(f"preview-selector.{extension}"), site / "preview" / f"selector.{extension}")
    if is_main:
        # Material search resolves result locations relative to this Main copy.
        search = site / "main/search/search_index.json"
        search.parent.mkdir(parents=True, exist_ok=True)
        search.write_bytes(search_index)
        (site / "index.html").write_text(
            '<!doctype html><html lang="en"><head><meta charset="utf-8">'
            '<meta name="robots" content="noindex">'
            f'<meta http-equiv="refresh" content="0; url={main_prefix}">'
            '<title>CP-Algorithms previews</title></head><body>'
            f'<a href="{main_prefix}">Browse previews</a></body></html>\n'
        )
        summary = f"[Browse Main preview]({site_url.rstrip('/')}/main/)\n"
    else:
        hub = site / "preview" / str(number) / "index.html"
        hub.parent.mkdir(parents=True, exist_ok=True)
        hub.write_text(review)
        if "index.html" not in pages:
            # Keep existing deployment links to /PR/ useful for article-only PRs.
            landing = site / str(number) / "index.html"
            landing.parent.mkdir(parents=True, exist_ok=True)
            review_url = url(f"preview/{number}", prefix) + "/"
            landing.write_text(
                '<!doctype html><html lang="en"><head><meta charset="utf-8">'
                '<meta name="robots" content="noindex">'
                f'<meta http-equiv="refresh" content="0; url={review_url}">'
                f'<title>PR #{number} preview</title></head><body>'
                f'<a href="{review_url}">Review changed pages</a></body></html>\n'
            )
    collect_assets(site, entries)
    landing = "main" if is_main else f"preview/{number}"
    print(f"Published {len(pages)} article previews at {prefix}{landing}/")
    return summary


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("operation", choices=("publish", "remove"))
    parser.add_argument("--site", type=Path, required=True)
    parser.add_argument("--pr", required=True, help="Positive PR number, or main to publish the Main preview")
    parser.add_argument("--build", type=Path)
    parser.add_argument("--files", type=Path, help="JSON array of GitHub PR-file API pages (gh --paginate --slurp)")
    parser.add_argument("--production-url", default="https://cp-algorithms.com/")
    parser.add_argument("--site-url", default="", help="Isolated preview site's URL, including its project path")
    parser.add_argument("--revision", default="", help="Full source commit SHA shown on the review page")
    parser.add_argument("--summary", type=Path, help="Write a Markdown review link for the deployment job summary")
    args = parser.parse_args()
    if args.pr != "main" and not re.fullmatch(r"[1-9][0-9]*", args.pr):
        parser.error("Version must be main or a positive PR number")
    if args.operation == "remove":
        if args.pr == "main":
            parser.error("Main cannot be removed by PR cleanup")
        remove(args.site.resolve(), args.pr)
    else:
        if args.build is None or not args.site_url or (args.pr != "main" and args.files is None):
            parser.error("publish requires --build, --site-url, and --files for PR versions")
        changed = [item["filename"] for page in json.loads(args.files.read_text()) for item in page] if args.files else []
        summary = publish(args.build, args.site, args.pr, changed, args.revision, args.site_url, args.production_url)
        if args.summary:
            args.summary.write_text(summary)


if __name__ == "__main__":
    main()
