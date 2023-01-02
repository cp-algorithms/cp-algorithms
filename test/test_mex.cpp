#include <cassert>
#include <map>
#include <set>
#include <vector>
using namespace std;

namespace MexSimple {
#include "mex_simple.h"
}

namespace MexLinear {
constexpr int MAX_N = 100;
#include "mex_linear.h"
} // namespace MexLinear

namespace MexUpdate {
#include "mex_updates.h"
}

struct Example {
  vector<int> array;
  int mex;
};

int main() {
  vector<Example> examples = {
      {{0, 1, 2}, 3},
      {{0, 1, 3}, 2},
      {{0, 2, 3}, 1},
      {{1, 2, 3}, 0},
  };

  for (auto example : examples) {
    assert(MexSimple::mex(example.array) == example.mex);
    assert(MexLinear::mex(example.array) == example.mex);
  }

  vector<int> A = {1, 2, 4, 1, 4};
  auto mex = MexUpdate::Mex(A);
  assert(mex.mex() == 0); // array = {1, 2, 4, 1, 4}
  mex.update(3, 0);
  assert(mex.mex() == 3); // array = {1, 2, 4, 0, 4}
  mex.update(2, 0);
  assert(mex.mex() == 3); // array = {1, 2, 0, 0, 4}
  mex.update(3, 3);
  assert(mex.mex() == 5); // array = {1, 2, 0, 3, 4}
  mex.update(4, 3);
  assert(mex.mex() == 4); // array = {1, 2, 0, 3, 3}
  mex.update(4, 9);
  assert(mex.mex() == 4); // array = {1, 2, 0, 9, 9}
  mex.update(3, 9);
  assert(mex.mex() == 3); // array = {1, 2, 0, 9, 9}
}
