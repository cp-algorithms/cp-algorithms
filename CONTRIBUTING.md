# How to Contribute

## General information

This website (articles, design, ...) is developed via [Github](https://github.com/cp-algorithms/cp-algorithms). And everybody is welcome to help out. All you need is a Github account.

Generated pages are compiled and published at [https://cp-algorithms.com](https://cp-algorithms.com).

In order to make contribution consider the following steps:

1. Go to an article that you want to change, and click the pencil icon :material-pencil: next to the article title.
2. Fork the repository if requested.
3. Modify the article.
4. Use the [preview page](preview.md) to check if you are satisfied with the result.
5. Make a commit by clicking the _Propose changes_ button.
6. Create a pull-request by clicking the _Compare & pull request_ button.
7. Somebody from the core team will look over the changes. This might take a few hours/days.

In case you want to make some bigger changes, like adding a new article, or edit multiple files, you should fork the project in the traditional way, create a branch, modify the files in the Github UI or locally on your computer, and create a pull-request.
If you are unfamiliar with the workflow, read [Step-by-step guide to contributing on GitHub](https://www.dataschool.io/how-to-contribute-on-github/).

If you're making a new article or moving existing one to a different place, please make sure that your changes are reflected in

- The list of all articles in [navigation.md](https://github.com/cp-algorithms/cp-algorithms/blob/master/src/navigation.md);
- The list of new articles in [README.md](https://github.com/cp-algorithms/cp-algorithms/blob/master/README.md) (if it is a new article).

## Syntax

We use [Markdown](https://daringfireball.net/projects/markdown) for the articles, and use the [Material for MkDocs](https://squidfunk.github.io/mkdocs-material/) to render the Markdown articles into HTML.

For advanced Markdown features of Material for MkDocs see their [reference pages](https://squidfunk.github.io/mkdocs-material/reference/formatting), like:

- [Math formulas with MathJax](https://squidfunk.github.io/mkdocs-material/reference/mathjax/#usage)
  Notice that you need to have an empty line before and after a `$$` math block.
- [Code blocks](https://squidfunk.github.io/mkdocs-material/reference/code-blocks/#usage) for code snippets.
- [Admonitions](https://squidfunk.github.io/mkdocs-material/reference/admonitions/#usage) (e.g. to decor theorems, proofs, problem examples).
- [Content tabs](https://squidfunk.github.io/mkdocs-material/reference/content-tabs/#usage) (e.g. for code examples in several languages).
- [Data tables](https://squidfunk.github.io/mkdocs-material/reference/data-tables/#usage).

However not everything of the features should be used, and some of the features are not enabled or require a paid subscription.

By default the first header (`# header`) will be also the HTML title of the article. In case the header contains a math formula, you can define a different HTML title with:

```markdown
---
tags:
    - ...
title: Alternative HTML title
---
# Proof of $a^2 + b^2 = c^2$

remaining article
```

### Redirects

Files should not be moved or renamed without making redirects. A redirect page should generally look as follows:

```md
<meta http-equiv="refresh" content="0; url=https://cp-algorithms.com/<new section>/<new name>.html">
# <Article name>
Article was moved (renamed). <a href="<new section>/<new name>.html">new URL</a>.
```

### Tags

To distinguish original and translatory articles, they should be marked with corresponding tags. For original articles, it's

```md
---
tags:
    - Original
---
```

And for translated articles, it's

```md
---
tags:
    - Translated
e_maxx_link: ...
---
```

Here, instead of `...` one should place the last part of the link to the original article. E.g. for [Euler function article](http://e-maxx.ru/algo/euler_function) it should be


```md
---
tags:
    - Translated
e_maxx_link: euler_function
---
```


## Some conventions

* We have agreed as of issue [#83](https://github.com/cp-algorithms/cp-algorithms/issues/83) to express binomial coefficients with `\binom{n}{k}` instead of `C_n^k`. The first one renders as $\binom{n}{k}$ and is a more universal convention. The second would render as $C_n^k$.

## Adding Problems

Try to add problems in ascending order of their difficulty. If you don't have enough time to do so, still add the problem. Lets hope that the next person will sort them accordingly.

## Local development

You can render the pages locally. All you need is Python, with the installed `mkdocs-material` package.

```console
$ git clone --recursive https://github.com/cp-algorithms/cp-algorithms.git && cd cp-algorithms
$ scripts/install-mkdocs.sh # requires pip installation
$ mkdocs serve
```

Note that some features are disabled by default for local builds.

### Git revision date plugin

Disabled because it might produce errors when there are uncommitted changes in the working tree.

To enable it, set the environment variable `MKDOCS_ENABLE_GIT_REVISION_DATE` to `True`:

```console
$ export MKDOCS_ENABLE_GIT_REVISION_DATE=True
```

### Git committers plugin

Disabled because it takes a while to prepare and also requires Github personal access token to work with Github APIs.

To enable it, set the environment variable `MKDOCS_ENABLE_GIT_COMMITTERS` to `True` and store your personal access token in the environment variable `MKDOCS_GIT_COMMITTERS_APIKEY`. You can generate the token [here](https://github.com/settings/tokens). Note that you only need the public access, so you shouldn't give the token any permissions.

```console
$ export MKDOCS_ENABLE_GIT_COMMITTERS=True
$ export MKDOCS_GIT_COMMITTERS_APIKEY= # put your PAT here 
```

## Tests

If your article involves code snippets, then it would be great you also contribute tests for them.
This way we can make sure that the snippets actually work, and don't contain any bugs.

Creating tests works like this:
You have to name each snippet that you want to test in the markdown article:

    ```{.cpp file=snippet-name}
    // some code
    ```

In the directory `test` you find a script `extract_snippets.py` that you can run.
This script extracts from every article all named snippets, and puts them in C++ header files: `snippet-name.h`
In the folder you can create a cpp file, that includes these snippets headers, and tests their behaviour.
If the snippets don't work, the test program should return 1 instead of 0.

You can run all tests with the script `test.sh`.

```console
$ cd test
$ ./test.sh
Running test_aho_corasick.cpp - Passed in 635 ms
Running test_balanced_brackets.cpp - Passed in 1390 ms
Running test_burnside_tori.cpp - Passed in 378 ms
...
Running test_vertical_decomposition.cpp - Passed in 2397 ms

51 PASSED in 49.00 seconds
```

Also, every pull-request will automatically tested via [Github Actions](https://github.com/cp-algorithms/cp-algorithms/actions).
