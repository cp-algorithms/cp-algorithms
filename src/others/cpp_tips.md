---
tags:
  - Original
---

# C++ Tips and Tricks for Competition Programming

## Faster I/O

- `std::ios_base::sync_with_stdio(false)`: by default, C++ works with C++ iostreams (like `std::cin`) and C style stdio streams (like `stdin`) by synchronizing them.
Since you should never need C style I/O (like `scanf`, `printf`), in C++, disabling this synchronization will make C++ I/O competitive with C style `scanf`.
- `std::cin.tie(0)`: By default, iostreams flush cout every time you read from cin, so that you will always display any output before reading any input.
If you are not solving an interactive problem, i.e. you don't require interleaving inputs and outputs, you can disable this automatic flushing to make I/O faster.

References:
[Dr. Dobbs - The Standard Librarian: IOStreams and Stdio](https://www.drdobbs.com/the-standard-librarian-iostreams-and-std/184401305),
[Codeforces - Best form of C++ I/O?](https://codeforces.com/blog/entry/6251)

## Less Typing

- `using namespace std;`: this saves lots of tedious typing of `std::` before all the standard library functions and objects. However, a blanket namespace import like this can cause name clashes, so don't name your variables or functions something common like `find` or anything from [this list](https://en.cppreference.com/w/cpp/symbol_index).
- `#include <bits/stdc++.h>`: this is a catch-all implementation-defined header in g++ that avoids having a list of dozens of includes like `#include <vector>`, `#include <iostream>`, `#include <string>`, etc. It should work on any CP judge site, but it is not a standard header.
