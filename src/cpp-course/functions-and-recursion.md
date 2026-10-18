---
title: Functions and Recursion
tags:
  - Course
---

# Functions and Recursion

## Functions

```cpp
#include <iostream>

using namespace std;

int sum(int a, int b) {
    return a + b;
}

int main() {
    cout << sum(3, 4) << "\n";
    return 0;
}
```

## Pass by Reference

```cpp
void swap_values(int &a, int &b) {
    int tmp = a; a = b; b = tmp;
}
```

## Function Overloading

```cpp
int max_val(int a, int b) { return a>b?a:b; }
double max_val(double a, double b) { return a>b?a:b; }
```

## Recursion

A function that calls itself.

### Factorial

```cpp
long long factorial(int n) {
    if (n <= 1) return 1LL;
    return n * factorial(n-1);
}
```

### Fibonacci

```cpp
long long fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}
```

**Note:** For large `n`, recursive Fibonacci is inefficient. Better to use DP or iterative approach.

## Next Topic

[STL Basics](stl-basics.md)
