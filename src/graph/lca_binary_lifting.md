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

For each node we will precompute its ancestor above it, its ancestor two nodes above, its ancestor four above, etc.
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
This is another method of doing LCA, that also accepts adding a leaf node  to node `v`.

The earlier method struggles with these updates, since adding a leaf will potentially modify the time of entry and exit for the entire graph.

Lets create an array `depth[u]`, containing the distance of node `u` from the root. This can be done with a DFS-traversal of the tree. Similarly to the earlier approach we precompute an array `up[u][j]`.

We handle LCA queries as followed: Let `(u, v)` be the pair that we want to find the answer to. From now on let `depth[u] ≥ depth[v]` (if `depth[v] > depth[u]`, we can just swap `u` and `v`). Now lets try and make `depth[u] = depth[v]`, by moving `u` up to an ancestor.
The ancestor of `u` that satisfies this requirement is exactly `depth[u]-depth[v]` nodes higher. So using our `up[u][j]` table and the binary representation of `depth[u]-depth[v]`, lets change the value of `u` to the specified ancestor.

Now we have another problem: Find the LCA of two vertices `(u, v)`, that have the same depth. First, lets check the trivial case if `u = v`, where the LCA of the two values is `u`. If not, then we find the highest vertex, that isn't a common ancestor of `(u, v)`.

Suppose that `L=ceil(log(N))`, where `N` is the maximum number of vertices the graph will have. Let `i = L`. If `up[u][i]=up[v][i]`, we just decrement `i`. If that is not the case, then we set `u = up[u][i]` and `v = up[v][i]`, then we decrement `i`.
After all these operations, we two vertices `u` and `v`, that aren't the LCA od the original pair, but `jump[u][0]` and `jump[v][0]` are. We again are using $O(N \log N)$ preprocessing complexity and a $O( \log N)$ query one.

Now, why does this work well in this dynamic environment? Well observe during the algorithm we only need to know the `up[u][j]` array for all vertices and the distance of each node from the root, both of which trivally can be obtained from the add leaf query in $O(\log n)$ time.

## Implementation

```cpp
int n, l;

//Set this to maximum size of graph
int MAXN;


int ups;
vector<vector<int>> adj;

vector<int> depth;
vector<vector<int>> up;

void dfs(int v, int p, int dist)
{
    depth[v]=dist;
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
    if (depth[u] < depth[v]) swap(u,v);
    for (int j = l; j >= 0; --j) {
        if (depth[up[u][j]] >= depth[v]) {
            u = up[u][j];
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

void add_leaf(int to)
{
    adj[to].push_back((int) adj.size() + 1);
    adj.push_back({to});
    depth.push_back(depth[to]+1);
    up.resize(ups + 1);
    ups++;
    up[ups - 1].resize(l+1);
    up[ups - 1][0] = to;
    for (int i = 1; i <= l; ++i)
        up[ups - 1][i] = up[up[ups - 1 ][i-1]][i-1];
}

void preprocess(int root)
{
    depth.resize(n);
    l = ceil(log2(MAXN));
    up.assign(n, vector<int>(l + 1));
    ups = n;
    dfs(root, root, 0);
}
```

## LCA with $O(n)$ space and preprocessing time

This method allows us to calculate the LCA while only using $O(n)$ space. It is also possible to extend it so it will work for a dynamic tree. It was first proposed by Harel and Tarjan in 1984.

Create an array `depth[]` which will store the depth of each node in the tree.
For each node we will define only **small** and **big** jumps. Small jumps will always point to the immediate ancestor (except for the root, which will point to itself). The big jumps have a more complicated definition. Denote `big[v]` as the node that we will be in after we do a big jump from node `v`. Let `big[root] = root`. 

After that we create a recursive definition.

$$\mathtt{big}[u] = \begin{cases} \mathtt{big}[\mathtt{big}[ancestor[u]]] & \text{if the size of the big jump from the parent node is equal to the one of }\mathtt{big}[ancestor[u]] \\
\mathtt{ancenstor}[u] & \text{otherwise}\end{cases}$$

We can check the size of the jump simply by subtracting `depth[big[u]]` from `depth[u]`. 
We have to evaluate this array in an order, such that for every node, we have computed the values for all of its ancestors. We can use the preorder ordering here, since it satisfies this property.


Now after all of that preprocessing, answering queries is easy. We first balance the nodes to an equal depth and then we try to find the lowest node that isn't a common ancestor. This is very similar to what has been done in the Dynamic LCA algorithm, but now we just check if we can preform a big jump and if not, then we do a small one. The time complexity is logarithmic, as Harel and Tarjan proved in their paper that we will use maximaly $6\lfloor{\log(d+1)}\rfloor-4$ jumps. The space complexity is linear 
## Implementation

```cpp
int n, l;
vector<vector<int>> adj;

vector<int> depth;
vector<int> small, big;

void dfs(int v, int p, int dist)
{
    depth[v] = dist;
    small[v] = p;
    
    if(depth[p] - depth[big[p]] == depth[big[p]] - depth[big[big[p]]]){
        big[v]= big[big[p]];
    }
    else{
        big[v]=p;
    }

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v, dist+1);
    }
}

int lca(int u, int v)
{
    if (depth[u] < depth[v]) swap(u,v);
    while(depth[u] != depth[v]) {
        if (depth[big[u]] >= depth[v]) {
            u = big[u];
        }
        else{
            u = small[u];
        }
    }

    while(u != v) {
        if (big[u] != big[v]) {
            u = big[u];
            v = big[v];
        }
        else{
            u = small[u];
            v = small[v];
        }
    }
    return u;
}


void preprocess(int root)
{
    depth.resize(n);
    small.resize(n);
    big.resize(n);
    big[root] = root;
    dfs(root, root, 0);
}
```



## Practice Problems

* [LeetCode -  Kth Ancestor of a Tree Node](https://leetcode.com/problems/kth-ancestor-of-a-tree-node)
* [Codechef - Longest Good Segment](https://www.codechef.com/problems/LGSEG)
* [HackerEarth - Optimal Connectivity](https://www.hackerearth.com/practice/algorithms/graphs/graph-representation/practice-problems/algorithm/optimal-connectivity-c6ae79ca/)
