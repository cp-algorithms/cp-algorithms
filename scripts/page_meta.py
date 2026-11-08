#!/usr/bin/env python3
"""Add the "Last update" date and the contributor list to built pages.

Zensical does not run MkDocs plugins, so this script does what
git-revision-date-localized, git-authors and git-committers did before:

* the date of the last commit that touched each article;
* the date the article was first added, following renames;
* each author's share of the article's current lines (git blame -w);
* GitHub logins for author emails, cached in authors.json.

It also re-dates the RSS and JSON feeds with the same dates, so that the
feeds agree with the pages, and keeps the newest FEED_LENGTH items.

It replaces two placeholders that partials/content.html leaves in every
article: <!-- page-meta:dates --> and <!-- page-meta:contributors -->.
GitHub lookups run only when GITHUB_TOKEN is set; without it, authors
missing from the cache are shown by their git name.
"""

import argparse
import datetime
import email.utils
import html
import json
import os
import re
import subprocess
import sys
import urllib.request
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

DATES = "<!-- page-meta:dates -->"
CONTRIBUTORS = "<!-- page-meta:contributors -->"
FEED_LENGTH = 20
FEEDS = {
    "created": ("feed_rss_created.xml", "feed_json_created.json"),
    "updated": ("feed_rss_updated.xml", "feed_json_updated.json"),
}


def git(*args):
    return subprocess.run(
        ["git", *args], check=True, capture_output=True, text=True
    ).stdout


def format_date(stamp):
    date = datetime.datetime.fromtimestamp(stamp, datetime.timezone.utc)
    return f"{date:%B} {date.day}, {date.year}"


def creation_dates():
    """Map each path to the author date of the commit that first added it.

    One pass over the whole history, oldest commit first. A rename or a
    copy carries the old path's date over to the new path, as
    `git log --follow` does. Each path keeps the earliest
    date seen, so the result does not depend on the order in which commits
    from different branches are listed. This avoids `git log --follow`,
    which follows only one line of history and can stop at a rename.
    """
    created = {}

    def note(path, stamp):
        created[path] = min(created.get(path, stamp), stamp)

    tokens = iter(git("log", "-z", "--reverse", "-C", "--name-status",
                      "--diff-filter=ACR", "--format=commit %at").split("\0"))
    stamp = None
    for token in tokens:
        token = token.strip("\n")
        if token.startswith("commit "):
            stamp = int(token.split()[1])
        elif token == "A":
            note(next(tokens), stamp)
        elif token[:1] in ("C", "R"):
            old, new = next(tokens), next(tokens)
            note(new, created.get(old, stamp))
    return created


def last_update(path):
    # Like git-revision-date-localized: author date, no merge commits,
    # symlinks resolved. No --follow, which can pick up commits that
    # renamed another file away from this path.
    path = os.path.relpath(os.path.realpath(path))
    stamp = git("log", "-1", "--no-merges", "--format=%at", "--", path).strip()
    return int(stamp) if stamp else None


def blame(path):
    """Return {email: (name, line count, a commit sha)} and the total."""
    lines = defaultdict(int)
    names, shas = {}, {}
    commits = {}
    sha = None
    total = 0
    for line in git("blame", "--porcelain", "-w", "--", str(path)).splitlines():
        if line.startswith("\t"):
            email, name = commits[sha]
            lines[email] += 1
            names.setdefault(email, name)
            shas.setdefault(email, sha)
            total += 1
            continue
        key, _, value = line.partition(" ")
        if len(key) == 40 and all(c in "0123456789abcdef" for c in key):
            sha = key
            commits.setdefault(sha, ["", ""])
        elif key == "author":
            commits[sha][1] = value
        elif key == "author-mail":
            # The cache and GitHub treat emails case-insensitively.
            commits[sha][0] = value.strip("<>").lower()
    return {e: (names[e], n, shas[e]) for e, n in lines.items()}, total


class Logins:
    """Map author emails to GitHub accounts, with a JSON cache."""

    def __init__(self, cache, repository, token):
        self.cache = cache
        self.repository = repository
        self.token = token
        self.authors = {}
        if cache.exists():
            self.authors = json.loads(cache.read_text())
        self.by_email = {
            email.lower(): author
            for author in self.authors.values()
            for email in author.get("emails", [])
        }
        self.changed = False

    def query(self, sha):
        owner, name = self.repository.split("/")
        query = (
            '{ repository(owner: "%s", name: "%s") { object(oid: "%s") '
            "{ ... on Commit { author { user { login name url } } } } } }"
        ) % (owner, name, sha)
        request = urllib.request.Request(
            "https://api.github.com/graphql",
            data=json.dumps({"query": query}).encode(),
            headers={"Authorization": f"bearer {self.token}"},
        )
        with urllib.request.urlopen(request, timeout=30) as response:
            data = json.load(response)
        obj = ((data.get("data") or {}).get("repository") or {}).get("object")
        return ((obj or {}).get("author") or {}).get("user")

    def resolve(self, email, name, sha):
        if email in self.by_email:
            author = self.by_email[email]
            return author["login"], author["url"]
        if self.token:
            try:
                user = self.query(sha)
            except OSError as error:
                print(f"page-meta: GitHub lookup failed for {sha}: {error}",
                      file=sys.stderr)
                user = None
            # Unknown emails are cached too, so each one is looked up once.
            author = {"login": name, "name": name, "url": "#", "emails": []}
            if user:
                author = self.authors.get(user["login"], {**user, "emails": []})
            author["emails"].append(email)
            self.authors[user["login"] if user else email] = author
            self.by_email[email] = author
            self.changed = True
            return author["login"], author["url"]
        return name, "#"

    def save(self):
        if self.changed:
            self.cache.write_text(json.dumps(self.authors, indent=2))


def recent_emails(path):
    """Author emails, most recent commit first."""
    emails = git("log", "--format=%ae", "--", str(path)).lower().split()
    return list(dict.fromkeys(emails))


def contributors(blamed, total, recent, logins):
    shares = {}
    # Insert recent committers first so that ties keep the old order.
    order = recent + [email for email in blamed if email not in recent]
    for email in order:
        if email not in blamed:
            continue
        name, count, sha = blamed[email]
        login, url = logins.resolve(email, name, sha)
        # Same rounding as the git-authors plugin plus the old template.
        share = shares.setdefault(login, [url, 0.0])
        share[1] += round(count / total * 100, 2)
    rows = sorted(shares.items(), key=lambda item: item[1][1], reverse=True)
    return [(login, url, round(share, 2)) for login, (url, share) in rows]


def render(rows):
    items = "".join(
        f'<li><a href="{html.escape(url)}" title="{html.escape(login)}" '
        f'data-bi-name="contributorprofile" target="_blank">'
        f"{html.escape(login)}</a> ({share}%)</li>"
        for login, url, share in rows
    )
    return (
        '<ul class="metadata page-metadata" data-bi-name="page info" '
        'lang="en-us" dir="ltr">\n'
        '  <span class="contributors-text">Contributors:</span>\n'
        f'  <ul class="contributors" data-bi-name="contributors">{items}</ul>\n'
        "</ul>"
    )


def rewrite_feeds(site, source_of, dates):
    """Re-date and re-sort the feeds.

    dates maps "created" and "updated" to functions from a source path to
    a timestamp or None.
    """
    for kind, (rss_name, json_name) in FEEDS.items():
        def stamp(url, fallback):
            when = dates[kind](source_of(url))
            return fallback if when is None else when

        rss = site / rss_name
        if rss.exists():
            text = rss.read_text()
            items = re.findall(r"<item>.*?</item>", text, re.S)
            dated = []
            for item in items:
                url = re.search(r"<link>(.*?)</link>", item).group(1)
                old = re.search(r"<pubDate>(.*?)</pubDate>", item).group(1)
                when = stamp(url, email.utils.parsedate_to_datetime(old).timestamp())
                new = email.utils.format_datetime(
                    datetime.datetime.fromtimestamp(when, datetime.timezone.utc))
                dated.append((when, item.replace(old, new)))
            dated.sort(key=lambda pair: pair[0], reverse=True)
            if items:
                start = text.index(items[0])
                end = text.index(items[-1]) + len(items[-1])
                body = "".join(item for _, item in dated[:FEED_LENGTH])
                rss.write_text(text[:start] + body + text[end:])

        feed = site / json_name
        if feed.exists():
            data = json.loads(feed.read_text())
            for item in data.get("items", []):
                for key, which in (("date_published", "created"),
                                   ("date_modified", "updated")):
                    when = dates[which](source_of(item["url"]))
                    if when is not None:
                        item[key] = datetime.datetime.fromtimestamp(
                            when, datetime.timezone.utc).isoformat()
            key = "date_published" if kind == "created" else "date_modified"
            data["items"].sort(key=lambda item: item.get(key) or "", reverse=True)
            data["items"] = data["items"][:FEED_LENGTH]
            feed.write_text(json.dumps(data, ensure_ascii=False))


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("site", type=Path, help="built site, e.g. public")
    parser.add_argument("--docs", type=Path, default=Path("src"))
    parser.add_argument("--authors-cache", type=Path, default=Path("authors.json"))
    parser.add_argument("--repository", default="cp-algorithms/cp-algorithms")
    args = parser.parse_args()

    pages = []
    for page in sorted(args.site.rglob("*.html")):
        text = page.read_text()
        if DATES in text or CONTRIBUTORS in text:
            source = args.docs / page.relative_to(args.site).with_suffix(".md")
            if source.exists():
                pages.append((page, source, text))

    created = creation_dates()
    with ThreadPoolExecutor() as pool:
        dates = list(pool.map(lambda p: last_update(p[1]), pages))
        blames = list(pool.map(lambda p: blame(p[1]), pages))
        recents = list(pool.map(lambda p: recent_emails(p[1]), pages))

    logins = Logins(args.authors_cache, args.repository,
                    os.environ.get("GITHUB_TOKEN"))
    for (page, source, text), date, (blamed, total), recent in zip(
            pages, dates, blames, recents):
        source = os.path.relpath(os.path.realpath(source))
        dates = ""
        if date:
            dates += f"Last update: {format_date(date)}&emsp;"
        if source in created:
            dates += f"Created: {format_date(created[source])}&emsp;"
        rows = contributors(blamed, total, recent, logins) if total else []
        text = text.replace(DATES, dates)
        text = text.replace(CONTRIBUTORS, render(rows) if rows else "")
        page.write_text(text)
    logins.save()

    # Feed links are absolute; map them back to source files.
    def source_of(url):
        path = url.split("://", 1)[-1].partition("/")[2]
        source = args.docs / Path(path or "index.html").with_suffix(".md")
        return os.path.relpath(os.path.realpath(source))

    def updated(source):
        return last_update(source) if os.path.exists(source) else None

    rewrite_feeds(args.site, source_of, {"created": created.get, "updated": updated})
    print(f"page-meta: updated {len(pages)} pages and the feeds")


if __name__ == "__main__":
    main()
