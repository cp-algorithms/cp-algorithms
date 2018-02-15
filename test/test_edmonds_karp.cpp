#include <cassert>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;
#include "edmondskarp.h"

void generate_adj() {
    adj.clear();
    adj.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (capacity[i][j] || capacity[j][i])
                adj[i].push_back(j);
        }
    }
}

void test_article_network() {
    // test flow network from the e-maxx-eng article
    n = 6;
    capacity = {
        {0, 7, 0, 0, 4, 0},
        {0, 0, 5, 3, 0, 0},
        {0, 0, 0, 0, 0, 8},
        {0, 0, 3, 0, 0, 5},
        {0, 3, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };
    generate_adj();

    assert(maxflow(0, 5) == 10);
}

void test_wiki() {
    // test flow network from wikipedia (Edmonds-Karp article)
    n = 7;
    capacity = {
        {0, 3, 0, 3, 0, 0, 0},
        {0, 0, 4, 0, 0, 0, 0},
        {3, 0, 0, 1, 2, 0, 0},
        {0, 0, 0, 0, 2, 6, 0},
        {0, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 9},
        {0, 0, 0, 0, 0, 0, 0}
    };
    generate_adj();

    assert(maxflow(0, 6) == 5);
}

void test_worst_case_wiki() {
    // test worst case flow network (for Ford-Fulkerson) from wikipedia
    n = 4;
    capacity = {
        {0, 1000, 1000, 0},
        {0, 0, 1, 1000},
        {0, 0, 0, 1000},
        {0, 0, 0, 0}
    };
    generate_adj();

    assert(maxflow(0, 3) == 2000);
}

int main() {
    test_article_network();
    test_wiki();
    test_worst_case_wiki();
}
