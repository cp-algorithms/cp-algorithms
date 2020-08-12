<!--?title Search for connected components in a graph -->

# Search for connected components in a graph

Given an undirected graph $G$ with $n$ nodes and $m$ edges. We are required to find in it all the connected components, i.e, several groups of vertices such that within a group each vertex can be reached from another and no path exists between different groups.

## An algorithm for solving the problem

* To solve the problem, we can use Depth First Search or Breadth First Search.

* In fact, we will be doing a series of rounds of DFS: The first round will start from first node and all the nodes in the first connected component will be traversed (found). Then we find the first unvisited node of the remaining nodes, and run Depth First Search on it, thus finding a second connected component. And so on, until all the nodes are visited.

* The total asymptotic running time of this algorithm is $O(n + m)$ : In fact, this algorithm will not run on the same vertex twice, which means that each edge will be seen exactly two times (at one end and at the other end).

## Implementation

``` cpp
int n;
vector<int> g[MAXN] ;
bool used[MAXN] ;
vector<int> comp ;

void dfs(int v) {
    used[v] = true ;
    comp.push_back(v);
    for (size_t i = 0; i < (int) g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to])
            dfs(to);
    }
}

void find_comps() {
    for (int i = 0; i < n ; ++i)
        used [i] = false;
    for (int i = 0; i < n ; ++i)
        if (!used[i]) {
            comp.clear();
            dfs(i);
	        cout << "Component:" ;
            for (size_t j = 0; j < comp.size(); ++j)
                cout << ' ' << comp[j];
            cout << endl ;
        }
}
```

* The most important function that is used is `find_comps()` which finds and displays connected components of the graph.

* The graph is stored in adjacency list representation, i.e `g[i]` contains a list of vertices that have edges from the vertex `i`. The constant `MAXN` should be set equal to the maximum possible number of vertices in the graph.

* Vector `comp` contains a list of nodes in the current connected component.

## Practice Problems
 - [SPOJ: CCOMPS](http://www.spoj.com/problems/CCOMPS/)
 - [SPOJ: CT23E](http://www.spoj.com/problems/CT23E/)
 - [CODECHEF: GERALD07](https://www.codechef.com/MARCH14/problems/GERALD07)
 - [CSES : Building Roads](https://cses.fi/problemset/task/1666)