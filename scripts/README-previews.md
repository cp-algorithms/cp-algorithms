# Article previews

Source stays on `main`. Generated pages, a preview registry, and shared assets
stay on `gh-pages`. This prototype keeps the existing domain, the `main/` mirror,
and production `.html` URLs.

An article such as `algebra/binary-exp.html` is previewed at
`algebra/binary-exp/preview/123/`. The deployment check's **Details** link and
the deployment job summary lead to `/preview/123/`. This review page shows
the built commit and lists changed pages first, with **Preview** and **Main**
links. Articles without a main version are marked **New page**. A **Review pages**
link on each preview returns to this index.
Only preview pages have the version selector and `noindex`.
The selector lists other published PRs that contain the same article.

The build still validates the whole site. Publication selects the changed
Markdown articles; deleted articles have no preview page. Navigation changes
do not expand that selection: each selected article already has the updated
sidebar. A navigation-only PR previews just the home page to show that sidebar.
Changes to `README.md` also preview the home page, which includes its content.
Template, build configuration, and shared source-asset changes select all
rendered pages.
There is no article-count threshold: independent article edits do not require
copies of unchanged pages. For shared changes, the review page explains why
all pages are included and keeps the other pages in an expandable list.
PRs without rendered article changes get only the small index page.

Links to other selected articles stay in that PR. Other links and search use
the existing `main/` mirror. This is an article-review view, not an isolated
snapshot of every site feature. `--main-prefix /` supports a later production
move to the root; this PR does not perform that move.

Non-HTML resources are stored in bundles under `preview/assets/<sha256>/`, with
their internal paths preserved so CSS and JavaScript dependencies still work.
Matching bundles are reused. Search indexes, sitemaps, and timestamped feeds do
not invalidate the bundles. Closing a PR removes its pages, index, and legacy
numeric directory, then removes bundles no remaining preview references.

The publisher runs from trusted workflow source and reads built PR artifacts
as data. It does not push refs; the existing serialized publication workflows
commit the resulting changes.

## Local prototype

After building the current checkout with `mkdocs build --strict`, create a fresh
publication directory and a sample changed-file list. The sample PR number is
only a local preview identifier:

```sh
python3 -m pip install -r scripts/preview-requirements.txt
preview_dir=$(mktemp -d)
cp -R public "$preview_dir/main"
printf '[[{"filename":"src/algebra/binary-exp.md"}]]\n' > "$preview_dir/changed.json"
python3 scripts/article_previews.py publish --build public --site "$preview_dir" \
  --pr 123 --files "$preview_dir/changed.json"
python3 -m http.server 8000 --bind 127.0.0.1 --directory "$preview_dir"
```

Open `http://127.0.0.1:8000/algebra/binary-exp/preview/123/`.
Publish another local PR number to try switching versions. Main pages should
have no selector. Check navigation, search, math, images, and both color themes.

Run the publisher tests with:

```sh
python3 -m unittest discover -s scripts -p 'test_article_previews.py'
```

CI runs these tests before the strict site build. They cover URL rewriting,
shared and changed bundles, cleanup, input failures, and preservation of main.
