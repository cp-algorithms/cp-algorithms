<!--?title Floyd-Warshall algorithm -->

# Floyd-Warshall Algorithm

**For shortests paths between all pairs of vertices in a graph**

Given an undirected weighted graph G with n vertices. It is required to find the values of all variables d<sub>ij</sub> (<i>The length of the shortest path from vertex i to the vertex j</i>) .

The graph may have negative weight edges, but no negative weight cycles (for then the shortest path is undefined).

This algorithm can also be used to detect the presence of negative cycles—the graph has one if at the end of the algorithm, the distance from a vertex v to itself is negative. 

This algorithm has been simultaneously published in articles by  Robert Floyd and Stephen Warshall in 1962. However, in 1959, Bernard Roy published essentially the same algorithm, but its publication went unnoticed.

## Description of the algorithm

The key idea of the algorithm - Partitioning the process of finding the shortest path between any two vertices, in incremental phases.

Let us number the vertices starting from 1 to n.
The Matrix of Distances is d[][].

Before k<sup>th</sup> phase $( k = 1 .... n )$, the d[i][j] for any vertices i and j, stores the length of the shortest path between the vertex i and vertex j, which contain only the vertices ${1, 2, ..... , k-1}$ as internal vertices in the path.

In other words, before k<sup>th</sup> phase value of d[i][j] equal to the length of the shortest path from vertex i to the vertex j, if this path is allowed to enter only the vertex with numbers smaller k (Beginning and end of the path are not considered).

It is easy to make sure that this property holds for the first phase. For k = 0, we can fill matrix as:
    
    /* Assuming weight(i, j) is the cost of the direct edge from the vertex i to the vertex j
    weight(i ,j) = 0 if no edge between vertex i and vertex j exits and
    weight(i, j) is non-zero if the edge between vertex i and vertex j exists */
    
    if ( weight(i, j) != 0) // direct edge between i and j exists
        d[i][j] = weight(i, j);
    else // direct edge between i and j does not exist
        d[i][j] = INF;

At the same time, if between some vertices i and j, direct edge not exists, the d[i][j] should be the value of INF (some high positive value denoting infinity) . As we shall see later, it is a requirement for the algorithm.

Suppose now that we are on k<sup>th</sup> phase, and we want to compute the matrix d[][] so that it meets the requirements of having (k + 1)<sup>th</sup> phase. We fix some vertices i and j . Then there are two fundamentally different cases:

* The shortest way from the vertex i to the vertex j which is allowed to pass through the internal vertices in the set ${1, 2, ....., k}$, coincides with the shortest path, which is allowed to pass through the internal vertices in the set ${1, 2, ....., k-1}$.
    
    In this case, the d[i][j] will not change during the transition from k on th (k + 1)<sup>th</sup> phase.

* "New" is the shorter path better than the "Old" way.
    
    This means that the "New" shorter path passing through the vertex k . Just note that we do not lose generality, further     considering only simple paths (i.e. paths not passing through some vertex twice).

    Then we note that if we divide this "New" way of through vertex k into two halves (one going i -> k, and, the other going from k -> j ), each of these halves no longer pass through the vertex k. But then it turns out that the length of each of the halves was calculated by another (k-1)<sup>th</sup> phase or even earlier than (k-1), and it is sufficient to simply take the amount d[i][k] + d[k][j], it will give the length of the "New" shortest path.

Combining these two cases, we find that k<sup>th</sup> phase is required to recalculate the length of the shortest paths between all pairs of vertices i and j in the following way:

    new_d[i][j] = min ( d[i][j] , d[i][k] + d[k][j] ) ; 

Thus, all the work that is required to produce k<sup>th</sup> phase is to iterate over all pairs of vertices and recalculate the length of the shortest path between them. As a result, after the n<sup>th</sup> phase, in the Distance Matrix, the value of d[i][j] is the length of the shortest path between pair of vertices i and j, or, is INF if the path between the vertices i and j does not exist.

A last remark - we don't need to create a separate matrix of distances d<sub>new</sub>[][] for temporarily storing shortest paths of k<sup>th</sup> phase while transitioning to (k + 1)<sup>th</sup>, i.e. all changes can be made directly in the matrix d[][] at any phase. In fact, at any k<sup>th</sup> phase we are at most improving (reducing) value of any path in matrix of distances, hence, we cannot worsen the length of the shortest path for any pair of the vertices that are to be processed in (k+1)<sup>th</sup> phase or later.

Asymptotic complexity of the algorithm obviously is O( n<sup>3</sup> ) .

## Implementation

Let d[][] is a 2-D array of size n x n, which is filled according to the 0<sup>th</sup> phase as explained earlier.

It is required to have d[i][i] = 0 for any i at the 0<sup>th</sup> phase.

     for ( int k = 0 ; k < n ; ++k )
        for ( int i = 0 ; i < n ; ++i )
            for ( int j = 0 ; j < n ; ++j )
                d[i][j] = min ( d[i][j] , d[i][k] + d[k][j] ) ; 

It is assumed that if there is no edge between two any vertices i and j, the adjacency matrix at d[i][j] recorded a large number (large enough so that it is greater than the length of any path in this graph), then this edge will always be unprofitable to take, and the algorithm will work correctly.

However, in the presence of negative weight edges in the graph, special measures are not taken, the resulting values in matrix may appear of the form INF-1,  INF-2, etc., which, of course, still indicates that between the respective vertices no path at all exists. Therefore, if the graph is having negative weight edges, it is better to write Floyd-Warshall algorithm in the following way, so that it does not perform transitions from states, which already are "non-existence of the path":

     for ( int k = 0 ; k < n ; ++k )
        for ( int i = 0 ; i < n ; ++i )
            for ( int j = 0 ; j < n ; ++j )
                if ( d [i][k] < INF && d [k][j] < INF )
                    d[i][j] = min ( d[i][j] , d[i][k] + d[k][j] ) ; 

## Retrieving the sequence of vertices in the shortest path

It is easy to maintain additional information of "ancestors" along with the standard Floyd-Warshall Algorithm, in which it will be possible to retrieve the shortest path between any two given vertices in the form of a sequence of vertices.

For this, in addition to the distance matrix d[][], a matrix of ancestors p[][] must be maintained, which for each pair of nodes will contain the number of the phase where the shortest distance between them was last modified. It is clear that the number of the phase is nothing more than the middle vertex of the desired shortest path, and now we just need to find the shortest path between vertices i and p[i][j], and between p[i][j] and j. This leads to a simple recursive reconstruction algorithm of the shortest path.

## The case of real weights

If the weights of the edges of the graph are not integer, and are real, it is necessary to take into account the errors that inevitably arise when working with float types.

With respect to the Floyd-Warshall Algorithm, the unpleasant effects of the real types may result in distances going much into negative due to accumulated errors. In fact, if there is an error in the first phase, say, (EPS), this error may propagate in turn to the second iteration - (2*EPS), at the third iteration - (4*EPS) , and so on.

To avoid this, the  can be modified to take the error(EPS) into account, by using following type of comparison:

     if ( d[i][k] + d[k][j] < d[i][j] - EPS )
        d[i][j] = d[i][k] + d[k][j] ; 

## The case of negative cycles

If the graph is having negative weight cycle(s), then formally, to such a graph, the Floyd-Warshall Algorithms does not apply.

But, in fact, for all those pairs of vertices i and j between which we can not go to a negative weight cycle, the algorithm will work correctly.

For the pair of vertices, the answer for which does not exist (due to the presence of a negative cycle in the path between them), the Floyd algorithm will store a certain number (perhaps highly negative, but not necessarily). However, it is possible to improve the algorithm of Floyd, if one carefully treats such pairs of vertices, and outputs them, for example -INF.

This can be done, for example, following the criterion "non-existence of the path". So, let us run the usual Floyd-Warshall algorithm for a given graph. Then a shortest path between vertices i and j does not exist, if and only if, there is a vertex t that is reachable from i and also from j, for which d[t][t] < 0.

In addition, when using the Floyd-Warshall algorithm for graphs with negative cycles, we should keep in mind that in the process of working with Floyd-Warshall Algorithm, situations may arise in which distances can strongly go into the negative, exponentially with each phase. Therefore, integer overflow must be handled by limiting the distance from the bottom of some value (e.g. -INF).

To learn more about finding negative cycles in a graph, see separate article: [Finding a negative cycle in the graph](./graph/finding-negative-cycle-in-graph.html).

## Practice Problems
 - [UVA: Page Hopping](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=762)
 - [SPOJ: Possible Friends](http://www.spoj.com/problems/SOCIALNE/)
 - [CODEFORCES: Greg and Graph](http://codeforces.com/problemset/problem/295/B)
 