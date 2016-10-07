<!--?title Lowest Common Ancestor - O(sqrt(N)) and O(log N) with O(N) preprocessing -->

# Lowest Common Ancestor - O(sqrt(N)) and O(log N) with O(N) preprocessing

Given a tree G. Given queries of the form (V1, V2), for each query you need to find the lowest common ancestor (or least common ancestor), i.e. a vertex V that lies on the path from the root to V1 and the path from the root to V2, and the vertex should be the lowest. In other words, the desired vertex V is the most bottom ancestor of V1 and V2. It is obvious that their lowest common ancestor lies on a shortest path from V1 and V2. Also, if V1 is the ancestor of V2, V1 is their lowest common ancestor.

### The Idea of the Algorithm

Before answering the queries, we need to do **preprocessing**. Run DFS from the root using preorder traversal and it will build an array Order which store the visit order of the vertices (current vertex is added to the list at the entrance to the vertex and after return from its child (children)). It is clear that the size of this list will be O(N). We also need to build an array First[1..N] which stores the position of each vertex in the array such that Order[First[I]] = I. Also by using the DFS we can find the height of each node (distance from root to it) - H[1..N].

So how to answer the queries? Suppose the query is a pair of V1 and V2. Consider the elements in Order between indices First[V1] and First[V2]. It is easy to notice that in this range there are LCA(V1, V2) and many other peaks. However the LCA(V1, V2) can be uniquely determined, that is, the vertex with the lowest height.

Thus, to answer the query, we just need **to find the vertex with smallest height** in the array Order in the range from First[V1] to First[V2]. Thus, **the objective of finding LCA is reduced to the RMQ problem** (minimum in an interval problem).

If you use the sqrt-decomposition, it is possible to obtain a solution, answering each query in **O(sqrt(N))** with preprocessing in O(N) time.

If you use segment tree, you can answer each query in **O(log(N))** with preprocessing in O(N) time.

### Implementation

The implementation of described LCA algorithm is as follows:

```
typedef vector < vector<int> > graph;
typedef vector<int>::const_iterator const_graph_iter;


vector<int> lca_h, lca_dfs_list, lca_first, lca_tree;
vector<char> lca_dfs_used;

void lca_dfs (const graph & g, int v, int h = 1)
{
    lca_dfs_used[v] = true;
    lca_h[v] = h;
    lca_dfs_list.push_back (v);
    for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i)
        if (!lca_dfs_used[**i])
        {
            lca_dfs (g, **i, h+1);
            lca_dfs_list.push_back (v);
        }
}

void lca_build_tree (int i, int l, int r)
{
    if (l == r)
        lca_tree[i] = lca_dfs_list[l];
    else
    {
        int m = (l + r) >> 1;
        lca_build_tree (i+i, l, m);
        lca_build_tree (i+i+1, m+1, r);
        if (lca_h[lca_tree[i+i]] < lca_h[lca_tree[i+i+1]])
            lca_tree[i] = lca_tree[i+i];
        else
            lca_tree[i] = lca_tree[i+i+1];
    }
}

void lca_prepare (const graph & g, int root)
{
    int n = (int) g.size();
    lca_h.resize (n);
    lca_dfs_list.reserve (n**2);
    lca_dfs_used.assign (n, 0);

    lca_dfs (g, root);

    int m = (int) lca_dfs_list.size();
    lca_tree.assign (lca_dfs_list.size() ** 4 + 1, -1);
    lca_build_tree (1, 0, m-1);

    lca_first.assign (n, -1);
    for (int i = 0; i < m; ++i)
    {
        int v = lca_dfs_list[i];
        if (lca_first[v] == -1)
            lca_first[v] = i;
    }
}

int lca_tree_min (int i, int sl, int sr, int l, int r)
{
    if (sl == l && sr == r)
        return lca_tree[i];
    int sm = (sl + sr) >> 1;
    if (r <= sm)
        return lca_tree_min (i+i, sl, sm, l, r);
    if (l > sm)
        return lca_tree_min (i+i+1, sm+1, sr, l, r);
    int ans1 = lca_tree_min (i+i, sl, sm, l, sm);
    int ans2 = lca_tree_min (i+i+1, sm+1, sr, sm+1, r);
    return lca_h[ans1] < lca_h[ans2] ? ans1 : ans2;
}

int lca (int a, int b)
{
    int left = lca_first[a],
        right = lca_first[b];
    if (left > right)  swap (left, right);
    return lca_tree_min (1, 0, (int)lca_dfs_list.size()-1, left, right);
}

int main()
{
    graph g;
    int root;
    ... read the graph ...

    lca_prepare (g, root);

    for (;;)
    {
        int v1, v2; // the query
        int v = lca (v1, v2); // answer of the query
    }
}
```