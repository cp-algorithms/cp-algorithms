#include <bits/stdc++.h>
using namespace std;
#include "manhattan_mst.h"

struct DSU {
    int n;
    vector<int> p, ps;
    DSU(int _n){
        n = _n;
        p = ps = vector<int>(n+1, 1);
        for(int i=1;i<=n;i++)p[i] = i;
    }
    int f(int x){return p[x]=(p[x]==x?x:f(p[x]));}
    bool join(int a,int b){
        a=f(a),b=f(b);
        if(a==b)return false;
        if(ps[a] > ps[b])swap(a,b);
        ps[b] += ps[a];
        p[a] = b;
        return true;
    }
};

long long mst_cost(vector<tuple<long long,int ,int> > e,int n){
    sort(e.begin(), e.end());
    DSU dsu(n);
    long long c=0;
    for(auto &[w, i, j] : e){
        if(dsu.join(i, j))c += w;
    }
    return c;
}

vector<tuple<long long,int,int> > brute(vector<point> ps){
    vector<tuple<long long,int,int> > e;
    for(int i=0;i<ps.size();i++)for(int j=i+1;j<ps.size();j++){
        e.push_back({abs(ps[i].x - ps[j].x) + abs(ps[i].y - ps[j].y), i, j});
    }
    return e;
}

mt19937 rng(123);
vector<point> get_random_points(int n,int maxC){
    vector<point> ps;
    for(int i=0;i<n;i++){
        int x = rng()%(2*maxC) - maxC, y = rng()%(2*maxC) - maxC;
        ps.push_back({x, y});
    }
    return ps;
}

int32_t main(){
    vector<int> max_cs = {5, 1000, 100000, 100000000};
    vector<int> ns = {5, 100, 500};
    for(int maxC : max_cs)for(int n : ns){
        auto ps = get_random_points(n, maxC);
        auto e1 = brute(ps);
        auto e2 = manhattan_mst_edges(ps);
        assert(mst_cost(e1, n) == mst_cost(e2, n));
    }
    auto time_begin = clock();
    auto ps = get_random_points(200000, 1000000);
    auto e = manhattan_mst_edges(ps);
    cerr << setprecision(5) << fixed;
    cerr << (double)(clock() - time_begin)/CLOCKS_PER_SEC << endl;
    assert((double)(clock() - time_begin)/CLOCKS_PER_SEC < 2);
}
