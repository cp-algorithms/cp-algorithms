#include <cassert>
#include <vector>
#include <complex>
using namespace std;

namespace recursive {
#include "fft_recursive.h"
#include "fft_multiply.h"
}

namespace iterative {
#include "fft_implementation_iterative.h"
#include "fft_multiply.h"
}

namespace iterative_opt {
#include "fft_implementation_iterative_opt.h"
#include "fft_multiply.h"
}

namespace modular {
long long inverse(long long x, int mod) {
    long long res = 1;
    int e = mod - 2;
    while (e) {
        if (e & 1)
            res = res * x % mod;
        x = x * x % mod;
        e >>= 1;
    }
    return res;
}

#include "fft_implementation_modular_arithmetic.h"

vector<int> multiply(vector<int> a, vector<int> b) {
    int n = root_pw;
    a.resize(root_pw);
    b.resize(root_pw);

    fft(a, false);
    fft(b, false);
    for (int i = 0; i < n; i++)
        a[i] = (int)(1LL * a[i] * b[i] % mod);
    fft(a, true);

    return a;
}
}

int main() {
    vector<int> a = {-10, -51, -96, 2, 83, 95}; 
    vector<int> b = {1, -85, -62, -40, 94, -88, 58, 47, -45};
    vector<int> expected = {-10, 799, 4859, 11724, 6965, -7158, -18417, -4002, -3689, -475, 868, 9321, 730, -4275};

    {
        vector<int> result = recursive::multiply(a, b);
        for (int i = 0; i < (int)expected.size(); i++)
            assert(expected[i] == result[i]);
    }
    {
        vector<int> result = iterative::multiply(a, b);
        for (int i = 0; i < (int)expected.size(); i++)
            assert(expected[i] == result[i]);
    }
    {
        vector<int> result = iterative_opt::multiply(a, b);
        for (int i = 0; i < (int)expected.size(); i++)
            assert(expected[i] == result[i]);
    }

    {
        vector<int> result = modular::multiply(a, b);
        for (int i = 0; i < (int)expected.size(); i++)
            assert((expected[i] - result[i]) % modular::mod == 0);
    }
}
