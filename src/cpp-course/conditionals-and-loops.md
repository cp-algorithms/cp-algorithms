---
title: Conditionals and Loops
tags:
  - Course
---

# Conditionals and Loops

Every algorithm you will ever write in competitive programming is built from three things: **decisions** (which branch to take), **repetition** (how many times to do something), and **data** (what to do it on). This article is about the first two. Master them and the third — arrays, graphs, trees — becomes mechanical. Get them subtly wrong and no amount of clever algorithmic thinking will save you: a single off-by-one in a loop bound or a missing `break` turns a correct \(O(n \log n)\) idea into a WA.

The goal here is not just to list syntax. It is to build the reflexes you need under contest pressure: which construct to reach for, and — more importantly — which reflex will bite you when you are not paying attention.

## Prerequisites

- [Introduction to C++](intro-to-cpp.md) — compilation, `-O2`, the CP template.
- [I/O and Data Types](io-and-data-types.md) — `int` vs `long long`, signed/unsigned traps, `size_t`.

Throughout, we assume the standard template:

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

## Conditional Statements

### `if` / `else if` / `else` — making decisions

An `if` statement asks a yes/no question about the current state of the program and picks a path. In competitive programming, conditionals are the glue between the mathematical core of a solution and its many edge cases: *Is \(n = 1\)? Is the answer negative? Did we reach the target?*

```cpp
int x; cin >> x;
if (x > 0)        cout << "Positive\n";
else if (x < 0)   cout << "Negative\n";
else              cout << "Zero\n";
```

The key mental model is **short-circuit evaluation** and **top-down matching**. Conditions are tested in order; the first one that is `true` wins, and everything below is skipped. This is not just a control-flow detail — it is a performance tool. When a later condition is expensive (a `map` lookup, a string comparison, a geometric predicate), put the cheap ones first:

```cpp
if (n == 0) { /* O(1) early exit */ }
else if (is_valid(grid)) { /* O(n·m) — only checked when necessary */ }
```

In CP, you will write `if` statements for three common roles:

1. **Guard clauses at the top** — handle degenerate input immediately so the rest of the code can assume well-formed data.
2. **Classification** — separate cases that need different algorithms (e.g., \(n\) even vs odd, connected vs disconnected).
3. **Boundary checks inside loops** — `if (i + 1 < n && a[i] == a[i+1])` appears constantly in sliding-window and two-pointer solutions.

**Best practice.** Keep each condition small and named when it is not obvious. A line like `if (x >= 0 && x < n && y >= 0 && y < m && !visited[x][y])` is fine; a line like `if (a * b > c ^ d & e)` is a bug you haven't found yet.

### The `if (x = 5)` pitfall — assignment vs comparison

```cpp
int x = 3;
if (x = 5) { /* ... */ }   // assigns 5; condition is 5 (truthy); x becomes 5
if (x == 5) { /* ... */ }  // compares
```

Both lines compile. Only one does what you mean. This is the single most common typo in the history of C-family languages, and it has cost contestants countless submission penalties.

**The defense is your compiler.** Always compile with `-Wall -Wextra`. GCC emits `-Wparentheses` for this exact mistake and refuses to stay silent. If you are building a contest habit, make `-Wall -Wextra` muscle memory from day one. The alternative — the "Yoda condition" `if (5 == x)` — works but is unfashionable and hard to read; trust the compiler instead.

### The dangling `else` — a bug that looks correct

Consider:

```cpp
if (a)
    if (b) cout << "ab\n";
    else   cout << "not b\n";   // which if does this belong to?
```

The `else` binds to the **nearest unmatched `if`**. Here, that is `if (b)`, not `if (a)`. So the code reads as "if `a`, then: (if `b` print 'ab', else print 'not b')" — but a human reader almost always misreads it as "(if `a` and `b` print 'ab', else print 'not b')". The two interpretations differ whenever `a` is false.

**The fix is trivially reliable: always use braces.** Not "when the body is more than one line" — always. Braces cost one keystroke and eliminate the entire class of dangling-else bugs. If you only adopt one habit from this article, adopt this one.

### The ternary operator `?:` — compact decisions

The ternary operator produces a value based on a condition:

```cpp
int mx = (a >= b) ? a : b;
```

It is essential in competitive programming for compact expressions that would otherwise require a temporary variable — `dp[i] = (take) ? dp[i-1] + w : dp[i-1];`, `ans = (x < 0) ? -x : x;` — but it has two real pitfalls.

**Pitfall 1: parentheses around `?:` when streaming.** The precedence of `<<` is *higher* than `?:`, so

```cpp
cout << a % 2 == 0 ? "Even" : "Odd";   // WRONG
```

is parsed as `(cout << (a % 2 == 0)) ? "Even" : "Odd"`. The first part writes a `bool` to `cout` (printing `0` or `1`) and evaluates to the stream, which is truthy in most contexts — you get nonsense output that looks like a number. Correct:

```cpp
cout << (a % 2 == 0 ? "Even" : "Odd") << "\n";
```

**Pitfall 2: hidden type conversions.** The two branches of `?:` are promoted to a **common type**, which is sometimes wider than expected:

```cpp
long long x = (flag ? 1 : 0) * n;   // int result — can overflow before assignment
long long y = (flag ? 1LL : 0) * n; // long long — correct
```

The `1LL` is not decoration; it makes the ternary return `long long`. This bites most often in `dp[...] = (cond) ? 1 : MOD;`-style lines where `MOD` is an `int` — the `long long` assignment does not rescue the overflow that already happened on the right side.

**Readability rule.** One level of `?:` is fine. Two is hostile. Three is a bug waiting to happen — rewrite as explicit `if-else` and move on.

### `switch` — matching against constants

`switch` compares an integral expression against a list of compile-time constants. Because the values are known at compile time, the compiler can emit a **jump table** — \(O(1)\) regardless of how many `case` labels there are, versus the \(O(k)\) of an `if-else` chain with \(k\) branches.

```cpp
int op; cin >> op;
switch (op) {
    case 1: cout << "Addition\n";       break;
    case 2: cout << "Subtraction\n";    break;
    case 3: cout << "Multiplication\n"; break;
    default: cout << "Invalid\n";       break;
}
```

In competitive programming, `switch` shows up most often when parsing structured input: operations in a command stream (`'L'`, `'R'`, `'U'`, `'D'` for grid movement), direction codes, or query types in problems with mixed updates and reads. It is also common on `enum` values that represent a small set of states.

**Pitfall 1: missing `break` → fall-through.** Without `break`, execution continues into the next `case`:

```cpp
switch (x) {
    case 1: do_one();
    case 2: do_two();   // runs for x == 1 as well!
}
```

Occasionally fall-through is intentional — for instance, grouping several cases under one handler:

```cpp
case 'A': case 'E': case 'I': case 'O': case 'U':
    cout << "vowel\n";
    break;
```

In C++17 you can document intentional fall-through with `[[fallthrough]];` to silence compiler warnings. For everything else, add the `break`.

**Pitfall 2: declaring variables inside a `case` without braces.** `case` labels do not introduce a new scope:

```cpp
switch (x) {
    case 1:
        int y = 5;   // error: declaration crosses case label
        break;
}
```

Wrap the body in braces — `case 1: { int y = 5; ... break; }` — and the error disappears.

**When to prefer `if-else`.** For two or three non-contiguous values, `if-else` is at least as fast and far clearer. `switch` pays off when cases are dense (`case 0..N`) or when matching an `enum`, where the compiler can warn about missing cases (`-Wswitch`).

## Loops

Loops are the heart of every algorithm. The three loop forms in C++ — `for`, `while`, and `do-while` — differ in *how the termination condition is expressed*, not in what they can compute. Choosing the wrong one rarely breaks your code, but it consistently makes it harder to reason about. Under contest pressure, that difficulty is where bugs live.

### `for` — when you know how many iterations

Use `for` when the iteration count is fixed or index-driven. Nearly every array and matrix traversal in competitive programming is a `for` loop, and so are most DP transitions (`for (int i = 1; i <= n; ++i) for (int j = 0; j <= W; ++j) ...`).

```cpp
for (int i = 0; i < n; ++i) {
    // body
}
```

The three parts of the header are **initialization** (once), **condition** (before each iteration), and **update** (after each iteration). The subtlety that matters: `continue` in a `for` loop **runs the update clause** before the next condition check, unlike in `while` and `do-while`. This is the reason `for` is safer with `continue`, and why the common bug "infinite loop from `continue` in `while`" cannot happen in a `for`.

**`++i` vs `i++` — the myth.** You will read in many tutorials that `++i` is faster than `i++`. **For `int`, this is false.** With `-O2`, GCC and Clang emit identical assembly for both — the optimizer eliminates the temporary. The distinction matters only for **iterator classes**, where `i++` must construct a copy of the old iterator. In competitive programming you almost never iterate by raw iterator; use whichever form you prefer. Do not waste mental energy micro-optimizing the wrong thing.

**Scope of the loop variable.** The counter `int i` declared in the header is scoped to the loop. This is usually what you want — but it means this fails:

```cpp
for (int i = 0; i < n; ++i) { /* ... */ }
cout << i;   // error: i not declared
```

Declare the counter before the loop if you need it after.

**The unsigned-counter infinite loop.** This is one of the classic CP bugs:

```cpp
for (unsigned i = n - 1; i >= 0; --i) {   // INFINITE if n == 0 or after i == 0
    // when i == 0, i-- wraps to UINT_MAX, which is >= 0
}
```

Two safe rewrites:

```cpp
for (int i = (int)n - 1; i >= 0; --i) { /* ... */ }   // signed — exits at -1
for (int i = 0; i < (int)n; ++i)       { /* ... */ }   // forward direction
```

The rule: **use `int` (or `long long`) for loop counters in competitive programming**. Reserve `unsigned` for hashing and bit manipulation. The only exception is a range-based loop over `.size()`, where `size_t` is the natural type — and even then, cast when you need to iterate backwards.

**The signed/unsigned comparison trap.** `v.size()` returns `size_t`, which is **unsigned**. Comparing an `int` counter to it silently converts the counter to unsigned:

```cpp
for (int i = 0; i < v.size(); ++i) { /* safe as long as i >= 0 always */ }
```

This is safe *only* because the loop starts at 0. If `i` ever goes negative, it wraps to a huge unsigned value and the condition becomes always true. The related expression `v.size() - 1` is a live grenade — on an empty `v`, it wraps to `SIZE_MAX`. Two robust idioms:

```cpp
for (int i = 0; i < (int)v.size(); ++i)    { /* ... */ }   // explicit cast, clearly signed
for (size_t i = 0; i < v.size(); ++i)      { /* ... */ }   // fully unsigned domain
```

Both are fine. Pick one and use it consistently.

**Overflow in the condition.** `for (int i = 0; i <= n; ++i)` with `n == INT_MAX` is **undefined behavior** — when `i` reaches `INT_MAX`, `++i` overflows a signed `int`, and with `-O2` the compiler is allowed to assume that never happens. The loop may terminate normally, may run forever, or may do something stranger. For `n` approaching `INT_MAX`, use `long long` and a strict comparison.

### Range-based `for` — when iterating a container

C++11 introduced range-based `for`, which iterates the elements of any container directly:

```cpp
vector<int> v = {1, 2, 3, 4, 5};
for (int x : v)        cout << x << " ";   // copies each element
for (int& x : v)       x *= 2;             // modifies v
for (const int& x : v) cout << x << " ";   // reads without copying
```

In competitive programming, this is the cleanest way to iterate over a `vector`, `set`, `map` (where `x` is a `pair<const K, V>`), a `string`, or the adjacency list of a graph:

```cpp
for (int v : adj[u]) {          // BFS/DFS neighbor iteration
    if (!visited[v]) { /* ... */ }
}
```

The mistake to avoid is **choosing the wrong reference qualifier**. This is the most common range-`for` bug:

```cpp
for (int x : v) x *= 2;   // modifies a COPY — v is unchanged
for (int& x : v) x *= 2;  // modifies v
```

Use `int&` (or `auto&`) when you mean to modify. Use `const int&` (or `const auto&`) when you read a **non-trivial type** — a `string`, a `vector`, a large struct — because the default `for (string s : vs)` copies every string in the container. The performance difference in a hot loop is enormous.

**Iterator invalidation.** Do not modify the container's *structure* inside a range-based `for`. `push_back` may reallocate the underlying buffer, invalidating the implicit iterator; `erase` invalidates it outright:

```cpp
for (int x : v) {
    if (x < 0) v.push_back(-x);   // UNDEFINED BEHAVIOR
}
```

If you need to modify the container during iteration, use an explicit index (`for (int i = 0; i < v.size(); ++i)`) or collect the changes first and apply them after.

**`vector<bool>` caveat.** `vector<bool>` is a bit-packed specialization — its elements are proxies, not real `bool` objects. As a result, `for (bool& b : vb)` **does not compile**, and `for (bool b : vb)` copies a proxy that may behave unexpectedly. Use `vector<char>` when you need a boolean array with normal semantics; use `bitset` when you actually want the bit packing.

### `while` — when the count is unknown

Use `while` when the loop terminates based on a **runtime condition**, not a precomputed count. Two extremely common CP idioms:

**Reading input until EOF** (unknown number of test cases):

```cpp
int x;
while (cin >> x) {
    // process x
}
```

**Search until found:**

```cpp
int pos = -1;
int i = 0;
while (i < n && a[i] != target) ++i;
if (i < n) pos = i;
```

`while` also appears in **convergence loops** — fixed-point iterations, binary search, and numerical methods where the termination condition is "the update is small enough":

```cpp
double lo = 0, hi = 1e9;
for (int iter = 0; iter < 100; ++iter) {     // binary search on doubles
    double mid = (lo + hi) / 2;
    if (ok(mid)) lo = mid; else hi = mid;
}
```

(Note: in that snippet we use `for` with a **fixed** iteration count, which is the standard CP technique for binary search on `double` — floating-point `while (hi - lo > 1e-9)` can loop forever on hard inputs.)

**Pitfall 1: forgetting to advance.** A `while` loop where the condition variable is never modified runs forever. `-Wall` does not catch this; only reading the code catches it. When you write a `while`, scan the body first and confirm: *does something here make the condition eventually false?*

**Pitfall 2: `continue` without advancing.**

```cpp
int i = 0;
while (i < n) {
    if (a[i] < 0) continue;   // BUG: i never advances — infinite loop
    cout << a[i++] << "\n";
}
```

The equivalent `for` version does not have this bug because `continue` still runs `++i`. If you must `continue` in a `while`, advance the variable explicitly before the `continue`.

**Pitfall 3: `while (cin >> x)` is false on *format error*, not just EOF.** If input contains a non-numeric token where an `int` is expected, `cin` enters a fail state and the loop exits silently — possibly in the middle of the input, not at the end. If the problem guarantees well-formed input, this is fine. Otherwise, distinguish `cin.eof()` from `cin.fail()`.

### `do-while` — at least once

The body executes first; the condition is checked afterwards. In competitive programming, `do-while` is **rare** — the "read at least one value, then repeat while not sentinel" pattern it expresses is usually clearer as a `while` with an explicit first read:

```cpp
// do-while style:
int x;
do {
    cin >> x;
    // ...
} while (x != 0);

// equivalent, and usually clearer:
int x; cin >> x;
while (x != 0) {
    // ...
    cin >> x;
}
```

The one place `do-while` has a natural home is **interactive problems** with a mandatory first query, or **menu-style input** that always presents at least one option. For standard input-processing, prefer the `while` form.

**Pitfall: `continue` in `do-while` jumps to the condition, not the body start.** This asymmetry — `for` runs the update, `while` re-checks, `do-while` re-checks — is a genuine source of bugs when you convert between loop forms. If you convert a `for` to a `do-while`, re-examine every `continue`.

## Loop Control: `break` and `continue`

**`break` exits the innermost loop.** In a single loop, it is a clean early exit:

```cpp
for (int i = 0; i < n; ++i) {
    if (a[i] == target) {
        cout << i << "\n";
        break;
    }
}
```

In **nested loops**, `break` exits only the innermost one. If you need to abandon both loops at once, three idioms:

```cpp
// 1. Flag in the condition
bool found = false;
for (int i = 0; i < n && !found; ++i)
    for (int j = 0; j < m; ++j)
        if (a[i][j] == target) { found = true; break; }

// 2. goto — cleanest for this narrow case
for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
        if (a[i][j] == target) goto done;
done:

// 3. Extract to a function and return
bool search(...) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (a[i][j] == target) return true;
    return false;
}
```

In competitive programming, the **flag in the condition** is the most idiomatic — it keeps everything local and makes the exit condition visible at the top of the loop. The `goto` form is legitimate for deeply nested searches; the `return` form is the cleanest when the search is already inside a helper function.

**`break` inside a `switch` inside a loop** exits the `switch`, not the loop. To exit the loop from inside a `switch`, use `return` or `goto`:

```cpp
for (int i = 0; i < n; ++i) {
    switch (a[i]) {
        case 0: break;      // exits the switch, continues the loop
        case 1: goto end;   // exits the loop (and the switch)
    }
}
end:
```

**`continue` skips to the next iteration.** In CP it is used mostly for filtering:

```cpp
for (int i = 0; i < n; ++i) {
    if (a[i] < 0) continue;   // skip negative values
    cout << a[i] << "\n";
}
```

And for skipping the transition in a DP where the current state is unreachable:

```cpp
for (int i = 0; i < n; ++i) {
    if (dp[i] == INF) continue;      // state never reached — skip
    dp[i + 1] = min(dp[i + 1], dp[i] + cost);
}
```

Both uses are fine. The only pattern to avoid is `continue` in a `while` loop without advancing the loop variable (covered above).

## Patterns You Will Reuse Constantly

The following idioms appear so often in competitive programming that they are worth memorizing.

**Read until EOF (unknown number of test cases):**

```cpp
int x;
while (cin >> x) { /* process */ }
```

**1-based indexing** — many problems are stated with indices \(1 \le i \le n\). Pick a convention and stick to it:

```cpp
vector<int> v(n + 1);
for (int i = 1; i <= n; ++i) cin >> v[i];
```

Mixing 1-based and 0-based indexing in the same file is one of the top three sources of off-by-one bugs. If the problem uses 1-based, convert *immediately* at input; if it uses 0-based, keep it 0-based everywhere. Do not switch conventions halfway through.

**Early-exit search** — the `&& !found` form is clearer than `if (found) break`:

```cpp
bool found = false;
for (int i = 0; i < n && !found; ++i)
    if (a[i] == x) found = true;
```

**Reading a grid** — `cin >> s` reads one whitespace-delimited token, so multi-line grids parse naturally:

```cpp
int n, m; cin >> n >> m;
vector<string> grid(n);
for (int i = 0; i < n; ++i) cin >> grid[i];
```

(If you use `getline` here, remember to flush the newline left behind by `cin >> n >> m`; see the I/O article.)

**Iterating neighbors in a graph:**

```cpp
for (int v : adj[u]) {          // range-based — no iterator hassle
    if (!visited[v]) { /* ... */ }
}
```

## Performance Considerations

Loops are where runtime is measured. A rough throughput table for typical contest hardware with `-O2`:

| Loop body | Approximate operations per second |
|---|---|
| Empty (`for (int i = 0; i < n; ++i) {}`) | \(\sim 10^9\) |
| Simple integer arithmetic | \(\sim 10^8 - 10^9\) |
| Contiguous array access | \(\sim 10^8\) |
| `std::map` / `std::set` operation | \(\sim 10^6 - 10^7\) |
| `std::unordered_map` operation | \(\sim 10^6 - 10^7\) |
| Random memory access (cache miss) | \(\sim 10^7\) |

These numbers are approximate but useful as a sanity check: if your solution does \(10^{10}\) elementary operations, it will TLE no matter how clean your loop is. If it does \(10^7\) `map` operations, that is already ~1 second.

**What `-O2` gives you automatically:**

- **Loop unrolling** for simple loops with a fixed small body.
- **Vectorization** (SIMD) of element-wise operations on contiguous arrays — `for (int i = 0; i < n; ++i) c[i] = a[i] + b[i];` compiles to SSE/AVX.
- **Hoisting** of loop-invariant expressions.
- **Dead-loop elimination** for loops with no observable side effects.

**What `-O2` cannot fix:**

- **The algorithm.** An \(O(n^2)\) solution with \(n = 10^5\) is \(10^{10}\) operations; no micro-optimization saves it. Get the complexity right first, *then* worry about the constants.
- **Cache-unfriendly memory access.** Accessing a row-major 2D array column-by-column is \(5\)–\(10\times\) slower than row-by-row because every access misses the cache:

```cpp
// Slow: column-major traversal of a row-major array
for (int j = 0; j < m; ++j)
    for (int i = 0; i < n; ++i)
        sum += a[i][j];

// Fast: row-major traversal (matches memory layout)
for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
        sum += a[i][j];
```

- **Unnecessary allocations.** `vector<int> v(n)` inside a hot loop is slow; declare it once outside and reuse. The same applies to `string`, `map`, and any container that allocates.

**Guidance for contests.** For \(n \ge 10^5\), aim for \(O(n \log n)\) or \(O(n)\). For \(n \ge 10^7\), even \(O(n)\) must be tight — avoid `map`, avoid `string` concatenation in loops, prefer arrays over containers. For \(n \le 10^3\), an \(O(n^2)\) approach is fine; do not over-engineer.

## Common Pitfalls

A checklist to run whenever your solution WAs or TLEs and you suspect control flow:

1. **`if (x = 5)` instead of `if (x == 5)`** — compile with `-Wall -Wextra`; GCC catches this.
2. **Dangling `else`** — use braces always.
3. **`cout << cond ? a : b`** — wrap the ternary in parentheses when streaming.
4. **Missing `break` in `switch`** — fall-through.
5. **Variable declaration in a `case` without braces** — compile error; wrap in `{ ... }`.
6. **`for (unsigned i = n - 1; i >= 0; --i)`** — infinite loop; use `int` counters.
7. **`v.size() - 1` on an empty vector** — wraps to `SIZE_MAX`.
8. **`v.size()` compared to `int`** — signed/unsigned conversion; safe only if the counter is always \(\ge 0\).
9. **`for (int x : v) x *= 2`** — modifies a copy; use `int&`.
10. **`for (string s : vs)`** — copies every string; use `const string&`.
11. **Modifying a container inside a range-`for`** — iterator invalidation; use an explicit index.
12. **`for (bool& b : vb)`** — `vector<bool>` is not a normal container; use `vector<char>`.
13. **`continue` in `while` without advancing** — infinite loop.
14. **`continue` in `do-while`** — jumps to the condition; re-examine conversion from `for`.
15. **`break` in nested loops** — exits only the innermost; use a flag, `goto`, or `return`.
16. **`break` in `switch` inside a loop** — exits the `switch`, not the loop.
17. **`while (cin >> x)` ends on format error, not just EOF** — distinguish `cin.eof()` from `cin.fail()` if input may be malformed.
18. **`i <= n` vs `i < n`** — the single most common source of off-by-one WA.
19. **Mixing 1-based and 0-based indices in one file** — pick a convention and stick to it.
20. **`for (int i = 0; i <= INT_MAX; ++i)`** — signed overflow is UB under `-O2`.

## Key Takeaways

- Always compile with `-Wall -Wextra`. Most control-flow bugs are caught by warnings before they reach the judge.
- Always use braces around `if`/`else` bodies. The dangling-else class of bugs disappears at zero cost.
- `++i` and `i++` compile to identical machine code for `int` under `-O2`. Don't optimize what doesn't matter.
- Use signed `int` (or `long long`) for loop counters. Unsigned counters invite wrap-around infinite loops.
- When iterating containers, `const auto&` avoids copies for non-trivial types; `auto&` modifies in place.
- `break` exits only the innermost loop; use a flag, `goto`, or `return` to abandon nested loops.
- `continue` in a `while` loop requires the loop variable to advance on the `continue` path; in `for`, it does not.
- The **algorithmic complexity** dominates runtime. Get \(O(n \log n)\) right before worrying about loop constants.

## Practice Problems

- [Codeforces 1A — Theatre Square](https://codeforces.com/problemset/problem/1/A) — off-by-one in ceiling division; watch for `int` overflow when multiplying the two dimensions.
- [Codeforces 158B — Taxi](https://codeforces.com/problemset/problem/158/B) — conditionals on group sizes; a good exercise in case analysis without branching everywhere.
- [CSES — Number Spiral](https://cses.fi/problemset/task/1071) — nested conditionals on the parity of `x` and `y`; the canonical "if-else on structure" problem.
- [CSES — Two Sets](https://cses.fi/problemset/task/1092) — loops with `break`/`continue`, and a parity check at the top; sum of \(10^5\) elements approaches `int` limits, so use `long long`.
- [Codeforces 546A — Soldier and Bananas](https://codeforces.com/problemset/problem/546/A) — simple loop, arithmetic sequence; teaches you where overflow hides in "obviously small" numbers.

## References

- [cppreference — Statements (`if`, `switch`, `for`, `while`)](https://en.cppreference.com/w/cpp/language/statements)
- [GCC — Warning options (`-Wall`, `-Wextra`, `-Wimplicit-fallthrough`)](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html)
- [cppreference — Range-based `for` loop](https://en.cppreference.com/w/cpp/language/range-for)

## Next Topic

[Arrays and Vectors](arrays-and-vectors.md)