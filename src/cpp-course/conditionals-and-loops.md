---
title: Conditionals and Loops
tags:
  - Course
---

# Conditionals and Loops

## Conditionals

### if-else

```cpp
if (x > 0) {
    cout << "Positive\n";
} else if (x < 0) {
    cout << "Negative\n";
} else {
    cout << "Zero\n";
}
```

### Ternary Operator

```cpp
int max_val = (a > b) ? a : b;
```

### switch

```cpp
switch (op) {
    case 1: cout << "Sum\n"; break;
    case 2: cout << "Subtraction\n"; break;
    default: cout << "Other\n";
}
```

## Loops

### for

```cpp
for (int i = 0; i < n; i++) {
    cout << i << "\n";
}
```

### while

```cpp
int i = 0;
while (i < n) {
    cout << i << "\n";
    i++;
}
```

### do-while

```cpp
int x;
do {
    cin >> x;
} while (x != 0);
```

## Next Topic

[Arrays and Vectors](arrays-and-vectors.md)
