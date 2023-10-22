---
tags:
  - Fibonacci
  - Dynamic Programming
  - Algorithm
---

# FibonacciByDynamicProgramming

This is a C++ program to calculate Fibonacci numbers using dynamic programming. Fibonacci numbers are a sequence of numbers where each number is the sum of the two preceding ones. This program uses a dynamic programming approach to efficiently compute these numbers.

## Description

The `FibonacciByDynamicProgramming` program efficiently calculates Fibonacci numbers using dynamic programming. It uses an array to store previously computed Fibonacci numbers, which allows it to optimize the calculation process. By avoiding redundant calculations, this program can handle even large Fibonacci numbers with ease.

## Algorithm

The Fibonacci sequence is typically defined recursively, but this program takes advantage of a more efficient approach. It uses an array to store the Fibonacci numbers as they are computed, starting with the first two values: 0 and 1. By iteratively calculating the next number in the sequence and updating the array, it avoids recalculating the same values multiple times.

Here's a simplified version of the algorithm:

1. Initialize an array to store Fibonacci numbers, starting with `[0, 1]`.
2. For the desired `n`, calculate and store each Fibonacci number from `2` to `n` in the array.
3. The `n`-th Fibonacci number is then available in the array.

## Usage

Compile and run the program, and it will prompt you to enter the range limit for the Fibonacci series. After providing the input, it will display the Fibonacci numbers up to the specified range.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int FibonacciByDynamicProgramming(int n) {
    
    vector<int> fibo_array={0,1};

    int size=2;

    if(n<=2){
        return fibo_array[n-1];
    }

    for(int i=0;i<n-2;i++){
        fibo_array.push_back(fibo_array[size-1]+fibo_array[size-2]);
        size++;
    }

    return fibo_array[size-1];

}


int main() {
    int num;
    cout << "Enter the range limit for the Fibonacci series: ";
    cin >> num;

    for (int i = 1; i <= num; i++) {
        cout << FibonacciByDynamicProgramming(i) << " ";
    }

    return 0;
}
