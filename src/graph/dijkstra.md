<!--?title Dijkstra Algorithm -->

# Dijkstra Algorithm
### Finding Shortest Paths from Given Vertex to all Other Vertices

You are given a directed or undirected weighted graph with $n$ vertices and $m$ edges. The weights of all edges are non-negative. You are also given a starting vertex $s$. Find the lengths of the shortest paths from vertex $s$ to all other vertices, and output the shortest paths themselves.

This problem is also called "single-source shortest paths problem".

## Algorithm

Here is an algorithm described by the Dutch computer scientist Edsger W. Dijkstra in 1959.

Let's create an array $d[]$ where for each vertex $v$ we store the current length of the shortest path from $s$ to $v$ $d[v]$. Initially $d[s] = 0$, and for all other vertices this length equals infinity. In a computer implementation a sufficiently large number (which is guaranteed to be greater than any possible path length) is chosen as infinity:

$$d[v] = \infty, v \ne s$$

In addition, we maintain a boolean array $u[]$ which stores for each vertex $v$ whether it's marked. Initially all vertices are unmarked:

$$u[v] = {\rm false}$$

The Dijkstra's algorithm runs for $n$ iterations. At each iteration a vertex $v$ is chosen as unmarked vertex which has the least value $d[v]$:

$$d[v] = \min_{p: u[p]={\rm false}} d[p]$$

Evidently, in the first iteration the starting vertex $s$ will be selected.

Thus selected vertex $v$ is marked. Next, from vertex $v$ **relaxations** are performed: all edges of the form $(v,to)$ are considered, and for each vertex $to$ the algorithm tries to improve the value $d[to]$. If the length of the current edge equals $len$, the code for relaxation is:

$$d[to] = \min (d[to], d[v] + len)$$

After all such edges are considered, the current iteration ends. Finally, after $n$ iterations, all vertices will be marked, and the algorithm terminates. We claim that the found values $d[v]$ are the lengths of shortest paths from $s$ to all vertices $v$.

Note that if some vertices are unreachable from the starting vertex $s$, the values $d[v]$ for them will remain infinite. Obviously, the last few iterations of the algorithm will choose those vertices, but no useful work will be done for them. Therefore, the algorithm can be stopped as soon as the selected vertex has infinite distance to it.

### Restoring Shortest Paths 

Usually one needs to know not only the lengths of shortest paths but also the shortest paths themselves. Let's see how to maintain sufficient information to restore the shortest path from $s$ to any vertex. We'll maintain an array of predecessors $p[]$ in which for each vertex $v \ne s$ $p[v]$ is the penultimate vertex in the shortest path from $s$ to $v$. Here we use the fact that if we take the shortest path to some vertex $v$ and remove $v$ from this path, we'll get a path ending in at vertex $p[v]$, and this path will be the shortest for the vertex $p[v]$. This array of predecessors can be used to restore the shortest path to any vertex: starting with $v$, repeatedly take the predecessor of the current vertex until we reach the starting vertex $s$ to get the required shortest path with vertices listed in reverse order. So, the shortest path $P$ to the vertex $v$ is equal to:

$$P = (s, \ldots, p[p[p[v]]], p[p[v]], p[v], v)$$

Building this array of predecessors is very simple: for each successful relaxation, i.e. when for some selected vertex $v$, there is an improvement in the distance to some vertex $to$, we update the predecessor vertex for $to$ with vertex $v$:

$$p[to] = v$$

## Proof

The main assertion on which Dijkstra's algorithm correctness is based is the following:

**After any vertex $v$ becomes marked, the current distance to it $d[v]$ is the shortest, and will no longer change.**

The proof is done by induction. For the first iteration this statement is obvious: the only marked vertex is $s$, and the distance to is $d[s] = 0$ is indeed the length of the shortest path to $s$. Now suppose this statement is true for all previous iterations, i.e. for all already marked vertices; let's prove that it is not violated after the current iteration completes. Let $v$ be the vertex selected in the current iteration, i.e. $v$ is the vertex that the algorithm will mark. Now we have to prove that $d[v]$ is indeed equal to the length of the shortest path to it $l[v]$.

Consider the shortest path $P$ to the vertex $v$. This path can be split into two parts: $P_1$ which consists of only marked nodes (at least the starting vertex $s$ is part of $P_1$), and the rest of the path $P_2$ (it may include a marked vertex, but it always starts with an unmarked vertex). Let's denote the first vertex of the path $P_2$ as $p$, and the last vertex of the path $P_1$ as $q$.

First we prove our statement for the vertex $p$, i.e. let's prove that $d[p] = l[p]$. This is almost obvious: on one of the previous iterations we chose the vertex $q$ and performed relaxation from it. Since (by virtue of the choice of vertex $p$) the shortest path to $p$ is the shortest path to $q$ plus edge $(p,q)$, the relaxation from $q$ set the value of $d[p]$ to the length of the shortest path $l[q]$.

Since the edges' weights are non-negative, the length of the shortest path $l[p]$ (which we just proved to be equal to $d[p]$) does not exceed the length $l[v]$ of the shortest path to the vertex $v$. Given that $l[v] \le d[v]$ (because Dijkstra's algorithm could not have found a shorter way than the shortest possible one), we get the inequality:

$$d[p] = l[p] \le l[v] \le d[v]$$

On the other hand, since both vertices $p$ and $v$ are unmarked, and the current iteration chose vertex $v$, not $p$, we get another inequality:

$$d[p] \ge d[v]$$

From these two inequalities we conclude that $d[p] = d[v]$, and then from previously found equations we get:

$$d[v] = l[v]$$

Q.E.D.

## Implementation

Dijkstra's algorithm performs $n$ iterations. On each iteration it selects an unmarked vertex $v$ with the lowest value $d[v]$, marks it and checks all the edges $(v, to)$ attempting to improve the value $d[to]$.

The running time of the algorithm consists of:

* $n$ searches for a vertex with the smallest value $d[v]$ among $O(n)$ unmarked vertices
* $m$ relaxation attempts

For the simplest implementation of these operations on each iteration vertex search requires $O(n)$ operations, and each relaxation can be performed in $O(1)$. Hence, the resulting asymptotic behavior of the algorithm is:

$$O(n^2+m)$$ 

```cpp
const int INF = 1000000000;

int main() {
    int n;
    /*... read n ...*/
   
    vector<vector<pair<int, int > > > g(n);
    /*... read graph ...*/
    
    int s = ...; // read starting vertex

    vector<int> d(n, INF), p(n);
    
    d[s] = 0;
    
    vector<char> u(n);
    
    for (int i = 0; i < n; ++i) {
        int v = -1;
        
        for (int j = 0; j < n; ++j)
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        
        if (d[v] == INF)
            break;
        
        u[v] = true;
        
        for (size_t j = 0; j < g[v].size(); ++j) {
            
            int to = g[v][j].first,
            int len = g[v][j].second;
            
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
}
```

Here the graph $g$ is stored as adjacency list: for each vertex $v$ $g[v]$ contains the list of edges going from this vertex, i.e. the list of `pair<int,int>` where the first element in the pair is the vertex at the other end of the edge, and the second element is the edge weight.

First of all, the code initializes arrays: distances $d[]$, labels $u[]$ and predecessors $p[]$. Then it performs $n$ iterations. At each iteration the vertex $v$ is selected which has the smallest distance $d[v]$ among all the unmarked vertices. If the distance to selected vertex $v$ is equal to infinity, the algorithm stops. Otherwise the vertex is marked, and all the edges going out from this vertex are checked. If relaxation along the edge is possible (i.e. distance $d[to]$ can be improved), the distance $d[to]$ and predecessor $p[to]$ are updated.

After performing all the iterations array $d[]$ stores the lengths of the shortest paths to all vertices, and array $p[]$ stores the predecessors of all vertices (except starting vertex $s$). The path to any vertex $t$ can be restored in the following way:

```cpp
vector<int> path;

for (int v = t; v != s; v = p[v])
    path.push_back(v);
path.push_back(s);

reverse(path.begin(), path.end());
```

## References

* Edsger Dijkstra. A note on two problems in connexion with graphs [1959]
* Thomas Cormen, Charles Leiserson, Ronald Rivest, Clifford Stein. Introduction to Algorithms [2005]

## Practice Problems
* [Timus - Ivan's Car](http://acm.timus.ru/problem.aspx?space=1&num=1930) [Difficulty:Medium]
* [Timus - Sightseeing Trip](http://acm.timus.ru/problem.aspx?space=1&num=1004)
* [SPOJ - SHPATH](http://www.spoj.com/problems/SHPATH/) [Difficulty:Easy]
* [Codeforces - Dijkstra?](http://codeforces.com/problemset/problem/20/C) [Difficulty:Easy]
* [Codeforces - Shortest Path](http://codeforces.com/problemset/problem/59/E)
* [Codeforces - Jzzhu and Cities](http://codeforces.com/problemset/problem/449/B)
* [Codeforces - The Classic Problem](http://codeforces.com/problemset/problem/464/E)
* [Codeforces - President and Roads](http://codeforces.com/problemset/problem/567/E)
* [Codeforces - Complete The Graph](http://codeforces.com/problemset/problem/715/B)
* [TopCoder - SkiResorts](https://community.topcoder.com/stat?c=problem_statement&pm=12468)
* [TopCoder - MaliciousPath](https://community.topcoder.com/stat?c=problem_statement&pm=13596)
