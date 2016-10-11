<!--?title Randomized heap -->
#Randomized heap

Randomized heap - a heap, which through the using of a random number generator lets you perform all necessary operations in logarithmic expected time.

A heap is a binary tree, for every vertex is true that the value in the top of less than or equal value in all its descendants (this is a heap to a minimum; of course, you can define a heap symmetrically to the maximum). Thus, the root is always minimum heap.

A standard set of operations defined for the heaps, the following:

Adding an item
Finding the minimum
Removing the minimum (remove it from the tree and return of its value)
The merger of the two heaps (returns a heap containing elements of both heaps; duplicates are not removed)
Removal of any element (at a known position in the tree)

Randomized heap lets you perform all these operations within the expected time O (log N) with a very simple implementation.
