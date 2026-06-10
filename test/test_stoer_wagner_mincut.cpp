#include <cassert>
#include <cstring>
#include <set>
#include <vector>

using namespace std;

#include "stoer_wagner_mincut.h"

int saved[MAXN][MAXN];

void reset_graph(int vertices) {
    n = vertices;
    memset(g, 0, sizeof g);
    memset(saved, 0, sizeof saved);
    best_cost = 1000000000;
    best_cut.clear();
}

void add_edge(int a, int b, int c) {
    g[a][b] = g[b][a] = c;
    saved[a][b] = saved[b][a] = c;
}

// computes the weight of the cut found, using the saved copy of the graph
int cut_weight() {
    set<int> cut(best_cut.begin(), best_cut.end());
    assert(!cut.empty() && (int)cut.size() < n);
    int weight = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (cut.count(i) != cut.count(j))
                weight += saved[i][j];
    return weight;
}

void test_two_vertices() {
    reset_graph(2);
    add_edge(0, 1, 5);
    mincut();
    assert(best_cost == 5);
    assert(cut_weight() == 5);
}

void test_stoer_wagner_paper_example() {
    // example graph from the paper "A Simple Min-Cut Algorithm",
    // the minimum cut is {3, 4, 7, 8} (1-indexed) with weight 4
    reset_graph(8);
    add_edge(0, 1, 2);
    add_edge(0, 4, 3);
    add_edge(1, 2, 3);
    add_edge(1, 4, 2);
    add_edge(1, 5, 2);
    add_edge(2, 3, 4);
    add_edge(2, 6, 2);
    add_edge(3, 6, 2);
    add_edge(3, 7, 2);
    add_edge(4, 5, 3);
    add_edge(5, 6, 1);
    add_edge(6, 7, 3);
    mincut();
    assert(best_cost == 4);
    assert(cut_weight() == 4);
    set<int> cut(best_cut.begin(), best_cut.end());
    set<int> expected = {2, 3, 6, 7};
    set<int> complement = {0, 1, 4, 5};
    assert(cut == expected || cut == complement);
}

void test_two_clusters() {
    // two triangles with heavy edges, connected by a single light edge
    reset_graph(6);
    add_edge(0, 1, 10);
    add_edge(1, 2, 10);
    add_edge(2, 0, 10);
    add_edge(3, 4, 10);
    add_edge(4, 5, 10);
    add_edge(5, 3, 10);
    add_edge(2, 3, 1);
    mincut();
    assert(best_cost == 1);
    assert(cut_weight() == 1);
}

void test_isolated_vertex() {
    // a vertex not connected to the rest gives a cut of weight 0
    reset_graph(4);
    add_edge(0, 1, 7);
    add_edge(1, 2, 4);
    add_edge(2, 0, 5);
    mincut();
    assert(best_cost == 0);
    assert(cut_weight() == 0);
}

int main() {
    test_two_vertices();
    test_stoer_wagner_paper_example();
    test_two_clusters();
    test_isolated_vertex();
    return 0;
}
