#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
using namespace std;

#include "snippets/2sat.h"

namespace
{
TEST(TwoSAT, ExampleUsage)
{
    TwoSatSolver::example_usage();
}

TEST(TwoSAT, ArticleExample)
{
    TwoSatSolver solver(3); // a, b, c
    solver.add_disjunction(0, false, 1, true); //      a  v not b
    solver.add_disjunction(0, true, 1, false); //  not a  v     b
    solver.add_disjunction(0, true, 1, true);  //  not a  v not b
    solver.add_disjunction(0, false, 2, true); //      a  v not c
    EXPECT_TRUE(solver.solve_2SAT());
    auto expected = vector<bool>{{false, false, false}};
    EXPECT_EQ(solver.assignment, expected);
}

TEST(TwoSAT, Unsatisfiable)
{
    TwoSatSolver solver(2); // a, b
    solver.add_disjunction(0, false, 1, false); //      a  v      b
    solver.add_disjunction(0, false, 1, true);  //      a  v  not b
    solver.add_disjunction(0, true, 1, false);  //  not a  v      b
    solver.add_disjunction(0, true, 1, true);   //  not a  v  not b
    EXPECT_FALSE(solver.solve_2SAT());
}

TEST(TwoSAT, OtherSatisfiableExample)
{
    TwoSatSolver solver(4); // a, b, c, d
    solver.add_disjunction(0, false, 1, true); //      a  v  not b
    solver.add_disjunction(0, true, 2, true);  //  not a  v  not c
    solver.add_disjunction(0, false, 1, false); //     a  v      b
    solver.add_disjunction(3, false, 2, true); //      d  v  not c
    solver.add_disjunction(3, false, 0, true); //      d  v  not a
    EXPECT_TRUE(solver.solve_2SAT());
    // two solutions
    auto expected_1 = vector<bool>{{true, true, false, true}};
    auto expected_2 = vector<bool>{{true, false, false, true}};
    EXPECT_THAT(solver.assignment, ::testing::AnyOf(expected_1, expected_2));
}

} // namespace
