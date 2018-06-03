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
        if (parts.size() < 1 || title.size() < 1 || title.attr('data-toc') == 'off') {
            return;
        }
        var toc = $('<div id="toc"><strong>Table of Contents</strong><br/></div>')
            .insertAfter('h1:first');
        parts.each(function(i, e) { tocElement(toc, i, e) });
    }

    function hash(s) {
        var sum = 0;
        for (var i = 0; i < s.length; i++) {
            sum += s.charCodeAt(i);
            sum <<= 1;
            sum = (sum % 0x10000) ^ (sum >> 16);
        }
        return sum;
    }

    function sendCnt() {
        var date = new Date();
        var k = 'stats.' + date.getYear() + '.' + date.getMonth() + '.' + date.getDay();
        var isNew = localStorage.getItem(k) === null;
        if (isNew) {
            localStorage.clear();
            localStorage.setItem(k, 1);
        }
        var data = {
            url: location.href,
            time: date.getTime(),
            isNew: isNew,
        };
        data = JSON.stringify(data);
        data = btoa(data);
        data = data + '.' + hash(data);
        var root = location.href.replace(/^([a-z]+\:\/\/[^\/]+).*/, '$1');
        $.post(root + '/cnt.php?d=' + data, 'r=' + Math.random(), function(d) {
        });
    }
    
    function visitors() {
        var data = $('body').attr('data-v');
        if (!data) {
            return;
        }
        var short = data.replace(/\S+?(\d+\:\S+).*/, '$1');
        var span = $('<span>' + short + '</span>')
                .css('float', 'right').css('cursor', 'pointer')
                .appendTo('#footer');
        span.click(function() {
            alert('Last week stats:\n\n' + data.replace(/\s/g, '\r'));
        });
    }
    
    window.onresize = function(){
        var w0 = 980;
        var w1 = $(window).width();
        if (w1 < w0) {
            var zoom = Math.floor(w1 * 100 / w0);
            document.body.style.zoom = "" + zoom + "%";
            document.body.style.MozTransform = 'scale(0.' + zoom + ')';
            document.body.style.MozTransformOrigin = '0 0';
        } else {
            document.body.style.zoom = "";
            document.body.style.MozTransform = '';
        }
    };
    
    tableOfContent();
    visitors();
    setTimeout(sendCnt, 5000);
    setTimeout(window.onresize, 350);
});


