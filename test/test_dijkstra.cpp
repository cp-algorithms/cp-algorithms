#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

#include "dijkstra_dense.h"
#include "dijkstra_restore_path.h"
#include "data/sssp.h"

int main() {
    for (auto const& graph : sssp_graphs) {
        adj = graph.adj;
        vector<int> d, p;
        dijkstra(graph.s, d, p);
        assert(d == graph.expected_d);
        assert(p == graph.expected_p);
    }
}
