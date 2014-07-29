$(function() {
    function codeTogglerPre(elem) {
        return $(elem).parent().next("pre");
    }
    $(".toggle-code").each(function() {
        codeTogglerPre(this).hide(0);
        $(this).click(function(evt) {codeTogglerPre(evt.target).toggle(1000);});
    });
});

