<!--?title Check whether a graph is bipartite -->

# Check whether a graph is bipartite

A bipartite graph is a graph whose vertices can be divided into two disjoint sets so that every edge connects two vertices from different sets (i.e. there are no edges which connect vertices from the same set). These sets are usually called parts.

You are given an undirected graph. Check whether it is bipartite, and if it is, output its parts.

## Algorithm

There exists a theorem which claims that a graph is bipartite if and only if all its cycles have even length. However, in practice it's more convenient to use a different formulation of the definition: a graph is bipartite if and only if it is two-colorable.

Let's use a series of [breadth-first searches](./graph/breadth-first-search.html), starting from each vertex which hasn't been visited yet. In each search, assign the vertex from which we start to part 1. Each time we visit a yet unvisited neighbor of a vertex assigned to one part, we assign it to the other part. When we try to go to a neighbor of a vertex assigned to one part which has already been visited, we check that is has been assigned to the other part; if it has been assigned to the same part, we conclude that the graph is not bipartite. Once we've visited all vertices and successfully assigned them to parts, we know that the graph is bipartite and we have constructed its partitioning.

## Implementation

```cpp

int n;
vector < vector<int> > g;
// ... read the graph ...

vector<char> part (n, -1);
bool ok = true;
vector<int> q (n);
for (int st=0; st<n; ++st)
	if (part[st] == -1) {
		int h=0, t=0;
		q[t++] = st;
		part[st] = 0;
		while (h<t) {
			int v = q[h++];
			for (size_t i=0; i<g[v].size(); ++i) {
				int to = g[v][i];
				if (part[to] == -1)
					part[to] = !part[v],  q[t++] = to;
				else
					ok &= part[to] != part[v];
			}
		}
	}

puts (ok ? "YES" : "NO");
```
