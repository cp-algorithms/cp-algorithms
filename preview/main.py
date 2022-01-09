import os
from pathlib import Path
from tempfile import TemporaryDirectory
from bs4 import BeautifulSoup

def main(request):
    # Set CORS headers for the preflight request
    if request.method == 'OPTIONS':
        headers = {
            'Access-Control-Allow-Origin': '*',
            'Access-Control-Allow-Methods': 'POST',
            'Access-Control-Allow-Headers': 'Content-Type',
            'Access-Control-Max-Age': '3600'
        }
        return ('', 204, headers)

    request_json = request.get_json()
    md_content = request_json['markdown']
    html_content = render(md_content)

    headers = {
        'Access-Control-Allow-Origin': '*'
    }
    return (html_content, 200, headers)

def render(markdown: str) -> str:
    with TemporaryDirectory() as tmpdirname:
        # prepare file structure and configuration for MkDocs
        tmp_path = Path(str(tmpdirname))
        (tmp_path / "docs").mkdir(parents=True, exist_ok=True)
        (tmp_path / "docs" / "index.md").write_text(markdown)
        (tmp_path / "mkdocs.yml").write_text("""
site_name: CP Algorithms
theme:
  name: material
markdown_extensions:
  - pymdownx.arithmatex:
      generic: true
  - pymdownx.highlight
  - pymdownx.superfences
  - attr_list
  - pymdownx.emoji:
      emoji_index: !!python/name:materialx.emoji.twemoji
      emoji_generator: !!python/name:materialx.emoji.to_svg
""")

        # render the page
        os.system(f"cd {tmp_path} && mkdocs build")

        # extract the main content (without header/footer/...)
        with open(tmp_path / "site" / "index.html") as fp:
            soup = BeautifulSoup(fp, "html.parser")
            article = soup.find("article")
            article_html = ''.join([str(x) for x in article])
    return article_html
