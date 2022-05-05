#include <iostream>
#include <vector>
#include <cassert>
#include <tuple>
using namespace std;

namespace e_maxx {
#include "extended_gcd.h"
}

namespace e_maxx_iter {
#include "extended_gcd_iter.h"
}

namespace std {
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> numbers = {11, 30, 24, 32, 50, 23, 11, 40, 47, 15, 30, 31, 0, 19, 23, 37, 48, 29, 37, 22};
    for (auto i = 0u; i + 1 < numbers.size(); i++) {
        int a = numbers[i];
        int b = numbers[i + 1];

        int x, y;
        int g = e_maxx::gcd(a, b, x, y);
        assert(g == std::gcd(a, b));
        assert(x * a + y * b == g);

        g = e_maxx_iter::gcd(a, b, x, y);
        assert(g == std::gcd(a, b));
        assert(x * a + y * b == g);
    }
}
