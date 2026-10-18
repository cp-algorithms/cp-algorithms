---
title: Introduction to C++
tags:
  - Course
---

# Introduction to C++

## What is C++?

C++ is a general-purpose, compiled, statically-typed programming language developed by Bjarne Stroustrup as an extension of C. It supports multiple paradigms, including procedural, object-oriented, and generic programming. Thanks to its combination of high performance and expressive syntax, C++ has become one of the most widely used languages in competitive programming, embedded systems, game development, and high-performance computing.

## Why Use C++ for Competitive Programming?

Competitive programming requires solving algorithmic problems under time and memory constraints. C++ is particularly well-suited for this for several reasons:

- **Execution speed**: As a compiled language, C++ produces highly optimized machine code, making it significantly faster than interpreted languages.
- **Memory efficiency**: It gives fine-grained control over memory allocation and deallocation, which is essential for problems with tight memory limits (often 256 MB or 512 MB).
- **Standard Template Library (STL)**: STL provides a rich collection of efficient data structures (like `vector`, `set`, `map`, `queue`) and algorithms (`sort`, `binary_search`, etc.), reducing implementation time.
- **Wide judge support**: Nearly all online judges (Codeforces, AtCoder, SPOJ, UVa, CodeChef, TopCoder) support C++ with fast judges and modern standards.
- **Low-level and high-level features**: C++ allows you to optimize critical parts while still writing readable, high-level code.
- **Predictable performance**: With compiler optimizations (`-O2`), runtime behavior is consistent and efficient.

## Setting Up a C++ Environment

To write and run C++ programs, you need a compiler. The most common choice for competitive programming and judges is GCC (GNU Compiler Collection), specifically `g++`.

### Recommended Compiler Flags

When compiling for competitive programming or coding in judges, use the following flags for safety and performance:

```bash
g++ -std=c++17 -Wall -Wextra -O2 -o program program.cpp
```

- `-std=c++17`: Enables C++17 features (widely supported across modern judges).
- `-Wall -Wextra`: Enables compiler warnings to help catch potential bugs early.
- `-O2`: Applies aggressive optimizations to improve runtime performance.
- `-o program`: Specifies the output executable name.

## Your First C++ Program

A classic "Hello World" program demonstrates the basic structure of C++:

```cpp
#include <iostream>

using namespace std;

int main() {
    cout << "Welcome to the C++ course for Competitive Programming!" << "\n";
    return 0;
}
```

### Explanation

1. `#include <iostream>`: Includes the standard input/output stream library, which allows us to use `cin` and `cout`.
2. `using namespace std;`: Brings the standard namespace (`std::`) into scope. While convenient for competitive programming and small programs, in larger projects it's often better to avoid it. For contest/CP environments, it's standard practice.
3. `int main() { ... }`: The entry point of every C++ program. Execution begins here.
4. `cout << ... << "\n";`: Outputs text to standard output. We prefer `"\n"` over `endl` to avoid unnecessary flushing (important for large I/O).
5. `return 0;`: Indicates successful program termination.

## Compilation and Execution

Assuming your file is named `program.cpp`, run the following in your terminal:

```bash
g++ -std=c++17 -Wall -Wextra -O2 -o program program.cpp
./program
```

This will compile and execute your program, printing the welcome message to the console.

## Key Takeaways

- C++ is the dominant language in competitive programming due to its speed and STL.
- Always compile with optimization flags (`-O2`) and warnings enabled in practice.
- Prefer `\n` over `endl` for competitive programming I/O.
- Understanding the basic program structure is essential before moving to more advanced topics.

## Next Topic

[Input/Output and Data Types](io-and-data-types.md)
