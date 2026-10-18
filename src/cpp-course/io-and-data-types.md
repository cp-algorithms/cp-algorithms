---
title: I/O and Data Types
tags:
  - Course
---

# Input/Output and Data Types

## Prerequisites

- [Introduction to C++](intro-to-cpp.md) — compilation, the CP template, `-O2`, and why `"\n"` beats `endl`.
- Comfort with the terminal to compile and run programs.

This article is the second in the course. It assumes the standard CP template from the previous article:

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

## Fast I/O for Competitive Programming

The default `cin`/`cout` is **synchronized with C's `stdio`** (`scanf`/`printf`) so that both families can be freely mixed. This synchronization runs on every I/O operation and is a measurable bottleneck when input or output is large (commonly \(10^5\)–\(10^6\) numbers in CP).

Two calls disable it:

```cpp
ios_base::sync_with_stdio(false);
cin.tie(nullptr);
```

### What each one does

- **`sync_with_stdio(false)`** — Removes the synchronization layer. After this, `cin` reads directly from the C++ stream buffer without checking that `stdio` is consistent, making reads significantly faster (often 3–5×).
- **`cin.tie(nullptr)`** — By default `cin` is *tied* to `cout`, meaning `cout` is flushed before every `cin` read. On a program that interleaves reads and writes, this causes gratuitous flushes. Untying removes them.

### The critical pitfall: do not mix families

After `sync_with_stdio(false)`:

```cpp
ios_base::sync_with_stdio(false);
cout << "hello\n";
printf("world\n");   // UNDEFINED BEHAVIOR
```

Output order between `cout` and `printf` is no longer guaranteed. If you disable sync, **use only `cin`/`cout`**, or **only `scanf`/`printf`**, for the rest of the program.

Similarly, `cin.tie(nullptr)` means you must call `cout.flush()` explicitly if you need flushing — **critical for interactive problems**. Interactive problems require flushing after each query:

```cpp
cout << "? " << x << "\n";
cout.flush();                    // mandatory in interactive mode
int response; cin >> response;
```

### `endl` vs `"\n"` vs `'\n'`

| Expression | Type written | Flush |
|---|---|---|
| `endl` | `char` + `flush()` | **Yes** — avoid |
| `"\n"` | `const char*` (calls `strlen`) | No |
| `'\n'` | `char` | No — marginal speedup |

On output-heavy problems (e.g., \(10^6\) lines), `endl` can cause **5–10× slowdown** and guaranteed TLE. Use `'\n'`. Use `endl` only when you *intend* to flush (i.e., interactive problems or before crashing).

### When `cin` with fast I/O is still not enough

For extremely tight limits (e.g., \(10^7\) integers), a **custom `fread`-based reader** is 2–4× faster than `cin` even with sync disabled. It's rarely needed on modern judges but worth knowing:

```cpp
namespace io {
    constexpr int BUF = 1 << 16;
    static char buf[BUF];
    static int pos = 0, len = 0;
    inline char rc() {
        if (pos == len) { len = fread(buf, 1, BUF, stdin); pos = 0; if (len <= 0) return 0; }
        return buf[pos++];
    }
    template<typename T> inline bool readInt(T &out) {
        char c; T sign = 1, num = 0;
        if (!(c = rc())) return false;
        while (c < '0' || c > '9') { if (c == '-') { sign = -1; c = rc(); break; } if (!(c = rc())) return false; }
        for (; c >= '0' && c <= '9'; c = rc()) num = num * 10 + (c - '0');
        out = sign * num;
        return true;
    }
}
```

> **Warning.** Mixing this with `cin`/`cout` is undefined behavior. Use it only in programs that read *exclusively* through `io::rc` and write through `printf` or a similar raw output.

## Reading Input

### How `cin >>` parses

`cin >> x` **skips leading whitespace** (spaces, tabs, newlines) and reads until the next whitespace. This means:

```cpp
int a, b; cin >> a >> b;
// input "   3\n\n    42   " works identically to "3 42"
```

- Multi-line input does **not** require any special handling — `cin >>` treats `\n` as whitespace.
- For strings, `cin >> s` reads up to the next whitespace. To read a whole line with spaces, use `getline`.

### Reading until EOF

A common judge format: read an unknown number of values until the end of the input.

```cpp
int x;
while (cin >> x) {
    // process x
}
```

`cin >> x` evaluates to the stream itself, which converts to `false` if the stream is in a fail state (EOF or a format error). Equivalent with `scanf`:

```cpp
while (scanf("%d", &x) == 1) { /* ... */ }
```

`scanf` returns the number of items successfully assigned, so `== 1` (or `!= EOF`) is the idiomatic check.

### Reading a whole line

```cpp
string s;
getline(cin, s);   // reads up to and including '\n', discards the '\n'
```

**Classic pitfall.** `cin >>` leaves the trailing newline in the buffer. A subsequent `getline` reads an *empty* string and returns immediately:

```cpp
int n; cin >> n;
string s;
getline(cin, s);       // BUG: reads empty string (the leftover '\n')
```

Fixes:

```cpp
cin.ignore(numeric_limits<streamsize>::max(), '\n');
getline(cin, s);
```

or, more idiomatically:

```cpp
cin >> ws;             // skip all leading whitespace, including '\n'
getline(cin, s);
```

### Reading characters

```cpp
char c;
c = getchar();         // fast; from <cstdio>
c = cin.get();         // slow; from <iostream>
```

For single-character input in tight loops (grid problems), `getchar()` (or `getchar_unlocked()` on GCC) is the fastest option.

## Writing Output

### Chaining

```cpp
cout << "Sum: " << a + b << "\n";
```

`<<` returns the stream, so it chains naturally. `'\n'` (a `char`) is marginally faster than `"\n"` (a C-string) because the `char` overload doesn't call `strlen`.

### Formatting floating point

By default, `cout` may print doubles in **scientific notation** (e.g., `1e+06`), which is a frequent WA cause. Force fixed-point with `fixed` and set precision:

```cpp
double ans = 0.1 + 0.2;
cout << fixed << setprecision(10) << ans << "\n";  // 0.3000000000
```

`fixed` and `setprecision` are **sticky** — they affect all subsequent writes to `cout` until reset (`cout << defaultfloat;`).

Alternatively, use `printf`:

```cpp
printf("%.10f\n", ans);
```

But only if you *never* called `sync_with_stdio(false)` **and** use `printf` for all output.

### Large integers stored in `double`

```cpp
double x = 123456789012345;
cout << x << "\n";   // 1.23456789012345e+14 — scientific notation!
```

This is another reason to use `fixed`. But note: `double` can exactly represent integers only up to \(2^{53} \approx 9 \cdot 10^{15}\). Beyond that, precision is silently lost. **Never use `double` to store large integer counts.**

## Data Types

Choosing the right type is the single most common source of **silent wrong answers**. Overflow, truncation, and sign errors rarely crash — they just produce plausible-looking wrong values.

### Integer types — what's guaranteed vs what's typical

The C++ standard only guarantees *minimum* ranges. On all modern judges (`g++` on Linux x86-64):

| Type | Guaranteed minimum | On judges | Range on judges |
|---|---|---|---|
| `short` | 16 bits | 16 bits | \([-2^{15}, 2^{15}-1]\) |
| `int` | 16 bits | **32 bits** | \([-2^{31}, 2^{31}-1] \approx [-2.1\cdot10^9, 2.1\cdot10^9]\) |
| `long` | 32 bits | **64 bits on Linux**, 32 on Windows | — (avoid) |
| `long long` | 64 bits | 64 bits | \([-2^{63}, 2^{63}-1] \approx [-9.2\cdot10^{18}, 9.2\cdot10^{18}]\) |
| `size_t` | — | 64 bits unsigned | \([0, 2^{64}-1]\) |

> **Portability pitfall.** `long` is 32-bit on Windows and 64-bit on Linux. Judges run Linux, so `long` behaves like `long long` *there*, but a solution developed on Windows with `long` will behave differently. **Never use `long` in competitive code** — use `int` or `long long`.

### Fixed-width types

For maximum portability and explicit width, use `<cstdint>`:

```cpp
int32_t x;       // always 32-bit signed
int64_t y;       // always 64-bit signed
uint32_t z;      // always 32-bit unsigned
```

CP code often prefers `using ll = long long;` for brevity.

### Signed overflow is undefined behavior

```cpp
int a = 1'000'000'000;
int b = a + a;    // UB — signed overflow
```

With `-O2`, the compiler is allowed to **assume this never happens**, and may produce code that misbehaves in ways you cannot debug from the source:

```cpp
if (a + b < 0) { /* compiler may eliminate this branch entirely */ }
```

There are two correct options:

1. **Use `long long`** whenever a sum or product of `int`s can exceed \(2.1 \cdot 10^9\).
2. **Use `unsigned`** if you accept the modular wrap-around semantics (see below) — rarely the right choice in CP.

```cpp
int a = 1'000'000'000, b = 1'000'000'000;
long long c = (long long)a * b;    // correct; promotes before multiply
long long d = 1LL * a * b;         // idiomatic short form
```

### Unsigned types — wrap-around and mixed comparison

`unsigned` arithmetic wraps modulo \(2^N\) — no UB, but often not what you want:

```cpp
unsigned int x = 0;
cout << (x - 1);    // 4294967295, not -1
```

Worse, **comparisons between signed and unsigned convert the signed operand to unsigned**:

```cpp
int n = -1;
vector<int> v = {1, 2, 3};
if (n < v.size()) { /* FALSE! n is converted to a huge unsigned value */ }
```

This is the source of countless real bugs. Practical rule: **avoid `unsigned` in CP**, except for bitmask tricks and hash computations where wrap-around is desired.

### `size_t` — the `.size()` return type

All STL `.size()` methods return `size_t` (unsigned). Direct comparisons with `int` are the canonical trigger of the pitfall above. Two safe idioms:

```cpp
vector<int> v;
for (int i = 0; i < (int)v.size(); i++) { ... }       // explicit cast
for (size_t i = 0; i < v.size(); i++) { ... }         // use size_t throughout
```

And never write:

```cpp
for (int i = 0; i <= (int)v.size() - 1; i++) { ... }  // BUG: infinite loop if v is empty
```

because `(int)0 - 1 = -1`, then `-1 <= huge` is false only by luck; with `size_t`, `0 - 1 = SIZE_MAX` → infinite loop.

### `__int128` — beyond 64 bits

GCC provides a 128-bit integer for values exceeding `long long` (e.g., multiplying two \(10^{18}\) values, or RSA-like problems):

```cpp
__int128 x = (__int128)a * b;   // a, b are long long
```

There is **no `cin >>` overload** for `__int128`. Read and print manually:

```cpp
// read
long long hi, lo;   // hi * 2^64 + lo ... custom parsing
// print
void print128(__int128 x) {
    if (x == 0) { cout << '0'; return; }
    if (x < 0) { cout << '-'; x = -x; }
    string s;
    while (x > 0) { s += char('0' + x % 10); x /= 10; }
    reverse(s.begin(), s.end());
    cout << s;
}
```

Non-portable (GCC/Clang only; not on MSVC), but every judge uses GCC.

### Floating point types

| Type | Bits | Decimal precision | Use in CP |
|---|---|---|---|
| `float` | 32 | ~6–7 digits | Almost never — insufficient |
| `double` | 64 | ~15–17 digits | Standard for geometry, probability, real answers |
| `long double` | 80–128 (platform) | ~18–21 digits | High-precision geometry, cumulative sums |

> **Pitfall.** `double` cannot represent most decimal fractions exactly — `0.1 + 0.2 != 0.3`. **Never compare doubles with `==`.** Use an epsilon:

```cpp
const double EPS = 1e-9;
if (abs(a - b) < EPS) { /* a ≈ b */ }
```

For values spanning many orders of magnitude, use a *relative* tolerance:

```cpp
if (abs(a - b) < EPS * max(1.0, max(abs(a), abs(b)))) { /* a ≈ b */ }
```

> **Pitfall.** In geometry, summing \(10^6\) doubles each ~\(10^{-3}\) can lose ~3 decimal digits of precision to accumulated rounding. If the problem demands high precision, use `long double`. If it's borderline, Kahan summation can help, but the correct fix is usually to restructure the computation.

### `char` — signedness is implementation-defined

Whether plain `char` is signed or unsigned is **implementation-defined**. On x86-64 Linux judges, `char` is *signed*, meaning `char c = 200;` actually stores `-56`. This matters when:

- Passing `char` to `<cctype>` functions:

```cpp
char c = ...;
if (isalpha(c)) { ... }               // UB if c is negative!
if (isalpha((unsigned char)c)) { ... } // correct
```

- Indexing with character values as integers: `int idx = c - 'a';` is fine because ASCII ranges are contiguous, but `c - '0'` combined with `isdigit` has the same signedness trap.

### `bool`

`bool` is 1 byte on virtually all platforms. `vector<bool>` is a **specialization** packed into bits — its elements are not real `bool&` references, `&v[i]` does not compile, and concurrent modification of adjacent elements is data-race-prone. Use `vector<char>` or `bitset` when you need an array of booleans with normal semantics.

## Type Conversions

### Implicit conversions

C++ converts types silently. Most are harmless, but **narrowing** (large → small) truncates:

```cpp
long long x = 3'000'000'000;
int y = x;              // implementation-defined (wraps to a negative number on GCC)
```

Curly-brace initialization rejects narrowing at compile time:

```cpp
int a{1'000'000'000};   // OK
int b{3'000'000'000};   // compile error: narrowing — good, catches the bug early
```

Use `{}` initialization for constants; it turns silent bugs into compile errors.

### Multiplication overflow before casting

```cpp
int a = 1'000'000'000, b = 1'000'000'000;
long long c = (long long)a * b;   // CORRECT: cast before multiply
long long d = (long long)(a * b); // WRONG: overflow happens as int first
```

The rule: **cast one operand *before* the operation, not the result**.

### `static_cast` vs C-style cast

Prefer `static_cast<T>(x)` in modern code:

```cpp
int a = static_cast<int>(some_double);
```

C-style `(int)` still works but is more permissive and harder to search for. In competitive code, either is acceptable; in learning code, use `static_cast`.

## Constants

Common idioms for the "infinity" value used in shortest paths, DP initialization, etc.:

```cpp
const int INF      = 1'000'000'000;               // fits in int
const long long LINF = 1'000'000'000'000'000'000LL; // fits in ll
const int MOD      = 1'000'000'007;               // prime, common in problems
```

> **Pitfall.** Adding two `INF`s overflows an `int`: `INF + INF = 2e9` fits, but `INF + INF + INF` overflows. Common trick: initialize with `INF / 2` or `INF / 3` so that `2 * INF` and `INF + x` never overflow. Alternatively, use `LINF` for all DP values and let the compiler's 64-bit arithmetic absorb the sum.

For compile-time constants, prefer `constexpr` (C++11+) over `const`:

```cpp
constexpr int MAX_N = 200'005;
constexpr int MOD   = 1'000'000'007;
```

`constexpr` guarantees the value is computed at compile time. `const` only guarantees "not modified".

## Common Pitfalls

A checklist to review whenever a solution gets WA or TLE:

1. **`endl` instead of `'\n'`** — the #1 cause of TLE on output-heavy problems.
2. **`ios_base::sync_with_stdio(false)` without `cin.tie(nullptr)`** — half the speedup lost.
3. **Mixing `printf`/`scanf` with `cin`/`cout` after disabling sync** — undefined behavior, garbled output.
4. **`int` overflow** — sums of \(10^9 + 10^9\), products of \(10^5 \cdot 10^5\), factorials above \(12!\), etc. Use `long long`.
5. **`(long long)(a * b)` instead of `(long long)a * b`** — the multiplication overflows before the cast.
6. **`unsigned` comparison** — `int n = -1; n < v.size()` is false.
7. **`v.size() - 1` on an empty vector** — wraps to `SIZE_MAX`.
8. **`getline` after `cin >>`** — reads the leftover newline; use `cin >> ws`.
9. **Double `==` comparison** — always use epsilon.
10. **Printing doubles without `fixed`** — scientific notation causes WA.
11. **Storing `long long` counts in `double`** — silent precision loss above \(2^{53}\).
12. **`isalpha(c)` with negative `char`** — cast to `unsigned char` first.
13. **`vector<bool>` misuse** — not a normal container; `&v[i]` fails.
14. **`long` on Windows vs Linux** — use `long long` for 64-bit values.

## Key Takeaways

- Always include `ios_base::sync_with_stdio(false); cin.tie(nullptr);` **and** use `'\n'`, never `endl`.
- After disabling sync, use **either** `cin`/`cout` **or** `scanf`/`printf` — never both.
- Use `long long` for any value that can exceed \(2.1 \cdot 10^9\); cast **before** multiplying.
- Never compare doubles with `==`; use `abs(a - b) < EPS`.
- Never use `unsigned` or `long` in competitive code; use `int`, `long long`, and `size_t` (only for `.size()`).
- Use `constexpr` for constants; `INF = 1e9`, `LINF = 1e18`, and be careful summing them.
- Watch for `getline` after `cin >>`; use `cin >> ws` to skip leftover newlines.
- Format doubles with `fixed << setprecision(10)` or `printf("%.10f")`.

## Practice Problems

- [CSES — Weird Algorithm](https://cses.fi/problemset/task/1068) — basic loop + output speed (try it with `endl` vs `'\n'` and compare).
- [CSES — Missing Number](https://cses.fi/problemset/task/1622) — sum of \(10^6\) integers near \(10^6\); sum fits in `long long` but is close enough to test your instinct.
- [CSES — Repetitions](https://cses.fi/problemset/task/1069) — string reading, `char` handling.
- [Codeforces 158A — Next Round](https://codeforces.com/problemset/problem/158/A) — basic input, 1-based indexing.
- [Codeforces 71A — Way Too Long Words](https://codeforces.com/problemset/problem/71/A) — string input, conditional output.

## References

- [cppreference — `std::ios_base::sync_with_stdio`](https://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio)
- [cppreference — Fundamental types](https://en.cppreference.com/w/cpp/language/types)
- [cppreference — Floating-point environment](https://en.cppreference.com/w/cpp/numeric/fenv)
- [GCC — `__int128` and other extensions](https://gcc.gnu.org/onlinedocs/gcc/_005f_005fint128.html)

## Next Topic

[Conditionals and Loops](conditionals-and-loops.md)
