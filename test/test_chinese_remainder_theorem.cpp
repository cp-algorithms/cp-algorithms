#include <cassert>
#include <vector>
using namespace std;

int extended_euclidean(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int x1, y1;
  int d = extended_euclidean(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}

long long mod_inv(long long a, long long m) {
  int x, y;
  int g = extended_euclidean(a, m, x, y);
  assert(g == 1);
  return (x % m + m) % m;
}

#include "chinese_remainder_theorem.h"

int main() {
  // Sunzi Suanjing problem
  vector<Congruence> C1{
      {2, 3},
      {3, 5},
      {2, 7},
  };
  assert(chinese_remainder_theorem(C1) == 23);

  // example 5 from
  // https://www.math.cmu.edu/~mradclif/teaching/127S19/Notes/ChineseRemainderTheorem.pdf
  vector<Congruence> C2{
      {2, 5},
      {3, 7},
      {10, 11},
  };

  // example 6 from same PDF
  vector<Congruence> C3{
      {3, 7},
      {3, 5},
      {4, 12},
  };
  assert(chinese_remainder_theorem(C3) == 388);
}
