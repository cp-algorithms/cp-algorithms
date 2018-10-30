#include <cassert>
#include <cmath>
using namespace std;

#include "line_intersection.h"

int main() {
    pt res;
    line m{1, -1, 2};  // y = x + 2
    line n{-0.5, -1, 4};  // y = -0.5x + 4
    assert(intersect(m, n, res));
    assert(abs(res.x - 4. / 3.) < 1e-7);
    assert(abs(res.y - 10. / 3.) < 1e-7);
}
