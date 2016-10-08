<!--?title Negative Cycle Search -->

#Finding a negative cycle in the graph

A directed weighted graph G with n vertices and m edges. Required to find it in any of the negative cycle of weight, if any.

These two options to solve the problem. It is convenient different algorithms, so both of them will be discussed below.

#The decision by the algorithm of Bellman-Ford

Bellman-Ford algorithm allows you to check the presence or absence of the negative weight cycle in the graph, and if present then find one of these cycles.

We will not go into details (which are described in the article on the algorithm of Bellman-Ford ), and give only the result - how the algorithm works.

done n iterations of the algorithm of Bellman-Ford, and if at the last iteration has been no change - the negative cycle in the graph not present. Otherwise, take the top, the distance to which has changed and will go on from her ancestors until will enter the ring; this cycle will be the desired negative cycle.

#Implementation:

	struct edge {
		int a, b, cost ;
	} ;
	 
	int n, m ;
	vector < edge > e ;
	const int INF = 1000000000 ;
	 
	void solve ( ) {
		vector < int > d ( n ) ;
		vector < int > p ( n, - 1 ) ;
		int x ;
		for ( int i = 0 ; i < n ; ++ i ) {
			x = - 1 ;
			for ( int j = 0 ; j < m ; ++ j )
				if ( d [ e [ j ] . b ] > d [ e [ j ] . a ] + e [ j ] . cost ) {
					d [ e [ j ] . b ] = max ( - INF, d [ e [ j ] . a ] + e [ j ] . cost ) ;
					p [ e [ j ] . b ] = e [ j ] . a ;
					x = e [ j ] . b ;
				}
		}
	 
		if ( x == - 1 )
			cout << "No negative cycle found." ;
		else {
			int y = x ;
			for ( int i = 0 ; i < n ; ++ i )
				y = p [ y ] ;
	 
			vector < int > path ;
			for ( int cur = y ; ; cur = p [ cur ] ) {
				path. push_back ( cur ) ;
				if ( cur == y && path. size ( ) > 1 )  break ;
			}
			reverse ( path. begin ( ) , path. end ( ) ) ;
	 
			cout << "Negative cycle: " ;
			for ( size_t i = 0 ; i < path. size ( ) ; ++ i )
				cout << path [ i ] << ' ' ;
		}
	} 

#The decision by the algorithm of Floyd-Warshall

Floyd-Warshall algorithm allows to solve a second statement of the problem - when you need to find all pairs of vertices (i, j) Between which there is not the shortest path (ie, it has an infinitesimal amount).

Again, a more detailed explanation is contained in the description of the algorithm of Floyd-Warshall , but here we present only the result.

Once the algorithm of Floyd-Warshall will work for the input graph Let's brute force over all pairs of vertices (i, j) And check infinitesimal shortest path for each pair of i at j or not. To do this Let's brute over the third vertex t And if it turned out for her d [t][t] <0 (i.e. it is in a cycle of negative weight), and she is accessible from i and because it is achievable j - The path (i, j) It could have infinitesimal length.

#Implementation:

	for ( int i = 0 ; i < n ; ++ i )
		for ( int j = 0 ; j < n ; ++ j )
			for ( int t = 0 ; t < n ; ++ t )
				if ( d [ i ] [ t ] < INF && d [ t ] [ t ] < 0 && d [ t ] [ j ] < INF )
					d [ i ] [ j ] = - INF ; 

Tasks in the online judges

The list of tasks that need to search for a cycle of negative weight:
* [UVA: Wormholes](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=499)
* [SPOJ: Alice in Amsterdam, I mean Wonderland](http://www.spoj.com/problems/UCV2013B/)
* [SPOJ: Johnsons Algorithm](http://www.spoj.com/problems/JHNSN/)
