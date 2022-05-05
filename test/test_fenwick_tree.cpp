#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>
using namespace std;

namespace Fenwick_Sum {
#include "fenwick_sum.h"
}

namespace Fenwick_Min {
#include "fenwick_min.h"
}

namespace Fenwick_Sum_Onebased {
#include "fenwick_sum_onebased.h"
}


void test_fenwick_sum() {
    using namespace Fenwick_Sum;
    vector<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = a.size();
    FenwickTree tree(a);
    for (int i = 0; i < n; i++) {
        int expected_sum = 0;
        for (int j = i; j < n; j++) {
            expected_sum += a[j];
            assert(expected_sum == tree.sum(i, j));
        }
    }
    for (int k = 0; k < n; k++) {
        tree.add(k, 100);
        a[k] += 100;
        for (int i = 0; i < n; i++) {
            int expected_sum = 0;
            for (int j = i; j < n; j++) {
                expected_sum += a[j];
                assert(expected_sum == tree.sum(i, j));
            }
        }
    }
}

void test_fenwick_min() {
    using namespace Fenwick_Min;
    vector<int> a = {36, 22, 69, 86, 9, 30, 69, 91, 94, 64};
    int n = a.size();
    FenwickTreeMin tree(a);
    int expected_min = std::numeric_limits<int>::max();
    for (int j = 0; j < n; j++) {
        expected_min = min(expected_min, a[j]);
        assert(expected_min == tree.getmin(j));
    }
    vector<int> b = {10, 10, 9, 4, 4, 8, 0, 4, 9, 1};
    for (int k = 0; k < n; k++) {
        tree.update(k, b[k]);
        a[k] = b[k];
        int expected_min = std::numeric_limits<int>::max();
        for (int j = 0; j < n; j++) {
            expected_min = min(expected_min, a[j]);
            assert(expected_min == tree.getmin(j));
        }
    }
}

void test_fenwick_sum_onebased() {
    using namespace Fenwick_Sum_Onebased;
    vector<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = a.size();
    FenwickTreeOneBasedIndexing tree(a);
    for (int i = 0; i < n; i++) {
        int expected_sum = 0;
        for (int j = i; j < n; j++) {
            expected_sum += a[j];
            assert(expected_sum == tree.sum(i, j));
        }
    }
    for (int k = 0; k < n; k++) {
        tree.add(k, 100);
        a[k] += 100;
        for (int i = 0; i < n; i++) {
            int expected_sum = 0;
            for (int j = i; j < n; j++) {
                expected_sum += a[j];
                assert(expected_sum == tree.sum(i, j));
            }
        }
    }
}

int main() {
    test_fenwick_sum();
    test_fenwick_min();
    test_fenwick_sum_onebased();
}
