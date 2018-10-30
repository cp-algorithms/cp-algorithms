#include <cassert>
#include <vector>
#include <set>
using namespace std;

namespace SLOW {
#include "pruefer_code_slow.h"
#include "pruefer_decode_slow.h"
}

namespace FAST {
#include "pruefer_code_fast.h"
#include "pruefer_decode_fast.h"
}

vector<vector<int>> get_adj(vector<pair<int, int>> edges) {
    vector<vector<int>> adj(edges.size() + 1);
    for (auto edge : edges) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }
    return adj;
}

int main() {
    {
        using namespace SLOW;
        adj = {
            {3}, 
            {3},
            {3},
            {0, 1, 2, 4},
            {3, 5},
            {4}
        };
        vector<int> exp_code = {3, 3, 3, 4};
        assert(pruefer_code() == exp_code);

        vector<int> code2 = {5, 3, 2, 4, 4};
        auto edges = pruefer_decode(code2);
        adj = get_adj(edges);
        assert(pruefer_code() == code2);
    }
    {
        using namespace FAST;
        adj = {
            {3}, 
            {3},
            {3},
            {0, 1, 2, 4},
            {3, 5},
            {4}
        };
        vector<int> exp_code = {3, 3, 3, 4};
        assert(pruefer_code() == exp_code);

        vector<int> code2 = {5, 3, 2, 4, 4};
        auto edges = pruefer_decode(code2);
        adj = get_adj(edges);
        assert(pruefer_code() == code2);
    }
}
