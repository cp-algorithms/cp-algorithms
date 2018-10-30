#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

#include "next_balanced_brackets_sequence.h"
#include "kth_balances_bracket.h"
#include "kth_balances_bracket_multiple.h"

bool balanced(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[') {
            st.push(c);
        } else {
            if (st.empty())
                return false;
            if (c == ')' && st.top() != '(')
                return false;
            if (c == ']' && st.top() != '[')
                return false;
            st.pop();
        }
    }
    return st.empty();
}

void find_all_permutation(string s, vector<string> & all) {
    do {
        if (balanced(s))
            all.push_back(s);
    } while (next_permutation(s.begin(), s.end()));
}

vector<string> generate_all(int n) {
    vector<string> all;
    string s = string(n, '(') + string(n, ')');
    find_all_permutation(s, all);
    return all;
}

vector<string> generate_all2(int n) {
    vector<string> all;
    for (int i = 0; i <= n; i++) {
        string s = string(i, '(') + string(i, ')');
        s += string(n-i, '[') + string(n-i, ']');
        find_all_permutation(s, all);
    }
    sort(all.begin(), all.end());
    return all;
}

void test_all(int n) {
    vector<string> all = generate_all(n);

    for (int i = 0; i < (int)all.size() - 1; i++) {
        string s = all[i];
        assert(next_balanced_sequence(s));
        assert(s == all[i+1]);
    }
    assert(!next_balanced_sequence(all.back()));

    for (int i = 0; i < (int)all.size(); i++) {
        assert(kth_balanced(n, i + 1) == all[i]);
    }
}

void test_all2(int n) {
    vector<string> all = generate_all2(n);
    for (int i = 0; i < (int)all.size(); i++) {
        assert(kth_balanced2(n, i + 1) == all[i]);
    }
}

int main() {
    for (int n = 1; n <= 10; n++)
        test_all(n);

    for (int n = 1; n <= 5; n++)
        test_all2(n);
}
