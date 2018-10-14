#include<bits/stdc++.h>

using namespace std;

#include "dinic.h"

int main(){
	Dinic solver(10, 8, 9);
	int C = (int)1e8;
	long long inf = (long long)1e15;
	solver.add_edge(8, 0, C);
	solver.add_edge(8, 1, C);
	solver.add_edge(8, 2, C);
	solver.add_edge(8, 3, C);
	solver.add_edge(0, 4, inf);
	solver.add_edge(1, 5, inf);
	solver.add_edge(2, 6, inf);
	solver.add_edge(3, 7, inf);
	solver.add_edge(4, 9, C + 2);
	solver.add_edge(5, 9, C - 2);
	solver.add_edge(6, 9, C - 1);
	solver.add_edge(7, 9, C + 1);
	solver.add_edge(0, 6, inf);
	solver.add_edge(0, 7, inf);
	solver.add_edge(1, 7, inf);
	solver.add_edge(2, 7, inf);
	solver.add_edge(4, 1, inf);
	solver.add_edge(4, 2, inf);
	solver.add_edge(5, 3, inf);
	solver.add_edge(6, 3, inf);
	assert(solver.flow() == 4 * C - 2);
	return 0;
}
