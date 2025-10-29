import argparse
import re
import os
import sys
import shutil
import logging
from typing import List, Optional
from dataclasses import dataclass


@dataclass
class Snippet:
    name: str
    lines: List[str]


def write_snippet(target_dir: os.PathLike, snippet: Snippet):
    assert os.path.exists(target_dir) and os.path.isdir(target_dir)

    file_name = f'{snippet.name}.h'
    with open(os.path.join(target_dir, file_name), 'w', encoding='utf-8') as f:
        f.writelines(snippet.lines)


def extract_snippets(filepath: os.PathLike) -> List[Snippet]:
    with open(filepath, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    snippets = []

    snippet_start = re.compile(r"^```\{.cpp\s+file=(\S+)\}$")
    snippet_end = re.compile(r"^```$")

    snippet_start_line: Optional[int] = None
    snippet_name: Optional[str] = None

    for line_idx, line in enumerate(lines):
        match_snippet_start = snippet_start.match(line)
        match_snippet_end = snippet_end.match(line)
        assert not (match_snippet_start and match_snippet_end)

        if match_snippet_start:
            assert snippet_start_line is None
            assert snippet_name is None

            snippet_start_line = line_idx
            snippet_name = match_snippet_start.group(1)
        elif match_snippet_end:
            if snippet_start_line is not None:
                assert snippet_start_line is not None
                assert snippet_name is not None

                snippet = lines[snippet_start_line + 1: line_idx]

                snippets.append(Snippet(name=snippet_name, lines=snippet))

            snippet_start_line = None
            snippet_name = None

    return snippets


def main(args: argparse.Namespace) -> None:
    src_dir = args.src_dir
    target_dir = args.target_dir

    logging.info(f'--src-dir="{src_dir}"')
    logging.info(f'--target-dir="{target_dir}"')

    assert os.path.isdir(src_dir)

    if args.remove_prev_target_dir and os.path.exists(target_dir):
        logging.info(f'Script launched with --remove-prev-target-dir flag')
        logging.info(f'Removing --target-dir="{target_dir}"')
        shutil.rmtree(target_dir)

    if not os.path.exists(target_dir):
        logging.info(
            f'--target-dir="{target_dir}" does not exist, creating')
        os.makedirs(target_dir, exist_ok=False)
        assert os.path.isdir(
            target_dir), f'Failed to create --target-dir: "{target_dir}"'

    snippets = []

    for subdir, _, files in os.walk(src_dir):
        for filename in files:
            if filename.lower().endswith('.md'):
                filepath = os.path.join(subdir, filename)
                logging.debug(f'Extracting snippets from {filename}')
                snippets.extend(extract_snippets(filepath))

    n_snippets = len(snippets)
    for snippet_idx, snippet in enumerate(snippets, start=1):
        logging.debug(
            f'({snippet_idx}/{n_snippets}) writing snippet {snippet.name} to "{target_dir}"')
        write_snippet(target_dir, snippet)

    logging.info(
        f'All done, {n_snippets} snippets have been written to "{target_dir}"')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Recursively extracts specially annotation cpp code snippets from src dir with .md files')

    parser.add_argument('--src-dir', type=str, required=True,
                        help='path to the directory with .md source to recursively look for cpp snippets with {.cpp file=...} annotation')
    parser.add_argument('--target-dir', type=str, required=True,
                        help='path to the resulting directory with .h snippets extracted from src-dir')
    parser.add_argument('--remove-prev-target-dir', action='store_true',
                        help='remove --target-dir prior to generating snippets')

    logging_level_names = list(logging.getLevelNamesMapping().keys())
    assert 'INFO' in logging_level_names
    parser.add_argument('--logging-level', type=str, choices=logging_level_names,
                        default='INFO', help='script logging level')

    args = parser.parse_args()

    logging.basicConfig(
        stream=sys.stdout,
        format='%(asctime)s %(module)-15s - [%(levelname)-6s] - %(message)s',
        datefmt='%H:%M:%S',
        level=args.logging_level
    )

    main(args)
