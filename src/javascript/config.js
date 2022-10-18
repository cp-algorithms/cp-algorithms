// Makes text selectable
MathJax = {
  startup: {
    ready() {
      const {TeXFont} = MathJax._.output.chtml.fonts.tex_ts;
      const {CHTMLFontData} = MathJax._.output.chtml.FontData;
      const {CHTMLTextNode} = MathJax._.output.chtml.Wrappers.TextNode;

      for (const name of Object.keys(TeXFont.defaultChars)) {
        var chars = TeXFont.defaultChars[name];
        for (const n of Object.keys(chars)) {
          const options = chars[n][3];
          if (options && options.c) {
            options.c = options.c.replace(/\\[0-9A-F]+/ig, (x) => String.fromCodePoint(parseInt(x.substr(1), 16)));
          } else if (options) {
            options.c = String.fromCodePoint(parseInt(n));
          } else {
            chars[n][3] = {c: String.fromCodePoint(parseInt(n))};
          }
        }
      };
      delete TeXFont.defaultStyles['mjx-c::before'];

      CHTMLFontData.prototype.addCharStyles = function (styles, vclass, n, data, charUsed) {
        const options = data[3];
        const letter = (options.f !== undefined ? options.f : vletter);
        const selector = 'mjx-c' + this.charSelector(n) + (letter ? '.TEX-' + letter : '');
        styles[selector + '::before'] = {padding: this.padding(data, 0, options.ic || 0)};
      };

      CHTMLTextNode.prototype.toCHTML = function (parent) {
        this.markUsed();
        const adaptor = this.adaptor;
        const variant = this.parent.variant;
        const text = this.node.getText();
        if (variant === '-explicitFont') {
          adaptor.append(parent, this.jax.unknownText(text, variant, this.getBBox().w));
        } else {
          let utext = '';
          const chars = this.remappedText(text, variant);
          for (const n of chars) {
            const data = this.getVariantChar(variant, n)[3];
            if (data.unknown) {
              utext += String.fromCodePoint(n);
            } else {
              utext = this.addUtext(utext, variant, parent);
              const font = (data.f ? ' TEX-' + data.f : '');
              adaptor.append(parent, this.html('mjx-c', {class: this.char(n) + font}, [
                this.text(data.c || String.fromCodePoint(n))
              ]));
              this.font.charUsage.add([variant, n]);
            }
          }
          this.addUtext(utext, variant, parent);
        }
      };
      CHTMLTextNode.prototype.addUtext = function (utext, variant, parent) {
        if (utext) {
          this.adaptor.append(parent, this.jax.unknownText(utext, variant));
        }
        return '';
      };

      MathJax.startup.defaultReady();
    }
  },
  tex: {
    inlineMath: [["\\(", "\\)"]],
    displayMath: [["\\[", "\\]"]],
    processEscapes: true,
    processEnvironments: true
  },
  options: {
    ignoreHtmlClass: ".*|",
    processHtmlClass: "arithmatex"
  }
}

document$.subscribe(() => {
  MathJax.typesetPromise()
})
