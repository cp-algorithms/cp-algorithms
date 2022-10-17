import subprocess 
from pathlib import Path
from tempfile import TemporaryDirectory
from bs4 import BeautifulSoup
import time

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
    with TemporaryDirectory() as tmpdirname:
        html_content = render(md_content, tmpdirname)

    headers = {
        'Access-Control-Allow-Origin': '*'
    }
    return (html_content, 200, headers)

def render(markdown: str, directory: str) -> str:
    # prepare file structure and configuration for MkDocs
    tmp_path = Path(str(directory))
    (tmp_path / "docs").mkdir(parents=True, exist_ok=True)
    (tmp_path / "mkdocs.yml").write_text("""
site_name: CP Algorithms
theme:
  name: material
markdown_extensions:
  - pymdownx.arithmatex:
      generic: true
  - pymdownx.highlight
  - admonition
  - pymdownx.details
  - pymdownx.superfences
  - pymdownx.tabbed:
      alternate_style: true
  - attr_list
  - pymdownx.emoji:
      emoji_index: !!python/name:materialx.emoji.twemoji
      emoji_generator: !!python/name:materialx.emoji.to_svg

plugins:
  - macros
""")
    (tmp_path / "docs" / "index.md").write_text(markdown)

    # render the page
    
    start_time = time.time()
    subprocess.run(['mkdocs', 'build', '--dirty'], cwd=tmp_path) 
    print(f"finish dirty build: {time.time() - start_time:2.5f}s")

    # extract the main content (without header/footer/...)
    with open(tmp_path / "site" / "index.html") as fp:
        soup = BeautifulSoup(fp, "html.parser")
        article = soup.find("article")
        article_html = ''.join([str(x) for x in article])
    return article_html


if __name__ == "__main__":
    with TemporaryDirectory() as tmpdirname:
        print(render("# H1", tmpdirname))
