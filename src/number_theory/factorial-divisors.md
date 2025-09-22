---
tags:
  - Translated
e_maxx_link: factorial_divisors
---

# Finding Power of Factorial Divisor

You are given two numbers $n$ and $k$. Find the largest power of $k$ $x$ such that $n!$ is divisible by $k^x$.

## Prime $k$ {data-toc-label="Prime k"}

Let's first consider the case of prime $k$. The explicit expression for factorial

$$n! = 1 \cdot 2 \cdot 3 \ldots (n-1) \cdot n$$

Note that every $k$-th element of the product is divisible by $k$, i.e. adds $+1$ to the answer; the number of such elements is $\Bigl\lfloor\dfrac{n}{k}\Bigr\rfloor$.

Next, every $k^2$-th element is divisible by $k^2$, i.e. adds another $+1$ to the answer (the first power of $k$ has already been counted in the previous paragraph). The number of such elements is $\Bigl\lfloor\dfrac{n}{k^2}\Bigr\rfloor$.

And so on, for every $i$ each $k^i$-th element adds another $+1$ to the answer, and there are $\Bigl\lfloor\dfrac{n}{k^i}\Bigr\rfloor$ such elements.

The final answer is

$$\Bigl\lfloor\dfrac{n}{k}\Bigr\rfloor + \Bigl\lfloor\dfrac{n}{k^2}\Bigr\rfloor + \ldots + \Bigl\lfloor\dfrac{n}{k^i}\Bigr\rfloor + \ldots$$

This result is also known as [Legendre's formula](https://en.wikipedia.org/wiki/Legendre%27s_formula).
The sum is of course finite, since only approximately the first $\log_k n$ elements are not zeros. Thus, the runtime of this algorithm is $O(\log_k n)$.

### Implementation

```cpp

int fact_pow (int n, int k) {
	int res = 0;
	while (n) {
		n /= k;
		res += n;
	}
	return res;
}

```

## Composite $k$ {data-toc-label="Composite k"}

The same idea can't be applied directly. Instead we can factor $k$, representing it as $k = k_1^{p_1} \cdot \ldots \cdot k_m^{p_m}$. For each $k_i$, we find the number of times it is present in $n!$ using the algorithm described above - let's call this value $a_i$. The answer for composite $k$ will be

$$\min_ {i=1 \ldots m} \dfrac{a_i}{p_i}$$
