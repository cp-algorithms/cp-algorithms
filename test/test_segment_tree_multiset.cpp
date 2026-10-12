#include <bits/stdc++.h>
using namespace std;
vector<int> a;
multiset<int> t[128];
#include "segment_tree_multiset_update.h"

void build(int v, int l, int r) {
    t[v] = multiset<int>(a.begin()+l, a.begin()+r);
    if (r-l > 1) { int m=(l+r)/2; build(v*2,l,m); build(v*2+1,m,r); }
}
void check(int v, int l, int r, const vector<int>& expected) {
    assert(t[v] == multiset<int>(expected.begin()+l, expected.begin()+r));
    for (int x = -7; x <= 7; ++x) {
        int answer = INT_MAX;
        for (int i = l; i < r; ++i) if (expected[i] >= x) answer = min(answer, expected[i]);
        auto it = t[v].lower_bound(x);
        assert((it == t[v].end() ? INT_MAX : *it) == answer);
    }
    if (r-l > 1) { int m=(l+r)/2; check(v*2,l,m,expected); check(v*2+1,m,r,expected); }
}
int main() {
    mt19937 rng(123984);
    for (int n = 1; n <= 31; ++n) {
        a.assign(n,5); build(1,0,n);
        vector<int> expected = a;
        for (int step = 0; step < 150; ++step) {
            int pos = step < n ? step : rng()%n, value = int(rng()%15)-7;
            update(1,0,n,pos,value); expected[pos] = value;
            assert(a == expected); check(1,0,n,expected);
        }
    }
}
