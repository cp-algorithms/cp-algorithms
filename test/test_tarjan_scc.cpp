#include <bits/stdc++.h>
using namespace std;

#include "tarjan_scc.h"

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
    strongly_connected_components(adj, components, adj_scc);

    auto sorted_components = components;
    for (vector<int> &a : sorted_components)
        sort(a.begin(), a.end());
    sort(sorted_components.begin(), sorted_components.end(),
         [](auto &l, auto &r) { return l[0] < r[0]; });

    vector<int> root(n);
    for (auto &comp : components) {
        for (auto v : comp) {
            root[v] = *comp.begin();
        }
    }

    vector<int> minimal_element(n);
    for (auto &comp : components) {
        minimal_element[*comp.begin()] = *min_element(comp.begin(), comp.end());
    }

    for (vector<int> &a : adj_scc)
        sort(a.begin(), a.end(), [minimal_element](auto &l, auto &r) { return minimal_element[l] < minimal_element[r]; });

    assert(sorted_components.size() == 4);
    assert(sorted_components[0] == std::vector<int>({0, 7}));
    assert(sorted_components[1] == std::vector<int>({1, 2, 3, 5, 6}));
    assert(sorted_components[2] == std::vector<int>({4, 9}));
    assert(sorted_components[3] == std::vector<int>({8}));

    assert(adj_scc[root[0]] == std::vector<int>({root[1], root[1], root[8]}));
    assert(adj_scc[root[1]] == std::vector<int>({root[4], root[4]}));
    assert(adj_scc[root[8]] == std::vector<int>({root[1], root[4]}));

    return 0;
}

