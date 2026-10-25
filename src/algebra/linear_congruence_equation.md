---
tags:
  - Translated
e_maxx_link: diofant_1_equation
---

# Linear Congruence Equation

This equation is of the form:

$$a \cdot x \equiv b \pmod n,$$

where $a$, $b$ and $n$ are given integers and $x$ is an unknown integer.

It is required to find the value $x$ from the interval $[0, n-1]$. On the entire number line $\mathbb{Z}$, when a solution exists, there are infinitely many solutions that differ from each other by multiples of $\frac{n}{\gcd(a, n)}$ (rather than just $n$). If the solution is not unique, then we will consider how to get all the solutions.

## Solution by finding the inverse element

Let us first consider a simpler case where $a$ and $n$ are **coprime** ($\gcd(a, n) = 1$).
Then one can find the [inverse](module-inverse.md) of $a$, and multiplying both sides of the equation with the inverse, we get a **unique** solution.

$$x \equiv b \cdot a ^ {- 1} \pmod n$$

Now consider the case where $a$ and $n$ are **not coprime** ($\gcd(a, n) \ne 1$).
Then the solution will not always exist (for example $2 \cdot x \equiv 1 \pmod 4$ has no solution).

Let $g = \gcd(a, n)$, i.e. the [greatest common divisor](euclid-algorithm.md) of $a$ and $n$ (which in this case is greater than one).

Then, if $b$ is not divisible by $g$, there is no solution. In fact, the congruence $a \cdot x \equiv b \pmod n$ is equivalent to the linear equation $a \cdot x - n \cdot q = b$ for some integer $q$. Since $g = \gcd(a, n)$ divides both $a$ and $n$, it must divide the left-hand side $a \cdot x - n \cdot q$, and therefore must divide the right-hand side $b$. If $g \nmid b$, no integer solution can exist.

If $g$ divides $b$, then by dividing both sides of the equation by $g$ (i.e. dividing $a$, $b$ and $n$ by $g$), we receive a new equation:

$$a^\prime \cdot x \equiv b^\prime \pmod{n^\prime}$$

in which $a^\prime = \frac{a}{g}$, $b^\prime = \frac{b}{g}$, and $n^\prime = \frac{n}{g}$, where $a^\prime$ and $n^\prime$ are already relatively prime ($\gcd(a^\prime, n^\prime) = 1$). Because dividing or multiplying the equation $a \cdot x - n \cdot q = b$ by $g \neq 0$ is an if-and-only-if algebraic equivalence ($\forall x, \, a \cdot x \equiv b \pmod n \iff a^\prime \cdot x \equiv b^\prime \pmod{n^\prime}$), no solutions are lost or introduced, and we have already learned how to handle such an equation.

We obtain a unique base solution $x^\prime$ modulo $n^\prime$.
It is clear that this $x^\prime$ will also be a solution of the original equation.
However, it will **not be the only solution**.
Since $x^\prime$ is unique modulo $n^\prime$, the general solution in $\mathbb{Z}$ is $x = x^\prime + i \cdot n^\prime$ for any integer $i$.
To find all distinct solutions modulo $n$, observe that two solutions $x^\prime + i \cdot n^\prime$ and $x^\prime + j \cdot n^\prime$ are congruent modulo $n$ if and only if $n = g \cdot n^\prime$ divides $(i - j) n^\prime$, which simplifies to $g \mid (i - j)$.
Thus, choosing $i = 0, 1, \dots, g - 1$ yields all $g$ mutually incongruent solutions strictly within $[0, n - 1]$:

$$x_i = x^\prime + i \cdot n^\prime \quad \text{for } i = 0 \ldots g-1$$

Summarizing, we can say that the **number of solutions** of the linear congruence equation is equal to either $g = \gcd(a, n)$ or to zero.

## Solution with the Extended Euclidean Algorithm

We can rewrite the linear congruence to the following Diophantine equation:

$$a \cdot x + n \cdot k = b,$$

where $x$ and $k$ are unknown integers.

The method of solving this equation is described in the corresponding article [Linear Diophantine equations](linear-diophantine-equation.md) and it consists of applying the [Extended Euclidean Algorithm](extended-euclid-algorithm.md).

It also describes the method of obtaining all solutions of this equation from one found solution, and incidentally this method, when carefully considered, is absolutely equivalent to the method described in the previous section.

Specifically, let $g = \gcd(a, n)$. If $g \mid b$, by Bézout's Identity we can find integers $u$ and $v$ using the Extended Euclidean Algorithm such that:

$$a \cdot u + n \cdot v = g$$

Multiplying both sides by $b^\prime = \frac{b}{g}$ gives:

$$a \cdot (u \cdot b^\prime) + n \cdot (v \cdot b^\prime) = b \implies a \cdot (u \cdot b^\prime) \equiv b \pmod n$$

Thus, $x = u \cdot b^\prime$ is a solution. Reducing it modulo $n^\prime = \frac{n}{g}$ gives the unique base solution $x^\prime = (u \cdot b^\prime) \bmod n^\prime$ in $[0, n^\prime - 1]$ (valid because $a \cdot n^\prime = a^\prime \cdot n \equiv 0 \pmod n$, so adding multiples of $n^\prime$ preserves validity modulo $n$), from which all $g$ distinct solutions modulo $n$ are obtained as $x_i = x^\prime + i \cdot n^\prime$ for $i = 0, 1, \dots, g - 1$.

### Implementation

```{.cpp file=solve_linear_congruence}
long long extgcd(long long a, long long b, long long &u, long long &v) {
    if (b == 0) {
        u = 1;
        v = 0;
        return a;
    }
    long long u1, v1;
    long long g = extgcd(b, a % b, u1, v1);
    u = v1;
    v = u1 - v1 * (a / b);
    return g;
}

// Finds all solutions to a * x = b (mod n) in the interval [0, n - 1].
// Precondition: n > 0.
// Complexity: O(log n + g) time and O(g) space, where g = gcd(a, n).
vector<long long> solve_linear_congruence(long long a, long long b, long long n) {
    if (n <= 0) {
        return {};
    }
    a %= n;
    if (a < 0) a += n;
    b %= n;
    if (b < 0) b += n;

    long long u, v;
    long long g = extgcd(a, n, u, v);

    if (b % g != 0) {
        return {};
    }

    long long n_prime = n / g;
    long long b_prime = b / g;

    long long x_prime = u % n_prime;
    if (x_prime < 0) x_prime += n_prime;
    // Cast to __int128 to prevent overflow when n_prime > 3 * 10^9
    x_prime = (long long)((__int128)x_prime * b_prime % n_prime);

    vector<long long> solutions(g);
    for (long long i = 0; i < g; ++i) {
        solutions[i] = x_prime + i * n_prime;
    }
    return solutions;
}
```
