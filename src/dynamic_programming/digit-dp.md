---
tags:
  - Original
---

# Digit Dynamic Programming

## Introduction

Digit dynamic programming (commonly abbreviated *digit DP*) is a technique for counting the integers in a range $[L, R]$ that satisfy some property of their decimal representation, without iterating over the range itself.

Consider a typical question: *how many integers between $1$ and $10^{18}$ contain no two consecutive equal digits?* The range is far too large to enumerate, but the number of **distinct states** the digits can be in is tiny. Digit DP exploits this by building numbers digit by digit, from the most significant to the least (a common approach), and grouping together all prefixes that behave identically from that point on.

The standard reduction is to define $f(X)$ as the count of valid integers from $0$ to $X$ (inclusive), then answer the original query as $f(R) - f(L-1)$. This lets us solve a single prefix-counting problem rather than a two-sided one.

A key constraint in digit DP is the **tight flag**. When counting numbers up to $X$, we can't build arbitrary digit sequences. We must stay at or below $X$. We track this with a boolean flag, usually called *tight*, which records whether the prefix built so far is exactly equal to the corresponding prefix of $X$. 

- **While tight=true**: the prefix matches $X$'s prefix exactly, so the next digit is capped by $X$'s digit at that position.
- **Once tight=false**: we've placed a digit smaller than $X$'s, so all remaining positions are unconstrained.

A digit DP state consists of the current position, the *tight* flag, and whatever additional information the specific problem requires: the previous digit, a running digit sum, a remainder modulo $m$, or a bitmask of digits already used. Since position ranges over $O(\log X)$ digits and the extra components are typically small, the resulting state space is exponentially smaller than the original range.

## Example: counting numbers with close adjacent digits

> Given $l$, $r$ and $k$, count the integers in $[l, r]$ such that every pair of adjacent digits differs by at most $k$, with $10 \le l \le r \le 10^{15}$ and $0 \le k \le 9$.

For instance with $k = 1$, the number $2321$ is good, because $|2-3| = 1$, $|3-2| = 1$ and $|2-1| = 1$. The number $2521$ is not, because $|2-5| = 3$.

Following the reduction from the introduction, we write the answer as $f(r) - f(l-1)$, where $f(x)$ counts the valid integers from $0$ to $x$ (inclusive). It remains to compute $f$.

For this problem, to decide whether the next digit is allowed, we only need to know the **previous digit**. So our DP state consists of the position, the tight flag, and the previous digit. Here's the full state:

- `pos`: the index of the digit we are about to place, counting from the most significant;
- `last`: the digit placed at `pos - 1`;
- `tight`: whether the prefix so far matches that of $x$.

There is one more detail. A number such as $7$ is written as $0\ldots07$ when padded to the length of $x$, and those padding zeros are not really adjacent digits. If we treated them as such, the leading zeros would be tested against the first significant digit and we would reject valid numbers. We therefore carry a fourth component, `started`, which tells us whether a significant digit has been placed yet. While it is false we are still inside the padding, no adjacency check applies, and the number being built is really a shorter one.

### Implementation

=== "Recursive"

    The recursive formulation follows the state description directly. At each position we try every digit that is permitted, capped by the current digit of $x$ whenever we are tight:

    ```{.cpp file=digit_dp_recursive}
    vector<int> digits;
    int limit;
    long long memo[16][11][2];
    bool seen[16][11][2];

    long long go(int pos, int last, bool started, bool tight) {
        if (pos == (int)digits.size())
            return started ? 1 : 0;

        // Skip leading zeros: they don't count as real digits.
        if (!tight && seen[pos][last + 1][started])
            return memo[pos][last + 1][started];

        int hi = tight ? digits[pos] : 9;
        long long res = 0;

        for (int d = 0; d <= hi; d++) {
            if (!started && d == 0) {
                // Still a leading zero, keep going.
                res += go(pos + 1, -1, false, tight && d == hi);
                continue;
            }
            if (started && abs(d - last) > limit)
                continue;
            // Update tight: stays true only if we matched the bound.
            res += go(pos + 1, d, true, tight && d == hi);
        }

        if (!tight) {
            // Cache the result (tight states are not reusable).
            seen[pos][last + 1][started] = true;
            memo[pos][last + 1][started] = res;
        }
        return res;
    }

    long long count_upto(long long n) {
        if (n < 0)
            return 0;

        digits.clear();
        if (n == 0) {
            digits.push_back(0);
        } else {
            while (n > 0) {
                digits.push_back(n % 10);
                n /= 10;
            }
            reverse(digits.begin(), digits.end());
        }

        memset(seen, 0, sizeof seen);
        return go(0, -1, false, true);
    }

    long long good_integers(long long l, long long r, int k) {
        limit = k;
        return count_upto(r) - count_upto(l - 1);
    }
    ```

    The base case returns $1$ only when `started` is true. A build that never places a significant digit represents the number $0$, which we do not want to count.

=== "Iterative"

    The same recurrence can be filled bottom-up, processing digits from the least significant end. Here `dp[i][j][0]` is the number of ways to build a free (non-tight) suffix of length $i+1$ starting with digit $j$, and `dp[i][j][1]` is the corresponding count for a prefix still tight against $x$:

    ```{.cpp file=digit_dp_iterative}
    long long dp[16][10][2];

    long long count_upto(long long n, int k) {
        if (n <= 0)
            return 0;

        memset(dp, 0, sizeof dp);

        vector<int> digits;
        while (n > 0) {
            digits.push_back(n % 10);
            n /= 10;
        }
        int len = digits.size();

        for (int j = 0; j <= 9; j++)
            dp[0][j][0] = 1;
        for (int j = 0; j <= digits[0]; j++)
            dp[0][j][1] = 1;

        for (int i = 1; i < len; i++) {
            // Free state: can use any digit 0-9 (no constraint).
            for (int j = 0; j <= 9; j++)
                for (int p = 0; p <= 9; p++)
                    if (abs(j - p) <= k)
                        dp[i][j][0] += dp[i - 1][p][0];

            // Tight to free: place digit < bound, then remaining digits are unconstrained.
            for (int j = 0; j < digits[i]; j++)
                for (int p = 0; p <= 9; p++)
                    if (abs(j - p) <= k)
                        dp[i][j][1] += dp[i - 1][p][0];

            // Tight to tight: place exactly the bound digit, stay tight.
            for (int p = 0; p <= 9; p++)
                if (abs(digits[i] - p) <= k)
                    dp[i][digits[i]][1] += dp[i - 1][p][1];
        }

        long long ans = 0;
        // Count numbers with all digits (full length).
        for (int j = 1; j <= 9; j++)
            ans += dp[len - 1][j][1];

        // Count numbers with fewer digits (no leading zero, no bound constraint).
        for (int i = 0; i < len - 1; i++)
            for (int j = 1; j <= 9; j++)
                ans += dp[i][j][0];

        return ans;
    }
    ```

    The three inner blocks are exactly the three transitions of the tight flag. A free suffix may be extended by any digit; a tight prefix becomes free as soon as we place a digit strictly below the bound; and it stays tight only by placing the bound digit itself.

    Leading zeros are handled differently here. Instead of a `started` flag, both final loops start at $j = 1$, so the leading digit is never zero: the first sums over numbers of full length, and the second adds the numbers with fewer digits, which are unconstrained by the bound.

### Complexity

A number below $10^{15}$ has at most $16$ digits. For each digit position we store one state per previous digit, and each state tries $10$ new digits.

That is $16 \cdot 10 \cdot 10$ operations, a few thousand instead of the $10^{15}$ of a naive loop.

## Practice Problems


- [Leetcode: Count of Integers](https://leetcode.com/problems/count-of-integers/)
- [Leetcode: Total waviness](https://leetcode.com/problems/total-waviness-of-numbers-in-range-ii/)
- [Leetcode: Number of Digit One](https://leetcode.com/problems/number-of-digit-one/)
- [Leetcode: Good Integers](https://leetcode.com/problems/count-good-integers-in-a-range/)
- [Leetcode: Distinct Integers](https://leetcode.com/problems/count-distinct-integers-after-removing-zeros/)
- [CodeForces: Magic Numbers](https://codeforces.com/contest/628/problem/D)
- [CodeForces: Interesting Function](https://codeforces.com/problemset/problem/1538/f)
- [CodeForces: Living Sequence](https://codeforces.com/problemset/problem/1811/E)
- [CSES: Counting Numbers](https://cses.fi/problemset/task/2220)
