#include <bits/stdc++.h>
using namespace std;

#include "strongly_connected_components.h"

int main() {
    // we only have a single test case for now
    int n = 10;
    vector<vector<int>> adj(n);
    adj[0].push_back(1);
    adj[0].push_back(7);
    adj[1].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[2].push_back(5);
    adj[3].push_back(2);
    adj[3].push_back(4);
    adj[4].push_back(9);
    adj[5].push_back(3);
    adj[5].push_back(6);
    adj[5].push_back(9);
    adj[6].push_back(2);
    adj[7].push_back(0);
    adj[7].push_back(6);
    adj[7].push_back(8);
    adj[8].push_back(6);
    adj[8].push_back(9);
    adj[9].push_back(4);

    vector<vector<int>> components, adj_scc;
    strongy_connected_components(adj, components, adj_scc);

    // sort things to make it easier to verify
    sort(components.begin(), components.end(),
         [](auto &l, auto &r) { return l[0] < r[0]; });
    for (vector<int> a : adj_scc)
        sort(a.begin(), a.end());

    assert(components.size() == 4);
    assert(components[0] == std::vector<int>({0, 7}));
    assert(components[1] == std::vector<int>({1, 2, 3, 5, 6}));
    assert(components[2] == std::vector<int>({4, 9}));
    assert(components[3] == std::vector<int>({8}));

    assert(adj_scc[0] == std::vector<int>({1, 1, 8}));
    assert(adj_scc[1] == std::vector<int>({4, 4}));
    assert(adj_scc[8] == std::vector<int>({1, 4}));

    return 0;
}
