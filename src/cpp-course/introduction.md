---
title: Introduction to C++
tags:
  - Course
---

# Introduction to C++

## Prerequisites

Before starting this course, you should be comfortable with:

- Basic programming constructs (variables, loops, conditionals, functions) in *some* language.
- Using a terminal to compile and run programs.
- Solving (or at least reading) simple algorithmic problems on an online judge.

This course assumes you can already program and focuses on *competitive programming* with C++. If you have never written code before, start with a general programming tutorial.

## What is C++?

C++ is a general-purpose, compiled, statically-typed language created by Bjarne Stroustrup as an extension of C. It supports procedural, object-oriented, and generic paradigms, and is standardized by ISO. The standards relevant for competitive programming are **C++17** (widely supported) and **C++20** (supported on modern judges). Anything older than C++17 is best avoided today.

## Why C++ for Competitive Programming?

Competitive programming requires solving algorithmic problems under strict time and memory limits. C++ dominates for several reasons:

- **Execution speed.** As a compiled language, C++ produces highly optimized native code. In practice, equivalent \(O(n \log n)\) solutions in C++ often run **10–50× faster** than in Python, and 1.5–3× faster than in Java. On many problems with tight limits, C++ passes where Python is guaranteed to TLE.
- **Memory efficiency.** Fine-grained control over allocation and object layout. Problems routinely cap memory at 256 MB or 512 MB; STL containers have far smaller overhead than Python's.
- **Standard Template Library (STL).** Efficient containers (`vector`, `set`, `map`, `unordered_map`, `priority_queue`) and algorithms (`sort`, `lower_bound`, `next_permutation`, etc.) drastically reduce implementation time.
- **Universal judge support.** Every major judge (Codeforces, AtCoder, CSES, CodeChef, SPOJ, UVa, TopCoder) supports GCC with modern standards and `-O2`.
- **Low-level and high-level features.** Readable high-level code, with hand-optimization reserved for the critical 5%.

### Comparison with other languages

| Language | Speed vs C++ | STL equivalent | Role in CP |
|---|---|---|---|
| C++ | 1× (reference) | Rich (STL) | Dominant |
| Java | ~2–3× slower | `java.util.*` | Second most popular |
| Python | ~20–50× slower | Built-in, slow | Prototyping, easy problems |
| Rust | ~1–1.5× | Moderate | Growing, less common |

> **Rule of thumb.** If a problem expects an \(O(n \log n)\) C++ solution in 1 s at \(n = 2 \cdot 10^5\), an \(O(n \log n)\) Python solution will often take 5–10 s and TLE. Language choice matters.

## Setting Up a C++ Environment

The reference compiler is **GCC** (`g++`). Almost every judge uses it, so always test locally with `g++`. Clang works too but differs in warnings and in how it treats some undefined behavior.

### Recommended compiler flags

For **submission** (what judges effectively do):

```bash
g++ -std=c++17 -O2 -Wall -Wextra -o program program.cpp
```

For **debugging locally** (never submit these binaries):

```bash
g++ -std=c++17 -O2 -g -fsanitize=address,undefined -D_GLIBCXX_DEBUG -o program program.cpp
```

- `-std=c++17` — Enable C++17. Most judges support it; some support C++20. Don't rely on C++20 features unless the judge explicitly advertises them.
- `-O2` — Optimization. This approximates what judges use. **Always test with `-O2`**: undefined behavior (out-of-bounds stack access, signed overflow) can behave differently under optimization, and performance changes dramatically.
- `-Wall -Wextra` — Warnings. Take them seriously; they catch real bugs.
- `-g` — Debug symbols. Required for sanitizers to produce useful traces.
- `-fsanitize=address,undefined` — Runtime detection of memory errors and undefined behavior. ~2–10× slower; use only while debugging.
- `-D_GLIBCXX_DEBUG` — Turns some silent STL bugs (e.g., out-of-bounds `vector::operator[]`) into runtime errors. Also slow.

> **Pitfall.** Debug builds can hide or expose bugs that the judge build does not. Always time your solution with the exact submission flags.

### Which standard header to include?

Two viable styles:

1. **Explicit includes** — `#include <vector>`, `#include <iostream>`, … Portable, slower to write.
2. **`#include <bits/stdc++.h>`** — GCC-specific umbrella header that pulls in nearly the whole standard library. Ubiquitous in competitive programming and supported on virtually every judge. Use it for contests; avoid it in production code.

For the rest of this course we use `<bits/stdc++.h>` for brevity.

## The Competitive Programming Template

Almost every solution starts from a fixed template. Memorize it.

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi  = vector<int>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // solution goes here
    return 0;
}
```

Two lines are essential for I/O performance and are explained in the next article:

- `ios_base::sync_with_stdio(false);` — Unsynchronizes C and C++ I/O streams.
- `cin.tie(nullptr);` — Prevents `cin` from flushing `cout` before each read.

Do **not** mix C-style (`scanf`/`printf`) and C++-style (`cin`/`cout`) I/O after calling `sync_with_stdio(false)`; doing so is undefined behavior.

## Your First Program

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Welcome to the C++ course for Competitive Programming!\n";
    return 0;
}
```

### Explanation

1. `#include <iostream>` — Provides `cin` and `cout`. In real solutions we use `<bits/stdc++.h>` instead.
2. `using namespace std;` — Brings `std::` into scope. Convenient in CP; discouraged in large codebases because it pollutes the namespace. It is standard practice on judges.
3. `int main() { ... }` — Program entry point.
4. `cout << ... << "\n";` — Writes to standard output. Prefer `"\n"` over `endl`; see the pitfall section.
5. `return 0;` — Success exit code.

## Compiling and Running

Assuming the file is `program.cpp`:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -o program program.cpp
./program
```

## Common Pitfalls

These trip up beginners constantly. Each one is worth memorizing.

### 1. `endl` vs `"\n"`

`endl` inserts a newline **and flushes the stream**. Flushing on every line is catastrophic on output-heavy problems — a solution that would otherwise pass can TLE by a factor of 5–10×. **Always use `"\n"`.** `cout << '\n'` is even marginally faster than `"\n"` since it's a character, not a C-string.

### 2. Signed integer overflow is undefined behavior

```cpp
int a = 1'000'000'000, b = 1'000'000'000;
int c = a + b;   // UB; with -O2 the compiler may assume this never happens
```

Use `long long` (`ll`) when the product of two `int`s can exceed \(2^{31}-1 \approx 2.15 \cdot 10^9\), and cast at least one operand:

```cpp
ll c = 1LL * a * b;   // correct
```

For values beyond \(2^{63}-1\), use `__int128` (GCC-only) or big-integer emulation.

### 3. Mixing `cin`/`cout` with `scanf`/`printf`

After `ios_base::sync_with_stdio(false)`, using both families is undefined behavior. Pick one — either is fine as long as you're consistent.

### 4. Recursion depth

The default stack is typically **8 MB**. Recursive functions with deep recursion (e.g., DFS on a path of length \(10^6\)) overflow it and crash — often as a *stack overflow*, sometimes as a **wrong answer** under `-O2`. Remedies:

- Increase the stack in your shell: `ulimit -s unlimited` (local only).
- Allocate large arrays **globally** (static storage), not on the stack.
- Convert deep recursion to an explicit stack or iterative DP.

### 5. `vector::operator[]` does not bounds-check

`v[i]` with `i >= v.size()` is undefined behavior. Only use `v.at(i)` when you want a runtime error (e.g., during debugging). Similarly, `array[n]` on a fixed-size array is UB.

## Debugging Locally

Two habits that save enormous time:

### Print macro

```cpp
#define dbg(x) cerr << #x << " = " << (x) << '\n'
```

`cerr` is not tied to `cout`, so it won't interleave awkwardly, and you can disable it before submission with a single `#define`.

### Sanitizers and stress testing

Compile with `-fsanitize=address,undefined` to catch memory errors and UB during practice. Combine with **stress testing** (generate random small inputs, compare against a brute force) to catch logical bugs before the judge does. Stress testing is covered later in this course.

## Key Takeaways

- C++ is the dominant CP language thanks to speed and STL. Always compile with `-O2` when timing.
- Use `<bits/stdc++.h>` and the standard template.
- `"\n"` over `endl`; unbuffer `cin`/`cout`; never mix C and C++ I/O after `sync_with_stdio(false)`.
- Beware signed integer overflow, shallow stack depth, and `vector::operator[]` without bounds checks.
- Debug with sanitizers; submit with the judge's flags.

## Practice Problems

- [Codeforces 4A — Watermelon](https://codeforces.com/problemset/problem/4/A) — warm-up.
- [CSES — Weird Algorithm](https://cses.fi/problemset/task/1068) — loop + output speed.
- [CSES — Increasing Array](https://cses.fi/problemset/task/1094) — watch for overflow on large sums.

## References

- [ISO C++ Standard (C++17)](https://isocpp.org/std/the-standard)
- [GCC manual — Optimize options](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)
- [AddressSanitizer documentation](https://clang.llvm.org/docs/AddressSanitizer.html)

## Next Topic

[Input/Output and Data Types](io-and-data-types.md)

