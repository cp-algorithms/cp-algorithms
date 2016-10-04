<!--?title Depth First Search-->

# Depth First Search

Depth First Search is one of the main graph algorithms.

Depth First Search finds the lexicographically first path in the graph to each vertex $v$ from a source vertex $u$.

The algorithm works in about $O(m + n)$ time where $n$ is the number of vertices and $m$ is the number of edges.

## Applications of Depth First Search

* Search for any path in the graph to all vertices $v$ from source $u$.

* Search for lexicographically first path to all vertices $v$ in the graph from source $u$.

* Check if a vertex in a tree is the ancestor of some other vertex: At the beginning and end of each search call, maintain the entry and exit "time" of each vertex. Now, you can find the answer for any pair of vertices (i, j) in O(1): the vertex i is an ancestor of the node j if and only if the $entry[i] < entry[j]$ and $exit[i] > exit[j]$.

* Finding the lowest common ancestor (LCA) of two nodes.

* Topological sorting : Run a series of depth first searches so as to visit each vertex exactly once. This will take $ O(n + m)$ time. Sort the vertices in descending order of exit time. This will be the required topological order.

* Testing if a given graph is acyclic and finding cycles in a graph.

* Finding strongly connected components of a given directed graph: First do a topological sort of the graph. Then take a transpose of the graph and once again, run a series of depth first searches in the order found by the topological sort. Each component created by each DFS call is a strongly connected component.

* Search for Bridges in an undirected graph: First convert the given graph into a directed graph by running a series of depth first searches and making each edge directed as we go through it, in the direction we went. Now, find the strongly connected components in this directed graph. Finally, bridges are those edges whose ends belong to different
strongly connected components.

## Implementation

	vector <vector <int>> g; // adjacency list representation of graph
	int n; // Number of vertices

	vector <int> color; // Vertex color (0, 1, or 2)

	vector <int> time_in, time_out; // Entry and exit "times" for each vertex from the source
	int dfs_timer = 0; // "Timer" to determine the current time

	void dfs (int v) {
		time_in [v] = dfs_timer ++;
		color [v] = 1;
		for (vector <int> :: iterator i = g [v] .begin ();! i = g [v] .end (); ++ i)
			if (color [* i] == 0)
				dfs (* i);
		color [v] = 2;
		time_out [v] = dfs_timer ++;
	}


This is the most common implementation of Depth First Search. In many cases however, the entry and exit times and the vertex colors are not important, so they can be discarded. However it will be necessary to store a boolean array $used[]$ which is almost the same as colors. Here is the simplest implementation of DFS:

	vector <vector <int>> g; // Adjacency list representation of graph
	int n; // Number of vertices

	vector <bool> used;

	void dfs (int v) {
		used [v] = true;
		for (vector <int> :: iterator i = g [v] .begin ();! i = g [v] .end (); ++ i)
			if (! used [* i])
				dfs (* i);
	}

## Practice Problems

* [SPOJ: ABCPATH](http://www.spoj.com/problems/ABCPATH/)
* [SPOJ: EAGLE1](http://www.spoj.com/problems/EAGLE1/)
* [Codeforces: Kefa and Park](http://codeforces.com/problemset/problem/580/C)
