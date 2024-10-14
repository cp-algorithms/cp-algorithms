#include <cassert>
#include <vector>
using namespace std;

#include "2sat.h"

void test_2sat_example_usage() {
    TwoSatSolver::example_usage();
}

void test_2sat_article_example() {
    TwoSatSolver solver(3); // a, b, c
    solver.add_disjunction(0, false, 1, true); //      a  v not b
    solver.add_disjunction(0, true, 1, false); //  not a  v     b
    solver.add_disjunction(0, true, 1, true);  //  not a  v not b
    solver.add_disjunction(0, false, 2, true); //      a  v not c
    assert(solver.solve_2SAT() == true);
    auto expected = vector<bool>{{false, false, false}};
    assert(solver.assignment == expected);
}

void test_2sat_unsatisfiable() {
    TwoSatSolver solver(2); // a, b
    solver.add_disjunction(0, false, 1, false); //      a  v      b
    solver.add_disjunction(0, false, 1, true);  //      a  v  not b
    solver.add_disjunction(0, true, 1, false);  //  not a  v      b
    solver.add_disjunction(0, true, 1, true);   //  not a  v  not b
    assert(solver.solve_2SAT() == false);
}

void test_2sat_other_satisfiable_example() {
    TwoSatSolver solver(4); // a, b, c, d
    solver.add_disjunction(0, false, 1, true); //      a  v  not b
    solver.add_disjunction(0, true, 2, true);  //  not a  v  not c
    solver.add_disjunction(0, false, 1, false); //     a  v      b
    solver.add_disjunction(3, false, 2, true); //      d  v  not c
    solver.add_disjunction(3, false, 0, true); //      d  v  not a
    assert(solver.solve_2SAT() == true);
    // two solutions
    auto expected_1 = vector<bool>{{true, true, false, true}};
    auto expected_2 = vector<bool>{{true, false, false, true}};
    assert(solver.assignment == expected_1 || solver.assignment == expected_2);
}

int main() {
    test_2sat_example_usage();
    test_2sat_article_example();
    test_2sat_unsatisfiable();
    test_2sat_other_satisfiable_example();
}
