---
title: Preview
hide:
  - navigation
---
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
<script>
  $(document).ready(function(){
    $("#previewBtn").click(function(){
      var markdown = $("#markdownInput").val();
      var URL = "https://us-central1-cp-algorithms.cloudfunctions.net/convert-markdown-mkdocs";
      var data = {"markdown": markdown};
      var refresh_script = `<scr` + `ipt>MathJax.typeset();</scr` + `ipt>`;
      $.ajax({
        url: URL,
        contentType: "application/json",
        method: 'POST',
        data: JSON.stringify(data),
        success: function(data) { $("#previewArea").html(data + "\n" + refresh_script); }
      });
    });
  });
</script>
# Preview the rendering of your article

<form>
  <textarea style="width:90%;height:400px;" id="markdownInput" placeholder="paste your text here..."></textarea>
  <br/>
  <br/>
  <button type='button' class="md-button md-button--primary" id="previewBtn">Preview</button>
</form>
</center>
<hr/>

<div id="previewArea">
</div>
<br/>
