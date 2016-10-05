<!--?title For Contributors-->
#How to Contribute

At least at first stage we are going to collaborate via means of github.

Generated pages are placed at [http://e-maxx-eng.appspot.com](http://e-maxx-eng.appspot.com).

And sources (to which you may want to contribute) are [here](http://github.com/e-maxx-eng/e-maxx-eng/tree/master/src).

In order to make contribution consider the following steps:

1. Fork [source repository](https://github.com/e-maxx-eng/e-maxx-eng).
2. Add or modify files in `src` subfolder in Markdown format (you can do this in web-interface of github now).
3. Make sure you added `<!--?title ... -->` to your page and the corresponding link to main (index) page.
3. Use [Test-Your-Page form](./test.php) to check if you are satisfied with the result.
4. Use `pull-request` feature to send the request for your changes to be merged.
5. It may take few hours or few days before someone who have admin rights will merge your request. Contact any of admins personally to speed up this process!
6. After merging it will take about 5 minutes before updated html page will appear at the site.

Please kindly refer to manuals on using `git` and `github` anywhere over internet. You may also watch this demo video:

<div style="text-align:center">
<iframe width="420" height="315" src="https://www.youtube.com/embed/TrBBw4J9X30" frameborder="0" allowfullscreen></iframe>
</div>

###Your Authorship is Preserved

If you want, you can place note like "translated by Rodion Gork" at the bottom of the article, probably with the link to your GitHub or CodeForces account for example. However it is not necessary (and not very convenient if the article was edited by several people). All commits [are tracked in GitHub](https://github.com/e-maxx-eng/e-maxx-eng/commits/master) and so it is always easy to determine or prove the authorship of any line (especially with "blame" functionality on a specific file).

###Source format

We use [Markdown](https://daringfireball.net/projects/markdown) for source texts and
convert them automatically to HTML.
Some [extra](https://michelf.ca/projects/php-markdown/extra/) features also could be used.

Formulas could be added thanks to `MathJax` library. Simply use `TeX` expressions inside single or double dollar marks `$`, for example:

here is an inline equation: $P \ne NP$

And here is the formula in the separate block:

$$E = mc^{2}$$

###Adding images

Small images could be pushed along with texts to the [/img](https://github.com/e-maxx-eng/e-maxx-eng/tree/master/img) subfolder. Let them be in `PNG` format and less than `200kb`. Then you can refer to them inside the article with the tag:

    ![some image description](&imgroot&/my-image.png)

Here `my-image.png` should be your file name, while `&imgroot&` is some magic which will expand to proper url prefix when shown at the site (so you need not know the precise prefix of github raw data).

Larger images should be posted to some image-hosting, like [PostImage](http://postimage.org) or [ImgUr](http://imgur.com/) - they will then give you the url to insert into the page.
