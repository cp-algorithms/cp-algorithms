<!--?title Disjoint Set Union-->

# Disjoint Set Union

This article discusses the data structure **Disjoint Set Union** or **DSU**.
Often it is also called **Union Find** because of its two operations.

This data structure provides the following capabilities.
Initially there are several elements, each of which is a separate set.
In one operation you can combine any two sets, and you can also query in which set a specific element is.
The classical version also introduces a third operation, you can create a set from a new element.

Thus the basic interface of this data structure consists of only three operations:

- `make_set(x)` - adds a new element $x$, creates a new set consisting of this element
- `union_sets(x, y)` - brings together the two specified sets (the set in which the element $x$ is located, and the set in which the element $y$ is located.
- `find_set(x)` - returns the representative of the set that contains the element $x$.
This representative is an element of its corresponding set. It is selected in each set by the data structure itself (and can change over time, namely after `union_sets` calls).
This representative can be used to check if two elements are part of the same set of not. 
$x$ and $y$ are exactly in the same set, if $\text{find\_set}(x) == \text{find\_set}(y)$. Otherwise they are in different sets. 

As described in more detail later, the data structure allows you to do each of these operations in almost $O(1)$ time on average.

Also in one of the subsections an alternative structure of a DSU is explained, which allows to achieve the average complexity $O(\log n)$ for $m \ge n$ requests.
And $O(1)$ when $m >> n$ (i.e. $m$ much bigger then $n$). 

## Build an efficient data structure

We will store the sets in the form of **trees**: each tree will correspond to one set.
And the root of the tree will be the representative of the set.

For the implementation this means, that we will maintain an array `parent` that stores a reference to its immediate ancestor in the tree.

### Native implementation

We can already write the first implementation of the Disjoint Set Union data structure. 
It will be pretty inefficient at first, but later we can improve it using two techniques, so that it will take nearly constant time for each function call.

As we said, all the information about the sets of elements will be kept in an array `parent`. 

To create a new set (operation `make_set(x)`), we simply create a tree with root in the vertex `x`, meaning that it is its own ancestor. 

To combine two sets (operation `union_sets(x, y)`), we first find the representative of the set in which `x` is located, and the representative of the set in which `y` is located. 
If the representatives are identical, that we have nothing to do: the sets are already merged. 
Otherwise, we can simply specify that one of the representatives is the parent of the other representative - thereby combining the two trees.

Finally the implementation of the find representative function (operation `find_set(x)`): 
we simply climb the ancestors of the vertex `x` until we reach the root, i.e. that the reference to the ancestor leads to itself.
This operation is easily implemented recursively.

```cpp
void make_set(int x) {
    parent(x) = x;
}

int find_set(int x) {
    if (x == parent[x])
        return x;
    return find_set(parent[x]);
}

void union_sets(int x, int y) {
    x = find_set(x);
    y = find_set(y);
    if (x != y)
        parent[y] = x;
}
```

However this implementation is inefficient.
It is easy to construct an example, so that the chains degenerate into long chains.
In that case each call `find_set(x)` can take $O(n)$ time.

This is far away from the complexity that we want to have (nearly constant time). 
Therefore we will consider two optimizations that will allow to significantly accelerate the work.

### Path compression optimization

This optimization is designed for speeding up `find_set`.

If we call `find_set(x)` for some vertex `x`, we actually find the representative `p` for all vertices that are passed on the path between `x` and the actual representative `p`. 
The trick is to make the paths for all those nodes shorter, by setting the parent of each visited vertex to `p`. 

You can see the effect in the following image.
On the left is a tree, and on the right side is the modified tree after calling `find_set(7)`, which shortens the paths for the visited nodes 7, 5, 3 and 2.

![Path compression during call of $\text{find\_set}(7)$](&imgroot&/DSU_path_compression.png)

The new implementation of `find_set` is as follows:

```cpp
int find_set(int x) {
    if (x == parent[x])
        return x;
    return parent[x] = find_set(parent[x]);
}
```

The simple implementation does what was intended:
first find the representative of the set (root vertex), and the in the process of stack unwinding the visited nodes are attached directly to the representative.

This simple modification of the operation already achieves the time complexity $O(\log n)$ per call on average.
There is a second modification, that will make it even faster.

### Union by size / rank

In this optimization we will change the `union_set` operation. 
To be precise, we will change which tree gets attached to the other one.
In the native implementation the second tree always got attached to the first one.
In practice that can lead to trees containing chains of length $O(n)$. 
With this optimization we will avoid this by choosing very carefully which tree gets attached.

There are two possible approaches: 
In the first approach we as the size of the trees as rank, and in the second one we use the depth of the tree (more precisely, the upper bound on the tree depth, because the depth will get smaller when applying path compression in the `find_set` method).

In both approaches the essence of the optimization is the same: we attach the tree with the lower rank to the one with the bigger rank.

Here is the implementation of union by size:

```cpp
void make_set(int x) {
    parent(x) = x;
    size[x] = 1;
}

void union_sets(int x, int y) {
    x = find_set(x);
    y = find_set(y);
    if (x != y) {
        if (size[x] < size[y])
            swap(x, y);
        parent[y] = x;
        size[x] += size[y];
    }
}
```

And here is the implementation of union by rank based on the depth of the trees:

```cpp
void make_set(int x) {
    parent(x) = x;
    rank[x] = 0;
}

void union_sets(int x, int y) {
    x = find_set(x);
    y = find_set(y);
    if (x != y) {
        if (rank[x] < rank[y])
            swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y])
            rank[x]++;
    }
}
```

Both optimizations are equivalent in terms of time and space complexity. 
So in practice you can use any of them. 

### Time complexity

As mentioned before, if we combine both optimizations - path compression with union by size / rank - we will reach reach nearly constant time queries.
It turns out, that the final time complexity is $O(\alpha(n))$ on average, where $\alpha(n)$ is the inverse Ackerman function, which grows very slowly. 
In fact so slowly, that it doesn't exceed 4 for all reasonable $n$ (approximately $n <  10^{600}$).

We will not present a proof for this time complexity, since it is quite long and complicated. 

## Applications and various improvements

In this section we consider several applications of the data structure, both the trivial uses and some improvements to the data structure.

### Connected components in a graph

This is one of the obvious applications of DSU. 

Formally the problem is: 
initially we have an empty graph.
We have to add vertices and undirected edges, and answer queries of the form $(a, b)$ - "are the vertices $a$ and $b$ in the same connected component of the graph?"

Here we can directly apply the data structure, and get a solution that handles an addition of a vertex or an edge and a query in nearly constant time on average.

This application is quite important, because nearly the same problem appears in [Kruskal's algorithm for finding a minimum spanning tree](./graph/mst_kruskal.html).
Using DSU we can [improve](./graph/mst_kruskal_with_dsu.html) the $O(m \log n + n^2)$ complexity to $O(m \log n)$.

### Search for connected components in an image

One of the applications of DSU is the following task:
there is an image of $n \times m$ pixels.
Originally all are white, but then a few black pixels are drawn. 
You want to determine the size of each white connected component in the final image.

For the solution we simply iterate over all white pixels in the image, for each cell iterate over its four neighbors, and if the neighbor is white call `union_sets`.
Thus we will have a DSU with $n m$ nodes corresponding to image pixels.
The resulting trees in the DSU are the desired connected components.

The problem can also be solved by [DFS](./graph/depth-first-search.html) or [BFS](./graph/breadth-first-search.html), but the method described here has a small advantage: 
it can process the matrix row by row.

### Store additional information for each set

DSU allows you to easily store additional information pertaining to the sets.

A simple example is the size of the sets:
how to store the sizes was already described in the Union by size section (the information was stored by the current representative of the set).

In the same way - by storing it at the representative nodes - you can also store any other information about the sets.

### Compress hops along a segment / Problem of painting subarrays offline

One common application of the DSU is that if there is a set of vertices, and each vertex has an outgoing edge to another vertex. 
With DSU you can find the end point, to which we get after following all edges from a given starting point, in almost constant time.

A good example of this application it the **problem of painting subarrays**: 
We have a segment of length $L$, each element has the color 0.
We have to repaint the subarray $[l; r]$ with the color $c$ for each requests $(l, r, c)$.
At the end we want to find the final color of each cell.
We assume that we know all requests in advance, i.e. the task is offline.

For the solution we can make a DSU, which for each cell stores a link to the next unpainted cell. 
Thus initially each cell points to itself.
After painting one requested repaint of a segment, all cells from that segment will point to the cell after the segment.

Now to solve this problem, we consider the requests **in reverse order**: from last to first.
To execute the query, we take help from our DSU.
We find the left-most unpainted cell inside of a segment, repaint it, and with the pointer we move to the next empty cell to the right.

Here we can use the DSU with path compression, but we cannot use union by rank / size (because it is important who becomes the leader after the merge).
Therefore the complexity will be $O(\log n)$ per union (which is also quite fast).

Implementation:

```cpp
void init() {
    for (int i = 0; i < L; i++) {
        make_set(i);
    }
}

void process_query(int l, int r, int c) {
    for (int v = find_set(l); v <= r; v = find_set(v)) {
        answer[v] = c;
        parent[v] = v + 1;
    }
}
```

There is one optimization:
We can use **union by rank**, if we store the next unpainted cell in some array `end[]`.
Then we can merge two sets into one ranked according to their heuristics, and we obtain the solution in $O(\alpha(n))$.
