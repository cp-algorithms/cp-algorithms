---
title: How to Contribute
hide:
  - navigation
---
# How to Contribute

## General information

This website (articles, design, ...) is developed via [Github](https://github.com/e-maxx-eng/e-maxx-eng). And everybody is welcome to help out. All you need is a Github account.

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

In case you are adding a new article, start by copying some other article in order to have the required header lines, and make sure to link to the article from the main (index.md) page.

## Syntax

We use [Markdown](https://daringfireball.net/projects/markdown) for the articles, and use the [Material for MkDocs](https://squidfunk.github.io/mkdocs-material/) to render the Markdown articles into HTML.

For advanced Markdown features of Material for MkDocs see their [reference pages](https://squidfunk.github.io/mkdocs-material/reference/formatting), like:

- [Math formulas with MathJax](https://squidfunk.github.io/mkdocs-material/reference/mathjax/#usage)
  Notice that you need to have an empty line before and after a `$$` math block.
- [Data tables](https://squidfunk.github.io/mkdocs-material/reference/data-tables/#usage)

However not everything of the features should be used, and some of the features are not enabled or require a paid subscription.

## Some conventions

* We have agreed as of issue [#83](https://github.com/e-maxx-eng/e-maxx-eng/issues/83) to express binomial coefficients with `\binom{n}{k}` instead of `C_n^k`. The first one renders as $\binom{n}{k}$ and is a more universal convention. The second would render as $C_n^k$.

## Adding Problems

Try to add problems in ascending order of their difficulty. If you don't have enough time to do so, still add the problem. Lets hope that the next person will sort them accordingly.

## Local development

You can render the pages very easily also locally.
All you need is Python, with the installed `mkdocs-material` package.

```console
$ pip install mkdocs-material
$ mkdocs serve
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

Also, every pull-request will automatically tested via [Github Actions](https://travis-ci.org/e-maxx-eng/e-maxx-eng/).
