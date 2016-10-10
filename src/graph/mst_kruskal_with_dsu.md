# Minimum spanning tree - Kruskal's algorithm with Disjoint Set Union data structure

Statement of the problem and a description of Kruskal's algorithm, <a href="/mst_kruskal.html">see here</a>.

In this article we will consider the data structure "Disjoint Set Union" (The DSU) for implementation of the Kruskal's Minimum Spanning Tree algorithm, which will allow the algorithm to achieve the asymptotic complexity of $O (M log N)$.

## Description

Just as in the simple version of the Kruskal algorithm, we sort the all the edges of the graph in non-decreasing order of weights. Then put each vertex in its own tree (i.e. its set) via DSU $make_set()$ function call - it will take a total of $O (N)$. Iterate through all the edges (in sorted order) and for each edge determine whether the ends belong to different trees (with two $find_set()$ calls in $O (1)$ each). Finally, we need to perform the union of the two trees(sets), for which the DSU $union_sets()$ function will be called - also in $O (1)$. So we get the total asymptotic complexity $O (M log N + N + M)$ = $O (M log N)$.

## Implementation

Here, a randomized version of the DSU is used.

    vector <int> p(n);

    int dsu_get (int v) {
        return (v == p[v])?  v : (p[v] = dsu_get(p[v]));
    }

    void dsu_unite (int a, int b) {
        a = dsu_get (a);
        b = dsu_get (b);
        if (rand() & 1)
            swap(a, b);
        if (a! = b)
            p[a] = b;
    }

    /*... In the main () function: ...*/

    int m;
    vector < pair < int, pair < int, int > > > g;  // Weight - the top 1 - top 2
    /*... Read the count ...*/

    int cost = 0;
    vector < pair < int, int > > res;

    sort(g.begin (), g.end ());
    p.resize(n);

    for (int i = 0; i < n; ++i)
        p [i] = i;
        
    for (int i = 0; i < m; ++i) {
        int a = g[i].second.first, b = g[i].second.second, l = g[i].first;
        if(dsu_get(a)! = dsu_get(b)) {
            cost + = l;
            res.push_back (g[i] .second);
            dsu_unite (a, b);
        }
    } 
