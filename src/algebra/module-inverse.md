<!--?title Modular Inverse -->

# Modular Multiplicative Inverse

## Definition

A [modular multiplicative inverse](http://en.wikipedia.org/wiki/Modular_multiplicative_inverse) of an integer $a$ is an integer $x$ such that $a \cdot x$ is congruent to $1$ modular some modulus $m$.
To write it in a formal way: we want to find an integer $x$ so that 
$$a \cdot x \equiv 1 \mod m.$$
We will also denote $x$ simply with $a^{-1}$.

We should note that the modular inverse does not always exist. For example, let $m = 4$, $a = 2$. 
By checking all possible values modulo $m$ is should become clear that we cannot find $a^{-1}$ satisfying the above equation. 
It can be proven that the modular inverse exists if and only if $a$ and $m$ are relatively prime (i.e. $\gcd(a, m) = 1$).

In this article, we present two methods for finding the modular inverse in case it exists, and one method for finding the modular inverse for all numbers in linear time.

## Finding the Modular Inverse using Extended Euclidean algorithm

Consider the following equation (with unknown $x$ and $y$):

$$a \cdot x + m \cdot y = 1$$

This is a [Linear Diophantine equation in two variables](./algebra/linear-diophantine-equation.html).
As shown in the linked article, when $\gcd(a, m) = 1$, the equation has a solution which can be found using the [extended Euclidean algorithm](http://en.wikipedia.org/wiki/Extended_Euclidean_algorithm).
Note that $\gcd(a, m) = 1$ is also the condition for the modular inverse to exist.

Now, if we take modulo $m$ of both sides, we can get rid of $m \cdot y$, and the equation becomes:

$$a \cdot x \equiv 1 \mod m$$

Thus, the modular inverse of $a$ is $x$.

The implementation is as follows:

```cpp
int x, y;
int g = extended_euclidean(a, m, x, y);
if (g != 1) {
    cout << "No solution!";
}
else {
    x = (x % m + m) % m;
    cout << x << endl;
}
```

Notice that we way we modify `x`.
The resulting `x` from the extended Euclidean algorithm may be negative, so `x % m` might also be negative, and we first have to add `m` to make it positive.

## Finding the Modular Inverse using Binary Exponentiation

Another method for finding modular inverse is to use Euler's theorem, which states that the following congruence is true if $a$ and $m$ are relatively prime:

$$a^{\phi (m)} \equiv 1 \mod m$$

$\phi$ is [Euler's Totient function](./algebra/phi-function.html).
Again, note that $a$ and $m$ being relative prime was also the condition for the modular inverse to exist.

If $m$ is a prime number, this simplifies to [Fermat's little theorem](http://en.wikipedia.org/wiki/Fermat's_little_theorem):

$$a^{m - 1} \equiv 1 \mod m$$

Multiply both sides of the above equations by $a^{-1}$, and we get:

* For an arbitrary (but coprime) modulus $m$: $a ^ {\phi (m) - 1} \equiv a ^{-1} \mod m$
* For a prime modulus $m$: $a ^ {m - 2} \equiv a ^ {-1} \mod m$

From these results, we can easily find the modular inverse using the [binary exponentiation algorithm](./algebra/binary-exp.html), which works in $O(\log m)$ time.

Even though this method is easier to understand than the method described in previous paragraph, in the case when $m$ is not a prime number, we need to calculate Euler phi function, which involves factorization of $m$, which might be very hard. If the prime factorization of $m$ is known, then the complexity of this method is $O(\log m)$.

## Finding the modular inverse for every numbers modulo $m$

The problem is the following: 
we want to compute the modular inverse for every number in the range $[1, m-1]$.

Applying the algorithms described in the previous sections, we can obtain a solution with complexity $O(m \log m)$. 

Here we present a better algorithm with complexity $O(m)$.
However for this specific algorithm we require that the modulus $m$ is prime.

We denote by $\text{inv}[i]$ the modular inverse of $i$. Then for $i > 1$ the following equation is valid:

$$\text{inv}[i] = - \left\lfloor \frac{m}{i} \right\rfloor \cdot \text{inv}[m \bmod i] \bmod m$$

Thus the implementation is very simple:

```cpp
inv[1] = 1;
for(int i = 2; i < m; ++i)
    inv[i] = (m - (m/i) * inv[m%i] % m) % m;
```

### Proof

We have:
$$m \bmod i = m -  \left\lfloor \frac{m}{i} \right\rfloor \cdot i$$
Taking both sides modulo $m$ yields:
$$m \bmod i \equiv - \left\lfloor \frac{m}{i} \right\rfloor \cdot i \mod m$$
Multiply both sides by $i^{-1} \cdot (m \bmod i)^{-1}$ yields
$$(m \bmod i) \cdot i^{-1} \cdot (m \bmod i)^{-1} \equiv -\left\lfloor \frac{m}{i} \right\rfloor \cdot i \cdot i^{-1} \cdot (m \bmod i)^{-1} \mod m,$$
which simplifies to:
$$i^{-1} \equiv -\left\lfloor \frac{m}{i} \right\rfloor \cdot (m \bmod i)^{-1} \mod m,$$

## Application: computing binomial coefficients modulo $m$.

Quite often you come across the problem of computing [binomial coefficients](./combinatorics/binomial-coefficients.html) modulo some $m$.

### Binomial coefficient modulo large prime

The formula for the binomial coefficients is
$$\binom n k = \frac {n!} {k!(n-k)!},$$
so if we want to compute it modulo some prime $m > n$ we get
$$\binom n k \equiv n! \cdot (k!)^{-1} \cdot ((n-k)!)^{-1} \mod m.$$

First we precompute all factorials modulo $m$ up to $\text{MAXN}!$ in $O(\text{MAXN})$ time.

```cpp
factorial[0] = 1;
for (int i = 1; i <= MAXN; i++) {
    factorial[i] = factorial[i - 1] * i % m;
}
```

And afterwards we can compute the binomial coefficient in $O(\log m)$ time.

```cpp
long long binomial_coefficient(int n, int k) {
    return factorial[n] * inverse(factorial[k]) % m * inverse(factorial[n - k]) % m;
}
```

We even can compute the binomial coefficient in $O(1)$ time if we precompute the inverses of all factorials in $O(\text{MAXN} \log m)$ using the regular method for computing the inverse, or even in $O(\text{MAXN})$ time using the congruence $(x!)^{-1} \equiv ((x-1)!)^{-1} \cdot x^{-1}$ and the method for computing all inverses in $O(m)$.

### Binomial coefficient modulo prime power

Here we want to compute the binomial coefficient modulo some prime power, i.e. $m = p^b$ for some prime $p$.
If $p > \max(k, n-k)$, then we can use the same method as described in the previous section.
But if $p \le \max(k, n-k)$, then at least one of $k!$ and $(n-k)!$ are not coprime with $m$, and therefore we cannot compute the inverses - they don't exist.
Nevertheless we can compute the binomial coefficient.

The idea is the following:
We compute for each $x!$ the biggest exponent $c$ such that $p^c$ divides $x!$, i.e. $p^c ~|~ x!$.
Let $c(x)$ be that number.
And let $g(x) := \frac{x!}{p^{c(x)}}$.
Then we can write the binomial coefficient as:
$$\binom n k = \frac {g(n) p^{c(n)}} {g(k) p^{c(k)} g(n-k) p^{c(n-k)}} = \frac {g(n)} {g(k) g(n-k)}p^{c(n) - c(k) - c(n-k)}$$

The interesting thing is, that $g(x)$ is now free from the prime divisor $p$.
Therefore $g(x)$ is coprime to m, and we can compute the modular inverses of $g(k)$ and $g(n-k)$.

After precomputing all values for $g$ and $c$ (which can be done efficiently using dynamic programming), we can compute the binomial coefficient in $O(\log m)$ time.
Or precompute all inverses and all powers of $p$, and then compute the binomial coefficient in $O(1)$.

Notice, if $c(n) - c(k) - c(n-k) \ge b$, than $p^b ~|~ p^{c(n) - c(k) - c(n-k)}$, and the binomial coefficient is $0$.

### Binomial coefficient modulo an arbitrary number

Now we compute the binomial coefficient modulo some arbitrary modulus $m$.

Let the prime factorization of $m$ be $m = p_1^{e_1} p_2^{e_2} \cdots p_h^{e_h}$.
We can compute the binomial coefficient modulo $p_i^{e_i}$ for every $i$.
This gives us $h$ different congruences.
Since all moduli $p_i^{e_i}$ are coprime, we can apply the [Chinese Remainder Theorem](./algebra/chinese-remainder-theorem.html) to compute the binomial coefficient modulo the product of the moduli, which is the desired binomial coefficient modulo $m$.




## Practice Problems

* [UVa 11904 - One Unit Machine](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3055)
* [Hackerrank - Longest Increasing Subsequence Arrays](https://www.hackerrank.com/contests/world-codesprint-5/challenges/longest-increasing-subsequence-arrays)
* [Codeforces 300C - Beautiful Numbers](http://codeforces.com/problemset/problem/300/C)
* [Codeforces 622F - The Sum of the k-th Powers](http://codeforces.com/problemset/problem/622/F)
* [Codeforces 717A - Festival Organization](http://codeforces.com/problemset/problem/717/A)
* [Codeforces 896D - Nephren Runs a Cinema](http://codeforces.com/problemset/problem/896/D)
