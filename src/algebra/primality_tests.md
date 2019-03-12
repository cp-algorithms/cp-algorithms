<!--?title Primality tests -->
# Primality tests

This article describes multiple algorithms to determine if a number is prime or not.

# Fermat primality test

This is a probabilistic test.

Fermat's little theorem (see also [Euler's totient function](https://cp-algorithms.com/algebra/phi-function.html)) states, that for a prime number $p$ and coprime integer $a$ the following equation holds:

$$a^{p-1} \equiv 1 \bmod p$$

In general this theorem doesn't hold for composite numbers.

This can be used to create a primality test.
We pick an integer $2 \le a \le p - 2$, and check if the equation holds or not.
If it doesn't hold, e.g. $a^{p-1} \not\equiv 1 \bmod p$, we know that $p$ cannot be a prime number.
In this case we call the base $a$ a *Fermat witness* for the compositeness of $p$.

However it is also possible, that the equation holds for a composite number.
So if the equation holds, we don't have a proof for primality.
We only can say that $p$ is *probably prime*.
If it turns out that the number is actually composite, we call the base $a$ a *Fermat liar*.

By running the test for all possible bases $a$, we can actually prove that a number is prime.
However this is not done in practice, since this is a lot more effort that just doing *trial division*.
Instead the test will be repeated multiple times with random choices for $a$.
If we find no witness for the compositeness, it is very likely that the number is in fact prime.

```cpp
bool probablyPrimeFermat(int n, int iter) {
    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3);
        if (binpower(a, n - 1, n) != 1)
            return false;
    }
    return true;
}
```

We use [Binary Exponentiation](./algebra/binary-exp.html) to efficiently compute the power $a^{p-1}$.

There is one bad news though:
there exist some composite numbers where $a^{n-1} \equiv 1 \bmod n$ holds for all $a$ coprime to $n$, for instance for the number $561 = 3 \cdot 11 \cdot 17$.
Such numbers are called *Carmichael numbers*.
The Fermat primality test can identify these numbers only, if we randomly choose a base $a$ with $\gcd(a, n) \ne 1$, which is highly unlikely.

The Fermat test is still be used in practice, as it is very fast and Carmichael numbers are very rare.
There only exist 646 such numbers below $10^9$.

## Miller-Rabin primality test
