"""Executable regressions for article snippets: python3 test_dp_strings_numerics_regressions.py."""
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



class DpStringsNumericsRegressions(unittest.TestCase):
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

    def test_catalan_products(self):
        code = snippet('combinatorics/catalan-numbers.md', 'void init')
        code = code.replace('const int MOD = ....', 'const int MOD = 1000000007;')
        code = code.replace('const int MAX = ....', 'const int MAX = 101;')
        self.cpp(code + r"""
long long power(long long a,int n){long long r=1;for(;n;n>>=1,a=a*a%MOD)if(n&1)r=r*a%MOD;return r;}
int main(){init(100);long long expected=1;assert(catalan[22]==482563003);
for(int n=1;n<=100;n++){expected=expected*(4*n-2)%MOD*power(n+1,MOD-2)%MOD;assert(catalan[n]==expected);}}
""")

    def test_zero_bishops(self):
        path = 'combinatorics/bishops-on-chessboard.md'
        code = snippet(path, 'int squares') + snippet(path, 'int bishop_placements')
        self.cpp(code + r"""
int main(){for(int n=1;n<=4;n++){vector<int> counts(2*n+1);
for(int mask=0;mask<(1<<(n*n));mask++){bool ok=true;int k=__builtin_popcount((unsigned)mask);
for(int a=0;a<n*n;a++)if(mask>>a&1)for(int b=a+1;b<n*n;b++)if(mask>>b&1)
if(abs(a/n-b/n)==abs(a%n-b%n))ok=false;
if(ok)counts[k]++;}
for(int k=0;k<=2*n;k++)assert(bishop_placements(n,k)==counts[k]);}}
""")

    def test_repeated_suffix_automaton_builds(self):
        path = 'string/suffix-automaton.md'
        code = ''.join(snippet(path, token) for token in ['struct state', 'state st[', 'void sa_init', 'void sa_extend', 'string lcs'])
        self.cpp(code + r"""
int main(){assert(lcs("a","a")=="a");assert(lcs("b","a")=="");mt19937 rng(13);
for(int z=0;z<3000;z++){string a(1+rng()%30,'a'),b(1+rng()%30,'a');for(char&c:a)c+=rng()%3;for(char&c:b)c+=rng()%3;
auto got=lcs(a,b);int best=0;for(int i=0;i<(int)a.size();i++)for(int j=i;j<(int)a.size();j++)if(b.find(a.substr(i,j-i+1))!=string::npos)best=max(best,j-i+1);
assert((int)got.size()==best);assert(a.find(got)!=string::npos&&b.find(got)!=string::npos);}}
""")

    def test_ternary_search_progress(self):
        code = 'double peak; int calls; double f(double x){assert(++calls<10000);return -(x-peak)*(x-peak);}'
        code += snippet('num_methods/ternary_search.md', 'double ternary_search')
        self.cpp(code + r"""
int main(){for(double offset:{-1e9,0.,1e9})for(double width:{1.,10.,1000.})for(double fraction:{0.,.25,.75,1.}){
peak=offset+width*fraction;calls=0;double got=ternary_search(offset,offset+width);assert(isfinite(got));assert(got>-1e-10);}}
""")

    def test_kraut_negative_rows(self):
        code = snippet('linear_algebra/determinant-kraut.md', 'static BigInteger det', 'java')
        main = r"""
static long exact(int[][] a,int row,boolean[] used){if(row==a.length)return 1;long ans=0;int pos=0;for(int j=0;j<a.length;j++)if(!used[j]){used[j]=true;ans+=(pos%2==0?1:-1)*a[row][j]*exact(a,row+1,used);used[j]=false;pos++;}return ans;}
static void check(int[][] a){int n=a.length;BigDecimal[][] b=new BigDecimal[n][n];for(int i=0;i<n;i++)for(int j=0;j<n;j++)b[i][j]=BigDecimal.valueOf(a[i][j]);
BigInteger want=BigInteger.valueOf(exact(a,0,new boolean[n]));if(!det(b,n).equals(want))throw new AssertionError(want);}
public static void main(String[] args){check(new int[][]{{-1}});java.util.Random r=new java.util.Random(18);for(int z=0;z<2000;z++){int n=1+r.nextInt(4);int[][] a=new int[n][n];for(int i=0;i<n;i++)for(int j=0;j<n;j++)a[i][j]=r.nextInt(7)-3;check(a);}}
"""
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / 'KrautRegression.java'
            source.write_text('import java.math.*; public class KrautRegression {\n' + code + main + '}')
            subprocess.run([os.environ.get('JAVAC', 'javac'), str(source)], check=True, capture_output=True, text=True)
            subprocess.run([os.environ.get('JAVA', 'java'), '-cp', directory, 'KrautRegression'], check=True, capture_output=True, text=True, timeout=30)


if __name__ == '__main__':
    unittest.main()
