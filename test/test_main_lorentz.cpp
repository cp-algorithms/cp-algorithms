#include <cassert>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#include "main_lorentz.h"

int main() {
    find_repetitions("acababaee");
    sort(repetitions.begin(), repetitions.end());
    vector<pair<int, int>> expected = {
        {2, 5}, 
        {3, 6},
        {7, 8}
    };
    assert(expected == repetitions);

    repetitions.clear();
    find_repetitions("abaaba");
    sort(repetitions.begin(), repetitions.end());
    expected = {
        {0, 5}, 
        {2, 3}
    };
    assert(expected == repetitions);

    repetitions.clear();
    find_repetitions("aaaaaa");
    sort(repetitions.begin(), repetitions.end());
    expected = {
        {0, 1}, 
        {0, 3},
        {0, 5},
        {1, 2}, 
        {1, 4},
        {2, 3}, 
        {2, 5},
        {3, 4},
        {4, 5},
    };
    assert(expected == repetitions);
}
