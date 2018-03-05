#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

#include "johnsons_rule.h"

int main() {
    // example from wikipedia
    vector<Job> jobs = {
        {32, 42, 1},
        {47, 15, 2},
        {22, 50, 3},
        {58, 40, 4},
        {31, 28, 5}
    };
    auto schedule = johnsons_rule(jobs);
    assert(finish_times(schedule) == make_pair(190, 205));
}
