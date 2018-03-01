#include <cassert>
#include "data/flow_networks.h"

#include "push_relabel_faster.h"

int main() {
    for (auto fn : flow_networks) {
       capacity = fn.capacity;
       n = capacity.size();

       assert(max_flow(fn.source, fn.sink) == fn.maxflow);
    }
}
