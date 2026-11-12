#include <algorithm>
#include <cassert>
#include <cstring>
#include <utility>
#include <vector>

using namespace std;

#include "edmonds_blossom.h"

void reset_graph(int vertices) {
    n = vertices;
    for (int i = 0; i < MAXN; ++i)
        g[i].clear();
}

void add_edge(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
}

void check_matching(int expected) {
    assert(maximum_matching() == expected);
    int edges = 0;
    for (int i = 0; i < n; ++i) {
        if (match[i] != -1) {
            assert(match[i] >= 0 && match[i] < n);
            assert(match[match[i]] == i);
            assert(find(g[i].begin(), g[i].end(), match[i]) != g[i].end());
            ++edges;
        }
    }
    assert(edges == 2 * expected);
}

void test_empty_graph() {
    reset_graph(5);
    check_matching(0);
}

void test_triangle() {
    reset_graph(3);
    add_edge(0, 1);
    add_edge(1, 2);
    add_edge(2, 0);
    check_matching(1);
}

void test_triangle_with_tail() {
    reset_graph(4);
    add_edge(0, 1);
    add_edge(1, 2);
    add_edge(2, 0);
    add_edge(1, 3);
    check_matching(2);
}

void test_source_counterexample() {
    reset_graph(6);
    add_edge(0, 1);
    add_edge(0, 5);
    add_edge(1, 5);
    add_edge(1, 3);
    add_edge(3, 2);
    add_edge(0, 4);
    add_edge(3, 4);
    check_matching(3);
}

void test_nested_blossoms() {
    reset_graph(8);
    add_edge(0, 1);
    add_edge(1, 2);
    add_edge(2, 0);
    add_edge(2, 3);
    add_edge(3, 4);
    add_edge(4, 5);
    add_edge(5, 3);
    add_edge(0, 6);
    add_edge(5, 7);
    check_matching(4);
}

int brute_force_matching(const vector<unsigned>& adj, unsigned remaining) {
    if (remaining == 0)
        return 0;
    int v = __builtin_ctz(remaining);
    unsigned without_v = remaining & ~(1U << v);
    int answer = brute_force_matching(adj, without_v);
    for (unsigned candidates = adj[v] & without_v; candidates != 0;
         candidates &= candidates - 1) {
        int u = __builtin_ctz(candidates);
        answer = max(answer, 1 + brute_force_matching(
                                     adj, without_v & ~(1U << u)));
    }
    return answer;
}

void test_all_small_graphs() {
    for (int vertices = 1; vertices <= 5; ++vertices) {
        vector<pair<int, int>> edges;
        for (int i = 0; i < vertices; ++i)
            for (int j = i + 1; j < vertices; ++j)
                edges.push_back({i, j});

        for (unsigned mask = 0; mask < (1U << edges.size()); ++mask) {
            reset_graph(vertices);
            vector<unsigned> adj(vertices);
            for (int i = 0; i < (int)edges.size(); ++i) {
                if (mask & (1U << i)) {
                    auto [a, b] = edges[i];
                    add_edge(a, b);
                    adj[a] |= 1U << b;
                    adj[b] |= 1U << a;
                }
            }
            int expected = brute_force_matching(adj, (1U << vertices) - 1);
            check_matching(expected);
        }
    }
}

int main() {
    test_empty_graph();
    test_triangle();
    test_triangle_with_tail();
    test_source_counterexample();
    test_nested_blossoms();
    test_all_small_graphs();
    return 0;
}
