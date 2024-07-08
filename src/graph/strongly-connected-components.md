---
tags:
  - Translated
e_maxx_link: strong_connected_components
---

# Strongly connected components and the condensation graph

## Definitions
Let $G=(V,E)$ be a directed graph with vertices $V$ and edges $E \subseteq V \times V$. We denote with $n=|V|$ the number of vertices and with $m=|E|$ the number of edges in $G$. It is easy to extend all definitions in this article to multigraphs, but we will not focus on that.

A subset of vertices $C \subseteq V$ is called a **strongly connected component** if the following conditions hold:

- for all $u,v\in C$, if $u \neq v$ there exists a path from $u$ to $v$ and a path from $v$ to $u$, and
- $C$ is maximal, in the sense that no vertex can be added without violating the above condition.

We denote with $\text{SCC}(G)$ the set of strongly connected components of $G$. These strongly connected components do not intersect each other, and cover all nodes in the graph. Thus, the set $\text{SCC}(G)$ is a partition of $V$. 

Consider this graph $G_\text{example}$, in which the strongly connected components are highlighted:

<center><img src="strongly-connected-components-tikzpicture/graph.svg" alt="drawing" style="width:700px;"/></center>

Here we have $\text{SCC}(G_\text{example})=\{\{0,7\},\{1,2,3,5,6\},\{4,9\},\{8\}\}.$ We can confirm that within each strongly connected component, all vertices are reachable from each other.

We define the **condensation graph** $G^{\text{SCC}}=(V^{\text{SCC}}, E^{\text{SCC}})$ as follows:

- the vertices of $G^{\text{SCC}}$ are the strongly connected components of $G$; i.e., $V^{\text{SCC}} = \text{SCC}(G)$, and
- for all vertices $C_i,C_j$ of the condensation graph, there is an edge from $C_i$ to $C_j$ if and only if $C_i \neq C_j$ and there exist $a\in C_i$ and $b\in C_j$ such that there is an edge from $a$ to $b$ in $G$.

The condensation graph of $G_\text{example}$ looks as follows:

<center><img src="strongly-connected-components-tikzpicture/cond_graph.svg" alt="drawing" style="width:600px;"/></center>


The most important property of the condensation graph is that it is **acyclic**. Indeed, there are no 'self-loops' in the condensation graph by definition, and if there were a cycle going through two or more vertices (strongly connected components) in the condensation graph, then due to reachability, the union of these strongly connected components would have to be one strongly connected component itself: contradiction.

The algorithm described in the next section finds all strongly connected components in a given graph. After that, the condensation graph can be constructed.

## Description of the algorithm
The described algorithm was independently suggested by Kosaraju and Sharir around 1980. It is based on two series of [depth first search](depth-first-search.md), with a runtime of $O(n + m)$.

In the first step of the algorithm, we perform a sequence of depth first searches (with the function `dfs1`), visiting the entire graph. That is, as long as there are still unvisited vertices, we take one of them, and initiate a depth first search from that vertex. For each vertex, we keep track of the *exit time* $t_\text{out}[v]$. This is the 'timestamp' at which the execution of `dfs1` on node $v$ finishes; that is, the moment at which all nodes reachable from $v$ have been visited and the algorithm is back at $v$. The timestamp counter should *not* be reset between consecutive calls to `dfs1`. The exit times play a key role in the algorithm, which will become clear when we discuss the following theorem.

First, we define the exit time $t_\text{out}[C]$ of a strongly connected component $C$ as the maximum of the values $t_\text{out}[v]$ for all $v \in C.$ Furthermore, in the proof of the theorem, we will mention the *entry time* $t_{\text{in}}[v]$ for each vertex $v\in G$. The number $t_{\text{in}}[v]$ represents the 'timestamp' at which `dfs1` is called on node $v$. For a strongly connected component $C$, we define $t_{\text{in}}[C]$ to be the minimum of the values $t_{\text{in}}[v]$ for all $v \in C$.

**Theorem**. Let $C$ and $C'$ be two different strongly connected components, and let there be an edge from $C$ to $C'$ in the condensation graph. Then, $t_\text{out}[C] > t_\text{out}[C']$.

**Proof.** There are two different cases, depending on which component will first be reached by depth first search:

- Case 1: the component $C$ was reached first (i.e., $t_{\text{in}}[C] < t_{\text{in}}[C']$). In this case, depth first search visits some vertex $v \in C$ at some moment at which all other vertices of the components $C$ and $C'$ are not visited yet. Since there is an edge from $C$ to $C'$ in the condensation graph, not only are all other vertices in $C$ reachable from $v$ in $G$, but all vertices in $C'$ are reachable as well. This means that this `dfs1` execution, which is running from vertex $v$, will also visit all other vertices of the components $C$ and $C'$ in the future, so these vertices will be descendants of $v$ in the depth first search tree. This implies that for each vertex $u \in (C \cup C')\setminus \{v\},$ we have that $t_\text{out}[v] > t_\text{out}[u]$. Therefore, $t_\text{out}[C] > t_\text{out}[C']$, which completes this case of the proof.

- Case 2: the component $C'$ was reached first (i.e., $t_{\text{in}}[C] > t_{\text{in}}[C']$). In this case, depth first search visits some vertex $v \in C'$ at some moment at which all other vertices of the components $C$ and $C'$ are not visited yet. Since there is an edge from $C$ to $C'$ in the condensation graph, there cannot be an edge from $C'$ to $C$, by the acyclicity property. Hence, the `dfs1` execution that is running from vertex $v$ will not reach any vertices of $C$, but it will visit all vertices of $C'$. The vertices of $C$ will be visited by some `dfs1` execution later, so indeed we have $t_\text{out}[C] > t_\text{out}[C']$. This completes the proof.

The proved theorem is very important for finding strongly connected components. It means that any edge in the condensation graph goes from a component with a larger value of $t_\text{out}$ to a component with a smaller value.

If we sort all vertices $v \in V$ in decreasing order of their exit time $t_\text{out}[v]$, then the first vertex $u$ will belong to the "root" strongly connected component, which has no incoming edges in the condensation graph. Now we want to run some type of search from this vertex $u$ so that it will visit all vertices in its strongly connected component, but not other vertices. By repeatedly doing so, we can gradually find all strongly connected components: we remove all vertices belonging to the first found component, then we find the next remaining vertex with the largest value of $t_\text{out}$, and run this search from it, and so on. In the end, we will have found all strongly connected components. In order to find a search method that behaves like we want, we consider the following theorem:

**Theorem.** Let $G^T$ denote the *transpose graph* of $G$, obtained by reversing the edge directions in $G$. Then, $\text{SCC}(G)=\text{SCC}(G^T)$. Furthermore, the condensation graph of $G^T$ is the transpose of the condensation graph of $G$.

The proof is omitted (but straightforward). As a consequence of this theorem, there will be no edges from the "root" component to the other components in the condensation graph of $G^T$. Thus, in order to visit the whole "root" strongly connected component, containing vertex $v$, we can just run a depth first search from vertex $v$ in the transpose graph $G^T$! This will visit precisely all vertices of this strongly connected component. As was mentioned before, we can then remove these vertices from the graph. Then, we find the next vertex with a maximal value of $t_\text{out}[v]$, and run the search in the transpose graph starting from that vertex to find the next strongly connected component. Repeating this, we find all strongly connected components.

Thus, in summary, we discussed the following algorithm to find strongly connected components:

 - Step 1. Run a sequence of depth first searches on $G$, which will yield some list (e.g. `order`) of vertices, sorted on increasing exit time $t_\text{out}$.

- Step 2. Build the transpose graph $G^T$, and run a series of depth first searches on the vertices in reverse order (i.e., in decreasing order of exit times). Each depth first search will yield one strongly connected component.

- Step 3 (optional). Build the condensation graph.

The runtime complexity of the algorithm is $O(n + m)$, because depth first search is performed twice. Building the condensation graph is also $O(n+m).$

Finally, it is appropriate to mention [topological sort](topological-sort.md) here. In step 2, the algorithm finds strongly connected components in decreasing order of their exit times. Thus, it finds components - vertices of the condensation graph - in an order corresponding to a topological sort of the condensation graph.

## Implementation
```cpp
vector<vector<int>> adj, adj_rev; // adjacency lists of G and G^T
vector<bool> visited;             // keeps track of which nodes are already visited
vector<int> order;                // sorted list of G's vertices by exit time
vector<int> component;            // stores one strongly connected component at a time
 
void dfs1(int v) {
    visited[v] = true;
    for (auto u : adj[v])
        if (!visited[u])
            dfs1(u);

    order.push_back(v);
}
 
void dfs2(int v) {
    visited[v] = true;
    component.push_back(v);

    for (auto u : adj_rev[v])
        if (!visited[u])
            dfs2(u);
}
 
int main() {
    int n = ...; 
    for ( ... ) {
        int a = ..., b = ...;
        adj[a].push_back(b);
        adj_rev[b].push_back(a);
    }
 
    visited.assign(n, false);

    // first series of depth first searches
    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs1(i);

    visited.assign(n, false);
    reverse(order.begin(), order.end());

    // condensation graph (explained in text below)
    vector<int> root_nodes;
    vector<int> roots(n, 0);
    vector<vector<int>> adj_scc(n);
    
    // second series of depth first searches
    for (auto v : order)
        if (!visited[v]) {
            dfs2(v);
            int root = component.front();
            for (auto u : component) roots[u] = root;
            root_nodes.push_back(root);
            component.clear();
        }
    
    
    // add edges to condensation graph
    for (int v = 0; v < n; v++)
        for (auto u : adj[v])
            if (roots[v] != roots[u])
                adj_scc[roots[v]].push_back(roots[u]);

    // finished finding SCCs and constructing condensation graph.
    .......
}
```

Here, the function `dfs1` implements depth first search on $G$, and the function `dfs2` implements depth first search on $G^T$. The function `dfs1` fills the vector `order` with vertices in increasing order of their exit times. The function `dfs2` adds all reached vertices to the vector `component`, which, after each run, will contain the just-found strongly connected component.

When building the condensation graph, we select the *root* of each component as the first node in its list (this is an arbitrary choice). This node will represent its entire SCC in the condensation graph. For each vertex `v`, the value `roots[v]` indicates the root node of the SCC which `v` belongs to. `root_nodes` is the list of all root nodes (one per component) in the condensation graph. 

Our condensation graph is now given by the vertices `root_nodes`, and the adjacency list is given by `adj_scc`, using only those vertices which belong to `root_nodes`.

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
* [CSES - Coin Collector](https://cses.fi/problemset/task/1686)
* [Codeforces - Checkposts](https://codeforces.com/problemset/problem/427/C)
