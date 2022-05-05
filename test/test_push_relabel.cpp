#include <cassert>
#include "data/flow_networks.h"
#include <queue>

#include "push_relabel.h"

int main() {
    for (auto fn : flow_networks) {
       capacity = fn.capacity;
       n = capacity.size();

       assert(max_flow(fn.source, fn.sink) == fn.maxflow);
    }
}
