<!--?title Floyd-Warshall algorithm -->

# Floyd-Warshall Algorithm

**For shortest paths between all pairs of vertices in a graph**

Given an undirected weighted graph $G$ with $n$ vertices. The task is to find the values of all variables $d_{ij}$ (<i>The length of the shortest path from vertex i to the vertex j</i>) .

The graph may have negative weight edges, but no negative weight cycles (for then the shortest path is undefined).

This algorithm can also be used to detect the presence of negative cycles. The graph has a negative cycle if at the end of the algorithm, the distance from a vertex $v$ to itself is negative. 

This algorithm has been simultaneously published in articles by  Robert Floyd and Stephen Warshall in 1962. However, in 1959, Bernard Roy published essentially the same algorithm, but its publication went unnoticed.

## Description of the algorithm

The key idea of the algorithm is to partition the process of finding the shortest path between any two vertices to several incremental phases.

Let us number the vertices starting from 1 to $n$.
The Matrix of Distances is $d[ ][ ]$.

Before $k^{th}$ phase $( k = 1 ... n )$, the $d[i][j]$ for any vertices $i$ and $j$, stores the length of the shortest path between the vertex $i$ and vertex $j$, which contain only the vertices {${1, 2, ..., k-1}$} as internal vertices in the path.

In other words, before $k^{th}$ phase the value of $d[i][j]$ is equal to the length of the shortest path from vertex $i$ to the vertex $j$, if this path is allowed to enter only the vertex with numbers smaller $k$ (the beginning and end of the path are not restricted by this property).

It is easy to make sure that this property holds for the first phase. For $k = 0$, we can fill matrix as:

```cpp   
/* Assuming weight(i, j) is the cost of the direct edge from the vertex i to the vertex j
weight(i ,j) = 0 if no edge between vertex i and vertex j exits and
weight(i, j) is non-zero if the edge between vertex i and vertex j exists */

if ( weight(i, j) != 0) // direct edge between i and j exists
    d[i][j] = weight(i, j);
else // direct edge between i and j does not exist
    d[i][j] = INF;
```

At the same time, if there is no edge from $i$ to $j$, $d[i][j]$ should be $\infty$ (some high positive value denoting infinity). As we shall see later, it is a requirement for the algorithm.

Suppose now that we are in the $k^{th}$ phase, and we want to compute the matrix $d[ ][ ]$ so that it meets the requirements for the $(k + 1)^{th}$ phase. We fix some vertices $i$ and $j$. Then there are two fundamentally different cases:

* The shortest way from the vertex i to the vertex j which is allowed to pass through the internal vertices in the set {${1, 2, ....., k}$}, coincides with the shortest path, which is allowed to pass through the internal vertices in the set {${1, 2, ....., k-1}$}.
    
    In this case, the $d[i][j]$ will not change during the transition from k on th $(k + 1)^{th}$ phase.

* "New" is the shorter path better than the "Old" way.
    
    This means that the "New" shorter path passing through the vertex $k$ . Just note that we do not lose generality, further considering only simple paths (i.e. paths not passing through some vertex twice).

    Then we note that if we divide this "New" way of through vertex $k$ into two halves (one $i \to k$, and, the other $k \to j$ ), each of these halves no longer pass through the vertex $k$. But then it turns out that the length of each of the halves was calculated by another $(k-1)^{th}$ phase or even earlier than $(k-1)$, and it is sufficient to simply take the amount $d[i][k] + d[k][j]$, it will give the length of the "New" shortest path.

Combining these two cases, we find that $k^{th}$ phase is required to recalculate the length of the shortest paths between all pairs of vertices $i$ and $j$ in the following way:

```cpp
new_d[i][j] = min ( d[i][j] , d[i][k] + d[k][j] ) ; 
```

Thus, all the work that is required to produce $k^{th}$ phase is to iterate over all pairs of vertices and recalculate the length of the shortest path between them. As a result, after the $n^{th}$ phase, in the Distance Matrix, the value of $d[i][j]$ is the length of the shortest path between pair of vertices $i$ and $j$, or, is $\infty$ if the path between the vertices $i$ and $j$ does not exist.

A last remark - we don't need to create a separate matrix of distances $d_{new}[ ][ ]$ for temporarily storing shortest paths of $k^{th}$ phase while transitioning to $(k + 1)^{th}$, i.e. all changes can be made directly in the matrix $d[ ][ ]$ at any phase. In fact, at any $k^{th}$ phase we are at most improving (reducing) value of any path in matrix of distances, hence, we cannot worsen the length of the shortest path for any pair of the vertices that are to be processed in $(k+1)^{th}$ phase or later.

Asymptotic complexity of the algorithm obviously is $O(n^3)$ .

## Implementation

Let $d[][]$ is a $2-D$ array of size n x n, which is filled according to the $0^{th}$ phase as explained earlier.

It is required to have $d[i][i] = 0$ for any $i$ at the $0^{th}$ phase.

```cpp
 for ( int k = 0 ; k < n ; ++k )
    for ( int i = 0 ; i < n ; ++i )
        for ( int j = 0 ; j < n ; ++j )
            d[i][j] = min ( d[i][j] , d[i][k] + d[k][j] ) ; 
```

It is assumed that if there is no edge between two any vertices $i$ and $j$, the adjacency matrix at $d[i][j]$ contains a large number (large enough so that it is greater than the length of any path in this graph), then this edge will always be unprofitable to take, and the algorithm will work correctly.

However, in the presence of negative weight edges in the graph, special measures are not taken, the resulting values in matrix may appear of the form $\infty - 1$,  $\infty - 2$, etc., which, of course, still indicates that between the respective vertices no path at all exists. Therefore, if the graph is having negative weight edges, it is better to write Floyd-Warshall algorithm in the following way, so that it does not perform transitions from states, which already are "non-existence of the path":

```cpp
for ( int k = 0 ; k < n ; ++k )
    for ( int i = 0 ; i < n ; ++i )
        for ( int j = 0 ; j < n ; ++j )
            if ( d [i][k] < INF && d [k][j] < INF )
                d[i][j] = min ( d[i][j] , d[i][k] + d[k][j] ) ; 
```

## Retrieving the sequence of vertices in the shortest path

It is easy to maintain additional information of "ancestors" along with the standard Floyd-Warshall Algorithm, in which it will be possible to retrieve the shortest path between any two given vertices in the form of a sequence of vertices.

For this, in addition to the distance matrix $d[ ][ ]$, a matrix of ancestors $p[ ][ ]$ must be maintained, which for each pair of nodes will contain the number of the phase where the shortest distance between them was last modified. It is clear that the number of the phase is nothing more than the middle vertex of the desired shortest path, and now we just need to find the shortest path between vertices $i$ and $p[i][j]$, , and, between $p[i][j]$ and $j$. This leads to a simple recursive reconstruction algorithm of the shortest path.

## The case of real weights

If the weights of the edges of the graph are not integer, and are real, it is necessary to take into account the errors that inevitably arise when working with float types.

With respect to the Floyd-Warshall Algorithm, the unpleasant effects of the real types may result in distances going much into negative due to accumulated errors. In fact, if there is an error in the first phase, say, $\Delta$, this error may propagate in turn to the second iteration  as $(2 * \Delta)$, at the third iteration as $(4 * \Delta)$ , and so on.

To avoid this, the  can be modified to take the error(EPS = $\Delta$) into account, by using following type of comparison:

```cpp
if ( d[i][k] + d[k][j] < d[i][j] - EPS )
    d[i][j] = d[i][k] + d[k][j] ; 
```

## The case of negative cycles

If the graph is having negative weight cycle(s), then formally, to such a graph, the Floyd-Warshall Algorithms does not apply.

But, in fact, for all those pairs of vertices i and j between which we can not go to a negative weight cycle, the algorithm will work correctly.

For the pair of vertices, the answer for which does not exist (due to the presence of a negative cycle in the path between them), the Floyd algorithm will store a certain number (perhaps highly negative, but not necessarily). However, it is possible to improve the algorithm of Floyd, if one carefully treats such pairs of vertices, and outputs them, for example -INF.

This can be done, for example, following the criterion "non-existence of the path". So, let us run the usual Floyd-Warshall algorithm for a given graph. Then a shortest path between vertices $i$ and $j$ does not exist, if and only if, there is a vertex $t$ that is reachable from $i$ and also from $j$, for which $d[t][t] \lt 0$.

In addition, when using the Floyd-Warshall algorithm for graphs with negative cycles, we should keep in mind that in the process of working with Floyd-Warshall Algorithm, situations may arise in which distances can strongly go into the negative, exponentially with each phase. Therefore, integer overflow must be handled by limiting the distance from the bottom of some value (e.g. -INF).

To learn more about finding negative cycles in a graph, see separate article: [Finding a negative cycle in the graph](./graph/finding-negative-cycle-in-graph.html).

## Practice Problems
 - [UVA: Page Hopping](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=762)
 - [SPOJ: Possible Friends](http://www.spoj.com/problems/SOCIALNE/)
 - [CODEFORCES: Greg and Graph](http://codeforces.com/problemset/problem/295/B)
 - [SPOJ: CHICAGO - 106 miles to Chicago](http://www.spoj.com/problems/CHICAGO/)
 * [UVA 10724 - Road Construction](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1665)
 * [UVA  117 - The Postal Worker Rings Once](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=53)
 * [Codeforces - Traveling Graph](http://codeforces.com/problemset/problem/21/D)
 * [UVA - 1198 - The Geodetic Set Problem](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3639)
 * [UVA - 10048 - Audiophobia](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=989)
 * [UVA - 125 - Numbering Paths](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=61)
 * [LOJ - Travel Company](http://lightoj.com/volume_showproblem.php?problem=1221)
 * [UVA 423 - MPI Maelstrom](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=364)
 * [UVA 1416 - Warfare And Logistics](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4162)
 * [UVA 1233 - USHER](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3674)
 * [UVA 10793 - The Orc Attack](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1734)
 * [UVA 10099 The Tourist Guide](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1040)
 * [UVA 869 - Airline Comparison](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=810)
 * [UVA 13211 - Geonosis](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5134)
 * [SPOJ - Defend the Rohan](http://www.spoj.com/problems/ROHAAN/)
 * [Codeforces - Roads in Berland](http://codeforces.com/contest/25/problem/C)
 * [Codeforces - String Problem](http://codeforces.com/contest/33/problem/B)
 * [GYM - Manic Moving (C)](http://codeforces.com/gym/101223)
 * [SPOJ - Arbitrage](http://www.spoj.com/problems/ARBITRAG/)
 * [UVA - 12179 - Randomly-priced Tickets](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3331)
 * [LOJ - 1086 - Jogging Trails](http://lightoj.com/volume_showproblem.php?problem=1086)
 * [SPOJ - Ingredients](http://www.spoj.com/problems/INGRED/)
