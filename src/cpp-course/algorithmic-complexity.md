---
title: Algorithmic Complexity
tags:
  - Course
---

# Algorithmic Complexity

Every competitive programming problem is a negotiation between what you want to compute and what the judge will let you compute. Complexity analysis is the tool that makes that negotiation explicit: it tells you, *before you write a single line of code*, whether your planned algorithm will fit in the time and memory limit. A contestant who can look at `n ≤ 10^5` and immediately think "\(O(n \log n)\) required, \(O(n)\) ideal, \(O(n \sqrt{n})\) borderline, \(O(n^2)\) impossible" has already solved half the problem — they know which algorithmic family to reach for. A contestant who cannot will spend thirty minutes coding an \(O(n^2)\) DP that TLEs on test 5.

This article covers the notation, the calculation rules, the STL-specific constants that Big-O hides, and — most importantly — the **practical mapping between constraints and complexities** that judges actually enforce.

## Prerequisites

- [Introduction to C++](intro-to-cpp.md) — `-O2`, the CP template.
- [I/O and Data Types](io-and-data-types.md) — `int` vs `long long`, the overflow traps.
- [Conditionals and Loops](conditionals-and-loops.md) — loop idioms, off-by-one.
- [Arrays and Vectors](arrays-and-vectors.md) — contiguous memory, cache behavior.
- [Functions and Recursion](functions-and-recursion.md) — stack frames, recursion depth.
- [STL Basics](stl-basics.md) — containers and their asymptotic costs.

## What Complexity Measures

Algorithmic complexity measures **how the resource consumption of an algorithm scales with input size \(n\)**. Two resources matter in CP:

- **Time complexity** — the number of elementary operations (roughly: CPU instructions) as a function of \(n\).
- **Space complexity** — the amount of auxiliary memory (heap, stack, arrays) as a function of \(n\), **excluding the input** in most contest conventions.

Why "scaling" and not "exact count"? Because exact counts depend on the machine, the compiler, the optimizer, and dozens of microarchitectural details. Two implementations of the same algorithm can differ by 10× in wall-clock time and still be "the same complexity". What is invariant across machines is the **growth rate**: doubling \(n\) roughly quadruples the operations of an \(O(n^2)\) algorithm, regardless of whether those operations take 1 ns or 10 ns.

The judge cares about **absolute time** (typically 1–2 seconds), but you can only reason about **relative growth**. The bridge between them is the empirical fact that on modern judges, an \(O(n)\) algorithm with a simple body does roughly \(10^8\)–\(10^9\) operations per second. This constant is stable enough across judges to be a design tool (more on this in the benchmarks section).

## Asymptotic Notation — Big-O, Big-Omega, Big-Theta

Most CP tutorials only teach Big-O. That is enough for choosing algorithms, but not for understanding why some comparisons are subtler than they look. Here is the full picture, briefly.

| Notation | Meaning | Analogy |
|---|---|---|
| \(O(f(n))\) | **Upper bound**: \(T(n) \le c \cdot f(n)\) for large \(n\) | "\(T\) grows **no faster** than \(f\)" |
| \(\Omega(f(n))\) | **Lower bound**: \(T(n) \ge c \cdot f(n)\) for large \(n\) | "\(T\) grows **at least as fast** as \(f\)" |
| \(\Theta(f(n))\) | **Tight bound**: both \(O(f)\) and \(\Omega(f)\) | "\(T\) grows **exactly like** \(f\)" |

In competitive programming, when someone says "this algorithm is \(O(n \log n)\)", they almost always mean \(\Theta(n \log n)\) — the tight bound. Big-O is used as shorthand for "the dominant term". The distinction matters in a few places:

- Saying "bubble sort is \(O(n^2)\)" is **true but uninformative** — it's also \(O(n^3)\), \(O(2^n)\), and \(O(n!)\), because Big-O is only an upper bound. The tight statement is \(\Theta(n^2)\).
- Saying "`unordered_map` lookup is \(O(1)\)" is **misleading** — the worst case is \(O(n)\) when every key collides. The honest statement is **average \(O(1)\), worst \(O(n)\)**. This matters enormously in CP (see the anti-hash section).
- Saying "`vector::push_back` is \(O(1)\)" is **imprecise** — the honest statement is **amortized \(O(1)\)**: a single `push_back` can cost \(O(n)\) when reallocation occurs, but the average over \(n\) pushes is \(O(1)\).

For design purposes, assume everyone means the tightest bound unless stated otherwise, and always ask "worst case or average?" when the answer involves hashing.

## Common Time Complexities

Listed in increasing order of growth. The rightmost columns tell you **when each is viable under a 1–2 second limit**.

| Complexity | Name | Typical \(n\) limit | Common example |
|---|---|---|---|
| \(O(1)\) | constant | any \(n\) | array index, `unordered_map` avg lookup, `bitset` count |
| \(O(\log n)\) | logarithmic | up to \(10^{18}\) (integer math) | binary search, `set::find`, bit length |
| \(O(\sqrt{n})\) | square root | \(10^{12}\)–\(10^{14}\) | trial division, sqrt decomposition, block algorithms |
| \(O(n)\) | linear | \(10^7\)–\(10^8\) | array scan, prefix sum, BFS/DFS |
| \(O(n \log n)\) | linearithmic | \(10^5\)–\(10^6\) | merge sort, `std::sort`, FFT, sieve of Eratosthenes |
| \(O(n \sqrt{n})\) | — | \(10^4\)–\(10^5\) | Mo's algorithm, sqrt-decomposition on arrays |
| \(O(n^2)\) | quadratic | \(10^3\)–\(10^4\) | double loop, Floyd–Warshall on dense, naive DP |
| \(O(n^2 \log n)\) | — | \(10^3\) | Fenwick tree 2D on medium \(n\) |
| \(O(n^3)\) | cubic | \(10^2\)–\(500\) | Floyd–Warshall, matrix multiplication (naive), triple DP |
| \(O(2^n)\) | exponential | \(n \le 20\) (subset enumeration) | brute-force subsets, naive TSP |
| \(O(n \cdot 2^n)\) | — | \(n \le 18\) | bitmask DP |
| \(O(n!)\) | factorial | \(n \le 10\)–\(12\) | brute-force permutations, naive TSP |

The \(n\) limits are approximations for **simple** operations under `-O2` in 1–2 seconds. The actual threshold depends on the operation's constant factor — see the benchmarks section below.

## Calculating Complexity

### Rule 1 — Sequential adds, nested multiplies

```cpp
for (int i = 0; i < n; ++i) { /* O(1) */ }        // O(n)
sort(v.begin(), v.end());                          // O(n log n)
// Total: O(n) + O(n log n) = O(n log n) — dominated by the larger term

for (int i = 0; i < n; ++i)                        // n iterations
    for (int j = 0; j < m; ++j) { /* O(1) */ }    // × m iterations
// Total: O(n · m)
```

The dominant term wins. `O(n^2 + n log n + n) = O(n^2)`. **Lower-order terms are always dropped.**

### Rule 2 — Loops halved or doubled → logarithmic

If the loop variable is **divided or multiplied by a constant**, the loop runs \(O(\log n)\) times:

```cpp
for (int i = n; i > 0; i /= 2) { /* O(1) */ }     // log_2(n) iterations
for (int i = 1; i < n; i *= 3) { /* O(1) */ }     // log_3(n) iterations
```

The base of the logarithm does not matter for complexity (it's a constant factor), so both are \(O(\log n)\). In practice, base 2 is what you get from binary search, and \(n = 10^{18}\) requires only **60 iterations**.

### Rule 3 — Loops with non-trivial step sizes

The outer loop runs \(O(n)\) times but the inner loop runs fewer times depending on the outer index — a harmonic series:

```cpp
for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n / i; ++j) { /* O(1) */ }
// Inner total: n/1 + n/2 + n/3 + ... + n/n = n · H(n) ≈ n · ln(n) = O(n log n)
```

This pattern appears in **sieve-like algorithms** and **divisor enumeration**. Recognizing it as \(O(n \log n)\) (not \(O(n^2)\)) is a common step in optimizing number-theoretic code.

Another common pattern — **two pointers** on a sorted array:

```cpp
int j = 0;
for (int i = 0; i < n; ++i) {
    while (j < n && a[i] + a[j] < target) ++j;
    // ...
}
// Although it looks like O(n^2) (nested loops), j only advances: total O(n)
```

The key observation: `j` never goes backwards, so the inner `while` runs at most \(n\) times in total across the entire outer loop. **Amortized analysis over both loops** gives \(O(n)\), not \(O(n^2)\).

### Rule 4 — Recursion via recurrence relations

For a recursive algorithm, write the recurrence \(T(n)\) = (work per call) + (sum of recursive call costs). Three common patterns:

**A. Halving with constant work → \(O(\log n)\)**

Binary search: \(T(n) = T(n/2) + O(1)\). Solved by unrolling: \(T(n) = O(1) \cdot \log_2(n) = O(\log n)\).

```cpp
int binary_search(int lo, int hi, int target) {
    if (lo > hi) return -1;
    int mid = (lo + hi) / 2;
    if (a[mid] == target) return mid;
    if (a[mid] < target) return binary_search(mid + 1, hi, target);
    return binary_search(lo, mid - 1, target);
}
// T(n) = T(n/2) + O(1) → O(log n)
```

**B. Two halving calls with linear work → \(O(n \log n)\)**

Merge sort: \(T(n) = 2T(n/2) + O(n)\). The Master Theorem (case 2) gives \(O(n \log n)\).

```cpp
void merge_sort(int l, int r) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    merge(l, mid, r);        // O(r - l) = O(n)
}
// T(n) = 2T(n/2) + O(n) → O(n log n)
```

**C. Two calls with overlapping subproblems → exponential**

Naive Fibonacci: \(T(n) = T(n-1) + T(n-2) + O(1)\). The recursion tree has as many leaves as Fibonacci numbers, so \(T(n) = \Theta(\phi^n)\) where \(\phi = (1 + \sqrt{5})/2 \approx 1.618\). The common upper bound \(O(2^n)\) is **not tight** — the true growth is base \(\phi\), not base 2. Both bounds are exponential, but the difference matters numerically: at \(n = 40\), \(\phi^{40} \approx 2.3 \cdot 10^8\) while \(2^{40} \approx 10^{12}\) — a factor of ~4000. The honest statement is **\(\Theta(\phi^n)\)**, and the practical implication is that naive Fibonacci is already impractical at \(n = 40\), not \(n = 60\) as \(O(2^n)\) might suggest.

```cpp
long long fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);   // T(n) = T(n-1) + T(n-2) + O(1) = Θ(φ^n)
}
```

The **Master Theorem** handles recurrences of the form \(T(n) = a T(n/b) + f(n)\):

| Case | Condition | Result |
|---|---|---|
| 1 | \(f(n) = O(n^{\log_b a - \epsilon})\) for some \(\epsilon > 0\) | \(T(n) = \Theta(n^{\log_b a})\) |
| 2 | \(f(n) = \Theta(n^{\log_b a})\) | \(T(n) = \Theta(n^{\log_b a} \log n)\) |
| 3 | \(f(n) = \Omega(n^{\log_b a + \epsilon})\) and regularity holds | \(T(n) = \Theta(f(n))\) |

For **merge sort**: \(a = 2, b = 2, f(n) = n\). \(\log_2 2 = 1\), \(f(n) = \Theta(n^1)\) — case 2, so \(T(n) = \Theta(n \log n)\).

For **binary search**: \(a = 1, b = 2, f(n) = 1\). \(\log_2 1 = 0\), \(f(n) = \Theta(n^0)\) — case 2, so \(T(n) = \Theta(\log n)\).

For **naive matrix multiplication by divide-and-conquer**: \(a = 8, b = 2, f(n) = n^2\). \(\log_2 8 = 3\), \(f(n) = O(n^{3 - \epsilon})\) — case 1, so \(T(n) = \Theta(n^3)\). (Strassen's algorithm reduces \(a\) to 7 and gets \(O(n^{\log_2 7}) \approx O(n^{2.807})\).)

Master Theorem does **not** handle all recurrences — it misses \(T(n) = 2T(n/2) + O(n \log n)\), for instance. But it covers the vast majority of divide-and-conquer algorithms you will encounter.

### Rule 5 — Memory and stack

Space complexity follows the same rules, applied to allocations and stack depth:

```cpp
// O(1) auxiliary space
long long sum(const vector<int>& v) {
    long long s = 0;
    for (int x : v) s += x;
    return s;
}

// O(n) auxiliary space — the copy is the whole point
vector<int> double_all(const vector<int>& v) {
    vector<int> out(v.size());
    for (int i = 0; i < (int)v.size(); ++i) out[i] = 2 * v[i];
    return out;
}

// O(h) stack space where h = tree depth
void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v]) dfs(v);
}
// For a balanced tree: h = O(log n). For a skewed (path) tree: h = O(n).
```

The recursion stack space is **part of the total space complexity**, and it is the source of the "recursion works fine on small trees but crashes on 10^5-node paths" pattern from the previous article. A \(10^5\)-node recursion with a ~64-byte frame uses ~6 MB of stack, already near the typical 8 MB limit.

## Amortized Analysis

Some operations are individually expensive but cheap on average across a sequence of operations. The canonical example is `vector::push_back`:

```cpp
vector<int> v;
for (int i = 0; i < n; ++i) v.push_back(i);
```

`push_back` is \(O(1)\) most of the time, but when the vector is full, it allocates a new buffer of **2× the current capacity**, copies all existing elements, and frees the old buffer — an \(O(n)\) operation at that moment. Without amortization, one might fear the total is \(O(n^2)\) for \(n\) pushes. It is not.

**The argument.** Let the capacities at each reallocation be \(1, 2, 4, 8, \dots, 2^k\) where \(2^k \le n < 2^{k+1}\). The reallocation at size \(2^i\) copies \(2^i\) elements. Total copying:

\[
\sum_{i=0}^{k} 2^i = 2^{k+1} - 1 < 2n = O(n)
\]

So the total work over \(n\) `push_back`s is \(O(n)\), giving an **amortized cost of \(O(1)\)** per operation. The geometric growth factor (2×) is what makes this work. A growth factor of 1.1× (like `std::string` in some implementations) would also give amortized \(O(1)\), but with a larger constant.

**Amortized analysis is not average-case analysis.** Average-case refers to random inputs; amortized refers to a guaranteed worst-case bound across a sequence of operations, with no randomness. `push_back` is amortized \(O(1)\) even on adversarial sequences — there is no input that makes \(n\) `push_back`s take worse than \(O(n)\) total.

**The same argument applies to:**

- `unordered_map` insertion (rehashing at 2× growth).
- `deque::push_front` and `deque::push_back`.
- `priority_queue::push` and `pop` (sift up/down).
- Union-find with path compression: \(O(\alpha(n))\) amortized per operation, where \(\alpha\) is the inverse Ackermann function, effectively constant for any \(n\) you will encounter.

**Amortization does not apply to:**

- `vector::insert` at arbitrary position — the shift is \(O(n)\) every time, no compensation.
- `multiset::erase(value)` when the value appears \(k\) times — \(O(\log n + k)\).
- `string::substr` — a fresh allocation of size \(O(\text{length})\) every call.

## Complexity of STL Operations

The containers and algorithms you use constantly have specific asymptotic costs that you must know by heart. Here is the reference table for the operations that matter:

| Operation | Complexity | Notes |
|---|---|---|
| `v[i]` access on `vector` | \(O(1)\) | two pointer dereferences |
| `v.push_back` | amortized \(O(1)\) | 2× growth |
| `v.pop_back` | \(O(1)\) | |
| `v.insert(v.begin()+k, x)` | \(O(n)\) | shifts all elements after \(k\) |
| `v.erase(v.begin()+k)` | \(O(n)\) | shifts all elements after \(k\) |
| `v.clear()` | \(O(n)\) | destroys \(n\) elements |
| `v.resize(k)` | \(O(n)\) | fills or destroys \(n\) elements |
| `sort(v.begin(), v.end())` | \(O(n \log n)\) | introsort |
| `lower_bound(v.begin(), v.end(), x)` | \(O(\log n)\) | requires random-access iterators |
| `set::find(x)` / `set::insert(x)` | \(O(\log n)\) | red-black tree |
| `set::lower_bound(x)` (member) | \(O(\log n)\) | uses tree structure |
| `std::lower_bound(s.begin(), s.end(), x)` on a `set` | **\(O(n)\)** | linear scan — the classic trap |
| `set::erase(x)` | \(O(\log n)\) | |
| `multiset::erase(x)` | \(O(\log n + k)\) where \(k\) = count | erases all copies |
| `multiset::erase(iterator)` | \(O(\log n)\) | erases one |
| `map::operator[]` | \(O(\log n)\) | **inserts if missing** |
| `map::find(x)` | \(O(\log n)\) | |
| `unordered_map::find` / `insert` | average \(O(1)\), **worst \(O(n)\)** | anti-hash vulnerability |
| `priority_queue::push` / `pop` | \(O(\log n)\) | sift-up / sift-down |
| `priority_queue::top` | \(O(1)\) | |
| `queue`/`stack` push/pop | \(O(1)\) | |
| `deque` push_front/push_back/pop | \(O(1)\) amortized | |
| `nth_element` | \(O(n)\) average | introselect |
| `partial_sort(first, mid, last)` | \(O(n \log k)\) | \(k\) = distance from first to mid |
| `binary_search(begin, end, x)` | \(O(\log n)\) | requires sorted |
| `accumulate` | \(O(n)\) | |
| `unique(begin, end)` | \(O(n)\) | only collapses consecutive duplicates |
| `next_permutation` | \(O(n)\) per call | total \(n!\) calls to enumerate all |
| `s.find(t)` on `string` | \(O(\|s\| \cdot \|t\|)\) worst | naive matching |

The two most-tested traps in this table are the **`set::lower_bound` trap** (a \(O(\log n)\) operation becomes \(O(n)\) if you call the free function) and the **`multiset::erase(value)` trap** (erases all copies, not one). Both have been the cause of TLEs and WAs on countless contest submissions.

## Mapping Constraints to Complexities

The judge's constraint on \(n\) (usually stated in the problem as \(1 \le n \le 10^5\), etc.) is the single most useful signal about the intended complexity. Reverse-engineer it:

| Constraint on \(n\) | Intended complexity | Why |
|---|---|---|
| \(n \le 10\) | \(O(n!)\), \(O(n^n)\) | \(10! = 3.6 \cdot 10^6\), brute force fits |
| \(n \le 20\) | \(O(2^n)\), \(O(n \cdot 2^n)\) | \(2^{20} \approx 10^6\), subset enumeration fits |
| \(n \le 100\) | \(O(n^3)\) | \(10^6\), Floyd–Warshall territory |
| \(n \le 500\) | \(O(n^3)\) tight, \(O(n^2 \log n)\) preferred | \(1.25 \cdot 10^8\) borderline |
| \(n \le 10^3\) | \(O(n^2)\) | \(10^6\) comfortable |
| \(n \le 10^4\) | \(O(n^2)\) tight, prefer \(O(n \log n)\) | \(10^8\) near the limit |
| \(n \le 10^5\) | \(O(n \log n)\) required | \(n^2 = 10^{10}\) impossible |
| \(n \le 10^6\) | \(O(n \log n)\) tight, prefer \(O(n)\) | need efficient I/O |
| \(n \le 10^7\) | \(O(n)\) with small constant | tight on I/O, use custom reader |
| \(n \le 10^9\) | \(O(\log n)\), \(O(\sqrt{n})\) | cannot loop over \(n\) |
| \(n \le 10^{12}\) | \(O(\sqrt{n})\) or \(O(n^{1/3})\) | number-theoretic techniques |
| \(n \le 10^{18}\) | \(O(\log n)\), \(O(\log^2 n)\) | matrix exponentiation, binary lifting |

**The reverse question** is equally useful: given a complexity and a time limit, what is the largest \(n\) you can afford? The answer depends on the constant factor, which you can approximate:

| Time budget | \(O(1)\) | \(O(\log n)\) | \(O(n)\) | \(O(n \log n)\) | \(O(n^2)\) | \(O(n^3)\) | \(O(2^n)\) |
|---|---|---|---|---|---|---|---|
| 1 s (modern) | any \(n\) | any \(n\) | \(\sim 10^8\) | \(\sim 5 \cdot 10^6\) | \(\sim 10^4\) | \(\sim 500\) | \(\sim 25\) |
| 1 s (older) | any \(n\) | any \(n\) | \(\sim 10^7\) | \(\sim 10^6\) | \(\sim 3 \cdot 10^3\) | \(\sim 200\) | \(\sim 22\) |
| 2 s (modern) | any \(n\) | any \(n\) | \(\sim 2 \cdot 10^8\) | \(\sim 10^7\) | \(\sim 1.5 \cdot 10^4\) | \(\sim 600\) | \(\sim 26\) |

The "modern" column assumes a typical 2024-era Codeforces/AtCoder machine: ~\(5 \cdot 10^8\) simple operations per second for the \(O(n)\) column, and correspondingly faster for other complexities. The "older" column is a conservative assumption for judges running on weaker hardware or with heavier per-operation overhead.

## Real-World Benchmarks

The \(10^8\) operations-per-second rule of thumb is useful but crude. Here are measured approximate throughputs on typical 2024-era judges under `-O2` with `<bits/stdc++.h>` and `sync_with_stdio(false)`:

| Operation | Approximate rate | Time for \(n = 10^6\) |
|---|---|---|
| `int` arithmetic in a tight loop | \(\sim 10^9\)/s | 1 ms |
| Array/vector access, sequential | \(\sim 5 \cdot 10^8\)/s | 2 ms |
| `vector::push_back` (with `reserve`) | \(\sim 5 \cdot 10^8\)/s | 2 ms |
| `vector::push_back` (without `reserve`) | \(\sim 10^8\)/s | 10 ms |
| `std::sort` on random `int`s | \(\sim 5 \cdot 10^7 \cdot \log_2 n\)/s | ~100 ms |
| `lower_bound` on `vector<int>` | \(\sim 2 \cdot 10^7\)/s | 50 ms |
| `set::insert` | \(\sim 3 \cdot 10^6\)/s | 330 ms |
| `unordered_map::insert` | \(\sim 10^7\)/s | 100 ms |
| `priority_queue::push` + `pop` | \(\sim 5 \cdot 10^6\)/s | 200 ms |
| `string` concatenation (single char) | \(\sim 10^7\)/s | 100 ms |
| `cout << x` (with fast I/O) | \(\sim 10^7\)/s | 100 ms |
| `cout << x` (without `sync_with_stdio(false)`) | \(\sim 10^6\)/s | 1 s |
| `cin >> x` (with fast I/O) | \(\sim 5 \cdot 10^7\)/s | 20 ms |
| `cin >> x` (without `sync_with_stdio(false)`) | \(\sim 10^6\)/s | 1 s |

The **factor of 50× between `cin` with and without fast I/O**, and the **factor of 10× between `set::insert` and `unordered_map::insert`**, are the kind of gaps that Big-O hides — both pairs have "the same" asymptotic for a single operation, but the constants differ enormously. This is why the practical rules (fast I/O, sorted `vector` over `set`, custom hash for `unordered_map`) matter as much as the asymptotic analysis itself.

## Space-Time Tradeoffs

Complexity analysis applies to memory as well as time, and in CP the two are often **exchangeable**:

**Precomputation for faster queries.** The classic example is prefix sums:

```cpp
// O(n) precompute, O(1) per query
vector<long long> pref(n + 1, 0);
for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + a[i];
long long range_sum(int l, int r) { return pref[r + 1] - pref[l]; }

// vs O(1) precompute, O(r - l) per query
long long range_sum_naive(int l, int r) {
    long long s = 0;
    for (int i = l; i <= r; ++i) s += a[i];
    return s;
}
```

If you have \(q = 10^5\) queries, the precomputed version is \(10^5 \cdot O(1) = 10^5\) operations; the naive version is \(10^5 \cdot 10^5 = 10^{10}\) — a TLE by four orders of magnitude. The price is \(O(n)\) extra memory, which is negligible.

**Memoization for overlapping subproblems.** Naive Fibonacci is \(O(\phi^n)\); memoized is \(O(n)\) time and \(O(n)\) space. The price of a hash table or array turns an exponential algorithm into a linear one — the foundational tradeoff of dynamic programming.

**Sparse tables for range queries.** For static range-min queries, a **sparse table** takes \(O(n \log n)\) precomputation and \(O(n \log n)\) memory, but answers any query in \(O(1)\). The naive approach is \(O(n)\) precomputation and \(O(r-l)\) per query. For \(10^5\) queries on \(10^5\) elements, the sparse table is 50× faster at the cost of ~5× memory.

**Hash tables for lookup.** An `unordered_map` uses roughly 2× the memory of a sorted `vector` of pairs, but gives average \(O(1)\) lookup instead of \(O(\log n)\). For \(10^7\) lookups, this is a factor of ~20 in time.

The general principle: **spend memory to save time, as long as you stay within the memory limit**. Typical CP memory limits are 256 MB or 512 MB; a \(10^6\)-element `int` array is 4 MB, and a \(10^7\)-element array is 40 MB. Both fit comfortably. A \(10^8\)-element array at 4 bytes each is 400 MB — over the limit on most judges, so \(10^8\) is usually the practical ceiling for a single array.

## Common Pitfalls

A checklist for when complexity analysis or its application goes wrong:

1. **Assuming `unordered_map` is \(O(1)\) worst case** — it is average \(O(1)\), worst \(O(n)\). Codeforces anti-hash tests exploit this; use a custom hash.
2. **Calling `std::lower_bound` on a `set`** — it is \(O(n)\), not \(O(\log n)\). Use `s.lower_bound(x)`.
3. **Forgetting `accumulate(..., 0)` accumulates in `int`** — use `0LL` for `long long` sums.
4. **Naive Fibonacci as "\(O(2^n)\)"** — it is \(\Theta(\phi^n)\); a factor of ~4000 more efficient than the bound suggests at \(n = 40\).
5. **Confusing \(10^5\) with `10^5`** — the latter is `15` in C++. Use `100'000`.
6. **Estimating time from operations without considering constants** — 10^8 `set::insert` takes 30 s, not 0.1 s, because each insert is \(O(\log n)\) with a large constant.
7. **Ignoring I/O cost** — \(10^6\) numbers read with default `cin` take 1 s on its own; always use `sync_with_stdio(false)` and `cin.tie(nullptr)`.
8. **Assuming `vector::erase` is \(O(1)\)** — it is \(O(n)\) in the middle of the vector, because subsequent elements shift.
9. **Forgetting to count the recursion stack** — a DFS on a \(10^5\)-node path uses \(O(n)\) stack, which can overflow 8 MB on some judges.
10. **Assuming \(O(n^2)\) is fine for \(n = 10^4\)** — it is \(10^8\), which is borderline on 1 s limits. Prefer \(O(n \log n)\) when possible.
11. **Underestimating \(O(n \log n)\) for \(n = 10^6\)** — \(10^6 \cdot 20 = 2 \cdot 10^7\), fine; but with a large constant (like `set`-based operations), it becomes 10 s.
12. **Confusing "amortized \(O(1)\)" with "worst-case \(O(1)\)"** — `push_back` can be \(O(n)\) for a single call; if that single call is in a hot loop with interrupts or time limits, it matters.
13. **Ignoring the constant factor for small \(n\)** — an \(O(n^2)\) algorithm with tiny constant may beat \(O(n \log n)\) with large constant for \(n \le 100\). Measure if in doubt.
14. **Assuming `sort` is \(O(n \log n)\) worst case** — `std::sort` is introsort, which is \(O(n \log n)\) worst case (heapsort fallback), unlike naive quicksort which is \(O(n^2)\) worst case.
15. **Estimating constraints from \(n\) alone** — \(n \le 10^5\) with \(m\) also up to \(10^5\) edges means the algorithm must be \(O((n + m) \log n)\) or better for graph problems, not just \(O(n \log n)\).
16. **Ignoring the total operations across multiple test cases** — \(t\) test cases each with \(n = 10^4\) requires the algorithm to be fast per test case; a \(10^4 \cdot 10^4 = 10^8\) total is fine, but \(10^4 \cdot 10^6 = 10^{10}\) is not.

## Key Takeaways

- **Asymptotic notation is about growth, not exact counts.** Big-O is an upper bound; \(\Theta\) is the tight one; \(\Omega\) is a lower bound. Use \(\Theta\) when you mean "exactly this complexity".
- **The \(n\)-limit table is the most useful tool in your kit.** \(n \le 10^5\) means \(O(n \log n)\) is required, \(O(n^2)\) is impossible. Read the constraints before choosing an algorithm.
- **Sequential adds, nested multiplies, halved/doubled loops are logarithmic.** Recursion via recurrence relations; Master Theorem for divide-and-conquer.
- **Naive Fibonacci is \(\Theta(\phi^n)\), not \(O(2^n)\).** The bound \(O(2^n)\) is correct but not tight, and the difference matters numerically.
- **Amortized \(O(1)\) is not \(O(1)\).** `push_back` can be \(O(n)\) on a single call, but averages \(O(1)\). Understand the difference.
- **`unordered_map` is average \(O(1)\), worst \(O(n)\).** Codeforces adversarial tests exploit this. Use a custom hash if you rely on hashing.
- **`set::lower_bound` is \(O(\log n)\); `std::lower_bound` on a `set` is \(O(n)\).** This is the most-tested STL complexity trap.
- **The \(10^8\) ops/s rule is a starting point, not a law.** Constants vary by 10–50× across operations. Measure, or use the benchmark table in this article.
- **Spend memory to save time, up to the memory limit.** Prefix sums, sparse tables, memoization — these are the fundamental space-time tradeoffs of CP.
- **Always count the recursion stack.** \(O(n)\) recursion depth is \(O(n)\) memory; on a 8 MB stack, that means a few \(10^5\) frames maximum.

## Practice Problems

- [CSES — Maximum Subarray Sum](https://cses.fi/problemset/task/1643) — Kadane's \(O(n)\) vs. naive \(O(n^2)\) vs. \(O(n^3)\); the problem shows why \(n \le 10^5\) rules out the slower versions.
- [CSES — Sum of Two Values](https://cses.fi/problemset/task/1640) — two-pointer \(O(n \log n)\) after sort vs. \(O(n^2)\) double loop; \(n \le 2 \cdot 10^5\) forces the sorted approach.
- [CSES — Building Teams](https://cses.fi/problemset/task/1668) — bipartite check via BFS, \(O(n + m)\); a good drill for reading the constraints as \(O((n+m) \log n)\) for the full problem.
- [Codeforces 4A — Watermelon](https://codeforces.com/problemset/problem/4/A) — trivial \(O(1)\); the point is recognizing that no complexity analysis is needed.
- [CSES — Creating Strings](https://cses.fi/problemset/task/1622) — \(n \le 8\) permits \(O(n!)\) enumeration via `next_permutation`; the constraint is the hint.
- [CSES — Subset Sums](https://cses.fi/problemset/task/1092) — a problem where \(n \le 10^5\) rules out \(O(n \cdot \text{sum})\) subset-sum DP and forces an \(O(1)\) mathematical construction; a good example of constraints reverse-engineering the intended solution.
- [Codeforces 1611E1 — Escape The Maze (easy version)](https://codeforces.com/problemset/problem/1611/E1) — BFS on a tree, \(O(n)\); contrast with the hard version, where a slower approach TLEs at the larger constraint.

## References

- [CLRS, Introduction to Algorithms, Chapter 3 (Growth of functions)](https://mitpress.mit.edu/9780262046305/introduction-to-algorithms/) — the definitive treatment of asymptotic notation.
- [cp-algorithms — Complexity of an algorithm](https://cp-algorithms.com/) — the CP-focused perspective.
- [Wikipedia — Master theorem for divide-and-conquer recurrences](https://en.wikipedia.org/wiki/Master_theorem_(analysis_of_algorithms))
- [Codeforces — On the performance of `unordered_map` (anti-hash)](https://codeforces.com/blog/entry/62393)
- [cppreference — Complexity guarantees of containers and algorithms](https://en.cppreference.com/w/cpp/container)

## Next Topic

[Practice and Problems](practice-and-problems.md)