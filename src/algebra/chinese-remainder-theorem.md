---
tags:
  - Translated
e_maxx_link: chinese_theorem
---

# Chinese Remainder Theorem

The Chinese Remainder Theorem (which will be referred to as CRT in the rest of this article) was discovered by Chinese mathematician Sun Zi.

## Formulation

Let $m = m_1 \cdot m_2 \cdots m_k$, where $m_i$ are pairwise coprime. In addition to $m_i$, we are also given a system of congruences

$$\left\{\begin{array}{rcl}
    a & \equiv & a_1 \pmod{m_1} \\
    a & \equiv & a_2 \pmod{m_2} \\
      & \vdots & \\
    a & \equiv & a_k \pmod{m_k}
\end{array}\right.$$

where $a_i$ are some given constants. The original form of CRT then states that the given system of congruences always has *one and exactly one* solution modulo $m$.

E.g. the system of congruences

$$\left\{\begin{array}{rcl}
    a & \equiv & 2 \pmod{3} \\
    a & \equiv & 3 \pmod{5} \\
    a & \equiv & 2 \pmod{7}
\end{array}\right.$$

has the solution $23$ modulo $105$, because $23 \bmod{3} = 2$, $23 \bmod{5} = 3$, and $23 \bmod{7} = 2$.
We can write down every solution as $23 + 105\cdot k$ for $k \in \mathbb{Z}$.


### Corollary

A consequence of the CRT is that the equation

$$x \equiv a \pmod{m}$$

is equivalent to the system of equations

$$\left\{\begin{array}{rcl}
    x & \equiv & a_1 \pmod{m_1} \\
      & \vdots & \\
    x & \equiv & a_k \pmod{m_k}
\end{array}\right.$$

(As above, assume that $m = m_1 m_2 \cdots m_k$ and $m_i$ are pairwise coprime).

## Solution for Two Moduli

Consider a system of two equations for coprime $m_1, m_2$:

$$
\left\{\begin{align}
    a &\equiv a_1 \pmod{m_1} \\
    a &\equiv a_2 \pmod{m_2} \\
\end{align}\right.
$$

We want to find a solution for $a \pmod{m_1 m_2}$. Using the [Extended Euclidean Algorithm](extended-euclid-algorithm.md) we can find Bézout coefficients $n_1, n_2$ such that

$$n_1 m_1 + n_2 m_2 = 1.$$

In fact $n_1$ and $n_2$ are just the [modular inverses](module-inverse.md) of $m_1$ and $m_2$ modulo $m_2$ and $m_1$.
We have $n_1 m_1 \equiv 1 \pmod{m_2}$ so $n_1 \equiv m_1^{-1} \pmod{m_2}$, and vice versa $n_2 \equiv m_2^{-1} \pmod{m_1}$. 

With those two coefficients we can define a solution:

$$a = a_1 n_2 m_2 + a_2 n_1 m_1 \bmod{m_1 m_2}$$

It's easy to verify that this is indeed a solution by computing $a \bmod{m_1}$ and $a \bmod{m_2}$.

$$
\begin{array}{rcll}
a & \equiv & a_1 n_2 m_2 + a_2 n_1 m_1 & \pmod{m_1}\\
  & \equiv & a_1 (1 - n_1 m_1) + a_2 n_1 m_1 & \pmod{m_1}\\
  & \equiv & a_1 - a_1 n_1 m_1 + a_2 n_1 m_1 & \pmod{m_1}\\
  & \equiv & a_1 & \pmod{m_1}
\end{array}
$$

Notice, that the Chinese Remainder Theorem also guarantees, that only 1 solution exists modulo $m_1 m_2$.
This is also easy to prove.

Lets assume that you have two different solutions $x$ and $y$.
Because $x \equiv a_i \pmod{m_i}$ and $y \equiv a_i \pmod{m_i}$, it follows that $x − y \equiv 0 \pmod{m_i}$ and therefore $x − y \equiv 0 \pmod{m_1 m_2}$ or equivalently $x \equiv y \pmod{m_1 m_2}$.
So $x$ and $y$ are actually the same solution.

## Solution for General Case

### Inductive Solution

As $m_1 m_2$ is coprime to $m_3$, we can inductively repeatedly apply the solution for two moduli for any number of moduli.
First you compute $b_2 := a \pmod{m_1 m_2}$ using the first two congruences,
then you can compute $b_3 := a \pmod{m_1 m_2 m_3}$ using the congruences $a \equiv b_2 \pmod{m_1 m_2}$ and $a \equiv a_3 \pmod {m_3}$, etc.

### Direct Construction

A direct construction similar to Lagrange interpolation is possible.

Let $M_i := \prod_{i \neq j} m_j$, the product of all moduli but $m_i$, and $N_i$ the modular inverses $N_i := M_i^{-1} \bmod{m_i}$.
Then a solution to the system of congruences is:

$$a \equiv \sum_{i=1}^k a_i M_i N_i \pmod{m_1 m_2 \cdots m_k}$$

We can check this is indeed a solution, by computing $a \bmod{m_i}$ for all $i$.
Because $M_j$ is a multiple of $m_i$ for $i \neq j$ we have

$$\begin{array}{rcll}
a & \equiv & \sum_{j=1}^k a_j M_j N_j & \pmod{m_i} \\
  & \equiv & a_i M_i N_i              & \pmod{m_i} \\
  & \equiv & a_i M_i M_i^{-1}         & \pmod{m_i} \\
  & \equiv & a_i                      & \pmod{m_i}
\end{array}$$

### Implementation

```{.cpp file=chinese_remainder_theorem}
struct Congruence {
    long long a, m;
};

long long chinese_remainder_theorem(vector<Congruence> const& congruences) {
    long long M = 1;
    for (auto const& congruence : congruences) {
        M *= congruence.m;
    }

    long long solution = 0;
    for (auto const& congruence : congruences) {
        long long a_i = congruence.a;
        long long M_i = M / congruence.m;
        long long N_i = mod_inv(M_i, congruence.m);
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    return solution;
}
```

## Solution for not coprime moduli

As mentioned, the algorithm above only works for coprime moduli $m_1, m_2, \dots m_k$.

In the not coprime case, a system of congruences has exactly one solution modulo $\text{lcm}(m_1, m_2, \dots, m_k)$, or has no solution at all.

E.g. in the following system, the first congruence implies that the solution is odd, and the second congruence implies that the solution is even.
It's not possible that a number is both odd and even, therefore there is clearly no solution.

$$\left\{\begin{align}
    a & \equiv 1 \pmod{4} \\
    a & \equiv 2 \pmod{6}
\end{align}\right.$$

It is pretty simple to determine is a system has a solution.
And if it has one, we can use the original algorithm to solve a slightly modified system of congruences.

A single congruence $a \equiv a_i \pmod{m_i}$ is equivalent to the system of congruences $a \equiv a_i \pmod{p_j^{n_j}}$ where $p_1^{n_1} p_2^{n_2}\cdots p_k^{n_k}$ is the prime factorization of $m_i$.

With this fact, we can modify the system of congruences into a system, that only has prime powers as moduli.
E.g. the above system of congruences is equivalent to:

$$\left\{\begin{array}{ll}
    a \equiv 1          & \pmod{4} \\
    a \equiv 2 \equiv 0 & \pmod{2} \\
    a \equiv 2          & \pmod{3}
\end{array}\right.$$

Because originally some moduli had common factors, we will get some congruences moduli based on the same prime, however possibly with different prime powers.

You can observe, that the congruence with the highest prime power modulus will be the strongest congruence of all congruences based on the same prime number.
Either it will give a contradiction with some other congruence, or it will imply already all other congruences.

In our case, the first congruence $a \equiv 1 \pmod{4}$ implies $a \equiv 1 \pmod{2}$, and therefore contradicts the second congruence $a \equiv 0 \pmod{2}$.
Therefore this system of congruences has no solution.

If there are no contradictions, then the system of equation has a solution.
We can ignore all congruences except the ones with the highest prime power moduli.
These moduli are now coprime, and therefore we can solve this one with the algorithm discussed in the sections above.

E.g. the following system has a solution modulo $\text{lcm}(10, 12) = 60$.

$$\left\{\begin{align}
    a & \equiv 3 \pmod{10} \\
    a & \equiv 5 \pmod{12}
\end{align}\right.$$

The system of congruence is equivalent to the system of congruences:

$$\left\{\begin{align}
    a & \equiv 3 \equiv 1 \pmod{2} \\
    a & \equiv 3 \equiv 3 \pmod{5} \\
    a & \equiv 5 \equiv 1 \pmod{4} \\
    a & \equiv 5 \equiv 2 \pmod{3}
\end{align}\right.$$

The only congruence with same prime modulo are $a \equiv 1 \pmod{4}$ and $a \equiv 1 \pmod{2}$.
The first one already implies the second one, so we can ignore the second one, and solve the following system with coprime moduli instead:

$$\left\{\begin{align}
    a & \equiv 3 \equiv 3 \pmod{5} \\
    a & \equiv 5 \equiv 1 \pmod{4} \\
    a & \equiv 5 \equiv 2 \pmod{3}
\end{align}\right.$$

It has the solution $53 \pmod{60}$, and indeed $53 \bmod{10} = 3$ and $53 \bmod{12} = 5$.

## Garner's Algorithm

Another consequence of the CRT is that we can represent big numbers using an array of small integers. For example, let $p$ be the product of the first $1000$ primes. From calculations we can see that $p$ has around $3000$ digits.

Any number $a$ less than $p$ can be represented as an array $a_1, \ldots, a_k$, where $a_i \equiv a \pmod{p_i}$. But to do this we obviously need to know how to get back the number $a$ from its representation. In this section, we discuss Garner's Algorithm, which can be used for this purpose. We seek a representation on the form

$$a = x_1 + x_2 \cdot p_1 + x_3 \cdot p_1 \cdot p_2 + \ldots + x_k \cdot p_1 \cdots p_{k-1}$$

which is called the mixed radix representation of $a$.
Garner's algorithm computes the coefficients $x_1, \ldots, x_k$.

Let $r_{ij}$ denote the inverse of $p_i$ modulo $p_j$

$$r_{ij} = (p_i)^{-1} \pmod{p_j}$$

which can be found using the algorithm described in [Modular Inverse](module-inverse.md). Substituting $a$ from the mixed radix representation into the first congruence equation we obtain

$$a_1 \equiv x_1 \pmod{p_1}.$$

Substituting into the second equation yields

$$a_2 \equiv x_1 + x_2 p_1 \pmod{p_2}.$$

which can be rewritten by subtracting $x_1$ and dividing by $p_1$ to get

$$\begin{array}{rclr}
    a_2 - x_1 &\equiv& x_2 p_1 &\pmod{p_2} \\
    (a_2 - x_1) r_{12} &\equiv& x_2 &\pmod{p_2} \\
    x_2 &\equiv& (a_2 - x_1) r_{12} &\pmod{p_2}
\end{array}$$

Similarly we get that

$$x_3 \equiv ((a_3 - x_1) r_{13} - x_2) r_{23} \pmod{p_3}.$$

Now, we can clearly see an emerging pattern, which can be expressed by the following code:

```cpp
for (int i = 0; i < k; ++i) {
    x[i] = a[i];
    for (int j = 0; j < i; ++j) {
        x[i] = r[j][i] * (x[i] - x[j]);

        x[i] = x[i] % p[i];
        if (x[i] < 0)
            x[i] += p[i];
    }
}
```

So we learned how to calculate coefficients $x_i$ in $O(k^2)$ time. The number $a$ can now be calculated using the previously mentioned formula

$$a = x_1 + x_2 \cdot p_1 + x_3 \cdot p_1 \cdot p_2 + \ldots + x_k \cdot p_1 \cdots p_{k-1}$$

It is worth noting that in practice, we almost always need to compute the answer using Big Integers, but the coefficients $x_i$ can usually be calculated using built-in types, and therefore Garner's algorithm is very efficient.

## Implementation of Garner's Algorithm

It is convenient to implement this algorithm using Java, because it has built-in support for large numbers through the `BigInteger` class.

Here we show an implementation that can store big numbers in the form of a set of congruence equations.
It supports addition, subtraction and multiplication.
And with Garner's algorithm we can convert the set of equations into the unique integer.
In this code, we take 100 prime numbers greater than $10^9$, which allows numbers as large as $10^{900}$.

```java
final int SZ = 100;
int pr[] = new int[SZ];
int r[][] = new int[SZ][SZ];

void init() {
    for (int x = 1000 * 1000 * 1000, i = 0; i < SZ; ++x)
        if (BigInteger.valueOf(x).isProbablePrime(100))
            pr[i++] = x;

    for (int i = 0; i < SZ; ++i)
        for (int j = i + 1; j < SZ; ++j)
            r[i][j] =
                BigInteger.valueOf(pr[i]).modInverse(BigInteger.valueOf(pr[j])).intValue();
}

class Number {
    int a[] = new int[SZ];

    public Number() {
    }

    public Number(int n) {
        for (int i = 0; i < SZ; ++i)
            a[i] = n % pr[i];
    }

    public Number(BigInteger n) {
        for (int i = 0; i < SZ; ++i)
            a[i] = n.mod(BigInteger.valueOf(pr[i])).intValue();
    }

    public Number add(Number n) {
        Number result = new Number();
        for (int i = 0; i < SZ; ++i)
            result.a[i] = (a[i] + n.a[i]) % pr[i];
        return result;
    }

    public Number subtract(Number n) {
        Number result = new Number();
        for (int i = 0; i < SZ; ++i)
            result.a[i] = (a[i] - n.a[i] + pr[i]) % pr[i];
        return result;
    }

    public Number multiply(Number n) {
        Number result = new Number();
        for (int i = 0; i < SZ; ++i)
            result.a[i] = (int)((a[i] * 1l * n.a[i]) % pr[i]);
        return result;
    }

    public BigInteger bigIntegerValue(boolean can_be_negative) {
        BigInteger result = BigInteger.ZERO, mult = BigInteger.ONE;
        int x[] = new int[SZ];
        for (int i = 0; i < SZ; ++i) {
            x[i] = a[i];
            for (int j = 0; j < i; ++j) {
                long cur = (x[i] - x[j]) * 1l * r[j][i];
                x[i] = (int)((cur % pr[i] + pr[i]) % pr[i]);
            }
            result = result.add(mult.multiply(BigInteger.valueOf(x[i])));
            mult = mult.multiply(BigInteger.valueOf(pr[i]));
        }

        if (can_be_negative)
            if (result.compareTo(mult.shiftRight(1)) >= 0)
                result = result.subtract(mult);

        return result;
    }
}
```

### Note on negative numbers

* Let $p$ be the product of all primes.

* Modular scheme itself does not allow representing negative numbers. However, it can be seen that if we know that the absolute values our numbers are smaller than $p / 2$, then we know that it must be negative when the resulting number is greater than $p / 2$. The flag `can_be_negative` in this code allows converting it to negative in this case.

## Practice Problems:

* [Google Code Jam - Golf Gophers](https://codingcompetitions.withgoogle.com/codejam/round/0000000000051635/0000000000104f1a#problem)
* [Hackerrank - Number of sequences](https://www.hackerrank.com/contests/w22/challenges/number-of-sequences)
* [Codeforces - Remainders Game](http://codeforces.com/problemset/problem/687/B)
