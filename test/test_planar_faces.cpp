#include <algorithm>
#include <assert.h>
#include <vector>

#include "planar.h"

bool equal_cycles(const std::vector<size_t> & a, const std::vector<size_t> & b) {
    size_t n = a.size();
    if (n != b.size()) {
        return false;
    }
    for (size_t begin = 0; begin < n; begin++) {
        bool ok = true;
        for (size_t i = 0; i < n; i++) {
            if (a[(begin + i) % n] != b[i]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            return true;
        }
    }
    return false;
}

void test_simple() {
    std::vector<Point> p = {
        Point(0, 0),
        Point(1, 0),
        Point(1, 1),
        Point(0, 1)
    };

    std::vector<std::vector<size_t>> adj = {
        {1, 2, 3},
        {0, 2},
        {0, 1, 3},
        {0, 2}
    };

    auto faces = find_faces(p, adj);
    assert(faces.size() == 3u);
    assert(equal_cycles(faces[0], {3, 2, 1, 0}));
    bool eq11 = equal_cycles(faces[1], {0, 1, 2});
    bool eq12 = equal_cycles(faces[1], {0, 2, 3});
    bool eq21 = equal_cycles(faces[2], {0, 1, 2});
    bool eq22 = equal_cycles(faces[2], {0, 2, 3});
    assert(eq11^eq21);
    assert(eq12^eq22);
}

void test_degenerate() {
    std::vector<Point> p = {
        Point(0, 0),
        Point(1, 1),
        Point(2, 2)
    };
    
    std::vector<std::vector<size_t>> adj = {
        {1},
        {0, 2},
        {1}
    };

    auto faces = find_faces(p, adj);
    assert(faces.size() == 1u);
    assert(equal_cycles(faces[0], {0, 1, 2, 1}));
}

void test_cycle_with_chain() {
    std::vector<Point> p = {
        Point(0, 0),
        Point(0, 3),
        Point(3, 3),
        Point(3, 0),
        Point(1, 1),
        Point(2, 2)
    };

    std::vector<std::vector<size_t>> adj = {
        {1, 3},
        {0, 2},
        {1, 3, 5},
        {0, 2},
        {5},
        {2, 4}
    };

    auto faces = find_faces(p, adj);
    assert(faces.size() == 2u);
    assert(equal_cycles(faces[0], {0, 1, 2, 3}));
    assert(equal_cycles(faces[1], {2, 5, 4, 5, 2, 1, 0, 3}));
}

void test_complex_outer() {
    std::vector<Point> p = {
        Point(334, 181),
        Point(403, 177),
        Point(463, 181),
        Point(524, 181),
        Point(521, 568),
        Point(460, 564),
        Point(405, 572),
        Point(335, 563),
        Point(333, 386),
        Point(400, 387),
        Point(466, 389),
        Point(523, 396),
        Point(521, 353),
        Point(466, 351),
        Point(409, 354),
        Point(333, 350),
    };

    std::vector<std::vector<size_t>> adj = {
        {1, 15},
        {0, 2, 14},
        {1, 3, 13},
        {2, 12},
        {5, 11},
        {6, 4, 10},
        {7, 5, 9},
        {8, 6},
        {9, 7, 15},
        {10, 8, 6},
        {11, 9, 5},
        {12, 10, 4},
        {3, 13, 11},
        {12, 14, 2},
        {13, 15, 1},
        {14, 0, 8},
    };

    auto faces = find_faces(p, adj);
    assert(faces.size() == 8u);
    assert(equal_cycles(faces[0], {15, 8, 7, 6, 5, 4, 11, 12, 3, 2, 1, 0}));
    assert(equal_cycles(faces[1], {1, 14, 15, 0}));
    assert(equal_cycles(faces[2], {2, 13, 14, 1}));
    assert(equal_cycles(faces[3], {3, 12, 13, 2}));
    assert(equal_cycles(faces[4], {5, 10, 11, 4}));
    assert(equal_cycles(faces[5], {6, 9, 10, 5}));
    assert(equal_cycles(faces[6], {7, 8, 9, 6}));
    assert(equal_cycles(faces[7], {15, 14, 13, 12, 11, 10, 9, 8}));
}

int main() {
    test_simple();
    test_degenerate();
    test_cycle_with_chain();
    test_complex_outer();
}
