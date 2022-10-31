// Makes text selectable
MathJax = {
  addCopyText(math, doc) {
      if (math.state() < MathJax.STATE.ADDTEXT) {
          if (!math.isEscaped) {
              const adaptor = doc.adaptor;
              const text = adaptor.node('span', {'aria-hidden': true, 'class': 'mathjax_ignore mjx-copytext'}, [
                adaptor.text(math.start.delim + math.math + math.end.delim)
              ]);
              adaptor.append(math.typesetRoot, text);
              // Insert thin space(s) if math is at begin or end of text
              if (math.start.n == 0) {
                  adaptor.insert(adaptor.text('\u200A'), adaptor.firstChild(math.typesetRoot));
              }
              if (math.end.n == math.end.node.length) {
                  adaptor.append(math.typesetRoot, adaptor.text('\u200A'));
              }
          }
          math.state(MathJax.STATE.ADDTEXT);
      }
  },
  startup: {
    ready() {
      MathJax._.output.chtml_ts.CHTML.commonStyles['mjx-copytext'] = {
        display: 'inline-block',
        position: 'absolute',
        top: 0, left: 0, width: 0, height: 0,
        opacity: 0,
        overflow: 'hidden'
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
    processHtmlClass: "arithmatex",
    renderActions: {
      addCopyText: [155,
        (doc) => {for (const math of doc.math) MathJax.config.addCopyText(math, doc)},
        (math, doc) => MathJax.config.addCopyText(math, doc)
      ]
    }
  }
}

document$.subscribe(() => {
  MathJax.typesetPromise()
})
