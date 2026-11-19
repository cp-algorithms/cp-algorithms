#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
// Select the portable predicate after system headers have detected native types.
#undef __SIZEOF_INT128__
#include "delaunay.h"
#include "data/delaunay_regression.h"
int main() {
    DelaunayRegression::run();
}
