#include <cassert>
#include <vector>
using namespace std;

namespace FibLinear {
#include "fibonacci_linear.h"
}

namespace FibMatrix {
#include "fibonacci_matrix.h"
}

namespace FibDoubling {
#include "fibonacci_doubling.h"
}

int main() {
  vector<int> expected = {
    0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987,
   1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 
   121393, 196418, 317811, 514229, 832040, 1346269, 
   2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 
   39088169, 63245986, 102334155
  };

  for (int i = 0; i < expected.size(); i++) {
    assert(FibLinear::fib(i) == expected[i]);
  }

  for (int i = 0; i < expected.size(); i++) {
    assert(FibMatrix::fib(i) == expected[i]);
  }

  for (int i = 0; i < expected.size(); i++) {
    assert(FibDoubling::fib(i).first == expected[i]);
  }
}

