<!--?title The Euclidean algorithm for finding GCD (greatest common divisor) -->

# The Euclidean algorithm for finding GCD (greatest common divisor)

Euclid's algorithm solves the following problem: Given two non-negative integers $a$ and $b$, we require the greater common divisor i.e. the largest number which is a divisor of $a$ and $b$ simultaneously. It's commonly denoted by $gcd$.

$$
gcd(a, b) = \max_ {k = 1, \ldots \infty  \ : \ k \mid a \ \& \ k \mid b} k
$$

(here the symbol "$\mid$" denotes divisibility, i.e. “$k\mid a$” means “$k$ divides $a$”)

When one of the numbers is zero, while the other is non zero, the greatest common divisor, by definition, is the second number. However, when both these numbers are zero, it is undefined(it can be an infinitely large number), but we can take it to be equal to zero. So we have a simple rule: if one of the numbers is zero, the other number is the gcd.

The Euclidean algorithm, discussed below, solves the problem of finding the greatest common divisor of two numbers $a$ and $b$ in $O(\log min(a, b))$.

The algorithm was first described in Euclid's “**Elements**” (circa 300 BC). However, it is possible that the algorithm has earlier origins.

## Algorithm

The algorithm is extremely simple and described by this formula:

$$ gcd(a, b) = \cases{a,&if $b = 0$\cr gcd(b, a \mod b),&otherwise \cr}$$

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

Finally, we present a non-recursive form of implementation of the algorithm:

```cpp
int gcd (int a, int b) {
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}
```

## The Proof of correctness

First, observe that at each successive iteration of the Euclidean algorithm, it's second argument strictly decreases, therefore, since the arguments are always non-negative, the algorithm must terminate.

For the proof of correctness, we need to show $gcd(a, b) = gcd(b, a \mod b)$ for all $a \geq 0$, $b > 0$.

We will show that the quantity on the left side of the equation, divides the quantity on it's right. Obviously, this would mean that the left and right sides are equal and prove Euclid's algorithm.

Let $d = gcd(a, b)$. Then, by definition $d\mid a$ and $d\mid b$.

New writing the remainder on dividing $a$ by $b$:

$$
a \mod b = a - b \cdot \Bigl\lfloor\dfrac{a}{b}\Bigr\rfloor\qquad
$$

But then, it follows:

$$
d \mid (a \mod b)
$$

So, remembering the statement $d \mid b$, we obtain the system:

$$
\cases{d \mid b,\cr d \mid (a \mod b)\cr}
$$

We now use the fact that if for any three numbers $p$, $q$, and $r$, if $p\mid q$ and $p\mid r$ then $p\mid gcd(q, r)$, In our case, we get:

$$
d \mid gcd(b, a \mod b)
$$

Or, by substituting $d$ by it's definition($gcd(a, b)$) we get:

$$
gcd(a, b) \mid gcd(b, a \mod b)
$$

So, we have shown that the left side divides the right. The second half of the proof is similar.

## Time complexity

The running time of the algorithm is estimated by Lame's theorem, which establishes a surprising connection between the euclidean algorithm and the Fibonacci sequence:

If $a > b \geq 1$ and $b < F_n$ for some $n$, the euclidean algorithm performs no more than $n-2$ recursive calls.

Moreover, one can show that the upper bound of this theorem is optimal. When $a = F_n$ and $b = F_{n-1}$, $gcd(a, b)$ performs $n-2$ recursive calls. In other words, consecutive fibonacci numbers are the worst case input for Euclid's algorithm.

Given that Fibonacci numbers grow exponentially(as a constant with respect to $n$), we find that the Euclidean algorithm is performed in $O(\log min(a, b))$

## LCM(Least common multiple)

Calculating least common multiple (least common multiplier or LCM) is reduced to calculating $gcd$ with the following simple statement:

$$
lcm(a, b) = \dfrac{a \cdot b}{gcd(a, b)}
$$

Thus, the calculation of the LCM can also be done using the euclidean algorithm with the same time complexity

```cpp
int lcm (int a, int b) {
	return a / gcd (a, b) * b;
}
```
(here it is advantageous to first divide $gcd$ and then multiply by $b$, as it helps avoid overflow in some cases)

## Literature

- Thomas Cormen, Charles Leiserson, Ronald Rivest, Clifford Stein. Algorithms: Construction and analysis [2005]

## Practice Problems

- [GCD and LCM[easy]](https://www.codechef.com/problems/FLOW016)
