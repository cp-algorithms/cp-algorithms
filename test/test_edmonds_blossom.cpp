#include <algorithm>
#include <cassert>
#include <cstring>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

using namespace std;

#include "edmonds_blossom.h"
#include "edmonds_blossom_greedy.h"

void reset_graph(int vertices) {
    n = vertices;
    for (int i = 0; i < MAXN; ++i)
        g[i].clear();
}

void add_edge(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
}

void check_stored_matching(int expected) {
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

void check_matching(int expected) {
    assert(maximum_matching() == expected);
    check_stored_matching(expected);
}

// Alternates the matching along the path found by find_path, as
// maximum_matching does.
void augment(int v) {
    while (v != -1) {
        int pv = p[v];
        int ppv = match[pv];
        match[v] = pv;
        match[pv] = v;
        v = ppv;
    }
}

// maximum_matching with the change described in the "Optimization:
// constructing an initial matching" section of the article.
int maximum_matching_with_initial_matching() {
    memset(match, -1, sizeof match);
    int matching = greedy_matching();
    for (int i = 0; i < n; ++i) {
        if (match[i] == -1) {
            int v = find_path(i);
            if (v == -1)
                continue;
            ++matching;
            augment(v);
        }
    }
    return matching;
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

// The example from the article on which Kuhn's algorithm gets stuck. With the
// matching 1-6, 2-4 (0-5, 1-3 here) and these adjacency orders, the search
// from either free vertex meets an odd cycle before it finds the path.
void test_source_counterexample() {
    for (int root : {2, 4}) {
        reset_graph(6);
        g[0] = {1, 5, 4};
        g[1] = {0, 5, 3};
        g[2] = {3};
        g[3] = {1, 2, 4};
        g[4] = {3, 0};
        g[5] = {0, 1};
        memset(match, -1, sizeof match);
        match[0] = 5;
        match[5] = 0;
        match[1] = 3;
        match[3] = 1;
        int v = find_path(root);
        assert(v == 6 - root);
        augment(v);
        check_stored_matching(3);
    }
    check_matching(3);
}

void test_two_blossoms() {
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

// A smallest graph (7 vertices and 8 edges, with edges added in this order)
// on which a contracted blossom is absorbed into a new blossom with a
// different base.
void test_nested_blossoms() {
    reset_graph(7);
    add_edge(0, 2);
    add_edge(0, 6);
    add_edge(1, 5);
    add_edge(1, 6);
    add_edge(2, 3);
    add_edge(2, 4);
    add_edge(2, 5);
    add_edge(3, 4);
    check_matching(3);
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

void test_random_graphs() {
    mt19937 rng(12345);
    for (int iteration = 0; iteration < 3000; ++iteration) {
        int vertices = 1 + rng() % 10;
        int density = rng() % 101;
        reset_graph(vertices);
        vector<unsigned> adj(vertices);
        for (int i = 0; i < vertices; ++i) {
            for (int j = i + 1; j < vertices; ++j) {
                if ((int)(rng() % 100) < density) {
                    add_edge(i, j);
                    adj[i] |= 1U << j;
                    adj[j] |= 1U << i;
                }
            }
        }
        for (int i = 0; i < vertices; ++i)
            shuffle(g[i].begin(), g[i].end(), rng);

        int expected = brute_force_matching(adj, (1U << vertices) - 1);
        check_matching(expected);
        assert(maximum_matching_with_initial_matching() == expected);
        check_stored_matching(expected);
    }
}

// Random graphs with a planted perfect matching. They are large enough for
// blossoms to nest, which the small graphs above rarely do.
void test_planted_matchings() {
    mt19937 rng(2026);
    const int vertices = 30;
    for (int iteration = 0; iteration < 2000; ++iteration) {
        reset_graph(vertices);
        vector<int> order(vertices);
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end(), rng);
        for (int i = 0; i < vertices; i += 2)
            add_edge(order[i], order[i + 1]);
        for (int i = 0; i < vertices; ++i) {
            int a = rng() % vertices, b = rng() % vertices;
            if (a != b)
                add_edge(a, b);
        }
        for (int i = 0; i < vertices; ++i)
            shuffle(g[i].begin(), g[i].end(), rng);

        check_matching(vertices / 2);
        assert(maximum_matching_with_initial_matching() == vertices / 2);
        check_stored_matching(vertices / 2);
    }
}

// Triangles sharing vertex 0, at the size limit. The searches shrink many
// blossoms, which fills the queue.
void test_max_size() {
    reset_graph(MAXN);
    for (int i = 1; i + 1 < MAXN; i += 2) {
        add_edge(0, i);
        add_edge(i, i + 1);
        add_edge(i + 1, 0);
    }
    check_matching((MAXN - 1) / 2);
}

int main() {
    test_empty_graph();
    test_triangle();
    test_triangle_with_tail();
    test_source_counterexample();
    test_two_blossoms();
    test_nested_blossoms();
    test_all_small_graphs();
    test_random_graphs();
    test_planted_matchings();
    test_max_size();
    return 0;
}
