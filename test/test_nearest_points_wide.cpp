#include <bits/stdc++.h>
using namespace std;
#include "nearest_pair_def.h"
#include "nearest_pair_update.h"
#include "nearest_pair_rec.h"

void check(vector<pt> points) {
    n = points.size();
    for (int i = 0; i < n; ++i) points[i].id = i;
    long double expected = numeric_limits<long double>::infinity();
    for (int i = 0; i < n; ++i) for (int j = 0; j < i; ++j)
        expected = min(expected, hypot((long double)points[i].x-points[j].x,
                                       (long double)points[i].y-points[j].y));
    a = points;
    #include "nearest_pair_main.h"
    assert(isfinite(mindist));
    assert(abs(mindist-expected) <= 1e-12L*max(1.0L, expected));
    int i = best_pair.first, j = best_pair.second;
    assert(i >= 0 && i < n && j >= 0 && j < n && i != j);
    long double actual = hypot((long double)points[i].x-points[j].x,
                               (long double)points[i].y-points[j].y);
    assert(abs(actual-expected) <= 1e-12L*max(1.0L, expected));
}
int main() {
    check({{0,0,0},{50000,0,1}});
    check({{INT_MIN,0,0},{INT_MAX,0,1},{0,INT_MIN,2},{0,INT_MAX,3}});
    check({{0,0,0},{0,0,1},{50000,50000,2},{-50000,-50000,3}});
    mt19937 rng(712983);
    for (int tt = 0; tt < 1200; ++tt) {
        vector<pt> points(2+rng()%40);
        for (auto& p : points) p = {int(rng()), int(rng()), 0};
        check(points);
    }
}
