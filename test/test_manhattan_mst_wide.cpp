#include <bits/stdc++.h>
using namespace std;
#include "manhattan_mst.h"

long long mst(const vector<vector<long long>>& w) {
    int n = w.size();
    vector<long long> d(n, LLONG_MAX);
    vector<bool> used(n);
    d[0] = 0;
    long long total = 0;
    for (int step = 0; step < n; ++step) {
        int v = -1;
        for (int i = 0; i < n; ++i)
            if (!used[i] && (v == -1 || d[i] < d[v])) v = i;
        assert(v != -1 && d[v] != LLONG_MAX);
        total += d[v]; used[v] = true;
        for (int i = 0; i < n; ++i) d[i] = min(d[i], w[v][i]);
    }
    return total;
}
void check(vector<point> p) {
    int n = p.size();
    vector<vector<long long>> full(n, vector<long long>(n)), candidate(n, vector<long long>(n, LLONG_MAX));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
        full[i][j] = abs(p[i].x-p[j].x) + abs(p[i].y-p[j].y);
    for (auto [w, i, j] : manhattan_mst_edges(p)) {
        assert(w == full[i][j]);
        candidate[i][j] = candidate[j][i] = min(candidate[i][j], w);
    }
    assert(mst(full) == mst(candidate));
}
int main() {
    check({{0,0},{2147483648LL,2147483648LL}});
    check({{INT_MIN,INT_MAX},{INT_MAX,INT_MIN},{0,0}});
    mt19937_64 rng(71924);
    for (int tt = 0; tt < 1000; ++tt) {
        vector<point> p(2 + rng()%24);
        long long offset = tt%2 ? 1000000000000LL : -2147483648LL;
        for (auto& a : p) {
            a.x = offset + (long long)(rng()%10000000001ULL)-5000000000LL;
            a.y = offset + (long long)(rng()%10000000001ULL)-5000000000LL;
        }
        check(p);
    }
}
