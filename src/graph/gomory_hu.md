---
tags:
    - Original
---

# Gomory-Hu Tree

## Definition

For an undirected graph $G$ with non-negative edge capacities, let $\lambda(s, t)$ be the value of the minimum $s$-$t$ cut. The Gomory-Hu tree of $G$ is a weighted tree on the same vertex set such that, for every pair of vertices $s$ and $t$, the minimum edge weight on the path between $s$ and $t$ is exactly $\lambda(s, t)$.

The construction below proves that such a tree always exists: it starts from a star and transforms it into a Gomory-Hu tree after only $|V| - 1$ flow computations. This is an improvement over the naive $O(|V|^2)$ approach of finding a maximum flow between every pair of vertices.

## Gusfield's Simplification Algorithm

We say that two cuts $(X, V \setminus X)$ and $(Y, V \setminus Y)$ *cross* if all four intersections $X \cap Y$, $X \setminus Y$, $Y \setminus X$, and $V \setminus (X \cup Y)$ are non-empty. A family of cuts with no crossing pairs is called *non-crossing* or *laminar*.

Non-crossing cuts are useful because they can be represented by a tree: removing one edge from the tree separates its vertices into the two sides of one cut. The original Gomory-Hu algorithm keeps such a non-crossing family explicitly. Gusfield's simplification avoids that bookkeeping. It can compute cuts that cross earlier cuts, but it uses them only to move still-unprocessed leaves. For undirected graphs, minimum cuts satisfy an uncrossing property: when two minimum cuts cross, one can replace one of them by a suitable union or intersection without increasing its capacity. This is the reason those leaf moves remain compatible with some non-crossing family of minimum cuts.

The invariant is that, after vertex $i$ is processed, the edge connecting $i$ to its parent has weight $\lambda(i, p_i)$ and will not be changed again. Future steps may move only unprocessed leaves. When a later path uses this finalized edge as its minimum edge, the cut that produced the edge separates the two endpoints of the path, so the path minimum is an upper bound on their minimum cut. The opposite inequality follows from the fact that for any three vertices $a$, $b$, and $c$, every $a$-$c$ cut separates either $a$ from $b$ or $b$ from $c$, hence $\lambda(a, c) \ge \min(\lambda(a, b), \lambda(b, c))$. Applying this along the path in the final tree gives equality.

Let's assume the vertices are 0-indexed for the next section.
The algorithm is composed of the following steps:

1. Create a (star) tree $T'$ on $n$ nodes, with node 0 at the center and nodes 1 through $n - 1$ at the leaves.
2. For $i$ from 1 to $n - 1$ do steps 3 and 4.
3. Compute the minimum cut $(X, Y)$ in $G$ between (leaf) node $i$ and its (unique) neighbor $t$ in $T'$. Label the edge $(i, t)$ in $T'$ with the capacity of the $(X, Y)$ cut.
4. For every node $j$ larger than $i$, if $j$ is a neighbor of $t$ and $j$ is on the $i$ side of $(X, Y)$, then modify $T'$ by disconnecting $j$ from $t$ and connecting $j$ to $i$. Note that each node $j$ larger than $i$ remains a leaf in $T'$.

It is easy to see that at every iteration, node $i$ and all nodes larger than $i$ are leaves in $T'$, as required by the algorithm.

## Complexity

The algorithm total complexity is $\mathcal{O}(V)$ times the complexity of a single maximum flow call, wich means that the overall complexity depends on the algorithm that was chosen to find the maximum flow.

### Implementation
Below, we implement the Gomory-Hu tree as a `struct` with methods:

- The maximum flow algorithm must also be a struct with methods, in the implementation below we utilize Dinic's algorithm to calculate the maximum flow.

- The algorithm is 0-indexed and will root the tree in node 0.

- The method *solve* returns a list that contains for each index $i$ the cost of the edge connecting $i$ and its parent, and the parent number.

- The returned tree stores the values needed for all-pairs minimum cut queries. It does not store the two vertex sets of each represented cut; to recover such a partition, rerun a minimum cut computation for the chosen pair.

```{.cpp file=gomoryhu}
struct gomory_hu {
	struct edg{
		int u, v, cap;
	};

	Dinic dinic; // you can change your Max Flow algorithm here
	// !! if you change remember to make it compatible with the rest of the code !!
 
	vector<edg> edgs;
 
	void add_edge(int u, int v, int cap) { // the edges are already bidirectional
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
