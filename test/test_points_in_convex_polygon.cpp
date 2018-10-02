#include <bits/stdc++.h>

using namespace std;

#include "points_in_convex_polygon.h"

int main(){
	pt *p = new pt[4];
	p[0] = pt(1, 1);
	p[1] = pt(0, 1);
	p[2] = pt(0, 0);
	p[3] = pt(1, 0);
	prepare(p, p + 4);
	assert(query(pt(1, 1)));
	assert(!query(pt(-1, 0)));
	delete[] p;
	p = new pt[3];
	p[0] = pt(3, 0);
	p[1] = pt(0, 3);
	p[2] = pt(0, 0);
	prepare(p, p + 3);
	assert(query(pt(1, 1)));
	assert(query(pt(1, 2)));
	assert(query(pt(2, 1)));
	assert(!query(pt(-1, -1)));
	assert(!query(pt(2, 2)));
	delete[] p;
	return 0;
}
