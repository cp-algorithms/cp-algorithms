#include <bits/stdc++.h>

using namespace std;

#include "minkowski.h"

bool equal_polygons(const vector<pt> & p, const vector<pt> & q){
    if(p.size() != q.size())
        return false;
    for(size_t i = 0; i < p.size(); i++){
        if(p[i].x != q[i].x || p[i].y != q[i].y)
            return false;
    }
    return true;
}

bool test1(){
    vector<pt> p = {
        pt{0, 0},
        pt{1, 0},
        pt{0, 1}
    };
    vector<pt> q = {
        pt{1, 1},
        pt{0, 1},
        pt{0, 0},
        pt{1, 0}
    };
    return equal_polygons(
        minkowski(p, q),
        vector<pt>{
            pt{0, 0},
            pt{2, 0},
            pt{2, 1},
            pt{1, 2},
            pt{0, 2}
        });
}

bool test2(){
    vector<pt> p = {
        pt{1, 1},
        pt{0, 1},
        pt{0, 0},
        pt{1, 0}
    };
    vector<pt> q = {
        pt{2, 2},
        pt{0, 2},
        pt{0, 0},
        pt{2, 0}
    };
    return equal_polygons(
            minkowski(p, q),
            vector<pt>{
                pt{0, 0},
                pt{3, 0},
                pt{3, 3},
                pt{0, 3}
            });
}

int main(){
    assert(test1());
    assert(test2());
}
