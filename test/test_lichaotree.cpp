#include <vector>
#include <complex>
#include <cassert>
using namespace std;

#include "lichaotree_line_definition.h"
#include "lichaotree_addline.h"
#include "lichaotree_getminimum.h"

int main() {
    vector<point> input_lines{
        {15, 125}, 
        {-1, 5000},
        {-10, 10000},
        {50, -2400},
        {17, 3000},
        {0, 100}
    };

    point r = {0, (int)1e9};
    fill(line, line+4*maxn, r);
    for (int i = 0; i < (int)input_lines.size(); i++) {
        add_line(input_lines[i]);

        for (int x = 0; x <= 1000; x++) {
            ftype mi = 1e9;
            for (int j = 0; j <= i; j++) {
                mi = min(mi, f(input_lines[j], x));
            }
            assert(mi == get(x));
        }
    }
}
