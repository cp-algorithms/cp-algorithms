# Article previews

Production is published from this repository's `gh-pages` root at
`https://cp-algorithms.com/`. Sources stay on `main`. A separate repository,
`cp-algorithms/cp-algorithms-previews`, publishes previews from its `gh-pages`
branch at `https://preview.cp-algorithms.com/`.

For `algebra/binary-exp.html`, the Main preview is at
`/main/algebra/binary-exp.html`; PR #123 uses `/123/algebra/binary-exp.html`.
All preview pages, including Main, have `noindex` and a version selector.
Production pages have neither. The selector lists published versions containing
the current article. Production `.html` URLs are unchanged.

The deployment check's **Details** link and job summary lead to `/preview/123/`.
That review page identifies the built commit and lists directly changed pages
first, with **Preview** and **Main** links. New articles are marked **New page**.
Each PR article links back through **Review pages**.

## What gets published

The build validates the whole site, but article-only PRs publish only their
changed Markdown pages. Deleted pages have no preview. Navigation changes do
not expand this selection: each selected page already contains the new sidebar.
Navigation-only PRs preview the home page; changing `README.md` also includes
that page. Shared templates, assets, or build configuration changes preview all
pages. The review page explains this and folds the additional pages into a list.
There is no article-count threshold. PRs without rendered changes get just a
review page.

Links between selected pages stay in the PR. Other article links and search
results open the Main preview on the same preview host. Main is refreshed after
each successful main-branch build. This is an article-review view, not a complete
snapshot of every site feature.

Assets live in bundles under `/preview/assets/<sha256>/`. Matching bundles are
shared between Main and PRs. Search indexes, sitemaps, and timestamped feeds are
excluded from these bundles; one search index accompanies Main. Closing a PR
removes its pages and review index, then collects bundles no version references.
Main and its assets remain available.

## Isolation and setup

Rendered PR HTML, JavaScript, and SVG can execute contributor code. They are
not sanitized, since reviewers need to test those changes. Keep the preview
origin separate from production and authenticated applications; paths and
`noindex` do not isolate browser state. Main's copy on this host is also a
preview, not a trusted application.

Before enabling publication:

1. Initialize the preview repository's `gh-pages` branch and enable Pages from
   its root. Configure `preview.cp-algorithms.com` in Pages before adding its
   DNS CNAME to `cp-algorithms.github.io`. Default GitHub project URLs are also
   supported.
2. Set the source repository's Actions variable `PREVIEW_REPOSITORY` to
   `cp-algorithms/cp-algorithms-previews`.
3. Create a fine-grained token restricted to that preview repository, with
   **Contents: read/write** and **Pages: read**. Store it in the source
   repository as an **Actions secret** named `PREVIEW_DEPLOY_TOKEN`.
   Never put the token in an Actions variable. The source repository's normal
   `GITHUB_TOKEN` cannot push to another repository.
4. Seed Main from a successful build of the current main branch using the
   publisher below with `--pr main` and without `--files`.
5. Before moving production to Pages, review the root publication and retire
   all legacy PR previews on that origin. Preserve a Git ref for rollback,
   review the deletion diff, and change the Pages custom domain and DNS only
   after the prepared site has been checked. Keep Firebase available during
   the transition. The Markdown preview editor still uses its existing Cloud
   Function; switching static hosting does not replace that service.

The workflow reads the actual destination URL from the Pages API and rejects
production origins, the source repository, and an unexpected Pages branch.
Missing configuration fails publication. PRs must be open at the built head
both before and after fetching their file list. Stale Main builds are also
skipped. The trusted publisher treats build artifacts as data and never
executes their scripts. Git writes and cleanup share one publication queue.

## Local preview

After `mkdocs build --strict`, use a new directory on a separate port:

```sh
python3 -m pip install -r scripts/preview-requirements.txt
preview_dir=$(mktemp -d)
python3 scripts/article_previews.py publish --build public --site "$preview_dir" \
  --pr main --site-url http://127.0.0.1:8001/
printf '[[{"filename":"src/algebra/binary-exp.md"}]]\n' > "$preview_dir/changed.json"
python3 scripts/article_previews.py publish --build public --site "$preview_dir" \
  --pr 123 --files "$preview_dir/changed.json" --site-url http://127.0.0.1:8001/
python3 -m http.server 8001 --bind 127.0.0.1 --directory "$preview_dir"
```

Open `http://127.0.0.1:8001/123/algebra/binary-exp.html`. Check the selector,
links, math, images, search, and both themes. To compare production, serve the
original build on port 8000; it has no preview controls.

Run the publisher and deployment-guard tests with:

```sh
python3 -m unittest discover -s scripts -p 'test_*preview*.py'
```

CI runs them before the strict site build. They cover publication, URL rewriting,
bundle sharing, cleanup, invalid inputs, preservation of Main, and deployment
with stale builds or unsafe destination settings.
