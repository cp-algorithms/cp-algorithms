---
tags:
  - Original
---

# Parity of a Permutation

## Permutations
A **permutation** of size $n$ is a sequence containing each integer from $1$ to $n$ exactly once.  
Example: $[3,1,2]$ is a permutation of size $3$.

The **parity** (or sign) of a permutation classifies it as **even** or **odd**.  
Parity is a key invariant in competitive programming, particularly for **sorting problems**, **reachability**, and **puzzle/game states**.

---

## Definitions

### 1. Inversions
An **inversion** is a pair $(i, j)$ with $i < j$ and $p_i > p_j$.  
Let $K$ be the total number of inversions. The **sign** is:

$$
\text{sgn}(p) = (-1)^K
$$

- Even permutation: $K$ even  
- Odd permutation: $K$ odd

**Example:** $p = [3,1,2]$

| i | j | p_i | p_j | Inversion? |
|---|---|-----|-----|------------|
| 1 | 2 | 3   | 1   | Yes        |
| 1 | 3 | 3   | 2   | Yes        |
| 2 | 3 | 1   | 2   | No         |

$K=2 \implies$ **Even permutation**

---

### 2. Transpositions (Swaps)
A **transposition** swaps two elements. Any permutation can be sorted using transpositions.  
The parity of the number of swaps is **unique**:

- Even swaps → Even permutation  
- Odd swaps → Odd permutation

---

## Cycle Decomposition (O(n))

A permutation can be decomposed into **disjoint cycles**.  
- Cycle of length $L$ → $L-1$ swaps to sort  
- If there are $m$ cycles (including fixed points):

$$
N(\sigma) = n - m
$$

- Parity = $(n - m) \bmod 2$

### Algorithm (Cycle Method)

```cpp
#include <vector>

// Returns 0 if even, 1 if odd
int get_parity(int n, const std::vector<int>& p) {
    std::vector<bool> visited(n, false);
    int cycles = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            cycles++;
            int current = i;
            while (!visited[current]) {
                visited[current] = true;
                current = p[current] - 1; // Adjust for 1-based values
            }
        }
    }
    
    return (n - cycles) % 2; 
}
```
---

## Properties & Invariants

- **Single Swap:** Flips parity  
- **3-Cycle:** Preserves parity (equivalent to 2 swaps)  
- **Adjacent Swap:** Flips parity (changes inversions by odd number)  
- **Pairwise Swaps:** Preserves parity if even total swaps  

**Use:** Check reachability in sorting puzzles, 15-puzzle, and other operations-constrained problems.

--

## Practice Problems

- [CF1585D – Yet Another Sorting Problem](https://codeforces.com/problemset/problem/1585/D)  
  *Hint:* Array is sortable using 3-cycles only if parity matches the sorted array.

- [CF2191B – Quartet Swapping](https://codeforces.com/problemset/problem/2191/B)  
  *Hint:* Simultaneous swaps → even number of transpositions → parity preserved.

- [CSES – Permutations](https://cses.fi/problemset/task/1070)

---

## References

- [Wikipedia: Parity of a permutation](https://en.wikipedia.org/wiki/Parity_of_a_permutation)
