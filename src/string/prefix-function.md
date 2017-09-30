<!--?title Prefix function. Knuth–Morris–Pratt algorithm -->

# Prefix function. Knuth–Morris–Pratt algorithm

## Prefix function definition

You are given a string $s$ of length $n$ $s[0..n-1]$. **Prefix function** for this string is defined as an array $\pi$
of length $n$ $\pi[0..n-1]$, where $\pi[i]$ is the length of the longest proper prefix of a substring $s[0...i]$
which is also a suffix of this substring. A proper prefix of a string is a prefix that is not equal to the string itself.
By definition, $\pi[0] = 0$.

Mathematically the definition of the prefix function can be written as follows:

$$\pi[i] = \max_ {k = 0..i} \\{k : s[0..k-1] = s[i-(k-1)..i] \\}$$

For example, prefix function of string "abcabcd" is $[0, 0, 0, 1, 2, 3, 0]$, and prefix function of string "aabaaab" is $[0, 1, 0, 1, 2, 2, 3]$.

## Trivial Algorithm

An algorithm which follows the definition of prefix function exactly is the following:

```cpp
vector<int> prefix_function (string s) {
	int n = (int) s.length();
	vector<int> pi (n);
	for (int i=0; i<n; ++i)
		for (int k=0; k<=i; ++k)
			if (s.substr(0,k) == s.substr(i-k+1,k))
				pi[i] = k;
	return pi;
}
```

It is easy to see that its complexity is $O(n^3)$, which has room for improvement.

## Efficient Algorithm

This algorithm was proposed by Knuth and Pratt and independently from them by Morris in 1977. 
It was used as the main element of a substring search algorithm.

### First Optimization

### Second Optimization

### Final Algorithm

### Implementation

The implementation ends up being surprisingly short and expressive.

```cpp
vector<int> prefix_function (string s) {
	int n = (int) s.length();
	vector<int> pi (n);
	for (int i=1; i<n; ++i) {
		int j = pi[i-1];
		while (j > 0 && s[i] != s[j])
			j = pi[j-1];
		if (s[i] == s[j])  ++j;
		pi[i] = j;
	}
	return pi;
}
```

This is an *online* algorithm, i.e. it processes the data as it arrives - for example, you can read the string 
characters one by one and process them immediately, finding the value of prefix function for each next character. 
The algorithm still requires storing the string itself and the previously calculated values of prefix function, 
but if we know beforehand the maximum value $M$ the prefix function can take on the string, we can store only $M+1$
first characters of the string and the same number of values of the prefix function.

## Practice Problems

* [UVA # 455 "Periodic Strings"](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=396)
* [UVA # 11022 "String Factoring"](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1963)
* [UVA # 11452 "Dancing the Cheeky-Cheeky"](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2447)
