#include <cassert>
#include <cmath>
using namespace std;

using ftype = int;
#include "point2d.h"
#include "point3d.h"
#include "dotproduct.h"
#include "dotproperties.h"

int main() {
    point2d a(1, 2);
    point2d b(3, 4);
    a += b;
    assert(a.x == 4 && a.y == 6);
    a -= b;
    assert(a.x == 1 && a.y == 2);
    a *= 2;
    assert(a.x == 2 && a.y == 4);
    assert(dot(a, b) == 22);

    point3d A(1, 2, 3);
    point3d B(4, 5, 6);
    assert(dot(A, B) == 32);

    point2d pyt(3, 4);
    assert(norm(pyt) == 25);
    assert(abs(pyt) == 5);
}
