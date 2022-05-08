#include <cassert>
#include <vector>
using namespace std;

#include "2sat.h"

void setup(int size) {
  n = 2 * size;
  adj.clear();
  adj.resize(n);
  adj_t.clear();
  adj_t.resize(n);
}

void test_2sat_article_example() {
  setup(3);
  add_disjunction(0, 0, 1, 1); //     a v not b
  add_disjunction(0, 1, 1, 0); // not a v     b
  add_disjunction(0, 1, 1, 1); // not a v not b
  add_disjunction(0, 0, 2, 1); //     a v not c
  assert(solve_2SAT() == true);
  auto expected = vector<bool>{{false, false, false}};
  assert(assignment == expected);
}

void test_2sat_unsatisfiable() {
  setup(2);
  add_disjunction(0, 0, 1, 0); //     x v     y
  add_disjunction(0, 0, 1, 1); //     x v not y
  add_disjunction(0, 1, 1, 0); // not x v     y
  add_disjunction(0, 1, 1, 1); // not x v not y
  assert(solve_2SAT() == false);
}

void test_2sat_other_satisfiable_example() {
  setup(4);
  add_disjunction(0, 0, 1, 1); //     a v not b
  add_disjunction(0, 1, 2, 1); // not a v not c
  add_disjunction(0, 0, 1, 0); //     a v     b
  add_disjunction(3, 0, 2, 1); //     d v not c
  add_disjunction(3, 0, 0, 1); //     d v not a
  assert(solve_2SAT() == true);
  // two solutions
  auto expected_1 = vector<bool>{{true, true, false, true}};
  auto expected_2 = vector<bool>{{true, false, false, true}};
  assert(assignment == expected_1 || assignment == expected_2);
}

int main() {
  test_2sat_article_example();
  test_2sat_unsatisfiable();
  test_2sat_other_satisfiable_example();
}
