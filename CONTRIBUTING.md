---
search:
  exclude: true
---

# How to Contribute

Thank you for your interest in contributing to the cp-algorithms project! Whether you want to fix a typo, improve an article, or add new content, your help is welcome. All you need is a [GitHub account](https://github.com). Contributions are managed through our [GitHub repository](https://github.com/cp-algorithms/cp-algorithms), where you can directly submit changes or propose improvements.

The pages are compiled and published at [https://cp-algorithms.com](https://cp-algorithms.com).

## Steps to Contribute

Follow these steps to start contributing:

1. **Find the article you want to improve**. Click the pencil icon (:material-pencil:) next to the article title.
2. **Fork the repository** if prompted. This creates a copy of the repository in your GitHub account.
3. **Make your changes** directly in the GitHub editor or clone the repository to work locally.
4. **Preview your changes** using the [preview page](preview.md) to ensure they look correct.
5. **Commit your changes** by clicking the _Propose changes_ button.
6. **Create a Pull Request (PR)** by clicking _Compare & pull request_.
7. **Review process**: Someone from the core team will review your changes. This may take a few hours to a few days.

### Making Larger Changes

If you’re planning to make more significant changes, such as adding new articles or modifying multiple files:

- **Fork the project** using the traditional Git workflow (create a branch for your changes).
- **Edit files locally or in the GitHub UI**.
- **Submit a pull request** with your updates.

For help with this workflow, check out this helpful guide: [Step-by-step guide to contributing on GitHub](https://opensource.guide/how-to-contribute/).

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

Some advanced features may not be enabled or require a paid subscription. Keep this in mind when experimenting with formatting.

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

If you rename a section, the link to that section (`/article.html#old-section-title`) might break. To avoid this, add an anchor manually:

```html
<div id="old-section-title"></div>
```

This will allow existing links to continue working even after the section title is changed.

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

When adding problems, try to arrange them by difficulty. If you're unable to, don't worry—just add the problem, and someone else can adjust the order later.

## Local Development Setup

You can preview changes locally before pushing them to GitHub. To do this:

1. Clone the repository:

    ```console
    git clone --recursive https://github.com/cp-algorithms/cp-algorithms.git && cd cp-algorithms
    ```

2. Install dependencies and serve the site:

    ```console
    scripts/install-mkdocs.sh # requires pip
    mkdocs serve
    ```

   This will run the site locally so you can preview your changes. Note that some features are disabled in local builds.

### Optional Plugins

- **Git Revision Date Plugin**: Disabled by default, as it produces errors when you have uncommited changes in the working tree. Can be enabled with:

    ```console
    export MKDOCS_ENABLE_GIT_REVISION_DATE=True
    ```

- **Git Committers Plugin**: Disabled by default, as it requires a GitHub personal access token. Enable it like this:

    ```console
    export MKDOCS_ENABLE_GIT_COMMITTERS=True
    export MKDOCS_GIT_COMMITTERS_APIKEY=your_token_here
    ```

   You can generate your token [here](https://github.com/settings/tokens). Only public access permissions are needed.

## Testing Code Snippets

If your article includes code snippets, it’s helpful to include tests to ensure that they run correctly.

1. Name the code snippet:
````
```{.cpp file=snippet-name}
// code here
```
````
3. Run `extract_snippets.py` from the `test` directory to extract snippets into header files. Create a test file that includes these headers and checks their behavior.
4. You can run all tests with the `test.sh` script:
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
    51 PASSED in 49.00 seconds
    ```
   This script will run tests and display the results.

Additionally, all pull requests will be automatically tested via [GitHub Actions](https://github.com/cp-algorithms/cp-algorithms/actions).
