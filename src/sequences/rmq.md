<!--?title RMQ Task -->

# RMQ Task

Given an array A[1..N]. You have to answer the queries of the form (L, R), asking the minimum value in array A from position L to position R.

### Application

The RMQ problem can be applied in a variety of problems, including:

- [LCA (Lowest Common Ancestor)]()

### Options

The RMQ task can be solved by using some data structures.


From the described data structures on this site, you can choose:

- [Sqrt-decomposition]() - answers each query in O(sqrt(N)) with preprocessing in O(N). It is a very simple data structure, but it is slower.
- [Segment tree]() - answers each query in O(log N) with preprocessing in O(N). It has good runtime complexity, but it has larger amount of code compared to the other data structures.
- [Fenwick tree](../data_structures/fenwick.html) - answers each query in O(log N) with preprocessing in O(N log N). It has the smallest amount of code and works faster, but Fenwick tree can only be used to the queries with L = 1, so it is not applicable to many problems.

Note: "Preprocessing" is the preliminary processing of array A by building a data structure for the corresponding array.

Now assume that array A may be changed in the process (i.e. there will also be queries to change values in some interval [L;R]). Then, the resulting problem can only be solved by Sqrt-decomposition or Segment tree.
