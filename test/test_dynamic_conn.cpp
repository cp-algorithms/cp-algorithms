#include<bits/stdc++.h>

using namespace std;

#include "dynamic-conn.h"

int main(){
	QueryTree t(11, 5);
	t.add_query(query(0, 1),  1, 10);
	t.add_query(query(1, 2), 2, 7);
	t.add_query(query(2, 3), 3, 10);
	t.add_query(query(3, 4), 4, 9);
	t.add_query(query(4, 0), 5, 10);
	auto ans = t.solve();
	assert(ans[0] == 5);
	assert(ans[6] == 1);
	assert(ans[8] == 1);
	assert(ans[10] == 2);
	return 0;
}

