#include <vector>
#include <cassert>
#include <array>
#include <map>
#include <cmath>
using namespace std;

long long power(long long b, long long e, long long mod) {
    long long res = 1;
    while (e) {
        if (e & 1)
            res = res * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return res;
}

long long gcd(long long a, long long b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

#include "../test/factorization_trial_division1.h"
#include "../test/factorization_trial_division2.h"
#include "../test/factorization_trial_division3.h"
#include "../test/factorization_trial_division4.h"
#include "../test/factorization_p_minus_1.h"
#include "../test/pollard_rho.h"
#include "../test/pollard_rho_brent.h"

int main() {
    map<long long, vector<long long>> test_data = {
        {132, {2, 2, 3, 11}},
        {123456789, {3, 3, 3607, 3803}},
        {4817191, {1303, 3697}}
    };
    primes = {2, 3, 5, 7, 1303, 3607};

    for (auto n_expected : test_data) {
        auto n = n_expected.first;
        auto expected = n_expected.second;

        assert(trial_division1(n) == expected);
        assert(trial_division2(n) == expected);
        assert(trial_division3(n) == expected);
        assert(trial_division4(n) == expected);

        long long g = pollards_p_minus_1(n);
        assert(g > 1 && g < n && n % g == 0);

        g = rho(n);
        assert(g > 1 && g < n && n % g == 0);
        g = brent(n);
        assert(g > 1 && g < n && n % g == 0);
    }
}
