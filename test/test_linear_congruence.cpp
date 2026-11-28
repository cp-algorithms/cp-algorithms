#include <algorithm>
#include <cassert>
#include <climits>
#include <vector>
using namespace std;

#include "solve_linear_congruence.h"

long long norm_mod(__int128 x, long long n) {
    long long r = static_cast<long long>(x % n);
    return r < 0 ? r + n : r;
}

// Brute-force: find all x in [0, n-1] with (a*x) mod n == b mod n.
vector<long long> brute_force(long long a, long long b, long long n) {
    vector<long long> results;
    long long b_mod = norm_mod(b, n);
    for (long long x = 0; x < n; ++x) {
        if (norm_mod(static_cast<__int128>(a) * x, n) == b_mod)
            results.push_back(x);
    }
    return results;
}

void test_basic_solvable() {
    // 3x ≡ 6 (mod 9)  →  gcd(3,9)=3 divides 6, so 3 solutions
    auto sol = solve_linear_congruence(3, 6, 9);
    auto expected = brute_force(3, 6, 9);
    sort(sol.begin(), sol.end());
    assert(sol == expected);
}

void test_unique_solution() {
    // 3x ≡ 1 (mod 7)  →  gcd(3,7)=1, unique solution: x=5
    auto sol = solve_linear_congruence(3, 1, 7);
    assert(sol.size() == 1);
    assert(sol[0] == 5);
}

void test_unsolvable() {
    // 2x ≡ 1 (mod 4)  →  gcd(2,4)=2 does not divide 1
    auto sol = solve_linear_congruence(2, 1, 4);
    assert(sol.empty());
}

void test_unsolvable_larger() {
    // 6x ≡ 5 (mod 9)  →  gcd(6,9)=3 does not divide 5
    auto sol = solve_linear_congruence(6, 5, 9);
    assert(sol.empty());
}

void test_negative_a() {
    // Negative coefficient: -3x ≡ 6 (mod 9)
    auto sol = solve_linear_congruence(-3, 6, 9);
    auto expected = brute_force(-3, 6, 9);
    sort(sol.begin(), sol.end());
    assert(sol == expected);
}

void test_negative_b() {
    // Negative b: 3x ≡ -6 (mod 9)  →  same as 3x ≡ 3 (mod 9)
    auto sol = solve_linear_congruence(3, -6, 9);
    auto expected = brute_force(3, -6, 9);
    sort(sol.begin(), sol.end());
    assert(sol == expected);
}

void test_negative_a_and_b() {
    // Both negative: -5x ≡ -10 (mod 15)
    auto sol = solve_linear_congruence(-5, -10, 15);
    auto expected = brute_force(-5, -10, 15);
    sort(sol.begin(), sol.end());
    assert(sol == expected);
}

void test_zero_a() {
    // a=0: 0*x ≡ b (mod n)
    // 0*x ≡ 0 (mod 5) → every x is a solution
    auto sol = solve_linear_congruence(0, 0, 5);
    auto expected = brute_force(0, 0, 5);
    sort(sol.begin(), sol.end());
    assert(sol == expected);
    assert(sol.size() == 5);

    // 0*x ≡ 3 (mod 5) → no solution
    sol = solve_linear_congruence(0, 3, 5);
    assert(sol.empty());
}

void test_zero_b() {
    // b=0: 6x ≡ 0 (mod 9)  →  gcd(6,9)=3 divides 0, 3 solutions
    auto sol = solve_linear_congruence(6, 0, 9);
    auto expected = brute_force(6, 0, 9);
    sort(sol.begin(), sol.end());
    assert(sol == expected);
}

void test_a_equals_n() {
    // a ≡ 0 (mod n): effectively 0*x ≡ b (mod n)
    auto sol = solve_linear_congruence(7, 0, 7);
    auto expected = brute_force(7, 0, 7);
    sort(sol.begin(), sol.end());
    assert(sol == expected);
}

void test_n_equals_one() {
    // n=1: any equation has exactly one solution: x=0
    auto sol = solve_linear_congruence(5, 3, 1);
    assert(sol.size() == 1);
    assert(sol[0] == 0);
}

void test_invalid_n() {
    // n <= 0 should return empty (precondition violation, graceful)
    assert(solve_linear_congruence(1, 1, 0).empty());
    assert(solve_linear_congruence(1, 1, -5).empty());
}

void test_all_solutions_in_range() {
    // Verify every returned solution is in [0, n-1] and satisfies the congruence
    long long a = 12, b = 8, n = 28;
    auto sol = solve_linear_congruence(a, b, n);
    auto expected = brute_force(a, b, n);
    sort(sol.begin(), sol.end());
    assert(sol == expected);
    for (long long x : sol) {
        assert(x >= 0 && x < n);
        assert(norm_mod(static_cast<__int128>(a) * x - b, n) == 0);
    }
}

void verify_solutions(long long a, long long b, long long n, size_t expected_count) {
    auto sol = solve_linear_congruence(a, b, n);
    assert(sol.size() == expected_count);
    if (expected_count == 0) {
        return;
    }
    long long b_mod = norm_mod(b, n);
    long long step = n / static_cast<long long>(expected_count);
    for (size_t i = 0; i < sol.size(); ++i) {
        assert(sol[i] >= 0 && sol[i] < n);
        assert(norm_mod(static_cast<__int128>(a) * sol[i], n) == b_mod);
        if (i > 0) {
            assert(sol[i] - sol[i - 1] == step);
        }
    }
}

void test_large_64bit_overflow() {
    // Exercises __int128 multiplication when n > sqrt(LLONG_MAX)
    auto sol = solve_linear_congruence(3999999999LL, 3999999997LL, 4000000000LL);
    assert(sol == vector<long long>{3});

    verify_solutions(999999999999999989LL, 123456789012345678LL, 1000000000000000003LL, 1);
}

void test_large_64bit_multiple_and_unsolvable() {
    // gcd(|-2000000000000000015|, 1000000000000000005) = 5
    long long n = 1000000000000000005LL;
    long long a = -2000000000000000015LL;
    verify_solutions(a, 25, n, 5);
    verify_solutions(a, 26, n, 0);
}

void test_extreme_llong_bounds() {
    // Stresses UBSan safety for LLONG_MAX and LLONG_MIN inputs
    assert(solve_linear_congruence(1, 1, LLONG_MAX) == vector<long long>{1});
    verify_solutions(LLONG_MAX - 1, -123456789012345LL, LLONG_MAX, 1);

    // LLONG_MIN ≡ -1 (mod LLONG_MAX), so (-1) * x ≡ -1 => x = 1
    assert(solve_linear_congruence(LLONG_MIN, LLONG_MIN, LLONG_MAX) == vector<long long>{1});

    assert(solve_linear_congruence(LLONG_MIN, -1, 1) == vector<long long>{0});
    assert(solve_linear_congruence(LLONG_MIN, 0, 2) == (vector<long long>{0, 1}));
    assert(solve_linear_congruence(LLONG_MIN, 1, 2).empty());
}

int main() {
    test_basic_solvable();
    test_unique_solution();
    test_unsolvable();
    test_unsolvable_larger();
    test_negative_a();
    test_negative_b();
    test_negative_a_and_b();
    test_zero_a();
    test_zero_b();
    test_a_equals_n();
    test_n_equals_one();
    test_invalid_n();
    test_all_solutions_in_range();
    test_large_64bit_overflow();
    test_large_64bit_multiple_and_unsolvable();
    test_extreme_llong_bounds();
    return 0;
}
