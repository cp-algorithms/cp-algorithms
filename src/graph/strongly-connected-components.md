---
tags:
  - Translated
e_maxx_link: strong_connected_components
---

# Finding strongly connected components / Building condensation graph

# Definitions
Let $G=(V,E)$ be a directed graph with vertices $V$ and edges $E$. It is possible that there are self-loops, or multiple edges between the same pair of vertices. We denote with $n=|V|$ the number of vertices and with $m=|E|$ the number of edges in $G$.

A nonempty subset of vertices $C \subseteq V$ is called a **strongly connected component** if the following conditions hold:

- for all $u,v\in C$, if $u \neq v$ there exists a path from $u$ to $v$, and
- if any node $u$ were removed from $C$, the above condition would not hold anymore.

We denote with $\text{SCC}(G)$ the set of strongly connected components of $G$. It is clear that these strongly connected components do not intersect each other, and that they cover all nodes in the graph. Thus, the set $\text{SCC}(G)$ is a partition of $V$. We define the **condensation graph** $G^{\text{SCC}}=(V^{\text{SCC}}, E^{\text{SCC}})$ as follows:

- the vertices of $G^{\text{SCC}}$ are the strongly connected components of $G$; i.e., $V^{\text{SCC}} = \text{SCC}(G)$, and
- for all vertices $C_i,C_j$ of the condensation graph, there is an edge from $C_i$ to $C_j$ if and only if $C_i \neq C_j$ and there exist $a\in C_i$ and $b\in C_j$ such that there is an edge from $a$ to $b$ in $G$.

The most important property of the condensation graph is that it is **acyclic**. If there were a cycle in $G^{\text{SCC}}$, then there would exist distinct strongly connected components $C_1$ and $C_2$ which are both reachable from each other in $G^{\text{SCC}}$ (recall that, by definition, there are no self-loops in $G^{\text{SCC}}$). However, this would imply that all vertices in $C_1\cup C_2$ are reachable from each other. Thus, $C_1$ and $C_2$ would be part of the same strongly connected component. We reach a contradiction, and conclude that the condensation graph is indeed acyclic.

The algorithm described in the next section finds all strongly connected components in a given graph. After that, the condensation graph can be constructed.

## Description of the algorithm
The described algorithm was independently suggested by Kosaraju and Sharir around 1980. It is an easy-to-implement algorithm based on two series of [depth first search](depth-first-search.md), with a runtime of $O(n + m)$.

**In the first step** of the algorithm, we perform a sequence of depth first searches, visiting the entire graph. As long as there are still unvisited vertices, we take one of them, and initiate a depth first search from that vertex. For each vertex, we keep track of the *exit time* $t_\text{out}[v]$. This is the 'timestamp' at which the call to `dfs` on node $v$ finishes (this timestamp should be preserved between consecutive calls to `dfs` on unvisited nodes). These exit times play a key role in the algorithm, which will become clear when we discuss the next theorem.

First, we define the exit time $t_\text{out}[C]$ of a strongly connected component $C$ as the maximum of the values $t_\text{out}[v]$ for all $v \in C.$ Furthermore, in the proof of the theorem, we will mention the *entry time* $t_{\text{in}}[v]$ for each vertex $v\in G$. The number $t_{\text{in}}[v]$ represents the 'timestamp' at which `dfs` is called on node $v$. For a strongly connected component $C$, we define $t_{\text{in}}[C]$ to be the minimum of the values $t_{\text{in}}[v]$ for all $v \in C$.

**Theorem**. Let $C$ and $C'$ be two different strongly connected components, and let there be an edge from $C$ to $C'$ in the condensation graph. Then, $t_\text{out}[C] > t_\text{out}[C']$.

There are two main different cases at the proof depending on which component will be visited by depth first search first, i.e. depending on difference between $t_{\text{in}}[C]$ and $t_{\text{in}}[C']$:

- The component $C$ was reached first. It means that depth first search comes at some vertex $v$ of component $C$ at some moment, but all other vertices of components $C$ and $C'$ were not visited yet. By condition there is an edge $(C, C')$ in a condensation graph, so not only the entire component $C$ is reachable from $v$ but the whole component $C'$ is reachable as well. It means that depth first search that is running from vertex $v$ will visit all vertices of components $C$ and $C'$, so they will be descendants for $v$ in a depth first search tree, i.e. for each vertex $u \in C \cup C', u \ne v$ we have that $t_\text{out}[v] > t_\text{out}[u]$, as we claimed.

- Assume that component $C'$ was visited first. Similarly, depth first search comes at some vertex $v$ of component $C'$ at some moment, but all other vertices of components $C$ and $C'$ were not visited yet. But by condition there is an edge $(C, C')$ in the condensation graph, so, because of acyclic property of condensation graph, there is no back path from $C'$ to $C$, i.e. depth first search from vertex $v$ will not reach vertices of $C$. It means that vertices of $C$ will be visited by depth first search later, so $t_\text{out}[C] > t_\text{out}[C']$. This completes the proof.

Proved theorem is **the base of algorithm** for finding strongly connected components. It follows that any edge $(C, C')$ in condensation graph comes from a component with a larger value of $t_\text{out}$ to component with a smaller value.

If we sort all vertices $v \in V$ in decreasing order of their exit time $t_\text{out}[v]$ then the first vertex $u$ is going to be a vertex belonging to "root" strongly connected component, i.e. a vertex that has no incoming edges in the condensation graph. Now we want to run such search from this vertex $u$ so that it will visit all vertices in this strongly connected component, but not others; doing so, we can gradually select all strongly connected components: let's remove all vertices corresponding to the first selected component, and then let's find a vertex with the largest value of $t_\text{out}$, and run this search from it, and so on.

Let's consider transposed graph $G^T$, i.e. graph received from $G$ by reversing the direction of each edge.
Obviously, this graph will have the same strongly connected components as the initial graph.
Moreover, the condensation graph $G^{SCC}$ will also get transposed.
It means that there will be no edges from our "root" component to other components.

Thus, for visiting the whole "root" strongly connected component, containing vertex $v$, is enough to run search from vertex $v$ in graph $G^T$. This search will visit all vertices of this strongly connected component and only them. As was mentioned before, we can remove these vertices from the graph then, and find the next vertex with a maximal value of $t_\text{out}[v]$ and run search in transposed graph from it, and so on.

Thus, we built next **algorithm** for selecting strongly connected components:

1st step. Run sequence of depth first search of graph $G$ which will return vertices with increasing exit time $tout$, i.e. some list $order$.

2nd step. Build transposed graph $G^T$. Run a series of depth (breadth) first searches in the order determined by list $order$ (to be exact in reverse order, i.e. in decreasing order of exit times). Every set of vertices, reached after the next search, will be the next strongly connected component.

Algorithm asymptotic is $O(n + m)$, because it is just two depth (breadth) first searches.

Finally, it is appropriate to mention [topological sort](topological-sort.md) here. First of all, step 1 of the algorithm represents reversed topological sort of graph $G$ (actually this is exactly what vertices' sort by exit time means). Secondly, the algorithm's scheme generates strongly connected components by decreasing order of their exit times, thus it generates components - vertices of condensation graph - in topological sort order.

## Implementation
```cpp
vector<vector<int>> adj, adj_rev;
vector<bool> used;
vector<int> order, component;
 
void dfs1(int v) {
    used[v] = true;

    for (auto u : adj[v])
        if (!used[u])
            dfs1(u);

    order.push_back(v);
}
 
void dfs2(int v) {
    used[v] = true;
    component.push_back(v);

    for (auto u : adj_rev[v])
        if (!used[u])
            dfs2(u);
}
 
int main() {
    int n;
    // ... read n ...

    for (;;) {
        int a, b;
        // ... read next directed edge (a,b) ...
        adj[a].push_back(b);
        adj_rev[b].push_back(a);
    }
 
    used.assign(n, false);

    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs1(i);

    used.assign(n, false);
    reverse(order.begin(), order.end());

    for (auto v : order)
        if (!used[v]) {
            dfs2 (v);

            // ... processing next component ...

            component.clear();
        }
}
```

Here, $g$ is graph, $gr$ is transposed graph. Function $dfs1$ implements depth first search on graph $G$, function $dfs2$ - on transposed graph $G^T$. Function $dfs1$ fills the list $order$ with vertices in increasing order of their exit times (actually, it is making a topological sort). Function $dfs2$ stores all reached vertices in list $component$, that is going to store next strongly connected component after each run.

### Condensation Graph Implementation

```cpp
// continuing from previous code

vector<int> roots(n, 0);
vector<int> root_nodes;
vector<vector<int>> adj_scc(n);

for (auto v : order)
    if (!used[v]) {
        dfs2(v);

        int root = component.front();
        for (auto u : component) roots[u] = root;
        root_nodes.push_back(root);

        component.clear();
    }


for (int v = 0; v < n; v++)
    for (auto u : adj[v]) {
        int root_v = roots[v],
            root_u = roots[u];

        if (root_u != root_v)
            adj_scc[root_v].push_back(root_u);
    }
```

Here, we have selected the root of each component as the first node in its list. This node will represent its entire SCC in the condensation graph. `roots[v]` indicates the root node for the SCC to which node `v` belongs. `root_nodes` is the list of all root nodes (one per component) in the condensation graph. 

`adj_scc` is the adjacency list of the `root_nodes`. We can now traverse on `adj_scc` as our condensation graph, using only those nodes which belong to `root_nodes`.

## Literature

* Thomas Cormen, Charles Leiserson, Ronald Rivest, Clifford Stein. Introduction to Algorithms [2005].
* M. Sharir. A strong-connectivity algorithm and its applications in data-flow analysis [1979].

## Practice Problems

* [SPOJ - Good Travels](http://www.spoj.com/problems/GOODA/)
* [SPOJ - Lego](http://www.spoj.com/problems/LEGO/)
* [Codechef - Chef and Round Run](https://www.codechef.com/AUG16/problems/CHEFRRUN)
* [Dev Skills - A Song of Fire and Ice](https://devskill.com/CodingProblems/ViewProblem/79)
* [UVA - 11838 - Come and Go](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2938)
* [UVA 247 - Calling Circles](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=183)
* [UVA 13057 - Prove Them All](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4955)
* [UVA 12645 - Water Supply](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4393)
* [UVA 11770 - Lighting Away](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2870)
* [UVA 12926 - Trouble in Terrorist Town](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=862&page=show_problem&problem=4805)
* [UVA 11324 - The Largest Clique](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2299)
* [UVA 11709 - Trust groups](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2756)
* [UVA 12745 - Wishmaster](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4598)
* [SPOJ - True Friends](http://www.spoj.com/problems/TFRIENDS/)
* [SPOJ - Capital City](http://www.spoj.com/problems/CAPCITY/)
* [Codeforces - Scheme](http://codeforces.com/contest/22/problem/E)
* [SPOJ - Ada and Panels](http://www.spoj.com/problems/ADAPANEL/)
* [CSES - Flight Routes Check](https://cses.fi/problemset/task/1682)
* [CSES - Planets and Kingdoms](https://cses.fi/problemset/task/1683)
* [CSES -Coin Collector](https://cses.fi/problemset/task/1686)
* [Codeforces - Checkposts](https://codeforces.com/problemset/problem/427/C)
