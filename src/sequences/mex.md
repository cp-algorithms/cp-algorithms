---
tags:
    - Original
title: MEX (minimal excluded) of a sequence
---
# MEX of a sequence in O(N)

Given an array $A$ of size $N$. You have to find the minimal element that is not present in the array and is equal to or greater than $0$. See [Wikipedia](https://en.wikipedia.org/wiki/Mex_(mathematics)) for more information.

First we have to create a set of all elements in the array to quickly check for element presence in $O(1)$. Then check all numbers from $0$ to $N$. If the current number is not present in the set, return it. If all numbers are present in the set, return $N$, because all elements from $0$ to $N-1$ are present.

*NB*: This approach is fast, but works well only if your array doesn't change during program execution, e.g. it is not effective in problems with changing the initial array. If your array is changed by any type of array queries, use [O(N log N) approach](https://codeforces.com/blog/entry/81287?#comment-677837) instead.

## Implementation (C++):

```cpp
int mex(vector<int> a) {
	set<int> b(a.begin(), a.end());
	for (int i=0; ; ++i)
		if (!b.count(i))
			return i;
}
```

If an algorithm requires fast $O(N)$ MEX computation, it is possible by computing an boolean vector of existing elements and then checking the first non-present one:

```cpp
int mex (const vector<int> & a) {
	static bool used[D+1] = { 0 };
	int c = (int) a.size();

	for (int i=0; i<c; ++i)
		if (a[i] <= D)
			used[a[i]] = true;

	int result;
	for (int i=0; ; ++i)
		if (!used[i]) {
			result = i;
			 break;
		}
 
	for (int i=0; i<c; ++i)
		if (a[i] <= D)
			used[a[i]] = false;

	return result;
}
```


## Practice Problems

- [CODEFORCES: Replace by MEX](https://codeforces.com/contest/1375/problem/D)
