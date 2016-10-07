#Treap

Treap is a data structure which are combains binary tree and binary heap (that's why this structure called Treap => tree + heap).

In more strict way, Treap is a data structure that stores pair (X,Y) in a form of binary tree, so that it is a binary search tree by X and binary heap by Y.
Assuming that all X and all Y are different, we find that if a some tree element contains (X0, Y0), then all elements in the left subtree have X < X0 and all elements in right subtree have X > X0, and also left and right subtree have Y < Y0

Treap been proposed Siedel and Aragon in 1989.

##Advantages of such data organisation

In the application, which we are considering (we consider deramidy as a Treap) only X values are the keys (also at same time they are values stored in data structure) and Y values  are called **priorities**. If there were no **priorities**, it would be a normal binary tree by the X and a set of X could be correspond to a lot of trees, some of which are degenerate (eg, in the form of a chain), and therefore are extremely slow (the main operations would be carried out of O(N)).

At the same time, priorities allow you to uniquely specify the tree that will be build (of course, does not depend on the order of addition of components)(this is proved by the corresponding theorem). Now it is obvious that if you choose priorities accident, then, we will achieve the construction of degenerate trees in the average case, which will provide the asymptotic behaviour of O (log N) on average. Hence it is clear that the name of another data structure - a **randomized binary search tree**.

##Operations
So, Treap have next operations:
- **Insert(X,Y)** - operation will take in average O(log N).
  It performs the addition of a new element in the tree. The variant in which Y priority value is not transmitted function and chosen randomly (but bear in mind that it should not coincide with any other Y in the tree).
- **Search (X)** - it has O(log N) mark in average.
  Searches for an item with the specified key X. Implemented in exactly the same way as for an ordinary binary tree.
- **Erase (X)** - in average - O(log N).
  Searches for an item and remove it from the tree.
- **Build (X1, ... Xn)** - O(N).
  Build a tree from a list of values. This operation can be implemented in linear time (assuming that the values of X1, ... Xn sorted),
  but here, this implementation will not be discussed. Here will be used a simplified variant with serial calls of Insert operation.
- **Union (T1, T2)** - in average - O(Mlog(n/m)).
  It merges two trees, on the assumption that all the elements are different (however, this operation can be realized with the same asymptotic behavior, if the merger is necessary to remove duplicate entries).
- **Intersect (T1, T2)** - in average for O(log N).
  Finds the intersection of two trees (ie, their common elements). Here the implementation of this operation will not be considered.

In  addition, due to the fact that the Cartesian tree is a binary searching tree, some operation are applicable to it such as finding the K-th largest element, and, on the contrary, the searching of item number.
