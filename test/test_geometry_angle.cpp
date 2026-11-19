#include <bits/stdc++.h>
using namespace std;
using ftype = double;
#include "point2d.h"
#include "point3d.h"
#include "dotproduct.h"
#include "dotproperties.h"

void check(point2d a, point2d b) {
    double got = angle(a,b);
    long double cross = (long double)a.x*b.y-(long double)a.y*b.x;
    long double scalar = (long double)a.x*b.x+(long double)a.y*b.y;
    long double expected = atan2(abs(cross),scalar);
    assert(isfinite(got));
    assert(got >= 0 && got <= acos(-1.0));
    assert(abs(got-expected) < 1e-7);
}
int main() {
    mt19937 rng(347182);
    for (int x=-15;x<=15;++x) for(int y=-15;y<=15;++y) {
        if(x==0&&y==0)continue;
        point2d a(x,y);
        check(a,a);check(a,point2d(-x,-y));check(a,point2d(-y,x));
        for(int j=0;j<10;++j){int u=int(rng()%101)-50,v=int(rng()%101)-50;if(u||v)check(a,point2d(u,v));}
    }
}
