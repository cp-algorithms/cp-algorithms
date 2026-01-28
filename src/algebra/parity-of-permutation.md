---
tags:
  - Original
---
# Permutations

A **permutation** of size $n$ is a sequence containing each integer from $1$ to $n$ exactly once.
Example: $[3,1,2]$ is a permutation of size $3$.

Permutations are fundamental in competitive programming, appearing in sorting problems, combinatorics, and group theory. This article covers their key properties, including inversions, parity, cycle decomposition, and lexicographical rank.

---

## 1. Inversions

An **inversion** is a pair of indices $(i, j)$ such that $i < j$ and $p_i > p_j$. The number of inversions is a measure of how "unsorted" a permutation is.

### Counting Inversions
A naive approach checks all pairs in $O(n^2)$. However, we can count inversions in $O(n \log n)$ using **Merge Sort** or a **Fenwick Tree (Binary Indexed Tree)**.

Below is an implementation using **Merge Sort**. The idea is that during the merge step, if we pick an element from the right half, it forms an inversion with all remaining elements in the left half.

```cpp
#include <vector>
#include <iostream>

using namespace std;

long long merge_and_count(vector<int>& p, int left, int mid, int right) {
    vector<int> left_sub(p.begin() + left, p.begin() + mid + 1);
    vector<int> right_sub(p.begin() + mid + 1, p.begin() + right + 1);

    int i = 0, j = 0, k = left;
    long long inversions = 0;

    while (i < left_sub.size() && j < right_sub.size()) {
        if (left_sub[i] <= right_sub[j]) {
            p[k++] = left_sub[i++];
        } else {
            // right_sub[j] is smaller than left_sub[i], implying it is also
            // smaller than all remaining elements in left_sub.
            p[k++] = right_sub[j++];
            inversions += (left_sub.size() - i);
        }
    }

    while (i < left_sub.size()) p[k++] = left_sub[i++];
    while (j < right_sub.size()) p[k++] = right_sub[j++];

    return inversions;
}

long long count_inversions(vector<int>& p, int left, int right) {
    if (left >= right) return 0;
    int mid = left + (right - left) / 2;
    long long count = count_inversions(p, left, mid);
    count += count_inversions(p, mid + 1, right);
    count += merge_and_count(p, left, mid, right);
    return count;
}
```
## 2. Parity of a Permutation

The **parity** (or sign) of a permutation classifies it as **even** or **odd**. This is a key invariant in puzzles like the 15-puzzle.

Let $K$ be the total number of inversions. The **sign** is defined as:

$$
\text{sgn}(p) = (-1)^K
$$

- **Even Permutation:** $K$ is even.
- **Odd Permutation:** $K$ is odd.

For example, $p = [3,1,2]$ has 2 inversions $( (3,1) \text{ and } (3,2) )$, so it is an **even** permutation.

### Properties
1.  **Single Swap:** A single swap of any two elements changes the parity of the permutation.
2.  **Transpositions:** If a permutation can be sorted using $k$ swaps, then the parity of $k$ is the same as the parity of the inversion count.

---

## 3. Cycle Decomposition

Any permutation can be decomposed into **disjoint cycles**. This can be visualized as a directed graph where edges go from $i \to p_i$.

**Example:**
For $p = [4, 1, 6, 2, 5, 3]$:
- $1 \to 4 \to 2 \to 1$ (Cycle 1)
- $3 \to 6 \to 3$ (Cycle 2)
- $5 \to 5$ (Fixed point / Cycle 3)

The permutation consists of 3 disjoint cycles.

### Swaps and Cycles
A crucial property of permutations involves how a swap affects the cycle decomposition. Let $C$ be the number of cycles in a permutation. If we swap two elements $u$ and $v$:

1.  **If $u$ and $v$ are in the same cycle:** The cycle splits into two disjoint cycles. ($C \to C+1$)
2.  **If $u$ and $v$ are in different cycles:** The two cycles merge into one. ($C \to C-1$)

In both cases, the number of cycles changes by exactly 1. This reinforces the parity definition:
$$\text{Parity} \equiv (N - C) \pmod 2$$
Since a swap changes $C$ by $\pm 1$, it changes $(N-C)$ by $\pm 1$, flipping the parity.

### Cycle Decomposition Code

```cpp
// Returns the number of cycles. 
// Parity is (n - cycles) % 2.
int count_cycles(int n, const std::vector<int>& p) {
    std::vector<bool> visited(n + 1, false);
    int cycles = 0;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            cycles++;
            int current = i;
            while (!visited[current]) {
                visited[current] = true;
                current = p[current-1]; // Assuming 1-based permutation in 0-based vector
            }
        }
    }
    return cycles;
}
```
## 4. Lexicographical Rank

The **rank** of a permutation is its position in the lexicographically sorted list of all $n!$ permutations of the same elements.

For a permutation $p$ of size $n$, the rank (0-indexed) is given by:
$$\text{Rank} = \sum_{i=0}^{n-1} (\text{count of smaller elements to the right}) \times (n - 1 - i)!$$

**Example:** $p = [2, 1, 3]$
1.  **Pos 0 (Value 2):** Elements to the right $\{1, 3\}$. Smaller than 2 is $\{1\}$ (Count: 1).
    - Add $1 \times 2! = 2$.
2.  **Pos 1 (Value 1):** Elements to the right $\{3\}$. Smaller than 1 is $\emptyset$ (Count: 0).
    - Add $0 \times 1! = 0$.
3.  **Pos 2 (Value 3):** No elements to the right.
    - Add $0 \times 0! = 0$.

Total Rank = $2 + 0 + 0 = 2$.
(The permutations are $[1,2,3], [1,3,2], \mathbf{[2,1,3]}, [2,3,1]...$)

**Implementation Note:**
To efficiently calculate the "count of smaller elements to the right," we can use a Fenwick Tree (BIT) or Segment Tree in $O(n \log n)$. For small $n$, a brute force $O(n^2)$ is sufficient.

---

## Practice Problems

- [CF 1585D – Yet Another Sorting Problem](https://codeforces.com/problemset/problem/1585/D)
- [CF 2191B – Quartet Swapping](https://codeforces.com/problemset/problem/2191/B)
- [CSES – Permutations](https://cses.fi/problemset/task/1070)
- [CSES – Creating Strings II](https://cses.fi/problemset/task/1715) (Related to rank/combinatorics)

---

## References

- [Wikipedia: Parity of a permutation](https://en.wikipedia.org/wiki/Parity_of_a_permutation)
- [Wikipedia: Inversion (discrete mathematics)](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics))
