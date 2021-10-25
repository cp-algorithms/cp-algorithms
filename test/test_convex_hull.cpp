#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

namespace GrahamScan {
#include "graham_scan.h"
}
namespace MonotoneChain {
#include "monotone_chain.h"
}
#include "data/convex_hull.h"

int main() {
    for (auto& [points, ans, ans_col] : convex_hulls) {
        // for searching valid rotations
        ans.insert(ans.end(), ans.begin(), ans.end());
        ans_col.insert(ans_col.end(), ans_col.begin(), ans_col.end());

        {
            using namespace GrahamScan;
            vector<GrahamScan::pt> hull, hull_col;
            for (auto p : points) {
                hull.push_back({ .x = p.x, .y = p.y });
                hull_col.push_back({ .x = p.x, .y = p.y });
            }

            convex_hull(hull, false);
            assert(hull.size() == ans.size()/2);
            assert(search(ans.begin(), ans.end(), hull.begin(), hull.end(), [](::pt a, GrahamScan::pt b){
                return a.x == b.x && a.y == b.y;
            }) != ans.end());

            convex_hull(hull_col, true);
            assert(hull_col.size() == ans_col.size()/2);
            assert(search(ans_col.begin(), ans_col.end(), hull_col.begin(), hull_col.end(), [](::pt a, GrahamScan::pt b){
                return a.x == b.x && a.y == b.y;
            }) != ans_col.end());
        }

        {
            using namespace MonotoneChain;
            vector<MonotoneChain::pt> hull, hull_col;
            for (auto p : points) {
                hull.push_back({ .x = p.x, .y = p.y });
                hull_col.push_back({ .x = p.x, .y = p.y });
            }

            convex_hull(hull, false);
            assert(hull.size() == ans.size()/2);
            assert(search(ans.begin(), ans.end(), hull.begin(), hull.end(), [](::pt a, MonotoneChain::pt b){
                return a.x == b.x && a.y == b.y;
            }) != ans.end());

            convex_hull(hull_col, true);
            assert(hull_col.size() == ans_col.size()/2);
            assert(search(ans_col.begin(), ans_col.end(), hull_col.begin(), hull_col.end(), [](::pt a, MonotoneChain::pt b){
                return a.x == b.x && a.y == b.y;
            }) != ans_col.end());
        }
    }
}
