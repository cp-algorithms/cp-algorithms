<!--?title Depth First Search-->

# Depth First Search

Depth First Search is one of the main graph algorithms.

Depth First Search finds the lexicographically first path in the graph from a source vertex $u$ to each vertex.

The algorithm works in $O(m + n)$ time where $n$ is the number of vertices and $m$ is the number of edges.

## Applications of Depth First Search

* Find any path in the graph from source vertex $u$ to all vertices.

* Find lexicographically first path in the graph from source $u$ to all vertices.

* Check if a vertex in a tree is an ancestor of some other vertex.

  At the beginning and end of each search call, remember the entry and exit "time" of each vertex. Now, you can find the answer for any pair of vertices $(i, j)$ in $O(1)$: vertex i is an ancestor of vertex j if and only if $entry[i] < entry[j]$ and $exit[i] > exit[j]$.

* Find the lowest common ancestor (LCA) of two vertices.

* Topological sorting.

  Run a series of depth first searches so as to visit each vertex exactly once in $O(n + m)$ time. The required topological ordering will be the vertices sorted in descending order of exit time.

* Check whether a given graph is acyclic and find cycles in a graph.

* Find strongly connected components in a directed graph.

 First do a topological sorting of the graph. Then transpose the graph and run another series of depth first searches in the order defined by the topological sort. For each BFS call the component created by it is a strongly connected component.

* Find bridges in an undirected graph.

  First convert the given graph into a directed graph by running a series of depth first searches and making each edge directed as we go through it, in the direction we went. Second, find the strongly connected components in this directed graph. Bridges are the edges whose ends belong to different strongly connected components.

## Implementation

```cpp
vector<vector<int>> g; // graph represented as an adjacency list
int n; // number of vertices

vector<int> color; // vertex color (0, 1, or 2)

vector<int> time_in, time_out; // entry and exit "times" for each vertex
int dfs_timer = 0; // "timer" to determine the current time

void dfs(int v) {
	time_in[v] = dfs_timer++;
	color[v] = 1;
	for (vector <int>::iterator i = g[v].begin(); i != g[v].end(); ++i)
		if (color[*i] == 0)
			dfs(*i);
	color[v] = 2;
	time_out[v] = dfs_timer++;
}
```

This is the most generic implementation of Depth First Search. In many cases entry and exit times and vertex colors are not important, so they can be discarded. In this case it will be necessary to store a boolean array $used[]$ to keep track of visited vertices. Here is the simplest implementation of DFS:

```cpp
vector<vector<int>> g; // graph represented as an adjacency list
int n; // number of vertices

vector<bool> used;

void dfs(int v) {
	used[v] = true;
	for (vector<int>::iterator i = g[v].begin(); i != g[v].end(); ++i)
		if (!used[*i])
			dfs(*i);
}
```

## Practice Problems

* [SPOJ: ABCPATH](http://www.spoj.com/problems/ABCPATH/)
* [SPOJ: EAGLE1](http://www.spoj.com/problems/EAGLE1/)
* [Codeforces: Kefa and Park](http://codeforces.com/problemset/problem/580/C)
* [Timus:Werewolf](http://acm.timus.ru/problem.aspx?space=1&num=1242)
* [Timus:Penguin Avia](http://acm.timus.ru/problem.aspx?space=1&num=1709)
* [Timus:Two Teams](http://acm.timus.ru/problem.aspx?space=1&num=1106)
* [SPOJ - Ada and Island](http://www.spoj.com/problems/ADASEA/)
* [UVA 657 - The die is cast](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=598)
* [SPOJ - Sheep](http://www.spoj.com/problems/KOZE/)
* [SPOJ - Path of the Rightenous Man](http://www.spoj.com/problems/RIOI_2_3/)
* [SPOJ - Validate the Maze](http://www.spoj.com/problems/MAKEMAZE/)
* [SPOJ - Ghosts having Fun](http://www.spoj.com/problems/GHOSTS/)
* [Codeforces - Underground Lab](http://codeforces.com/contest/781/problem/C)
* [DevSkills - Maze Tester](https://devskill.com/CodingProblems/ViewProblem/3)
* [DevSkills - Tourist](https://devskill.com/CodingProblems/ViewProblem/17)
* [Codeforces - Anton and Tree](http://codeforces.com/contest/734/problem/E)
* [Codeforces - Transformation: From A to B](http://codeforces.com/contest/727/problem/A)
* [Codeforces - One Way Reform](http://codeforces.com/contest/723/problem/E)
* [Codeforces - Centroids](http://codeforces.com/contest/709/problem/E)
* [Codeforces - Generate a String](http://codeforces.com/contest/710/problem/E)
* [Codeforces - Broken Tree](http://codeforces.com/contest/758/problem/E)
* [Codeforces - Dasha and Puzzle](http://codeforces.com/contest/761/problem/E)
* [Codeforces - Making genome In Berland](http://codeforces.com/contest/638/problem/B)
* [Codeforces - Road Improvement](http://codeforces.com/contest/638/problem/C)
* [Codeforces - Garland](http://codeforces.com/contest/767/problem/C)
* [Codeforces - Labeling Cities](http://codeforces.com/contest/794/problem/D)
* [Codeforces - Send the Fool Futher!](http://codeforces.com/contest/802/problem/K)
* [Codeforces - The tag Game](http://codeforces.com/contest/813/problem/C)
* [Codeforces - Leha and Another game about graphs](http://codeforces.com/contest/841/problem/D)
* [Codeforces - Shortest path problem](http://codeforces.com/contest/845/problem/G)
* [Codeforces - Upgrading Tree](http://codeforces.com/contest/844/problem/E)
* [Codeforces - From Y to Y](http://codeforces.com/contest/849/problem/C)
* [Codeforces - Chemistry in Berland](http://codeforces.com/contest/846/problem/E)
* [Codeforces - Wizards Tour](http://codeforces.com/contest/861/problem/F)
* [Codeforces - Ring Road](http://codeforces.com/contest/24/problem/A)
* [Codeforces - Mail Stamps](http://codeforces.com/contest/29/problem/C)
* [Codeforces - Ant on the Tree](http://codeforces.com/contest/29/problem/D)
* [SPOJ - Cactus](http://www.spoj.com/problems/CAC/)
* [SPOJ - Mixing Chemicals](http://www.spoj.com/problems/AMR10J/)
