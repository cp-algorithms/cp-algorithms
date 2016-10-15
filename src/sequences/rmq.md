<!--?title Range Minimum Query -->

# Range Minimum Query

You are given an array $A[1..N]$. You have to answer incoming queries of the form $(L, R)$ which ask to find the minimum element in array A between positions L and R, inclusive.

RMQ can appear in problems directly or be applied to other tasks, including [Lowest Common Ancestor](../graph/lca.html).

## Solution

RMQ task is solved by using appropriate data structures.

From the list of data structures described on this site, you can choose:

- [Sqrt-decomposition]() - answers each query in $O(\sqrt{N})$, preprocessing done in $O(N)$.
  Pros: a very simple data structure. Cons: worse complexity.
- [Segment tree]() - answers each query in $O(\log N)$, preprocessing done in $O(N)$.
  Pros: good runtime complexity. Cons: larger amount of code compared to the other data structures.
- [Fenwick tree](../data_structures/fenwick.html) - answers each query in $O(\log N)$, preprocessing done in $O(N \log N)$.
  Pros: the shortest code, good runtime complexity. Cons: Fenwick tree can only be used for queries with $L = 1$, so it is not applicable to many problems.

Note: Preprocessing is the preliminary processing of the given array by building corresponding data structure for it.

If the array $A$ might change during the runtime (i.e. there will also be queries to change values in some interval), the problem can only be solved by [Sqrt-decomposition]() or [Segment tree]().
