---
title: Functions and Recursion
tags:
  - Course
---

# Functions and Recursion

Functions and recursion are two names for the same idea viewed from different angles: a function is *how you factor a problem into reusable pieces*, and recursion is *how you let those pieces call themselves*. In competitive programming, this pair is unavoidable — DFS, divide-and-conquer, segment trees, backtracking, memoized DP, and union-find with path compression are all recursive by nature. Almost every non-trivial graph algorithm you will write for the rest of this course either **is** a recursion or **was** a recursion converted to an explicit stack.

The subtlety is that recursion in CP is not the recursion of textbooks. In a contest you are under an 8 MB stack, a 1 s time limit, and a judge that compiles your code with `-O2` — which changes how deep you can recurse and how much the compiler inlines. This article covers the parts that actually bite: **passing parameters cheaply, understanding stack frames, memoization, and converting recursion to iteration when depth matters**.

## Prerequisites

- [Introduction to C++](intro-to-cpp.md) — `-O2`, the CP template.
- [I/O and Data Types](io-and-data-types.md) — `int` vs `long long`, `size_t`, overflow.
- [Conditionals and Loops](conditionals-and-loops.md) — loop idioms.
- [Arrays and Vectors](arrays-and-vectors.md) — global arrays, `vector`, contiguous memory, iterator invalidation.

## Functions — What Actually Matters in CP

The syntax of `int f(int x) { return x + 1; }` is something you already know. What follows are the parts that determine whether your solution passes or TLEs, and the parts that produce silent bugs.

### The global-state idiom

In CP, functions almost never receive their state through parameters. Instead, state lives in **global arrays** declared once at file scope, and functions read/write them directly:

```cpp
constexpr int MAXN = 200'005;
vector<int> adj[MAXN];       // adjacency list
int dist[MAXN];              // BFS distances
bool visited[MAXN];          // DFS visited flags

void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v]) dfs(v);
}
```

This is deliberately *not* the "clean" way to write software, but it is the CP way, for three reasons:

1. **No copying.** Passing a `vector<vector<int>>` by value would copy the entire graph on every call. Global access is a memory read, not a copy.
2. **No stack frame bloat.** Every local variable added to a recursive function's signature enlarges its stack frame, reducing the recursion depth you can afford before crashing.
3. **Contest speed.** You write `dfs(u)`, not `dfs(u, adj, dist, visited, parent, ...)`. Fewer characters means fewer bugs under time pressure.

The one parameter that *does* travel through recursion is the **parent** — used to avoid revisiting the previous node in a tree DFS:

```cpp
void dfs(int u, int p) {   // p = parent of u; 0 or -1 at the root
    for (int v : adj[u])
        if (v != p) dfs(v, u);
}
```

### Pass by value, reference, and const reference — the CP-relevant rules

```cpp
void by_value(vector<int> v);            // COPIES the entire vector — usually a bug
void by_reference(vector<int>& v);       // allows modification, no copy
void by_const_ref(const vector<int>& v); // read-only, no copy — the default for input
```

Three practical rules:

- **Small primitives (`int`, `long long`, `double`, `char`, `bool`, small `pair`) — pass by value.** Copying 8 bytes is cheaper than dereferencing a reference.
- **Containers or structs, read-only — pass by `const&`.** This is the single most impactful habit for performance: a `const vector<int>&` on a \(10^5\)-element vector is O(1) instead of O(n) to pass.
- **Containers or structs, mutated — pass by `&`.** Same idea, allowing writes.

The performance difference is not marginal:

```cpp
long long sum_by_value(vector<int> v) {        // O(n) copy on every call
    long long s = 0;
    for (int x : v) s += x;
    return s;
}

long long sum_by_ref(const vector<int>& v) {   // O(1) pass
    long long s = 0;
    for (int x : v) s += x;
    return s;
}
```

For a loop that calls this \(10^5\) times on vectors of size \(10^5\), the first version does \(10^{10}\) extra element copies — that's a TLE the compiler cannot save you from.

### Return by value — RVO makes it free

Returning a `vector` or `string` from a function *looks* expensive but usually is not. C++17 guarantees **Return Value Optimization (RVO)** in the common case — the return object is constructed directly in the caller's storage, with no copy and no move:

```cpp
vector<int> make_range(int n) {
    vector<int> v(n);
    iota(v.begin(), v.end(), 0);
    return v;   // No copy — constructed in the caller's slot (C++17 guaranteed)
}

vector<int> v = make_range(10);
```

In CP, returning a `pair<int, int>`, `tuple`, or `vector` from a helper is idiomatic and free.

### `inline` — the semantic meaning, not the optimization hint

Most tutorials describe `inline` as "a hint to the compiler to insert the function body at the call site". That was true in 1995. **In modern C++, `inline` primarily has a semantic meaning**: it allows a function to be defined in a header file and included in multiple translation units without violating the One Definition Rule (ODR). The optimization hint is a legacy side effect — GCC's `-O2` decides what to inline based on cost models, largely ignoring your `inline` keyword.

For CP, this means:

- **Don't sprinkle `inline`** to "make your code faster". It doesn't.
- **Use `inline` on functions defined in headers** if you ever split your code into multiple files. For single-file contest submissions, this never applies.
- **Trust `-O2`** to inline small functions. It does, aggressively.

> **Pitfall.** `-O2` inlines almost everything, which means **your stack frames for inlineable functions disappear** — useful for reducing recursion depth, but it also means your `static` variables inside inlined functions may behave unexpectedly if you rely on function identity. Don't use `static` inside recursive functions (see pitfalls below).

### Function templates — cheap generics

CP code often needs the same function for `int` and `long long`:

```cpp
template<typename T>
T gcd(T a, T b) {
    while (b) { T t = a % b; a = b; b = t; }
    return a;
}
```

This is the standard CP idiom: `gcd<int>(12, 18)` and `gcd<long long>(1e18, 1e9)` compile to two independent, fully-inlined functions. `__gcd` from `<algorithm>` and `std::gcd` from `<numeric>` work too, but writing your own template is trivial and avoids namespace conflicts.

### Default arguments — a small caution

```cpp
long long modpow(long long b, long long e, long long m = 1'000'000'007) { ... }
```

Convenient, but default arguments are **evaluated at the call site**, not at the definition, so a default that references a global constant must be visible at every call site. In single-file CP code this is fine; in multi-file builds it can produce surprises. Also, defaults only work right-to-left, so once you add one defaulted parameter, all following parameters must also be defaulted.

## Recursion — the mental model

A recursive function is just a function that calls itself. What makes recursion powerful in CP is that the **call stack acts as an implicit data structure** — it remembers the path from the root to the current state without any explicit bookkeeping in your code.

When you write:

```cpp
void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v]) dfs(v);
}
```

the compiler emits code that, on each call, pushes a **frame** onto the stack containing the current `u` and the loop iterator. When `dfs(v)` returns, `u` and the iterator are restored automatically. You get the "path from the current node to the DFS root" for free — without keeping an explicit vector of ancestors.

This is why recursion is elegant for trees, DFS, and backtracking, and awkward for simple loops. The cost is that every recursive call consumes **real memory** on the stack, and the depth of that stack is limited.

### Stack frames — why depth is limited

Each recursive call pushes a stack frame onto the **call stack**. The frame contains:

- Return address (8 bytes on x86-64).
- Saved registers (variable; often 0–48 bytes).
- Function parameters not passed in registers.
- Local variables (`int`, `long long`, small arrays).

Typical frame sizes for competitive C++ functions:

| Function body | Approximate frame size |
|---|---|
| Empty function, few `int` locals | ~32 bytes |
| Function with 5–10 locals | ~64–128 bytes |
| Function with a local array `int a[100]` | ~400+ bytes |
| Function with a local `vector<int> v` | ~24 bytes (the vector itself is on heap) |

The **stack limit** on Linux is typically **8 MB** (`ulimit -s`). So:

- ~32-byte frames → depth ≈ 250,000
- ~64-byte frames → depth ≈ 130,000
- ~128-byte frames → depth ≈ 65,000

This is why **recursion to depth \(10^5\) works on most judges but not all**, and why depth \(10^6\) reliably segfaults.

> **The real numbers per judge.**
>
> - **Codeforces**: submissions run in a **thread with a 256 MB stack**, not the default 8 MB. Depth \(10^6\) typically works; depth \(10^7\) is risky.
> - **AtCoder**: 1024 MB stack by default. Very forgiving; large recursion works.
> - **CSES**: 512 MB; depth \(10^6\) is fine.
> - **Many other judges** (SPOJ, some UVa mirrors, custom judges): default 8 MB. Depth beyond ~\(10^5\) crashes unpredictably.
> - **Local testing on Linux**: `ulimit -s` is typically 8192 (8 MB). See the pitfall below.

**Rule of thumb**: if the problem has \(n \le 10^5\) and the recursion depth is bounded by \(n\) (e.g., DFS on a tree), you are safe on major judges. For \(n \le 10^6\), **convert to iterative** unless you know the judge gives a large stack.

### The `setrlimit` myth

Many CP tutorials (including the original version of this article) suggest:

```cpp
#include <sys/resource.h>
void increase_stack() {
    const rlim_t kStackSize = 16 * 1024 * 1024;
    struct rlimit rl;
    int res = getrlimit(RLIMIT_STACK, &rl);
    if (res == 0 && rl.rlim_cur < kStackSize) {
        rl.rlim_cur = kStackSize;
        setrlimit(RLIMIT_STACK, &rl);
    }
}
```

**This does not work on modern Linux.** The main thread's stack is allocated by the kernel at program startup, based on the `RLIMIT_STACK` value at `exec` time. Calling `setrlimit` after the program has started **does not enlarge the already-mapped stack** — it only changes the limit for threads created *afterwards*. On a judge that compiles and runs your code with the default 8 MB, this function does nothing.

The reasons this code persists in tutorial-land:

- It's a copy of a copy of a hack from 20 years ago, when the situation was different.
- Some judges (notably Codeforces) **do** run submissions in a thread with a pre-set large stack size — but that is done by the **judge's wrapper**, not by your program calling `setrlimit`.
- On old Linux kernels the main stack could still grow up to the new `rlim_cur` if `setrlimit` was called early. This is no longer reliable.

**The correct advice**: **do not rely on `setrlimit`**. Either (a) assume the judge gives you enough stack for the depth implied by the problem constraints, or (b) rewrite the algorithm iteratively. Do not add this function to your template.

### Converting recursion to iteration

When depth is a real risk, convert to an explicit stack. The transformation is mechanical:

**Recursive DFS:**
```cpp
void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v]) dfs(v);
}
```

**Iterative DFS, same behavior (pre-order):**
```cpp
void dfs_iter(int start) {
    vector<int> stack = {start};
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        if (visited[u]) continue;
        visited[u] = true;
        for (int v : adj[u])
            if (!visited[v]) stack.push_back(v);
    }
}
```

The differences to be aware of:

- **Pre-order vs post-order.** The iterative version processes the node *when popped*, which equals pre-order. If you need post-order (process node *after* its children), push a `(u, phase)` pair or push `u` twice — once as "to process", once as "to finish".
- **Memory.** The explicit stack uses heap, not the call stack, so depth is limited only by available memory — effectively unlimited for CP.
- **Performance.** Iterative DFS is typically **1.5–3× faster** than recursive DFS, because there is no call/return overhead and no register saves per frame. For \(10^6\)-node graphs, this matters.
- **Clarity.** Recursive DFS is easier to write and read for most patterns. Use iterative only when depth is a concern, or when profiling shows the recursive version is too slow.

For **BFS**, there is no recursive equivalent that makes sense (BFS is inherently level-by-level), so you will always write it iteratively with a queue.

### Memoization — the top-down DP pattern

Recursion becomes a **dynamic programming technique** when you cache the result of each subproblem. This is called **top-down DP** or **memoization**, and it is often the fastest way to code a DP when you are not sure which states are reachable:

```cpp
constexpr int MAXN = 100'005;
long long memo[MAXN];          // 0 means "not computed" — valid only if 0 isn't a possible answer
bool computed[MAXN];           // explicit flag — the safe way

long long solve(int n) {
    if (n <= 1) return 1;
    if (computed[n]) return memo[n];
    long long result = solve(n - 1) + solve(n - 2);
    memo[n] = result;
    computed[n] = true;
    return result;
}
```

The sentinel choice matters:

- **`0` as sentinel** works only if `0` is never a legitimate answer. Many CP solutions use this (e.g., counting paths where every count is ≥ 1).
- **`-1` as sentinel** works for non-negative answers, but not for signed sums that could be negative.
- **A separate `bool[]`** works universally and costs at most one array. **Use it when in doubt.**

For 2D or larger state spaces, use a `vector` of the right dimension:

```cpp
vector<vector<long long>> memo(n + 1, vector<long long>(m + 1, -1));

long long dp(int i, int j) {
    if (i == 0) return 1;
    if (memo[i][j] != -1) return memo[i][j];
    // ...
}
```

> **Pitfall.** `vector<vector<long long>>` allocates one heap block per row — the same "row discontiguity" problem from the previous article. For DP tables accessed in nested loops, a **flat vector** (`vector<long long> memo((n+1)*(m+1), -1)` with index `i*(m+1)+j`) is faster and saves allocation overhead. For DP tables accessed by sparse recursion, the difference is marginal.

### Recursion + `-O2` — what changes

At `-O2`, GCC performs **tail-call optimization** for self-recursive functions in tail position. A tail call is a recursive call that is the **last operation** of the function:

```cpp
// Tail-recursive (TCO possible): recursive call is the last thing
long long fact_tail(int n, long long acc = 1) {
    if (n <= 1) return acc;
    return fact_tail(n - 1, acc * n);
}

// NOT tail-recursive: multiplication happens after the recursive call returns
long long fact(int n) {
    if (n <= 1) return 1;
    return n * fact(n - 1);
}
```

GCC at `-O2` **does** transform tail-recursive functions into loops, eliminating the stack growth. This makes the tail-recursive version safe for arbitrarily deep recursion — but **only for self-recursion**. Mutual recursion (`f` calls `g`, `g` calls `f`) and non-tail recursion are **not** optimized.

**Do not rely on TCO in CP:**

1. The transformation is not guaranteed by the C++ standard.
2. Judges that add sanitizers or debug flags may disable it.
3. Many functions you want to write (DFS, backtracking, merge sort) are not tail-recursive, so TCO is irrelevant.

The practical rule: **if depth is a concern, write the iterative version.** Relying on TCO for correctness is a source of runtime crashes that are impossible to reproduce locally.

### The `std::function` trap

When you need a recursive lambda (e.g., a one-off DFS passed to `std::sort` or captured in another function), the instinct is:

```cpp
function<void(int)> dfs = [&](int u) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v]) dfs(v);
};
dfs(0);
```

This compiles and works, but has three costs:

1. **Heap allocation.** `std::function` type-erases the lambda, which typically requires a heap allocation on construction. For a \(10^6\)-node graph with one DFS, the allocation is once; for nested lambdas called millions of times, it adds up.
2. **Indirection.** Every call to `dfs(v)` goes through a virtual function pointer, adding ~5–10 ns overhead per call. On a \(10^6\)-call DFS, that is 5–10 ms — measurable.
3. **Inlining blocked.** The compiler cannot inline a `std::function` call, so the body is a real function call with all the associated cost.

**For one-off DFS**, this is usually acceptable. **For hot recursive code**, use one of:

- **A global function** (the standard CP choice).
- **A `struct` with `operator()`** (zero-overhead, inlinable).
- **A lambda with `auto`** using the `this`-trick (C++23 `deducing this`) or the explicit self-pass pattern:

```cpp
auto dfs = [&](auto&& self, int u) -> void {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v]) self(self, v);
};
dfs(dfs, 0);
```

This compiles to essentially the same code as a named function — no heap allocation, no indirection, fully inlinable.

## Patterns You Will Reuse Constantly

### DFS on a tree, with parent

```cpp
void dfs(int u, int p) {
    for (int v : adj[u])
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
}
```

The `p` (parent) parameter replaces a `visited[]` array for trees: since trees have no cycles, avoiding the parent is sufficient to avoid revisits. This is faster and uses one fewer array than the general graph DFS.

### DFS on a general graph

```cpp
void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v]) dfs(v);
}
```

For general graphs (with cycles), `visited[]` is necessary. If the graph is disconnected, call `dfs(u)` for every unvisited `u`.

### Backtracking with pruning

Backtracking is a DFS over a **decision tree**, where each node represents a partial solution and each edge a choice. The template is:

```cpp
void backtrack(state, choices) {
    if (is_complete(state)) { record(state); return; }
    for (auto c : choices) {
        if (!feasible(state, c)) continue;   // pruning — the key to speed
        apply(state, c);
        backtrack(state, next_choices);
        undo(state, c);                       // restore state — the "backtrack"
    }
}
```

The canonical example is **N-Queens**:

```cpp
int n;
vector<int> queens(n);       // queens[r] = column of the queen in row r
int solutions = 0;

bool can_place(int r, int c) {
    for (int prev_r = 0; prev_r < r; ++prev_r) {
        int prev_c = queens[prev_r];
        if (prev_c == c) return false;                    // same column
        if (abs(prev_c - c) == r - prev_r) return false;  // same diagonal
    }
    return true;
}

void solve(int r) {
    if (r == n) { ++solutions; return; }
    for (int c = 0; c < n; ++c) {
        if (!can_place(r, c)) continue;   // prune — only try feasible columns
        queens[r] = c;
        solve(r + 1);
    }
}
```

Two observations that matter more than the template itself:

1. **Pruning is everything.** Without the `if (!can_place(...))` check, N-Queens would explore \(n^n\) possibilities. With pruning, \(n = 8\) explores only 92 solutions, and \(n = 12\) is fast.
2. **`undo` is the source of bugs.** Every `apply` must have a matching `undo` before the recursion returns. Missing it produces nonsense results that are painful to debug. The "push/backtrack with `pop_back`" pattern in the original subset example is the simplest case: `current.push_back(x)` must always be followed by `current.pop_back()` after the recursive call.

### Recursive segment tree

Segment trees are naturally recursive: a tree node represents a range `[l, r]`, and the children represent `[l, m]` and `[m+1, r]`.

```cpp
constexpr int MAXN = 100'005;
long long tree[4 * MAXN];
long long a[MAXN];

void build(int node, int l, int r) {
    if (l == r) { tree[node] = a[l]; return; }
    int m = (l + r) / 2;
    build(2 * node, l, m);
    build(2 * node + 1, m + 1, r);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

long long query(int node, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 0;              // disjoint
    if (ql <= l && r <= qr) return tree[node];   // fully covered
    int m = (l + r) / 2;
    return query(2 * node, l, m, ql, qr)
         + query(2 * node + 1, m + 1, r, ql, qr);
}
```

The recursion depth is \(O(\log n)\), so no stack concerns — a segment tree on \(10^6\) elements has depth ~20. This is one of the cases where recursion is **always** the right choice: the iterative version is a mess of bit manipulation and barely faster.

### Recursive union-find with path compression

```cpp
int parent[MAXN], sz[MAXN];

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);   // path compression
}
```

The `parent[x] = find(parent[x])` line is the **path compression**: it flattens the tree by making every node point directly to its root. The resulting amortized cost is nearly \(O(1)\) per query, and the recursion depth is bounded by the rank (logarithmic before compression, \(\le \log n\) after). **This is safe** — depth never exceeds 20 for \(n = 10^6\).

The iterative version is slightly faster:

```cpp
int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];   // path halving
        x = parent[x];
    }
    return x;
}
```

For most CP code, the recursive version is fine — the depth bound guarantees no overflow.

## Performance Considerations

| Operation | Typical cost |
|---|---|
| Function call, small body, inlined (`-O2`) | 0 (absorbed into caller) |
| Function call, non-inlined | ~2–5 ns |
| Recursive call, ~64-byte frame | ~5–10 ns + stack pointer adjustment |
| Recursive call via `std::function` | ~10–15 ns + heap lookup |
| Memoized recursive DP (hit) | ~5 ns for the array lookup |
| Memoized recursive DP (miss) | ~100 ns + the work of the subproblem |
| Iterative DFS (vs recursive) | **1.5–3× faster** |

**When recursion is the right choice:**

- Depth is small or bounded by \(O(\log n)\) (segment trees, DSU with path compression, divide-and-conquer on arrays).
- The problem is naturally recursive (DFS on trees, backtracking).
- You are prototyping and clarity matters more than 30% speed.

**When recursion is the wrong choice:**

- Depth could approach \(10^5\) or \(10^6\) and the judge may have a small stack (SPOJ, some UVa).
- The recursive call is on the hot path (inner loop of a \(10^7\)-iteration computation).
- You are writing BFS or any algorithm that is inherently iterative.

**When it does not matter:**

- Memoized DP where the number of states is small but the transitions are cheap. The recursion depth is bounded by the state dimension, usually small.
- Segment trees, DSU, and other \(O(\log n)\)-depth structures.

## Common Pitfalls

Checklist for when a solution with functions or recursion WAs, TLEs, or crashes:

1. **Missing base case** — infinite recursion → stack overflow (segfault, or silent crash on some judges).
2. **`int` overflow in recursive factorial** — `21!` overflows `long long`. Compute factorials modulo a prime, or use `__int128`, or use big-int emulation.
3. **Naive recursive Fibonacci** — \(O(\phi^n)\) calls, impractical for \(n > 40\). Use iterative \(O(n)\) or matrix exponentiation \(O(\log n)\).
4. **`setrlimit` doesn't increase the main thread stack** — modern Linux ignores it after startup. Don't rely on it.
5. **Default stack is 8 MB** — a 100,000-deep recursion with 64-byte frames uses ~6 MB; a 1,000,000-deep recursion segfaults.
6. **Passing a container by value** — O(n) copy per call; use `const&`.
7. **`std::function` for hot recursion** — heap allocation + indirection; use a global function or self-pass lambda.
8. **Missing `undo` in backtracking** — a `push_back` without a matching `pop_back` produces garbage.
9. **`static` variables inside recursive functions** — the static is shared across all recursion levels, not per-frame. This is almost never what you want.
10. **`vector<bool>` in a `visited` array** — proxy references; use `vector<char>` or global `bool[]`.
11. **Recursion depth in a tree chain** — a path graph of \(10^5\) nodes is depth \(10^5\); on judges with 8 MB stacks, this crashes. Convert to iterative DFS.
12. **Modifying a container inside recursive iteration** — invalidation; same as the loop pitfall from the previous article.
13. **Missing parent parameter in tree DFS** — you revisit the parent endlessly if the graph is a tree and you have no `visited[]` guard.
14. **`visited` set after the recursive call instead of before** — leads to revisiting the node during recursion, producing cycles or exponential blowup.
15. **Recursive segment tree on \(n = 0\)** — `build(1, 0, -1)` recurses forever; guard with `if (n == 0) return;`.
16. **Memoization with `-1` sentinel when `-1` is a valid answer** — false "already computed" hits. Use a `bool` flag array.
17. **Overlapping state in memoization** — memoizing on the wrong key (e.g., memoizing `solve(i)` when the state is actually `(i, j)`) produces wrong answers silently.
18. **Recursive `sort` comparator** — the comparator must be a strict weak ordering; do not call `sort` recursively inside a comparator.
19. **Tail-recursive Fibonacci** — the transformation requires an accumulator; naive `fib(n-1) + fib(n-2)` is not tail-recursive and gets no TCO.
20. **Assuming `inline` makes code faster** — GCC's `-O2` decides; the keyword is a semantic tool, not a performance tool.

## Key Takeaways

- Functions in CP read state from **global arrays**, not parameters. Pass only the parent (tree DFS) or small indices.
- **Always pass containers by `const&`** unless you intend to modify them. The performance difference is not marginal.
- Return by value is free thanks to RVO; returning a `vector` from a helper costs nothing.
- `inline` is a semantic keyword (ODR), not a performance hint. Trust `-O2` to inline small functions.
- Each recursive call uses a **real stack frame** (~32–128 bytes) on an **8 MB default stack**. Depth above ~\(10^5\) is risky on judges without large stacks.
- **Codeforces gives 256 MB stack; AtCoder ~1 GB; many smaller judges give the default 8 MB.** Assume 8 MB unless you know otherwise.
- **`setrlimit` does not enlarge the main thread stack** on modern Linux. Do not rely on it. Convert to iterative when depth matters.
- **Memoization turns recursion into top-down DP.** Choose the sentinel (`0`, `-1`, or explicit `bool[]`) based on the answer range.
- Recursion is **always right** for segment trees, DSU, and divide-and-conquer with \(O(\log n)\) depth. It is **usually right** for DFS and backtracking. It is **almost never right** for depth \(10^6\) without an explicit stack.
- **Backtracking = recursion + apply + undo.** Every `push_back` must have its `pop_back`.

## Practice Problems

- [CSES — Building Roads](https://cses.fi/problemset/task/1666) — connected components via DFS; test the recursive version against an iterative one on a chain input.
- [CSES — Subordinates](https://cses.fi/problemset/task/1674) — tree DP via recursion; small depth, ideal for learning the pattern.
- [CSES — Tree Diameter](https://cses.fi/problemset/task/1131) — two DFS passes; recursion depth equals the longest path — test both forms.
- [Codeforces 4C — Registration System](https://codeforces.com/problemset/problem/4/C) — not recursion, but good practice with `map` lookups inside loops that resemble recursion.
- [CSES — N-Queens](https://cses.fi/problemset/task/1624) — classic backtracking with pruning; the canonical DFS-with-undo problem.
- [Codeforces 1526C1 — Potions (Easy)](https://codeforces.com/problemset/problem/1526/C1) — iteratively re-derives a greedy result; a good contrast with the recursive DP formulation.
- [CSES — Company Queries I](https://cses.fi/problemset/task/1687) — binary lifting on trees; the classic case where an \(O(\log n)\) recursive formulation is replaced with an iterative doubling table.

## References

- [cppreference — Functions](https://en.cppreference.com/w/cpp/language/functions)
- [cppreference — `std::function`](https://en.cppreference.com/w/cpp/utility/functional/function)
- [GCC — Options that control optimization (`-O2`, `-finline-functions`)](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)
- [Stack Overflow — Does `setrlimit(RLIMIT_STACK)` work after program start?](https://stackoverflow.com/questions/2279052/increase-stack-size-in-linux-with-setrlimit)
- [Wikipedia — Tail call](https://en.wikipedia.org/wiki/Tail_call)

## Next Topic

[STL Basics](stl-basics.md)