---
tags:
  - Original
---

# Hopcroft-Karp Algorithm

## Problem

You are given a bipartite graph $G = (U \cup V, E)$ containing $n_1$ vertices in the first part, $n_2$ vertices in the second part, and $m$ edges. Find the maximum matching, i.e., select as many edges as possible so that no selected edge shares a vertex with any other selected edge.

## Algorithm Description

The Hopcroft-Karp algorithm finds a maximum matching in a bipartite graph in $O(m \sqrt{n})$ time, where $n = n_1 + n_2$ is the total number of vertices and $m$ is the number of edges. It is significantly faster than [Kuhn's algorithm](kuhn_maximum_bipartite_matching.md) which runs in $O(nm)$ time.

The algorithm uses the concept of **augmenting paths**. A matching is a maximum matching if and only if there are no augmenting paths. An augmenting path is a path that starts and ends at unmatched vertices, and alternates between edges not in the matching and edges in the matching.

Instead of finding one augmenting path at a time like Kuhn's algorithm, Hopcroft-Karp finds a maximal set of shortest augmenting paths simultaneously in each phase. 

Each phase consists of two steps:
1. **Breadth-First Search (BFS):** We perform a BFS starting from all unmatched vertices in $U$ to find the shortest augmenting paths to unmatched vertices in $V$. The BFS explores the graph in an alternating fashion: it traverses from $U$ to $V$ using edges *not* in the matching, and from $V$ to $U$ using edges *in* the matching. The BFS determines the length of the shortest augmenting paths and builds a layered graph (or a level graph) containing only the edges that can be part of such paths.
2. **Depth-First Search (DFS):** Using the layered graph constructed by the BFS, we perform a DFS to find a maximal set of vertex-disjoint augmenting paths of the shortest length. For each such path found, we augment the matching by flipping the edges along the path (edges not in the matching are added, and edges in the matching are removed).

The algorithm terminates when the BFS can no longer find any augmenting path.

### Why is it $O(m \sqrt{n})$?

It can be proven that each phase strictly increases the length of the shortest augmenting path. Furthermore, after $\sqrt{n}$ phases, the length of the shortest augmenting path is at least $\sqrt{n}$. Any augmenting path increases the size of the matching by 1, and the maximum matching size is at most $n/2$. Thus, if the shortest augmenting path is $\ge \sqrt{n}$, there can be at most $\sqrt{n}$ more augmenting paths, meaning at most $\sqrt{n}$ more phases. Therefore, the algorithm requires at most $O(\sqrt{n})$ phases.

Since each phase (one BFS and one DFS) takes $O(m)$ time, the total time complexity is bounded by $O(m \sqrt{n})$.

### Connection to Maximum Flow

The Maximum Bipartite Matching problem can be directly formulated as a Maximum Flow problem by creating a source vertex $s$ connected to all vertices in $U$, and a sink vertex $t$ connected from all vertices in $V$. If we assign a capacity of $1$ to all edges, the maximum flow from $s$ to $t$ will be equal to the maximum matching.

In this context, the Hopcroft-Karp algorithm is essentially mathematically equivalent to **[Dinic's Algorithm](dinic.md)** running on this specific unit-capacity network. 
In Dinic's algorithm, we construct a level graph using BFS and then find blocking flows using DFS. This perfectly matches the BFS and DFS phases of Hopcroft-Karp. Because the flow network constructed for bipartite matching is a **Unit Network** (all vertices except source and sink have either a single incoming edge of capacity $1$ or a single outgoing edge of capacity $1$), Dinic's algorithm is proven to run in $O(m \sqrt{n})$ time, which directly gives the time complexity for Hopcroft-Karp.

## Implementation

Let the vertices in $U$ be numbered from $1$ to $n_1$ and vertices in $V$ be numbered from $1$ to $n_2$.
The array `match_u[u]` stores the matched vertex in $V$ for vertex $u \in U$. If $u$ is not matched, `match_u[u] = 0`.
Similarly, `match_v[v]` stores the matched vertex in $U$ for vertex $v \in V$. If $v$ is not matched, `match_v[v] = 0`.

The vertex $0$ is used as a dummy vertex. The distance to $0$ represents the length of the shortest augmenting path found by the BFS.

```cpp
const int INF = 1e9;

int n1, n2; // n1 is number of vertices in U, n2 is number of vertices in V
vector<vector<int>> g; // Adjacency list from U to V
vector<int> match_u, match_v, dist;

bool bfs() {
    queue<int> q;
    for (int u = 1; u <= n1; ++u) {
        if (match_u[u] == 0) {
            dist[u] = 0;
            q.push(u);
        } else {
            dist[u] = INF;
        }
    }
    dist[0] = INF;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (dist[u] < dist[0]) {
            for (int v : g[u]) {
                if (dist[match_v[v]] == INF) {
                    dist[match_v[v]] = dist[u] + 1;
                    q.push(match_v[v]);
                }
            }
        }
    }
    return dist[0] != INF;
}

bool dfs(int u) {
    if (u != 0) {
        for (int v : g[u]) {
            if (dist[match_v[v]] == dist[u] + 1) {
                if (dfs(match_v[v])) {
                    match_v[v] = u;
                    match_u[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int hopcroft_karp() {
    match_u.assign(n1 + 1, 0);
    match_v.assign(n2 + 1, 0);
    dist.assign(n1 + 1, 0);

    int matching = 0;
    while (bfs()) {
        for (int u = 1; u <= n1; ++u) {
            if (match_u[u] == 0 && dfs(u)) {
                matching++;
            }
        }
    }
    return matching;
}
```

In the main function, you would set `n1` and `n2`, resize `g` to `n1 + 1` and populate the adjacency list using 1-based indexing for both $U$ and $V$.

## Practice Problems

* [SPOJ - MATCHING](https://www.spoj.com/problems/MATCHING/)
* [CSES - School Dance](https://cses.fi/problemset/task/1696)
