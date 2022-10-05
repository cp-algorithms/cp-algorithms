---
tags:
  - Original
---

# Fast I/O

Although rarely talked about, I/O can make a huge impact on the running time of your solution. Here are some techniques for tricking the testing system into thinking your program is faster than it actually is.

## C++ streams

C++ streams are a bad fit for competetive programming, due to their extensive error checking and clunky syntax. Even so, you can still use them without leaving a **ton** of performance on the table if you add the following lines to the beginning of your program:

```cpp
#include <iostream>

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // ...
}
```

## Standard C I/O

`scanf` and `printf` are faster than C++ streams **in most testing systems**. They're also more convenient to use. Their only downside is the fact that you have to use [conversion specifiers](https://en.cppreference.com/w/cpp/io/c/fscanf). Even still, it only takes a couple of days of using them to remember all the ones you need.

It is **strongly recommended** to compile with `-Wformat`. Failing to use the correct specifier - for example using `%d` with a `long long` argument will cause overflows.

## Fast integer input

Reading the input character by character allows us to write our own string to integer conversion, and thanks to the assumption that all input is correct we can make it much faster than `scanf` or `cin` implementations. Note that this function can be extended to allow for negative numbers.

When compiling with GCC you can replace `getchar` with `getchar_unlocked` for a slight speedup.

```cpp
#include <cstdio>

template<typename T>
void read(T& v) {
    char c;
    do
        c = getchar();
    while (c < '0' || c > '9');

    v = T{0};
    do {
        v = v * T{10} + T{c - '0'};
        c = getchar();
    } while (c >= '0' && c <= '9');
}
```

## Input buffering

For some reason, I couldn't find any good resources on using this technique in competetive programming. When profiling a program that's using classic fast integer input you might notice that the overhead of calling `getchar` gets pretty big when the input is large (or has a lot of whitespace). We can improve this by reading the whole input in one function call.

When compiling with GCC you can replace `fread` with `fread_unlocked`.

```cpp
#include <cstdio>

// Maximum size of the input, including whitespace
constexpr int max_input = 1e6;
char buffer[max_input];
const char* ptr;

template<typename T>
void read(T& v) {
    while (*ptr < '0' || *ptr > '9')
        ++ptr;

    v = T{0};
    while (*ptr >= '0' && *ptr <= '9') {
        v = v * T{10} + T{*ptr - '0'};
        ++ptr;
    }
}

int main() {
    fread(buffer, sizeof(char), max_input, stdin);
    ptr = buffer;
    // ...
}
```

## Output buffering

Output is rarely a bottleneck for competetive programing problems, but when it is it might be worth it to use a buffer. The way we do this is very simillar to input buffering.

The print function can be sped up **significantly** if you use a custom algorithm for integer formatting that takes advantage of assumptions about the number of digits. This implementation uses `to_chars`, which is available in C++17.

```cpp
#include <charconv>
#include <cstdio>

// Maximum size of output, including whitespace
constexpr int max_output = 1e6;
char buffer[max_output];
char* ptr;

template<typename T>
void print(T v) {
    ptr = to_chars(ptr, buffer + max_output, v).ptr;
}

// Used for printing newlines, spaces etc.
void print(char c) {
    *ptr++ = c;
}

int main() {
    ptr = buffer;
    // ...
    puts(buffer);
}
```