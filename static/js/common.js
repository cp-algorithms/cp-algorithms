$(function() {

    function codeTogglerPre(elem) {
        return $(elem).parent().next("pre");
    }

    $(".toggle-code").each(function() {
        codeTogglerPre(this).hide(0);
        $(this).click(function(evt) {codeTogglerPre(evt.target).toggle(1000);});
    });

    function tocElement(toc, idx, e) {
        var style = e.tagName;
        var ee = $(e);
        var name = ee.attr('id') ? ee.attr('id') : 'toc-tgt-' + idx;
        ee.attr('id', name);
        var span = '<div class="toc-' + style + '"><a href="'
                + location.href.replace(/\#.*/, '') + '#'
                + name + '">'+ ee.text() + '<a/></div>';
        toc.append(span);
    }

    function tableOfContent() {
        var parts = $('h2,h3');
        var title = $('h1:first');
        if (parts.length < 1 || title.length < 1 || title.attr('data-toc') == 'off') {
            return;
        }
        var toc = $('<div id="toc"><strong>Table of Contents</strong><br/></div>')
            .insertAfter('h1:first');
        parts.each(function(i, e) { tocElement(toc, i, e) });
    }

    tableOfContent();
});
