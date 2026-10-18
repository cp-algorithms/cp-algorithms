---
title: Conditionals and Loops
tags:
  - Course
---

# Conditionals and Loops

Control flow structures allow programs to make decisions and repeat actions. Mastering these is fundamental to solving algorithmic problems efficiently and correctly.

## Conditional Statements

### `if`, `else if`, `else`

The `if` statement executes a block of code only when a condition evaluates to `true`. You can chain multiple conditions using `else if`, and provide a fallback with `else`.

```cpp
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x;
    cin >> x;
    
    if (x > 0) {
        cout << "Positive\n";
    } else if (x < 0) {
        cout << "Negative\n";
    } else {
        cout << "Zero\n";
    }
    
    return 0;
}
```

**Best practice:** Keep conditions simple and readable. For complex logical expressions, consider extracting variables or adding parentheses for clarity.

### Nested `if` Statements

You can nest `if` statements when decisions depend on multiple criteria:

```cpp
if (age >= 18) {
    if (has_id) {
        cout << "Allowed\n";
    } else {
        cout << "ID required\n";
    }
} else {
    cout << "Not allowed\n";
}
```

However, deep nesting can reduce readability. Often, combining conditions with logical operators (`&&`, `||`, `!`) is cleaner.

```cpp
if (age >= 18 && has_id) {
    cout << "Allowed\n";
} else {
    cout << "Not allowed\n";
}
```

### Ternary Operator (`?:`)

The ternary operator provides a concise way to assign a value based on a condition. It's ideal for simple assignments, but avoid overusing it for complex logic.

```cpp
int a, b;
cin >> a >> b;
int max_val = (a >= b) ? a : b;
cout << "Max: " << max_val << "\n";
```

You can also use it inline in output:

```cpp
cout << (a % 2 == 0 ? "Even" : "Odd") << "\n";
```

### `switch` Statement

The `switch` statement is efficient and readable when comparing a single integer/character expression against multiple constant values.

```cpp
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int op;
    cin >> op;
    
    switch (op) {
        case 1:
            cout << "Addition\n";
            break;
        case 2:
            cout << "Subtraction\n";
            break;
        case 3:
            cout << "Multiplication\n";
            break;
        case 4:
            cout << "Division\n";
            break;
        default:
            cout << "Invalid operation\n";
            break;
    }
    
    return 0;
}
```

**Important notes:**

- Always include `break` after each `case` unless you intentionally want fall-through (rare and should be documented).
- The `default` case handles values not matched by any `case`.
- `switch` works with `int`, `char`, `enum`, and other integral types (not with `string` or floating point).

## Loops

Loops allow repetitive execution of code until a condition is met. Choosing the right loop type improves clarity and efficiency.

### `for` Loop

The `for` loop is ideal when the number of iterations is known in advance (e.g., iterate over `n` elements).

```cpp
int n;
cin >> n;
for (int i = 0; i < n; ++i) {
    cout << i << "\n";
}
```

The `for` header consists of three parts: initialization (`int i = 0`), condition (`i < n`), and increment/decrement (`++i`). Using prefix `++i` is a small optimization habit (avoids creating a temporary in some contexts, though negligible here).

### Range-based `for` Loop (C++11+)

Range-based `for` is concise and safe when iterating over containers like `vector`, `array`, or strings. It avoids index errors and is highly readable.

```cpp
#include <vector>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> v = {1, 2, 3, 4, 5};
    for (int val : v) {
        cout << val << " ";
    }
    cout << "\n";
    
    // To modify elements, use reference
    for (int &val : v) {
        val *= 2;
    }
    
    return 0;
}
```

Use `const int &val` when iterating by reference but not modifying:

```cpp
for (const int &val : v) {
    cout << val << "\n";
}
```

### `while` Loop

The `while` loop is best when the number of iterations is unknown beforehand and depends on a runtime condition (e.g., reading input until end-of-file or a sentinel value).

```cpp
int x;
while (cin >> x) {
    if (x == 0) break; // exit on sentinel
    cout << x * x << "\n";
}
```

This example reads integers until input ends or `0` is encountered. Using `while (cin >> x)` is a common idiom for handling input in judges.

### `do-while` Loop

The `do-while` loop guarantees at least one execution, since the condition is checked after the body. It's useful for input validation or menus.

```cpp
int choice;
do {
    cout << "Enter 1 to continue, 0 to exit: ";
    cin >> choice;
    // process...
} while (choice != 0);
```

## Loop Control Statements

### `break`

Exits the innermost loop immediately. Commonly used to stop searching or to handle edge cases.

```cpp
for (int i = 0; i < n; ++i) {
    if (a[i] == target) {
        cout << "Found at index " << i << "\n";
        break;
    }
}
```

### `continue`

Skips the remaining statements in the current iteration and proceeds to the next iteration.

```cpp
for (int i = 0; i < n; ++i) {
    if (a[i] < 0) continue; // skip negative numbers
    cout << a[i] << "\n";
}
```

## Common Patterns in Competitive Programming

### Reading input until EOF

```cpp
int val;
while (cin >> val) {
    // process val
}
```

### Iterating over ranges

```cpp
int n; cin >> n;
for (int i = 1; i <= n; ++i) {
    // 1-based indexing is common in CP
}
```

### Flag-based search

```cpp
bool found = false;
for (int i = 0; i < n && !found; ++i) {
    if (a[i] == x) found = true;
}
```

## Performance Considerations

- Avoid unnecessary computations inside tight loops. Move constant expressions outside.
- Prefer simple loop conditions (comparisons to integers/indices).
- With `-O2`, the compiler optimizes loops heavily; focus on algorithmic efficiency first.
- For very large `n` ($10^8$), even simple loops can be borderline in time; usually $10^9$ simple operations are not allowed. Aim for $O(n \log n)$ or better for $n \ge 10^5$.

## Key Takeaways

- Use `if-else` for branching logic, `switch` for fixed constant choices.
- Prefer `for` when count is known, `while` when count is unknown, `do-while` for at-least-once logic.
- Range-based `for` is cleaner for container iteration.
- `break` and `continue` are powerful but should be used judiciously to maintain readability.
- Combine fast I/O with efficient control flow for optimal performance in judges.

## Next Topic

[Arrays and Vectors](arrays-and-vectors.md)
