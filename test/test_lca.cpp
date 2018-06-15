#include <cassert>
#include <vector>

using namespace std;

namespace LCA {
#include "lca.h"
}

int main() {
  vector<vector<int>> g(7);
  g[0] = {1, 2, 3};
  g[2] = {4, 5, 6};
  LCA::LCA lca(g, 0);
  assert(lca.lca(4, 6) == 2);
  assert(lca.lca(1, 6) == 0);
  assert(lca.lca(1, 6) == 0);
  assert(lca.lca(0, 3) == 0);
  assert(lca.lca(2, 2) == 2);
  return 0;
}
