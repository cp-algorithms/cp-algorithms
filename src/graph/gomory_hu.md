# Gomory Hu Tree

## Definition

The gomory-hu tree of an undirected graph with capacities consists of a weighted tree that condenses information from all the *s-t cuts* for all s-t vertex pairs in the graph. Naively, one must think that $O(|V|^2)$ flow computations are needed to build this data structure, but actually it can be shown that only $|V| - 1$ flow computations are needed. Once the tree is constructed, we can get the minimum cut between two vertices *s* and *t* by querying the minimum weight edge in the unique *s-t* path.

## Gusfield's Simplification Algorithm

We can say that two cuts (X, Y) and (U, V) *cross* if all four set intersections $X \cap U$, $X \cap V$, $Y \cap U$, $Y \cap V$ are nonempty. Most of the work of the original gomory-hu method is involved in maintaining the noncrossing condition. The following simpler, yet efficient method, proposed by Gusfield uses crossing cuts to produce equivalent flow trees.

## Complexity

The algorithm total complexity is $\mathcal{O}(V*MaxFlow)$, wich means that the overall complexity depends on the algorithm that was choosen to find the maximum flow.

### Implementation
This implementation considers the Gomory-Hu tree as a struct with methods:

- The maximum flow algorithm must also be a struct with methods, in the implementation bellow we utilize Dinic's algorithm to calculate the maximum flow.

- The algorithm is 0-indexed and will root the tree in node 0.

- The method *solve* returns the list of edges of the Gomory-Hu tree.

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

- Given a weighted and connected graph, find the minimun s-t cut for all pair of vertices.

- Given a weighted and connected graph, find the minimum/maximum s-t cut among all pair of vertices.

- Find an approximate solution for the [Minimum K-Cut problem](https://en.wikipedia.org/wiki/Minimum_k-cut).

## Practice Problems

- [Codeforces - Juice Junctions](https://codeforces.com/gym/101480/attachments)

- [Codeforces - Honeycomb](https://codeforces.com/gym/103652/problem/D)

- [Codeforces - Pumping Stations](https://codeforces.com/contest/343/problem/E)
