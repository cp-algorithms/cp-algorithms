# Breadth-first search
Breadth first search is one of the basic and essential algorithms on graphs.

As a result of how the algorithm works, the path found by breadth first search to any node is the shortest path to that node i.e
the path that contains the smallest number of edges in unweighted graphs.

The algorithm works in $O (n + m)$ time, where $n$ is number of vertices and $m$ is the number of edges.

## Description of the algorithm

The algorithm takes as input an unweighted graph and the id of the source vertex $s$. The input graph can be directed or undirected,
it does not matter to the algorithm.

The algorithm can be understood as a fire spreading on the graph: at the zeroth step only the source $s$ is on fire. At each step, the fire burning at each vertex spreads to all of its neighbors. In one iteration of the algorithm, the "ring of
fire" is expanded in width by one unit (hence the name of the algorithm).

More precisely, the algorithm can be stated as follows: Create a queue $q$ which will contain the vertices to be processed and a
boolean array $used[]$ which indicates for each vertex, if it has been lit (or visited) or not.

Initially, push the source $s$ to the queue and set $used[s] = true$, while for all other vertices, $used[] = false$. Then, loop until the queue is empty and in each iteration, pop a vertex from the front of the queue. Iterate through all the edges going out
of this vertex and if some of these edges go to vertices that are not already lit, set them on fire and place them in the queue.

As a result, when the queue is empty, the "ring of fire" contains all vertices reachable from the source $s$, with each vertex
begin reached in the shortest possible way. You can also calculate the lengths of the shortest paths (which just requires maintaining an array of path lengths $d[]$) as well as save information to restore all of these shortest paths (for this, it is
necessary to maintain an array of "parents" $p[]$, which stores for each vertex, the vertex number from which we reached here).

## Implementation

We write code for the described algorithm in C++.

Input data:

    vector < vector<int> > g; // adjacency list representation of graph
    int n; // number of nodes in the graph
    int s; // the source vertex
    // take input ...

Breadth first Search:

    queue<int> q;
    q.push (s);
    vector<bool> used (n);
    vector<int> d (n), p (n);
    used[s] = true;
    p[s] = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < g[v].size(); ++i) {
            int to = g[v][i];
            if (!used[to]) {
                used[to] = true;
                q.push (to);
                d[to] = d[v] + 1;
                p[to] = v;
            }
        }
    }

If we have to restore and display the shortest path from the source to some vertex $to$, it can be done in the following
manner:

    if (!used[to])
        cout << "No path!";
    else {
        vector<int> path;
        for (int v=to; v!=-1; v=p[v])
            path.push_back (v);
        reverse (path.begin(), path.end());
        cout << "Path: ";
        for (size_t i=0; i<path.size(); ++i)
            cout << path[i] + 1 << " ";
    }

## Applications of BFS

* Find the shortest path from a source to other vertices in an unweighted graph.

* Find all connected components in a graph in O (n + m) time.: To do this, we just run BFS from each vertex, except for vertices which have already been visited from previous runs. Thus, we perform normal BFS from each of the vertices, but do not reset the array $used []$ each and every time, due to which every time we run a BFS, we get a new connected component, and the total running time will still be $O (n + m)$ (such multiple BFS on the graph without zeroing array $used []$ is called a series of breadth first searches).

* Finding a solution to a problem or a game with the least number of moves , if each state of the game can be represented by a vertex of the graph, and the transitions from one state to the other are the edges of the graph.

* Finding the shortest path in a graph with weights 0 or 1: This requires just a little modification to normal breadth-first search: if the current edge of zero weight, and distance to the vertex is shorter than the current found distance, then add this vertex not to the back, but to the front of the queue.

* Finding the shortest cycle in a directed unweighted graph: start a breadth-first search from each vertex; as soon as we try to go from the current vertex from the queue to an already visited vertex, then it means that we have found the shortest cycle, and should stop the BFS; from all such cycles (one from each BFS), choose the shortest.

* Find all the edges that lie on any shortest path between a given pair of vertices (a, b). To do this, run two breadth first searches: one from a and one from b. Let $d_a []$ be the array containing shortest distances obtained from the first BFS (from a) and $d_b []$ be the array containing shortest distances obtained from the second BFS from b. Now, for every edge (u, v), it is easy to check whether that edge lies on any shortest path between a and b: the criterion is the condition $d_a [u] + 1 + d_b [v] = d_a [b]$.

* Find all the vertices on any shortest path between a given pair of vertices (a, b). To do this, run two breadth first searches: one from a and one from b. Let $d_a []$ be the array containing shortest distances obtained from the first BFS (from a) and $d_b []$ be the array containing shortest distances obtained from the second BFS from b.  Now, for each vertex, it is easy to check whether it lies on any shortest path between a and b: the criterion is the condition $d_a [v] + d_b [v] = d_a [b]$.

* Find the shortest path of even length from start vertex to end vertex in an unweighted graph: For this, we must construct an auxiliary graph, whose vertices are the state (v, c), where v- the number of current node, c = 0 or 1- the current parity. Any edge (a, b) of the original graph in this new column will turn into two edges ((u, 0), (v, 1))and ((u, 1), (v, 0)). After that, on this graph, we need to run a BFS to find the shortest path from the starting vertex to the end, with parity, equal to 0.

## Practice Problems

* [SPOJ: AKBAR](http://spoj.com/problems/AKBAR)
* [SPOJ: NAKANJ](http://www.spoj.com/problems/NAKANJ/)
* [SPOJ: WATER](http://www.spoj.com/problems/WATER)


