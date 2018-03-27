#include <vector>
using namespace std;

struct Graph_SSSP {
    vector<vector<pair<int, int>>> adj;
    int s;
    vector<int> expected_d;
    vector<int> expected_p;
};

vector<Graph_SSSP> sssp_graphs = {
    // wikipedia
    {
        {
            {{1, 7}, {2, 9}, {5, 14}}, 
            {{0, 7}, {2, 10}, {3, 15}},
            {{0, 9}, {1, 10}, {3, 11}, {5, 2}},
            {{1, 15}, {2, 11}, {4, 6}}, 
            {{3, 6}, {5, 9}}, 
            {{0, 14}, {2, 2}, {4, 9}}
        }, 
        0,
        {0, 7, 9, 20, 20, 11},
        {-1, 0, 0, 2, 5, 2}
    }
};
