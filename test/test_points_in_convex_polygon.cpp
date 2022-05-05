#include <bits/stdc++.h>
using namespace std;

#include "points_in_convex_polygon.h"

int main(){
    {
        vector<pt> p(4);
        p[0] = pt(1, 1);
        p[1] = pt(0, 1);
        p[2] = pt(0, 0);
        p[3] = pt(1, 0);
        prepare(p);
        assert(pointInConvexPolygon(pt(1, 1)));
        assert(!pointInConvexPolygon(pt(-1, 0)));
    }

    {
        vector<pt> p(3);
        p[0] = pt(3, 0);
        p[1] = pt(0, 3);
        p[2] = pt(0, 0);
        prepare(p);
        assert(pointInConvexPolygon(pt(1, 1)));
        assert(pointInConvexPolygon(pt(1, 2)));
        assert(pointInConvexPolygon(pt(2, 1)));
        assert(!pointInConvexPolygon(pt(-1, -1)));
        assert(!pointInConvexPolygon(pt(2, 2)));
    }

    {
        vector<pt> p(3);
        p[0] = pt(8, 5);
        p[1] = pt(5, 8);
        p[2] = pt(5, 5);
        prepare(p);
        assert(pointInConvexPolygon(pt(6, 6)));
        assert(!pointInConvexPolygon(pt(1, 1)));
    }

    {
        vector<pt> p(3);
        p[0] = pt(0, -3);
        p[1] = pt(-3, 0);
        p[2] = pt(0, 0);
        prepare(p);
        assert(pointInConvexPolygon(pt(0, -1)));
        assert(!pointInConvexPolygon(pt(2, -1)));
    }

	return 0;
}
