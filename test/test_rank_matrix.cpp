#include <bits/stdc++.h>

using namespace std;

#include "matrix-rank.h"

typedef double dbl;
typedef vector<vector<dbl> > matrix;

void test1(){
    matrix A(3);
    A[0] = {1, 1, 0};
    A[1] = {0, 1, 0};
    A[2] = {1, 0, 0};
    assert(compute_rank(A) == 2);
}

void test2(){
    matrix A(3);
    A[0] = {1, 1, 1};
    A[1] = {0, 1, 1};
    A[2] = {0, 0, 1};
    assert(compute_rank(A) == 3);
}

void test3(){
    matrix A(3);
    A[0] = {0, 0, 0};
    A[1] = {0, 0, 0};
    A[2] = {0, 0, 0};
    assert(compute_rank(A) == 0);
}

void test4(){
    matrix A(3);
    A[0] = {1, 1, 1};
    A[1] = {1, 1, 1};
    A[2] = {1, 1, 1};
    assert(compute_rank(A) == 1);
}

void test5(){
    matrix A(2);
    A[0] = {1, 0, 1, 0};
    A[1] = {0, 1, 0, 1};
    assert(compute_rank(A) == 2);
}

int main(){
    test1();
    test2();
    test3();
    test4();
    test5();
}
