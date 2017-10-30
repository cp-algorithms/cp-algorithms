<!--?title Checking a graph for acyclicity and finding a cycle in O(M) -->

# Checking a graph for acyclicity and finding a cycle in $O(M)$

Consider a directed or undirected graph without loops and multiple edges. We have to check whether it is acyclic, and if it is not, then find any cycle.

We can solve this problem by using [depth first search](./graph/depth-first-search.html) in $O(M)$ where $M$ is number of edges.

## Algorithm

We will run a series of DFS in the graph. From each unvisited vertex, start the DFS, mark it gray while entering and mark it black on exit. If DFS moves to a gray vertex, then we have found a cycle (if the graph is undirected, the edge to parent is not considered).
The cycle itself can be reconstructed using parent array.

## Implementation

Here is an implementation for directed graph.

C++ implementation <span class="toggle-code">Show/Hide</span>

```cpp
int n;
vector <vector <int>> g;
vector <char> cl;
vector <int> p;
int cycle_st, cycle_end;

bool dfs (int v) {
    cl [v] = 1;
    for (size_t i = 0; i <g [v] .size (); ++ i) {
        int to = g [v] [i];
        if (cl [to] == 0) {
            p [to] = v;
            if (dfs (to)) return true;
        }
        else if (cl [to] == 1) {
            cycle_end = v;
            cycle_st = to;
            return true;
        }
    }
    cl [v] = 2;
    return false;
}

int main () {
    ... reading the graph ...

    p.assign (n, -1);
    cl.assign (n, 0);
    cycle_st = -1;
    for (int i = 0; i <n; ++ i)
        if (dfs (i))
            break;

    if (cycle_st == -1)
        puts ("Acyclic");
    else {
        puts ("Cyclic");
        vector <int> cycle;
        cycle.push_back (cycle_st);
        for (int v = cycle_end; v! = cycle_st; v = p [v])
            cycle.push_back (v);
        cycle.push_back (cycle_st);
        reverse (cycle.begin (), cycle.end ());
        for (size_t i = 0; i <cycle.size (); ++ i)
            printf ("% d", cycle [i] +1);
    }
}
```