---
title: STL Basics
tags:
  - Course
---

# STL Basics (Standard Template Library)

The Standard Template Library is the single biggest reason C++ remains dominant in competitive programming. It hands you a sorting algorithm that beats most hand-written quicksorts, a hash table, a balanced BST, a heap, and a dozen other structures — all well-tested, all with predictable asymptotics, and all in a few lines of code. Knowing *which* container to reach for, and knowing the handful of places where the STL will silently betray you, is the difference between writing $O(n \log n)$ solutions that fit in 30 lines and fighting the language for an hour.

This article is not an exhaustive STL reference. It is a **tour of the parts that matter in contests**, with emphasis on the traps that turn correct algorithms into WA or TLE.

## Prerequisites

- [Introduction to C++](intro-to-cpp.md) — `-O2`, the CP template.
- [I/O and Data Types](io-and-data-types.md) — `int` vs `long long`, `size_t`.
- [Conditionals and Loops](conditionals-and-loops.md) — loop idioms.
- [Arrays and Vectors](arrays-and-vectors.md) — `vector` in depth, iterator invalidation, `reserve`.
- [Functions and Recursion](functions-and-recursion.md) — `const&`, lambdas, global state.

## Why STL for Competitive Programming

Three concrete reasons, in order of importance:

1. **The asymptotics are right.** `std::sort` is introsort — quicksort + heapsort + insertion sort, guaranteed $O(n \log n)$ even in the worst case. `std::set` is a red-black tree — $O(\log n)$ guaranteed. A hand-rolled quicksort can degenerate to $O(n^2)$ on adversarial input; the STL cannot.
2. **The constants are small.** These implementations have been tuned by experts for decades. On $10^6$ integers, `std::sort` typically runs in ~100 ms; a naive hand-written quicksort on the same input is 2–3× slower and — more importantly — has adversarial worst cases that TLE.
3. **The code is short.** A `map`-based frequency counter is 3 lines. Hand-rolling a red-black tree is 200. In a contest, those 197 lines are 197 opportunities for bugs.

The price is that some operations have **hidden costs** you have to know about. Those are covered in the pitfall section at the end.

## The `<bits/stdc++.h>` idiom

Every modern judge's GCC ships a non-standard header that pulls in the entire standard library:

```cpp
#include <bits/stdc++.h>
using namespace std;
```

In production code this is frowned upon — it bloats compile times and pulls in things you don't need. In contests it is universal and idiomatic. The alternative — listing 15 `#include` lines at the top of every file — wastes time and invites a forgotten include.

> **Caveat.** `<bits/stdc++.h>` is a **GCC extension**. It works on Codeforces, AtCoder, CSES, and every judge that compiles with `g++`. It does **not** work on MSVC (Visual Studio) without a compatibility shim. If you develop locally on Windows, install MinGW or WSL.

For the rest of this article, all examples assume the `<bits/stdc++.h>` header and the CP template:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // ...
    return 0;
}
```

## Algorithms from `<algorithm>`

The `<algorithm>` header is where the biggest wins live. These functions operate on iterator ranges `[begin, end)` — first included, last excluded — which is the convention throughout the STL.

### Sorting — `sort`, `stable_sort`, `partial_sort`, `nth_element`

```cpp
vector<int> v = {5, 2, 9, 1, 5, 6, 3};

sort(v.begin(), v.end());                          // ascending, O(n log n)
sort(v.begin(), v.end(), greater<int>());          // descending
sort(v.begin(), v.end(), [](int a, int b) {        // custom comparator
    return (a % 10) < (b % 10);                    // sort by last digit
});
```

The comparator **must define a strict weak ordering** — that is, `cmp(a, a)` must be `false`. Writing `return a <= b;` violates this and leads to undefined behavior (usually a crash or infinite loop on inputs larger than ~20, though it can look fine on small tests). **Always use `<`, never `<=`.**

Three specialized sorts you will actually use:

```cpp
// 1. Sort only the first k elements — O(n log k), much faster than full sort
partial_sort(v.begin(), v.begin() + k, v.end());

// 2. k-th smallest element in O(n) average — for "find the median" or "k-th largest"
nth_element(v.begin(), v.begin() + k, v.end());
// now v[k] is the k-th smallest; elements before are <=, after are >=
// use nth_element when you need JUST the k-th element, not a sorted array

// 3. Stable sort — equal elements keep their relative order
//    Use when sorting structs by one field but preserving the input order on ties
stable_sort(v.begin(), v.end(), [](const Item& a, const Item& b) {
    return a.score < b.score;
});
```

> **`nth_element` is underused.** For problems like "find the median of $10^6$ values", `nth_element` runs in ~30 ms; `sort` takes ~100 ms. It is the standard tool for k-th-order statistics when you don't need the rest of the array ordered.

### Binary search — `lower_bound`, `upper_bound`, `binary_search`

These require the range to be **sorted by the same comparator**. They operate on any random-access container, but for `set` and `map` you must use the **member functions** (see the iterator section — this is a huge TLE trap).

```cpp
sort(v.begin(), v.end());

// First position where v[i] >= 5 — returns iterator
auto lo = lower_bound(v.begin(), v.end(), 5);

// First position where v[i] > 5
auto hi = upper_bound(v.begin(), v.end(), 5);

// How many 5s are in v?
int cnt = hi - lo;

// Convenience: first index, not iterator
int idx = lower_bound(v.begin(), v.end(), 5) - v.begin();

// Just existence
bool has = binary_search(v.begin(), v.end(), 5);
```

The `- v.begin()` conversion from iterator to index is the idiomatic CP form. It works because `vector` iterators are random-access (they support `-`); **it does not work for `set` or `map` iterators**, which are bidirectional. For those, use `std::distance(it, end)` — but if you find yourself needing this on a `set`, you probably wanted an `unordered_map` or a sorted `vector` in the first place.

### `unique` — the shift-and-erase idiom

`unique` **does not remove** elements. It **shifts the first of each run of consecutive equal elements to the front** and returns an iterator past the last unique element. To actually remove duplicates:

```cpp
sort(v.begin(), v.end());                         // sort first — REQUIRED
v.erase(unique(v.begin(), v.end()), v.end());     // then erase the tail
```

Without `sort`, `unique` only collapses *consecutive* duplicates. The combination `sort + unique + erase` is the canonical way to deduplicate a `vector`, and it's the first step of **coordinate compression** (see below).

### Aggregations and transformations

```cpp
#include <numeric>

// Sum — the initial value's type determines the accumulator
long long total = accumulate(v.begin(), v.end(), 0LL);   // 0LL, not 0

// Product (and other operations via the 4-argument form)
long long prod = accumulate(v.begin(), v.end(), 1LL, multiplies<long long>());

// Min and max — return ITERATORS, not values
auto it_min = min_element(v.begin(), v.end());
auto it_max = max_element(v.begin(), v.end());
int lo = *it_min, hi = *it_max;

// C++11 initializer-list form
int m = min({a, b, c, d});
int M = max({a, b, c, d});

// Transform in place — but see the pitfall below
transform(v.begin(), v.end(), v.begin(), [](int x) { return x * 2; });
```

> **`accumulate` pitfall.** The accumulator type is the type of the **third argument**, not the type of the elements. `accumulate(v.begin(), v.end(), 0)` on a `vector<long long>` **accumulates in `int`** and overflows silently at \(2^{31}-1\). Always use `0LL` when the sum can exceed \(2 \cdot 10^9\). This is a real WA pattern in problems like "sum of \(10^5\) numbers up to \(10^9\)" — the "obvious" answer of $\sim 10^{14}$ overflows in the wrong version.

### Permutations — `next_permutation`

If the problem asks for "the next lexicographic permutation" or "all permutations of size $k$":

```cpp
sort(v.begin(), v.end());       // start from the smallest permutation
do {
    // process v as a permutation
    process(v);
} while (next_permutation(v.begin(), v.end()));
```

`next_permutation` returns `false` when the input is the largest permutation (already sorted descending), which is why the loop terminates. This is the standard tool for problems with $n \le 8$ that ask about "arrangements" — often the intended solution is exactly this loop.

## Containers — the shortlist

The containers below cover 95% of competitive programming. The tables include the **complexities you'll actually hit** and the **CP-specific gotchas**.

| Container | Access | Insert | Find | Ordered? | Use in CP |
|---|---|---|---|---|---|
| `vector<T>` | $O(1)$ | amortized $O(1)$ | $O(n)$ unsorted | no | Default; everything |
| `array<T, N>` | $O(1)$ | $O(1)$ (fixed size) | $O(n)$ | no | Rarely used in CP (global C arrays preferred) |
| `deque<T>` | $O(1)$ | $O(1)$ both ends | $O(n)$ | no | 0-1 BFS, monotonic queue |
| `stack<T>` | $O(1)$ top | $O(1)$ | — | no | DFS iterative, brackets matching |
| `queue<T>` | $O(1)$ front | $O(1)$ | — | no | BFS |
| `priority_queue<T>` | $O(1)$ top | $O(\log n)$ | — | max-heap | Dijkstra, greedy |
| `set<T>` | $O(\log n)$ find | $O(\log n)$ | $O(\log n)$ | yes | Sorted unique elements |
| `multiset<T>` | $O(\log n)$ find | $O(\log n)$ | $O(\log n)$ | yes | Sorted with duplicates |
| `map<K, V>` | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | by key | Sparse array |
| `unordered_set<T>` | $O(1)$ avg, $O(n)$ worst | same | same | no | Fast lookup, no order |
| `unordered_map<K, V>` | $O(1)$ avg, $O(n)$ worst | same | same | no | Fast dict, no order |

### `vector` — already covered

See [Arrays and Vectors](arrays-and-vectors.md). Key rules repeated: `reserve` if the size is known; pass by `const&`; `push_back` may invalidate iterators.

### `stack` and `queue` — the two adaptors

```cpp
stack<int> st;
st.push(1); st.push(2);
st.top();     // 2
st.pop();     // removes 2
st.empty();

queue<int> q;
q.push(1); q.push(2);
q.front();    // 1
q.pop();      // removes 1
q.empty();
```

Neither supports iteration — that is the point. `stack` is the iterative DFS tool; `queue` is the BFS tool. Both are thin adaptors over `deque<T>` by default.

> **Pitfall.** `st.pop()` **returns `void`**, not the popped value. To use the value, call `top()` first, then `pop()`. This trips up everyone coming from Python or Java. The reason is exception safety — if the copy of the popped value throws, the stack must not be left in a modified state.

### `priority_queue` — the max-heap, and its three traps

`priority_queue<T>` is a **max-heap**: the largest element is at the top. This is the correct behavior for Dijkstra (smallest distance popped first requires a min-heap, see below), Huffman coding, and k-largest queries.

```cpp
priority_queue<int> pq;                  // max-heap
pq.push(3); pq.push(1); pq.push(4);
pq.top();                                 // 4
pq.pop();                                 // removes 4

// Min-heap — three-argument template
priority_queue<int, vector<int>, greater<int>> minpq;
minpq.push(3); minpq.push(1); minpq.push(4);
minpq.top();                              // 1
```

**Trap 1: `priority_queue` does not support `erase` or `decrease_key`.** This affects Dijkstra. The standard workaround is **lazy deletion**: push a node every time its distance improves, and check whether the popped entry is stale:

```cpp
// Dijkstra with lazy deletion
priority_queue<pair<long long, int>,
               vector<pair<long long, int>>,
               greater<pair<long long, int>>> pq;
pq.push({0, s});
vector<long long> dist(n, LLONG_MAX);
dist[s] = 0;

while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;              // stale entry — skip
    for (auto [v, w] : adj[u]) {
        if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
    }
}
```

The `if (d > dist[u]) continue;` line is essential. Without it, the heap can grow to $O(E)$ entries and the total work becomes $O(E \log E)$ instead of $O(E \log V)$. On dense graphs, this is a TLE.

**Trap 2: `priority_queue<pair<int, int>>` is a max-heap by lexicographic order.** For a min-heap on `pair<int, int>`, use `greater<pair<int, int>>` (which compares lexicographically in reverse). For a min-heap on a struct, use a custom comparator struct — **not** a lambda, because `priority_queue` requires the comparator to be a type, not a value:

```cpp
struct Node { int dist, id; };
struct Cmp {
    bool operator()(const Node& a, const Node& b) const {
        return a.dist > b.dist;   // "greater than" → min-heap
    }
};
priority_queue<Node, vector<Node>, Cmp> pq;
```

**Trap 3: `priority_queue` on a vector of `pair` with a `greater` comparator does not build a min-heap on `pair.first` alone** — it uses the full lexicographic comparison. This matters when you have duplicate first elements and the algorithm depends on tie-breaking. Usually the tie-break does not matter for correctness, but it does for performance on adversarial inputs (a well-known Dijkstra antics on Codeforces relies on it).

### `set` and `multiset` — the sorted BST

```cpp
set<int> s;
s.insert(5); s.insert(1); s.insert(3);
s.insert(1);                        // ignored — already present
s.count(1);                         // 1 (present) or 0
s.find(1);                          // iterator to 1
s.erase(1);                         // removes by value — returns number erased
s.erase(s.find(1));                 // removes by iterator
```

`set` maintains unique elements in sorted order. Iterating over a `set` visits elements in ascending order.

`multiset<int>` allows duplicates but the erase semantics are a **landmine**:

```cpp
multiset<int> ms = {1, 5, 5, 3};
ms.erase(5);                        // removes ALL 5s → {1, 3}
ms.erase(ms.find(5));               // removes ONE 5 → {1, 3, 5}
```

This is the single most common `multiset` bug. If you want to remove one copy, you must `find()` first. `erase(value)` on `multiset` is $O(\log n + k)$ where $k$ is the number of copies; `erase(iterator)` is $O(\log n)$.

**The `set::lower_bound` vs `std::lower_bound` trap.** This is critical:

```cpp
set<int> s = {1, 3, 5, 7, 9};

// WRONG — O(n)!
auto it = lower_bound(s.begin(), s.end(), 5);    // walks from begin() one by one

// CORRECT — O(log n)
auto it = s.lower_bound(5);                       // uses the tree structure
```

The global `std::lower_bound` requires **random-access iterators** to be $O(\log n)$; `set` iterators are bidirectional. Called on a `set`, `std::lower_bound` does a linear scan starting at `begin()`. On a $10^5$-element set inside a loop, this is a TLE you can stare at for an hour before noticing the wrong `lower_bound`. **For `set` and `map`, always use the member function.**

Same story for `upper_bound`: `s.upper_bound(x)`, not `upper_bound(s.begin(), s.end(), x)`.

**The `set` cannot be accessed by index.** `s[i]` does not compile. If you need random access, use a sorted `vector` and `lower_bound`. If you need fast insert/delete *and* random access, you need a Fenwick tree or a balanced BST — not `std::set`.

### `map` — the sparse array

```cpp
map<string, int> freq;
freq["apple"]++;                    // O(log n), inserts if absent
freq.find("banana");                // iterator or end()
freq.count("apple");                // 1 or 0
freq.erase("apple");
freq.size();
```

Iterating a `map` visits keys in ascending order. The element type is `pair<const K, V>` — the key is `const` and cannot be modified through the iterator.

**`operator[]` inserts.** `freq["x"]` on a missing key creates `{"x", 0}` (the default value) and returns a reference to it. This is convenient for `freq[x]++` but dangerous elsewhere:

```cpp
if (freq["apple"] == 0) { ... }   // INSERTS "apple" with value 0 as a side effect!
```

Use `find()` or `count()` for existence checks:

```cpp
if (freq.find("apple") != freq.end()) { ... }   // no insertion
if (freq.count("apple")) { ... }                 // also no insertion, but does a second lookup
```

> **Prefer `find()` over `count()` for existence.** `count()` does a full lookup and returns an `int`; `find()` returns an iterator you can use directly. In a loop with $10^5$ existence checks, `find()` saves an average of $O(\log n)$ per call — half the work.

### `unordered_map` and `unordered_set` — the hash tables

Average $O(1)$ lookup, insert, delete. No sorted order — iteration order is unspecified and can vary between runs, compilers, and even between different executions on the same machine.

```cpp
unordered_map<string, int> freq;
freq["apple"]++;                    // amortized O(1)
freq.reserve(200000);               // pre-size bucket count — avoids rehashing during inserts
freq.find("apple");
```

**The anti-hash attack — you will hit this on Codeforces.** Many judges include adversarial test cases where every key in the input hashes to the same bucket, degrading `unordered_map` from $O(1)$ to $O(n)$ per operation and from $O(n)$ to $O(n^2)$ overall. The classic example: `unordered_map<int, int>` with inputs designed so that all keys are multiples of a power of 2 that maps to the same bucket in libstdc++.

**The fix is a custom hash** that mixes the bits more thoroughly:

```cpp
struct CustomHash {
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        x += FIXED_RANDOM;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        x = x ^ (x >> 31);
        return x;
    }
};

unordered_map<long long, int, CustomHash> safe_map;
```

The `FIXED_RANDOM` seed makes the hash unpredictable at runtime, so an adversary cannot construct an input that causes collisions. For `unordered_map<string, ...>` and `unordered_map<pair<...>, ...>` you need to combine this with the standard hash — see the references.

> **When to skip `unordered_map` entirely.** For $n \le 10^5$, `std::map` is often **faster** than `unordered_map` because hash tables have high constant factors (bucket allocation, load factor management, cache misses from scattered memory). For $n = 10^6$ with adversarial risk, a sorted `vector` + `lower_bound` is safer and often competitive. Use `unordered_map` when the number of operations is large ($n > 10^6$) and the input is not adversarial, or when you've added the custom hash.

## Iterators — the glue

An iterator is an abstraction of "position in a container". Every STL algorithm works with iterators, not with container types, which is why `sort` works on a `vector`, a `deque`, and a C array — and not on a `set` (which is already sorted and has no `sort`).

```cpp
vector<int> v = {1, 2, 3, 4, 5};

v.begin(), v.end()              // forward [begin, end)
v.rbegin(), v.rend()            // reverse
v.cbegin(), v.cend()            // const — read-only

auto it = find(v.begin(), v.end(), 3);
if (it != v.end()) *it = 30;    // modify through iterator

// Insertion iterators — for algorithms that need a destination of unknown size
copy(v.begin(), v.end(), back_inserter(v2));    // v2.push_back for each element
```

The **iterator categories** matter because they determine which algorithms can run on which containers:

| Category | Operations | Containers |
|---|---|---|
| Input/Output | `++`, `*` (read once) | `istream_iterator`, `ostream_iterator` |
| Forward | Multiple passes | `unordered_set`, `unordered_map` |
| Bidirectional | `++`, `--` | `set`, `map`, `multiset`, `list` |
| Random access | `+ n`, `- n`, `<`, `- it` | `vector`, `deque`, `array`, C arrays |

**This is why the `set::lower_bound` trap exists**: `std::lower_bound` needs random-access iterators to be $O(\log n)$; on bidirectional iterators it falls back to linear scanning. The table above is the mental model behind a huge fraction of "STL is slow" complaints.

## CP idioms built from STL primitives

### Coordinate compression

Reduce a `vector<long long>` of large values to indices `0..k-1` — essential when values don't fit in an array but there are only \(10^5\) distinct ones:

```cpp
vector<long long> vals = {1e18, -5, 42, 1e18, 7};

vector<long long> sorted = vals;
sort(sorted.begin(), sorted.end());
sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

vector<int> compressed;
for (long long x : vals)
    compressed.push_back(lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin());

// compressed = {3, 0, 2, 3, 1}, sorted.size() == 4
```

### Frequency counting

```cpp
// For small value range (< 10^7) — direct-address array
vector<int> cnt(MAXV, 0);
for (int x : a) cnt[x]++;

// For large or unknown range — unordered_map with custom hash, or map for sorted output
map<int, int> freq;
for (int x : a) freq[x]++;
```

The direct-address version is 10–50× faster and should be your default when the value range fits.

### Min-heap on pairs — for Dijkstra and event processing

```cpp
priority_queue<pair<long long, int>,
               vector<pair<long long, int>>,
               greater<pair<long long, int>>> pq;
```

This is the single most-written line in competitive programming. Memorize it.

### Top-k largest with a min-heap of size k

```cpp
priority_queue<int, vector<int>, greater<int>> pq;    // min-heap
for (int x : a) {
    pq.push(x);
    if ((int)pq.size() > k) pq.pop();
}
// pq now contains the k largest elements
```

$O(n \log k)$ instead of $O(n \log n)$ — significant when $k$ is small.

### Deduplicate and count occurrences

```cpp
sort(v.begin(), v.end());
vector<pair<int, int>> counts;
for (int i = 0; i < (int)v.size(); ) {
    int j = i;
    while (j < (int)v.size() && v[j] == v[i]) ++j;
    counts.push_back({v[i], j - i});
    i = j;
}
```

### Reading structured input

```cpp
int n; cin >> n;
vector<pair<int, int>> events(n);
for (auto& [l, r] : events) cin >> l >> r;         // C++17 structured binding
sort(events.begin(), events.end());                // sorts by l, then by r
```

Pairs and tuples sort lexicographically by default — this is why they're so convenient in CP.

## Performance

Relative throughput on typical judge hardware with `-O2`:

| Operation | Approximate cost |
|---|---|
| Array / vector access | ~1 ns |
| `vector::push_back` with `reserve` | ~1 ns |
| `vector::push_back` without `reserve` (amortized) | ~2 ns |
| `sort` | \(n \log n\) comparisons, ~100 ns each |
| `lower_bound` on `vector` | ~50 ns |
| `set` / `map` operation | ~200 ns (tree walk + cache misses) |
| `unordered_map` operation | ~50 ns avg, up to ~1 µs worst case |
| `priority_queue` push/pop | ~100 ns |
| `deque` push/pop | ~5 ns |
| `stack` / `queue` push/pop | ~5 ns |

**Practical rules:**

- **Sorted vector beats `map`/`set` in the constant factor** by 5–20×. If the algorithm allows it — no interleaved insertions — build the sorted vector once and use `lower_bound`. This is why "sort offline, process queries" is such a common technique.
- **`unordered_map` is not always faster than `map`.** For $n \le 10^5$ with non-adversarial input, `map` often wins. For $n \ge 10^6$ or highly repetitive operations, `unordered_map` with a custom hash wins.
- **Arrays beat every associative container** when the keys are small integers. A `vector<int>` used as a direct-address table is 10–100× faster than `unordered_map<int, int>`.
- **Pre-`reserve` your `vector` and `unordered_map`.** For a `vector` of $10^6$, this saves ~20 reallocations. For an `unordered_map` with $10^6$ entries, this prevents ~10 rehashes.

## Common Pitfalls

A checklist to run whenever a solution involving STL containers WAs or TLEs:

1. **`accumulate(..., 0)` on `long long` values** — accumulates in `int`, overflows silently. Use `0LL`.
2. **`std::lower_bound` on a `set`/`map`** — $O(n)$ linear scan. Use `s.lower_bound(x)` ($O(\log n)$).
3. **`multiset::erase(value)`** — removes ALL copies. Use `erase(find(value))` for one.
4. **`map::operator[]`** — inserts a default entry if the key is missing. Use `find()` for existence checks.
5. **`priority_queue` has no `erase`/`decrease_key`** — use lazy deletion for Dijkstra.
6. **`st.pop()` returns `void`** — call `top()` first if you need the value.
7. **`priority_queue<pair, ..., greater<>>`** — needed for min-heap on pairs; the default is a max-heap on lexicographic order.
8. **`unordered_map` on adversarial input** — Codeforces anti-hash tests blow up `unordered_map<int,int>` from $O(n)$ to $O(n^2)$. Use the custom hash from this article.
9. **`unique` without `sort`** — only collapses consecutive duplicates.
10. **`unique` without `erase`** — does not remove elements; the container keeps `n` entries.
11. **`sort` comparator `return a <= b`** — violates strict weak ordering; UB.
12. **Iterator invalidation from `push_back`** — pointer/iterator/reference into a `vector` becomes dangling after reallocation. Use `reserve` or index-based access.
13. **Modifying a container during iteration** — `erase` invalidates iterators; collect keys first.
14. **`v.size() - 1` on an empty vector** — wraps to `SIZE_MAX`; guard with `!v.empty()`.
15. **`vector<bool>`** — bit-packed specialization; `bool&` does not compile, `&v[i]` invalid. Use `vector<char>` or `bitset`.
16. **Missing `break` in a `switch` inside a loop** — exits the `switch`, not the loop.
17. **`std::function` for a comparator** — heap allocation and indirection; use a struct with `operator()` or a plain lambda.
18. **`transform` in a hot loop** — a manual `for` loop with `-O2` is often faster because the compiler can vectorize it without the iterator overhead. Measure before "optimizing".
19. **`string::substr` in a loop** — $O(\text{length})$ copy per call; use `string_view` or index arithmetic.
20. **`multimap::count`** — $O(\log n + k)$ where $k$ is the number of matching keys; use `equal_range` if iterating anyway.

## Key Takeaways

- `<bits/stdc++.h>` is the CP header. Use it in every contest submission.
- `sort`, `lower_bound`, `unique`, `nth_element`, `next_permutation`, `accumulate` (with `0LL`!) are the workhorses. Memorize their signatures and pitfalls.
- The comparator in `sort` must be strict — `<`, not `<=`. Violating this is UB, not "just wrong".
- **For `set`/`map`, always use the member functions `lower_bound` and `upper_bound`** — the `std::` versions are linear scans on these containers.
- **`multiset::erase(value)` removes all copies**; `erase(iterator)` removes one. This is the #1 `multiset` WA.
- **`priority_queue` has no `erase` and no `decrease_key`** — use lazy deletion with an `if (d > dist[u]) continue;` guard.
- **`unordered_map`/`unordered_set` are vulnerable to anti-hash tests.** Use a custom hash for any competitive submission that relies on hashing.
- Sorted `vector` + `lower_bound` often beats `map`/`set` by 5–20× in the constant factor. Reach for it whenever the algorithm allows.
- Direct-address arrays beat every associative container when keys are small non-negative integers. Use them.
- `reserve` on `vector` and `unordered_map` is a one-line optimization with measurable impact on large inputs.

## Practice Problems

- [CSES — Restaurant Customers](https://cses.fi/problemset/task/1619) — sweep line with a sorted `vector` of events; exercise in `vector<pair>` and `sort`.
- [CSES — Concert Tickets](https://cses.fi/problemset/task/1754) — `multiset` with `upper_bound` and `erase(iterator)`; the canonical drill for the multiset pitfall.
- [CSES — Traffic Lights](https://cses.fi/problemset/task/1163) — `set` for maintaining positions + a `multiset` or priority-queue trick for maximum gaps.
- [CSES — Josephus Problem II](https://cses.fi/problemset/task/1732) — needs order statistics on a dynamic set; try `set` first, observe TLE, then move to a Fenwick tree.
- [CSES — Distinct Numbers](https://cses.fi/problemset/task/1621) — the canonical `sort + unique + erase` deduplication.
- [Codeforces 4C — Registration System](https://codeforces.com/problemset/problem/4/C) — `map<string, int>` frequency counting; introduces the `operator[]` insert-on-read semantics.
- [CSES — Sum of Two Values](https://cses.fi/problemset/task/1640) — `unordered_map` lookup; the problem where the anti-hash issue first shows up on Codeforces-style judges.

## References

- [cppreference — `<algorithm>`](https://en.cppreference.com/w/cpp/algorithm)
- [cppreference — Containers library](https://en.cppreference.com/w/cpp/container)
- [cppreference — `<numeric>` (`accumulate`, `iota`)](https://en.cppreference.com/w/cpp/numeric)
- [Codeforces — On the performance of `unordered_map`](https://codeforces.com/blog/entry/62393) — the canonical anti-hash discussion
- [GCC libstdc++ — Implementation of `std::unordered_map`](https://gcc.gnu.org/onlinedocs/libstdc++/manual/unordered_associative.html)

## Next Topic

[Algorithmic Complexity](algorithmic-complexity.md)