<!--?title Lowest Common Ancestor - O(sqrt(N)) and O(log N) with O(N) preprocessing -->

# Lowest Common Ancestor - $O(\sqrt{N})$ and $O(log\ N)$ with $O(N)$ preprocessing

Given a tree $G$. Given queries of the form $(v_1, v_2)$, for each query you need to find the lowest common ancestor (or least common ancestor), i.e. a vertex $v$ that lies on the path from the root to $v_1$ and the path from the root to $v_2$, and the vertex should be the lowest. In other words, the desired vertex $v$ is the most bottom ancestor of $v_1$ and $v_2$. It is obvious that their lowest common ancestor lies on a shortest path from $v_1$ and $v_2$. Also, if $v_1$ is the ancestor of $v_2$, $v_1$ is their lowest common ancestor.

### The Idea of the Algorithm

Before answering the queries, we need to do **preprocessing**. Run DFS from the root using preorder traversal and it will build an array $list$ which stores the visit order of the vertices (current vertex is added to the list at the entrance to the vertex and after return from its child (children)). This may also be called an euler tour of the tree. It is clear that the size of this list will be $O(N)$. We also need to build an array $first[1...N]$ which stores, for each vertex $i$, its first occurance in $list$. That is, the first position in $list$ such that $list[first[i]] = i$. Also by using the DFS we can find the height of each node (distance from root to it) and store it at $height[1...N]$.

So how to answer the queries? Suppose the query is a pair of $v_1$ and $v_2$. Consider the elements in $list$ between indices $first[v_1]$ and $first[v_2]$. It is easy to notice that in this range there are $LCA(v_1, v_2)$ and many other peaks. However the $LCA(v_1, v_2)$ can be uniquely determined, that is, the vertex with the lowest height.

Let's illustrate this idea. Consider the following graph:

<div style="text-align:center" markdown="1">

![Example graph](&imgroot&/graph-lca.png "Example graph")

</div>

In this example:

$$\begin{eqnarray}
list    &=& \\{1,2,1,3,4,3,5,3,6,7,6,3,1\\} \\\\\\
height  &=& \\{1,2,1,2,3,2,3,2,3,4,3,2,1\\} \\\\\\
\end{eqnarray}$$

Thus, to answer the query, we just need **to find the vertex with smallest height** in the array $list$ in the range from $first[v_1]$ to $first[v_2]$. Thus, **the objective of finding LCA is reduced to the RMQ problem** (minimum in an interval problem).

If you use the sqrt-decomposition, it is possible to obtain a solution, answering each query in $O(\sqrt{N})$ with preprocessing in $O(N)$ time.

If you use segment tree, you can answer each query in $O(log\ N)$ with preprocessing in $O(N)$ time.

### Implementation

The implementation of described LCA algorithm is as follows, using a segment tree:

```
typedef vector < vector<int> > graph;
typedef vector<int>::const_iterator const_graph_iter;

vector<int> lca_height, lca_dfs_list, lca_first, lca_tree;
vector<bool> lca_dfs_used;

// a preprocessing dfs to find the euler tour list and the height of each vertex
void lca_dfs(const graph & g, int v, int h = 1)
{
    lca_dfs_used[v] = true;
    lca_height[v] = h;
    lca_dfs_list.push_back(v);
    for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i) {
        int& next = **i;
        if (!lca_dfs_used[next]) {
            lca_dfs(g, next, h+1);
            lca_dfs_list.push_back(v);
        }
    }
}

// build the segment tree
void lca_build_tree(int i, int l, int r)
{
    if (l == r)
        lca_tree[i] = lca_dfs_list[l];
    else
    {
        int m = (l + r) >> 1;
        lca_build_tree(2*i, l, m);
        lca_build_tree(2*i+1, m+1, r);
        if (lca_height[lca_tree[2*i]] < lca_height[lca_tree[2*i+1]])
            lca_tree[i] = lca_tree[2*i];
        else
            lca_tree[i] = lca_tree[2*i+1];
    }
}

// the preprocessing function
void lca_prepare(const graph & g, int root)
{
    int n = (int) g.size();
    lca_height.resize(n);
    lca_dfs_list.reserve(n**2);
    lca_dfs_used.assign(n, 0);

    lca_dfs(g, root);

    int m = (int) lca_dfs_list.size();
    lca_tree.assign(m * 4 + 1, -1);
    lca_build_tree(1, 0, m-1);

    lca_first.assign(n, -1);
    for (int i = 0; i < m; ++i)
    {
        int v = lca_dfs_list[i];
        if (lca_first[v] == -1)
            lca_first[v] = i;
    }
}

// queries the segment tree for the element with minimum height between l and r
int lca_tree_min(int i, int sl, int sr, int l, int r)
{
    if (sl == l && sr == r)
        return lca_tree[i];
    int sm = (sl + sr) >> 1;
    if (r <= sm)
        return lca_tree_min(2*i, sl, sm, l, r);
    if (l > sm)
        return lca_tree_min(2*i+1, sm+1, sr, l, r);
    int ans1 = lca_tree_min(2*i, sl, sm, l, sm);
    int ans2 = lca_tree_min(2*i+1, sm+1, sr, sm+1, r);
    return lca_height[ans1] < lca_height[ans2] ? ans1 : ans2;
}

// function to be called for lca between a and b
int lca(int a, int b)
{
    int left = lca_first[a], right = lca_first[b];
    if (left > right) swap(left, right);
    return lca_tree_min(1, 0, (int)lca_dfs_list.size()-1, left, right);
}

int main()
{
    graph g; // graph is a adjacency list defined at the beginning
    int root; // the root of the graph

    // read the graph to g
    // define root

    lca_prepare(g, root);

    while (true) {
        int v1, v2; // the query
        // read query vertices v1 and v2
        int v = lca (v1, v2); // answer of the query
    }
}
```

## Practice Problems
 - [SPOJ: LCA](http://www.spoj.com/problems/LCA/)
 - [SPOJ: DISQUERY](http://www.spoj.com/problems/DISQUERY/)
 - [TIMUS: 1471. Distance in the Tree](http://acm.timus.ru/problem.aspx?space=1&num=1471)
 - [CODEFORCES: Design Tutorial: Inverse the Problem](http://codeforces.com/problemset/problem/472/D)
 - [CODECHEF: Lowest Common Ancestor](https://www.codechef.com/problems/TALCA)
