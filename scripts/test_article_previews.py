import hashlib
import json
from pathlib import Path
import tempfile
import unittest

from bs4 import BeautifulSoup

import article_previews as previews


PAGE = '''<!doctype html><html><head>
<link rel="canonical" href="https://cp-algorithms.com/algebra/a.html">
<link rel="stylesheet" href="../assets/theme.css">
<meta name="robots" content="index">
</head><body><article><h1>Article</h1><span class="arithmatex">$x^2$</span>
<a href="#proof">Proof</a><a href="b.html?q=1#proof">B</a>
<a href="../graph/c.html">C</a><img src="../images/example.svg">
<img srcset="../images/example.svg 1x, ../images/example.svg 2x">
<pre><code>int x = 1;</code></pre></article>
<script id="__config" type="application/json">{"base":"..","search":"../assets/worker.js"}</script>
<script src="../assets/app.js"></script></body></html>'''


def snapshot(root):
    return {
        path.relative_to(root).as_posix(): hashlib.sha256(path.read_bytes()).hexdigest()
        for path in root.rglob("*") if path.is_file()
    }


class ArticlePreviewsTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.build, self.site = self.root / "build", self.root / "site"
        for name, content in {
            "algebra/a.html": PAGE, "algebra/b.html": PAGE,
            "graph/c.html": PAGE, "index.html": PAGE, "404.html": PAGE,
            "assets/theme.css": 'body {background: url("../images/example.svg")}',
            "assets/app.js": "// app", "assets/worker.js": "// worker",
            "images/example.svg": "<svg></svg>", "favicon.ico": "icon",
            "search/search_index.json": '{"docs": []}',
            "sitemap.xml": "timestamp", "feed_rss_created.xml": "timestamp",
        }.items():
            path = self.build / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(content)
        for name in ("main/algebra/a.html", "main/index.html", "index.html", "CNAME", ".nojekyll"):
            path = self.site / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text("production " + name)
        self.production = snapshot(self.site)

    def publish(self, number=123, changed=None):
        previews.publish(self.build, self.site, number, changed or ["src/algebra/a.md"])

    def test_changed_articles_links_assets_and_noindex(self):
        self.publish(changed=["src/algebra/a.md", "src/algebra/b.md"])
        target = self.site / "algebra/a/preview/123/index.html"
        self.assertTrue(target.is_file())
        self.assertFalse((self.site / "graph/c/preview/123/index.html").exists())
        soup = BeautifulSoup(target.read_text(), "html.parser")
        self.assertEqual(soup.find("meta", attrs={"name": "robots"})["content"], "noindex")
        links = {a.get_text(): a["href"] for a in soup.find_all("a")}
        self.assertEqual(links["Proof"], "#proof")
        self.assertEqual(links["B"], "/algebra/b/preview/123/?q=1#proof")
        self.assertEqual(links["C"], "/main/graph/c.html")
        bundle = previews.registry(self.site)["123"]["assets"]
        self.assertEqual(soup.img["src"], f"/preview/assets/{bundle}/images/example.svg")
        self.assertTrue((self.site / soup.img["src"].lstrip("/")).is_file())
        config = json.loads(soup.find("script", id="__config").string)
        self.assertEqual(config["base"], "/main/")
        self.assertEqual(config["search"], f"/preview/assets/{bundle}/assets/worker.js")
        self.assertEqual(soup.code.get_text(), "int x = 1;")
        self.assertEqual(soup.find(class_="arithmatex").get_text(), "$x^2$")
        for name, digest in self.production.items():
            self.assertEqual(snapshot(self.site)[name], digest)
        self.assertNotIn("article-preview", (self.site / "main/algebra/a.html").read_text())

    def test_asset_bundle_is_shared_and_ignores_feed_timestamps(self):
        self.publish()
        (self.build / "feed_rss_created.xml").write_text("new timestamp")
        (self.build / "search/search_index.json").write_text('{"docs": ["changed"]}')
        self.publish(124, ["src/algebra/b.md"])
        entries = previews.registry(self.site)
        self.assertEqual(entries["123"]["assets"], entries["124"]["assets"])
        self.assertEqual(len(list((self.site / previews.ASSETS).iterdir())), 1)

    def test_asset_changes_get_a_distinct_bundle(self):
        self.publish()
        (self.build / "assets/app.js").write_text("// new app")
        self.publish(124)
        entries = previews.registry(self.site)
        self.assertNotEqual(entries["123"]["assets"], entries["124"]["assets"])

    def test_navigation_only_change_previews_just_the_home_page(self):
        (self.build / "navigation.html").write_text(PAGE)
        self.publish(changed=["src/navigation.md"])
        pages = previews.registry(self.site)["123"]["pages"]
        self.assertEqual(set(pages), {"index.html"})
        soup = BeautifulSoup((self.site / "preview/123/index.html").read_text(), "html.parser")
        self.assertIn("updated sidebar", soup.get_text())
        self.assertEqual(soup.find("a", string="Preview navigation on the home page")["href"], "/index/preview/123/")
        self.assertIsNone(soup.details)

    def test_new_article_with_navigation_stays_small_and_readme_adds_only_home(self):
        navigation = '<nav><a href="new.html">New article</a><a href="a.html">Existing article</a></nav>'
        (self.build / "algebra/new.html").write_text(PAGE.replace('<article>', navigation + '<article>'))
        (self.build / "navigation.html").write_text(PAGE)
        self.publish(changed=["src/algebra/new.md", "src/navigation.md"])
        self.assertEqual(set(previews.registry(self.site)["123"]["pages"]), {"algebra/new.html"})
        soup = BeautifulSoup((self.site / previews.preview_path("algebra/new.html", 123)).read_text(), "html.parser")
        links = {a.get_text(): a["href"] for a in soup.nav.find_all("a")}
        self.assertEqual(links["New article"], "/algebra/new/preview/123/")
        self.assertEqual(links["Existing article"], "/main/algebra/a.html")
        self.assertEqual([option.get_text() for option in soup.select(".article-preview option")], ["PR #123"])
        self.publish(changed=["src/algebra/new.md", "src/navigation.md", "README.md"])
        self.assertEqual(set(previews.registry(self.site)["123"]["pages"]), {"algebra/new.html", "index.html"})

    def test_readme_links_to_new_articles_stay_in_the_preview(self):
        (self.build / "index.html").write_text(PAGE.replace(
            '<article>', '<article><a href="https://cp-algorithms.com/algebra/b.html#proof">New article</a>',
        ))
        self.publish(changed=["README.md", "src/algebra/b.md"])
        self.assertEqual(set(previews.registry(self.site)["123"]["pages"]), {"index.html", "algebra/b.html"})
        soup = BeautifulSoup((self.site / previews.preview_path("index.html", 123)).read_text(), "html.parser")
        self.assertEqual(soup.find("a", string="New article")["href"], "/algebra/b/preview/123/#proof")
        self.assertEqual(soup.find("link", rel="canonical")["href"], "https://cp-algorithms.com/algebra/a.html")

    def test_review_index_links_changed_pages_main_and_source_revision(self):
        revision = "a" * 40
        summary = previews.publish(
            self.build, self.site, 123, ["src/algebra/a.md", "src/algebra/b.md"], revision=revision,
        )
        soup = BeautifulSoup((self.site / "preview/123/index.html").read_text(), "html.parser")
        rows = soup.select("tbody tr")
        self.assertEqual([row.code.get_text() for row in rows], ["algebra/a.html", "algebra/b.html"])
        self.assertEqual([a["href"] for a in rows[0].find_all("a")], ["/algebra/a/preview/123/", "/main/algebra/a.html"])
        self.assertIn("New page", rows[1].get_text())
        self.assertNotIn("/main/algebra/b.html", str(rows[1]))
        self.assertIsNone(soup.details)
        self.assertIsNotNone(soup.find("a", href=f"https://github.com/cp-algorithms/cp-algorithms/commit/{revision}"))
        self.assertIn("https://gh.cp-algorithms.com/preview/123/", summary)
        self.assertIn("This preview contains 2 changed pages.", summary)
        article = BeautifulSoup((self.site / previews.preview_path("algebra/a.html", 123)).read_text(), "html.parser")
        self.assertEqual(article.find("a", string="Review pages")["href"], "/preview/123/")

    def test_shared_change_keeps_directly_edited_articles_first(self):
        (self.build / "navigation.html").write_text(PAGE)
        self.publish(changed=["src/stylesheets/extra.css", "src/navigation.md", "src/algebra/b.md"])
        soup = BeautifulSoup((self.site / "preview/123/index.html").read_text(), "html.parser")
        self.assertEqual(soup.table.code.get_text(), "algebra/b.html")
        self.assertEqual(
            {code.get_text() for code in soup.details.select("tbody code")},
            {"index.html", "navigation.html", "algebra/a.html", "graph/c.html"},
        )

    def test_contributing_symlink_maps_to_rendered_contrib_page(self):
        (self.build / "contrib.html").write_text(PAGE)
        self.publish(changed=["CONTRIBUTING.md"])
        self.assertEqual(set(previews.registry(self.site)["123"]["pages"]), {"contrib.html"})

    def test_no_article_change_creates_only_a_noindex_hub(self):
        self.publish(changed=["test/test_example.cpp"])
        entry = previews.registry(self.site)["123"]
        self.assertEqual(entry, {"pages": {}, "assets": None})
        self.assertFalse((self.site / previews.ASSETS).exists())
        soup = BeautifulSoup((self.site / "preview/123/index.html").read_text(), "html.parser")
        self.assertEqual(soup.find("meta", attrs={"name": "robots"})["content"], "noindex")
        self.assertIn("no changed articles with rendered preview pages", soup.get_text())
        self.assertIsNone(soup.table)

    def test_new_article_does_not_offer_a_missing_main_page(self):
        self.publish(changed=["src/algebra/b.md"])
        target = self.site / previews.preview_path("algebra/b.html", 123)
        soup = BeautifulSoup(target.read_text(), "html.parser")
        self.assertEqual([option.get_text() for option in soup.select(".article-preview option")], ["PR #123"])

    def test_update_removes_old_pages_and_cleanup_keeps_shared_assets(self):
        self.publish(changed=["src/algebra/a.md", "src/algebra/b.md"])
        self.publish(124)
        self.publish(changed=["src/algebra/b.md"])
        self.assertFalse((self.site / "algebra/a/preview/123/index.html").exists())
        previews.remove(self.site, 123)
        self.assertTrue((self.site / "algebra/a/preview/124/index.html").exists())
        self.assertEqual(len(list((self.site / previews.ASSETS).iterdir())), 1)
        previews.remove(self.site, 124)
        self.assertEqual(list((self.site / previews.ASSETS).iterdir()), [])
        before = snapshot(self.site)
        previews.remove(self.site, 124)
        self.assertEqual(snapshot(self.site), before)
        for name, digest in self.production.items():
            self.assertEqual(snapshot(self.site)[name], digest)

    def test_cleanup_removes_legacy_preview(self):
        path = self.site / "123/index.html"
        path.parent.mkdir()
        path.write_text("legacy")
        previews.remove(self.site, 123)
        self.assertEqual(snapshot(self.site), self.production)

    def test_invalid_build_does_not_replace_previous_preview(self):
        self.publish()
        before = snapshot(self.site)
        (self.build / "algebra/a.html").write_text(PAGE.replace('"base":".."', 'INVALID'))
        with self.assertRaises(json.JSONDecodeError):
            self.publish()
        self.assertEqual(snapshot(self.site), before)

    def test_rejects_symlinks_overlapping_roots_and_unsafe_article_paths(self):
        (self.build / "escape").symlink_to(self.site / "CNAME")
        with self.assertRaises(ValueError):
            self.publish()
        with self.assertRaises(ValueError):
            previews.publish(self.site, self.site, 123, [])
        for article in ("../main/index.html", "/main/index.html", "a.md", "main.html", "123/a.html", "preview/assets/a.html"):
            with self.assertRaises(ValueError):
                previews.preview_path(article, 123)


if __name__ == "__main__":
    unittest.main()
