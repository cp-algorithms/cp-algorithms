<!--?title Modular Inverse -->

# Modular Multiplicative Inverse

## Definition

Suppose we are given a positive integer $m$. Consider the integers in modulo $m$ (i.e. all integers from $0$ to $m-1$). Then, for some integer $a$, we can find its [modular multiplicative inverse](http://en.wikipedia.org/wiki/Modular_multiplicative_inverse), denoted by $a ^ {-1}$, which satisfy:

$a \cdot a^{-1} \equiv 1 \; (mod \, m)$

We should note that the modular inverse does not always exist. For example, let $m = 4$, $a = 2$. Obviously we cannot find $a^{-1}$ satisfying the above equation. It can be proven that the modular inverse exists if and only if $a$ and $m$ are relatively prime (i.e. $gcd(a, m) = 1$).

In this article, we present two methods for finding the modular inverse in case it exists, and one method for finding all the modular inverse of all numbers in linear time.

## Finding the Modular Inverse using Extended Euclidean algorithm

Consider the following equation (with unknown $x$ and $y$):

$a \cdot x + m \cdot y = 1$

This is known as [Linear Diophantine equation of two variables](./algebra/linear-diophantine-equation.html). As shown in the linked article, when $gcd(a, m) = 1$, the equation has a solution which can be found using the [extended Euclidean algorithm](http://en.wikipedia.org/wiki/Extended_Euclidean_algorithm). Note that $gcd(a, m) = 1$ is also the condition for the Modular inverse to exist.

Now, if we take modulo $m$ of both sides, we can get rid of $m \cdot y$, and the equation becomes:

$a \cdot x \equiv 1 \; (mod \, m)$

Thus, the modular inverse of $a$ is $x$.

The implementation is as follows:

```cpp
int x, y;
int g = extended_euclidean(a, m, x, y);
if (g != 1) cout << "No solution!";
else {
    x = (x % m + m) % m;
    cout << x << endl;
}
```

## Finding the Modular Inverse using Binary exponention

Another method for finding modular inverse is to use Euler's theorem, which is as follows:

$a ^ {\phi (m)} \equiv 1 \; (mod \, m)$

which is true when $a$ and $m$ are relatively prime. (Again, note that this was also our condition for Modular inverse to exist).

If $m$ is a prime number, we have an even simpler equation from [Fermat's little theorem](http://en.wikipedia.org/wiki/Fermat's_little_theorem):

$a ^ {m - 1} \equiv 1 \; (mod \, m)$

Multiply both sides of the above equations by $a ^ {-1}$, and we get:

* For any modulo $m$: $a ^ {\phi (m) - 1} \equiv a ^{-1} \; (mod \, m)$
* For a prime modulo $m$: $a ^ {m - 2} \equiv a ^ {-1} \; (mod \, m)$

From these results, we can easily find the modular inverse using [binary exponentiation algorithm](./algebra/binary-exp.html), which works in time $O(\log m)$.

Even though this method is easier to understand than the method described in previous paragraph, in the case when $m$ is not a prime number, we need to calculate Euler phi function, which involves factorization of $m$, which might be very hard. If the prime factorization of $m$ is known, then the complexity of this method is $O(\log m)$.

## Finding all Modular Inverse of numbers in modulo $m$

In this section, we consider a special case when $m$ is a prime number, and we will describe a method that can calculate all the Modular inverse of every number in range $[1, m-1]$.

Applying the algorithms described in previous sections, we obtain a solution with complexity $O(m \log m)$. Here we present a better algorithm with complexity $O(m)$. The method is as follows: We denote by $r[i]$ the modular inverse of $i$. Then when $i > 1$, we have:

$r[i] = - \lfloor \frac{m}{i} \rfloor \cdot r[m \, mod \, i] \; (mod \, m)$

The implementation is very simple:

```cpp
r[1] = 1;
for(int i = 2; i < m; ++i)
    r[i] = (m - (m/i) * r[m%i] % m) % m;
```

### Proof

We have:

$m \, mod \, i = m -  \lfloor \frac{m}{i} \rfloor \cdot i$

Then, taking both sides modulo $m$ yield:

$m \, mod \, i = - \lfloor \frac{m}{i} \rfloor \cdot i \; (mod \, m)$

Multiply both sides by modular inverse of $i$ and then by modular inverse of $(m \, mod \, i)$ yield:

$r[i] = - \lfloor \frac{m}{i} \rfloor \cdot r[m \, mod \, i] \; (mod \, m)$


