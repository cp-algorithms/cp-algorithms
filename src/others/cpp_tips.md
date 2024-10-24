---
tags:
  - Original
---

# C++ Tips and Tricks for Competition Programming

## Faster I/O

- `std::ios_base::sync_with_stdio(false)`: by default, C++ works with C++ iostreams (like `std::cin`) and C style stdio streams (like `stdin`) by synchronizing them.
Since you should never need C style I/O (like `scanf`, `printf`), in C++, disabling this synchronization will make C++ I/O competitive with C style `scanf`.
- `std::cin.tie(0)`: By default, iostreams flush cout every time you read from cin, so that you will always display any output before reading any input.
You can disable this automatic flushing to make I/O faster. The exception is for interactive problems with interleaved inputs and outputs, for which you can either not use `cin.tie(0)` or flush explicitly with `cout.flush()`/`cout.endl`.

References:
[Dr. Dobbs - The Standard Librarian: IOStreams and Stdio](https://www.drdobbs.com/the-standard-librarian-iostreams-and-std/184401305),
[Codeforces - Best form of C++ I/O?](https://codeforces.com/blog/entry/6251)

## Less Typing

- `using namespace std;`: this saves lots of tedious typing of `std::` before all the standard library functions and objects. However, a blanket namespace import like this can cause name clashes, so don't name your variables or functions something common like `find` or anything from [this list](https://en.cppreference.com/w/cpp/symbol_index).
- `#include <bits/stdc++.h>`: this is a catch-all implementation-defined header in g++ that avoids having a list of dozens of includes like `#include <vector>`, `#include <iostream>`, `#include <string>`, etc. It should work on any CP judge site, but it is not a standard header.
- `#define int long long`: some people define `int` to always be (at least) 64-bit to avoid overflow issues, since most CP problems use numbers that fit in a 64-bit integer. However, be aware of unexpected issues:
  - C++ requires `main` to be a function returning `int` and not `long long`, so use `signed main` as a workaround.
  - Function calls like `min(x, 0)` may complain that `0` is type `int`. 
  - May require twice as much memory than `int` and make the program slower, which may be important in extremely time-critical code.
  - Otherwise you can use `typedef long long ll` or use the appropriate fixed-width integer types like `int64_t`. 
