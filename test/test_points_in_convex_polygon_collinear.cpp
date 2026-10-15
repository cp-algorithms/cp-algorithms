#include <bits/stdc++.h>
using namespace std;
#include "points_in_convex_polygon.h"

vector<pt> hull(vector<pt> p) {
    sort(p.begin(), p.end(), lexComp);
    p.erase(unique(p.begin(), p.end(), [](pt a, pt b) { return a.x == b.x && a.y == b.y; }), p.end());
    vector<pt> a, b;
    for (pt x : p) {
        while (a.size() > 1 && a[a.size()-2].cross(a.back(), x) <= 0) a.pop_back();
        a.push_back(x);
    }
    reverse(p.begin(), p.end());
    for (pt x : p) {
        while (b.size() > 1 && b[b.size()-2].cross(b.back(), x) <= 0) b.pop_back();
        b.push_back(x);
    }
    a.pop_back(); b.pop_back();
    a.insert(a.end(), b.begin(), b.end());
    return a;
}
void check(vector<pt> polygon) {
    auto original = polygon;
    prepare(polygon);
    for (int x = -22; x <= 22; ++x) for (int y = -22; y <= 22; ++y) {
        pt query(x, y);
        bool expected = true;
        for (int i = 0; i < (int)original.size(); ++i)
            expected &= original[i].cross(original[(i+1)%original.size()], query) >= 0;
        assert(pointInConvexPolygon(query) == expected);
    }
    for (pt p : original) assert(pointInConvexPolygon(p));
}
int main() {
    check({{0,0},{1,0},{2,0},{2,2},{0,2}});
    mt19937 rng(123876);
    for (int tt = 0; tt < 300; ++tt) {
        vector<pt> p;
        do {
            p.clear();
            for (int i = 0; i < 12; ++i) p.emplace_back(2*(int(rng()%21)-10), 2*(int(rng()%21)-10));
            p = hull(p);
        } while (p.size() < 3);
        vector<pt> boundary;
        for (int i = 0; i < (int)p.size(); ++i) {
            pt a = p[i], b = p[(i+1)%p.size()];
            boundary.push_back(a);
            boundary.emplace_back((a.x+b.x)/2, (a.y+b.y)/2);
        }
        rotate(boundary.begin(), boundary.begin()+rng()%boundary.size(), boundary.end());
        check(boundary);
    }
}
