<!--?title Negative Cycle Search -->

# Finding a negative cycle in the graph

You are given a directed weighted graph $G$ with $N$ vertices and $M$ edges. Find any cycle of negative weight in it, if such a cycle exists.

In another formulation of the problem you have to find all pairs of vertices which have a path of arbitrarily small weight between them.

It is convenient to use different algorithms to solve these two versions of the problem, so we'll discuss both of them here.

## Using Bellman-Ford algorithm

Bellman-Ford algorithm allows you to check whether there exists a cycle of negative weight in the graph, and if it does, find one of these cycles.

The details of the algorithm are described in the article on Bellman-Ford algorithm. Here we'll describe only its application to this problem.

Do $N$ iterations of Bellman-Ford algorithm. If there were no changes on the last iteration, there is no cycle of negative weight in the graph. Otherwise take a vertex the distance to which has changed, and go from it via its ancestores until a cycle is found. This cycle will be the desired cycle of negative weight.

### Implementation<span class="toggle-code">Show/Hide</span>

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

## Using Floyd-Warshall algorithm

Floyd-Warshall algorithm allows to solve the second version of the problem - finding all pairs of vertices $(i, j)$ which don't have a shortest path between them (i.e. a path of arbitrarily small weight exists).

Again, the details can be found in Floyd-Warshall algorithm article, and here we describe only its application.

Run Floyd-Warshall algorithm on the graph. Iterate over all pairs of vertices $(i, j)$ and for each pair check whether they have a shortest path between them. To do this try all possibilities for a third vertex $t$, and if for one of them $d[t][t] < 0$ (i.e. it is part of a cycle of negative weight), and $t$ can be reached from $i$ and $j$ can be reached from $t$, then the path from $i$ to $j$ can have arbitrarily small weight.

### Implementation

	for ( int i = 0 ; i < n ; ++ i )
		for ( int j = 0 ; j < n ; ++ j )
			for ( int t = 0 ; t < n ; ++ t )
				if ( d [ i ] [ t ] < INF && d [ t ] [ t ] < 0 && d [ t ] [ j ] < INF )
					d [ i ] [ j ] = - INF ; 

## Practice Problems

- [UVA: Wormholes](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=499)
- [SPOJ: Alice in Amsterdam, I mean Wonderland](http://www.spoj.com/problems/UCV2013B/)
- [SPOJ: Johnsons Algorithm](http://www.spoj.com/problems/JHNSN/)
