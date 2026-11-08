---
search:
  exclude: true
---

# How to Contribute

Anyone with a [GitHub account](https://github.com) can contribute. You can fix a typo, improve an article or add a new one. Send your changes as a pull request to the [cp-algorithms repository](https://github.com/cp-algorithms/cp-algorithms).

The pages are compiled and published at [https://cp-algorithms.com](https://cp-algorithms.com).

## Steps to Contribute

Follow these steps to start contributing:

1. **Find the article you want to improve**. Click the pencil icon (:material-pencil:) next to the article title.
2. **Fork the repository** if prompted. This creates a copy of the repository in your GitHub account.
3. **Make your changes** directly in the GitHub editor or clone the repository to work locally.
4. **Preview your changes** using the [preview page](preview.md) to ensure they look correct.
5. **Commit your changes** by clicking the _Propose changes_ button.
6. **Create a Pull Request (PR)** by clicking _Compare & pull request_.
7. **Wait for review**. A maintainer reviews each pull request. Review can take from a few days to a few weeks.

### Making Larger Changes

If you’re planning to make more significant changes, such as adding new articles or modifying multiple files:

- **Fork the project** using the traditional Git workflow (create a branch for your changes).
- **Edit files locally or in the GitHub UI**.
- **Submit a pull request** with your updates.

New to pull requests? Read [How to Contribute to Open Source](https://opensource.guide/how-to-contribute/).

### Updating Indexes

When you add new articles or reorganize existing ones, be sure to update the following files:

- **[navigation.md](https://github.com/cp-algorithms/cp-algorithms/blob/main/src/navigation.md)**: Update the list of all articles.
- **[README.md](https://github.com/cp-algorithms/cp-algorithms/blob/main/README.md)**: Update the list of new articles on the main page.

## Article Syntax

We use [Markdown](https://daringfireball.net/projects/markdown) to format articles. Articles are rendered using [Material for MkDocs](https://squidfunk.github.io/mkdocs-material/), which provides a lot of flexibility. Here are some key features:

- **Math formulas**: Use [MathJax](https://squidfunk.github.io/mkdocs-material/reference/mathjax/#usage) for equations. Make sure to leave an empty line before and after any `$$` math blocks.
- **Code blocks**: [Code blocks](https://squidfunk.github.io/mkdocs-material/reference/code-blocks/#usage) are great for adding code snippets in articles.
- **Admonitions**: Use [admonitions](https://squidfunk.github.io/mkdocs-material/reference/admonitions/#usage) for special content, such as theorems or examples.
- **Tabs**: Organize content with [content tabs](https://squidfunk.github.io/mkdocs-material/reference/content-tabs/#usage).
- **Tables**: Use [data tables](https://squidfunk.github.io/mkdocs-material/reference/data-tables/#usage) for organizing information.

Not every Material for MkDocs feature is enabled on this site. Check your page in the [preview](preview.md) before you submit it.

### Setting the HTML Title

By default, the first header (`# header`) of your article will be used as the HTML title. If your header contains a formula or complex text, you can manually set the title:

```markdown
---
title: Alternative HTML Title
---
# Proof of $a^2 + b^2 = c^2$
```

### Handling Redirects

If you move or rename an article, make sure to set up a redirect. A redirect file should look like this:

```md
<meta http-equiv="refresh" content="0; url=../new-section/new-article.html">
# Article Name
This article has been moved to a [new location](new-section/new-article.md).
```

### Maintaining Anchor Links

If you rename a section, links to its old anchor (`/article.html#old-section-title`) stop working. To keep them working, add the old anchor by hand:

```html
<div id="old-section-title"></div>
```

Existing links then keep working after the section title changes.

### Article Tags

We use tags to differentiate between original content and translated articles. Add the appropriate tag at the top of your article:

- **For original articles**:

    ```md
    ---
    tags:
        - Original
    ---
    ```

- **For translated articles**:

    ```md
    ---
    tags:
        - Translated
    e_maxx_link: <original-link>
    ---
    ```

    Replace `<original-link>` with the last part of the URL (e.g., for `http://e-maxx.ru/algo/euler_function`, use `euler_function`).

## Conventions

We follow certain conventions across the project. For example, we agreed to use the `\binom{n}{k}` notation for binomial coefficients instead of `C_n^k` as outlined in [issue #83](https://github.com/cp-algorithms/cp-algorithms/issues/83). The first one renders as $\binom{n}{k}$ and is a more universal convention. The second would render as $C_n^k$.

## Adding Problems

Before you add a problem, check that the article's technique is a useful part of its solution. Check that the list does not already teach the same idea. Place the problem by difficulty if you can. If you cannot, add it anyway, and a maintainer can reorder the list later.

## Local Development Setup

You can preview changes locally before pushing them to GitHub. To do this:

1. Clone the repository:

    ```console
    git clone https://github.com/cp-algorithms/cp-algorithms.git && cd cp-algorithms
    ```

2. Install dependencies and serve the site:

    ```console
    scripts/install-zensical.sh # requires pip
    zensical serve
    ```

   This will run the site locally so you can preview your changes.

### Page dates and contributors

The build adds each article's "Last update" and "Created" dates and its contributor list after Zensical has rendered the site. The same step dates the RSS feeds. To see them locally, run this after `zensical build`:

```console
python3 scripts/page_meta.py public
```

Set `GITHUB_TOKEN` to show GitHub accounts for authors who are not yet in `authors.json`. Without it, those authors are shown by their git name.

## Testing Code Snippets

Each new or changed executable snippet needs a test in the `test` directory.

1. Name the code snippet:
````
```{.cpp file=snippet-name}
// code here
```
````
2. Run `extract_snippets.py` from the `test` directory. It extracts the named snippets into header files.
3. Create a test file that includes these headers and checks their behavior.
4. Run the C++ tests with the `test.sh` script:
    ```console
    cd test
    ./test.sh
    ```
    **Example Output:**
    ```
    Running test_aho_corasick.cpp - Passed in 635 ms
    Running test_balanced_brackets.cpp - Passed in 1390 ms
    Running test_burnside_tori.cpp - Passed in 378 ms
    ...
    67 PASSED in 49.00 seconds
    ```

Additionally, all pull requests will be automatically tested via [GitHub Actions](https://github.com/cp-algorithms/cp-algorithms/actions).
