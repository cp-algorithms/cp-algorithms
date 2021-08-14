"""Converter of the e-maxx-eng project into HTML

Todos:
- fix header links (e.g. in the Segmented Tree page)
- add CSS
- add code highlighting
- add search page
- title not found
"""
from argparse import ArgumentParser
from datetime import datetime
from pathlib import Path
import re
from contextlib import redirect_stderr
import io
from urllib.parse import urljoin

import markdown  # type: ignore
from tqdm import tqdm  # type: ignore


def parse_arguments(args=None):
    arg_parser = ArgumentParser(
        description="Convert the e-maxx-eng markdown pages into HTML"
    )
    arg_parser.add_argument(
        "-i", "--input-dir",
        type=lambda p: Path(p).resolve(),
        required=True,
        help="path to the input markdown files"
    )
    arg_parser.add_argument(
        "-o", "--output-dir",
        type=lambda p: Path(p).resolve(),
        required=True,
        help="path to the output files"
    )
    arg_parser.add_argument(
        "--template-dir",
        type=lambda p: Path(p).resolve(),
        required=True,
        help="path to the template directory"
    )
    arg_parser.add_argument(
        "--baseurl",
        default=None,
        help="Base-URL of the website"
    )
    arg_parser.add_argument(
        "--show-progress",
        const=True,
        action="store_const",
        default=False,
        help="show progress bar"
    )
    arguments = arg_parser.parse_args(args)
    return arguments


class MarkdownConverter(markdown.Markdown):
    def __init__(self, **kwargs):
        self.template_dir = kwargs.pop("template_dir")
        self.default_template = "default.html"
        self.baseurl = kwargs.pop("baseurl")
        self.history_baseurl = (
            "https://github.com/e-maxx-eng/e-maxx-eng/commits/master/src/"
        )

        super().__init__(**kwargs)

    def convert(self, md_content: str, relative_url: Path) -> str:
        lines = md_content.split("\n")
        title_regex = re.compile(r"\<!--\?title\s+(.*)\s*--\>")
        template_regex = re.compile(r"\<!--\?template\s+(.*)\s*--\>")

        title = "Title"
        template_name = self.default_template
        filtered_lines = []
        for line in lines:
            if m := title_regex.match(line.strip()):
                title = m.group(1).strip()
            elif m := template_regex.match(line.strip()):
                template_name = m.group(1).strip()
            else:
                filtered_lines.append(line)
        lines = filtered_lines

        # fix for markdown bugs
        cleaned_lines = []
        for line in lines:
            line = line.replace("&imgroot&", "./img")
            line = line.replace(r"\\\\", r"\\")
            if line.strip().startswith("```cpp"):
                line = "```cpp"
            line = line.replace(r"\\_", "_")
            if line.strip().startswith("$$"):
                cleaned_lines.append("$$")
                line = line.replace("$$", "", 1)
            if line.strip().endswith("$$"):
                cleaned_lines.append(line.replace("$$", ""))
                cleaned_lines.append("$$")
            else:
                cleaned_lines.append(line)

        html_content = super().convert("\n".join(cleaned_lines))

        history_url = urljoin(self.history_baseurl, str(relative_url))
        content = (
            (self.template_dir / template_name).read_text()
            .replace("&title&", title)
            .replace("&year&", str(datetime.now().year))
            .replace("&baseurl&", self.baseurl)
            .replace("&history&", history_url)
            .replace("&text&", html_content)
        )

        return content


def main():
    args = parse_arguments()

    # prepare markdown converter
    extensions = [
        "fenced_code",  # code blocks formatting
        "markdown_math_escape",  # support for math formula
        "mdx_linkify",  # convert text that looks like links into links
    ]
    baseurl = args.baseurl or f"{args.output_dir}/"
    md = MarkdownConverter(
        extensions=extensions,
        template_dir=args.template_dir,
        baseurl=baseurl
    )

    input_paths = list(args.input_dir.glob("**/*.md"))
    for input_path in tqdm(input_paths, disable=not args.show_progress):
        relative_path = input_path.relative_to(args.input_dir)
        # read
        md_content = input_path.read_text()

        # convert
        f = io.StringIO()
        with redirect_stderr(f):
            html_content = md.convert(md_content, relative_path)
        if f.getvalue():
            print(relative_path)
            print(f.getvalue())

        # write
        output_path = args.output_dir / relative_path.with_suffix(".html")
        output_path.parent.mkdir(parents=True, exist_ok=True)
        output_path.write_text(html_content)


if __name__ == '__main__':
    main()
