#include <cassert>
#include <cmath>
#include <vector>
using namespace std;

#include "parallel_binary_search.h"

void test_parallel_binary_search()
{
    vector<int> a = {1, 3, 5, 7, 9, 9, 13, 15};
    vector<int> x = {8, 11, 4, 5};
    vector<int> expected = {3, 5, 1, 2};

    assert(parallel_binary_search(a, x) == expected);

    // N is a power of two here, which needs one more halving step than
    // ceil(log2(N)) provides; the queries below sit at the end of the array.
    vector<int> edge_x = {15, 14, 0};
    vector<int> edge_expected = {7, 6, -1};

    assert(parallel_binary_search(a, edge_x) == edge_expected);
}

int main()
{
    test_parallel_binary_search();
}
