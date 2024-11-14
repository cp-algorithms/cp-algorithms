#include <bits/stdc++.h>
using namespace std;

#include "manacher_odd.h"

string getRandomString(size_t n, uint32_t seed, char minLetter='a', char maxLetter='b') {
    assert(minLetter <= maxLetter);
    const size_t nLetters = static_cast<int>(maxLetter) - static_cast<int>(minLetter) + 1;
    static std::uniform_int_distribution<size_t> distr(0, nLetters - 1);
    std::mt19937 gen(seed);

    string res;
    res.reserve(n);

    for (size_t i = 0; i < n; ++i)
        res.push_back('a' + distr(gen));

    return res;
}

bool testManacherOdd(const std::string &s) {
    const auto n = s.size();
    const auto d_odd = manacher_odd(s);

    if (d_odd.size() != n)
        return false;

    const auto inRange = [&](size_t idx) {
        return idx >= 0 && idx < n;
    };

    for (size_t i = 0; i < n; ++i) {
        if (d_odd[i] < 0)
            return false;
        for (int d = 0; d < d_odd[i]; ++d) {
            const auto idx1 = i - d;
            const auto idx2 = i + d;

            if (!inRange(idx1) || !inRange(idx2))
                return false;
            if (s[idx1] != s[idx2])
                return false;
        }

        const auto idx1 = i - d_odd[i];
        const auto idx2 = i + d_odd[i];
        if (inRange(idx1) && inRange(idx2) && s[idx1] == s[idx2])
            return false;
    }

    return true;
}

int main() {
    vector<string> testCases;

    testCases.push_back("");
    for (size_t i = 1; i <= 25; ++i) {
        auto s = string{};
        s.resize(i, 'a');
        testCases.push_back(move(s));
    }
    testCases.push_back("abba");
    testCases.push_back("abccbaasd");
    for (size_t n = 9; n <= 100; n += 10)
        testCases.push_back(getRandomString(n, /* seed */ n, 'a', 'd'));
    for (size_t n = 7; n <= 100; n += 10)
        testCases.push_back(getRandomString(n, /* seed */ n));

    for (const auto &s: testCases)
        assert(testManacherOdd(s));

    return 0;
}
