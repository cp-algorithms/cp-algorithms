#include <bits/stdc++.h>
using namespace std;
namespace QueueVersion {
#include "push_relabel.h"
}
namespace HeightVersion {
#include "push_relabel_faster.h"
}

void check(const vector<vector<int>>& c) {
    int n = c.size();
    long long expected = LLONG_MAX;
    for (int mask = 1; mask < (1 << n); mask += 2) {
        if (mask >> (n - 1) & 1) continue;
        long long cut = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if ((mask >> i & 1) && !(mask >> j & 1)) cut += c[i][j];
        expected = min(expected, cut);
    }
    QueueVersion::capacity = HeightVersion::capacity = c;
    QueueVersion::n = HeightVersion::n = n;
    assert(QueueVersion::max_flow(0, n - 1) == expected);
    assert(HeightVersion::max_flow(0, n - 1) == expected);
}

int main() {
    vector<vector<int>> c(4, vector<int>(4));
    c[0][1] = c[0][2] = 600000000; c[0][3] = 1;
    check(c);
    c.assign(6, vector<int>(6));
    for (int i = 1; i <= 3; ++i) c[0][i] = c[i][4] = 1000000000;
    c[4][5] = 1;
    check(c);
    mt19937 rng(271828);
    for (int tt = 0; tt < 1000; ++tt) {
        int n = 2 + rng() % 6;
        c.assign(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (i != j) c[i][j] = rng() % 31;
        check(c);
    }
}
