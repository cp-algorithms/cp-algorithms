#include <cassert>
#include <stack>
#include <string>
using namespace std;

namespace Simple {
#include "expression_parsing_simple.h"
}
namespace Unary {
#include "expression_parsing_unary.h"
}

int main() {
    {
        using namespace Simple;
        string exp = "1 + 2 * (3 - 4 * 5 + 2) / 2";
        assert(evaluate(exp) == -14);
    }
    {
        using namespace Unary;
        string exp = "---1 + 2 * (-3 - -4 * ++5 + -2) / +2";
        assert(evaluate(exp) == 14);
    }
}
