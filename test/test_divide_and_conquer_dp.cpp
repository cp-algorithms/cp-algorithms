// https://codeforces.com/contest/1527/problem/E

#include <bits/stdc++.h>

using namespace std;

#include "divide_and_conquer_dp.h"

vector<int> ar;

int solve(int k)
{
    n = ar.size();
    dp_before.resize(n, 0), dp_cur.resize(n, 0);

    for (int i = 0; i < n; i++)
        dp_before[i] = C(0, i);

    for (int i = 1; i < k; i++) {
        compute(0, n - 1, 0, n - 1);
        dp_before = dp_cur;
    }

    return dp_before[n - 1];
}

/// O(n^2 * k) DP
int brute_force(int k)
{
    const int INF = 1 << 25;

    n = ar.size();
    vector<long long> dp[2];

    dp[0].resize(n + 1), dp[1].resize(n + 1);
    for (int i = 0; i < n; i++)
        dp[0][i] = dp[1][i] = INF;

    for (int j = 1; j <= k; j++) {
        int cur = j & 1;
        int prev = cur ^ 1;

        for (int i = 0; i < n; i++) {
            dp[cur][i] = INF;
            for (int l = i; l < n; l++) {
                dp[cur][i] = min(dp[cur][i], dp[prev][l + 1] + C(i, l));
            }
        }
    }

    return dp[k & 1][0];
}

// sum of last occurrence of x - first occurence of x for all unique x in the range
long long C(int i, int j)
{
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

int main()
{
    ar = vector<int>({ 32, 8, 32, 32, 32, 34, 38, 38, 39, 32, 22, 29, 39,
        5, 5, 32, 5, 32, 32, 22, 10, 22, 8, 35, 38, 23,
        29, 9, 8, 29, 34, 32, 11, 29, 22, 32, 38, 38, 32 });

    assert(solve(3) == 30);

    mt19937 rng(0);
    for (int i = 0; i < 1000; i++) {
        int n = rng() % 10 + 1;
        ar.clear();
        for (int i = 0; i < n; i++)
            ar.push_back(rng() % 10 + 1);

        for (int k = 1; k <= n; k++) {
            assert(solve(k) == brute_force(k));
        }
    }
}
