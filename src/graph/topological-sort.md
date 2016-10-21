<!--?title Topological Sorting -->
#  Topological Sorting

Given a directed graph with `n` vertices and `m` edges. You want to **renumber the vertices** so that every edge led from the top with a smaller number in the top with a large.

In other words, you want to find a permutation of the vertices **(topological order)** corresponding to the order defined by all edges of the graph.

Topological sort can be **not only** (for example, if the graph is empty; or if there are three such vertices `a`, `b`, `c`, what `a` is the way in `b` and in `c`, but neither `b` in `c` nor out `c` to `b` get them).

Topological sorting **may not** exist at all - if the graph contains cycles (because there is a contradiction: there is a path from one vertex to another, and Vice versa).

A **common problem** for topological sorting next.... There are n variables whose values are unknown to us. We know only about some pairs of variables, one variable less than the other. You want to check, is not controversial whether these inequalities, and if not, to give the variables in ascending order (if the answer to any issue). It is easy to notice that this is exactly the task is about finding a topological sort of the graph of `n` vertices.

## The Algorithm

For the solution we will use a depth-first-search.

Assume that the graph is acyclic, i.e. there is a solution. What makes the depth? When you run out of some of the peaks `v` he tries to run along all edges emanating from `v`. Along those edges, the ends of which have already been previously visited, it doesn't pass, and along the rest goes and causes themselves from their ends.

Thus, by the time of the call, {\rm dfs}(v) all vertices that are reachable from `v` either directly (one edge), and indirectly (by the way) - all such vertices already visited. Therefore, if we at the time of exit from {\rm dfs}(v) add our peak in the beginning of a list, in the end, this list will get a **topological sort**.

These explanations can also be presented in a somewhat different light, through the concept of **"time out"** of depth. Output time for each vertex `v` is the point at which the finished challenge {\rm dfs}(v) the depth of it (the times, when you can zanemarivali from 1 before n). It is easy to understand that the depth-first-exit time of any vertex `v` is always greater than the exit time of all vertices reachable from it (since they were visited either before the call {\rm dfs}(v)or during it). Thus, the desired topological sort is sorting in descending order times out.

## Implementation

Here is an implementation, assuming that the graph is acyclic, i.e. the desired topological sort exists. If necessary, check the graph on acyclicity easy to insert into the depth, as described in the article on depth.

`C++` implementation <span class="toggle-code">Show/Hide</span>

```cpp
int n; // number of vertices
vector<int> g[MAXN]; // count
bool used[MAXN];
vector<int> ans;
 
void dfs (int v) {
 used[v] = true;
    for (size_t i=0; i<g[v].size(); ++i) {
	    int to = g[v][i];
	    if (!used[to])
 dfs (to);
    }
 ans.push_back (v);
}
 
void topological_sort() {
    for (int i=0; i<n; ++i)
 used[i] = false;
 ans.clear();
    for (int i=0; i<n; ++i)
	    if (!used[i])
 dfs (i);
 reverse (ans.begin(), ans.end());
}
```

Here the constant **MAXN** value must be set equal to the maximum possible number of vertices in the graph.

The main function of the solution is topological_sort, it initializes marking depth, starts it, and answer the result in the vector \rm ans.

## Practice Problems

The task list in which you want to search topological sorting:

- [SPOJ TOPOSORT "Topological Sorting" [difficulty: easy]](http://www.spoj.com/problems/TOPOSORT/)
- [UVA #10305 "Ordering Tasks" [difficulty: easy]](https://z5h64q92x9.net/proxy_u/ru-en.en/uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1246)
- [UVA #124 "Following Orders" [difficulty: easy]](https://z5h64q92x9.net/proxy_u/ru-en.en/uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=60)
- [UVA #200 "Rare Order" [difficulty: easy]](https://z5h64q92x9.net/proxy_u/ru-en.en/uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=136)
