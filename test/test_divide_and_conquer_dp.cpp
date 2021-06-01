// https://codeforces.com/contest/1527/problem/E

#include <bits/stdc++.h>

using namespace std;

#include "divide_and_conquer_dp.h"

vector<int> ar;

/// O(m * n^2) DP, ignoring complexity of C(i, j)
int brute_force() {
    for (int j = 0; j < n; j++)
        dp_before[j] = C(0, j);

    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            dp_cur[j] = INT_MAX;
            for (int k = 0; k <= j; k++) {
                dp_cur[j] = min(dp_cur[j], (k ? dp_before[k - 1] : 0) + C(k, j));
            }
        }
        dp_before = dp_cur;
    }

    return dp_before[n - 1];
}

// sum of last occurrence of x - first occurence of x for all unique x in the range
long long C(int i, int j) {
    map<int, int> last;

    int cost = 0;
    for (int l = i; l <= j; l++) {
        int x = ar[l];
        if (last.count(x))
            cost += (l - last[x]);
        last[x] = l;
    }

    return cost;
}

void test_handcrafted_case() {
    ar = vector<int>({
      32, 8, 32, 32, 32, 34, 38, 38, 39, 32, 22, 29, 39,
      5, 5, 32, 5, 32, 32, 22, 10, 22, 8, 35, 38, 23, 29,
      9, 8, 29, 34, 32, 11, 29, 22, 32, 38, 38, 32,
    });

    m = 3;
    n = ar.size();
    dp_before.resize(n, 0), dp_cur.resize(n, 0);

    assert(solve() == 30);
}

void test_random_cases(int t, int maxn, int maxv) {
    mt19937 rng(0);
    for (int i = 0; i < t; i++) {
        n = rng() % maxn + 1;
        dp_before.resize(n, 0), dp_cur.resize(n, 0);

        ar.clear();
        for (int i = 0; i < n; i++)
            ar.push_back(rng() % maxv + 1);

        for (m = 1; m <= n; m++) {
            assert(solve() == brute_force());
        }
    }
}

int main() {
    test_handcrafted_case();
    test_random_cases(100, 10, 5);
    return 0;
}
