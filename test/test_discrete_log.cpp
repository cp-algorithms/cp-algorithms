#include <cassert>
#include <cmath>
#include <unordered_map>
#include <vector>
using namespace std;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int powmod(int a, int b, int m) {
    int res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * 1ll * a) % m;
        }
        a = (a * 1ll * a) % m;
        b >>= 1;
    }
    return res;
}

namespace DiscreteLog {
#include "discrete_log.h"
}

namespace DiscreteLogExtended {
#include "discrete_log_extended.h"
}

struct TestData {
    int a, b, m, expected_x;
};

const int M = 1e9 + 7;
const vector<TestData> test_data = {
    {2, 1, 7, 0},           
    {2, 0, 7, -1},
    {1, 2, 7, -1},          
    {2, 3, 7, -1},
    {12, 23, 101, 66},      
    {2837, 12831, 101, 29},
    {3, 2, M, 316884446},  
    {2432872, 12837, M, 107040312},
    {1024, 12121212, M, -1},
    {171096626, 222452761, M, 24275631}
};

const int M2 = 223092870; // = 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23
const vector<TestData> test_data_ex = {
    {2, 1, 8, 0},
    {2, 0, 8, 3},
    {2, 3, 8, -1},
    {15, 25, 100, 2},
    {12, 76, 100, 20},
    {225, 101004765, M2, 823},
    {81969, 138873279, M2, 1143},
    {171096626, 151148516, M2, 1587},
    {171096626, 2, M2, -1},
};

int naive(int a, int b, int m) {
    a %= m, b %= m;
    int cur = 1 % m;
    for (int x = 0; x < m; x++) {
        if (cur == b) {
            return x;
        }
        cur = cur * 1ll * a % m;
    }
    return -1;
}

vector<TestData> generate_small_cases(bool coprime_only) {
    vector<TestData> test_data;
    for (int a = 0; a < 50; a++) {
        for (int b = 0; b < 50; b++) {
            for (int m = 1; m < 50; m++) {
                if (coprime_only && gcd(a, m) > 1) {
                    continue;
                }
                int expected_x = naive(a, b, m);
                test_data.push_back({a, b, m, expected_x});
            }
        }
    }
    return test_data;
}

void test_data_ok() {
    for (const TestData &td : test_data) {
        assert(gcd(td.a, td.m) == 1);
    }
    for (const TestData &td : test_data_ex) {
        assert(gcd(td.a, td.m) > 1);
    }

    vector<TestData> test_data_all = test_data;
    test_data_all.insert(test_data_all.end(), test_data_ex.begin(), test_data_ex.end());

    for (const TestData &td : test_data_all) {
        int no_answer_limit;
        if (td.expected_x == -1) {
            no_answer_limit = td.m;
        } else {
            assert(powmod(td.a, td.expected_x, td.m) == td.b % td.m);
            no_answer_limit = td.expected_x;
        }

        int b = td.b % td.m, cur = 1;
        for (int i = 0; i < no_answer_limit; ++i) {
            assert(cur != b);
            cur = cur * 1ll * td.a % td.m;
        }
    }
}

void verify(const TestData &td, int actual_x) {
    if (td.expected_x == -1) {
        assert(actual_x == -1);
    } else {
        assert(0 <= actual_x && actual_x < td.m);
        assert(actual_x == td.expected_x);
    }
}

void test_discrete_log() {
    for (const TestData &td : test_data) {
        int actual_x = DiscreteLog::solve(td.a, td.b, td.m);
        verify(td, actual_x);
    }
    for (const TestData &td : generate_small_cases(true)) {
        int actual_x = DiscreteLog::solve(td.a, td.b, td.m);
        verify(td, actual_x);
    }
}

void test_discrete_log_extended() {
    for (const TestData &td : test_data) {
        int actual_x = DiscreteLogExtended::solve(td.a, td.b, td.m);
        verify(td, actual_x);
    }
    for (const TestData &td : test_data_ex) {
        int actual_x = DiscreteLogExtended::solve(td.a, td.b, td.m);
        verify(td, actual_x);
    }
    for (const TestData &td : generate_small_cases(false)) {
        int actual_x = DiscreteLogExtended::solve(td.a, td.b, td.m);
        verify(td, actual_x);
    }

}

int main() {
    // Check hardcoded test data integrity. Takes a while.
    // test_data_ok();

    test_discrete_log();
    test_discrete_log_extended();
}
