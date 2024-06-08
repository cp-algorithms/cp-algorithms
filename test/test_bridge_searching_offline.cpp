#include <algorithm>
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
    normalize(expected_bridges);
    normalize(bridges);
    assert(bridges == expected_bridges);
}

int main() {
    vector<vector<int>> adj;
    auto add_edge = [&](int a,int b){
        adj[a].push_back(b);
        adj[b].push_back(a);
    };
    {
        int n = 5;
        adj.resize(n);
        add_edge(0, 1);
        add_edge(0, 1);
        
        add_edge(2, 3);
        add_edge(3, 4);
        vector<pair<int,int> > expected_bridges;
        expected_bridges.push_back({2,3});
        expected_bridges.push_back({3,4});
        // note that 0-1 is not a bridge due to duplicate edges!
        test_suite(n, adj, expected_bridges);
        adj.clear();
    }
    {
        int n = 7;
        adj.resize(n);
        add_edge(0, 1);
        add_edge(1, 2);
        add_edge(2, 3);
        add_edge(3, 1);
        add_edge(3, 4);
        add_edge(0, 4);
        add_edge(4, 5);
        add_edge(1, 6);
        vector<pair<int,int> > expected_bridges;
        expected_bridges.push_back({4, 5});
        expected_bridges.push_back({1, 6});
        test_suite(n, adj, expected_bridges);
        adj.clear();   
    }
    {
        int n = 4;
        adj.resize(n);
        add_edge(0, 1);
        add_edge(0, 1);
        add_edge(1, 2);
        add_edge(2, 3);
        add_edge(2, 3);
        vector<pair<int,int> > expected_bridges;
        expected_bridges.push_back({1, 2});
        test_suite(n, adj, expected_bridges);
        adj.clear();   
    }
}
