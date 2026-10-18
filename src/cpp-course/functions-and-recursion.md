---
title: Functions and Recursion
tags:
  - Course
---

# Functions and Recursion

Functions allow us to modularize code, improve readability, avoid duplication, and solve complex problems by breaking them into smaller, reusable units. Recursion is a powerful technique where a function calls itself to solve problems that exhibit self-similarity (like divide-and-conquer, tree traversals, or combinatorial problems).

## Functions

### Defining and Calling Functions

A function has a return type, a name, a parameter list (optional), and a body. It can return a value using `return`.

```cpp
#include <iostream>

using namespace std;

int add(int a, int b) {
    return a + b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x = 3, y = 4;
    cout << add(x, y) << "\n"; // Output: 7
    return 0;
}
```

### Function Declaration vs Definition

If you define a function after it's used, you must declare it beforehand (a function prototype).

```cpp
#include <iostream>

using namespace std;

int multiply(int a, int b); // Declaration

int main() {
    cout << multiply(5, 6) << "\n";
    return 0;
}

int multiply(int a, int b) { // Definition
    return a * b;
}
```

For small programs or single-file solutions (common in CP), defining before use is often easier.

### Passing Parameters

#### Pass by Value

By default, parameters are copied. Modifications inside the function do not affect the original arguments.

```cpp
void increment(int x) {
    x++; // Original remains unchanged
}
```

Use pass-by-value for small, primitive types when you don't need to modify the caller's value.

#### Pass by Reference (`&`)

Passing by reference avoids copying and allows the function to modify the original variable. This is efficient for large objects (like vectors, strings).

```cpp
void swap_vals(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}
```

#### Pass by Const Reference (`const &`)

When you only need to read a large object without modifying it, use `const &` to avoid copying while ensuring immutability.

```cpp
#include <vector>
#include <iostream>

using namespace std;

long long sum_vec(const vector<int> &v) {
    long long s = 0;
    for (int val : v) s += val;
    return s;
}
```

This is a critical optimization in competitive programming when passing large containers.

### Default Arguments

Functions can have default parameter values. If the caller omits an argument, the default is used.

```cpp
void greet(const string &name, const string &prefix = "Hello") {
    cout << prefix << ", " << name << "!\n";
}

int main() {
    greet("Alice");           // Hello, Alice!
    greet("Bob", "Welcome");  // Welcome, Bob!
    return 0;
}
```

Default arguments must be specified from right to left in the parameter list.

### Function Overloading

C++ allows multiple functions with the same name but different parameter lists (different types/counts). The compiler selects the correct one based on arguments.

```cpp
int max_int(int a, int b) {
    return a > b ? a : b;
}

double max_dbl(double a, double b) {
    return a > b ? a : b;
}

// Better: overloaded
int max_val(int a, int b) { return a > b ? a : b; }
double max_val(double a, double b) { return a > b ? a : b; }
long long max_val(long long a, long long b) { return a > b ? a : b; }
```

Overloading improves code readability and reusability.

### Inline Functions

For very small, frequently called functions, `inline` suggests to the compiler to replace the function call with the body (reducing call overhead). With `-O2`, compilers often inline automatically.

```cpp
inline int square(int x) {
    return x * x;
}
```

Use `inline` judiciously—it's a hint, not a guarantee.

### Return Types and `void`

- If a function doesn't return a value, use `void`.
- Functions can return by value, by reference, or by pointer. Returning by reference is useful for chaining but must not return a local variable (dangling reference).
- In modern C++, you can also use `auto` for return type deduction (with trailing return types or C++14+).

```cpp
auto add_auto(int a, int b) -> int {
    return a + b;
}
```

## Recursion

Recursion occurs when a function calls itself directly or indirectly to solve a problem. It's elegant for problems with recursive structure: subproblems, trees, graphs (DFS), backtracking, and divide-and-conquer.

### How Recursion Works

Each recursive call creates a new stack frame. The recursion must have a **base case** that terminates the chain; otherwise, it leads to infinite recursion and a **stack overflow**.

### Classic Examples

#### Factorial

$$n! = n \cdot (n-1)!$, with base case $0! = 1$.

```cpp
long long factorial(int n) {
    if (n <= 1) return 1LL; // Base case
    return (long long)n * factorial(n - 1);
}
```

#### Fibonacci Numbers

Naive recursive Fibonacci is exponential ($O(2^n)$) due to overlapping subproblems. It's mainly for demonstration.

```cpp
long long fib_naive(int n) {
    if (n <= 1) return n; // Base cases
    return fib_naive(n - 1) + fib_naive(n - 2);
}
```

**Note:** For $n > 40$, naive recursion is impractical. For CP, use iterative DP ($O(n)$, $O(1)$ space) or matrix exponentiation ($O(\log n)$) for large n.

```cpp
// Iterative (efficient)
long long fib_iter(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}
```

### Recursion Depth and Stack Overflow

C++ has a limit on recursion depth (system-dependent). For deep recursion (e.g., DFS on a tree with $10^5$ nodes, or chain), default stack may overflow.

- **Linux judges**: Often allow ~10^7 stack in practice with optimizations? No. Typical limit is $10^4$ for recursion depth by default. For $10^5$ depth, need to increase or avoid recursion.
- **Solutions**: Use iterative methods, or increase stack (platform-specific). In competitive programming environments (GNU++), for deep trees, recursion depth up to $10^7$ isn't allowed; $10^4$ is common. So prefer iterative DFS for very deep graphs, or note judge constraints.

In practice, for Codeforces/AtCoder with GNU++17 and 64-bit, recursion depth up to ~10^7 is possible with some judges if using fast methods, but safer to assume limit ~10^4. Alternatively, add:

```cpp
#include <sys/resource.h>
void increase_stack() {
    const rlim_t kStackSize = 16 * 1024 * 1024; // 16 MB
    struct rlimit rl;
    int res = getrlimit(RLIMIT_STACK, &rl);
    if (res == 0 && rl.rlim_cur < kStackSize) {
        rl.rlim_cur = kStackSize;
        setrlimit(RLIMIT_STACK, &rl);
    }
}
```

But this is OS-specific (Linux). Most judges don't require this if problem states constraints reasonably, or tree is not skewed badly.

### Tail Recursion

Tail recursion is when the recursive call is the last operation. Some compilers optimize it (tail-call optimization) to avoid growing stack. Factorial as written above is not tail-recursive (needs multiplication after return). A tail-recursive version:

```cpp
long long fact_tail(int n, long long acc = 1LL) {
    if (n <= 1) return acc;
    return fact_tail(n - 1, acc * n);
}
```

Not all compilers guarantee TCO, so don't rely on it in CP.

### Backtracking and Recursion

Recursion shines in backtracking (permutations, combinations, N-Queens, subset generation):

```cpp
#include <vector>
#include <iostream>

using namespace std;

void subsets(const vector<int> &nums, vector<int> &current, int idx) {
    if (idx == (int)nums.size()) {
        // Process current subset
        for (int v : current) cout << v << " ";
        cout << "\n";
        return;
    }
    // Include
    current.push_back(nums[idx]);
    subsets(nums, current, idx + 1);
    current.pop_back(); // Backtrack
    // Exclude
    subsets(nums, current, idx + 1);
}

int main() {
    vector<int> nums = {1, 2, 3};
    vector<int> cur;
    subsets(nums, cur, 0);
    return 0;
}
```

### Recursion vs Iteration

| Aspect | Recursion | Iteration |
|---|---|---|
| Code clarity | Often cleaner for tree/DFS/backtrack | Often clearer for loops |
| Stack usage | Uses call stack (risk of overflow) | Uses fixed stack space |
| Performance | Slight overhead per call | Generally faster, no call overhead |
| Debugging | Harder (deep call chains) | Easier |
| Use case | Divide-and-conquer, DFS, backtracking | Simple loops, large depth cases |

**Guideline:** Use recursion when the problem is naturally recursive. Convert to iterative if depth is large or stack is limited.

## Key Takeaways

- Use `const &` for large parameters to avoid copies.
- Always include a base case in recursion to prevent infinite calls.
- Be mindful of recursion depth limits in judges; prefer iterative for very deep cases.
- Naive recursive Fibonacci has exponential complexity—use iterative/matrix form for large n.
- Backtracking relies heavily on recursion + undoing state (pop_back).
- Functions improve modularity, testability, and readability.

## Next Topic

[STL Basics](stl-basics.md)
