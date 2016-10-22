<!--?title Dijkstra Algorithm -->

# Dijkstra Algorithm

**Shortest paths from given vertex to all other**

## Problem Statement

Given a directed or undirected weighted graph with $n$ vertices and $m$ edges. The weights of all edges are non-negative. Provided some starting vertex s. You want to find the length of shortest paths from a vertex $s$ to all other vertices, and provide a way to make themselves shortest paths.

This is called the "single-source shortest path problem".

## Algorithm

Here is an algorithm described by the Dutch Explorer Edsger W. Dijkstra in 1959.

Let's create an array $d[]$ where for each vertex v we store the current length $d[v]$ of the shortest path from $s$ to $v$. Initially $d[s] = 0$, and for all other vertices, this length is equal to $\infty$ (when implemented on a computer, usually a sufficiently large number, certainly more possible path length, is chosen as infinite):

$$d[v] = \infty, v \ne s$$

In addition, for each vertex v we store whether it's marked or unmarked, i.e. we have a Boolean array $u[]$. Initially all vertices are unmarked, i.e.

$$u[v] = {\rm false}$$

The Dijkstra's algorithm consists of $n$ iterations. At the next iteration is chosen vertex $v$ with the least value $d[v]$ among the not yet marked, i.e.:

$$d[v] = \min_{p\ u[p]={\rm false}} d[p]$$

(Of course, in the first iteration, the starting vertex $s$ will be selected.)

Thus the selected vertex $v$ is marked. Further, in the current iteration, for vertex v, we perform <b>relaxation</b>: iterate all edges of the form $(v,to)$ i.e. edges emnating from the vertex $v$, and for each such vertex $to$, the algorithm tries to improve the value $d[to]$. Let the length of the current edge equal $len$, then in code, what relaxation looks like:

$$d[to] = \min (d[to], d[v] + {\rm len})$$

As this current iteration ends, the algorithm proceeds to the next iteration (again selects some vertex $v$ with the least $d[v]$ and perfoms relaxation from it, etc.). In the end, after $n$ iterations, all vertices will be marked, and the algorithm terminates. It is believed that the found value $d[v]$ is the desired length of shortest path from $s$ to $v$.

It should be noted that if not all the vertices are reachable from the vertex $s$, the values $d[v]$ for them will remain $\infty$. It is clear that the last few iterations of the algorithm will just choose those vertices, but no useful work will be done by these iterations (since an infinite distance cannot relax other edges emnating from these vertices). Therefore, the algorithm can be stopped as soon as the selected vertex is having infinite distance.

## Restoring shortest paths 

Of course, you usually need to know not only the lengths of shortest path but also the shortest path itself. So, let us see how to maintain information sufficient for restoration of the shortest path from $s$ to any vertex. For this, we maintain an <b>array of predecessor</b>: $p[]$ in which for each vertex $v \ne s$, $p[v]$ stores the last vertex from which the vertex $v$ emnated to form the shortest path length $d[v]$. Here we use the fact that if we take the shortest path to some vertiex $v$, and then remove $v$ from this path, we get a path ending in at vertex $p[v]$, and this path will be the shortest for the vertex $p[v]$ with its predecessor being $p[p[v]]$. So, if we have this array of predecessors, then the shortest path can be restored using it, each time taking a predecessor of the current vertex, until we reach the starting vertex $s$ — so we get the desired shortest path, but in reverse order. So, the shortest path $P$ to the vertex $v$ is equal to:

$$P = (s, \ldots, p[p[p[v]]], p[p[v]], p[v], v)$$

Now, all that remains is to understand how to build this array of predecessors. However, that's very simple: at each successful relaxation, i.e., when for some selected vertex $v$, there is improvement in the distance of some vertex $to$, we store that the predecessor vertex for $to$ is vertex $v$:

$p[to] = v$

## Proof

The main assertion based on the correctness of Dijkstra's algorithm, is the following. 

<b> After any vertex $v$ becomes marked, the current distance $d[v]$ to it is the shortest, and, hence, will no longer change.</b>

The proof will be done by induction. For the first iteration its validity is obvious i.e for the vertex $s$ the distance is $d[s] = 0$, which is the length of the shortest path to $s$. Now suppose this statement is $true$ for all previous iterations, i.e. for all already marked vertices; we prove that it is not violated after execution of the current iteration. Let $v$ be the vertex selected in the current iteration, i.e., $v$ is the vertex that the algorithm is going to mark. Now we have to prove that $d[v]$ is equal to the length of the shortest path to it (we denote this length using $l[v]$).

Consider a shortest path $P$ to the vertex $v$. Clearly, this path can be divided into two ways: $P_1$ consisting of only marked nodes (at least starting vertex $s$ is in the path), and the rest of the way $P_2$ (it may include a marked vertex, but starts always with unmarked). Let us denote the $p$ as first vertex of the path $P_2$, and $q$ as the last vertex of the path $P_1$.

First we prove our statement for the vertex $p$, i.e., let us prove the equality $d[p] = l[p]$. However, this is almost obvious: as, on one of the previous iterations, we chose the vertex $q$ and performed relaxation from it. Since (by virtue of the choices of vertices $p$) shortest path to $p$ equals the shortest path to vertex $q$ plus edge $(p,q)$. Hence while performing the relaxation from $q$, the value $d[p]$ is set to be the desired value.

Due to the nonnegativity of the costs of edges the length of the shortest path $l[p]$ (we just proved it to be equal to $d[p]$) does not exceed the length $l[v]$ of the shortest path to the vertex $v$. Given that $l[v] \le d[v]$ (because Dijkstra's algorithm could not find a shorter way than this, even if possible), finally we get the inequality:

$$d[p] = l[p] \le l[v] \le d[v]$$

On the other hand, since and vertices $p$ and $v$ are unmarked, and, the current iteration chose vertex $v$, not $p$, we obtain another inequality:

$$d[p] \ge d[v]$$

From these two inequalities we conclude the equality $d[p] = d[v]$, and then from this inequality, we get:

$$d[v] = l[v]$$

what we wanted to prove.

## Implementation

So, Dijkstra's algorithm performs $n$ iterations. Each iteration selects an unmarked vertex $v$ with the lowest value $d[v]$. This vertex $v$ is marked, and then all the edges emnating from this vertex $v$ are checked. Along each edge $(v,to)$ it attempts to improve the value $d[to]$ where $to$ is the other end of the edge.

The running time of the algorithm consists of:

* $n$ times: searches for a vertex with the smallest value $d[v]$ among all the unmarked vertices, i.e., among the O(n) vertices
* $m$ times: attempts relaxation

For the simplest implementation of these operations, for $n$ iterations, searching requires $O(n)$ operations, and each relaxation can be performed in $O(1)$. Hence, the resulting asymptotic behavior of the algorithm is:

$$O(n^2+m)$$ 

## Implementation:

```cpp
const int INF = 1000000000;

int main() {
    int n;
    /*... read n ...*/
   
    vector < vector < pair < int, int > > > g (n);
    /*... reading graph ...*/
    
    int s = ...; // starting vertex

    vector < int > d (n, INF), p (n);
    
    d[s] = 0;
    
    vector<char> u (n);
    
    for (int i=0; i<n; ++i) {
        int v = -1;
        
        for (int j=0; j<n; ++j)
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        
        if (d[v] == INF)
            break;
        
        u[v] = true;
        
        for (size_t j=0; j<g[v].size(); ++j) {
            
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

Here the graph $g$ is stored as adjacency list: for each vertex $v$ list $g[v]$ contains the list of edges outgoing from this vertex, i.e. a list of pairs $\rm pair<int,int>$ where the first element in the pair is the vertex which is the other end of the edge, and the second element is the edge weight.

First of all, the arrays, distances $d[]$, labels $u[]$ and predecessor $p[]$ are initialized. Then $n$ iterations are performed. At each iteration, first of all, the vertex $v$ is selected with the smallest distance $d[v]$ among all the unmarked vertices. If the distance to selected vertex $v$ is equal to infinity, the algorithm stops. Otherwise the vertex is marked, and all the edges emnating from this vertex are checked for relaxation. If relaxation is possible (i.e., distance $d[to]$ can be improved), the distance $d[to]$ is recalculated and predecessor $p[to]$ stored.

After performing all the iterations, the array $d[]$ is having the lengths of the shortest paths to all vertices, and, the array $p[]$ is having the predecessors of all vertices (except starting vertex $s$). The path to any vertex $t$ can be restored in the following way:

```cpp
vector < int > path;

for (int v=t; v!=s; v=p[v])
    path.push_back (v);
path.push_back (s);

reverse (path.begin(), path.end());
```

References:

* Thomas Cormen, Charles Leiserson, Ronald Rivest, Clifford Stein. Introduction to Algorithms [2005]
* Edsger Dijkstra. A note on two problems in connexion with graphs [1959]

## Practice Problem:
* [Timus - Ivan's Car [Difficulty:Medium]](http://acm.timus.ru/problem.aspx?space=1&num=1930)
* [SPOJ  - SHPATH [Difficulty:Easy]](http://www.spoj.com/problems/SHPATH/)
* [Codeforces - Dijkstra? [Difficulty:Easy]](http://codeforces.com/problemset/problem/20/C)

