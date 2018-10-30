#include <cassert>
#include <vector>
#include <string>
using namespace std;

#include "rabin_karp.h"

int main() {
    string t = "aabbabbbcddbadabbaac";
    string s = "abb";
    vector<int> result = {1, 4, 14};
    assert(rabin_karp(s, t) == result);

    t = "abbababbaaabaabbababdabbabcbaaabbaabaadcaabcaaaabb";
    s = "abbaa";
    result = {5, 30};
    assert(rabin_karp(s, t) == result);
}
