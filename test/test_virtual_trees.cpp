#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

namespace Implementation {
    const int MAXN = 30;
    const int LOGN = 10;
    #include "virtual_trees.h"
}

int main() {
    int n = 20;
    vector<pair<int,int>> edges = {
        {1,2}, {1,4}, {1,5}, {1,6}, {1,10},
        {1,16}, {2,3}, {2,15}, {2,19},
        {3,11}, {4,7}, {4,9}, {6,12},
        {6,13}, {6,14}, {6,20}, {7,8},
        {8,17}, {13,18}
    };
    vector<int> colors = {2, 10, 6, 3, 16, 20, 6, 17, 8, 13, 9, 11, 7, 12, 5, 13, 7, 18, 3, 18};
    assert(Implementation::solve(n, edges, colors) == 25);
    return 0;
}