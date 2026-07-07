#include <algorithm>
#include <cassert>
#include <climits>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;
using ll = long long;

struct Dinic {
    struct Edge {
        int to, rev;
        ll c, f;

        ll flow() const {
            return f;
        }
    };

    int n;
    vector<vector<Edge>> adj;
    vector<int> level, ptr;

    Dinic() : n(0) {}

    Dinic(int n) : n(n), adj(n), level(n), ptr(n) {}

    void add_directed(int v, int u, ll cap) {
        Edge a{u, (int)adj[u].size(), cap, 0};
        Edge b{v, (int)adj[v].size(), 0, 0};
        adj[v].push_back(a);
        adj[u].push_back(b);
    }

    void addEdge(int v, int u, ll cap) {
        add_directed(v, u, cap);
        add_directed(u, v, cap);
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto &e : adj[v]) {
                if (level[e.to] == -1 && e.c - e.f > 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }

        return level[t] != -1;
    }

    ll dfs(int v, int t, ll pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;

        for (int &cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            Edge &e = adj[v][cid];
            if (level[e.to] != level[v] + 1 || e.c - e.f <= 0)
                continue;

            ll tr = dfs(e.to, t, min(pushed, e.c - e.f));
            if (tr == 0)
                continue;

            e.f += tr;
            adj[e.to][e.rev].f -= tr;
            return tr;
        }

        return 0;
    }

    ll calc(int s, int t) {
        ll result = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(s, t, LLONG_MAX))
                result += pushed;
        }
        return result;
    }
};

#include "gomoryhu.h"

ll brute_force_mincut(int n, const vector<tuple<int, int, int>> &edges, int s, int t) {
    ll best = LLONG_MAX;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (((mask >> s) & 1) == ((mask >> t) & 1))
            continue;

        ll cut = 0;
        for (auto [u, v, cap] : edges) {
            if (((mask >> u) & 1) != ((mask >> v) & 1))
                cut += cap;
        }
        best = min(best, cut);
    }
    return best;
}

ll tree_mincut(const vector<pair<ll, int>> &tree, int s, int t) {
    int n = tree.size();
    vector<vector<pair<int, ll>>> adj(n);
    for (int v = 1; v < n; v++) {
        int parent = tree[v].second;
        ll cap = tree[v].first;
        adj[v].push_back({parent, cap});
        adj[parent].push_back({v, cap});
    }

    vector<int> seen(n, 0);
    vector<ll> best(n, LLONG_MAX);
    queue<int> q;
    seen[s] = 1;
    q.push(s);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (v == t)
            return best[v];

        for (auto [to, cap] : adj[v]) {
            if (!seen[to]) {
                seen[to] = 1;
                best[to] = min(best[v], cap);
                q.push(to);
            }
        }
    }

    assert(false);
    return -1;
}

void check_graph(int n, const vector<tuple<int, int, int>> &edges) {
    gomory_hu solver;
    for (auto [u, v, cap] : edges)
        solver.add_edge(u, v, cap);

    auto tree = solver.solve(n);

    for (int s = 0; s < n; s++)
        for (int t = s + 1; t < n; t++)
            assert(tree_mincut(tree, s, t) == brute_force_mincut(n, edges, s, t));
}

int main() {
    check_graph(2, {
        {0, 1, 5},
    });

    check_graph(4, {
        {0, 1, 5},
        {1, 2, 3},
        {2, 3, 4},
    });

    check_graph(4, {
        {0, 1, 3},
        {0, 2, 5},
        {1, 2, 4},
        {0, 3, 6},
        {1, 3, 2},
        {2, 3, 7},
    });

    check_graph(6, {
        {0, 1, 8},
        {1, 2, 6},
        {3, 4, 7},
        {4, 5, 9},
    });

    return 0;
}
