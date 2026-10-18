---
title: I/O and Data Types
tags:
  - Course
---

# I/O and Data Types

## Input and Output

In C++, we use `<iostream>` for standard input/output.

- `cin >> variable`: Reads from standard input
- `cout << variable`: Writes to standard output
- `endl`: Newline (adds flush; better to use `\n` in contests)

```cpp
#include <iostream>

using namespace std;

int main() {
    int x;
    cin >> x;
    cout << "Value: " << x << "\n";
    return 0;
}
```

**Recommendation for competitive programming:** Disable synchronization between C and C++ for faster I/O.

```cpp
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    cout << n << "\n";
    return 0;
}
```

## Basic Data Types

| Type | Typical Size | Range |
|---|---|---|
| `char` | 1 byte | -128 to 127 or 0 to 255 |
| `int` | 4 bytes | -2^31 to 2^31-1 (~ ±2e9) |
| `long long` | 8 bytes | -2^63 to 2^63-1 (~ ±9e18) |
| `float` | 4 bytes | Single precision |
| `double` | 8 bytes | Double precision |
| `bool` | 1 byte | `true` or `false` |

```cpp
int a = 5;
long long b = 1000000000000LL;
double d = 3.14159;
bool flag = true;
```

## Constants

```cpp
const int MAX = 1000005;
#define INF 1000000000
```

## Next Topic

[Conditionals and Loops](conditionals-and-loops.md)
