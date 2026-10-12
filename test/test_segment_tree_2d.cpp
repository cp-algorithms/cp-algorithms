#include <bits/stdc++.h>
using namespace std;
int n, m, a[8][8], t[32][32];
#include "segment_tree_2d_build.h"
#include "segment_tree_2d_sum.h"
#include "segment_tree_2d_update.h"

void check() {
    for (int lx = 0; lx < n; ++lx) for (int rx = lx+1; rx <= n; ++rx)
        for (int ly = 0; ly < m; ++ly) for (int ry = ly+1; ry <= m; ++ry) {
            int expected = 0;
            for (int x = lx; x < rx; ++x) for (int y = ly; y < ry; ++y) expected += a[x][y];
            assert(sum_x(1,0,n,lx,rx,ly,ry) == expected);
        }
}
int main() {
    mt19937 rng(198347);
    for (n = 1; n <= 7; ++n) for (m = 1; m <= 7; ++m) {
        for (int x = 0; x < n; ++x) for (int y = 0; y < m; ++y) a[x][y] = x*m+y+1;
        build_x(1,0,n); check();
        for (int step = 0; step < n*m+30; ++step) {
            int x = step < n*m ? step/m : rng()%n, y = step < n*m ? step%m : rng()%m;
            int value = int(rng()%101)-50;
            update_x(1,0,n,x,y,value); a[x][y] = value; check();
        }
    }
}
