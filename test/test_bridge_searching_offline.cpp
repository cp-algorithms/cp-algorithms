#include <cassert>
#include <vector>
#include <set>
using namespace std;

#include "bridge_searching_offline.h"

vector<pair<int,int>> bridges;
void IS_BRIDGE(int v,int to){
    bridges.push_back({v, to});
}

void normalize(vector<pair<int,int>> &v){
    for(auto &p : v){
        if(p.first > p.second)swap(p.first, p.second);
    }
    sort(v.begin(), v.end());
}

void test_suite(
    int _n,
    vector<vector<int>> _adj,
    vector<pair<int,int> > expected_bridges){
    bridges.clear();
    n = _n;
    adj = _adj;
    find_bridges();
    normalize(&expected_bridges);
    normalize(&bridges);
    assert(bridges == expected_bridges);
}

int main() {
    {
        int n = 5;
        vector<vector<int>> adj(n);
        adj[0].push_back(1), adj[1].push_back(0);
        adj[0].push_back(1), adj[1].push_back(0);
        
        adj[2].push_back(3), adj[3].push_back(2);
        adj[3].push_back(4), adj[4].push_back(3);
        vector<pair<int,int> > expected_bridges;
        expected_bridges.push_back({2,3});
        expected_bridges.push_back({3,4});
        // note that 0-1 is not a bridge due to duplicate edges!
        test_suite(n, adj, expected_bridges);
    }
}
