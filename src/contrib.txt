<!--?title For Contributors-->
#How to Contribute

###Using GitHub

At least at first stage we are going to collaborate via means of github.

Generated pages are placed at [http://e-maxx-eng.github.io](http://e-maxx-eng.github.io).

And sources (to which you may want to contribute) are [here](http://github.com/e-maxx-eng/e-maxx-eng).

In order to make contribution consider the following steps:

1. Contact any of [admins](https://github.com/orgs/e-maxx-eng/people) and explain what
    article you want to add or improve. Get the approval.
2. Fork [source repository](https://github.com/e-maxx-eng/e-maxx-eng) and `clone` it to your
    local machine.
3. Add or modify files in `src` subfolder in Markdown format.
4. Run `compile.bat` or `compile.sh` (you'll need `PHP 5.3+` interpreter installed) and
    verify your changes opening site locally in the browser (you'll see the link in console).
5. Repeat steps `3-4` until all is well.
6. Use `commit` and `push` commands to update your copy of repository at github.
7. Use `pull-request` feature to send the request for your changes to be merged.

Please kindly refer to manuals on using `git` and `github` anywhere over internet.

###Source format

We use [Markdown](https://daringfireball.net/projects/markdown) for source texts and
convert them automatically with the help of small tool.
Some [extra](https://michelf.ca/projects/php-markdown/extra/) features also could be used.

If you have **PHP** installed, you can run `compile.bat` or `compile.sh` file in the root folder - it will parse `src`
directory and convert all the files inside into HTML documents under the new folder `target`.

Formulas could be added thanks to `MathJax` library. Simply use `TeX` expressions inside single or double dollar marks `$`, for
example:

here is an inline equation: $P \ne NP$

And here is the formula in the separate block:

$$E = mc^{2}$$

