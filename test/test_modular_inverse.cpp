#include <cassert>
#include <initializer_list>
#include <vector>
using namespace std;

namespace EuclideanDivision {
int m;
#include "modular_inverse_euclidean_division.h"
} // namespace EuclideanDivision

int main() {
  for (int m : {307, 1'000'000'007}) {
    for (int x : {1, 5, 100, 152, 299}) {
      EuclideanDivision::m = m;
      int x_inv = EuclideanDivision::inv(x);
      assert((long long)x * x_inv % m == 1);
    }
  }

  for (int m : {307, 12347}) {
    vector<int> inv(m);
#include "modular_inverse_euclidean_division_all.h"

    for (int x = 1; x < m; x++) {
      assert((long long)x * inv[x] % m == 1);
    }
  }
}
