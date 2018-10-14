#include<bits/stdc++.h>

using namespace std;

#include "check-segments-inter.h"

int main() {
	assert(check_inter(pt(0, 0), pt(1, 1), pt(0, 1), pt(1, 0)));
	assert(!check_inter(pt(0, 0), pt(1, 1), pt(2, 2), pt(3, 3)));
	assert(check_inter(pt(0, 0), pt(1, 1), pt(2, 2), pt(1, 1)));
	assert(check_inter(pt(0, 0), pt(1, 1), pt(1, 1), pt(1, 0)));
	assert(!check_inter(pt(0, 0), pt(1, 0), pt(0, 1), pt(1, 1)));
	assert(!check_inter(pt(0, 0), pt(1, 1), pt(2, 2), pt(2, 0)));
	assert(!check_inter(pt(0, 0), pt(-1, -1), pt(0, 1), pt(1, 0)));
	return 0;
}
