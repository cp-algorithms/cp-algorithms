#include <cassert>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#include "spfa.h"
#include "data/sssp.h"

int main() {
    for (auto const& graph : sssp_graphs) {
        adj = graph.adj;
        vector<int> d;
        spfa(graph.s, d);
        assert(d == graph.expected_d);
    }
}
