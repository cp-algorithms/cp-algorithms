#include <cassert>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

#include "solve_linear_congruence.h"

// Brute-force: find all x in [0, n-1] with (a*x) mod n == b mod n.
vector<long long> brute_force(long long a, long long b, long long n) {
    vector<long long> results;
    // Normalize b into [0, n-1].
    long long b_mod = ((b % n) + n) % n;
    for (long long x = 0; x < n; ++x) {
        long long val = ((a % n * (x % n)) % n + n) % n;
        if (val == b_mod)
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
        assert(((a * x - b) % n + n) % n == 0);
    }
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
    return 0;
}
