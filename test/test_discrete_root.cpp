#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>
using namespace std;

#include "discrete_root.h"

int powmod_naive(int a, int b, int p) {
    long long res = 1 % p;
    for (int i = 0; i < b; i++)
        res = res * a % p;
    return res;
}

bool is_prime(int n) {
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return n > 1;
}

void test_small_primes() {
    for (int n = 2; n < 60; n++) {
        if (!is_prime(n))
            continue;
        for (int k = 1; k <= 2 * n; k++) {
            for (int a = 0; a < n; a++) {
                vector<int> expected;
                for (int x = 0; x < n; x++)
                    if (powmod_naive(x, k, n) == a)
                        expected.push_back(x);
                assert(discrete_root(n, k, a) == expected);
            }
        }
    }
}

void test_large_primes() {
    // The products do not fit into int for these moduli.
    assert(discrete_root(46349, 2, 4) == vector<int>({2, 46347}));
    assert(discrete_root(1000003, 2, 4) == vector<int>({2, 1000001}));
    assert(discrete_root(998244353, 2, 4) == vector<int>({2, 998244351}));
    assert(discrete_root(998244353, 3, 8) == vector<int>({2}));
    assert(discrete_root(1000000007, 2, 9) == vector<int>({3, 1000000004}));
    // 5 is a quadratic non-residue modulo 998244353.
    assert(discrete_root(998244353, 2, 5).empty());
    // The largest prime that fits into int.
    assert(discrete_root(2147483647, 2, 4) == vector<int>({2, 2147483645}));
    assert(discrete_root(2147483647, 5, 32) == vector<int>({2}));
    assert(discrete_root(2147483647, 2, 7).empty());

    const int n = 1000000007;
    for (int k : {4, 5, 123456, 1000000}) {
        for (int x : {2, 12345, 123456789, 1000000006}) {
            int a = powmod(x, k % (n - 1), n);
            vector<int> roots = discrete_root(n, k, a);
            assert((int)roots.size() == gcd(k % (n - 1), n - 1));
            assert(is_sorted(roots.begin(), roots.end()));
            assert(binary_search(roots.begin(), roots.end(), x));
            for (int root : roots)
                assert(powmod(root, k % (n - 1), n) == a);
        }
    }
}

int main() {
    test_small_primes();
    test_large_primes();
}
