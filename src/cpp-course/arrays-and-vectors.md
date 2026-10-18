---
title: Arrays and Vectors
tags:
  - Course
---

# Arrays and Vectors

## Arrays (Static)

```cpp
int arr[100];      // array of size 100
int mat[10][10];   // 10x10 matrix
```

```cpp
for (int i = 0; i < n; i++) {
    cin >> arr[i];
}
```

## Vectors (Dynamic) - STL

Vectors are much more flexible and widely used in competitive programming.

```cpp
#include <vector>

using namespace std;

int main() {
    vector<int> v;
    v.push_back(5);
    v.push_back(10);
    v.push_back(3);
    
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
    return 0;
}
```

### Useful Vector Operations

```cpp
vector<int> v(n, 0); // vector of n elements initialized to 0
v.resize(n);
v.clear();
v.pop_back();
sort(v.begin(), v.end());
reverse(v.begin(), v.end());
```

## Range-based for Loop (C++11+)

```cpp
for (int x : v) {
    cout << x << " ";
}
```

## Next Topic

[Functions and Recursion](functions-and-recursion.md)
