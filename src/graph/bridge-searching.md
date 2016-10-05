<!--?title Searching for bridges in a graph in O(N+M) -->

# Searching for bridges

Suppose that we are given an undirected graph. A bridge is defined as an edge, whose removal makes the graph disconnected(or more precisely, increases the number of connected components). You want to find all the bridges in a given graph.

Informally, the problem is formulated as follows: Given a map of cities with roads between them, find all "important" roads, i.e. roads whose removal leads to disappearance of the path between some pair of cities.

Below, we describe the algorithm based of [depth first search](http://e-maxx.ru/algo/dfs), having running time $O(n+m)$, where $n$ is the number of vertices, and $m$ is the number of edges in the graph.

Note that the website also describes an [online algorithm for finding bridges](http://e-maxx.ru/algo/bridge_searching_online) - in contrast to the offline algorithm described here, the online algorithm is able to maintain all bridges in a graph that is changing(new edges are being added).

## Algorithm

Run [DFS](http://e-maxx.ru/algo/dfs) from an arbitrary vertex of the graph; lets denote it through $root$. We note the following fact(which is easy to prove):

- Let's say we are in the DFS, and looking through the edges from vertex $v$. Then for some edge $(v, to)$, it is a bridge if the vertices $to$ and it's descendants in the DFS tree have no back-edges to vertex $v$ or any of it's ancestors. Otherwise, the edge must not be a bridge. (In fact, we check the condition that there is no other way from $v$ to $to$ except for edge $(v, to)$ traversing the DFS tree.)

Now we have to learn how to effectively verify this fact for each vertex. For doing this, we use "time of entry into node", computed by the depth first search algorithm.

So, let $tin[v]$ denote the the depth first search time of node $v$. Now, we introduce the array $fup[v]$, which is the minimum of $tin[v]$, the DFS time of all nodes $p$ that are connected to node $v$ via back-edge $(v, p)$ and all the values of $fup[to]$ for each vertex to which is a direct child of $v$ in the DFS tree.

![Formula for algorithm complexity](https://raw.githubusercontent.com/e-maxx-eng/e-maxx-eng/master/img/search-bridge-formula.png)

Now, there is a back edge from node $v$ or it's descendants if there is a son $to$ of node $v$ such that $fup[to] \leq tin[v]$.(If $fup[to] = tin[v]$, it means back edge comes directly to $v$, otherwise it comes to some ancestor).

Thus, if the current edge $(v, to)$ in the DFS tree satisfies $fup[to] > tin[v]$, then it must be a bridge; otherwise it isn't one.

##Implementation

Regarding the implementation, here we need to distinguish 3 cases: when we are on an edge to a child in DFS tree, when we try to go on a back edge to some ancestor and when we are going in the reverse direction to our parent. Therefore, these are the cases accordingly:

- $used[to] = false$ - DFS tree edges criteria;
- $used[to] = true$ && $to \neq parent$ - back edge to some ancestor criteria;
- $to = parent$ - Criteria for edge to be edge to parent in DFS tree.

Thus, to implement, we need a depth first search function with all the information for a current node.

C++ implementation <span class="toggle-code">Show/Hide</span>

<pre><code>const int MAXN = ...;
vector&lt;int&gt; g[MAXN];
bool used[MAXN];
int timer, tin[MAXN], fup[MAXN];
 
void dfs (int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	for (size_t i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue;
		if (used[to])
			fup[v] = min (fup[v], tin[to]);
		else {
			dfs (to, v);
			fup[v] = min (fup[v], fup[to]);
			if (fup[to] > tin[v])
				IS_BRIDGE(v,to);
		}
	}
}
 
void find_bridges() {
	timer = 0;
	for (int i = 0; i < n; ++i)
		used[i] = false;
	for (int i = 0; i < n; ++i)
		if (!used[i])
			dfs (i);
} </code></pre>

</span>

Here, the main function calls function $find$_$bridges$ which produces necessary initialization and starts depth first search in all components of a graph.

Function $IS$_$BRIDGE(a, b)$ - is a function that will produce output to the fact that edge $(a, b)$ is a bridge.

Constant $MAXN$ at beginning of code is initialised to maximum number of nodes in the graph.

It should be noted that this does not work correctly if multiple edges are present in the graph, as it actually ignores their presence. Of course, multiple edges must not be a part of the answer, so checks must be made in the function $IS$_$BRIDGE$. Another way to work with multiple edges more accurately is to transfer the number of edges by which we entered the current node(we all need to store this additionally).

## Tasks in online judges

Some tasks in which we aim to find bridges:

- [UVA #796 "Critical Links" [difficulty: low]](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=737)
- [UVA #610 "Street Directions" [difficulty: medium]](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=551)
- [Case of the Computer Network (Codeforces Round #310 Div. 1 E) [difficulty: hard]](http://codeforces.com/problemset/problem/555/E)

####Note: Translated by [NibNalin](http://codeforces.com/profile/NibNalin)
