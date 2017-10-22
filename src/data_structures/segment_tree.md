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

### Sum queries

For now we are going to answer sum queries. As an input we receive two integers $l$ and $r$, and we have to compute the sum of the segment $a[l \dots r]$ in $O(\log n)$ time. 

To do this, we will traverse the Segment Tree and use the precomputed sums of the segments.
Initially we start at the root of the Segment Tree.
There are three possible cases. 

The easiest case is when the segment $a[l \dots r]$ is equal to the whole array $a[0 \dots n-1]$, then we are finished and can return the precomputed sum that is stored in the root node.

Alternatively the segment of the query falls completely into the damain of either the left or the right child.
Recall that the left child covers the segment $a[0 \dots n/2]$ and the right node covers the segment $a[n/2 + 1 \dots n - 1]$. 
In this case we can simply go to the child node, which contains the query segment, and apply the algorithm described here to that node. 

And then there is the last case, the query segment intersects with both children. 
In this case we have no other option to go to both children. 
First we go to the left child, compute a partial answer to the query using it, then go to the right child, compute the partial answer using it, and then combine the answers by adding them. 
In other words, if the left child represents the segment $a[L_1 \dots R_1]$ and the right child the segment $a[L_2 \dots R_1]$ (notice that $R_1 + 1 = L_2$), then we compute the sum query $a[l \dots R_1]$ using the left child, and the sum query $a[L_2 \dots r]$ using the right child. 

So processing a sum query is a function that recursively calls itself once with either the left or the right child (without changing the query boundaries), or twice, once for the left and once for the right child (by splitting the query into two subqueries). 
However recursive calls will not be done, whenever the current query coincides with the boundaries of the segment of the current node. 
Then the answer will be the precomputed value of the sum of this segment, which is stored in the tree.
kk
In other words, the calculation of the query is a traversal of the tree, which spreads through all necessary branches of the tree, and uses the precomputed sum values of the segments in the tree. 

Why is the complexity of this algorithm $O(\log n)$?
To show this complexity we look at each level of the tree. 
It turns out, that for each level we only visit not more than four nodes. 
And since the height of the tree is $O(\log n)$, we receive the desired running time. 

We can show that this allegation (maximal four nodes each level) is true. 
At the first level, we only visit one node, the root node. 
In the next level two nodes will be visit in the worst case.
But those two recursive calls will coexist. 
Both subqueries will touch the segment boundaries of the subnodes. 
So even if the queries on one child (or both children) calls again two nodes, only one each will be a real recursive call. The other one will end immediately. 
I.e. if the query $a[l \dots r]$ gets distributed on the two children (left child $a[L_1 \dots R_1]$ receives the subquery $a[l \dots R_1]$, right child $a[L_2 \dots R_2]$ receives the subquery $a[L_2 \dots r]$) and the left left child again makes to recursive calls to the nodes representing the segments $a[L_1 \dots R_1^']$ and $a[L_1^' \dots R_1]$. The left child receives the subquery $a[l \dots R_1^']$ and the right child receives the subquery $a[L_1^' \dots R_1]$. 
Now the right boundaries of the right query coincides with the boundaries of the right segment, and no recursive calls will be made from this node.
So in each level we only visit two nodes, that have the potential to make recursive calls.
We can say that one branch approaches the left boundary of the query, and the second branch approaches the right one. 
But in total, since each of the two potential nodes can make no more than two new calls, the number of visited segments each level is at most four.
Therefore we visit at most $4 \log n$ nodes in total, and that is equal to a running time of $O(\log n)$. 

In conclusion the query works by dividing the input segment into several sub-segments for which all the sums are already precomputed and stored in the tree. 
And if you do the partitioning the the right way, then we only need $O(\log n)$ such segments, which gives the effectiveness of the Segment Tree. 

### Update queries

Now we want to modify a specific element in the array, lets say we want to do the assignment $a[i] = x$. 
It turns out, that we only need to modify $O(\log n)$ segments.
To see this, we need to count how many segments contain the element $a[i]$. 
There is one leaf node, that coinsides with the element.
The parent of this leaf node, the parent of the parent, the parent of the parent of the parent, and so on. 
Exactly one leaf node and all its parents are effected by a modification of a single element in the array. 
And since the height of the tree is $O(\log n)$, exactly that many segments we have to change. 

To implement the modification efficiently, we act similar to the build process. We start with the child node and assign it to $x$. 
Then we can recompute the parent node, by using the precomputed values of its child nodes and repeat the process to all its parents. 
As an implementation, we can start with the root node, recursively call one of the child nodes, and afterwards fix the sum using the now correct precomputed values of the children. 

