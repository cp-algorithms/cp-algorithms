#include <cassert>
#include <vector>
#include <string>
using namespace std;

#include "duval_algorithm.h"
#include "smallest_cyclic_string.h"

int main() {
    string s = "abacabab";
    vector<string> exp_fact = {"abac", "ab", "ab"};
    vector<string> fact = duval(s);
    assert(exp_fact == fact);

    string exp_min_shift = "abababac";
    assert(exp_min_shift == min_cyclic_string(s));
}
