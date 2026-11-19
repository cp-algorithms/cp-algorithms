#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace {

namespace Trie {
#include "snippets/aho_corasick_trie_definition.h"
#include "snippets/aho_corasick_trie_add.h"
} // namespace Trie

namespace Automaton {
#include "snippets/aho_corasick_automaton.h"
} // namespace Automation

TEST(AhoKorasick, TrieAddString)
{
    using namespace Trie;

    vector<string> set = {"a", "to", "tea", "ted", "ten", "i", "in", "inn"};
    for (string s : set) {
        add_string(s);
    }

    EXPECT_EQ(trie.size(), 11);
}

TEST(AhoKorasick, TrieAutomation)
{
    using namespace Automaton;

    vector<string> set = {"a", "ab", "bab", "bc", "bca", "c", "caa"};
    for (string s : set) {
        add_string(s);
    }
    EXPECT_EQ(t.size(), 11);

    int v = 0;
    v = go(v, 'a');
    EXPECT_TRUE(t[v].output);
    v = go(v, 'b');
    EXPECT_TRUE(t[v].output);
    v = go(v, 'c');
    EXPECT_TRUE(t[v].output);
    v = go(v, 'd');
    EXPECT_FALSE(t[v].output);
    EXPECT_EQ(v, 0);
    v = go(v, 'b');
    EXPECT_FALSE(t[v].output);
    v = go(v, 'a');
    EXPECT_FALSE(t[v].output);
    v = go(v, 'a');
    EXPECT_TRUE(t[v].output);
    v = go(v, 'b');
    EXPECT_TRUE(t[v].output);
}

} // namespace
