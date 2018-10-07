#include <cassert>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#include "nearest_pair_def.h"
#include "nearest_pair_update.h"
#include "nearest_pair_rec.h"

int main() {
    n = 5;
    a = {{0, 2, 0}, {6, 67, 1}, {43, 71, 2}, {39, 107, 3}, {189, 140, 4}};

    #include "nearest_pair_main.h"
    assert(abs(mindist - 36.2215) < 1e-3);
}
