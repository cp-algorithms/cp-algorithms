#include <bits/stdc++.h>
using namespace std;
#include "halfplane_primitives.h"
#include "halfplane_intersection.h"

long double area(const vector<Point>& p) {
    long double a=0;
    for (int i=0;i<(int)p.size();++i) a+=cross(p[i],p[(i+1)%p.size()]);
    return abs(a)/2;
}
vector<Point> hull(vector<Point> p) {
    sort(p.begin(),p.end(),[](Point a,Point b){return a.x!=b.x?a.x<b.x:a.y<b.y;});
    vector<Point> h;
    for(auto a:p){while(h.size()>1&&cross(h.back()-h[h.size()-2],a-h.back())<=0)h.pop_back();h.push_back(a);}
    int lower=h.size();reverse(p.begin(),p.end());
    for(int i=1;i<(int)p.size();++i){auto a=p[i];while((int)h.size()>lower&&cross(h.back()-h[h.size()-2],a-h.back())<=0)h.pop_back();h.push_back(a);}
    if(h.size()>1)h.pop_back();return h;
}
void check(vector<Halfplane> h, int expected_nonempty=-1) {
    vector<Point> candidates;
    for(int i=0;i<(int)h.size();++i)for(int j=0;j<i;++j) {
        if(abs(cross(h[i].pq,h[j].pq))<eps)continue;
        Point p=inter(h[i],h[j]);bool feasible=true;
        for(auto g:h)feasible &= !g.out(p);
        if(feasible)candidates.push_back(p);
    }
    auto input=h;auto got=hp_intersect(input);
    if(expected_nonempty!=-1)assert(!got.empty()==bool(expected_nonempty));
    assert(got.empty()==candidates.empty());
    for(auto p:got){assert(isfinite(p.x)&&isfinite(p.y));for(auto g:h)assert(!g.out(p));}
    assert(abs(area(got)-area(hull(candidates)))<1e-6);
}
int main() {
    check({{Point(0,1),Point(1,0)},{Point(0,1),Point(1,2)},{Point(2,-1),Point(0,0)},{Point(1,0),Point(0,0)},{Point(0,1),Point(0,0)}},0);
    check({{Point(0,0),Point(1,0)},{Point(0,1),Point(0,0)},{Point(1,-1),Point(0,0)}},1); // point (0,0)
    check({{Point(0,0),Point(1,0)},{Point(1,0),Point(0,0)},{Point(0,1),Point(0,0)},{Point(2,0),Point(2,1)}},1); // segment
    mt19937 rng(878102);
    for(int tt=0;tt<12000;++tt){
        vector<Halfplane> h{{Point(-10,-10),Point(10,-10)},{Point(10,-10),Point(10,10)},{Point(10,10),Point(-10,10)},{Point(-10,10),Point(-10,-10)}};
        int count=1+rng()%10;
        while(count--){Point a(int(rng()%21)-10,int(rng()%21)-10),b(int(rng()%21)-10,int(rng()%21)-10);if(dot(b-a,b-a)==0){++count;continue;}h.emplace_back(a,b);}
        check(h);
    }
}
