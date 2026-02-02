---
tags:
  - Translated
e_maxx_link: lca_simpler
---

# Lowest Common Ancestor - Binary Lifting

Let $G$ be a tree.
For every query of the form `(u, v)` we want to find the lowest common ancestor of the nodes `u` and `v`, i.e. we want to find a node `w` that lies on the path from `u` to the root node, that lies on the path from `v` to the root node, and if there are multiple nodes we pick the one that is farthest away from the root node.
In other words the desired node `w` is the lowest ancestor of `u` and `v`.
In particular if `u` is an ancestor of `v`, then `u` is their lowest common ancestor.

The algorithm described in this article will need $O(N \log N)$ for preprocessing the tree, and then $O(\log N)$ for each LCA query.

## Algorithm

For each node we will precompute its ancestor above him, its ancestor two nodes above, its ancestor four above, etc.
Let's store them in the array `up`, i.e. `up[i][j]` is the `2^j`-th ancestor above the node `i` with `i=1...N`, `j=0...ceil(log(N))`.
These information allow us to jump from any node to any ancestor above it in $O(\log N)$ time.
We can compute this array using a [DFS](depth-first-search.md) traversal of the tree.

For each node we will also remember the time of the first visit of this node (i.e. the time when the DFS discovers the node), and the time when we left it (i.e. after we visited all children and exit the DFS function).
We can use this information to determine in constant time if a node is an ancestor of another node.

Suppose now we received a query `(u, v)`.
We can immediately check whether one node is the ancestor of the other.
In this case this node is already the LCA.
If `u` is not the ancestor of `v`, and `v` not the ancestor of `u`, we climb the ancestors of `u` until we find the highest (i.e. closest to the root) node, which is not an ancestor of `v` (i.e. a node `x`, such that `x` is not an ancestor of `v`, but `up[x][0]` is).
We can find this node `x` in $O(\log N)$ time using the array `up`.

We will describe this process in more detail.
Let `L = ceil(log(N))`.
Suppose first that `i = L`.
If `up[u][i]` is not an ancestor of `v`, then we can assign `u = up[u][i]` and decrement `i`.
If `up[u][i]` is an ancestor, then we just decrement `i`.
Clearly after doing this for all non-negative `i` the node `u` will be the desired node - i.e. `u` is still not an ancestor of `v`, but `up[u][0]` is.

Now, obviously, the answer to LCA will be `up[u][0]` - i.e., the smallest node among the ancestors of the node `u`, which is also an ancestor of `v`.

So answering a LCA query will iterate `i` from `ceil(log(N))` to `0` and checks in each iteration if one node is the ancestor of the other.
Consequently each query can be answered in $O(\log N)$.

## Implementation

```cpp
int n, l;
vector<vector<int>> adj;

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root)
{
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
}
```

## Binary Lifting on a dynamic tree
This is another method of doing LCA, while also accepting adding a leaf of the next number to node `v`.

The earlier method struggles with these updates, since adding a leaf will modify the time of entry and exit for potentially the entire graph.

Lets create an array `d[u]`, containing the distance of node `u` from the root. This can be done with a DFS-traversal of the tree. Similarly to the earlier approach we precompute an array `up[u][j]`.

We handle LCA queries as followed: Let `(u, v)` be the pair that we want to find the answer to. From now on let `d[u] ≥ d[v]` (if `d[v] > d[u]`, we can just swap `u` and `v`). Now lets try and make `d[u] = d[v]`, by moving `u` up to an ancestor.
The ancestor of `u` that satisfies this requirement is exactly `d[u]-d[v]` nodes higher. So using our `up[u][j]` table and the binary representation of `d[u]-d[v]`, lets change the value of `u` to the specified ancestor.

Now we have another problem: Find the LCA of two vertices `(u, v)`, that have the same depth. First, lets check the trivial case if `u = v`, where the LCA of the two values is `u`. If not, then we find the highest vertex, that isn't a common ancestor of `(u, v)`.

Suppose that `L=ceil(log(N))`, where `N` is the maximum number of vertices the graph will have. Let `i = L`. If `up[u][i]=up[v][i]`, we just decrement `i`. If that is not the case, then we set `u = up[u][i]` and `v = up[v][i]`, then we decrement `i`.
After all these operations, we two vertices `u` and `v`, that aren't the LCA od the original pair, but `jump[u][0]` and `jump[v][0]` are. We again are using $O(N \log N)$ preprocessing complexity and a $O( \log N)$ query one.

Now why does this work well in this dynamic environment. Well observe during the algorithm we only need to know the `up[u][j]` array for all vertices and the distance of each node from the root, both of which trivally can be obtained from this query.

## Implementation

```cpp
int n, l;
vector<vector<int>> adj;

vector<int> d;
vector<vector<int>> up;

void dfs(int v, int p, int dist)
{
    d[v]=dist;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v, dist+1);
    }
}

int lca(int u, int v)
{
    if (d[u] < d[v]) swap(u,v);
    for (int j = l; j >= 0; --j) {
      if (d[up[u][j]] >= d[v]) {
            u = up[u][j]
      }
    }

    if(u == v) return u;

    for (int i = l; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

void Add_Leaf(int to)
{
    adj[to].push_back((int) adj.size() + 1);
    adj.push_back({to});

    d.push_back(d[to]+1);
    up.resize((int) up.size() + 1);
    up[(int) up.size() - 1].resize(l+1);
    up[(int) up.size() - 1][0] = to;
    for (int i = 1; i <= l; ++i)
        up[(int) up.size() - 1][i] = up[up[(int) up.size() - 1 ][i-1]][i-1];
}

void preprocess(int root)
{
    d.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root, 0);
}
```


## Practice Problems

* [LeetCode -  Kth Ancestor of a Tree Node](https://leetcode.com/problems/kth-ancestor-of-a-tree-node)
* [Codechef - Longest Good Segment](https://www.codechef.com/problems/LGSEG)
* [HackerEarth - Optimal Connectivity](https://www.hackerearth.com/practice/algorithms/graphs/graph-representation/practice-problems/algorithm/optimal-connectivity-c6ae79ca/)
