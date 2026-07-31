// https://leetcode.com/problems/count-good-integers-in-a-range/

#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

namespace Recursive {
#include "digit_dp_recursive.h"
}

namespace Iterative {
#include "digit_dp_iterative.h"
}

bool is_good(long long n, int k) {
    vector<int> d;
    while (n > 0) {
        d.push_back(n % 10);
        n /= 10;
    }
    for (size_t i = 1; i < d.size(); i++)
        if (abs(d[i] - d[i - 1]) > k)
            return false;
    return true;
}

long long brute_force(long long l, long long r, int k) {
    long long cnt = 0;
    for (long long n = l; n <= r; n++)
        if (is_good(n, k))
            cnt++;
    return cnt;
}

long long iterative_answer(long long l, long long r, int k) {
    return Iterative::count_upto(r, k) - Iterative::count_upto(l - 1, k);
}

int main() {
    for (int k = 0; k <= 9; k++) {
        for (long long l = 1; l <= 200; l++) {
            for (long long r = l; r <= 200; r += 7) {
                long long expected = brute_force(l, r, k);
                assert(Recursive::good_integers(l, r, k) == expected);
                assert(iterative_answer(l, r, k) == expected);
            }
        }
    }

    for (int k = 0; k <= 9; k++) {
        long long l = 1, r = 100000;
        long long expected = brute_force(l, r, k);
        assert(Recursive::good_integers(l, r, k) == expected);
        assert(iterative_answer(l, r, k) == expected);
    }

    assert(Recursive::good_integers(10, 1000000000000000LL, 9) == 1000000000000000LL - 10 + 1);
    assert(iterative_answer(10, 1000000000000000LL, 9) == 1000000000000000LL - 10 + 1);

    assert(Recursive::good_integers(1, 999999, 0) == 54);
    assert(iterative_answer(1, 999999, 0) == 54);

    for (int k = 0; k <= 9; k++) {
        long long r = 1000000000000000LL;
        assert(Recursive::good_integers(10, r, k) == iterative_answer(10, r, k));
    }

    return 0;
}
