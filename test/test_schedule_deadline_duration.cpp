#include <cassert>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#include "schedule_deadline_duration.h"

int main() {
    vector<Job> jobs = {
        {6, 5, 1},
        {15, 2, 2},
        {18, 5, 3},
        {16, 2, 4},
        {14, 1, 5},
        {5, 8, 6},
        {5, 6, 7},
        {17, 9, 8},
        {9, 6, 9},
        {10, 1, 10}
    };
    vector<int> schedule = compute_schedule(jobs);
    set<int> optimal = {1, 2, 3, 4, 5, 10};
    set<int> result(schedule.begin(), schedule.end());
    assert(result == optimal);
}
