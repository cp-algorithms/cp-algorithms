#include <cassert>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
using namespace std;

namespace Set{
#include "dijkstra_sparse_set.h"
}

namespace PriorityQueue {
#include "dijkstra_sparse_pq.h"
}

#include "data/sssp.h"

int main() {
    {
        using namespace Set;
        for (auto const& graph : sssp_graphs) {
            adj = graph.adj;
            vector<int> d, p;
            dijkstra(graph.s, d, p);
            assert(d == graph.expected_d);
            assert(p == graph.expected_p);
        }
    }
    {
        using namespace PriorityQueue;
        for (auto const& graph : sssp_graphs) {
            adj = graph.adj;
            vector<int> d, p;
            dijkstra(graph.s, d, p);
            assert(d == graph.expected_d);
            assert(p == graph.expected_p);
        }
    }
}
