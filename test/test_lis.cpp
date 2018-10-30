#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

namespace Method1 {
#include "lis_n2.h"
}

namespace Method1_Restore {
#include "lis_n2_restore.h"
}

namespace Method2 {
#include "lis_method2_n2.h"
}

namespace Method2_nlogn {
#include "lis_method2_nlogn.h"
}

int main() {
    vector<int> a = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};

    assert(Method1::lis(a) == 6);

    vector<int> subseq = {0, 4, 6, 9, 13, 15};
    assert(Method1_Restore::lis(a) == subseq);

    assert(Method2::lis(a) == 6);

    assert(Method2_nlogn::lis(a) == 6);
}
