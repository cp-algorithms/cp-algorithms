# Knuth's optimization

Knuth's optimization is a special case range DP, that can optimize the time complexity of solutions by a linear factor.

### Preconditions

This DP Speedup is applied for dp transitions of the form - $dp(i, j) =
\min_{i \leq k < j} [ dp(i, k) + dp(k+1, j) + C(i, j) ]$. Further, 
the cost function $C$ must satisfy the following conditions (for $a \leq b \leq c \leq d$) - 
1. $C(b, c) \leq C(a, d)$
2. $C(a, c) + C(b, d) \leq C(a, d) + C(b, c)$

Now, just as in <a href="https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html">divide and conquer DP</a>, let $opt(i, j)$ be the value of $k$ that minimizes the above expression in the dp transition. Then, we can show the following monotonicity condition - $opt[i][j-1] \leq opt[i][j] \leq opt[i+1][j]$. The proof for this is linked in the resources for this article, which contains a sample problem and itss editorial as well. 

This simplifies the problem a lot. If we process the dp states in such a way that we calculate $dp(i, j-1)$ and $dp(i+1, j)$ before $dp(i, j)$, and in doing so calculate $opt(i, j-1)$ and $opt(i+1, j)$, then when we process $dp(i, j)$, instead of testing values of $k$ from $i$ to $j-1$, we only need to loop from $opt(i, j-1)$ to $opt(i+1, j)$. 

## Generic implementation

Even though implementation varies based on problem, here's a fairly generic
template. Notice that the structure of the code is almost identical to that of Range DP. 
It can be shown (link in resources) that the 2 inner loops combined take $\mathcal{O}(n)$ time to run. Thus, the overall time complexity of the algorithm is $\mathcal{O}(n^2)$.

```{.cpp file=knuth_optimization}
int M, N;
int dp[N][N];

// Implement cost function C.
int C(int i, int j); 

int solve() {

    for (int i = 0; i < N; i++) {
        opt[i][i] = i;
        // Initialize dp[i][i] according to the problem
    }

    for (int i = N-2; i >= 0; i--) {
        for (int j = i+1; j < N; j++) {
            int mn = INT_MAX;
            int cost = C(i, j);
            for (int k = opt[i][j-1]; k <= min(j-1, opt[i+1][j]); k++) {
                if (mn >= dp[i][k] + dp[k+1][j] + cost) {
                    opt[i][j] = k; 
                    mn = dp[i][k] + dp[k+1][j] + cost; 
                }
            }
            dp[i][j] = mn; 
        }
    }

    cout << dp[0][N-1] << endl;
}
```

### Things to look out for

The most common application of Knuth's optimization is in Range DP, with the given transition. The only difficulty is in proving that the cost function satisfies the given conditions. The simplest case is when the cost function C(i, j) is simply the sum of the elements of the subarray S[i, i+1, ... j] for some array (depending on the question). However, they can be more complicated at times. 

Further, note that more than the conditions on the dp transition and the cost function, the key to this optimization is the inequality on the optimum splitting point. In some problems (found very rarely), such as the optimal binary search tree problem (which is, incidentally, the original problem for which this optimization was developed), the transitions and cost functions will be less obvious, however, one can still prove that $opt[i][j-1] \leq opt[i][j] \leq opt[i+1][j]$, and thus, use this optimization.

## Practice Problems
- [UVA - Cutting Sticks](https://onlinejudge.org/external/100/10003.pdf)
- [UVA - Prefix Codes](https://onlinejudge.org/external/120/12057.pdf)
- [SPOJ - Breaking String](https://www.spoj.com/problems/BRKSTRNG/)
- [UVA - Optimal Binary Search Tree](https://onlinejudge.org/external/103/10304.pdf)


## References
- [Geeksforgeeks Article (with proof of the optimization)](https://www.geeksforgeeks.org/knuths-optimization-in-dynamic-programming/)
- [Tutorial on USACO.guide]()
- [Doc on DP Speedups](https://home.cse.ust.hk/~golin/COMP572/Notes/DP_speedup.pdf)
