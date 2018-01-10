<!--?title Euler's Totient Function-->
#Euler's Totient Function

Euler's totient function, also known as **phi-function** $\phi (n)$, is the number of integers between 1 and $n$, inclusive, which are coprime to $n$. Two numbers are coprime if their greatest common divisor equals $1$ ($1$ is considered to be coprime to any number).

Here are values of $\phi(n)$ for the first few positive integers:

    N        1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21
    
    Phi(N)   1   1   2   2   4   2   6   4   6   4  10   4  12   6   8   8  16   6  18   8  12

## Properties

The following properties of Euler totient function are sufficient to calculate it for any number:

- If $p$ is a prime number, $\phi (p) = p - 1$  
  Evidently, since $\gcd(p, q) = 1$ for all $1 \le q < p$.
- If $p$ is a prime number and $k \ge 1$, $\phi (p^k) = p^k - p^{k - 1}$
- If $a$ and $b$ are relatively prime, $\phi (ab) = \phi (a) \cdot \phi (b)$.  
  This follows from [Chinese remainder theorem](../algebra/chinese-remainder-theorem.html).  
- In general for not coprime $a$ and $b$ holds $\phi(ab) = \phi(a) \cdot \phi(b) \cdot \dfrac{d}{\phi(d)}$ for $d = \gcd(a, b)$.

Thus, we can get $\phi (n)$ through factorization of $n$ (decomposition of $n$ into a product of its prime factors).  
If $n = {p_1}^{a_1} \cdot {p_2}^{a_2} \cdot \ldots \cdot {p_k}^{a_k}$, where $p_i$ are prime factors of $n$,

$$\phi (n) = \phi ({p_1}^{a_1}) \cdot \phi ({p_2}^{a_2}) \cdot  \ldots  \cdot \phi ({p_k}^{a_k})$$
$$= ({p_1}^{a_1} - {p_1}^{a_1 - 1}) \cdot ({p_2}^{a_2} - {p_2}^{a_2 - 1}) \cdot \ldots \cdot ({p_k}^{a_k} - {p_k}^{a_k - 1})$$
$$= n \cdot \left(1 - \frac{1}{p_1}\right) \cdot \left(1 - \frac{1}{p_2}\right) \cdot \ldots \cdot \left(1 - \frac{1}{p_k}\right)$$

## Implementation

`C++` implementation using factorization in $O(\sqrt{n})$ <span class="toggle-code">Show/Hide</span>

	int phi(int n) {
		int result = n;
		for(int i = 2; i * i <= n; ++i)
			if(n % i == 0) {
				while(n % i == 0)
					n /= i;
				result -= result / i;
			}
		if(n > 1)
			result -= result / n;
		return result;
	}

`Python 3` implementation <span class="toggle-code">Show/Hide</span>

    def phi(n):
	    result = n
	    i = 2
	    while i * i <= n:
		    if n % i == 0:
			    while n % i == 0:
				    n //= i
			    result -= result // i
		    i += 1
	    if n > 1:
		    result -= result // n
	    return result

## Applications of Euler's totient function

The most famous and important property of Euler's function is expressed in **Euler's theorem** :  
$a^{\phi (m)} \equiv 1 \pmod m$ if $a$ and $m$ are relatively prime.

In the particular case when $m$ is prime, Euler's theorem turns into the so-called **Fermat's little theorem** :  
$a^{m - 1} \equiv 1 \pmod m$

Euler's theorem occurs quite often in practical applications, for example, [modular multiplicative inverse](../algebra/module-inverse.html).

## General Euler's theorem

There is less known version of Euler's theorem for not coprime $x$ and $m$. That is for arbitrary $x, m$ and $n \geq \log_2 m$:

$$x^{n}\equiv x^{\varphi(m)+[n \bmod \varphi(m)]} \mod m$$

To prove this let's start with the following. Assume we want to calculate $x^n \bmod m$.
We should note that $an \bmod am = a(n \bmod m)$.
Indeed if $n = d m + r, r < m$ then $an = a d m + ar, ar < am$.
Now assume that $p_1, \dots, p_t$ are common divisors of $x$ and $m$.
Let $a=p_1^{k_1} \dots p_t^{k_t}$ be the number in which all such divisors taken with the same degree as in $m$ and $k$ is the smallest number such that $a$ divides $x^k$.
Then we can write:

$$x^n \bmod m = \left(\dfrac{x^k}{a}\right)ax^{n-k}\bmod a \left(\dfrac m a \right) = $$
$$=\dfrac{x^k}{a} a \left[x^{n-k} \bmod \left(\dfrac m a\right)\right]\bmod m = x^k\left[x^{n-k} \bmod \left(\dfrac m a\right)\right]\bmod m$$

Now we see that $x$ and $\tfrac m a$ are coprime, so if we consider powers of $x$ modulo $m$ they will have pre-period at most $k$ and its period will divide $\varphi\left(\dfrac m a\right)$.
It is easy to see that $k \leq \varphi(m)$, since $k \leq \log_2 m$ and $\varphi \geq \log_2 m$.
And we can use the period $\varphi(m)$ instead of $\varphi\left(\tfrac{m}{a}\right)$, because $\varphi(a)$ always divides $\varphi(ab)$.

This gives the desired formula:

$$ x^n \equiv x^{\varphi(m)} x^{(n - \varphi(m)) \bmod \varphi(m)} \bmod m \equiv x^{\varphi(m)+[n \bmod \varphi(m)]} \mod m$$

## Practice Problems  

* [SPOJ #4141 "Euler Totient Function" [Difficulty: CakeWalk]](http://www.spoj.com/problems/ETF/)  
* [UVA #10179 "Irreducible Basic Fractions" [Difficulty: Easy]](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1120)
* [UVA #10299 "Relatives" [Difficulty: Easy]](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1240)
* [UVA #11327 "Enumerating Rational Numbers" [Difficulty: Medium]](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2302)
* [TIMUS #1673 "Admission to Exam" [Difficulty: High]](http://acm.timus.ru/problem.aspx?space=1&num=1673)
* [UVA 10990 - Another New Function](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1931)
* [Codechef - Golu and Sweetness](https://www.codechef.com/problems/COZIE)
* [SPOJ - LCM Sum](http://www.spoj.com/problems/LCMSUM/)
* [GYM - Simple Calculationg  (F)](http://codeforces.com/gym/100975)
* [UVA 13132 - Laser Mirrors](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5043)
* [SPOJ - GCDEX](http://www.spoj.com/problems/GCDEX/)
* [UVA 12995 - Farey Sequence](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4878)
* [SPOJ - Totient in Permutation (easy)](http://www.spoj.com/problems/TIP1/)
* [LOJ - Mathematically Hard](http://lightoj.com/volume_showproblem.php?problem=1007)
* [SPOJ - Totient Extreme](http://www.spoj.com/problems/DCEPCA03/)
* [SPOJ - Playing with GCD](http://www.spoj.com/problems/NAJPWG/)
* [SPOJ - G Force](http://www.spoj.com/problems/DCEPC12G/)
* [SPOJ - Smallest Inverse Euler Totient Function](http://www.spoj.com/problems/INVPHI/)
* [Codeforces - Power Tower](http://codeforces.com/problemset/problem/906/D)
