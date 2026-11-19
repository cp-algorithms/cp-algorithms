#include <bits/stdc++.h>
using namespace std;
#include "convex_hull_trick_point.h"
#include "convex_hull_trick_add.h"
#include "convex_hull_trick_get.h"
#undef x
#undef y

int main() {
    mt19937 rng(918273);
    for (int tt = 0; tt < 400; ++tt) {
        hull.clear(); vecs.clear();
        vector<pair<int,int>> lines;
        int slope = -60;
        for (int step = 0; step < 35; ++step) {
            slope += 1+rng()%3;
            int intercept = int(rng()%201)-100;
            add_line(slope,intercept); lines.push_back({slope,intercept});
            for (int x=-30;x<=30;++x) {
                int expected = INT_MAX;
                for (auto [k,b] : lines) expected = min(expected,k*x+b);
                assert(get(x)==expected);
            }
        }
    }
}
