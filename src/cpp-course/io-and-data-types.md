---
title: I/O and Data Types
tags:
  - Course
---

# Input/Output and Data Types

## Fast I/O for Competitive Programming

In C++, the default `cin`/`cout` is synchronized with C's `stdio.h` (`scanf`/`printf`) for compatibility. While this is safe for general use, it introduces overhead that can become a bottleneck when handling large amounts of input/output (common in contests and judges with $10^5$ lines).

To speed up I/O significantly, we disable this synchronization and untie `cin` from `cout`:

```cpp
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Your code here
    return 0;
}
```

### Explanation

- `ios_base::sync_with_stdio(false)`: Disables synchronization between C and C++ standard streams. This allows `cin`/`cout` to operate independently and much faster.
- `cin.tie(NULL)`: Unties `cin` from `cout`, meaning `cout` will not be automatically flushed before `cin` operations. This is safe as long as you don't rely on interactive input/output, which is almost never the case in online judges.

**Important:** If you use this, always prefer `\n` instead of `endl`, since `endl` also flushes the buffer unnecessarily.

## Standard Input and Output

### Input with `cin`

`cin >>` reads whitespace-separated values (integers, strings, doubles, etc.) from standard input:

```cpp
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b;
    cin >> a >> b;
    cout << a + b << "\n";
    return 0;
}
```

### Output with `cout`

`cout <<` writes values to standard output. You can chain multiple values together:

```cpp
cout << "Sum: " << (a + b) << "\n";
```

## Data Types in C++

Data types define the kind of value a variable can hold and how much memory it occupies. Choosing the correct type is crucial for correctness (avoiding integer overflow) and efficiency.

### Integer Types

| Type | Size (typical) | Range | Use Case |
|---|---|---|---|
| `short` | 2 bytes | $[-2^{15}, 2^{15}-1]$ | Small integers |
| `int` | 4 bytes | $[-2^{31}, 2^{31}-1] \approx [-2\cdot10^9, 2\cdot10^9]$ | Most common for general integers |
| `long long` | 8 bytes | $[-2^{63}, 2^{63}-1] \approx [-9\cdot10^{18}, 9\cdot10^{18}]$ | Large values (sums, products, counts) |
| `unsigned int/long long` | same as signed | Non-negative, larger upper bound | When values are guaranteed non-negative |

**Rule of thumb:** If a value can exceed $2^{31}-1$ (e.g., $10^9 + 10^9$ or array indices in very large problems), use `long long`.

```cpp
int x = 1000000000;           // OK within 2e9
long long y = 1000000000000LL; // Use LL suffix for literals
```

### Floating Point Types

| Type | Precision | Use Case |
|---|---|---|
| `float` | ~6-7 decimal digits | Rarely used in CP; less precise |
| `double` | ~15-17 decimal digits | Standard for real numbers, comparisons, and geometry |
| `long double` | Higher (platform-dependent) | Occasionally used for very high precision, but slower |

For most competitive programming problems involving floating point (e.g., distances, areas), `double` is sufficient.

```cpp
double pi = 3.141592653589793;
double area = pi * r * r;
```

### Character and Boolean

- `char`: Stores a single character. Also used to represent small integers (-128..127).
- `bool`: Stores `true` or `false`. Often used for flags and conditions.

```cpp
char c = 'A';
bool is_valid = true;
```

## Type Modifiers and Constants

### `const`

Use `const` to declare variables whose values should not change. This improves readability and helps prevent accidental modifications.

```cpp
const int INF = 1000000000; // 10^9
const long long LINF = 1000000000000000000LL; // 10^18
const int MOD = 1e9 + 7;
```

### `constexpr` (C++11+)

For values known at compile time, `constexpr` is preferred over `const` in modern C++:

```cpp
constexpr int MAX_N = 100005;
```

## Type Conversions

C++ allows implicit and explicit type conversions. Be cautious with narrowing conversions, especially when mixing integer types.

```cpp
int a = 5;
double d = a;        // Implicit: int to double (safe)
long long ll = a;    // Safe
int b = (int)d;      // Explicit cast
```

When multiplying two `int` values that may be large, cast to `long long` first:

```cpp
int a = 10^9, b = 10^9;
long long prod = (long long)a * b; // Correct, avoids overflow
```

## Common Pitfalls

- **Integer overflow**: Using `int` for sums/products of large numbers. Always consider `long long`.
- **Forgetting fast I/O**: For $10^5$ elements, default I/O can exceed time limits.
- **Mixing types carelessly**: Can lead to unexpected truncation or precision loss.
- **Using `endl`**: Causes unnecessary buffer flushes. Use `\n` instead.

## Key Takeaways

- Always include `ios_base::sync_with_stdio(false); cin.tie(NULL);` at the beginning of `main()` for competitive programming.
- Use `long long` when values may exceed $2^{31}-1$.
- Prefer `double` for floating point arithmetic.
- Use `const`/`constexpr` for fixed values like limits and moduli.
- Be explicit when casting to avoid subtle bugs.

## Next Topic

[Conditionals and Loops](conditionals-and-loops.md)
