#include <cassert>
#include <vector>
#include <sstream>

using namespace std;

#include "next_combination.h"

namespace Naive {
stringstream cout;
#include "generate_all_combinations_naive.h"
}

namespace Fast {
stringstream cout;
#include "generate_all_combinations_fast.h"
}

int main() {
    vector<int> comb = {1, 3, 6};
    vector<int> next = {1, 4, 5};
    next_combination(comb, 6);
    assert(next == comb);

    string all = "123\n134\n234\n124\n145\n245\n345\n135\n235\n125\n";
    Naive::all_combinations(5, 3);
    assert(Naive::cout.str() == all);

    string all2 = "345\n235\n234\n245\n125\n124\n123\n135\n134\n145\n";
    Fast::all_combinations(5, 3);
    assert(Fast::cout.str() == all2);
}
