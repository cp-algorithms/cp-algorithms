---
tags:
  - Original
---

# Number of divisors / sum of divisors

In this article we discuss how to compute the number of divisors $d(n)$ and the sum of divisors $\sigma(n)$ of a given number $n$.

## Number of divisors

It should be obvious that the prime factorization of a divisor $d$ has to be a subset of the prime factorization of $n$, e.g. $6 = 2 \cdot 3$ is a divisor of $60 = 2^2 \cdot 3 \cdot 5$.
So we only need to find all different subsets of the prime factorization of $n$.

Usually the number of subsets is $2^x$ for a set with $x$ elements.
However this is no longer true, if there are repeated elements in the set. In our case some prime factors may appear multiple times in the prime factorization of $n$.

If a prime factor $p$ appears $e$ times in the prime factorization of $n$, then we can use the factor $p$ up to $e$ times in the subset.
Which means we have $e+1$ choices.

Therefore if the prime factorization of $n$ is $p_1^{e_1} \cdot p_2^{e_2} \cdots p_k^{e_k}$, where $p_i$ are distinct prime numbers, then the number of divisors is:

$$d(n) = (e_1 + 1) \cdot (e_2 + 1) \cdots (e_k + 1)$$

A way of thinking about it is the following:

* If there is only one distinct prime divisor $n = p_1^{e_1}$, then there are obviously $e_1 + 1$ divisors ($1, p_1, p_1^2, \dots, p_1^{e_1}$).

* If there are two distinct prime divisors $n = p_1^{e_1} \cdot p_2^{e_2}$, then you can arrange all divisors in form of a tabular.

$$\begin{array}{c|ccccc}
& 1 & p_2 & p_2^2 & \dots & p_2^{e_2} \\\\\hline
1 & 1 & p_2 & p_2^2 & \dots & p_2^{e_2} \\\\
p_1 & p_1 & p_1 \cdot p_2 & p_1 \cdot p_2^2 & \dots & p_1 \cdot p_2^{e_2} \\\\
p_1^2 & p_1^2 & p_1^2 \cdot p_2 & p_1^2 \cdot p_2^2 & \dots & p_1^2 \cdot p_2^{e_2} \\\\
\vdots & \vdots & \vdots & \vdots & \ddots & \vdots \\\\
p_1^{e_1} & p_1^{e_1} & p_1^{e_1} \cdot p_2 & p_1^{e_1} \cdot p_2^2 & \dots & p_1^{e_1} \cdot p_2^{e_2} \\\\
\end{array}$$

So the number of divisors is trivially $(e_1 + 1) \cdot (e_2 + 1)$.

* A similar argument can be made if there are more then two distinct prime factors.


```cpp
long long numberOfDivisors(long long num) {
    long long total = 1;
    for (int i = 2; (long long)i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);
            total *= e + 1;
        }
    }
    if (num > 1) {
        total *= 2;
    }
    return total;
}
```

## Sum of divisors

We can use the same argument of the previous section.

* If there is only one distinct prime divisor $n = p_1^{e_1}$, then the sum is:

$$1 + p_1 + p_1^2 + \dots + p_1^{e_1} = \frac{p_1^{e_1 + 1} - 1}{p_1 - 1}$$

* If there are two distinct prime divisors $n = p_1^{e_1} \cdot p_2^{e_2}$, then we can make the same table as before.
  The only difference is that now we now want to compute the sum instead of counting the elements.
  It is easy to see, that the sum of each combination can be expressed as:

$$\left(1 + p_1 + p_1^2 + \dots + p_1^{e_1}\right) \cdot \left(1 + p_2 + p_2^2 + \dots + p_2^{e_2}\right)$$

$$ = \frac{p_1^{e_1 + 1} - 1}{p_1 - 1} \cdot \frac{p_2^{e_2 + 1} - 1}{p_2 - 1}$$

* In general, for $n = p_1^{e_1} \cdot p_2^{e_2} \cdots p_k^{e_k}$ we receive the formula:

$$\sigma(n) = \frac{p_1^{e_1 + 1} - 1}{p_1 - 1} \cdot \frac{p_2^{e_2 + 1} - 1}{p_2 - 1} \cdots \frac{p_k^{e_k + 1} - 1}{p_k - 1}$$

```cpp
long long SumOfDivisors(long long num) {
    long long total = 1;

    for (int i = 2; (long long)i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);

            long long sum = 0, pow = 1;
            do {
                sum += pow;
                pow *= i;
            } while (e-- > 0);
            total *= sum;
        }
    }
    if (num > 1) {
        total *= (1 + num);
    }
    return total;
}
```

## Multiplicative functions

A multiplicative function is a function $f(x)$ which satisfies

$$f(a \cdot b) = f(a) \cdot f(b)$$

if $a$ and $b$ are coprime.

Both $d(n)$ and $\sigma(n)$ are multiplicative functions.

Multiplicative functions have a huge variety of interesting properties, which can be very useful in number theory problems.
For instance the Dirichlet convolution of two multiplicative functions is also multiplicative.

## Practice Problems

  - [SPOJ - COMDIV](https://www.spoj.com/problems/COMDIV/)
  - [SPOJ - DIVSUM](https://www.spoj.com/problems/DIVSUM/)
  - [SPOJ - DIVSUM2](https://www.spoj.com/problems/DIVSUM2/)
