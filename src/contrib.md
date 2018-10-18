<!--?title For Contributors-->
# How to Contribute

## General information

We collaborate via means of github.

Generated pages are compiled and published at [https://cp-algorithms.com](https://cp-algorithms.com).

And sources (to which you may want to contribute) are [here](http://github.com/e-maxx-eng/e-maxx-eng/tree/master/src).

In order to make contribution consider the following steps:

1. Fork [source repository](https://github.com/e-maxx-eng/e-maxx-eng).
2. Add or modify files in `src` subfolder in Markdown format (you can do this in web-interface of github now).
3. Make sure you added `<!--?title ... -->` to your page and the corresponding link to main (index) page.
3. Use [Test-Your-Page form](./test.php) to check if you are satisfied with the result.
4. Use `pull-request` feature to send the request for your changes to be merged.
5. It may take few hours or few days before someone who have admin rights will merge your request. Contact any of admins personally to speed up this process!
6. After merging it will take about 5 minutes before updated html page will appear at the site.

**You may start with this [demo-article](./demo-article.html) or even use [its source](https://raw.githubusercontent.com/e-maxx-eng/e-maxx-eng/master/src/contrib.md) as a template for your new article.**

Please kindly refer to manuals on using `git` and `github` anywhere over internet. You may also watch this demo video:

<div style="text-align:center">
<iframe width="420" height="315" src="https://www.youtube.com/embed/TrBBw4J9X30" frameborder="0" allowfullscreen></iframe>
</div>

## Your Authorship is Preserved

Some contributors add explicit links to their profiles at the bottom of the translated articles. However it is discouraged and simply not very convenient if the article was edited by several people. Every page has `Page Authors` link in its top - this link leads to the github commit history, so it is always easy to determine or prove the authorship (even of any single line). Just make sure that your GitHub profile (which is mentioned in history) provides enough information about you.

## Source format

We use [Markdown](https://daringfireball.net/projects/markdown) for source texts and
convert them automatically to HTML.
Some [extra](https://michelf.ca/projects/php-markdown/extra/) features also could be used.

Formulas could be added thanks to `MathJax` library. Simply use `TeX` expressions inside single or double dollar marks `$`, for example:

here is an inline equation: $P \ne NP$

And here is the formula in the separate block:

$$E = mc^{2}$$

## Some conventions

* We have agreed as of issue [#83](https://github.com/e-maxx-eng/e-maxx-eng/issues/83) to express binomial coefficients with `\binom{n}{k}` instead of `C_n^k`. The first one renders as $\binom{n}{k}$ and is a more universal convention. The second would render as $C_n^k$.

## Adding images

Small images could be pushed along with texts to the [/img](https://github.com/e-maxx-eng/e-maxx-eng/tree/master/img) subfolder. Let them be in `PNG` format and less than `200kb`. Then you can refer to them inside the article with the tag:

    ![some image description](&imgroot&/my-image.png)

Here `my-image.png` should be your file name, while `&imgroot&` is some magic which will expand to proper url prefix when shown at the site (so you need not know the precise prefix of github raw data).

Larger images should be posted to some image-hosting, like [PostImage](http://postimage.org) or [ImgUr](http://imgur.com/) - they will then give you the url to insert into the page.

## Modifying CSS and JS files

This is not something you usually need to do, when just writing content. It is rather for exceptional cases there arose necessity to improve general page style or behavior. These files are (due to certain technical reasons) in the other branch of the same github repository: https://github.com/e-maxx-eng/e-maxx-eng/tree/gh-pages - please, be careful here, as usually changes will affect the whole site. Also make sure site's cache and your browser cache is expired after changes done, otherwise testing could be bewildering.

## Creating anchors and link to them

It is possible to generate HTLM anchors for sections of an article.
E.g. the following generates a header and a named anchor.

    ## Implementation ## {#implementation}

And then link to it from the same or a different article:

    For more detail read the [Implementation](#implementation).
    More infos in [Impl. of Segmenttree](./data_structures/segment_tree.html#implementation).

## Page Template

Template for the pages (the one which creates small violet header and footer, determines the layout of the text, includes css and js files) is now also stored in this repo, in [src/\_templates](https://github.com/e-maxx-eng/e-maxx-eng/tree/master/src/_templates) folder. So in case you find some bugs in it, or with the passing of time some new features may be needed in it - create PR to improve it. Note that for testing purposes the alternative template could be created and used for specific page with the inclusion of special comment as shown below:

 `<!--?template myfunnytemplate-->`

The templates are cached for about 3600 seconds, rather than 300 seconds for ordinary pages, so be patient :)

## Tests

If your article involves code snippets, then it would be great you also contribute tests for them.
This way we can make sure that the snippets actually work, and don't contain any bugs.

Creating tests works like this:
You have to name each snippet that you want to test in the markdown article:

    ```cpp snippet-name
    // some code
    ```

In the directory `test` you find a script `extract_snippets.py` that you can run.
This script extracts from every article all named snippets, and puts them in C++ header files: `snippet-name.h`
In the folder you can create a cpp file, that includes these snippets headers, and tests their behaviour.
If the snippets don't work, the test program should return 1 instead of 0.

You can run all tests with the script `test.sh`.
Also, every pull-request will automatically tested via [Travis CI](https://travis-ci.org/e-maxx-eng/e-maxx-eng/), and the result of the tests will be shown.
