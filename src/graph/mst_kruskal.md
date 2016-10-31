<!--?title Minimum spanning tree - Kruskal's algorithm -->

# Minimum spanning tree - Kruskal's algorithm

Given a weighted undirected graph. We want to find a subtree of this graph which connects all vertices (i.e. a spanning tree), and is having the least weight (i.e. the sum of weights of all the edges is minimum) of all possible spanning trees. This spanning tree is called a minimum spanning tree.

This article will discuss few important facts associated with minimum spanning trees, and then will give the simplest implementation of Kruskal's algorithm for finding minimum spanning tree.

## Properties of the minimum spanning tree

* A minimum spanning tree of a graph is unique, if the weight of all the edges are distinct. Otherwise, there may be multiple minimum spanning trees.
    (Specific algorithms typically output one of the possible minimum spanning trees).
* Minimum spanning tree is also the tree with minimum product of weights of edges.
    (It can be easily proved by replacing the weights of all edges to their logarithms)
* In a minimum spanning tree of a graph, the maximum weight of an edge is the minimum possible from all possible spanning trees of that graph.
    (This follows from the validity of Kruskal's algorithm).
* The maximum spanning tree (spanning tree with the sum of weights of edges being maximum) of a graph can be obtained similarly to that of the minimum spanning tree, by changing the signs of the weights of all the edges to their opposite and then applying any of the minimum spanning tree algorithm. 

## Kruskal's algorithm

This algorithm was described by Joseph Bernard Kruskal, Jr. in 1956.

Kruskal's algorithm initially places all the nodes of the original graph isolated from each other, to form a forest of single node trees, and then gradually merges these trees, combining at each iteration any two of all the trees with some edge of the original graph. Before the execution of the algorithm, all edges are sorted by weight (in non-decreasing order). Then begins the process of unification: pick all edges from the first to the last (in sorted order), and if the ends of the currently picked edge belong to different subtrees, these subtrees are combined, and the edge is added to the answer. After iterating through all the edges, all the vertices will belong to the same sub-tree, and we will get the answer.

## The simplest implementation

The following code directly implements the algorithm described above, and is having $O(M log N + N^2)$ time complexity. Sorting edges require $O(M log N)$ operations. Information regarding the subtree to which a vertex belongs is maintained with the help of an array tree_id[ ] - for each vertex $i$, tree_id[i] stores the number of the tree , to which $i$ belongs. For each edge, whether it belongs to the ends of different trees, can be determined in $O(1)$, . Finally, the union of the two trees is carried out in $O​​(N)$ by a simple pass through tree_id[ ] array. Given that total merge operations are $N-1$, we obtain the asymptotic behavior of $O(M log N + N^2)$.

```cpp
int m;
vector < pair < int, pair < int, int > > > g (m);  //  stores edges (weight - the vertex 1 - vertex 2)

int cost = 0;
vector < pair < int, int > > res;

sort (g.begin(), g.end()); // sorting edges

vector < int > tree_id (n);

for (int i = 0; i < n; ++i)
    tree_id[i] = i;
    
for (int i = 0; i < m; ++i)
{ 
    int a = g[i].second.first, b = g[i].second.second, l = g[i].first;
    
    if (tree_id[a] != tree_id[b])
    {
        cost += l;
        res.push_back (make_pair (a, b));

        int old_id = tree_id[b], new_id = tree_id[a];
         
        for (int j = 0; j < n; ++j)
            if (tree_id[j] == old_id)
                tree_id[j] = new_id;
    }
} 
```

## Improved implementation

We can use the **Disjoint Set Union** (DSU) data structure to write faster implementation of the Kruskal's algorithm with an asymptotic complexity of about $O(M log N)$. [This article details such approach](./graph/mst_kruskal_with_dsu.html).

##Practice Problems
- [SPOJ - Koicost](http://www.spoj.com/problems/KOICOST/)
- [SPOJ - MaryBMW](http://www.spoj.com/problems/MARYBMW/)
- [Codechef - Fullmetal Alchemist](https://www.codechef.com/ICL2016/problems/ICL16A)
- [Codeforces - Edges in MST](http://codeforces.com/contest/160/problem/D)
