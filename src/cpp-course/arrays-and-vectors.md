---
title: Arrays and Vectors
tags:
  - Course
---

# Arrays and Vectors

An array is a **contiguous block of memory holding elements of the same type**. That one sentence is the reason arrays dominate competitive programming: contiguous memory means the CPU can prefetch, vectorize, and cache efficiently, and index arithmetic compiles to a single `mov` instruction. Almost every efficient data structure you will meet — segment trees, Fenwick trees, sparse tables, DP tables, adjacency lists, union-find — is built on top of an array. If you understand how arrays and `vector`s work at the memory level, every algorithm downstream becomes easier to reason about; if you treat them as opaque boxes, subtle bugs (overflow, invalidation, shallow copies) will follow you through the entire course.

This article covers both `std::array`-style static arrays and `std::vector`, with a focus on the parts that matter in contests: **initialization guarantees, stack vs heap, capacity growth, iterator invalidation, and cache behavior**. Those are the areas where nearly every WA/TLE comes from.

## Prerequisites

- [Introduction to C++](intro-to-cpp.md) — compilation, `-O2`, the CP template.
- [I/O and Data Types](io-and-data-types.md) — `int` vs `long long`, `size_t`, signed/unsigned traps.
- [Conditionals and Loops](conditionals-and-loops.md) — loop idioms, off-by-one hazards.

Throughout we assume the CP template:

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

## Arrays as Contiguous Memory

Before writing any code, internalize this mental model:

```
int a[5] = {10, 20, 30, 40, 50};

Address:   0x1000  0x1004  0x1008  0x100c  0x1010
Value:       10      20      30      40      50
Index:        0       1       2       3       4
```

The address of `a[i]` is `a + i * sizeof(int)`. Two consequences follow:

1. **Indexing is \(O(1)\)** — a single multiply-add, then a memory load.
2. **Accesses to nearby indices hit the same cache line** (typically 64 bytes = 16 `int`s). Iterating left to right is much faster than iterating in a scattered order, and vastly faster than traversing a linked structure.

These two facts are why the array is the workhorse of competitive programming. A `std::map` has the same \(O(\log n)\) asymptotic as binary search on a sorted array, but the array's constant factor is typically **10–50× smaller** because it never leaves a cache line.

## Static Arrays

A static array's size is known at compile time. In CP, "static" usually means two things: **declared at global scope** (fast zero-initialization, plentiful memory) or **declared locally with a compile-time constant size**.

### Declaration and initialization

```cpp
int arr[5];                 // Uninitialized (if local) — contains garbage
int fixed[5] = {1, 2, 3, 4, 5};
int partial[5] = {1, 2};    // {1, 2, 0, 0, 0} — the rest are zero
int zeros[5] = {};          // {0, 0, 0, 0, 0} — the canonical way
```

The pitfall hiding in the first line is **initialization guarantees differ by storage duration**:

- **Global or `static` arrays** are zero-initialized by the OS. `int cnt[100];` at file scope starts as all zeros.
- **Local arrays** are **not** initialized. `int cnt[100];` inside `main` contains whatever was on the stack — often zeros in practice, but **undefined behavior** to read. Under `-O2`, the compiler may assume uninitialized values are *never read*, and eliminate code that would have "read" them.

This is why competitive programming templates almost universally use **global arrays** for large state: they are guaranteed zero-initialized, allocated in the static data segment (not the 8 MB stack), and accessible from any function without passing pointers.

```cpp
constexpr int MAXN = 200'005;
int parent[MAXN];     // global — zero-initialized, 200005 * 4 bytes = ~800 KB, no stack cost
long long dp[MAXN];   // global — fits the entire DP without heap allocations
```

### `std::array` — the modern C++ alternative

Since C++11, `std::array<T, N>` is the standard-library type for fixed-size arrays. It is stack-allocated, size is part of the type, and it supports `.size()`, iterators, and STL algorithms:

```cpp
array<int, 5> a = {1, 2, 3, 4, 5};
a.size();          // 5, always — no pointer decay
a.fill(0);         // reset all elements
sort(a.begin(), a.end());
```

In CP, `std::array` is useful when you need **STL compatibility without heap allocation** — e.g., as a key type in `map`, or as the return value of a function that would otherwise decay to a pointer. For pure CP use, though, plain C arrays declared globally remain the most common choice.

### Stack overflow with large local arrays

The **stack is typically 8 MB** (Linux default). A local `int a[1'000'000];` is 4 MB — dangerously close to the limit once you add the call chain. A local `int a[10'000'000];` is 40 MB and **will crash** with a segmentation fault or, worse, produce garbage under `-O2` because the runtime did not catch the overflow.

The fix is simple and habitual: **declare any array larger than ~100 KB at global scope**.

```cpp
// BAD: 4 MB on the stack — dangerous
int main() {
    int dp[1'000'000];
    // ...
}

// GOOD: 4 MB in the static data segment — safe, zero-initialized
constexpr int MAXN = 1'000'000;
int dp[MAXN];   // global

int main() {
    // ...
}
```

If you *must* have a local array whose size is enormous, use `vector<int>` instead — it allocates on the heap. If you genuinely need a stack array for performance, increase the stack size locally with `ulimit -s unlimited` (this affects *your* machine, not the judge — never rely on it in the final submission).

### Multi-dimensional arrays — memory layout matters

A 2D array `int mat[R][C]` is *not* an array of arrays in the general sense; it is one contiguous block of `R * C` ints, stored **row-major**:

```
int mat[2][3] = {{1,2,3}, {4,5,6}};

Address:  0x1000 0x1004 0x1008 0x100c 0x1010 0x1014
Value:      1      2      3      4      5      6
Logical:  [0][0] [0][1] [0][2] [1][0] [1][1] [1][2]
```

The address of `mat[i][j]` is `base + (i * C + j) * sizeof(int)`. Two consequences:

1. **Iterating row by row matches memory order** — the cache happily prefetches the entire next row.
2. **Iterating column by column jumps `C * sizeof(int)` bytes at each step** — every access is a potential cache miss. For a \(1000 \times 1000\) array, column-major traversal can be **5–10× slower** than row-major:

```cpp
// FAST — row-major traversal matches memory layout
for (int i = 0; i < R; ++i)
    for (int j = 0; j < C; ++j)
        sum += mat[i][j];

// SLOW — column-major traversal, cache-hostile
for (int j = 0; j < C; ++j)
    for (int i = 0; i < R; ++i)
        sum += mat[i][j];
```

> **How big can a 2D array be?** With a 256 MB limit, you can fit \(\lfloor 256 \cdot 10^6 / 4 \rfloor = 64 \cdot 10^6\) ints. That is a \(8000 \times 8000\) grid, not \(10^3 \times 10^3\) as some tutorials incorrectly state. The practical limit depends on the memory limit and element size, not on any "row × column" threshold. Compute `R * C * sizeof(T)` and compare it to the limit before assuming a matrix "won't fit".

## `std::vector` — the dynamic array

`std::vector<T>` is a heap-allocated, dynamically-sized, contiguous array. For competitive programming, it is the default choice for anything whose size is read at runtime. Its overhead over a raw array is one pointer (`data()`), one size counter, and one capacity counter — **24 bytes on 64-bit**, allocated on the heap.

### Construction — five idioms to know

```cpp
vector<int> v1;                  // empty, capacity 0
vector<int> v2(5);               // five 0s
vector<int> v3(5, 10);           // {10, 10, 10, 10, 10}
vector<int> v4 = {1, 2, 3, 4};   // list initialization
vector<int> v5(v4.begin(), v4.end()); // copy of v4
```

All five are common in CP, but the second one has a trap:

> **`vector<int> v(-1)` is a bomb.** The constructor's parameter is `size_t` (unsigned). `-1` is converted to `SIZE_MAX ≈ 1.8 · 10^{19}`, the vector tries to allocate that many `int`s, and you get `std::bad_alloc` or a hard crash. If a variable that should be non-negative becomes negative, the bug manifests as a memory error rather than a logical wrong answer — much harder to debug. **Compile with `-Wall -Wextra`**; GCC warns about the sign conversion for literals.

### `push_back` vs `emplace_back`

Both append an element in amortized \(O(1)\). The distinction only matters for non-trivial types:

```cpp
vector<pair<int, int>> vp;
vp.push_back({1, 2});           // constructs a temporary pair, then moves it
vp.emplace_back(1, 2);          // constructs the pair in place — one fewer move

vector<string> vs;
vs.push_back("hello");          // temporary, then move — usually optimized away
vs.emplace_back(10, 'a');       // constructs "aaaaaaaaaa" in place — no temporary
```

For `int`, `long long`, `double`, and small structs, the difference is negligible and `push_back` is clearer. For containers of containers, `emplace_back` can save measurable time. In DP-heavy code where you build arrays of pairs millions of times, `emplace_back` is the right habit.

### `size` vs `capacity` vs `reserve` vs `resize`

This is the most important conceptual difference in `vector`. Understanding it eliminates both TLEs and memory bugs:

- **`size()`** — number of elements currently in the vector.
- **`capacity()`** — number of elements the current allocation can hold *without reallocating*. `capacity() >= size()` always.
- **`reserve(n)`** — ensures `capacity() >= n`. Does **not** change `size()`. If called before a series of `push_back`, it eliminates all reallocations.
- **`resize(n)`** — changes `size()` to exactly `n`. If `n > size()`, new elements are value-initialized (`0` for `int`, `""` for `string`); if `n < size()`, elements are destroyed.

```cpp
vector<int> v;
v.reserve(1'000'000);       // capacity is now >= 1e6, size is still 0
for (int i = 0; i < 1'000'000; ++i) v.push_back(i);   // zero reallocations

v.resize(500'000);          // size is now 500k — half the elements destroyed
```

> **The `10^5` bug (seriously).** In C++, `10^5` is **bitwise XOR**, not exponentiation. `10 ^ 5` equals `15`, not `100000`. So a line like

```cpp
v.reserve(10^5);                         // reserves 15 elements — useless!
for (int i = 0; i < 10^5; ++i) { ... }   // loops 15 times, not 100000!
```

silently loops the wrong number of times and reserves the wrong amount of memory. This is a real, common WA pattern in CP code. Always write `100000`, `100'000`, or `1e5` (which is a `double` and converts to `int` cleanly — `int(1e5) == 100000`, but be aware that `1e9` as a `double` is exact while `1e10` is not).

### How `vector` grows — and why iterators are invalidated

When `push_back` needs space and `size == capacity`, the vector allocates a new buffer of typically **2× the current capacity**, moves all elements, and frees the old buffer. This is amortized \(O(1)\) because the geometric growth spreads the reallocation cost across all insertions.

The consequence is **iterator invalidation**:

> **After any `push_back` that triggers reallocation, all iterators, pointers, and references into the vector are invalidated.**

```cpp
vector<int> v = {1, 2, 3};
int* p = &v[0];
v.push_back(4);          // may reallocate — p is now dangling
cout << *p;              // UNDEFINED BEHAVIOR
```

The classic bug pattern is modifying a vector inside a range-`for`:

```cpp
for (int x : v) {
    if (x < 0) v.push_back(-x);   // UB — invalidates the implicit iterator
}
```

If you need to append while iterating, use an explicit index and process the appended elements in a second pass, or collect the additions in a separate vector first:

```cpp
vector<int> to_add;
for (int x : v) if (x < 0) to_add.push_back(-x);
v.insert(v.end(), to_add.begin(), to_add.end());
```

`reserve()` before a loop with `push_back` avoids all reallocations and the invalidation problem entirely:

```cpp
v.reserve(n);
for (int i = 0; i < n; ++i) v.push_back(compute(i));
```

### Element access

```cpp
vector<int> v = {10, 20, 30, 40};

v[0]            // no bounds check — O(1), the workhorse in CP
v.at(0)         // bounds check — throws std::out_of_range, ~2x slower
v.front()       // v[0]
v.back()        // v[size()-1]
v.data()        // raw pointer — useful for C API interop and scanf
```

For competitive programming, prefer `v[i]` — the bounds check in `.at()` is a real cost in hot loops, and correctness is guaranteed by your algorithm. Use `.at()` only while **debugging** an out-of-bounds bug: compile with `-D_GLIBCXX_DEBUG` and every `v[i]` out-of-bounds becomes a runtime error, catching the bug immediately.

> **Empty-vector traps.** `v.back()` and `v.pop_back()` on an empty vector are undefined behavior. `v[v.size() - 1]` wraps to `v[SIZE_MAX]` and crashes. Always guard with `if (!v.empty())` before back/pop.

### Iterating — four idiomatic forms

```cpp
vector<int> v = {1, 2, 3, 4, 5};

// 1. Index — needed when you also want the position
for (int i = 0; i < (int)v.size(); ++i)
    cout << v[i] << " ";

// 2. Range-based — cleanest for read-only iteration
for (const int& x : v)
    cout << x << " ";

// 3. Iterator — needed for STL algorithms that return iterators
for (auto it = v.begin(); it != v.end(); ++it)
    cout << *it << " ";

// 4. Reverse iterator — for backward passes
for (auto it = v.rbegin(); it != v.rend(); ++it)
    cout << *it << " ";
```

**Prefer the range-based form** for anything read-only, with `const auto&` for non-trivial element types. For write access, use `auto&`:

```cpp
for (int& x : v) x *= 2;               // modifies v — cheap, int is a primitive
for (const string& s : vs) cout << s;  // no copies
for (string s : vs)        /* BUG */ ; // copies every string
```

The signed/unsigned trap resurfaces with `.size()`:

```cpp
for (int i = 0; i < v.size(); ++i)         // warns with -Wsign-compare; safe only if i >= 0
for (int i = 0; i < (int)v.size(); ++i)    // explicit cast — recommended
for (size_t i = 0; i < v.size(); ++i)      // fully unsigned — also fine
```

## STL Algorithms on Ranges

`<algorithm>` and `<numeric>` provide operations that operate on any iterator range — `vector`, `std::array`, C arrays, `string`, `deque`. These are implemented by experts and are usually faster than hand-rolled equivalents because the compiler can vectorize them.

### Sorting

```cpp
sort(v.begin(), v.end());                            // ascending, O(n log n)
sort(v.begin(), v.end(), greater<int>());            // descending
sort(v.begin(), v.end(), [](int a, int b) {          // custom order
    return (a % 10) < (b % 10);                      // sort by last digit
});
```

> **The comparator must define a strict weak ordering.** `return a <= b;` is a bug — it says `a` comes before itself, which `sort` does not expect, and the standard says the behavior is undefined. It usually looks fine on small inputs and crashes or loops on large ones. **Always use `<`, never `<=`.**

For pairs and tuples, `sort` uses lexicographic order by default — `pair<int, int>` sorts by first, then by second. This is why the `pair` type is so convenient for sorting events, coordinates, or anything with a natural tiebreak.

### `unique` — the shift-and-return idiom

`unique(begin, end)` does **not** remove elements. It **shifts the first of each run of equal elements to the front**, and returns an iterator past the last unique element. To actually remove duplicates:

```cpp
sort(v.begin(), v.end());                              // sort first — required
v.erase(unique(v.begin(), v.end()), v.end());          // then erase tail
```

If you call `unique` without sorting, only *consecutive* duplicates are collapsed — which is almost never what you want.

### Binary search — `lower_bound`, `upper_bound`, `binary_search`

These require the range to be **sorted** (by the same comparator). They return **iterators**, not indices:

```cpp
sort(v.begin(), v.end());

bool found = binary_search(v.begin(), v.end(), 5);

// First position where v[i] >= 5
int lo = lower_bound(v.begin(), v.end(), 5) - v.begin();

// First position where v[i] > 5
int hi = upper_bound(v.begin(), v.end(), 5) - v.begin();

// Count of elements equal to 5
int cnt = hi - lo;
```

The `- v.begin()` conversion to index is the idiomatic way to use these in CP. `lower_bound` on an unsorted range is *undefined behavior* — not just "wrong result", actually UB, because the algorithm uses the comparator's transitivity assumption to narrow the search.

### `iota`, `fill`, `accumulate`, `count`, `find`, `reverse`

```cpp
#include <numeric>

vector<int> v(n);
iota(v.begin(), v.end(), 0);           // v = {0, 1, 2, ..., n-1}
fill(v.begin(), v.end(), -1);          // set all elements
long long total = accumulate(v.begin(), v.end(), 0LL); // 0LL forces long long accumulation

int c = count(v.begin(), v.end(), 5);
auto it = find(v.begin(), v.end(), 9);
reverse(v.begin(), v.end());
```

> **`accumulate(v.begin(), v.end(), 0)` on an `int` vector accumulates in `int`** — the result overflows at \(2^{31}\), silently. Use `0LL` to force 64-bit accumulation. This is one of the most common silent-WA patterns in contest code.

## 2D Structures

Two idioms for 2D data, with different tradeoffs.

### Nested vectors — `vector<vector<int>>`

```cpp
int n, m; cin >> n >> m;
vector<vector<int>> grid(n, vector<int>(m));
for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
        cin >> grid[i][j];
```

Clear, natural syntax, `grid[i][j]` works as expected. The downside is that each inner vector is a **separate heap allocation**, so rows are not contiguous with each other. For \(n = 10^5\) rows of size 1, this is 100,000 separate allocations — a measurable constant-factor cost. For moderate \(n, m\), it is fine; the clarity usually wins.

### Flat vector — one contiguous buffer

```cpp
int n, m; cin >> n >> m;
vector<int> grid(n * m);
auto idx = [m](int i, int j) { return i * m + j; };
for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
        cin >> grid[idx(i, j)];
```

One allocation, perfect cache locality, and `.data()` gives you a raw pointer if needed. The downside is the explicit index arithmetic — a source of subtle bugs (`i * m + j` vs `i * n + j`) if you are not careful. **Use flat vectors for large grids** ($n \cdot m \ge 10^6$) or when you will do row-wise passes; use nested for readability otherwise.

### Fixed 2D array at global scope

For matrices with compile-time dimensions, the simplest option is often the best:

```cpp
constexpr int MAXN = 1'005;
int mat[MAXN][MAXN];   // global — zero-initialized, one allocation
```

This is a single contiguous block of `MAXN * MAXN * 4` bytes — for `MAXN = 1005`, about 4 MB. Fits comfortably under any memory limit and is fast enough that grid DP, BFS on grids, and prefix-sum matrices rarely need more.

## Patterns You Will Reuse Constantly

### Global arrays for large state

```cpp
constexpr int MAXN = 200'005;
int parent[MAXN];
long long dist[MAXN];
int visited[MAXN];
```

Global = zero-initialized, no stack limit, no allocation overhead. The default choice for anything above ~10^4 elements.

### Prefix sums — \(O(1)\) range-sum queries after \(O(n)\) preprocessing

```cpp
vector<long long> pref(n + 1, 0);
for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + a[i];
// sum of a[l..r] inclusive:
long long s = pref[r + 1] - pref[l];
```

Use `long long` for the prefix array — the running sum of \(10^5\) values near \(10^9\) overflows `int`.

### Adjacency list for graphs

```cpp
vector<vector<int>> adj(n);
for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v; --u; --v;
    adj[u].push_back(v);
    adj[v].push_back(u);   // omit for directed graphs
}
```

This is *the* standard graph representation in CP: \(O(V + E)\) memory and \(O(\text{deg}(u))\) neighbor iteration. Most graph algorithms are written against it directly.

### DP table as a vector

```cpp
vector<long long> dp(n + 1, INF);
dp[0] = 0;
for (int i = 1; i <= n; ++i)
    for (int j : moves[i])
        dp[i] = min(dp[i], dp[j] + cost(j, i));
```

For DP with only previous-row dependency, a **rolling array** saves memory:

```cpp
vector<long long> prev(m + 1, 0), curr(m + 1, 0);
for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) curr[j] = ...;
    swap(prev, curr);   // O(1) — no copying
}
```

### `bitset` for boolean arrays

`vector<bool>` is a bit-packed specialization with proxy references — `bool&` does not work, `&v[i]` does not compile, and non-adjacent elements share bytes. For a dense boolean array, use `std::bitset` instead:

```cpp
bitset<200'005> visited;    // 25 KB, all zeros
visited[42] = 1;
visited.count();            // number of set bits
visited.flip();             // complement
```

`bitset` operations (`&`, `|`, `^`, `<<`, `>>`) run on entire words in parallel — a `bitset<10^6>` shift is ~15,000× faster than a loop. This is the foundation of many "small boolean state" optimizations in DP and reachability.

## Performance Considerations

Rough throughput of array- and vector-based operations on typical judge hardware with `-O2`:

| Operation | Operations per second |
|---|---|
| `v[i]` (sequential, cached) | \(\sim 10^9\) |
| `push_back` with `reserve` | \(\sim 10^8 - 10^9\) |
| `push_back` without `reserve` | \(\sim 10^7 - 10^8\) (reallocation dominates) |
| `sort` | \(\sim 10^7 \cdot \log n\) comparisons |
| `lower_bound` (random access) | \(\sim 10^7\) per second |
| `std::map` operation | \(\sim 10^6 - 10^7\) |
| `unordered_map` operation | \(\sim 10^6 - 10^7\) |

**Key guidance:**

- **`reserve` when the final size is known.** For a vector of \(10^6\) elements, `reserve` before the `push_back` loop can save 20 reallocations and 2× total memory churn.
- **Contiguous beats tree-shaped.** Sorting a vector and binary-searching it is often 10× faster than using `std::map` or `std::set` for the same logical queries, because the vector never leaves cache. **Reach for `map` only when you need ordered insertion/deletion interleaved with queries.**
- **Small integer keys can use arrays as hash maps.** A `vector<int> cnt(MAXV)` indexed by value is \(O(1)\) with a tiny constant — beats `unordered_map` unless `MAXV` is large and sparse. This is the "direct-address table" trick and is everywhere in CP.
- **Flat 2D arrays beat nested vectors for large grids.** For \(1000 \times 1000\), the difference is typically 2–3×.
- **Iterate in memory order.** Row-major for row-major arrays; forward for forward-access containers. The cache loves this.

## Common Pitfalls

A checklist to run whenever your array- or vector-based solution WAs or TLEs:

1. **`10^5` instead of `100000`** — `^` is XOR, not power. `10^5 == 15`, not `100000`. Write `100'000` or `1e5`.
2. **Local arrays are uninitialized** — global arrays are zero, local ones are garbage. Declare large state at global scope.
3. **Stack overflow from large local arrays** — a local `int a[10^6]` is 4 MB; the stack is typically 8 MB. Move it to global.
4. **`vector<int> v(-1)`** — constructor parameter is `size_t`, `-1` becomes `SIZE_MAX`, crash.
5. **`v.back()` or `v.pop_back()` on an empty vector** — UB; guard with `!v.empty()`.
6. **`v.size() - 1` on an empty vector** — wraps to `SIZE_MAX`; guard.
7. **Iterators invalidated by `push_back`** — reference/pointer/iterator into the vector is dangling after a reallocation. Use `reserve` or index-based access.
8. **Modifying a container inside a range-`for`** — the same invalidation, hidden.
9. **`accumulate(v.begin(), v.end(), 0)` on an `int` vector** — accumulates in `int`, overflows silently. Use `0LL`.
10. **`unique` without `sort`** — only removes *consecutive* duplicates.
11. **`unique` without `erase`** — only shifts elements; the container still has `n` elements.
12. **`lower_bound` on an unsorted range** — UB, not just a wrong result.
13. **Comparator `return a <= b`** — not a strict weak ordering; UB. Use `<`.
14. **`v.at()` in a hot loop** — bounds check costs 1.5–2×; use `v[i]` unless debugging.
15. **Passing a vector by value** — copies the entire buffer. Use `const vector<int>&`.
16. **`vector<bool>` misuse** — proxy references, `bool&` does not compile, `&v[i]` invalid. Use `bitset` or `vector<char>`.
17. **Column-major traversal of a row-major 2D array** — 5–10× slowdown from cache misses.
18. **`i * m + j` vs `i * n + j`** in flat-vector indexing — a silent way to read wrong cells.
19. **Signed/unsigned comparison with `.size()`** — safe only if the counter is always \(\ge 0\); use `(int)v.size()` when in doubt.
20. **`sort` on a range of size 0** — fine (no-op), but `v.front()` on an empty vector is UB; guard.

## Key Takeaways

- An array is contiguous memory; indexing is \(O(1)\) address arithmetic, and sequential access exploits the cache. Every fast data structure in CP rests on this.
- **Global arrays are zero-initialized and escape the 8 MB stack.** Default to global for anything larger than ~\(10^4\) elements.
- `vector` is the default container for runtime-sized data. Use `reserve` to eliminate reallocations; `resize` changes size, `reserve` changes capacity.
- **`push_back` may invalidate all iterators into the vector.** Guard with `reserve`, or use index-based access.
- The comparator in `sort` must be strict (`<`, not `<=`). The result of violating this is undefined behavior.
- `accumulate` accumulates in the initial value's type — use `0LL` for `long long` results.
- 2D: nested `vector<vector<int>>` for clarity, flat `vector<int>` for large grids. Row-major traversal matches memory layout.
- Reach for **arrays and `bitset` before `map`** whenever possible — contiguous memory is orders of magnitude faster than tree-shaped containers.
- Write `100'000`, not `10^5`. The XOR bug is silent and lethal.

## Practice Problems

- [CSES — Missing Number](https://cses.fi/problemset/task/1622) — sum-based solution; watch `long long` accumulation over \(10^6\) elements near \(10^6\).
- [CSES — Repetitions](https://cses.fi/problemset/task/1069) — sequential scan; the canonical exercise in memory-order iteration.
- [Codeforces 474B — Worms](https://codeforces.com/problemset/problem/474/B) — prefix sums + `lower_bound`; classic conversion from iterator to index.
- [CSES — Josephus Problem I](https://cses.fi/problemset/task/2162) — array-based simulation, then the \(O(n \log n)\) optimization; good intuition for where arrays stop being enough.
- [CSES — Message Route](https://cses.fi/problemset/task/1667) — BFS on an adjacency list; the `vector<vector<int>>` graph representation in action.
- [Codeforces 1213D1 — Equalizing by Division (easy)](https://codeforces.com/problemset/problem/1213/D1) — array-based counting; introduces the "small key → direct array" trick.

## References

- [cppreference — `std::vector`](https://en.cppreference.com/w/cpp/container/vector)
- [cppreference — `std::array`](https://en.cppreference.com/w/cpp/container/array)
- [cppreference — `<algorithm>`](https://en.cppreference.com/w/cpp/algorithm)
- [cppreference — `<numeric>` (`iota`, `accumulate`)](https://en.cppreference.com/w/cpp/numeric)
- [cppreference — `std::bitset`](https://en.cppreference.com/w/cpp/utility/bitset)

## Next Topic

[Functions and Recursion](functions-and-recursion.md)