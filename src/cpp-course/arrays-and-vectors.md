---
title: Arrays and Vectors
tags:
  - Course
---

# Arrays and Vectors

Arrays and vectors are the most fundamental data structures for storing collections of elements. In competitive programming, they form the basis for almost every algorithm, from simple loops to complex graph traversals.

## Static Arrays

An array is a fixed-size, contiguous block of memory that holds elements of the same data type. The size must be known at compile time (or be a constant expression).

### Declaration and Initialization

```cpp
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int arr[5]; // Uninitialized array of 5 integers
    for (int i = 0; i < 5; ++i) arr[i] = i + 1;
    
    // Initialize at declaration
    int fixed[5] = {1, 2, 3, 4, 5};
    int partial[5] = {1, 2}; // Remaining elements become 0
    int zeros[5] = {0};     // All zeros
    
    return 0;
}
```

### Accessing Elements

Array elements are accessed by index, starting from `0`. Out-of-bounds access is undefined behavior and a common source of bugs—always ensure indices are within `[0, size-1]`.

```cpp
arr[0] = 10;
cout << arr[4] << "\n";
```

### Multi-dimensional Arrays

C++ supports multi-dimensional arrays. The 2D case is most common for matrices and grids.

```cpp
int mat[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

cout << mat[1][2] << "\n"; // Row 1, column 2 -> 6
```

For competitive programming, 2D arrays up to $10^3 \times 10^3$ are possible only if using 32-bit ints and global/static arrays (global arrays are allocated on heap-like static memory). Otherwise, prefer vectors for large sizes.

### Static Array Limitations

- **Fixed size**: Cannot grow or shrink at runtime.
- **Size must be constant**: You can't do `int arr[n]` with `n` from `cin` in some older compilers, though C++ supports Variable Length Arrays (VLAs) in some implementations. However, VLAs are not standard in C++ and may be rejected by certain judges. Safer to use `vector`.
- **No built-in bounds checking**: Easy to introduce memory errors.
- **Hard to pass/return**: Passing arrays to functions decays to pointers.

## Dynamic Vectors (`std::vector`)

`std::vector` is a dynamic array from the STL that automatically manages its size. It grows/shrinks as needed, provides bounds-safe access in debug builds (with some methods), and integrates seamlessly with STL algorithms.

### Declaration and Initialization

```cpp
#include <vector>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> v1;                // Empty vector
    vector<int> v2(5);             // 5 elements, default-initialized to 0
    vector<int> v3(5, 10);         // 5 elements, all set to 10
    vector<int> v4 = {1, 2, 3, 4}; // List initialization
    vector<int> v5(v4.begin(), v4.end()); // Copy from range
    
    return 0;
}
```

### Adding and Removing Elements

```cpp
vector<int> v;
v.push_back(5);  // Append to end - O(1) amortized
v.push_back(10);
v.push_back(3);
v.pop_back();    // Remove last element - O(1)
v.clear();       // Remove all elements - O(size)
```

### Accessing Elements

Vectors support multiple access methods:

```cpp
vector<int> v = {10, 20, 30, 40};
cout << v[0] << "\n";      // Index access (no bounds check)
cout << v.at(1) << "\n";   // Bounds-checked access (throws if out of range)
cout << v.front() << "\n"; // First element
cout << v.back() << "\n";  // Last element
```

For performance-critical code in CP, prefer `operator[]` over `at()` since bounds checking is unnecessary when logic is correct.

### Size and Capacity

Understanding the difference between `size()` and `capacity()` is important for efficiency:

- `size()`: Number of elements currently stored.
- `capacity()`: Amount of memory allocated (can be >= size).
- `resize(n)`: Changes size to `n`. If larger, fills with default values.
- `reserve(n)`: Allocates capacity for at least `n` elements without changing size. Useful to avoid reallocations when pushing many elements.

```cpp
vector<int> v;
v.reserve(10^5); // Avoids repeated reallocations
for (int i = 0; i < 10^5; ++i) v.push_back(i);
```

### Iterating Over Vectors

There are several ways to iterate efficiently:

```cpp
vector<int> v = {1, 2, 3, 4, 5};

// Index-based
for (size_t i = 0; i < v.size(); ++i) {
    cout << v[i] << " ";
}
cout << "\n";

// Range-based for (recommended for readability)
for (int val : v) {
    cout << val << " ";
}
cout << "\n";

// Iterator-based (useful with STL algorithms)
for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";
}
cout << "\n";

// Reverse iteration
for (auto it = v.rbegin(); it != v.rend(); ++it) {
    cout << *it << " ";
}
cout << "\n";
```

### Common Vector Operations with STL Algorithms

`<algorithm>` provides powerful operations on vectors/ranges:

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> v = {5, 2, 9, 1, 5, 6};
    sort(v.begin(), v.end());           // Ascending sort: {1,2,5,5,6,9}
    sort(v.begin(), v.end(), greater<int>()); // Descending: {9,6,5,5,2,1}
    reverse(v.begin(), v.end());        // Reverse order
    unique(v.begin(), v.end());         // Remove consecutive duplicates (sort first!)
    
    // Binary search (vector must be sorted)
    bool has = binary_search(v.begin(), v.end(), 5);
    auto lo = lower_bound(v.begin(), v.end(), 5); // First >= 5
    auto hi = upper_bound(v.begin(), v.end(), 5); // First > 5
    
    // Count elements
    int cnt = count(v.begin(), v.end(), 5);
    
    // Find
    auto it = find(v.begin(), v.end(), 9);
    if (it != v.end()) cout << "Found\n";
    
    return 0;
}
```

**Note:** `unique()` doesn't erase elements from the vector; it shifts unique ones to front and returns an iterator to the new end. To actually remove duplicates:

```cpp
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
```

## 2D Vectors

For dynamic 2D structures (grids where dimensions may be read at runtime), use `vector<vector<int>>` or a flat `vector<int>` for better cache locality.

### Nested Vector

```cpp
int n, m;
cin >> n >> m;
vector<vector<int>> grid(n, vector<int>(m, 0));
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
        cin >> grid[i][j];
    }
}
```

### Flat Vector (Efficient Alternative)

```cpp
vector<int> grid(n * m);
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
        cin >> grid[i * m + j]; // Row-major indexing
    }
}
```

Flat vectors are often faster for large grids due to better memory locality.

## When to Use Array vs Vector?

| Aspect | Array | Vector |
|---|---|---|
| Size | Fixed at compile time | Dynamic at runtime |
| Memory | Stack or static | Heap (dynamic allocation) |
| Safety | No bounds checking | `at()` provides bounds check; iterators safer |
| STL compatibility | Limited (decays to pointer) | Full support with algorithms |
| CP usage | Small, fixed sizes or global | Preferred for most problems |
| Performance | Slightly less overhead | Amortized O(1) push_back with small overhead |

**Recommendation:** Use `vector` by default in competitive programming. Only use raw arrays when you have a strong reason (e.g., very tight memory constraints or interfacing with C APIs).

## Common Pitfalls

- **Out-of-bounds access**: Check indices, especially with user input.
- **Copying large vectors**: Passing by value copies the entire vector. Use references (`const vector<int> &`) when reading.
- **Forgetting to reserve**: Can cause many reallocations when building large vectors.
- **Using VLA in non-standard environments**: Stick to `vector` for runtime sizes.
- **Comparing signed/unsigned**: `size()` returns `size_t` (unsigned). Be careful mixing with `int` in loops.

## Key Takeaways

- Arrays are fixed-size; vectors are dynamic and STL-friendly.
- Always use fast I/O when handling large input for arrays/vectors.
- `reserve()` prevents reallocations; `resize()` changes logical size.
- Prefer range-based `for` and iterators for clarity and safety.
- For 2D, nested vectors are easy; flat vectors are faster for large grids.
- Pass vectors by const reference to avoid unnecessary copies.

## Next Topic

[Functions and Recursion](functions-and-recursion.md)
