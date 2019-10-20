#include<bits/stdc++.h>

using namespace std;

#include "gauss.h"

typedef double dbl;
typedef vector<vector<dbl> > matrix;
typedef vector<dbl> vec;

void test1(){
    //x + y = 0
    matrix A = {{1, 1}};
    vec b = {0};
    vec ans(2);
    A[0].push_back(b[0]);
    assert(gauss(A, ans) == INF);
}

void test2(){
    //x + y = 0
    //2x + 3y = 1
    matrix A = {{1, 1}, {2, 3}};
    vec b = {0, 1};
    vec ans(2);
    A[0].push_back(b[0]);
    A[1].push_back(b[1]);
    assert(gauss(A, ans) == 1);
    assert(abs(ans[0] + 1) < EPS && abs(ans[1] - 1) < EPS);
}

void test3(){
    //x = 0
    //y = 1
    //x + y = 2
    matrix A = {{1, 0}, {0, 1}, {1, 1}};
    vec b = {0, 1, 2};
    vec ans(2);
    A[0].push_back(b[0]);
    A[1].push_back(b[1]);
    A[2].push_back(b[2]);
    assert(gauss(A, ans) == 0);
}

int main(){
    test1();
    test2();
    test3();
}
