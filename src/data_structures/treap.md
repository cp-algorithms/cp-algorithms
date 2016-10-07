#Treap

Treap is a data stucture which are combains binary tree and binary heap (thats why this structure called treap - tree + heap).

In more strict way, treap is a data structure that stores pair (X,Y) in a form of binary tree, so that it is a binary search tree by X and binary heap by Y.
Assuming that all X and all Y are different, we find that if a some tree element contains (X0, Y0), then all elements in the left subtree of X < X0 and all elements in right subtree X > X0, and also left and right subtree have Y < Y0

Treap been proposed Siedel and Aragon in 1989.

##Advantages of such data organisation

In the application, which we are considering (we consider deramidy as a Treap) only X are the keys (also at same tibe values stored in data structure) and Y which are called priorities. If there were no **priorities**, it would be a normal binary tree by the X and a set of X could be correspond to a lot of rees, some of which are degenerate(eg, in the form of a chain), and therefore is extremely slow (the main operations would be carried out of O(N)).
At the same time, priorities allow you lo uniquely specify the tree that will be build (of course, does not depend on the order of addition of components)(this is proved be the sorresponding theorem). Now it is obvious that if you choose priorities accident, then, we will achive the construction of degenerate trees in the average case, which will provide the asymptoic behaviour of O (log N) on average. Hence it is clear that the name of another data structure - a randomized binary serach tree.

##Operations
So, Treap have next operations:
- **Insert(X,Y)** - operation will take in average O (log N).
  It performs the addition of a new element in the tree. The variant in which Y priority value is not transmitted function and chosen randomly (but bear in mind that it should not coincide with any other Y in the tree).
  
