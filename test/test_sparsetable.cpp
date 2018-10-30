#include <vector>
#include <numeric>
#include <cassert>

const int MAXN = 15;
const int K = 5;

const int N = MAXN;
const std::vector<int> array = {19, 16, 2, 15, 2, 12, 13, 13, 18, 14, 0, 4, 17, 17, 4};

void test_generic_sparsetable() {
    auto f = [&](int x, int y=0) { return x + y; };

    #include "sparsetable_definition.h"
    #include "sparsetable_generation.h"

    auto sum_query = [&](int L, int R) {
        #include "sparsetable_sum_query.h"
        return sum;
    };

    for (int L = 0; L < N; L++) {
        for (int R = L; R < N; R++) {
            int sum = std::accumulate(array.begin() + L, array.begin() + R + 1, 0);
            assert(sum == sum_query(L, R));
        }
    }
}

void test_range_sum_sparsetable() {
    #include "sparsetable_sum_generation.h"

    auto sum_query = [&](int L, int R) {
        #include "sparsetable_sum_query.h"
        return sum;
    };

    for (int L = 0; L < N; L++) {
        int sum = 0;
        for (int R = L; R < N; R++) {
            sum += array[R];
            assert(sum == sum_query(L, R));
        }
    }
}

void test_range_minimum_sparsetable() {
    using std::min;

    #include "sparse_table_log_table.h"
    #include "sparse_table_minimum_generation.h"

    auto minimum_query = [&](int L, int R) {
        #include "sparse_table_minimum_query.h"
        return minimum;
    };

    for (int L = 0; L < N; L++) {
        int minimum = array[L];
        for (int R = L; R < N; R++) {
            minimum = min(minimum, array[R]);
            assert(minimum == minimum_query(L, R));
        }
    }
}

int main() {
    test_generic_sparsetable();
    test_range_sum_sparsetable();
    test_range_minimum_sparsetable();
}
