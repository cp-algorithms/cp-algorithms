#include <cassert>
#include <vector>
using namespace std;

namespace Fast0 {
#include "josephus_fast0.h"
}

namespace Rec {
#include "josephus_rec.h"
}

namespace Iter {
#include "josephus_iter.h"
}

int brute_force_josephus(int n, int k) {
    vector<bool> v(n, true);
    int rem = n;
    int idx = -1;
    while (rem > 0) {
        int todo = k;
        while (todo > 0) {
            idx = (idx + 1) % n;
            if (v[idx])
                todo--;
        }
        v[idx] = false;
        rem--;
    }
    return idx + 1;
}

void test_josephus() {
    for (int n = 1; n <= 50; n++) {
        for (int k = 1; k <= 50; k++) {
            int expected = brute_force_josephus(n, k);
            assert(expected == Fast0::josephus(n, k) + 1);
            assert(expected == Rec::josephus(n, k));
            assert(expected == Iter::josephus(n, k));
        }
    }
}

int main() {
    test_josephus();
}
