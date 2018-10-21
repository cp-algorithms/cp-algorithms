<!--?title Demo Article-->

# Demo Article

_You can [see the source of this article](https://raw.githubusercontent.com/e-maxx-eng/e-maxx-eng/master/src/demo-article.md) to better understand formatting features._

The header is made of line starting with `#` (hash) symbol. Note that also we need to add a magical `?title` comment which
defines the title of the resulting HTML page for browser and search engines (see the source of this page - it is in the top).

Text is written in paragraphs, separated with empty lines. Line breaks in paragraphs are regarded as ordinary spaces. If you
add a couple of extra spaces in the line end, they will create "hard line-break" in that place.

The code snippets are created of blocks indented with 4 spaces:

    #include <stdio.h>
    int main() {
        printf("Hello, World\n");
    }
    
For long blocks it would be good to add "show/hide" button. It is created by adding small magic span in the end of
the preceding paragraph <span class="toggle-code">Show/Hide</span>

	int phi(int n) {
		int result = n;
		for(int i = 2; i * i <= n; ++i)
			if(n % i == 0) {
				while(n % i == 0)
					n /= i;
				result -= result / i;
			}
		if(n > 1)
			result -= result / n;
		return result;
	}

### TeX and Markdown references

We use [Markdown](https://daringfireball.net/projects/markdown) for source texts and
convert them automatically to HTML.
Some [extra](https://michelf.ca/projects/php-markdown/extra/) features also could be used.

Formulas could be added thanks to `MathJax` library. Simply use `TeX` expressions inside single or double dollar marks `$`, for example:

here is an inline equation: $P \ne NP$

And here is the formula in the separate block:

$$E = mc^{2}$$

### Adding images

Small images could be pushed along with texts to the [/img](https://github.com/e-maxx-eng/e-maxx-eng/tree/master/img) subfolder. Let them be in `PNG` format and less than `200kb`. Then you can refer to them inside the article like this (see the source here):

![some image description](&imgroot&/search-bridge-formula.png)

Note that file name is prefixed with `imgroot` variable (in ampersands) which will expand to proper url prefix when shown at the site (so you need not know the precise prefix of github raw data). It would be good if you use it instead of full path urls.

Larger images should be posted to some image-hosting, like [PostImage](http://postimage.org) or [ImgUr](http://imgur.com/) - they will then give you the url to insert into the page.

You can also embed videos from youtube, as it is done in the [contrib.md](./contrib.html) file.
