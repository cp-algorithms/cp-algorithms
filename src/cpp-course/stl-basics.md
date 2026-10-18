---
title: STL Basics
tags:
  - Course
---

# STL Basics (Standard Template Library)

STL is one of the most powerful tools in C++ for competitive programming.

## Useful Headers

```cpp
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <utility>
```

## Algorithm

```cpp
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> v = {3, 1, 4, 1, 5, 9};
    sort(v.begin(), v.end());      // {1,1,3,4,5,9}
    reverse(v.begin(), v.end());   // {9,5,4,3,1,1}
    
    if (binary_search(v.begin(), v.end(), 5)) {
        cout << "Found\n";
    }
    
    auto it = lower_bound(v.begin(), v.end(), 4);
    cout << *it << "\n"; // first >= 4
    return 0;
}
```

## Queue (FIFO)

```cpp
#include <queue>

queue<int> q;
q.push(1);
q.push(2);
q.pop();
cout << q.front() << "\n";
```

## Stack (LIFO)

```cpp
#include <stack>

stack<int> st;
st.push(1);
st.push(2);
cout << st.top() << "\n";
st.pop();
```

## Set (Sorted, No Duplicates)

```cpp
#include <set>

set<int> s;
s.insert(5);
s.insert(1);
s.insert(5);
for (int x : s) cout << x << " "; // 1 5
if (s.count(1)) cout << "Exists\n";
```

## Map (Key-Value, Sorted)

```cpp
#include <map>

map<string, int> m;
m["john"] = 20;
m["anna"] = 25;
cout << m["anna"] << "\n";
for (auto &[name, age] : m) {
    cout << name << ": " << age << "\n";
}
```

## Next Topic

[Algorithmic Complexity](algorithmic-complexity.md)
