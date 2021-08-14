from argparse import ArgumentParser
from pathlib import Path
# from typing import Optional

import markdown
from tqdm import tqdm


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
        "--show-progress",
        const=True,
        action="store_const",
        default=False,
        help="show progress bar"
    )
    arguments = arg_parser.parse_args(args)
    return arguments


def main():
    args = parse_arguments()

    # prepare markdown converter
    extensions = []
    md = markdown.Markdown(extensions=extensions)

    input_paths = list(args.input_dir.glob("**/*.md"))
    for input_path in tqdm(input_paths, disable=not args.show_progress):
        # read
        md_content = input_path.read_text()

        # convert
        html_content = md.convert(md_content)

        # write
        relative_path = input_path.relative_to(args.input_dir)
        output_path = args.output_dir / relative_path.with_suffix(".html")
        output_path.parent.mkdir(parents=True, exist_ok=True)
        output_path.write_text(html_content)


if __name__ == '__main__':
    main()
