<!--?title Efficient integer factorization -->
# Efficient integer factorization

In this article we list several algorithms for factorizing integers, each of them can be both fast and also very slowly depending on their input.
But in sum they combine to a very fast method.

## Trial division

This is the most basic algorithm to find a prime factorization.

We divide by each possible divisor $d$.
We can notice, that it is impossible that all prime factors of a composite number $n$ are bigger than $\sqrt{n}$.
Therefore, we only need to test the divisors $2 \le d \le \sqrt{n}$, which gives us the prime factorization in $O(\sqrt{n})$.

The smallest divisor has to be a prime number.
We remove the factor from the number, and repeat the process.
If we cannot find any divisor in the range $[2; \sqrt{n}]$, then the number itself has to be prime.

```cpp factorization_trial_division1
vector<long long> trial_division1(long long n) {
    vector<long long> factorization;
    for (long long d = 2; d * d <= n; d++) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    if (n > 1)
        factorization.push_back(n);
    return factorization;
}
```

### Wheel factorization

This is an optimization of the trial division.
The idea is the following.
Once we know that the number is not divisible by 2, we don't need to check every other even number.
This leaves us with only $50\%$ of the numbers to check.
After checking 2, we can simply start with 3 and skip every other number.

```cpp factorization_trial_division2
vector<long long> trial_division2(long long n) {
    vector<long long> factorization;
    while (n % 2 == 0) {
        factorization.push_back(2);
        n /= 2;
    }
    for (long long d = 3; d * d <= n; d += 2) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    if (n > 1)
        factorization.push_back(n);
    return factorization;
}
```

This method can be extended.
If the number is not divisible by 3, we can also ignore all other multiples of 3 in the future computations.
So we only need to check the numbers $5, 7, 11, 13, 17, 19, 23, \dots$.
We can observe a pattern of these remaining numbers.
We need to check all numbers with $d \bmod 6 = 1$ and $d \bmod 6 = 5$.
So this leaves us with only $33.3\%$ percent of the numbers to check.
We can implement this by checking the primes 2 and 3 first, and then start checking with 5 and alternatively skip 1 or 3 numbers.

We can extend this even further.
Here is an implementation for the prime number 2, 3 and 5.
It's convenient to use an array to store how much we have to skip.

```cpp factorization_trial_division3
vector<long long> trial_division3(long long n) {
    vector<long long> factorization;
    for (int d : {2, 3, 5}) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    static array<int, 8> increments = {4, 2, 4, 2, 4, 6, 2, 6};
    int i = 0;
    for (long long d = 7; d * d <= n; d += increments[i++]) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
        if (i == 8)
            i = 0;
    }
    if (n > 1)
        factorization.push_back(n);
    return factorization;
}
```

If we extend this further with more primes, we can even reach better percentages.
However, also the skip lists will get a lot bigger.

### Precomputed primes

Extending the wheel factorization with more and more primes will leave exactly the primes to check.
So a good way of checking is just to precompute all prime numbers until $\sqrt{n}$ and test them individually.

```cpp factorization_trial_division4
vector<long long> primes;

vector<long long> trial_division4(long long n) {
    vector<long long> factorization;
    for (long long d : primes) {
        if (d * d > n)
            break;
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    if (n > 1)
        factorization.push_back(n);
    return factorization;
}
```

## Pollard's $p - 1$ method

It is very likely that at least one factor of a number is $B$**-powersmooth** for small $B$.
$B$-powersmooth means, that every power $d^k$ of a prime $d$ that divides $p-1$ is at most $B$.
E.g. the prime factorization of $4817191$ are is $1303 \cdot 3697$.
And the factors are $31$-powersmooth and $16$-powersmooth respectably, because $1303 - 1 = 2 \cdot 3 \cdot 7 \cdot 31$ and $3697 - 1 = 2^4 \cdot 3 \cdot 7 \cdot 11$.
In 1974 John Pollard invented a method to extracts $B$-powersmooth factors from a composite number.

The idea comes from [Fermat's little theorem](./algebra/phi-function.html#application).
Let a factorization of $n$ be $n = p \cdot q$.
It says that if $a$ is coprime to $p$, the following statement holds:

$$a^{p - 1} \equiv 1 \pmod{p}$$

This also means that

$$a^{(p - 1)^k} \equiv a^{k \cdot (p - 1)} \equiv 1 \pmod{p}.$$

So for any $M$ with $p - 1 ~|~ M$ we know that $a^M \equiv 1$.
This means that $a^M - 1 = p \cdot r$, and because of that also $p ~|~ \gcd(a^M - 1, n)$.

Therefore, if $p - 1$ for a factor $p$ of $n$ divides $M$, we can extract a factor using [Euclid's algorithm](./algebra/euclid-algorithm.html).

It is clear, that the smallest $M$ that is a multiple of every $B$-powersmooth number is $\text{lcm}(1,~2~,3~,4~,~\dots,~B)$.
Or alternatively:
$$M = \prod_{\text{prime } q \le B} q^{\lfloor \log_q B \rfloor}$$

```cpp factorization_p_minus_1
vector<int> primes_100 = {2, 3, 5, 7, 11, 13, 17, 19, 23, 
                          29, 31, 37, 41, 43, 47, 53, 59,
                          61, 67, 71, 73, 79, 83, 89, 97};
int B = 100;

long long pollards_p_minus_1(long long n) {
    // perform 5 iterations with random a
    for (int iter = 1; iter <= 5; iter++) {
        long long a = rand() %  n;
        if (a < 2)
            continue;

        // test if a gives already a factor
        long long g = gcd(a, n);
        if (g > 1)
            return g;
        
        // compute a^M
        for (int p : primes_100) {
            int p_power = 1;
            while (p_power * p <= B)
                p_power *= p;
            a = power(a, p_power, n);

            g = gcd(a - 1, n);
            if (g > 1 && g < n)
                return g;
        }
    }
    return 1;
}
```

Notice, this is a probabilistic algorithm.
It doesn't find a factor for every number.

The complexity is $O(B \log B \log^2 n)$ per iteration.

## Pollard's rho algorithm

Another factorization algorithm from John Pollard.

Let the prime factorization from a number be $n = p q$.
The algorithm look at a pseudo-random sequence $\{x_i\} = \{x_0,~f(x_0),~f(f(x_0)),~\dots\}$ where $f$ is a polynomial function, usually $f(x) = x^2 + c \bmod n$ is chosen with $c = 1$.

Actually we are not very interested in the sequence $\{x_i\}$, we are more interested in the sequence $\{x_i \bmod p\}$.
Since $f$ is a polynomial function and all the values are in the range $[0;~p)$ this sequence will begin to cycle sooner or later.
The **birthday paradox** actually suggests, that the expected number of elements is $O(\sqrt{p})$ until the repetition starts.
If $p$ is smaller than $\sqrt{n}$, the repetition will start very likely in $O(\sqrt[4]{n})$.

Here is a visualization of such a sequence $\{x_i \bmod p\}$ with $n = 2206637$, $p = 317$, $x_0 = 2$ and $f(x) = x^2 + 1$.
From the form of the sequence you can see very clearly why the algorithm is called Pollard's $\rho$ algorithm.

<center>![Pollard's rho visualization](https://image.ibb.co/etmP3L/pollard-rho.png)</center>
<!-- %imgroot%/pollard_rho.png)</center> -->

There is still one big open question.
We don't know $p$ yet, so how can we argue about the sequence $\{x_i \bmod p\}$?

It's quite easy.
Even if we don't know $p$ and the cycle-start, cycle-length, ... we can find it using any common cycle detection algorithm.
There is a cycle in the sequence $\\{x_i \bmod p\\}_{i \le j}$ if and only if there are two indices $s, t \le j$ and $t$ with $x_s \equiv x_t \bmod p$.
This equation can be rewritten as $x_s - x_t \equiv 0 \bmod p$ which is the same as $p ~|~ \gcd(x_s - x_t, n)$.

Therefore, if we find two indices $s$ and $t$ with $g = \gcd(x_s - x_t, n) > 1$, we have found a factor $g$ of $n$.
Notice that it is possible that $g = n$.
In this case we haven't found a proper factor, and we have to repeat the algorithm with different parameter (different starting value $x_0$, different constant $c$ in the polynomial function $f$).

To find the cycle efficiently, we can use **Floyd's cycle-finding algorithm**, which finds the cycle in linear time.
Therefore, the algorithm runs (usually) in $O(\sqrt[4]{n} \log(n))$ time.

The following code includes a function `mult`, that multiplies two integers $\le 10^{18}$ without overflow using a similar idea as [binary exponentiation](./algebra/binary-exp.html).

```cpp pollard_rho
long long mult(long long a, long long b, long long mod) {
    long long result = 0;
    while (b) {
        if (b & 1)
            result = (result + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return result;
}

long long f(long long x, long long c, long long mod) {
    return (mult(x, x, mod) + c) % mod;
}

long long rho(long long n, long long x0=2, long long c=1) {
    long long x = x0;
    long long y = x0;
    long long g = 1;
    while (g == 1) {
        x = f(x, c, n);
        y = f(y, c, n);
        y = f(y, c, n);
        g = gcd(abs(x - y), n);
    }
    return g;
}
```

As already noticed above: if $n$ is composite and the algorithm doesn't return $n$ as factor, you have to repeat the procedure with different parameter $x_0$ and $c$.

And the following table shows the values of $x$ and $y$ during the algorithm for $n = 2206637$, $x_0 = 2$ and $c = 1$.

$$
\newcommand\T{\Rule{0pt}{1em}{.3em}}
\begin{array}{|l|l|l|l|l|l|}
\hline
i & x_i \bmod n & x_{2i} \bmod n & x_i \bmod 317 & x_{2i} \bmod 317 & \gcd(x_i - x_{2i}, n) \\\\
\hline
0   & 2       & 2       & 2       & 2       & -   \\\\
1   & 5       & 26      & 5       & 26      & 1   \\\\
2   & 26      & 458330  & 26      & 265     & 1   \\\\
3   & 677     & 1671573 & 43      & 32      & 1   \\\\
4   & 458330  & 641379  & 265     & 88      & 1   \\\\
5   & 1166412 & 351937  & 169     & 67      & 1   \\\\
6   & 1671573 & 1264682 & 32      & 169     & 1   \\\\
7   & 2193080 & 2088470 & 74      & 74      & 317 \\\\
\hline
\end{array}$$


## Practice Problems

- [SPOJ - FACT0](https://www.spoj.com/problems/FACT0/)
- [SPOJ - FACT1](https://www.spoj.com/problems/FACT1/)
- [SPOJ - FACT2](https://www.spoj.com/problems/FACT2/)
- [GCPC 15 - Divisions](https://codeforces.com/gym/100753)
