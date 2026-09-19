---
tags:
  - Original
---

# 0-1 BFS

It is well-known, that you can find the shortest paths between a single source and all other vertices in $O(|E|)$ using [Breadth First Search](breadth-first-search.md) in an **unweighted graph**, i.e. the distance is the minimal number of edges that you need to traverse from the source to another vertex.
We can interpret such a graph also as a weighted graph, where every edge has the weight $1$.
If not all edges in graph have the same weight, then we need a more general algorithm, like [Dijkstra](dijkstra.md) which runs in $O(|V|^2 + |E|)$ or $O(|E| \log |V|)$ time.

However if the weights are more constrained, we can often do better.
In this article we demonstrate how we can use BFS to solve the SSSP (single-source shortest path) problem in $O(|E|)$, if the weight of each edge is either $0$ or $1$.

## Algorithm

We can develop the algorithm by closely studying Dijkstra's algorithm and thinking about the consequences that our special graph implies.
The general form of Dijkstra's algorithm is (here a `set` is used for the priority queue):

```cpp
d.assign(n, INF);
d[s] = 0;
set<pair<int, int>> q;
q.insert({0, s});
while (!q.empty()) {
    int v = q.begin()->second;
    q.erase(q.begin());

    for (auto edge : adj[v]) {
        int u = edge.first;
        int w = edge.second;

        if (d[v] + w < d[u]) {
            q.erase({d[u], u});
            d[u] = d[v] + w;
            q.insert({d[u], u});
        }
    }
}
```

We can notice that the difference between the distances between the source `s` and two other vertices in the queue differs by at most one.
Especially, we know that $d[v] \le d[u] \le d[v] + 1$ for each $u \in Q$.
The reason for this is, that we only add vertices with equal distance or with distance plus one to the queue during each iteration.
Assuming there exists a $u$ in the queue with $d[u] - d[v] > 1$, then $u$ must have been inserted into the queue via a different vertex $t$ with $d[t] \ge d[u] - 1 > d[v]$.
However this is impossible, since Dijkstra's algorithm iterates over the vertices in increasing order.

This means, that the order of the queue looks like this:

$$Q = \underbrace{v}_{d[v]}, \dots, \underbrace{u}_{d[v]}, \underbrace{m}_{d[v]+1} \dots \underbrace{n}_{d[v]+1}$$

This structure is so simple, that we don't need an actual priority queue, i.e. using a balanced binary tree would be an overkill.
Since the queue only ever holds two distinct distances, we can keep them in two separate vectors: $q_0$ for the vertices at distance $d[v]$, and $q_1$ for those at distance $d[v] + 1$.
An edge of weight $0$ appends to $q_0$, an edge of weight $1$ to $q_1$.
Once $q_0$ runs out, every vertex at the current distance has been processed, so we swap the two vectors and the current distance increases by one.

```cpp
vector<int> d(n, INF);
d[s] = 0;
vector<int> q0, q1;
q0.push_back(s);
while (!q0.empty()) {
    int v = q0.back();
    q0.pop_back();
    for (auto edge : adj[v]) {
        int u = edge.first;
        int w = edge.second;
        if (d[v] + w < d[u]) {
            d[u] = d[v] + w;
            if (w == 0)
                q0.push_back(u);
            else
                q1.push_back(u);
        }
    }
    if (q0.empty())
        swap(q0, q1);
}
```

Written this way the two levels are explicit: a vertex is appended to $q_0$ when it is reached at the current distance and to $q_1$ when it is reached one step further, so the structure of $Q$ shown above is built into the code rather than maintained by hand.
A vertex that was appended to $q_1$ and is then improved to the current distance leaves its old copy behind, but the stale copy is harmless: when it is finally popped, the test `d[v] + w < d[u]` finds nothing left to improve.
Note that $q_0$ is used as a stack rather than a queue, which is harmless: all of its vertices share the same distance, so the order in which they are processed does not matter.

The same algorithm is more commonly written with a single `deque`, pushing to the front for weight $0$ and to the back for weight $1$, so that `push_front` and `push_back` play the roles of $q_0$ and $q_1$.
Two vectors are preferable in practice because they avoid the deque's chunked storage: on graphs small enough to stay in cache this measures about $1.15$ times faster, falling to roughly $1.06$ times on graphs of millions of vertices, where memory latency dominates and the choice of container matters much less (see this [benchmark](https://github.com/ahhz/zero-one-bfs-queue)).

If no edge has weight $0$, the algorithm degenerates into an ordinary BFS, and in that case a plain [BFS](breadth-first-search.md) is both simpler and slightly faster.

## Dial's algorithm

We can extend this even further if we allow the weights of the edges to be even bigger.
If every edge in the graph has a weight $\le k$, then the distances of vertices in the queue will differ by at most $k$ from the distance of $v$ to the source.
So we can keep $k + 1$ buckets for the vertices in the queue, and whenever the bucket corresponding to the smallest distance gets empty, we make a cyclic shift to get the bucket with the next higher distance.
This extension is called **Dial's algorithm**.

## Practice problems

- [Labyrinth](https://codeforces.com/contest/1063/problem/B)
- [KATHTHI](http://www.spoj.com/problems/KATHTHI/)
- [DoNotTurn](https://community.topcoder.com/stat?c=problem_statement&pm=10337)
- [Ocean Currents](https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2620)
- [Olya and Energy Drinks](https://codeforces.com/problemset/problem/877/D)
- [Three States](https://codeforces.com/problemset/problem/590/C)
- [Colliding Traffic](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2621)
- [CHamber of Secrets](https://codeforces.com/problemset/problem/173/B)
- [Spiral Maximum](https://codeforces.com/problemset/problem/173/C)
- [Minimum Cost to Make at Least One Valid Path in a Grid](https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid)
