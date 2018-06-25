#include <cassert>
#include <cmath>
#include <algorithm>

using namespace std;

#include "linear_diophantine_any.h"
#include "linear_diophantine_all.h"

int brute_force(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    int ans = 0;
    for (int x = minx; x <= maxx; x++) {
        for (int y = miny; y <= maxy; y++) {
            if (x * a + y * b == c) ans++;
        }
    }
    return ans;
}

void test(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    int expected = brute_force(a, b, c, minx, maxx, miny, maxy);
    assert(find_all_solutions(a, b, c, minx, maxx, miny, maxy) == expected);
}

int main() {
    test(-10, -8, -80, -100, 100, -90, 90);
    test(-389, 6, 836, 326, 777, 3, 926);
    test(-239, -138, 65, 786, 945, 218, 647);
    return 0;
}