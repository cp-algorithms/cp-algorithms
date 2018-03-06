#include <cassert>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#include "hashing_function.h"
#include "hashing_group_identical_strings.h"
#include "hashing_count_unique_substrings.h"

int main() {
    assert(compute_hash("abc") != compute_hash("abd"));

    vector<string> v = {"a", "b", "abc", "b", "b", "abc"};
    assert(group_identical_strings(v).size() == 3);

    assert(count_unique_substrings("abaabcabc") == 35);
}

