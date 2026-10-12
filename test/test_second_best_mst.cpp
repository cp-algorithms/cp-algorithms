#include <bits/stdc++.h>
using namespace std;
namespace Implementation {
int find_set(int);
bool unite_set(int, int);
#define main article_main
#include "second_best_mst.h"
#undef main
int find_set(int x) { return parent[x] == x ? x : parent[x] = find_set(parent[x]); }
bool unite_set(int x, int y) {
    x = find_set(x); y = find_set(y);
    if (x == y) return false;
    parent[x] = y;
    return true;
}
}

void check(int n, vector<array<int, 3>> edges) {
    set<long long> totals;
    int m = edges.size();
    for (int mask = 0; mask < (1 << m); ++mask) {
        if (__builtin_popcount((unsigned)mask) != n - 1) continue;
        vector<int> component(n);
        iota(component.begin(), component.end(), 0);
        long long total = 0;
        bool tree = true;
        for (int i = 0; i < m; ++i) if (mask >> i & 1) {
            auto [a, b, w] = edges[i];
            int x = component[a], y = component[b];
            if (x == y) { tree = false; break; }
            for (int& c : component) if (c == x) c = y;
            total += w;
        }
        if (tree) totals.insert(total);
    }
    assert(!totals.empty());
    long long expected = totals.size() < 2 ? (long long)1e18 : *next(totals.begin());
    Implementation::res = 0; Implementation::ans = 1e18;
    Implementation::edges.clear();
    for (int i = 0; i <= n; ++i) {
        Implementation::h[i] = 0;
        Implementation::adj[i].clear();
        fill(Implementation::up[i].begin(), Implementation::up[i].end(), -1);
        fill(Implementation::dp[i].begin(), Implementation::dp[i].end(),
             make_pair(Implementation::no_edge, Implementation::no_edge));
    }
    fill(Implementation::present.begin(), Implementation::present.begin() + m, 0);
    stringstream input, output;
    input << n << ' ' << m << '\n';
    for (auto [a, b, w] : edges) input << a + 1 << ' ' << b + 1 << ' ' << w << '\n';
    auto cin_buffer = cin.rdbuf(input.rdbuf()), cout_buffer = cout.rdbuf(output.rdbuf());
    Implementation::article_main();
    cin.rdbuf(cin_buffer); cout.rdbuf(cout_buffer);
    long long actual; output >> actual;
    assert(actual == expected);
}

int main() {
    check(3, {{0,1,-5},{1,2,-4},{0,2,-3}});
    check(3, {{0,1,INT_MIN},{1,2,INT_MIN + 1},{0,2,INT_MAX}});
    check(3, {{0,1,-1},{1,2,-1},{0,2,0}});
    mt19937 rng(76543);
    for (int tt = 0; tt < 1200; ++tt) {
        int n = 3 + rng() % 4;
        vector<array<int,3>> edges;
        for (int i = 1; i < n; ++i) edges.push_back({i-1, i, int(rng()%15)-7});
        for (int i = 0; i < n && edges.size() < 10; ++i)
            for (int j = i+2; j < n && edges.size() < 10; ++j)
                if (rng()%2) edges.push_back({i,j,int(rng()%15)-7});
        check(n, edges);
    }
}
