#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

#include "grahams_scan.h"

bool operator==(pt a, pt b) {
    return a.x == b.x && a.y == b.y;
}

int main() {
    vector<pt> points = {
        {0, 3},
        {1, 1},
        {2, 2},
        {4, 4},
        {0, 0},
        {1, 2},
        {3, 1},
        {3, 3}
    };

    convex_hull(points);
    vector<pt> expected = {
        {0, 0},
        {0, 3},
        {4, 4},
        {3, 1}
    };

    assert(points == expected);
}
