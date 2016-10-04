# Finding the shortest paths between all pairs of vertices - Floyd-Warshall Algorithm

Dan oriented or undirected weighted graph G from n vertices. Required to find the values ​​of all variables d_ {ij} - The length of the shortest path from vertex i to the top j .

It is assumed that the graph contains no negative weight cycles (if the response between some pairs of vertices may not exist - it will be infinitely small).

This algorithm has been simultaneously published in articles by and Stephen Warshall in 1962. However, in 1959, Bernard Roy published essentially the same algorithm, but its publication went unnoticed.

## Description of the algorithm

The key idea of the algorithm - a partition of the search process of the shortest tracks on the phase.

Before k th phase ( k = 1, \ ldots n ) Believed that in the matrix of distances d [] [] stored length of the shortest paths, which contain as the only internal vertices of the plurality of vertices \ {1, 2, \ ldots, k-1 \} (Vertices we number, starting with the unit).

In other words, before k th phase value of d [i] [j] equal to the length of the shortest path from vertex i to the top j If this path is allowed to enter only the top with numbers smaller k (Beginning and end of the path are not considered).

It is easy to make sure that this property holds for the first phase, it is sufficient in the distance matrix d [] [] write the adjacency matrix of the graph: d [i] [j] = g [i] [j] - The cost of the ribs from the top i to the top j . At the same time, if between some vertices edges not, the record should be the value of "infinity" \ infty . From the peak in itself should always record the value 0 , It is critical for the algorithm.

Suppose now that we are on k th phase, and we want to count the matrix d [] [] so that it meets the requirements have to k + 1 th phase. We fix some peaks i and j . We there are two fundamentally different cases:

    The shortest way from the top i to the top j Who is allowed to pass through the additional peaks \ {1, 2, \ ldots, k \} It coincides with the shortest route, which is allowed to pass through the top of the set \ {1, 2, \ ldots, k-1 \} .

    In this case, the d [i] [j] will not change during the transition from k on th k + 1 -th phase.

    "New" was the shortest way better than the "old" way.

    This means that the "new" shortest path passes through the top k . Just note that we do not lose generality, further considering only simple paths (ie paths not passing on some top twice).

    Then we note that if we will divide this "new" way of the apex k into two halves (one going i \ Rightarrow k And the other - k \ Rightarrow j ), Each of these halves is no longer goes to the top k . But then it turns out that the length of each of the halves was calculated by another k-1 th phase or even earlier, and it is sufficient to simply take the amount d [i] [k] + d [k] [j] , She will give the length of the "new" shortest path.

Combining these two cases, we find that k th phase is required to recalculate the length of the shortest paths between all pairs of vertices i and j in the following way:

new_d [ i ] [ j ] = min ( d [ i ] [ j ] , d [ i ] [ k ] + d [ k ] [ j ] ) ; 

Thus, all the work that is required to produce k th phase - is to iterate over all pairs of vertices and recalculate the length of the shortest path between them. As a result, after the n th phase in a distance matrix d [i] [j] length of the shortest path will be recorded between i and j or \ infty If the path between the nodes exists.

The last remark, which should be done - something that can not create a separate matrix \ Rm new \ _d [] [] for the shortest paths temporary matrix k th phase: all changes can be made directly in the matrix d [] [] . In fact, if we have improved (reduced) for a value in a matrix of distances, we could not worsen thus the length of the shortest path for any other pair of vertices processed later.

Asymptotic algorithm obviously is O (n ^ 3) .

implementation

The input program served graph defined as adjacency matrix - two-dimensional array d [] [] size n \ times n In which each element specifies the length of the edges between the vertices.

It is required to satisfy d [i] [i] = 0 for any i .

 for ( int k = 0 ; k < n ; ++ k )
	for ( int i = 0 ; i < n ; ++ i )
		for ( int j = 0 ; j < n ; ++ j )
			d [ i ] [ j ] = min ( d [ i ] [ j ] , d [ i ] [ k ] + d [ k ] [ j ] ) ; 

It is assumed that between two if some vertices have edges in adjacency matrix was recorded for a large number (large enough that it is greater than the length of any path in this graph); then this edge will always be profitable to take, and the algorithm works correctly.

However, if you do not take special measures, in the presence of edges in the graph of the negative weight, resulting in a matrix of the form may appear \ Infty-1 . \ Infty-2 , Etc., which, of course, still indicate that between the respective vertices no way at all. Therefore, if the graph of negative edges Floyd algorithm better to write so that it did not perform transitions from the states, which already is "no way":

 for ( int k = 0 ; k < n ; ++ k )
	for ( int i = 0 ; i < n ; ++ i )
		for ( int j = 0 ; j < n ; ++ j )
			if ( d [ i ] [ k ] < INF && d [ k ] [ j ] < INF )
				d [ i ] [ j ] = min ( d [ i ] [ j ] , d [ i ] [ k ] + d [ k ] [ j ] ) ; 

Restoring own ways

Easy to maintain additional information - the so-called "ancestral" in which it will be possible to restore itself the shortest path between any two given nodes in the form of a sequence of vertices.

To do this, in addition to the distance matrix d [] [] also support matrix ancestors p [] [] That for every pair of vertices will contain the number of the phase in which it was received the shortest distance between them. It is understood that the phase number is not more than a "middle" apex Seeking the shortest path, and now we just need to find the shortest path between the vertices i and p [i] [j] And between p [i] [j] and j . This yields a simple recursive algorithm restore the shortest path.

The case of real weights

If the weight of the edges of the graph is not an integer, and real, it is necessary to take into account the errors that inevitably arise when working with types float.

With respect to the algorithm of Floyd unpleasant special effect of these errors become what algorithm results may take much distance in minus due to the accumulated errors. In fact, if there is an error in the first phase \ Delta , This error may have to turn on the second iteration 2 \ Delta at -, the third 4 \ Delta , and so on.

To avoid this, the comparison algorithm Floyd should be made taking into account the error:

 if ( d [ i ] [ k ] + d [ k ] [ j ] < d [ i ] [ j ] - EPS )
	d [ i ] [ j ] = d [ i ] [ k ] + d [ k ] [ j ] ; 

The case of negative cycles

If the graph has cycles of negative weight, then formally the algorithm of Floyd-Uorshella not apply to such a graph.

In fact, for those pairs of vertices i and j Between which you can not go to a negative weight cycle, the algorithm will work correctly.

For those pairs of the vertices, for which the answer does not exist (due to the presence of the negative cycle of the path between them), Floyd's algorithm to find an answer for a number of (possibly strongly negative, but not necessarily). Nevertheless, we can improve the algorithm of Floyd that he carefully cultivated such pair of vertices and drew for them, for example, - \ Infty .

This can be done, for example, the following criterion "is not the existence of the way." Thus, even for a given graph has worked usual algorithm Floyd. Then, between the peaks i and j there is a shortest path if and only if there exists a vertex t , Accessible from i and which is accessible from j For which you are d [t] [t] <0 .

In addition, when using the Floyd algorithm for graphs with negative cycles should remember that arise during operation distance can go into much less exponentially with each phase. Therefore, action should be taken against integer overflow by limiting the distances from the bottom of any value (for example, - {\ Rm INF} ).

For more information about this task, see the separate article:. "Finding a negative cycle in the graph" . 
