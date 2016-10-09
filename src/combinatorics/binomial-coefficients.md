<!--?title Binomial Coefficients--> 
# Binomial Coefficients

Binomial coefficients $\binom n k$ are the numbers of ways to select a set of $k$ elements from $n$ different elements without taking into account the order of arrangement of these elements (i.e., the numbers of unordered sets). 

Binomial coefficients are also the coefficients in the expansion of $(a + b) ^ n$ (The so-called binomial theorem): 

$$ (a+b)^n = \binom n 0 a^n + \binom n 1 a^{n-1} b + \binom n 2 a^{n-2} b^2 + \cdots + \binom n k a^{n-k} b^k + \cdots + \binom n n b^n $$

It is believed that this formula, as a triangle, allowing effective finding of the coefficients was discovered by Blaise Pascal, who lived in the 17th century. Nevertheless, it was known to the Chinese mathematician Yang Hui(楊輝), who lived in the 13th century. Perhaps it was discovered by a Persian scholar Omar Khayyam(عمر خیام). Moreover, Indian mathematician Pingala (पिङ्गल), who lived  earlier in the 3rd. BC, got similar results. The merit of the Newton is that he generalized this formula for exponents that are not natural. 

## Calculation

**Analytic formula** for the calculation: 

$$ \binom n k = \frac {n!} {k!(n-k)!} $$

This formula can be easily deduced from the problem of ordered arrangement (number of ways to select k different elements from n different elements). First, count $n$, the number of different elements. There are $n$ ways to select the first element, $n-1$ ways to select the second element, $n-2$ ways to select the third element, and so on. As a result, we obtain the formula of the number of ordered arrangements: $n (n-1) (n-2) \cdots (n - k + 1) = \frac {n!} {(n-k)!}$. We can easily move to disordered arrangements, noting that each disordered arrangement corresponds exactly k! ordered arrangements(since it is the number of possible permutations of $k$ elements). As a result, by dividing $\frac {n!} {(n-k)!}$ by $k!$ , we obtain the required formula. 

**Recurrent formula** (which is associated with the famous "Pascal's Triangle"):

$$ \binom n k = \binom {n-1} {k-1} + \binom {n-1} k $$

It is easy to deduce through the previous formula.

It is worth noting especially when $n \lt k$ the value of $\binom n k$ is always assumed to be zero. 

## Properties

Binomial coefficients have many different properties, we present the simplest of them:

*   Symmetry rule:
$$ \binom n k = \binom n {n-k} $$
*   Adding-imposition:
$$ \binom n k = \frac n k \binom {n-1} {k-1} $$
*   Summation over $k$:
$$ \sum_{k = 0}^n \binom n k = 2 ^ n $$
*   Summation over $n$:
$$ \sum_{m = 0}^n \binom m k = \binom {n + 1} {k + 1} $$
*   Summation over $n$ and $k$:
$$ \sum_{k = 0}^m  \binom {n + k} k = \binom {n + m + 1} m $$
*   The summation of the squares:
$$ {\binom n 0}^2 + {\binom n 1}^2 + \cdots + {\binom n n}^2 = \binom {2n} n $$
*   The weighted summation:
$$ 1 \binom n 1 + 2 \binom n 2 + \cdots + n \binom n n = n 2^{n-1} $$
*   Conenction with the [Fibonacci numbers](./algebra/fibonacci-numbers.html):
$$ \binom n 0 + \binom {n-1} 1 + \cdots + \binom {n-k} k + \cdots + \binom 0 n = F_{n+1} $$

## Calculations in the program

### Direct calculations of the Analytical formula 

Calculations by the first, direct formula is very easy to program, but this method is likely to overflow, even for relatively small values of n and k (even if the answer completely fit into any type of data, the calculation of the intermediate factorials can lead to overflow). Therefore, very often, this method can only be used with the [Long arithmetic](./algebra/big-integer.html):

Here's a C++ implementation:

```cpp
int C (int n, int k) {
	int res = 1;
	for (int i=n-k+1; i<=n; ++i)
		res *= i;
	for (int i=2; i<=k; ++i)
		res /= i;
}
```

### Improved implementation

It may be noted that in the above implementation of the numerator and the denominator have the same number of factors ($k$), each of which is less than unity. Therefore, we can replace our work with multiplying $k$ fractions, each of which is real-valued. However, you will notice that, after mupltiplying current answer by each of the next fractions, the answer will still be integer (this, for example, follows the property of the "adding-imposition").

Here's a C++ implementation:

```cpp
int C (int n, int k) {
	double res = 1;
	for (int i=1; i<=k; ++i)
		res = res * (n-k+i) / i;
	return (int) (res + 0.01);
}
```

Here we carefully cast the floating point number to an integer, taking into account that due to the accumulated errors, it may be slightly less than the true value (for example, $2.99999$ instead of $3$).

### Pascal's Triangle

By using the recurrence relation we can construct a table of binomial coefficients (in fact, Pascal's triangle), and take the result from it. The advantage of this method are that intermediate results never exceed the anwser and calculating each new table element needs only one addition. The drawback is slow operation for large $n$ and $k$, if in fact the table is not necessary, and you just need a single value (because in order to calculate $\binom n k$ you will need to build a table for all $\binom i j, 1 \le i \le n, 1 \le j \le n$, or at least to $1 \le j \le \min (i, k)$).

Here's a C++ implementation:

```cpp
const int maxn = ...;
int C[maxn+1][maxn+1];
for (int n=0; n<=maxn; ++n) {
	C[n][0] = C[n][n] = 1;
	for (int k=1; k<n; ++k)
		C[n][k] = C[n-1][k-1] + C[n-1][k];
}
```

If the entire table of values is not necessary, it is easy to see, store only two lines of it is enough (current - $n$-th row and the previous - $n-1$-th).

### Calculation of $O(1)$

Finally, in some situations it is beneficial to pre-calculate all the factorials in order to produce any necessary binomial coefficient with only two divisions later.This can be advantageous when using [long arithmetic](./algebra/big-integer.html), when the memory does not allow precalculation of all Pascal's triangle, or when you need to make calculations for some prime modulo (if the modulus is not prime, then there are difficulties in dividing the numerator by the denominator and can be overcome by factoring modulus and store all numbers in the form of vectors of powers of these primes, [see the section "Long arithmetic in factored form"](./algebra/big-integer.html)).
