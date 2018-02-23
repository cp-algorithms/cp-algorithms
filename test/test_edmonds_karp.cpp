#include <cassert>
#include <queue>
#include "data/flow_networks.h"

const int INF = 1e9;
#include "edmondskarp.h"

int main() {
    for (auto fn : flow_networks) {
        capacity = fn.capacity;
        n = capacity.size();
        adj = fn.get_adj();

        assert(maxflow(fn.source, fn.sink) == fn.maxflow);
    }
}
