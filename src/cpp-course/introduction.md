---
title: Introduction to C++
tags:
  - Course
---

# Introduction to C++

## What is C++?

C++ is a general-purpose, compiled, multi-paradigm programming language. It is one of the most widely used languages in competitive programming due to its speed, efficiency, and the extensive Standard Template Library (STL).

## Why Use C++ for Competitive Programming?

- **Speed**: Much faster than interpreted languages
- **Memory efficiency**: Fine-grained control over memory usage
- **STL**: Ready-to-use data structures and algorithms
- **Portability**: Available on most online judges (Codeforces, SPOJ, UVa, etc.)
- **Familiar syntax**: Based on C with object-oriented improvements

## First Program

```cpp
#include <iostream>

using namespace std;

int main() {
    cout << "Welcome to the C++ course!" << endl;
    return 0;
}
```

## Compilation

To compile a C++ program, we typically use `g++`:

```bash
g++ -std=c++17 -Wall -O2 -o program program.cpp
./program
```

## Important Notes

- `-std=c++17`: Uses C++17 standard (common in current judges)
- `-Wall`: Enables useful warnings
- `-O2`: Enables optimizations for better performance

## Next Topic

[I/O and Data Types](io-and-data-types.md)
