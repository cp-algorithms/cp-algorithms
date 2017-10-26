<!--?title Segment Tree-->

# Segment Tree

A Segment Tree is a data structure that allows answering range queries over an array effectively, while still being flexible enough to allow modifying the array. 
This includes finding the sum of consecutive array elements $a[l \dots r]$, or finding the minimum element in a such a range in $O(\log n)$ time. 
Between answering such queries the Segment Tree allows modifying the array by replacing one element, or even change the elements of a whole subsegment (e.g. assigning all elements $a[l \dots r]$ to any value, or add to all numbers in the subsegment a number). 

In general a Segment Tree is a very flexible data structure, and a huge amount of problems can be solved with it. 
Additionally it is also possible to apply more complex operations and answer more complex queries (see section "Advanced versions of the Segment Tree"). 
In particular the Segment Tree can be easily generalized for larger dimensions. 
For instance with a 2D Segment Tree you can answer sum or minimum queries over some subrectangle of a given matrix. However only in $O(\log^2 n)$ time. 

One important property of Segment Trees is, that they require only a linear amount of memory. The standard Segment Tree requires $4n$ nodes for working on an array of size of size $n$. 

## Description of the simplest Segment Tree

To start easy, we consider the simplest case of a Segment Tree. 
We want to answer sum queries efficiently. 
The formal definition of our task is: We have an array $a[0 \dots n-1]$, and the Segment Tree must be able to find the sum of elements between the indices $l$ and $r$ (i.e. computing the sum $\sum_{i=l}^r a[i]$), and also handle changing values of the elements in the array (i.e. respond to the assignment $a[i] = x$). 
The Segment Tree will be able to process both queries in $O(\log n)$ time.

### Structure of the Segment Tree

So, what is a Segment Tree?

We compute and store the sum of the elements of the whole array, i.e. the sum of the segment $a[0 \dots n-1]$. 
We then split the array into two halves $a[0 \dots n/2]$ and $a[n/2+1 \dots n-1]$ and compute the sum of each halve and store them. 
Each of these two halves in turn also split in half, their sums are computed and stored. 
And this process repeats until all segments reach length $1$. 
In other words we start with the segment $a[0 \dots n-1]$, split the current segment in half (if it has not yet become a segment containing a single element), and then calling the same procedure for both halves. 
For each such segment we store the sum of the numbers on it. 

We can say, that these segments form a binary tree: 
the root of this tree is the segment $a[0 \dots n-1]$, and each node (except leaf nodes) has exacly two child nodes. 
This is why the data structure is called "Segment Tree", even though in most implementations the tree is not constructed explicitly (see section Implementation).

From this short description of the data structure, we can already conclude that it only requires a linear number of nodes. 
The first level of the tree only contains a single note (the root node), the second level will contain two nodes, in the third it will contain four nodes, until the number of nodes reaches $n$. 
Thus the number of nodes in the worst case can be estimated by the sum $1 + 2 + 4 + \dots + n/4 + n/2 + n \lt 2n$. 

It is worth noting that whenever $n$ is not a power of two, not all levels of the Segment tree will be completely filled. 
For example with an array size of $n = 3$, the left child of the root will cover the segment $a[0 \dots 1]$, and therefore it will have two child nodes. 
However the right child of the root, which covers the segment $a[2 \dots 2]$, and therefore is a leaf node. 

This doesn't happen if $n$ is a power of two, therefore an easy fix is to just append values to the array until its lenght is a power of two. 
Notice, that this new length is smaller than $2n$, therefore we need less than $4n$ nodes in total. 
So this problem doesn't complicate the implementation by much.

The height of the Segment Tree is $O(\log n)$, because when going down from the root to the leaves the length of the segments decreases approximately by half. 

### Construction

The Segment tree can be constructed efficiently as follows:
We start at the bottom level, the leaf nodes. 
A node is a leaf node, if its corresponding segment covers only one value. 
Therefore we can simply copy the values of the elements $a[i]$. 
On the basis of those values, we can compute the sums of the previous level.
And on the basis of those, we can compute the sums of the previous, and repeat the procedure until we reach the root node. 
It is convenient to describe this operation recursively:
we start the construction at the root node and the construction procedure, if called on a not-leaf node, first recursively constructs the two child nodes, and than sums up the computed sums of these children. 
If it is called on a leaf node, it simply uses the value of the array. 

The time complexity of the construction is $O(n)$.

### Sum queries

For now we are going to answer sum queries. As an input we receive two integers $l$ and $r$, and we have to compute the sum of the segment $a[l \dots r]$ in $O(\log n)$ time. 

To do this, we will traverse the Segment Tree and use the precomputed sums of the segments.
Initially we start at the root node of the Segment Tree.
There are three possible cases. 

The easiest case is when the segment $a[l \dots r]$ is equal to the corresponding segment of the current node (e.g. $a[l \dots r] = a[0 \dots n-1]$), then we are finished and can return the precomputed sum that is stored in the node.

Alternatively the segment of the query falls completely into the domain of either the left or the right child.
Recall that the left child covers the segment $a[0 \dots n/2]$ and the right node covers the segment $a[n/2 + 1 \dots n - 1]$. 
In this case we can simply go to the child node, which contains the query segment, and execute the algorithm described here with that node. 

And then there is the last case, the query segment intersects with both children. 
In this case we have no other option as to make two recursive calls, one for each child.
First we go to the left child, compute a partial answer (i.e. the sum of values of the intersection between the segment of the query and the segment of the left child) using it, then go to the right child, compute the partial answer using it, and then combine the answers by adding them. 
In other words, if the left child represents the segment $a[L_1 \dots R_1]$ and the right child the segment $a[L_2 \dots R_2]$ (notice that $R_1 + 1 = L_2$), then we compute the sum query $a[l \dots R_1]$ using the left child, and the sum query $a[L_2 \dots r]$ using the right child. 

So processing a sum query is a function that recursively calls itself once with either the left or the right child (without changing the query boundaries), or twice, once for the left and once for the right child (by splitting the query into two subqueries). 
However recursive calls will not be done, whenever the boundaries of the current query segment coincides with the boundaries of the segment of the current node. 
In that case the answer will be the precomputed value of the sum of this segment, which is stored in the tree.

In other words, the calculation of the query is a traversal of the tree, which spreads through all necessary branches of the tree, and uses the precomputed sum values of the segments in the tree. 

Why is the complexity of this algorithm $O(\log n)$?
To show this complexity we look at each level of the tree. 
It turns out, that for each level we only visit not more than four nodes. 
And since the height of the tree is $O(\log n)$, we receive the desired running time. 

We can show that this assertion (at most four nodes each level) is true by induction.
At the first level, we only visit one node, the root node, so here we visit less than four nodes. 
Now lets look at any level.
By induction hypothesis, we visit at most four nodes. 
If we only visit at most two nodes, the next level has at most four nodes. That trivial, because each node can only cause at most two recursive calls. 
So lets assume that we visit three or four nodes. 
From those nodes, we will analyze the nodes in the middle more carefully. 
Since the sum query asks for the sum of a continous subarray, we know that segments corresponding to the visited nodes in the middle we be completely covered by the segment of the sum query. 
Therefore these nodes will not make any recursive calls. 
So only the most left, and the most right node will have the potential to make recursive calls. 
And those will only create at most four recursive calls, so also the next level will satisfy the assertion.
We can say that one branch approaches the left boundary of the query, and the second branch approaches the right one. 

Therefore we visit at most $4 \log n$ nodes in total, and that is equal to a running time of $O(\log n)$. 

In conclusion the query works by dividing the input segment into several sub-segments for which all the sums are already precomputed and stored in the tree. 
And if you do the partitioning the the right way, then we only need $O(\log n)$ such segments, which gives the effectiveness of the Segment Tree. 

### Update queries

Now we want to modify a specific element in the array, lets say we want to do the assignment $a[i] = x$. 
And we have to rebuild the Segment tree, such that it correspond to the new, modified array. 

This query is easier than the sum query. 
Each level of a Segment Tree forms a partition of the array. 
Therefore an element $a[i]$ only contributes to one segment from each level. 
So it turns out, that only $O(\log n)$ segments need to be updated. 

It is easy to see, that the update request can be implemented using a recursive function. 
The function gets passed the current tree node, and it recursively calls itself with one of the two child nodes (the one that contains $a[i]$ in its segment), and after that recomputes its sum value, similar how it is done in the build method (that is as the sum of its two children). 

### Implementation

The main consideration is how to store the Segment Tree.
Of course we can create Node objects, that store the boundaries of the segment, its sum and additionally also pointers to its child nodes.
However we will use a simple trick, to make this a lot more efficient. 
We only store the sums in an array, the sum of the root node at index 1, the sums of its two child nodes at indices 2 and 3, the sums of the children of those two nodes at indices 4 to 7, and so on. 
It is easy to see, that the left child of a node at index $i$ is stored at index $2i$, and the right one at index $2i + 1$. 

This simplifies the implementation a lot. 
Now we don't need to store the structure of the tree in memory. 
It is defined implicitely. 
We only need one array which contains the sums of all segments. 

As noted before, the array should have the size $4n$, not $2n$. 
The reason is, that this numbering doesn't work, when $n$ is not a power of 2. 
There will be some elements in the sum array, that doesn't correspond to any nodes in the actual tree. 
However this doesn't complicate the implementation, we only have to make sure that we have to make the array at least $4n$ elements long. 

So, we store the Segment Tree simply as an array $t[]$ with a size of four times the input size $n$:

```cpp
int n, t[4*MAXN];
```

The procedure for constructing the Segment Tree from a given array $a[]$ looks like this: 
it is a recursive function with the parameters $a[]$ (the input array), $v$ (the index of the current node/segment), and the boundaries $tl$ and $tr$ of the current segment. 
In the main program this function will be called with the parameters $v = 1$, $tl = 0$, and $tr = n - 1$. 

```cpp
void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
}
```

Further the function for answering sum queries is also a recursive function, which receives as parameters information about the current node (i.e. the index $v$ and the boundaries $tl$ and $tr$) and also the information about the boundaries of the query, $l$ and $r$. 
In order to simplify the code, this function always does two recursive calls, even if only one is necessary - in that case the superfluous recursive call will have $l > r$, and this can easily be caught using an additional check at the beginning of the function.

```cpp
int sum(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return sum(v*2, tl, tm, l, min(r, tm))
           + sum(v*2, tm+1, tr, max(l, tm+1), r);
}
```

Finally the update query. The function will also receive information about the current segment, and additionally also information about the index of the changing element as well as the new value. 

```cpp
void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = new_value;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_value);
        else
            update(v*2+1, tm+1, tr, pos, new_value);
        t[v] = t[v*2] + t[v*2+1];
    }
}
```

