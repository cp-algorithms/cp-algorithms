#include <algorithm>
#include <assert.h>
#include <cmath>
#include <map>
#include <stdint.h>
#include <utility>
#include <vector>

#include "planar_implicit.h"

void test_square() {
    std::vector<Line> s = {
        Line(Point(0, 0), Point(0, 1)),
        Line(Point(0, 0), Point(1, 0)),
        Line(Point(1, 1), Point(0, 1)),
        Line(Point(1, 1), Point(1, 0)),
        Line(Point(0, 0), Point(1, 1)),
        Line(Point(1, 0), Point(0, 1))
    };
    auto [pts, adj] = build_graph(s);
    std::vector<Point> pts1 = {Point(0, 0), Point(0, 1), Point(1, 0), Point(1, 1), Point(0.5, 0.5)};
    assert(pts == pts1);
    std::sort(adj[4].begin(), adj[4].end());
    std::vector<size_t> adj1 = {0, 1, 2, 3};
    assert(adj[4] == adj1);
}

void test_grid() {
    std::vector<Line> s = {
        Line(Point(0, 0), Point(0, 3)),
        Line(Point(0, 0), Point(3, 0)),
        Line(Point(3, 3), Point(0, 3)),
        Line(Point(3, 3), Point(3, 0)),
        Line(Point(1, 0), Point(1, 3)),
        Line(Point(2, 0), Point(2, 3)),
        Line(Point(0, 1), Point(3, 1)),
        Line(Point(0, 2), Point(3, 2))
    };
    auto [pts, adj] = build_graph(s);
    auto pts_copy = pts;
    std::sort(pts_copy.begin(), pts_copy.end());
    std::vector<Point> pts1 = {
        Point(0, 0), Point(0, 1), Point(0, 2), Point(0, 3),
        Point(1, 0), Point(1, 1), Point(1, 2), Point(1, 3),
        Point(2, 0), Point(2, 1), Point(2, 2), Point(2, 3),
        Point(3, 0), Point(3, 1), Point(3, 2), Point(3, 3),
    };
    assert(pts_copy == pts1);
    std::map<Point, size_t> m;
    for (size_t i = 0; i < pts.size(); i++) {
        m[pts[i]] = i;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j <= 3; j++) {
            size_t v = m[Point(i, j)];
            size_t u = m[Point(i + 1, j)];
            assert(std::find(adj[v].begin(), adj[v].end(), u) != adj[v].end());
            assert(std::find(adj[u].begin(), adj[u].end(), v) != adj[u].end());
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j <= 3; j++) {
            size_t v = m[Point(j, i)];
            size_t u = m[Point(j, i + 1)];
            assert(std::find(adj[v].begin(), adj[v].end(), u) != adj[v].end());
            assert(std::find(adj[u].begin(), adj[u].end(), v) != adj[u].end());
        }
    }
}

void test_multiedges() {
    std::vector<Line> s = {
        Line(Point(0, 0), Point(2, 2)),
        Line(Point(1, 1), Point(3, 3))
    };
    auto [pts, adj] = build_graph(s);
    assert(adj[0].size() == 1u && adj[1].size() == 2u && adj[2].size() == 2u && adj[3].size() == 1u);
}

int main() {
    test_square();
    test_grid();
    test_multiedges();
}
