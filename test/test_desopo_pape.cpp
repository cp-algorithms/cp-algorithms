#include <cassert>
#include <vector>
#include <deque>
using namespace std;

#include "desopo_pape.h"

int main() {
    n = 5;
    adj.resize(n);
    adj[0].push_back({1, -1});
    adj[0].push_back({2, 4});
    adj[1].push_back({2, 3});
    adj[1].push_back({3, 2});
    adj[1].push_back({4, 2});
    adj[3].push_back({2, 5});
    adj[3].push_back({1, 1});
    adj[4].push_back({3, -3});

    vector<int> d, p;
    shortest_paths(0, d, p);
    vector<int> d_ideal{0, -1, 2, -2, 1};
    vector<int> p_ideal{-1, 0, 1, 4, 1};
    assert(d == d_ideal);
    assert(p == p_ideal);
}
