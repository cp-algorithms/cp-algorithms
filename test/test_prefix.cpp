#include <cassert>
#include <vector>
#include <string>
using namespace std;

namespace slow {
#include "prefix_slow.h"
}

namespace fast {
#include "prefix_fast.h"
}

namespace AutomatonSlow {
#include "prefix_fast.h"
#include "prefix_automaton_slow.h"
}

namespace AutomatonFast {
#include "prefix_fast.h"
#include "prefix_automaton_fast.h"
}


int main() {
    string s = "abcabcdabcabca";
    vector<int> prefix = {0, 0, 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 4};
    assert(slow::prefix_function(s) == prefix);
    assert(fast::prefix_function(s) == prefix);

    vector<int> pi = fast::prefix_function(s);
    int n = s.size();
#include "prefix_count_each_prefix.h"
    vector<int> prefix_cnt = {15, 5, 4, 4, 3, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1};
    assert(ans == prefix_cnt);

    string t = "babcbabcad";
    vector<int> pi_t = {0, 1, 2, 3, 0, 1, 2, 3, 4, 0};
    vector<vector<int>> aut;
    AutomatonSlow::compute_automaton(s, aut);
    int pi_cur = 0;
    for (int i = 0; i < (int)t.size(); i++) {
        pi_cur = aut[pi_cur][t[i] - 'a'];
        assert(pi_cur == pi_t[i]);
    }

    aut.clear();
    AutomatonFast::compute_automaton(s, aut);
    pi_cur = 0;
    for (int i = 0; i < (int)t.size(); i++) {
        pi_cur = aut[pi_cur][t[i] - 'a'];
        assert(pi_cur == pi_t[i]);
    }
}
