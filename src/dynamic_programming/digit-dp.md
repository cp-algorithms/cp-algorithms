---
tags:
  - Original
---

# Digit Dynamic Programming

## Introduction

Digit dynamic programming (commonly abbreviated *digit DP*) is a technique for counting the integers in a range $[L, R]$ that satisfy some property of their decimal representation, without iterating over the range itself.

Consider a typical question: *how many integers between $1$ and $10^{18}$ contain no two consecutive equal digits?* The range is far too large to enumerate, but the number of **distinct states** the digits can be in is tiny. Digit DP exploits this by building numbers one digit at a time, from the most significant to the least, and grouping together all prefixes that behave identically from that point on.

The standard reduction is to define

$$f(X) = (\text{count of valid integers in } [0, X])$$

and answer the original query as $f(R) - f(L-1)$. This lets us solve a single prefix-counting problem rather than a two-sided one.

The central difficulty is that we may not build an arbitrary sequence of digits the result must not exceed $X$. This is handled by carrying a boolean flag, usually called *tight*, which records whether the prefix built so far is exactly equal to the corresponding prefix of $X$. While tight, the next digit is capped by the matching digit of $X$; once we place anything smaller, every remaining position is free and the flag stays off for the rest of the construction.

A digit DP state therefore consists of the current position, the *tight* flag, and whatever additional information the property being counted requires the previous digit, a running digit sum, a remainder modulo $m$, or a bitmask of digits already used. Since the position ranges over the $O(\log X)$ digits of $X$ and the remaining components are typically small, the resulting state space is exponentially smaller than the range being counted.

## Practice Problems


- [Leetcode: Count of Integers](https://leetcode.com/problems/count-of-integers/)
- [Leetcode: Total waviness](https://leetcode.com/problems/total-waviness-of-numbers-in-range-ii/)
- [Leetcode: Number of Digit One](https://leetcode.com/problems/number-of-digit-one/)
- [Leetcode: Good Integers](https://leetcode.com/problems/count-good-integers-in-a-range/)
- [Leetcode: Distinct Integers](https://leetcode.com/problems/count-distinct-integers-after-removing-zeros/submissions/1831471022/)
- [CodeForces: Magic Numbers](https://codeforces.com/contest/628/problem/D)
- [CodeForces: Interesting Function](https://codeforces.com/problemset/problem/1538/f)
- [CodeForces: Living Sequence](https://codeforces.com/problemset/problem/1811/E)
- [CSES: Counting Numbers](https://cses.fi/problemset/task/2220)
