---
title: STL Basics
tags:
  - Course
---

# STL Basics (Standard Template Library)

The Standard Template Library (STL) is one of C++'s greatest strengths for competitive programming. It provides efficient, well-tested implementations of common data structures and algorithms, allowing you to focus on problem-solving rather than reinventing the wheel.

## Why Use STL?

- **Efficiency**: Implementations are highly optimized (often using advanced techniques).
- **Correctness**: Battle-tested across countless projects and judges.
- **Readability**: Concise, expressive code.
- **Productivity**: Reduces boilerplate and development time.
- **Interoperability**: All components work together via iterators and common interfaces.

## Core Components of STL

1. **Containers**: Data structures like `vector`, `array`, `set`, `map`, `queue`, `stack`, `unordered_set`, `unordered_map`.
2. **Algorithms**: Generic operations like `sort`, `search`, `min/max`, `copy`, `transform`.
3. **Iterators**: Provide uniform access to elements across containers.
4. **Functors/Predicates**: Objects/functions used to customize behavior.
5. **Utilities**: Pairs, tuples, smart pointers (less common in pure CP).

## Essential Headers

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <utility>
#include <functional>
#include <iterator>
#include <limits>
#include <cstddef>
```

## Algorithms (`<algorithm>`)

The `<algorithm>` header is indispensable. Most algorithms operate on ranges `[begin, end)` using iterators.

### Sorting and Ordering

```cpp
#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> v = {5, 2, 9, 1, 5, 6, 3};
    
    // Ascending sort
    sort(v.begin(), v.end()); // O(n log n)
    
    // Descending sort (two ways)
    sort(v.begin(), v.end(), greater<int>());
    // or reverse after ascending: reverse(v.begin(), v.end());
    
    // Partial sort: first k elements in ascending order
    vector<int> v2 = {5, 2, 9, 1, 5, 6, 3};
    partial_sort(v2.begin(), v2.begin() + 3, v2.end()); // first 3 smallest
    
    // Stable sort preserves relative order of equal elements
    stable_sort(v2.begin(), v2.end());
    
    return 0;
}
```

### Searching

```cpp
vector<int> v = {1, 2, 3, 5, 5, 6, 9};
sort(v.begin(), v.end()); // Ensure sorted

// Binary search (O(log n), requires sorted range)
bool exists = binary_search(v.begin(), v.end(), 5);

// lower_bound: first element >= value
auto lb = lower_bound(v.begin(), v.end(), 5); // iterator to first 5

// upper_bound: first element > value
auto ub = upper_bound(v.begin(), v.end(), 5); // iterator after last 5

// Count of elements equal to value
size_t count5 = distance(lb, ub); // or (ub - lb)
size_t count5_alt = upper_bound(v.begin(), v.end(), 5) - lower_bound(v.begin(), v.end(), 5);
```

### Other Useful Algorithms

```cpp
vector<int> a = {1, 2, 3}, b = {4, 5, 6};
vector<int> c(6);

// min, max, min_element, max_element
int m = min({1, 2, 3, 4}); // C++11 initializer list
auto it_max = max_element(a.begin(), a.end());

// Copy
copy(a.begin(), a.end(), c.begin());
copy(a.begin(), a.end(), back_inserter(c)); // safer if resizing needed

// Fill
fill(c.begin(), c.end(), 0);

// Reverse
reverse(a.begin(), a.end());

// Rotate
rotate(a.begin(), a.begin() + 1, a.end()); // shift left by 1

// Swap
swap(a, b);

// Transform (apply function to range)
transform(a.begin(), a.end(), a.begin(), [](int x) { return x * 2; });
```

## Sequential Containers

### `vector` (Dynamic Array)

As covered in the previous lesson, `vector` is the go-to for most CP problems. See [Arrays and Vectors](arrays-and-vectors.md) for details.

### `array` (Fixed-size Array, C++11+)

`std::array` is a safer, STL-aware alternative to C-style arrays with size known at compile time.

```cpp
#include <array>
#include <iostream>

using namespace std;

int main() {
    array<int, 5> a = {1, 2, 3, 4, 5};
    cout << a.size() << "\n";      // 5
    cout << a[0] << " " << a.at(2) << "\n";
    for (int x : a) cout << x << " ";
    return 0;
}
```

Use `array` when size is fixed and small/known. It's allocated on stack and has zero overhead compared to C arrays.

### `string`

`string` is far more convenient than C-style `char` arrays for text manipulation.

```cpp
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    string s = "competitive";
    s += " programming"; // concatenation
    cout << s.length() << "\n";
    cout << s.substr(0, 11) << "\n"; // "competitive"
    reverse(s.begin(), s.end());
    if (s.find("gnimmargorp") != string::npos) cout << "Found\n";
    return 0;
}
```

## Container Adaptors

### `stack` (LIFO)

```cpp
#include <stack>
#include <iostream>

using namespace std;

int main() {
    stack<int> st;
    st.push(1); st.push(2); st.push(3);
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    return 0;
}
// Output: 3 2 1
```

**Use cases:** Balanced parentheses, expression evaluation, DFS (iterative), undo operations.

### `queue` (FIFO)

```cpp
#include <queue>
#include <iostream>

using namespace std;

int main() {
    queue<int> q;
    q.push(1); q.push(2); q.push(3);
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    return 0;
}
// Output: 1 2 3
```

**Use cases:** BFS, level-order traversal, task scheduling.

### `priority_queue` (Max-Heap by Default)

`priority_queue` maintains elements in descending order (max-heap). Great for getting maximum quickly.

```cpp
#include <queue>
#include <iostream>

using namespace std;

int main() {
    priority_queue<int> pq;
    pq.push(3); pq.push(1); pq.push(4); pq.push(1);
    while (!pq.empty()) {
        cout << pq.top() << " "; // 4 3 1 1
        pq.pop();
    }
    return 0;
}
```

To get min-heap behavior, use `greater`:

```cpp
priority_queue<int, vector<int>, greater<int>> minpq;
minpq.push(3); minpq.push(1); minpq.push(4);
cout << minpq.top(); // 1
```

**Use cases:** Dijkstra's algorithm, Huffman coding, K-largest/smallest elements.

### `deque` (Double-ended Queue)

```cpp
#include <deque>
#include <iostream>

using namespace std;

int main() {
    deque<int> dq;
    dq.push_back(1); dq.push_front(2); // dq = {2,1}
    dq.pop_back(); dq.pop_front();
    return 0;
}
```

Useful when you need efficient push/pop from both ends.

## Associative Containers (Sorted)

### `set` (Unique, Sorted)

```cpp
#include <set>
#include <iostream>

using namespace std;

int main() {
    set<int> s;
    s.insert(5); s.insert(1); s.insert(3); s.insert(1); // duplicate ignored
    for (int x : s) cout << x << " "; // 1 3 5
    
    // Find
    auto it = s.find(3);
    if (it != s.end()) cout << "\nFound";
    
    // Erase
    s.erase(1);
    s.erase(it); // erase by iterator
    
    return 0;
}
```

Operations: `insert`, `erase`, `find`, `count` all in $O(\log n)$.

**Use cases:** Maintaining sorted unique elements, dynamic order statistics.

### `multiset` (Duplicates Allowed, Sorted)

```cpp
#include <set>
#include <iostream>

using namespace std;

int main() {
    multiset<int> ms;
    ms.insert(1); ms.insert(5); ms.insert(5); ms.insert(3);
    for (int x : ms) cout << x << " "; // 1 3 5 5
    
    // Find first occurrence
    auto it = ms.find(5);
    // Erase one occurrence
    ms.erase(it);
    // Erase all occurrences
    ms.erase(5);
    
    return 0;
}
```

### `map` (Key-Value Pairs, Sorted by Key)

```cpp
#include <map>
#include <iostream>

using namespace std;

int main() {
    map<string, int> m;
    m["alice"] = 90;
    m["bob"] = 85;
    m["charlie"] = 92;
    
    // Access
    cout << m["alice"] << "\n";
    
    // Check existence
    if (m.count("bob")) cout << "Exists\n";
    auto it = m.find("dave");
    if (it == m.end()) cout << "Not found\n";
    
    // Iterate
    for (const auto &p : m) {
        cout << p.first << ": " << p.second << "\n";
    }
    // Or structured binding (C++17)
    for (const auto &[name, score] : m) {
        cout << name << ": " << score << "\n";
    }
    
    return 0;
}
```

`operator[]` creates an entry with default value if key doesn't exist—use `find()` if you don't want this behavior.

**Use cases:** Frequency maps, dictionaries, coordinate compression with values.

### `multimap` (Multiple Values per Key)

```cpp
#include <map>
#include <iostream>

using namespace std;

int main() {
    multimap<int, string> mm;
    mm.insert({1, "one"});
    mm.insert({2, "two"});
    mm.insert({1, "uno"}); // same key, different value
    auto range = mm.equal_range(1);
    for (auto it = range.first; it != range.second; ++it) {
        cout << it->second << " ";
    }
    return 0;
}
```

## Unordered Associative Containers (Hash-based)

These provide average $O(1)$ for lookup/insert/delete vs $O(\log n)$ for ordered ones. No sorting by key.

### `unordered_set`

```cpp
#include <unordered_set>
#include <iostream>

using namespace std;

int main() {
    unordered_set<int> us = {1, 2, 3, 1};
    us.insert(4);
    if (us.find(2) != us.end()) cout << "Found\n";
    return 0;
}
```

### `unordered_map`

```cpp
#include <unordered_map>
#include <iostream>

using namespace std;

int main() {
    unordered_map<string, int> um;
    um["a"] = 1; um["b"] = 2;
    for (const auto &[k, v] : um) cout << k << ":" << v << " ";
    return 0;
}
```

**Trade-offs:**

- **Faster average**: $O(1)$ vs $O(\log n)$
- **No ordering**: Can't iterate in sorted key order
- **Extra memory**: Hash table overhead
- **Hash function needed**: Works well for built-in types; may need custom hash for complex types

**Rule of thumb:** If you don't need sorted order, prefer unordered variants for performance. For integer/string keys, they're usually faster.

## `pair` and `tuple` (Utilities)

### `pair`

```cpp
#include <utility>
#include <iostream>

using namespace std;

int main() {
    pair<int, string> p = {1, "apple"};
    cout << p.first << ": " << p.second << "\n";
    // Or make_pair
    auto p2 = make_pair(2, "banana");
    return 0;
}
```

Pairs are used in `map`, `multimap` and to return multiple values.

### `tuple` (C++11+)

```cpp
#include <tuple>
#include <iostream>

using namespace std;

int main() {
    tuple<int, string, double> t = {1, "test", 3.14};
    auto [a, b, c] = t; // structured binding (C++17)
    cout << a << " " << b << " " << c << "\n";
    return 0;
}
```

## Iterators: The Glue

Iterators abstract container traversal. All STL algorithms work with iterators, not container types directly.

- `begin()`, `end()`: Forward iterators
- `rbegin()`, `rend()`: Reverse iterators
- `cbegin()`, `cend()`: Const iterators
- `back_inserter()`, `front_inserter()`, `inserter()`: Insertion iterators

```cpp
vector<int> v = {1, 2, 3};
auto it = find(v.begin(), v.end(), 2); // returns iterator
if (it != v.end()) *it = 20; // modify
```

## Performance Tips for CP

- Prefer `reserve()` on vectors when size is known.
- Use `unordered_map/unordered_set` only if order doesn't matter and keys are hashable.
- Avoid unnecessary copies—pass by `const &`.
- `emplace_back()` can be more efficient than `push_back()` for complex objects (constructs in-place).
- For large ranges, prefer algorithms over hand-written loops (they're often optimized).
- Use `range-based for` for readability; with `-O2` it's as fast as index loops.
- Be careful with `map`/`set` vs `unordered_*`: choose based on $n$ and need for ordering.

## Common Pitfalls

- Using `unordered_map` with custom types without hash function.
- Calling `operator[]` on `unordered_map/map` for non-existent key unintentionally creates it.
- Forgetting `end()` checks after `find()`.
- Modifying container while iterating incorrectly (can invalidate iterators).
- Mixing `auto` carelessly—know iterator types when needed.

## Key Takeaways

- STL is essential for efficient, concise CP solutions.
- Master `vector`, `set`, `map`, `queue`, `stack`, `priority_queue`, `unordered_*`.
- Use `<algorithm>` extensively: `sort`, `lower_bound`, `upper_bound`, `binary_search`, `find`.
- Choose ordered vs unordered based on ordering requirement and performance.
- Prefer iterators/range-based for over index access when using algorithms.
- Pass containers by const reference to avoid copies.

## Next Topic

[Algorithmic Complexity](algorithmic-complexity.md)
