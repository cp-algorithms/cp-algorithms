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

int main() {
    test_simple();
    test_degenerate();
    test_cycle_with_chain();
}
