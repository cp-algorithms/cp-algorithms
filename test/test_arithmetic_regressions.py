"""Executable regressions for article snippets: python3 test_arithmetic_regressions.py."""
import os
from pathlib import Path
import re
import shlex
import subprocess
import tempfile
import unittest

SRC = Path(__file__).resolve().parents[1] / 'src'


def snippet(path, containing, language='cpp'):
    text = (SRC / path).read_text()
    blocks = re.findall(r'^```(?:' + language + r'|\{\.' + language + r'[^}]*\})\n(.*?)^```', text, re.M | re.S)
    return next(block for block in blocks if containing in block)


class ArithmeticRegressions(unittest.TestCase):
    def cpp(self, code, cases=(('', None),)):
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / 'test.cpp'
            executable = Path(directory) / 'test'
            source.write_text('#include <bits/stdc++.h>\nusing namespace std;\n' + code)
            command = shlex.split(os.environ.get('CXX', 'g++'))
            command += shlex.split(os.environ.get('CXXFLAGS', '-std=c++17 -O2'))
            subprocess.run(command + [str(source), '-o', str(executable)], check=True, capture_output=True, text=True)
            outputs = []
            for data, expected in cases:
                result = subprocess.run([str(executable)], input=data, capture_output=True, text=True, timeout=10)
                self.assertEqual(result.returncode, 0, result.stderr)
                if expected is not None:
                    self.assertEqual(result.stdout.strip(), expected)
                outputs.append(result.stdout)
            return outputs

    def test_discrete_root_products(self):
        code = snippet('algebra/discrete-root.md', 'int powmod')
        cases = [('65537 1 3\n', '1\n3')]
        for p in [3, 5, 7, 11, 17, 31]:
            for k in [1, 2, 3, 7]:
                for a in [0, 1, 2, p - 1]:
                    roots = [x for x in range(p) if pow(x, k, p) == a]
                    cases.append((f'{p} {k} {a}\n', str(len(roots)) + ('\n' + ' '.join(map(str, roots)) if roots else '')))
        self.cpp(code, cases)


if __name__ == '__main__':
    unittest.main()
