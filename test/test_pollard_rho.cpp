#include <cassert>
#include <cmath>
using namespace std;

long long gcd(long long a, long long b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

#include "pollard_rho.h"

int main() {
    long long n = 21471091LL * 38678789LL;
    long long g = rho(n);
    assert(g > 1 && g < n);
}
