---
tags:
    - Original
---

# Gomory-Hu Tree

## Definition

For an undirected graph $G$ with non-negative edge capacities, let $\lambda(s, t)$ be the value of the minimum $s$-$t$ cut. The Gomory-Hu tree of $G$ is a weighted tree on the same vertex set such that, for every pair of vertices $s$ and $t$, the minimum edge weight on the path between $s$ and $t$ is exactly $\lambda(s, t)$.

The construction below proves that such a tree always exists: it starts from a star and transforms it into a Gomory-Hu tree after only $|V| - 1$ flow computations. This is an improvement over the naive $O(|V|^2)$ approach of finding a maximum flow between every pair of vertices.

## Gusfield's Simplification Algorithm

The algorithm keeps a tree rooted at vertex $0$. Unprocessed vertices remain leaves, and each minimum cut determines which of these leaves should move to the current vertex. We use [maximum flow and its residual graph](edmonds_karp.md#max-flow-min-cut-theorem) to find each cut.

Let $V$ be the vertex set of $G$, and let $n = |V|$. The vertices are indexed from $0$ to $n - 1$.
The algorithm is composed of the following steps:

1. Create a (star) tree $T'$ on $n$ nodes, with node 0 at the center and nodes 1 through $n - 1$ at the leaves.
2. For $i$ from 1 to $n - 1$ do steps 3 and 4.
3. Compute the minimum cut $(X, Y)$ in $G$ between (leaf) node $i$ and its (unique) neighbor $t$ in $T'$. Label the edge $(i, t)$ in $T'$ with the capacity of the $(X, Y)$ cut.
4. For every node $j$ larger than $i$, if $j$ is a neighbor of $t$ and $j$ is on the $i$ side of $(X, Y)$, then modify $T'$ by disconnecting $j$ from $t$ and connecting $j$ to $i$. Note that each node $j$ larger than $i$ remains a leaf in $T'$.

It is easy to see that at every iteration, node $i$ and all nodes larger than $i$ are leaves in $T'$, as required by the algorithm.

### Why it works

The cut computed for a tree edge need not separate the endpoints of every later path using that edge. Instead, we prove that moving leaves preserves the required minimum-cut values.

First, for any three vertices $a$, $b$, and $c$,

$$\lambda(a, c) \ge \min(\lambda(a, b), \lambda(b, c)),$$

because every $a$-$c$ cut separates either $a$ from $b$ or $b$ from $c$. For the proof, set $\lambda(v, v) = +\infty$, and let $c(A)$ denote the capacity of the cut $(A, V \setminus A)$. Undirected cut capacities satisfy

$$c(A \setminus B) + c(B \setminus A) \le c(A) + c(B).$$

This follows by counting each graph edge's contribution to both sides.

Suppose $S$ is the side containing $i$ of a minimum $i$-$t$ cut, with capacity $w = \lambda(i, t)$. For any $u \in S$ and $v \notin S$, we claim that

$$\lambda(u, v) = \min(\lambda(u, i), w, \lambda(t, v)). \tag{1}$$

The three-vertex inequality gives the lower bound, and $S$ gives $\lambda(u, v) \le w$. To show $\lambda(u, v) \le \lambda(u, i)$, suppose instead that $a = \lambda(u, i) < \lambda(u, v)$. Take a minimum $i$-$u$ cut with side $A$ containing $i$. Since $a < \lambda(u, v) \le w$, $t$ must also belong to $A$, while $u$ and $v$ lie outside $A$. Thus $A \setminus S$ separates $i$ and $t$, so its capacity is at least $w$. The cut inequality gives

$$
\begin{aligned}
c(S \setminus A) &\le c(S) + c(A) - c(A \setminus S) \\
&\le w + a - w = a.
\end{aligned}
$$

But $S \setminus A$ separates $u$ and $v$, contradicting $a < \lambda(u, v)$. The symmetric argument proves $\lambda(u, v) \le \lambda(t, v)$, establishing (1).

For the induction, temporarily give every unprocessed leaf $u$ the edge weight $\lambda(u, p_u)$, where $p_u$ is its current parent. These weights are used only in the proof; the implementation computes a weight when processing its leaf. The invariant is that the minimum edge weight on each path equals the minimum-cut value between its endpoints, except possibly when both endpoints are unprocessed leaves with the same parent. Initially, only vertex $0$ is processed, and the invariant holds for the star.

When processing $i$, let $t$ be its parent and let $S$ and $w$ be as above. If a leaf $u$ moves from $t$ to $i$, equation (1), with $v = t$, gives

$$\lambda(u, t) = \min(\lambda(u, i), w).$$

Replacing $u$-$t$ by $u$-$i$-$t$ therefore preserves its path minimum to every vertex outside its former sibling group. For a moved leaf $u$ and an unmoved former sibling $v$, the cut $S$ separates $u$ and $v$. Their new path is $u$-$i$-$t$-$v$, whose minimum is correct by (1). The same equation with $u = i$ proves the value on $i$-$t$-$v$. Each new edge between $i$ and a moved leaf also has its true minimum-cut value. Only pairs of unprocessed leaves still sharing a parent can remain exceptions, so the invariant is preserved. After the last iteration there are no exceptions, proving the result.

This construction is Algorithm EQ in [Dan Gusfield, *Very Simple Methods for All Pairs Network Flow Analysis* (1990)](https://doi.org/10.1137/0219009).

## Complexity

The algorithm total complexity is $\mathcal{O}(V)$ times the complexity of a single maximum flow call, wich means that the overall complexity depends on the algorithm that was chosen to find the maximum flow.

### Implementation
Below, we implement the Gomory-Hu tree as a `struct` with methods:

- The maximum flow algorithm must also be a struct with methods, in the implementation below we utilize Dinic's algorithm to calculate the maximum flow.

- The algorithm is 0-indexed and will root the tree in node 0.

- The method *solve* returns a list that contains for each index $i$ the cost of the edge connecting $i$ and its parent, and the parent number.

- The returned tree stores the values needed for all-pairs minimum cut queries. It does not store the two vertex sets of each represented cut; to recover such a partition, rerun a minimum cut computation for the chosen pair.

Here `ll` is an alias for `long long`. Capacities are non-negative integers, and all cut sums, flow totals, and residual arithmetic must fit in `ll`. A sufficient arithmetic bound is that the sum of input capacities is at most `LLONG_MAX / 2`, allowing residual capacities up to twice an edge's input capacity; also respect any smaller limits imposed by the chosen maximum-flow implementation.

```{.cpp file=gomoryhu}
struct gomory_hu {
	struct edg{
		int u, v;
		ll cap;
	};

	Dinic dinic; // you can change your Max Flow algorithm here
	// !! if you change remember to make it compatible with the rest of the code !!
 
	vector<edg> edgs;
 
	void add_edge(int u, int v, ll cap) { // the edges are already bidirectional
		edgs.push_back({u, v, cap});
	}
 
	vector<int> vis;
 
	void dfs(int a) {
		if (vis[a]) return;
		vis[a] = 1;
		for (auto &e : dinic.adj[a])
			if (e.c - e.flow() > 0)
				dfs(e.to);
	}
 
	vector<pair<ll, int>> solve(int n) {					   
		vector<pair<ll, int>> tree_edges(n); // if i > 0, stores pair(cost, parent).

		for (int i = 1; i < n; i++) {
			dinic = Dinic(n);

			for (auto &e : edgs) dinic.addEdge(e.u, e.v, e.cap);
			tree_edges[i].first = dinic.calc(i, tree_edges[i].second);
			
			vis.assign(n, 0);
			dfs(i);
 
			for (int j = i + 1; j < n; j++) {
				if (tree_edges[j].second == tree_edges[i].second && vis[j])
					tree_edges[j].second = i;
			}
		}
 
		return tree_edges;
	}
};
```

## Task examples

Here are some examples of problems related to the Gomory-Hu tree:

- Given a weighted and connected graph, find the minimum $s$-$t$ cut for all pairs of vertices.

- Given a weighted and connected graph, find the minimum or maximum $s$-$t$ cut among all pairs of vertices.

- Find an approximate solution for the [Minimum K-Cut problem](https://en.wikipedia.org/wiki/Minimum_k-cut).

## Practice Problems

- [Codeforces - Juice Junctions](https://codeforces.com/gym/101480/attachments)

- [Codeforces - Honeycomb](https://codeforces.com/gym/103652/problem/D)

- [Codeforces - Pumping Stations](https://codeforces.com/contest/343/problem/E)
