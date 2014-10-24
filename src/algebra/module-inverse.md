<!--?title Module Inverse -->

# Modular Multiplicative Inverse

## Definition

Suppose we are given a positive integer $m$. Consider the integers in module $m$ (i.e. all integers from $0$ to $m-1$). Then, for some integer $a$, we can find its [Modular multiplicative inverse](http://en.wikipedia.org/wiki/Modular_multiplicative_inverse), denoted by $a ^ {-1}$, which satisfy:

$a . a^{-1} \equiv 1 \; (mod \, m)$

We should note that the modular inverse does not always exist. For example, let $m = 4$, $a = 2$. Obviously we cannot find $a^{-1}$ satisfying the above equation. It can be proven that the modular inverse exists if and only if $a$ and $m$ are relatively prime (i.e. $gcd(a, m) = 1$).

In this article, we present two methods for finding the modular inverse in case it exists, and one method for finding all the modular inverse of all numbers in linear time.

## Finding the Modular Inverse using Extended Euclidean algorithm

Consider the following equation (with unknown $x$ and $y$):

$a . x + m . y = 1$

This is known as [Linear Diophantine equation of two variables](./algebra/linear-diophantine-equation.html). As shown in the linked article, when $gcd(a, m) = 1$, the equation has a solution which can be found using the [Extended Euclidean algorithm](http://en.wikipedia.org/wiki/Extended_Euclidean_algorithm). Note that $gcd(a, m) = 1$ is also the condition for the Modular inverse to exist.

Now, if we take module $m$ of both sides, we can get rid of $m . y$, and the equation becomes:

$a . x \equiv 1 \; (mod \, m)$

Thus, the Modular inverse of $a$ is $x$.

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

Another method for finding Modular Inverse is to use Euler's theorem, which is as follows:

$a ^ {\phi (m)} \equiv 1 \; (mod \, m)$

which is true when $a$ and $m$ are relatively prime. (Again, note that this was also our condition for Modular inverse to exist).

In the case when $m$ is a prime number, we have an even simpler equation from [Fermat's little theorem](http://en.wikipedia.org/wiki/Fermat's_little_theorem):

$a ^ {m - 1} \equiv 1 \; (mod \, m)$

Multiply both sides of the above 2 equations, we have the following results:

* For any module $m$: $a ^ {\phi (m) - 1} \equiv a ^{-1} \; (mod \, m)$
* For a prime module $m$: $a ^ {m - 2} \equiv a ^ {-1} \; (mod \, m)$

From these results, we can easily find the Modular inverse using the [Binary exponential algorithm](./basic/binary-exp.html), which works in time $O(log m)$.

Even though this method is easier to understand than the method described in previous paragraph, in the case when $m$ is not a prime number, we need to calculate Euler phi function, which involves factorization of $m$, which might be very hard. If the prime factorization of $m$ is known, then the complexity of this method is $O(log m)$.

## Finding all Modular Inverse of numbers in module $m$

In this section, we consider a special case when $m$ is a prime number, and we will describe a method that can calculate all the Modular inverse of every number in range $[1, m-1]$.

Applying the algorithms described in previous sections, we obtain a solution with complexity $O(m log m)$. Here we present a better algorithm with complexity $O(m)$. The method is as follows: We denote by $r[i]$ the Modular inverse of $i$. Then when $i > 1$, we have:

$r[i] = - \lfloor \frac{m}{i} \rfloor . r[m \, mod \, i]. \; (mod \, m)$

The implementation is very simple:

```cpp
r[1] = 1;
for(int i = 2; i < m; ++i)
    r[i] = (m - (m/i) * r[m%i] % m) % m;
```

### Proof

We have:

$m \, mod \, i = m -  \lfloor \frac{m}{i} \rfloor . i$

Then, taking mod m of both sides yield:

$m \, mod \, i = - \lfloor \frac{m}{i} \rfloor . i \; (mod \, m)$

Multiply both sides by Modular inverse of i and then by Modular inverse of $(m \, mod \, i)$ yield:

$r[i] = - \lfloor \frac{m}{i} \rfloor . r[m \, mod \, i] \; (mod \, m)$


