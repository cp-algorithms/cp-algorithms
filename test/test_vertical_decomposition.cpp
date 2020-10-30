#include <bits/stdc++.h>

using namespace std;

#include "triangle_union.h"

dbl solve(vector<vector<int> > rects){
    vector<vector<pt> > processed_rects;
    for(const auto& v: rects){
        processed_rects.push_back(vector<pt>());
        processed_rects.back().push_back(pt{(dbl)v[0], (dbl)v[1]});
        processed_rects.back().push_back(pt{(dbl)v[2], (dbl)v[3]});
        processed_rects.back().push_back(pt{(dbl)v[4], (dbl)v[5]});
        processed_rects.back().push_back(pt{(dbl)v[6], (dbl)v[7]});
    }
    vector<tuple<pt, pt, pt> > tr;
    dbl sum = 0;
    for(const auto& r: processed_rects){
        sum += fabs((r[1] - r[0]).cross(r[3] - r[0]));
        tr.emplace_back(r[0], r[1], r[2]);
        tr.emplace_back(r[2], r[3], r[0]);
    }
    return sum/union_area(tr);
}

bool test1(){
    vector<vector<int> > rects = {
        {0, 0, 0, 1, 3, 1, 3, 0},
        {0, 0, 0, 3, 1, 3, 1, 0},
        {3, 3, 2, 3, 2, 0, 3, 0},
        {3, 3, 3, 2, 0, 2, 0, 3}
    };
    return fabs(solve(rects) - 1.5) < 1e-6;
}

bool test2(){
    vector<vector<int> > rects = {
        {-1, 0, 0, 1, 1, 0, 0, -1},
        {0, 0, 1, 1, 2, 0, 1, -1}
    };
    return fabs(solve(rects) - 1.1428571429) < 1e-6;
}

int main(){
    assert(test1());
    assert(test2());
}
