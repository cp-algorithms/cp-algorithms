#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

namespace Implementation {
const int MAXN = 10;
#include "segment_tree_implementation_definition.h"
#include "segment_tree_implementation_build.h"
#include "segment_tree_implementation_sum.h"
#include "segment_tree_implementation_update.h"
}

namespace MaximumAndCount {
const int MAXN = 10;
const int INF = 1e9;
#include "segment_tree_maximum_and_count.h"
}

namespace KthZero {
const int MAXN = 10;
#include "segment_tree_implementation_definition.h"
#include "segment_tree_implementation_build.h"
#include "segment_tree_implementation_sum.h"
#include "segment_tree_implementation_update.h"
#include "segment_tree_kth_zero.h"
}

namespace MaximalSubsegment {
#include "segment_tree_maximal_sum_subsegments1.h"
const int MAXN = 10;
data t[MAXN * 4];
#include "segment_tree_maximal_sum_subsegments2.h"
#include "segment_tree_maximal_sum_subsegments3.h"
}

namespace SmallestGreaterOrEqual {
const int MAXN = 10;
const int INF = 1e9;
#include "segment_tree_smallest_number_greater1.h"
#include "segment_tree_smallest_number_greater2.h"
}

void test_section_implementation() {
    using namespace Implementation;
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    n = 10;
    build(a, 1, 0, n-1);
    for (int i = 0; i < n; i++) {
        int expected_sum = 0;
        for (int j = i; j < n; j++) {
            expected_sum += j;
            assert(expected_sum == sum(1, 0, n-1, i, j));
        }
    }
    for (int k = 0; k < 0; k++) {
        update(1, 0, n-1, k, 100);
        for (int i = 0; i < n; i++) {
            int expected_sum = 0;
            for (int j = i; j < n; j++) {
                expected_sum += j > k ? j : 100;
                assert(expected_sum == sum(1, 0, n-1, i, j));
            }
        }
    }
}

void test_section_maximum_and_count() {
    using namespace MaximumAndCount;
    int a[] = {4, 7, 1, 3, 3, 0, 5, 9, 0, 7};
    int n = 10;
    build(a, 1, 0, n-1);
    pair<int, int> expected;
    assert(make_pair(9, 1) == get_max(1, 0, n-1, 0, 9));
    assert(make_pair(5, 1) == get_max(1, 0, n-1, 2, 6));
    update(1, 0, n-1, 6, 2);
    assert(make_pair(3, 2) == get_max(1, 0, n-1, 2, 6));
    update(1, 0, n-1, 6, 3);
    assert(make_pair(3, 3) == get_max(1, 0, n-1, 2, 6));
}

void test_section_kth_zero() {
    using namespace KthZero;
    // array    = {5, 0, 0, 2, 3, 0, 1, 0, 2, 0};
    int zeros[] = {0, 1, 1, 0, 0, 1, 0, 1, 0, 1};
    n = 10;
    build(zeros, 1, 0, n-1);
    assert(find_kth(1, 0, n-1, 1) == 1);
    assert(find_kth(1, 0, n-1, 2) == 2);
    assert(find_kth(1, 0, n-1, 3) == 5);
    assert(find_kth(1, 0, n-1, 4) == 7);
    assert(find_kth(1, 0, n-1, 5) == 9);
    assert(find_kth(1, 0, n-1, 6) == -1);
    update(1, 0, n-1, 4, 1);
    assert(find_kth(1, 0, n-1, 1) == 1);
    assert(find_kth(1, 0, n-1, 2) == 2);
    assert(find_kth(1, 0, n-1, 3) == 4);
    assert(find_kth(1, 0, n-1, 4) == 5);
    assert(find_kth(1, 0, n-1, 5) == 7);
    assert(find_kth(1, 0, n-1, 6) == 9);
    assert(find_kth(1, 0, n-1, 7) == -1);
}

void test_section_maximal_subsegment() {
    using namespace MaximalSubsegment;
    int a[] = {5, 8, -5, 6, 2, 3, -2, -5, 7, 6};
    int n = 10;
    build(a, 1, 0, n-1);
    assert(query(1, 0, n-1, 0, n-1).ans == 25);
    assert(query(1, 0, n-1, 2, 3).ans == 6);
    assert(query(1, 0, n-1, 1, 3).ans == 9);
    update(1, 0, n-1, 2, -10);
    assert(query(1, 0, n-1, 1, 3).ans == 8);
    assert(query(1, 0, n-1, 0, 3).ans == 13);
    assert(query(1, 0, n-1, 0, 5).ans == 14);
}

void test_section_smallest_number_greater_or_equal() {
    using namespace SmallestGreaterOrEqual;
    int a[] = {5, 8, -5, 6, 2, 3, -2, -5, 7, 6};
    int n = 10;
    build(a, 1, 0, n-1);
    assert(query(1, 0, n-1, 0, n-1, 0) == 2);
    assert(query(1, 0, n-1, 0, n-1, 3) == 3);
    assert(query(1, 0, n-1, 0, n-1, 4) == 5);
    assert(query(1, 0, n-1, 0, n-1, 10) == INF);
    assert(query(1, 0, n-1, 1, n-1, 4) == 6);
    assert(query(1, 0, n-1, 2, 4, -10) == -5);
    assert(query(1, 0, n-1, 2, 4, -4) == 2);
    assert(query(1, 0, n-1, 2, 4, 3) == 6);
    assert(query(1, 0, n-1, 2, 4, 7) == INF);
}

int main() {
    test_section_implementation();
    test_section_maximum_and_count();
    test_section_kth_zero();
    test_section_maximal_subsegment();
    test_section_smallest_number_greater_or_equal();
}
