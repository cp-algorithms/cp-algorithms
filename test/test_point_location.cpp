#include <bits/stdc++.h>

using namespace std;

#include "point-location.h"

DCEL from_polygon(vector<pt> p){
    DCEL ans;
    int n = p.size();
    DCEL::Edge *last = nullptr;
    for(int i = 0; i < n; i++){
        int j = i + 1;
        j -= j == n ? n : 0;
        DCEL::Edge* e = new DCEL::Edge;
        e->origin = p[i];
        e->face = 0;
        DCEL::Edge* te = new DCEL::Edge;
        te->origin = p[j];
        e->twin = te; te->twin = e;
        te->face = -1;
        if(last != nullptr){
            last->nxt = e;
            te->nxt = last->twin;
        }
        last = e;
        ans.body.push_back(e);
        ans.body.push_back(te);
    }
    last->nxt = ans.body[0];
    ans.body[1]->nxt = last->twin;
    return ans;
}

int main(){
    DCEL p = from_polygon({pt(0, 0), pt(3, 0), pt(0, 3)});
    auto res = point_location(p, {pt(1, 2), pt(2, 1), pt(1, 1), pt(2, 2), pt(0, 4), pt(-1, 0)});
    assert(res[0] == make_pair(0, 2) || res[0] == make_pair(0, 3));
    assert(res[1] == make_pair(0, 2) || res[1] == make_pair(0, 3));
    assert(res[2] == make_pair(1, 0));
    assert(res[3] == make_pair(1, -1));
    assert(res[4] == make_pair(1, -1));
    assert(res[5] == make_pair(1, -1));
    return 0;
}
