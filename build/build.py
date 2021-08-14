"""Converter of the e-maxx-eng project into HTML

Todos:
- fix header links (e.g. in the Segmented Tree page)
- add CSS
- add code highlighting
- add search page
- add remaining template values
- title not found
"""
from argparse import ArgumentParser
from datetime import datetime
from pathlib import Path
import re
from contextlib import redirect_stderr
import io

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
        "--template-path",
        type=lambda p: Path(p).resolve(),
        required=True,
        help="path to the template file"
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
        template_path = kwargs.pop("template_path")
        self.template = template_path.read_text()
        self.baseurl = kwargs.pop("baseurl")

        super().__init__(**kwargs)

    def convert(self, md_content: str) -> str:
        lines = md_content.split("\n")
        title_regex = re.compile(r"\<!--\?title\s+(.*)\s*--\>")

        title = "Fix later"
        if m := title_regex.match(lines[0].strip()):
            title = m.group(1)
            lines.pop(0)
        else:
            # raise Exception("Title missing")
            pass

        # fix for markdown bugs
        cleaned_lines = []
        for line in lines:
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

        content = (
            self.template
            .replace("&title&", title)
            .replace("&year&", str(datetime.now().year))
            .replace("&baseurl&", self.baseurl)
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
        template_path=args.template_path,
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
            html_content = md.convert(md_content)
        if f.getvalue():
            print(relative_path)
            print(f.getvalue())

        # write
        output_path = args.output_dir / relative_path.with_suffix(".html")
        output_path.parent.mkdir(parents=True, exist_ok=True)
        output_path.write_text(html_content)


if __name__ == '__main__':
    main()
