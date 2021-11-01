#!/usr/bin/python3
import re
import os

def write_snippet(name, lines):
    file_name = '{}.h'.format(name)
    with open(file_name, 'w') as f:
        for line in lines:
            f.write(line)

def extract_tests(filepath):
    filepath_short = os.path.basename(filepath) 
    article_name = filepath_short.split('.')[0]

    snippet_start = re.compile(r"^```\{.cpp\s+file=(\S+)\}$")
    snippet_end = re.compile(r"^```$")

    with open(filepath) as f:
        in_snippet = False;
        for line in f:
            m_start = snippet_start.match(line)
            m_end = snippet_end.match(line)

            if in_snippet and m_end:
                in_snippet = False
                write_snippet(snippet_name, lines)

            if in_snippet:
                lines.append(line)
            elif m_start:
                snippet_name = m_start.group(1)
                lines = []
                in_snippet = True


if __name__ == '__main__':
    for subdir, dirs, files in os.walk('../src/'):
        for filename in files:
            if filename.endswith(".md"):
                extract_tests(os.path.join(subdir, filename))
