---
title: Algorithmic Complexity
tags:
  - Course
---

# Algorithmic Complexity

Understanding complexity is essential for writing efficient solutions.

## What is Complexity?

Time complexity measures how many operations an algorithm performs as a function of input size `n`. We use Big-O notation: $O(f(n))$.

## Common Complexities

| Complexity | Name | Example |
|---|---|---|
| $O(1)$ | Constant | Array access |
| $O(\log n)$ | Logarithmic | Binary search |
| $O(n)$ | Linear | Loop through array |
| $O(n \log n)$ | Linearithmic | std::sort |
| $O(n^2)$ | Quadratic | Double nested loop |
| $O(2^n)$ | Exponential | Subsets |
| $O(n!)$ | Factorial | Permutations |

## Examples

### $O(n)$

```cpp
for (int i = 0; i < n; i++) {
    cout << a[i];
}
```

### $O(n^2)$

```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        // ...
    }
}
```

### $O(\log n)$

```cpp
while (n > 0) {
    n /= 2;
}
```

## Guidelines for Competitive Programming

- For $n \le 10^3$: $O(n^2)$ usually passes
- For $n \le 10^4$: $O(n^2)$ might be tight; prefer $O(n\log n)$
- For $n \le 10^5$: Need at least $O(n\log n)$
- For $n \le 10^9$: Only $O(\log n)$ or $O(1)$

## Next Topic

[Practice and Problems](practice-and-problems.md)
