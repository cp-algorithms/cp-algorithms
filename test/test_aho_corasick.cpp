#include <cassert>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace Trie {
#include "aho_corasick_trie_definition.h"
#include "aho_corasick_trie_add.h"
}

namespace Automaton {
#include "aho_corasick_automaton.h"
}

void test_trie() {
    using namespace Trie;

    vector<string> set = {"a", "to", "tea", "ted", "ten", "i", "in", "inn"};
    for (string s : set) {
        add_string(s);
    }
    assert(trie.size() == 11);
}

void test_automaton() {
    using namespace Automaton;

    vector<string> set = {"a", "ab", "bab", "bc", "bca", "c", "caa"};
    for (string s : set) {
        add_string(s);
    }
    assert(t.size() == 11);

    int v = 0;
    v = go(v, 'a');
    assert(t[v].leaf == true);
    v = go(v, 'b');
    assert(t[v].leaf == true);
    v = go(v, 'c');
    assert(t[v].leaf == true);
    v = go(v, 'd');
    assert(t[v].leaf == false);
    assert(v == 0);
    v = go(v, 'b');
    assert(t[v].leaf == false);
    v = go(v, 'a');
    assert(t[v].leaf == false);
    v = go(v, 'a');
    assert(t[v].leaf == true);
    v = go(v, 'b');
    assert(t[v].leaf == true);
}

int main() {
    test_trie();
    test_automaton();
}
