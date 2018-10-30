#include <cassert>
#include <vector>
#include <string>
using namespace std;

#include "suffix_array_sort_cyclic1.h"
#include "suffix_array_sort_cyclic2.h"
#include "suffix_array_sort_cyclic3.h"
#include "suffix_array_construction.h"
#include "suffix_array_lcp_construction.h"

int main() {
    string s = "abaab";

    vector<int> expected_p = {2, 0, 3, 1, 4};
    vector<int> p = sort_cyclic_shifts(s);
    assert(p == expected_p);

    vector<int> expected_suffix_array = {2, 3, 0, 4, 1};
    vector<int> suffix_array = suffix_array_construction(s);
    assert(suffix_array == expected_suffix_array);

    vector<int> expected_lcp = {1, 2, 0, 1};
    vector<int> lcp = lcp_construction(s, suffix_array);
    assert(lcp == expected_lcp);
}
