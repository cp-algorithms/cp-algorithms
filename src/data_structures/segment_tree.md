<!--?title Segment Tree-->

# Segment Tree

A Segment Tree is a data structure that allows answering range queries over an array effectively, while still being flexible enough to allow modifying the array. 
This includes finding the sum of consecutive array elements $a[l\dots r]$, or finding the minimum element in a such a range in $O(\log n)$ time. 
At the same time we can modify the array by replacing one element, or even change the elements of a whole subsegment (e.g. assigning all elements $a[l \dots r]$ to any value, or add to all numbers in the subsegment a number). 

In general a Segment Tree is a very flexible data structure, and a huge amount of problems can be solved with it. 
Additionally it is also possible to apply or answer more complex operations (see section "Advanced versions of the Segment Tree"). 
In particular the Segment Tree can be easily generalized for larger dimensions. 
For instance with a 2D Segment Tree you can answer sum or minimum queries over some sub-rectangle of a given matrix. However only in $O(\log^2 n)$ time. 

One important property of Segment Trees is, that they require only a linear amount of memory. The standard Segment Tree requires $4n$ nodes for working on an array of size of size $n$. 

## Description of the Segment Tree in the simplest version

To start easy, we consider the simplest case of a Segment Tree. 
We want to answer sum queries efficiently. 
The formal definition of our task is: We have an array $a[0\dots n-1]$, and the Segment Tree must be able to find the sum of elements between $l$ and $r$ (i.e. computing the sum $\sum_{i=l}^r a[i]$), and also handle changing values of the elements in the array (i.e. respond to the assignment $a[i] = x$). 
The Segment Tree has to process both queries in $O(\log n)$ time.

### Structure of the Segment Tree

So, what is a Segment Tree?

We compute and store the sum of the elements of the whole array, i.e. the sum of the segment $a[0\dots n-1]$. 
We then split the array into two halves $a[0\dots n/2]$ and $a[n/2+1 \dots n-1]$ and compute the sum of each halve and store them. 
Each of these two halves in turn also split in half, their sums are computed and stored. 
And this process repeats until all segments reach length $1$. 
In other words we start with the segment $[0; n-1]$, split the current segment in half (if it has not yet become a segment containing a single element), and then calling the same procedure for both halves. 
For each such segment we store the sum of the numbers on it. 

We can say, that these segments form a binary tree: 
the root of this tree is the segment $[0 \dots n-1]$, and each node (except leaf nodes) has exacly two child nodes. 
This is why the data structure is called "Segment Tree", even though in most implementations the tree is not constructed explicitly. 

From this short description of the data structure, we can already conclude that it only requires a linear number of nodes. 
The first level of the tree only contains a single note (the root node), the second level will contain two nodes, in the third it will contain four nodes, until the number of nodes reaches $n$. 
Thus the number of nodes in the worst case can be estimated by the sum $1 + 2 + 4 + \dots + n/4 + n/2 + n \lt 2n$. 

It is worth noting that whenever $n$ is not a power of two, not all levels of the Segment tree will be completely filled. 
For example with an array size of $n = 3$, the left child of the root will cover the segment $[0 \dots 1]$, and therefore it will have two child nodes. 
However the right child of the root, which covers the segment $[2 \dots 2]$, and therefore is a leaf node. 
It doesn't complicate the implementation by much, but we have to keep this fact in our minds.

The height of the Segment Tree is $O(\log n)$, because when going down from the root to the leaves the length of the segments decrease approximately by half. 

### Construction

The Segment tree can be constructed efficiently as follows:
We start at the bottom level, the leaf nodes. For those we can simply copy the values of the elements $a[i]$ into the corresponding nodes. 
Then we compute the values of the next level as the sums of child values. 
And then computing the values of one more level and so on. 
It is convenient to describe this operation recursively: we start the construction at the root node and the construction procedure, if called on a not-leaf node, first recursively constructs the two child nodes, and than sums up the computed values of these children. 
If it is called on a leaf node, it simply uses the value of the array. 

The time complexity of the construction is $O(n)$.
