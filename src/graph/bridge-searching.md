<!--?title Finding bridges in a graph in O(N+M) -->

# Finding bridges in a graph in $O(N+M)$

We are given an undirected graph. A bridge is defined as an edge which, when removed, makes the graph disconnected (or more precisely, increases the number of connected components in the graph). The task is to find all bridges in the given graph.

Informally, the problem is formulated as follows: given a map of cities connected with roads, find all "important" roads, i.e. roads which, when removed, cause disappearance of a path between some pair of cities.

The algorithm described here is based on [depth first search](./graph/depth-first-search.html) and has $O(N+M)$ complexity, where $N$ is the number of vertices and $M$ is the number of edges in the graph.

Note that there also exists an [online algorithm for finding bridges (ru)](http://e-maxx.ru/algo/bridge_searching_online) - unlike the offline algorithm described here, the online algorithm is able to maintain the list of all bridges in a changing graph (assuming that the only type of change is addition of new edges).

## Algorithm

Pick an arbitrary vertex of the graph $root$ and run [depth first search](./graph/depth-first-search.html) from it. Note the following fact (which is easy to prove):

- Let's say we are in the DFS, looking through the edges starting from vertex $v$. The current edge $(v, to)$ is a bridge if and only if none of the vertices $to$ and its descendants in the DFS traversal tree has a back-edge to vertex $v$ or any of its ancestors. (Indeed, this condition means that there is no other way from $v$ to $to$ except for edge $(v, to)$)

Now we have to learn to check this fact for each vertex efficiently. We'll use "time of entry into node" computed by the depth first search.

So, let $tin[v]$ denote entry time for node $v$. We introduce an array $fup$ which will let us check the fact for each vertex $v$. $fup[v]$ is the minimum of $tin[v]$, the entry time for all nodes $p$ that are connected to node $v$ via a back-edge $(v, p)$ and the values of $fup[to]$ for each vertex $to$ which is a direct descendant of $v$ in the DFS tree:

![Formula for fup](&imgroot&/search-bridge-formula.png)

Now, there is a back edge from vertex $v$ or one of its descendants to one of its ancestors if and only if vertex $v$ has a child $to$ for which $fup[to] \leq tin[v]$. If $fup[to] = tin[v]$, the back edge comes directly to $v$, otherwise it comes to one of the ancestors of $v$.

Thus, the current edge $(v, to)$ in the DFS tree is a bridge if and only if $fup[to] > tin[v]$.

## Implementation

The implementation needs to distinguish three cases: when we go down the edge in DFS tree, when we find a back edge to an ancestor of the vertex and when we return to a parent of the vertex. These are the cases:

- $used[to] = false$ - the edge is part of DFS tree;
- $used[to] = true$ && $to \neq parent$ - the edge is back edge to one of the ancestors;
- $to = parent$ - the edge leads back to parent in DFS tree.

To implement this, we need a depth first search function which accepts the parent vertex of the current node.

C++ implementation <span class="toggle-code">Show/Hide</span>

```cpp
const int MAXN = ...;
vector<int> g[MAXN];
bool used[MAXN];
int timer, tin[MAXN], fup[MAXN];
 
void dfs (int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (to == p)  continue;
        if (used[to])
            fup[v] = min (fup[v], tin[to]);
        else {
            dfs (to, v);
            fup[v] = min (fup[v], fup[to]);
            if (fup[to] > tin[v])
                IS_BRIDGE(v,to);
        }
    }
}
 
void find_bridges() {
    timer = 0;
    for (int i = 0; i < n; ++i)
        used[i] = false;
    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfs (i);
}
```

Main function is `find_bridges`; it performs necessary initialization and starts depth first search in each connected component of the graph.

Function `IS_BRIDGE(a, b)` is some function that will process the fact that edge $(a, b)$ is a bridge, for example, print it.

Constant `MAXN` at beginning of code should be initialized to the maximum possible number of vertices in the input graph.

Note that this implementation malfunctions if the graph has multiple edges, since it ignores them. Of course, multiple edges will never be a part of the answer, so `IS_BRIDGE` can check additionally that the reported bridge does is not a multiple edge. Alternatively it's possible to pass to `dfs` the index of the edge used to enter the vertex instead of the parent vertex (and store the indices of all vertices).

## Practice Problems

- [UVA #796 "Critical Links"](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=737) [difficulty: low]
- [UVA #610 "Street Directions"](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=551) [difficulty: medium]
- [Case of the Computer Network (Codeforces Round #310 Div. 1 E)](http://codeforces.com/problemset/problem/555/E) [difficulty: hard]

