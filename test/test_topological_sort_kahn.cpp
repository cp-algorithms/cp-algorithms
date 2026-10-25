#include <cassert>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#include "topological_sort_kahn.h"

bool is_valid_topological_order(int n, const vector<vector<int>>& adj, const vector<int>& order) {
    if ((int)order.size() != n) return false;
    vector<int> pos(n, -1);
    for (int i = 0; i < n; ++i) {
        if (order[i] < 0 || order[i] >= n || pos[order[i]] != -1) return false;
        pos[order[i]] = i;
    }
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            if (pos[u] >= pos[v]) return false;
        }
    }
    return true;
}

void test_dag_cases() {
    // 1. Example from article: 0->1, 0->2, 1->3, 2->3
    {
        int n = 4;
        vector<vector<int>> adj(n);
        adj[0] = {1, 2};
        adj[1] = {3};
        adj[2] = {3};
        vector<int> order = topological_sort(n, adj);
        assert(is_valid_topological_order(n, adj, order));
    }

    // 2. Linear chain: 0->1->2->3->4
    {
        int n = 5;
        vector<vector<int>> adj(n);
        for (int i = 0; i < n - 1; ++i) {
            adj[i].push_back(i + 1);
        }
        vector<int> order = topological_sort(n, adj);
        assert(is_valid_topological_order(n, adj, order));
        vector<int> expected = {0, 1, 2, 3, 4};
        assert(order == expected);
    }

    // 3. Disconnected DAG with isolated vertices and multiple components
    {
        int n = 6;
        vector<vector<int>> adj(n);
        adj[0] = {2};
        adj[1] = {3};
        // 4 and 5 are isolated
        vector<int> order = topological_sort(n, adj);
        assert(is_valid_topological_order(n, adj, order));
    }

    // 4. Single vertex with no edges
    {
        int n = 1;
        vector<vector<int>> adj(n);
        vector<int> order = topological_sort(n, adj);
        assert(is_valid_topological_order(n, adj, order));
        assert(order == vector<int>({0}));
    }

    // 5. Empty graph
    {
        int n = 0;
        vector<vector<int>> adj(0);
        vector<int> order = topological_sort(n, adj);
        assert(order.empty());
    }
}

void test_cycle_cases() {
    // 1. Simple 2-cycle: 0->1, 1->0
    {
        int n = 2;
        vector<vector<int>> adj(n);
        adj[0] = {1};
        adj[1] = {0};
        vector<int> order = topological_sort(n, adj);
        assert(order.empty());
    }

    // 2. 3-cycle: 0->1, 1->2, 2->0
    {
        int n = 3;
        vector<vector<int>> adj(n);
        adj[0] = {1};
        adj[1] = {2};
        adj[2] = {0};
        vector<int> order = topological_sort(n, adj);
        assert(order.empty());
    }

    // 3. Self-loop: 0->0
    {
        int n = 1;
        vector<vector<int>> adj(n);
        adj[0] = {0};
        vector<int> order = topological_sort(n, adj);
        assert(order.empty());
    }

    // 4. Cycle embedded within an otherwise acyclic structure: 0->1, 1->2, 2->1, 2->3
    {
        int n = 4;
        vector<vector<int>> adj(n);
        adj[0] = {1};
        adj[1] = {2};
        adj[2] = {1, 3};
        vector<int> order = topological_sort(n, adj);
        assert(order.empty());
    }
}

int main() {
    test_dag_cases();
    test_cycle_cases();
    return 0;
}
