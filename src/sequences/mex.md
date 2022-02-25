---
title: MEX (minimal excluded) of a sequence
---
# MEX of a sequence in O(N)

Given an array __A__ of size __N__. You have to find the minimal element that is not present in the array and is equal to or greater than 0. See [Wikipedia](https://en.wikipedia.org/wiki/Mex_(mathematics)) for more information.

First we have to create a set of all elements in the array to quickly check for element presence in O(1). Then check all numbers from 0 to __N__. If the current number is not present in the set, return it. If all numbers are present in the set, return __N__, because all elements from 0 to __N__ - 1 are present.

*NB*: This approach is fast, but works well only if your array doesn't change during program execution, e.g. it is not effective in problems with changing the initial array. If your array is changed by any type of array queries, use [O(N log N) approach](https://codeforces.com/blog/entry/81287?#comment-677837) instead.

## Implementation (Python, C++ will come soon):

```python
def mex(array):
    items = set(array)
    for i in range(len(array)):
        if i not in items:
            return i
    return len(array)
```


## Practice Problems

- [CODEFORCES: Replace by MEX](https://codeforces.com/contest/1375/problem/D)
