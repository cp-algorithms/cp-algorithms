<!--?title Chinese Remainder Theorem -->

# Chinese Remainder Theorem

## Formulation

The Chinese Remainder Theorem (will be refered to as CRT in the rest of this article), is formulated as follows:

Let $p = p_1 . p_2 ... p_k$ where $p_i$ are pairwise relatively prime.

In addition to $p_i$, we are also given a set of congruence equation:

$a \equiv a_1 \; (mod \, p_1)$

$a \equiv a_2 \; (mod \, p_2)$

$...$

$a \equiv a_k \; (mod \, p_k)$

where $a_i$ are some given constants.

The original form of CRT, proven by Chinese mathematician Sun Tzu, stated that:

The given set of congruence equation always have one and exactly one solution in module $p$.

### Consequence

A consequence of CRT is that, the equation:

$x \equiv a \; (mod \, p)$

is equivalent to the system of equations:

$x \equiv a \; (mod \, p_1)$
$...$
$x \equiv a \; (mod \, p_k)$

(As above, assume that $p = p_1 . p_2 ... p_k$ and $p_i$ are pairwise relatively prime).

## Garner Algorithm

Another consequence of CRT is that we can represent big numbers by an array of small integers. For example, let $p$ be the product of the first $1000$ primes. By calculation, we can see that $p$ has around $3000$ digits. For any number $a$ which is less than $p$, we can represent it as an array $a_1, ..., a_k$ where $a_i \equiv a \; (mod \, p_i)$. But to do this, we obviously need to know how to get back the number $a$ from its representation. In this section, we discuss Garner Algorithm, which can be used for this purpose.

We will find a solution in the form:

$a = x_1 + x_2 . p_1 + x_3 . p_1 . p_2 + ... + x_k . p_1 . ... . p_{k-1}$

(This is called the mixed radix equation).

We denote by $r_{ij}$ the inverse of $p_i$ in module $p_j$, which can be found using the algorithm described in [this article](./algebra/module-inverse.html)

$r_{ij} = (p_i)^{-1} \; (mod \, p_j)$.

Substituting $a$ in the mixed radix equation, we obtain:

$a_1 \equiv x_1 \; (mod \, p_1)$.

Now substitute $x_1$ in the same equation yield:

$a_2 \equiv x_1 + x_2 . p_1 \; (mod \, p_2)$.

Taking away $x_1$ from both side, and divide by $p_1$:

$a_2 - x_1 \equiv x_2 . p_1 \; (mod \, p_2)$
$(a_2 - x_1) . r_{12} \equiv x_2 \; (mod \, p_2)$
$x_2 \equiv (a_2 - x_1) . r_{12} \; (mod \, p_2)$

Similarly,

$x_3 \equiv ((a_3 - x_1) . r_{13} - x_2) . r_{23} \; (mod \, p_3)$

Now, we can clearly see an emerging pattern, which can be expressed by the following code:

```cpp
for (int i=0; i<k; ++i) {
	x[i] = a[i];
	for (int j=0; j<i; ++j) {
		x[i] = r[j][i] * (x[i] - x[j]);
 
		x[i] = x[i] % p[i];
		if (x[i] < 0)  x[i] += p[i];
	}
}
```

So we learned how to calculate the coefficient $x_i$ in time $O(k^2)$. The number $a$ can be calculated using the mentioned formula:

$a = x_1 + x_2 . p_1 + x_3 . p_1 . p_2 + ... + x_k . p_1 . ... . p_{k-1}$

It is worth noting that in practice, we almost always need to compute the answer using Big Integers, but the coefficients $x_i$ can usually be calculated using builtin types, and therefore Garner algorithm is very effective.

## Implementation

It is most convenient to implement this algorithm using Java, because it has BigInteger class.

Below is an implementation of Garner algorithm, which supports addition, subtraction and multiplication. In this code, we took 100 prime numbers greater than $10^9$, which allows the numbers to be as large as $10^900$.

```java
final int SZ = 100;
int pr[] = new int[SZ];
int r[][] = new int[SZ][SZ];
 
void init() {
	for (int x=1000*1000*1000, i=0; i<SZ; ++x)
		if (BigInteger.valueOf(x).isProbablePrime(100))
			pr[i++] = x;
 
	for (int i=0; i<SZ; ++i)
		for (int j=i+1; j<SZ; ++j)
			r[i][j] = BigInteger.valueOf( pr[i] ).modInverse(
					BigInteger.valueOf( pr[j] ) ).intValue();
}
 
 
class Number {
 
	int a[] = new int[SZ];
 
	public Number() {
	}
 
	public Number (int n) {
		for (int i=0; i<SZ; ++i)
			a[i] = n % pr[i];
	}
 
	public Number (BigInteger n) {
		for (int i=0; i<SZ; ++i)
			a[i] = n.mod( BigInteger.valueOf( pr[i] ) ).intValue();
	}
 
	public Number add (Number n) {
		Number result = new Number();
		for (int i=0; i<SZ; ++i)
			result.a[i] = (a[i] + n.a[i]) % pr[i];
		return result;
	}
 
	public Number subtract (Number n) {
		Number result = new Number();
		for (int i=0; i<SZ; ++i)
			result.a[i] = (a[i] - n.a[i] + pr[i]) % pr[i];
		return result;
	}
 
	public Number multiply (Number n) {
		Number result = new Number();
		for (int i=0; i<SZ; ++i)
			result.a[i] = (int)( (a[i] * 1l * n.a[i]) % pr[i] );
		return result;
	}
 
	public BigInteger bigIntegerValue (boolean can_be_negative) {
		BigInteger result = BigInteger.ZERO,
			mult = BigInteger.ONE;
		int x[] = new int[SZ];
		for (int i=0; i<SZ; ++i) {
			x[i] = a[i];
			for (int j=0; j<i; ++j) {
				long cur = (x[i] - x[j]) * 1l * r[j][i];
				x[i] = (int)( (cur % pr[i] + pr[i]) % pr[i] );					
			}
			result = result.add( mult.multiply( BigInteger.valueOf( x[i] ) ) );
			mult = mult.multiply( BigInteger.valueOf( pr[i] ) );
		}
 
		if (can_be_negative)
			if (result.compareTo( mult.shiftRight(1) ) >= 0)
				result = result.subtract( mult );
 
		return result;
	}
}
```

Note on negative numbers:

* Let $p$ be the product of all primes.

* Modular scheme itself does not allow representing negative numbers. However, it can be seen that if we know that the absolute values our numbers are smaller than $p / 2$, then we know that it must be negative when the resulting number is greater than $p / 2$. The flag $can_be_negative$ in this code allows converting it to negative in this case. 

## Practice Problem:
* [Hackerrank - Number of sequences](https://www.hackerrank.com/contests/w22/challenges/number-of-sequences)
