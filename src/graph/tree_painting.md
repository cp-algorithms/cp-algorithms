<!--?title Paint the edges of the tree -->

# Paint the edges of the tree

This is a fairly common task. Given a tree $G$, with $N$ vertices and $M$ edges. There are two types of queries: the first one is to paint an edge, the second one is to query the number of colored edges between two vertices.

Here we will describe a fairly simple solution (using a [segment tree](https://cp-algorithms.com/data_structures/segment_tree.html)) that will respond to each request for $O(\log N)$, by first preprocessing for $O(N + M)$.

## Decision

First, we need to implement [LCA](https://cp-algorithms.com/graph/lca.html) to reduce each query of the second kind $(i,j)$ to two queries $(a,b)$, where $a$ is the ancestor of $b$.

Now, we will describe the **preprocessing** for our problem. Run a depth-first search from the root of the tree, this depth-first search will compile a list of visits to the vertices(each vertex is added to the list when the search goes into it, and each time after the depth-first search returns from the son of the current vertex) - by the way, the same list is used by the LCA algorithm. This list will contain each edge (in the sense that if $i$ and $j$ are the ends of the edge, then there will be a place in the list where $i$ and $j$ go in a row one after another), and there will be exactly two times: in the forward direction (from $i$ to $j$, where vertex $i$ is closer to the root than vertex $j$) and in the reverse (from $j$ to $i$).

Let's build two segment trees (for sum with a single modification) according to this list: $T1$ and $T2$. The tree $T1$ will take into account each edge only in the forward direction, and the tree $T2$ - on the contrary, only in the opposite direction.

Let there be another query of the form $(i,j)$, where $i$ is the ancestor of $j$, and we need to determine how many edges are painted on the path between $i$ and $j$. Let's find $i$ and $j$ in the depth traversal list (we definitely need positions where they occur for the first time), let it be some positions $p$ and $q$ (this can be done in $O(1)$, if we calculate these positions in advance during preprocessing). Then the **answer is the sum $T1[p..q-1]$ - is the sum of $T2[p..q-1]$**.

**Why?** Consider the segment $[p;q]$ in the depth-first list. It contains edges of the path we need from $i$ to $j$ but also contains a set of edges that lie on other paths from $i$. However, there is one big difference between the edges we need and the rest of the edges: the edges we need will be listed only once, and in the forward direction, and all the other edges will meet twice: both in the forward and in the opposite direction. Hence, the difference $T1[p..q-1] - T2[p..q-1]$ will give us the answer (minus one is necessary because otherwise, we will capture an extra edge from vertex $j$ somewhere down or up). The sum query in the segment tree is executed in $O(\log N)$.

The answer to the **first type of query** (about painting any edge) is even easier - we just need to update $T1$ and $T2$, namely to perform a single modification of the element that corresponds to our edge (to find an edge in the list, again, it is possible for $O(1)$, if you perform this search in preprocessing). A single modification in the segment tree is performed in $O(log N)$.

## Implementation

Here is the full implementation of the solution, including LCA computation:

```
const int INF = 1000 * 1000 * 1000;

typedef vector <vector <int>> graph;

vector <int> dfs_list;
vector <int> ribs_list;
vector <int> h;

void dfs (int v, const graph & g, const graph & rib_ids, int cur_h = 1)
{
	h [v] = cur_h;
	dfs_list.push_back (v);
	for (size_t i = 0; i <g [v] .size (); ++ i)
		if (h [g [v] [i]] == -1)
		{
			ribs_list.push_back (rib_ids [v] [i]);
			dfs (g [v] [i], g, rib_ids, cur_h + 1);
			ribs_list.push_back (rib_ids [v] [i]);
			dfs_list.push_back (v);
		}
}

vector <int> lca_tree;
vector <int> first;

void lca_tree_build (int i, int l, int r)
{
	if (l == r)
		lca_tree [i] = dfs_list [l];
	else
	{
		int m = (l + r) >> 1;
		lca_tree_build (i + i, l, m);
		lca_tree_build (i + i + 1, m + 1, r);
		int lt = lca_tree [i + i], rt = lca_tree [i + i + 1];
		lca_tree [i] = h [lt] <h [rt]? lt: rt;
	}
}

void lca_prepare (int n)
{
	lca_tree.assign (dfs_list.size () * 8, -1);
	lca_tree_build (1, 0, (int) dfs_list.size () - 1);

	first.assign (n, -1);
	for (int i = 0; i <(int) dfs_list.size (); ++ i)
	{
		int v = dfs_list [i];
		if (first [v] == -1) first [v] = i;
	}
}

int lca_tree_query (int i, int tl, int tr, int l, int r)
{
	if (tl == l && tr == r)
		return lca_tree [i];
	int m = (tl + tr) >> 1;
	if (r <= m)
		return lca_tree_query (i + i, tl, m, l, r);
	if (l> m)
		return lca_tree_query (i + i + 1, m + 1, tr, l, r);
	int lt = lca_tree_query (i + i, tl, m, l, m);
	int rt = lca_tree_query (i + i + 1, m + 1, tr, m + 1, r);
	return h [lt] <h [rt]? lt: rt;
}

int lca (int a, int b)
{
	if (first [a]> first [b]) swap (a, b);
	return lca_tree_query (1, 0, (int) dfs_list.size () - 1, first [a], first [b]);
}


vector <int> first1, first2;
vector <char> rib_used;
vector <int> tree1, tree2;

void query_prepare (int n)
{
	first1.resize (n-1, -1);
	first2.resize (n-1, -1);
	for (int i = 0; i <(int) ribs_list.size (); ++ i)
	{
		int j = ribs_list [i];
		if (first1 [j] == -1)
			first1 [j] = i;
		else
			first2 [j] = i;
	}

	rib_used.resize (n-1);
	tree1.resize (ribs_list.size () * 8);
	tree2.resize (ribs_list.size () * 8);
}

void sum_tree_update (vector <int> & tree, int i, int l, int r, int j, int delta)
{
	tree [i] + = delta;
	if (l <r)
	{
		int m = (l + r) >> 1;
		if (j <= m)
			sum_tree_update (tree, i + i, l, m, j, delta);
		else
			sum_tree_update (tree, i + i + 1, m + 1, r, j, delta);
	}
}

int sum_tree_query (const vector <int> & tree, int i, int tl, int tr, int l, int r)
{
	if (l> r || tl> tr) return 0;
	if (tl == l && tr == r)
		return tree [i];
	int m = (tl + tr) >> 1;
	if (r <= m)
		return sum_tree_query (tree, i + i, tl, m, l, r);
	if (l> m)
		return sum_tree_query (tree, i + i + 1, m + 1, tr, l, r);
	return sum_tree_query (tree, i + i, tl, m, l, m)
		+ sum_tree_query (tree, i + i + 1, m + 1, tr, m + 1, r);
}

int query (int v1, int v2)
{
	return sum_tree_query (tree1, 1, 0, (int) ribs_list.size () - 1, first [v1], first [v2] -1)
		- sum_tree_query (tree2, 1, 0, (int) ribs_list.size () - 1, first [v1], first [v2] -1);
}


int main ()
{
	// reading the graph
	int n;
	scanf ("% d", & n);
	graph g (n), rib_ids (n);
	for (int i = 0; i <n-1; ++ i)
	{
		int v1, v2;
		scanf ("% d% d", & v1, & v2);
		--v1, --v2;
		g [v1] .push_back (v2);
		g [v2] .push_back (v1);
		rib_ids [v1] .push_back (i);
		rib_ids [v2] .push_back (i);
	}

	h.assign (n, -1);
	dfs (0, g, rib_ids);
	lca_prepare (n);
	query_prepare (n);

	for (;;) {
		if () {
			// request for painting edge x;
			// if start = true, then the edge is painted, otherwise the painting is removed
			rib_used [x] = start;
			sum_tree_update (tree1, 1, 0, (int) ribs_list.size () - 1, first1 [x], start? 1: -1);
			sum_tree_update (tree2, 1, 0, (int) ribs_list.size () - 1, first2 [x], start? 1: -1);
		}
		else {
			// query the number of colored edges on the path between v1 and v2
			int l = lca (v1, v2);
			int result = query (l, v1) + query (l, v2);
			// result - the answer to the request
		}
	}

}
```
