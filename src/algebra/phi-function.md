<!--?title Euler's Totient Function-->
#Euler's Totient Function

Also known as $\phi (n)$ i.e. **phi-function** it is just a count of coprimes (numbers,
having greatest common divisor of `1`) with $n$ and not exceeding $n$ itself.
Here $1$ is regarded as a coprime to any number.

$\phi (n) =$ the number of positive integers less than $n$ that are relatively prime to $n$
where $n >=1$.

For example, $4$ has two such coprimes - $1$ and $3$. Any prime, $n$ (like $7$) obviously have
$n - 1$ such coprimes.

Here are values of $\phi(n)$ for first few positive integers:

    N        1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22
    
    Phi(N)   1   1   2   2   4   2   6   4   6   4  10   4  12   6   8   8  16   6  18   8  12  10

###Properties

The following properties of Euler Totient Function are enough to calculate it for any number.

* If $p$ is a prime number, $\phi (p) = p - 1$ as $gcd(p, q) = 1$ where $1 <= q < p$.
* If $p$ is a prime number and $k > 0$, $\phi (p^k) = p^k - p^{(k - 1)}$
* If $a$ and $b$ are relatively prime, $\phi (ab) = \phi (a) . \phi (b)$

We can get easily Euler function for any $n$ through factorization ( decomposing $n$ into its prime factors ).  
If  
>$n = {P_{1}}^{a_{1}} \cdot {P_{2}}^{a_{2}} \cdot {P_{3}}^{a_{3}} \cdot \ldots \cdot {P_{k}}^{a_{k}}$
where $P_{i}$ are prime factors of $n$.  

>$\phi (n) = \phi ({P_{1}}^{a_{1}}) \cdot \phi ({P_{2}}^{a_{2}}) \cdot  \ldots  \cdot \phi ({P_{k}}^{a_{k}})$  
$= ({P_{1}}^{a_{1}} - {P_{1}}^{a_{1} - 1}) \cdot ({P_{2}}^{a_{2}} - {P_{2}}^{a_{2} - 1}) \cdot \ldots \cdot ({P_{k}}^{a_{k}} - {P_{k}}^{a_{k} - 1})$  
$= n \cdot (1 - \frac{1}{P_{1}}) \cdot (1 - \frac{1}{P_{2}}) \cdot \ldots \cdot (1 - \frac{1}{P_{k}})$

###Algorithm

Here is the code for generating `phi(n)`:

`C++` implementation <span class="toggle-code">Show/Hide</span>

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

###Applications of Euler's function

The most famous and important property of Euler's function is expressed in **Euler's theorem** :  
$a^{\phi (m)} = 1 (mod$ $m)$ $where$ $a$ and $m$ are relatively prime.

In the particular case when, $m$ is a prime Euler's theorem turns into the so-called **Fermat's little theorem** :  
$a^{(m - 1)} \equiv 1 \pmod m$   
Euler's theorem occurs quite often in practical applications

## Practice Problems  

* [SPOJ #4141 [Euler Totient Function] [Difficulty: CakeWalk]](http://www.spoj.com/problems/ETF/)  
* [UVA #10179 "Irreducible Basic Fractions" [Difficulty: Easy]](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1120)
* [UVA #10299 "Relatives" [Difficulty: Easy]](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1240)
* [UVA #11327 "Enumerating Rational Numbers" [Difficulty: Medium]](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2302)
* [TIMUS #1673 "tolerance for the exam" [Difficulty: High]](http://acm.timus.ru/problem.aspx?space=1&num=1673)

**We will add more practice problems soon**
