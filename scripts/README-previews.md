# Article previews

Source stays on `main`. The main mirror stays on this repository's `gh-pages`.
Untrusted PR pages, their registry, and shared assets go to a dedicated preview
repository's `gh-pages`, on a different origin. Production `.html` URLs and
the current production domain are unchanged.

An article such as `algebra/binary-exp.html` is previewed at
`algebra/binary-exp/preview/123/` under the preview site's base URL. Project-site
prefixes such as `/cp-algorithms-previews/` are supported. The deployment check's
**Details** link and job summary lead to `preview/123/` on that site. It shows
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
the existing `https://gh.cp-algorithms.com/main/` mirror. This is an article-review
view, not a complete snapshot of every site feature. The publisher reads the
main mirror's file inventory to distinguish existing pages from new articles.

Non-HTML resources are stored in bundles under `preview/assets/<sha256>/`, with
their internal paths preserved so CSS and JavaScript dependencies still work.
Matching bundles are reused. Search indexes, sitemaps, and timestamped feeds do
not invalidate the bundles. Closing a PR removes its pages, index, and legacy
numeric directory, then removes bundles no remaining preview references.

The publisher runs from trusted workflow source and reads built PR artifacts
as data. It does not push refs; the serialized publication workflows commit the
result. A PR must still be open at the built head before and after fetching its
file list; superseded builds are skipped.

## Preview isolation and setup

Rendered PR HTML and assets can contain contributor JavaScript, including SVG
scripts. They are deliberately not sanitized: reviewers need to test those
changes too. Path prefixes and `noindex` do not isolate browser state. Reserve
the preview origin for untrusted content; do not host production or authenticated
applications on it.

Before merging this workflow:

1. Create a dedicated public preview repository, for example
   `cp-algorithms/cp-algorithms-previews`. Initialize its `gh-pages` branch with
   `.nojekyll` and a small `noindex` landing page.
2. Enable GitHub Pages from `gh-pages`, at `/`. Its default `github.io` project
   URL needs no DNS change. Do not reuse the production or main-mirror domain.
3. Set the source repository's Actions variable `PREVIEW_REPOSITORY` to that
   repository's `owner/name`.
4. Set `PREVIEW_DEPLOY_TOKEN` to a fine-grained token restricted to the preview
   repository, with **Contents: read/write** and **Pages: read**. The source
   repository's normal `GITHUB_TOKEN` cannot push to another repository.

The workflow obtains the real site URL from the destination's Pages API and
rejects the source repository, a wrong Pages source branch, or an origin shared
with production or the main mirror. Missing configuration fails publication;
there is no fallback to the trusted host. Search reads the public main-mirror
index, whose Pages response permits cross-origin requests.

Existing previews on the old host also need retirement. After the new publisher
is enabled, enumerate the old PR directories and registry entries, then use
`article_previews.py remove --site OLD_CHECKOUT --pr NUMBER` for each reviewed
PR number. Review and commit the deletion diff before pushing; reverting that
commit is the rollback. Keep `main/`, `CNAME`, and unrelated root files. Until
this migration is complete, old previews retain the existing same-origin risk.
Close-event cleanup handles both repositories during this transition.

## Local prototype

After building with `mkdocs build --strict`, prepare a local preview. The sample
PR number is only a local identifier. Use separate ports to test origin isolation:

```sh
python3 -m pip install -r scripts/preview-requirements.txt
preview_dir=$(mktemp -d)
printf '[[{"filename":"src/algebra/binary-exp.md"}]]\n' > "$preview_dir/changed.json"
python3 -c 'import json,pathlib; print(json.dumps([p.relative_to("public").as_posix() for p in pathlib.Path("public").rglob("*.html")]))' > "$preview_dir/main-files.json"
python3 scripts/article_previews.py publish --build public --site "$preview_dir" \
  --pr 123 --files "$preview_dir/changed.json" --main-files "$preview_dir/main-files.json" \
  --site-url http://127.0.0.1:8001 --main-prefix http://127.0.0.1:8000/
python3 -m http.server 8001 --bind 127.0.0.1 --directory "$preview_dir"
```

In another terminal, serve the main build with
`python3 -m http.server 8000 --bind 127.0.0.1 --directory public`.
Open `http://127.0.0.1:8001/algebra/binary-exp/preview/123/`.
Publish another local PR number to try switching versions. Main pages have no
selector. Check links, math, images, and both themes. The simple local server
does not enable CORS, so use the live main-mirror URL when testing search.

Run the publisher tests with:

```sh
python3 -m unittest discover -s scripts -p 'test_*preview*.py'
```

CI runs these tests before the strict site build. They cover URL rewriting,
shared and changed bundles, cleanup, input failures, and preservation of main.
The workflow test runs the deployment shell with local API/Git stubs, checking
stale builds, closed PRs, missing credentials, and unsafe destination settings.
