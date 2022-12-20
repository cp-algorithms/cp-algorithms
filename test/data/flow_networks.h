#include <vector>
using namespace std;

struct FlowNetwork {
    vector<vector<int>> capacity;
    int source, sink;
    int maxflow;

    vector<vector<int>> get_adj() {
        int n = capacity.size();
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (capacity[i][j] || capacity[j][i])
                    adj[i].push_back(j);
            }
        }
        return adj;
    }
};

vector<FlowNetwork> flow_networks = {
    // flow network from the cp-algorithms article
    {{
        {0, 7, 0, 0, 4, 0},
        {0, 0, 5, 3, 0, 0},
        {0, 0, 0, 0, 0, 8},
        {0, 0, 3, 0, 0, 5},
        {0, 3, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 0}
    }, 0, 5, 10}, 
    // flow network from wikipedia (Edmonds-Karp article)
    {{
        {0, 3, 0, 3, 0, 0, 0},
        {0, 0, 4, 0, 0, 0, 0},
        {3, 0, 0, 1, 2, 0, 0},
        {0, 0, 0, 0, 2, 6, 0},
        {0, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 9},
        {0, 0, 0, 0, 0, 0, 0}
     }, 0, 6, 5}, 
    // worst case flow network (for Ford-Fulkerson) from wikipedia
    {{
        {0, 1000, 1000, 0},
        {0, 0, 1, 1000},
        {0, 0, 0, 1000},
        {0, 0, 0, 0}
    }, 0, 3, 2000},
    // example from brilliant.org
    {{
         {0, 16, 0, 13, 0, 0},
         {0, 0, 12, 10, 0, 0},
         {0, 0, 0, 9, 0, 20},
         {0, 4, 0, 0, 14, 0},
         {0, 0, 7, 0, 0, 4},
         {0, 0, 0, 0, 0, 0}
     }, 0, 5, 23},
     {{
         {0, 10, 5, 15, 0, 0, 0, 0},
         {0, 0, 4, 0, 9, 15, 0, 0},
         {0, 0, 0, 4, 0, 8, 0, 0},
         {0, 0, 0, 0, 0, 0, 16, 0},
         {0, 0, 0, 0, 0, 15, 0, 10},
         {0, 0, 0, 0, 0, 0, 15, 10},
         {0, 0, 6, 0, 0, 0, 0, 10},
         {0, 0, 0, 0, 0, 0, 0, 0}
     }, 0, 7, 28},
     // example from https://web.stanford.edu/class/cs97si/08-network-flow-problems
     {{
         {0, 0, 10, 0, 0, 12},
         {0, 0, 0, 4, 0, 7},
         {4, 14, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0},
         {16, 0, 12, 0, 0, 0},
         {0, 0, 9, 20, 0, 0}
     }, 4, 3, 23},
};
