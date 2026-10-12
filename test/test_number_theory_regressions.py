"""Executable regressions for article snippets: python3 test_number_theory_regressions.py."""
import os
from pathlib import Path
import re
import shlex
import subprocess
import tempfile
import textwrap
import unittest

SRC = Path(__file__).resolve().parents[1] / 'src'


def snippet(path, containing, language='cpp'):
    text = (SRC / path).read_text()
    blocks = re.findall(r'^[ \t]*```(?:' + language + r'|\{\.' + language + r'[^}]*\})\n(.*?)^[ \t]*```', text, re.M | re.S)
    return textwrap.dedent(next(block for block in blocks if containing in block))



class NumberTheoryRegressions(unittest.TestCase):
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

    def test_factorial_modulo_products(self):
        code = snippet('algebra/factorial-modulo.md', 'int factmod')
        self.cpp(code + r"""
int main() {
    assert(factmod(50000, 100003) == 100001);
    for (int p : {2,3,5,7,17,101}) {
        long long expected = 1;
        for (int n = 1; n <= 1000; ++n) {
            int x = n;
            while (x % p == 0) x /= p;
            expected = expected * x % p;
            assert(factmod(n,p) == expected);
        }
    }
}
""")

    def test_crt_wide_products(self):
        code = r"""
long long mod_inv(long long a,long long m){long long b=m,u=1,v=0;while(b){long long q=a/b;tie(a,b)=make_pair(b,a-q*b);tie(u,v)=make_pair(v,u-q*v);}return (u%m+m)%m;}
""" + snippet('algebra/chinese-remainder-theorem.md', 'struct Congruence')
        self.cpp(code + r"""
int main(){mt19937_64 rng(15);long long p=1000000007,q=1000000009,M=p*q;
assert(chinese_remainder_theorem({{123456789,p},{123456789,q}})==123456789);
for(int i=0;i<1000;i++){long long want=rng()%M;assert(chinese_remainder_theorem({{want%p,p},{want%q,q}})==want);}
for(int a=0;a<7;a++)for(int b=0;b<11;b++){long long got=chinese_remainder_theorem({{a,7},{b,11}});assert(got>=0&&got<77&&got%7==a&&got%11==b);}}
""")

    def test_primitive_root_modulo_two(self):
        code = snippet('algebra/primitive-root.md', 'int generator')
        self.cpp(code + r"""
int main(){assert(generator(2)==1);for(int p:{2,3,5,7,17,31,101,1009}){int g=generator(p),r=1;set<int>s;
for(int i=0;i<p-1;i++){s.insert(r);r=1LL*r*g%p;}assert(r==1&&(int)s.size()==p-1);}}
""")
        self.cpp(snippet('algebra/discrete-root.md', 'int generator'), [('2 1 1\n', '1\n1'), ('2 7 1\n', '1\n1')])


if __name__ == '__main__':
    unittest.main()
