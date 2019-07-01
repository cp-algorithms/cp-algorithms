<!--?title Strong Orientation-->

# Strong Orientation

A **strong orientation** of an undirected graph is an assignment of a direction to each edge that makes it a [strongly connected graph](./graph/strongly-connected-components.html).
That is, after the *orientation* we should be able to visit any vertex from any vertex by following the directed edges.

## Solution

Of course, this cannot be done to *every* graph.
Consider a [bridge](./graph/bridge-searching.html) in a graph.
We have to assign a direction to it and by doing so we make this bridge "crossable" in only one direction. That means we can't go from one of the bridge's ends to the other, so we can't make the graph strongly connected.

Now consider a [DFS](./graph/depth-first-search.html) through a bridgeless connected graph.
Clearly, we will visit each vertex.
And since there are no bridges, we can remove any DFS tree edge and still be able to go
from below the edge to above the edge by using a path that contains at least one back edge.
From this follows that from any vertex we can go to the root of the DFS tree.
Also, from the root of the DFS tree we can visit any vertex we choose.
We found a strong orientation!

In other words, to strongly orient a bridgeless connected graph,
run a DFS on it and let the DFS tree edges point away from the DFS root and
all other edges from the descendant to the ancestor in the DFS tree.

The result that bridgeless connected graphs are exactly the graphs that have strong orientations is called **Robbins' theorem**.

## Problem extension

Let's consider the problem of finding a graph orientation so that the number of SCCs is minimal.

Of course, each graph component can be considered separately.
Now, since only bridgeless graphs are strongly orientable, let's remove all bridges temporarily.
We end up with some number of bridgeless components
(exactly *how many components there were at the beginning* + *how many bridges there were*)
 and we know that we can strongly orient each of them.

We were only allowed to orient edges, not remove them, but it turns out we can orient the bridges arbitrarily.
Of course, the easiest way to orient them is to run the algorithm described above without modifications on each original connected component.

### Implementation

Here, the input is *n* — the number of vertices, *m* — the number of edges, then *m* lines describing the edges.

The output is the minimal number of SCCs on the first line and on the second line
a string of *m* characters,
either `>` — telling us that the corresponding edge from the input
is oriented from the left to the right vertex (as in the input),
or `<` — the opposite.

This is a bridge search algorithm modified to also orient the edges,
you can as well orient the edges as a first step and count the SCCs on the oriented graph as a second.

```cpp
#include <cstdio>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

vector<vector<pii>> adj; // adjacency list - pairs (vertex index, edge index)
vector<pii> edges;

vector<int> index, low;
int tmpbridges;
vector<int> orient;
vector<bool> edge_used;
void find_bridges(int v, int pedge = -1) {
	static int time = 0;
	low[v] = index[v] = time++;
	for (auto p : adj[v]) {
		if (edge_used[p.second]) continue;
		int nv = p.first;
		if (index[nv] == -1) { // if nv is not visited yet
			edge_used[p.second] = true;
			find_bridges(nv, p.second);
			orient[p.second] = v != edges[p.second].first;
			if (low[nv] < low[v]) {
				low[v] = low[nv];
			}
			if (low[nv] > index[v]) {
				// a bridge between v and nv
				tmpbridges++;
			}
		} else if (p.second != pedge) {
			edge_used[p.second] = true;
			orient[p.second] = v != edges[p.second].first;
			if (low[nv] < low[v]) {
				low[v] = low[nv];
			}
		}
	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	adj.resize(n);
	index.resize(n, -1);
	low.resize(n, -1);
	orient.resize(m);
	edges.resize(m);
	edge_used.resize(m);
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		adj[a].push_back({b, i});
		adj[b].push_back({a, i});
		edges[i] = {a, b};
	}
	int result = 0;
	for (int v = 0; v < n; v++) {
		if (index[v] == -1) {
			tmpbridges = 0;
			find_bridges(v);
			result += tmpbridges+1;
		}
	}
	printf("%d\n", result);
	for (int i = 0; i < m; i++) {
		if (orient[i] == 0) {
			printf(">");
		} else {
			printf("<");
		}
	}
	puts("");
}
```

## Practice Problems

* [26th Polish OI - Osiedla](https://szkopul.edu.pl/problemset/problem/nldsb4EW1YuZykBlf4lcZL1Y/site/)
