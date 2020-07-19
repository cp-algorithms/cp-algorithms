#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

#include "min_cost_flow_successive_shortest_path.h"

int main() {
    // example from topcoder
    vector<Edge> edges = {
        {1, 2, 3, 1},
        {1, 3, 3, 4},
        {2, 3, 7, 2},
        {3, 6, 1, 8},
        {3, 5, 6, 5},
        {3, 4, 5, 2},
        {4, 5, 3, 1},
        {0, 1, 5, 0},
        {0, 2, 2, 0},
        {4, 7, 2, 0},
        {5, 7, 4, 0},
        {6, 7, 1, 0},
    };
    
    vector<int> expected = {0, 4, 8, 14, 20, 26, 35, 47, -1};
    for (int K = 0; K <= 8; K++) {
        assert(expected[K] == min_cost_flow(8, edges, K, 0, 7));
    }

    // another example
    edges = {
        {0, 1, 3, 2}, 
        {0, 2, 4, 6},
        {1, 2, 3, 1},
        {1, 3, 5, 6},
        {2, 3, 2, 2}
    };

    expected = {0, 5, 10, 18, 29, 40, -1};
    for (int K = 0; K <= 6; K++) {
        assert(expected[K] == min_cost_flow(4, edges, K, 0, 3));
    }
}
