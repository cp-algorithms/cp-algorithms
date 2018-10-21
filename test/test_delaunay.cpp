#include<bits/stdc++.h>

using namespace std;

#include "delaunay.h"

int main(){
	vector<pt> p = {
		pt(0, 0),
		pt(1, 0),
		pt(0, 1),
		pt(5, 5)
	};
	auto res = delaunay(p);
	assert(res.size() == 2);
	auto has = [](tuple<pt, pt, pt> a, pt b){
		return get<0>(a) == b || get<1>(a) == b || get<2>(a) == b;
	};
	bool f = has(res[0], pt(5, 5));
	if(!f)
		swap(res[0], res[1]);
	assert(has(res[0], pt(5, 5)) && has(res[0], pt(1, 0)) && has(res[0], pt(0, 1)));
	assert(has(res[1], pt(0, 0)) && has(res[1], pt(1, 0)) && has(res[1], pt(0, 1)));
	return 0;
}
