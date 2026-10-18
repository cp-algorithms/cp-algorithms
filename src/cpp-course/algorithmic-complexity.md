---
title: Algorithmic Complexity
tags:
  - Course
---

# Algorithmic Complexity

Understanding algorithmic complexity is fundamental to competitive programming and efficient software design. It allows you to predict how your algorithm will scale with input size and determine whether a solution will pass time and memory limits.

## What is Algorithmic Complexity?

Algorithmic complexity measures the resources (time and memory) an algorithm consumes as a function of input size $n$. We focus primarily on:

- **Time complexity**: Number of elementary operations performed relative to input size.
- **Space complexity**: Amount of memory used relative to input size (excluding input storage in some conventions).

Since exact operation counts vary by machine and implementation, we use **asymptotic notation** (Big-O, Big-Theta, Big-Omega) to describe growth rates.

## Big-O Notation

Big-O notation describes the upper bound on growth: $O(f(n))$ means an algorithm runs at most $c \cdot f(n)$ operations for large $n$ and some constant $c > 0$.

We care about behavior as $n \to \infty$ (asymptotic behavior) and ignore constant factors and lower-order terms. For example, $O(2n^2 + 3n + 5) = O(n^2)$.

## Common Time Complexities (In Increasing Order)

| Complexity | Name | Growth | Example | Typical $n$ Limits (CP) |
|---|---|---|---|---|
| $O(1)$ | Constant | No growth | Array access, hash table lookup | Any $n$ |
| $O(\log n)$ | Logarithmic | Slow growth | Binary search, tree height | Very large ($10^{18}$ with tricks) |
| $O(n)$ | Linear | Proportional | Array traversal, max element | $10^8$ borderline, $10^7$ safe in practice |
| $O(n \log n)$ | Linearithmic | $n$ times log | Merge sort, `std::sort`, FFT | $10^5 - 10^6$ common |
| $O(n^2)$ | Quadratic | Polynomial | Double loops, naive DP (some cases) | Up to ~$10^3 - 10^4$ |
| $O(n^3)$ | Cubic | Polynomial | Floyd–Warshall (dense), triple loops | Up to ~$10^2 - 500$ |
| $O(2^n)$ | Exponential | Very fast | Subset enumeration, naive TSP | $n \le 20$ (max ~1M subsets) |
| $O(n!)$ | Factorial | Extremely fast | Permutations (brute force TSP) | $n \le 10-12$ |

## Visual Intuition

For large $n$, exponential/factorial grow far faster than polynomials. In practice:

- $O(\log n) < O(\sqrt{n}) < O(n) < O(n\log n) < O(n^2) < O(n^k) < O(2^n) < O(n!)$

## Calculating Time Complexity

### Rule 1: Loops

A single loop from 1 to $n$ is $O(n)$. Nested loops multiply.

```cpp
for (int i = 0; i < n; ++i) { /* O(1) */ }        // O(n)
for (int i = 0; i < n; ++i) {
  for (int j = 0; j < m; ++j) {}                 // O(n*m)
}
for (int i = 0; i < n; ++i) {
  for (int j = 0; j < n; ++j) {}                 // O(n^2)
}
```

### Rule 2: Logarithmic Loops

If the loop variable is divided/multiplied by a constant (usually 2), it's logarithmic.

```cpp
int x = n;
while (x > 0) {
  x /= 2;  // O(log n)
}
```

Binary search: $O(\log n)$. Each step halves the search space.

### Rule 3: Sequential vs Nested

Sequential statements add; nested multiply.

```cpp
// Sequential
for (i in 0..n) {}  // O(n)
sort(arr, n);       // O(n log n)
total = O(n + n log n) = O(n log n)

// Nested
for (i in 0..n) {
  for (j in 0..n) {}  // O(n^2)
}
```

### Rule 4: Recursion

For recursion, complexity is often (number of recursive calls) × (work per call). Use recurrence relations (Master Theorem helps for divide-and-conquer).

```cpp
// Binary search recursion: T(n)=T(n/2)+O(1) -> O(log n)
int bs(int l, int r) {
  if (l>=r) return l;
  int mid = (l+r)/2;
  return bs(l, mid); // or right half
}

// Merge sort: T(n)=2T(n/2)+O(n) -> O(n log n)
void merge_sort(int l, int r) {
  if (l>=r) return;
  int mid=(l+r)/2;
  merge_sort(l,mid);
  merge_sort(mid+1,r);
  merge(l,mid,r); // O(n)
}

// Naive Fibonacci: T(n)=T(n-1)+T(n-2)+O(1) -> O(2^n) (exponential)
long long fib(int n) {
  if (n<=1) return n;
  return fib(n-1)+fib(n-2);
}
```

## Space Complexity

Space complexity measures extra memory used (excluding input). We count auxiliary space + recursion stack.

```cpp
// O(1) extra space
int sum(const vector<int> &v) {
  int s=0;
  for(int x:v) s+=x;
  return s;
}

// O(n) extra space (creates copy)
vector<int> copy_vec(const vector<int> &v) {
  vector<int> c = v; // O(n)
  return c;
}

// O(n) recursion stack space
void dfs(int node) {
  visited[node]=true;
  for(auto nxt: adj[node]) if(!visited[nxt]) dfs(nxt);
}
// Tree depth up to n (skewed) -> O(n) stack
```

## Amortized Analysis

Some operations appear costly but average cheap over many calls. Classic example: `vector::push_back()`.

```cpp
vector<int> v;
for(int i=0;i<n;++i) v.push_back(i); // Total O(n), not O(n^2)
```

When vector grows, it reallocates (copies old elements) at powers of 2. Total copies: $\sum_{k} 2^k \approx 2n = O(n)$. So amortized $O(1)$ per push_back.

## Time Limits in Competitive Programming

Understanding typical judge limits helps you choose the right complexity:

| $n$ Range | Max Acceptable | Notes |
|---|---|---|
| $n \le 10^2$ | $O(n^3)$ | $10^6$ ops borderline but sometimes OK with fast judges |
| $n \le 10^3$ | $O(n^2)$ | $10^6$ simple ops acceptable (1 second ~10^9 simple, but with I/O/overhead ~10^8) |
| $n \le 10^4$ | $O(n^2)$ tight, prefer $O(n\log n)$ | $10^8$ simple operations roughly 1s in practice |
| $n \le 10^5$ | $O(n\log n)$ required | $O(n^2)$ is $10^{10}$—impossible |
| $n \le 10^6$ | $O(n)$ or $O(n\log n)$ efficient | Need efficient I/O + simple loops |
| $n \le 10^9$ | $O(\log n)$, $O(1)$, or $O(\sqrt{n})$ | Cannot loop over n directly |

**Rule of thumb (pragmatic):** In 1 second, GNU++ judges can roughly do $10^8$ simple operations. With heavy function calls, I/O, or complex objects, aim for $10^7$–$10^8$ safe upper bound.

## Common Complexity Pitfalls

1. **Nested loops with large n**: $O(n^2)$ for $n=10^5$ is disastrous.
2. **Hidden loops**: `std::set::find` is $O(\log n)$ (not O(1)), `vector::erase` in middle is $O(n)$.
3. **Recursion depth**: Deep recursion gives $O(n)$ stack space; can overflow for skewed trees ($n=10^5$).
4. **Unnecessary recomputations**: Naive DP without memoization (overlapping subproblems) explodes.
5. **Copying containers**: Passing vectors by value instead of `const &` adds hidden $O(n)$ per call.

## Estimating Before Coding

Before implementing, do a quick complexity check:

1. **Input size**: Look at problem constraints ($n, m \le ?$)
2. **Operations**: Estimate max operations = time limit × (10^8 ops/sec) roughly
3. **Match**: Choose algorithm whose complexity fits

Example: $n,m \le 10^3$ → up to $O(nm)=O(10^6)$ fine, $O(n^2 m)$ bad. $n\le10^5$ → need $O(n\log n)$.

## Big-O vs Real Performance

Big-O ignores constants. Sometimes $O(n^2)$ with tiny constant beats $O(n\log n)$ with large constant for small $n$. Also cache locality, branch prediction, and implementation details matter. But for contest/CP constraints, asymptotic complexity is the primary filter.

## Space-Time Tradeoffs

Often you can trade memory for time (caching/memoization, precomputation) or time for memory. For example:

- **Memoization (DP)**: Uses $O(n)$ memory to avoid recomputations, turns exponential → polynomial.
- **Prefix sums**: $O(n)$ precomputation, $O(1)$ range queries vs $O(r-l)$ naive.
- **Hash tables**: Extra memory for $O(1)$ average lookup.

## Key Takeaways

- Complexity is about growth, not exact counts. Ignore constants and lower-order terms.
- $O(n\log n)$ is efficient enough for $n\approx10^5$; $O(n^2)$ only up to $\sim10^4$.
- Nested loops multiply, sequential add. Logarithmic when dividing by constant.
- Space complexity includes recursion stack—watch for deep recursion.
- Always check problem constraints first to guide algorithm choice.
- Amortized analysis explains why `vector::push_back()` is $O(1)$.
- Prefer efficient data structures (STL) and pass by const reference.

## Next Topic

[Practice and Problems](practice-and-problems.md)
