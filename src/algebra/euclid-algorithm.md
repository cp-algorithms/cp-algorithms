<!--?title The Euclidean algorithm for finding greatest common divisor -->

# The Euclidean algorithm for finding greatest common divisor

Given two non-negative integers $a$ and $b$, find their greatest common divisor, i.e. the largest number which is a divisor of both $a$ and $b$. It's commonly denoted by $gcd$.

$$gcd(a, b) = \max_ {k = 1 \ldots \infty  \ : \ k \mid a \ \& \ k \mid b} k$$

(here the symbol "$\mid$" denotes divisibility, i.e. "$k \mid a$" means "$k$ divides $a$")

When one of the numbers is zero, while the other is non-zero, their greatest common divisor, by definition, is the second number. When both numbers are zero, their greatest common divisor is undefined (it can be any arbitrarily large number), but we can define it to be zero. So we have a simple rule: if one of the numbers is zero, the greatest common divisor is the other number.

The Euclidean algorithm, discussed below, allows to find the greatest common divisor of two numbers $a$ and $b$ in $O(\log min(a, b))$.

The algorithm was first described in Euclid's "Elements" (circa 300 BC), but it is possible that the algorithm has earlier origins.

## Algorithm

The algorithm is extremely simple:

$$gcd(a, b) = \cases{a,&if $b = 0$\cr gcd(b, a\mod b),&otherwise}$$

## Implementation

```cpp
int gcd (int a, int b) {
	if (b == 0)
		return a;
	else
		return gcd (b, a % b);
}
```

Using the ternary operator in C++, we can write a shorter implementation:

```cpp
int gcd (int a, int b) {
	return b ? gcd (b, a % b) : a;
}
```

Finally, here is a non-recursive implementation:

```cpp
int gcd (int a, int b) {
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}
```

## Correctness Proof

First, notce that at each iteration of the Euclidean algorithm the second argument strictly decreases, therefore (since the arguments are always non-negative) the algorithm will always terminate.

For the proof of correctness, we need to show that $gcd(a, b) = gcd(b, a \mod b)$ for all $a \geq 0$, $b > 0$.

We will show that the value on the left side of the equation divides the value on the right side and vice versa. Obviously, this would mean that the left and right sides are equal, which will prove Euclid's algorithm.

Let $d = gcd(a, b)$. Then by definition $d\mid a$ and $d\mid b$.

Now let's represent the remainder from dividing $a$ by $b$ as follows:

$$
a \mod b = a - b \cdot \Bigl\lfloor\dfrac{a}{b}\Bigr\rfloor
$$

But then, it follows:

$$
d \mid (a \mod b)
$$

So, recalling that $d \mid b$, we obtain the system:

$$
\cases{d \mid b,\cr d \mid (a \mod b)\cr}
$$

Now we use the fact that for any three numbers $p$, $q$, $r$, if $p\mid q$ and $p\mid r$ then $p\mid gcd(q, r)$, In our case, we get:

$$
d \mid gcd(b, a \mod b)
$$

Substituting $d$ with its definition ($gcd(a, b)$) we get:

$$
gcd(a, b) \mid gcd(b, a \mod b)
$$

Thus we have shown that the left side of the original equation divides the right. The second half of the proof is similar.

## Time Complexity

The running time of the algorithm is estimated by Lame's theorem, which establishes a surprising connection between the Euclidean algorithm and the Fibonacci sequence:

If $a > b \geq 1$ and $b < F_n$ for some $n$, the Euclidean algorithm performs at most $n-2$ recursive calls.

Moreover, it is possible to show that the upper bound of this theorem is optimal. When $a = F_n$ and $b = F_{n-1}$, $gcd(a, b)$ will perform exactly $n-2$ recursive calls. In other words, consecutive Fibonacci numbers are the worst case input for Euclid's algorithm.

Given that Fibonacci numbers grow exponentially (as a constant raised to $n$th power), we get that the Euclidean algorithm works in $O(\log min(a, b))$ multiplication operations.

## LCM (least common multiple)

Calculating least common multiple (commonly denoted LCM) is reduced to calculating $gcd$ with the following simple formula:

$$
lcm(a, b) = \dfrac{a \cdot b}{gcd(a, b)}
$$

Thus, LCM can be calculated using the Euclidean algorithm with the same time complexity:

```cpp
int lcm (int a, int b) {
	return a / gcd (a, b) * b;
}
```
(here it is advantageous to first divide by $gcd$ and then multiply by $b$ to avoid overflow in some cases)

## Literature

- Thomas Cormen, Charles Leiserson, Ronald Rivest, Clifford Stein. Algorithms: Construction and analysis [2005]

## Practice Problems

- [GCD and LCM [easy]](https://www.codechef.com/problems/FLOW016)
