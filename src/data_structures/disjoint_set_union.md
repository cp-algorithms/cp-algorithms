<!--?title Disjoint Set Union-->

# Disjoint Set Union

This article discusses the data structure **Disjoint Set Union** or **DSU**.
Often it is also called **Union Find** because of its two important functions.

This data structure provides the following two operations.
Initially there are several sets, each of which contains exactly one element.
In one operation you can merge any two sets, and you can also query which set now contains a certain element.
The classical version also introduces a third operation, you can create a set from a new element.

Thus the basic interface of this data structure consists of only three operations:

- `make_set(x)` - adds a new element $x$, placing it in a new set consisting.
- `union_sets(x, y)` - merges the two specified sets (the set in which the element $x$ is located, and the set in which the element $y$ is located.
- `find-set(x)` - returns the representative of the set that contains the element $x$.
This representative is selected in each set by the data structure itself (and can change over time, namely after `union_sets` calls).


