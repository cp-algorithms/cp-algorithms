<!--?title Operations on polynomials and series -->

# Operations on polynomials and series

In this article we will cover common operations that you will probably have to do if you deal with polynomials.

## Basic Notion and Facts

Consider polynomial $A(x) = a_0 + a_1 x + \dots + a_n x^n$ such that $a_n \neq 0$. 

- For simplicity we will write $A$ instead of $A(x)$ wherever possible which would be understandable from the context.
- We will define the degree of polynomial $A$ as $\deg A = n$. It is convenient to say that $\deg A = -\infty$ for $A(x) = 0$. 
- For arbitrary polynomials $A$ and $B$ it holds that $\deg AB = \deg A + \deg B$. 
- Polynomials form euclidean ring which means that for any polynomials $A$ and $B \neq 0$ we may uniquely represent $A$ as: $$A = D \cdot B + R, \deg R < \deg B$$ Here $R$ is called remainder of $A$ modulo $B$ and $D$ is called quotient.
- If $A$ and $B$ have same remainder modulo $C$, they're said to be equivalent modulo $C$ which is denoted as: $$A \equiv B \pmod{C}$$
- For any linear polynomial $x-r$ it holds that: $$A(x) \equiv A(r) \pmod{x-r}$$
- In particular: $$A(r) = 0 \iff A(x) \equiv 0 \pmod {x-r}$$ Which means that $A$ is divisible by $x-r$ $\iff$ $A(r)=0$.
- If $A \equiv B \pmod{C \cdot D}$ then $A \equiv B \pmod{C}$
- $A \equiv a_0 + a_1 x + \dots + a_{k-1} x^{k-1} \pmod{x^k}$

## Basic implementation
[Here](https://github.com/e-maxx-eng/e-maxx-eng-aux/blob/master/src/polynomial.cpp) you may find the basic implementation of polynomial algebra. 

It supports all trivial operations and some more. Main structure is `poly<T>` for polynomials with coefficients of class `T`.

All arythmetic operation `+`, `-`, `*`, `%` and `/` are supported, `%` and `/` standing for remainder and quotient in integer division.

There is also class `modular<int m>` for arythmetics of remainders mod prime number `m`.

Other useful functions:

- `deriv()`: computes derivative $P'(x)$ of $P(x)$.
- `integr()`: computes indefinite integral $Q(x) = \int P(x)$ of $P(x)$ such that $Q(0)=0$.
- `inv(size_t n)`: calculate first $n$ coefficients of $P^{-1}(x)$.
- `log(size_t n)`: calculate first $n$ coefficients of $\ln P(x)$.
- `exp(size_t n)`: calculate first $n$ coefficients of $\exp P(x)$.
- `pow(size_t k, size_t n)`: calculate first $n$ coefficients for $P^{k}(x)$.
- `deg()`: returns degree of $P(x)$.
- `lead()`: returns coefficient near $x^{\deg P(x)}$.
- `resultant(poly<T> a, poly<T> b)`: computes resultant of $a$ and $b$.
- `bpow(T x, size_t n)`: computes $x^n$.
- `bpow(T x, size_t n, T m)`: computes $x^n \pmod{m}$.
- And some more, feel free to explore the code!

Multipoint evaluation and interpolation are not implemented here, but it's an easy task to do, given this code and formulas.
## Arythmetics

### Multiplication

The very core operation is the multiplication of two polynomials, that is, given polynomial $A$ and $B$: 
$$A = a_0 + a_1 x + \dots + a_n x^n$$
$$B = b_0 + b_1 x + \dots + b_m x^m$$ 
You have to compute polynomial $C = A \cdot B$: $$\boxed{C = \sum\limits_{i=0}^n \sum\limits_{j=0}^m a_i b_j x^{i+j}}  = c_0 + c_1 x + \dots + c_{n+m} x^{n+m}$$
It may be computed in $O(n \log n)$ via fast Fourier transform and almost all methods here will use it as subroutine.

### Inverse series

If $A(0) \neq 0$ there always exists infinite series $A^{-1}(x) = \sum\limits_{i=0}^\infty a_i'x^i$ such that $A^{-1} A = 1$.  

It may be reasonable for us to calculate first $k$ coefficients of $A^{-1}$:

1. Let's say that $A^{-1} \equiv B_k \pmod{x^{a}}$. That means that $A B_k \equiv 1 \pmod {x^{a}}$.
2. We will have to find $B_{k+1} \equiv B_k + x^{a}C \pmod{x^{2a}}$ such that $A B_{k+1} \equiv 1 \pmod{x^{2a}}$: $$A(B_k + x^{a}C) \equiv 1 \pmod{x^{2a}}$$
3. Note that since $A B_k \equiv 1 \pmod{x^{a}}$ it also holds that $A B_k \equiv 1 + x^a D \pmod{x^{2a}}$. Thus: $$x^a(D+AC) \equiv 0 \pmod{x^{2a}} \implies D \equiv -AC \pmod{x^a} \implies C \equiv -B_k D \pmod{x^a}$$
4. From this we obtain that:
$$x^a C \equiv -B_k x^a D  \equiv B_k(1-AB_k) \pmod{x^{2a}} \implies \boxed{B_{k+1} \equiv B_k(2-AB_k) \pmod{x^{2a}}}$$

Thus starting with $B_0 \equiv a_0^{-1} \pmod x$ we will compute the sequence $B_k$ such that $AB_k \equiv 1 \pmod{x^{2^k}}$ with complexity: $$T(n) = T(n/2) + O(n \log n) = O(n \log n)$$

### Division with remainder

Consider polynomials $A(x)$ and $B(x)$ of degrees $n$ and $m$. As it was said earlier you may rewrite $A(x)$ as:

$$A(x) = B(x) D(x) + R(x), \deg R < \deg B$$

Let $n \geq m$, then you may immediately find out that $\deg D = n - m$ and that leading $n-m+1$ coefficients of $A$ don't influence $R$.

That means that you may recover $D(x)$ from largest $n-m+1$ coefficients of $A(x)$ and $B(x)$ if you consider it as system of equations.

Formal way to do it is to consider reversed polynomials: 
$$A^R(x) = x^nA(x^{-1})= a_n + a_{n-1} x + \dots + a_0 x^n$$ $$B^R(x) = x^m B(x^{-1}) = b_m + b_{m-1} x + \dots + b_0 x^m$$ $$D^R(x) = x^{n-m}D(x^{-1}) = d_{n-m} + d_{n-m-1} x + \dots + d_0 x^{n-m}$$

In their terms you may rewrite that statement about largest $n-m+1$ coefficients as:

$$A^R(x) \equiv B^R(x) D^R(x) \pmod{x^{n-m+1}}$$

From which you may unambiguously recover all coefficients of $D(x)$:

$$\boxed{D^R(x) \equiv A^R(x) (B^R(x))^{-1} \pmod{x^{n-m+1}}}$$

From this in turn you may easily recover $R(x)$ as $R(x) = A(x) - B(x)D(x)$.

## Calculating functions of polynomial

### Newton's method
Let's generalize inverse series approach. You want to find $P(x)$ satisfying $F(P) = 0$ where $F(x)$ is some function represented as:
$$F(x) = \sum\limits_{i=0}^\infty \alpha_i (x-\beta)^k$$

Where $\beta$ is some constant. It may be proven that if we introduce new formal variable $y$, for $F(x)$ will stand:
$$F(x) = F(y) + (x-y)F'(y) + (x-y)^2 G(x,y)$$

Where $F'(x)$ is derivative formal series defined as $F'(x) = \sum\limits_{i=0}^\infty (k+1)\alpha_{i+1}(x-\beta)^k$ and $G(x, y)$ is some formal series of $x$ and $y$.

Given this we may find coefficients of the solution iteratively:

1. Assume that $F(Q_k) \equiv 0 \pmod{x^{a}}$, we want to find $Q_{k+1} \equiv Q_k + x^a C \pmod{x^{2a}}$ such that $F(Q_{k+1}) \equiv 0 \pmod{x^{2a}}$. 
2. Pasting $x = Q_{k+1}$ and $y=Q_k$ in the formula above we get: $$F(Q_{k+1}) \equiv F(Q_k) + (Q_{k+1} - Q_k) F'(Q_k) + (Q_{k+1} - Q_k)^2 G(x, y) \pmod x^{2a}$$
3. Since $Q_{k+1} - Q_k \equiv 0 \pmod{x^a}$ we may say that $(Q_{k+1} - Q_k)^2 \equiv 0 \pmod{x^{2a}}$, thus: $$0 \equiv F(Q_{k+1}) \equiv F(Q_k) + (Q_{k+1} - Q_k) F'(Q_k) \pmod{x^{2a}}$$
4. From the last formula we derive the value of $Q_{k+1}$: $$\boxed{Q_{k+1} = Q_k - \dfrac{F(Q_k)}{F'(Q_k)} \pmod{x^{2a}}}$$

Thus knowing how to invert arbitrary polynomial and how to compute $F(Q_k)$ quickly, we may find $n$ coefficients of $P$ with complexity: $$T(n) = T(n/2) + f(n)$$ Where $f(n)$ is maximum of $O(n \log n)$ needed to invert series and time needed to compute $F(Q_k)$ which is usually also $O(n \log n)$.


### Logarithm

For function $\ln P(x)$ it's known that: $$\boxed{(\ln P(x))' = \dfrac{P'(x)}{P(x)}}$$ Thus we may calculate $n$ coefficients of $\ln P(x)$ in $O(n \log n)$.


### Inverse series

Turns out, we may get a formula for $A^{-1}$ using Newton's method. For this we take equation $A=Q^{-1}$, thus: $$F(Q) = Q^{-1} - A$$ $$F'(Q) = -Q^{-2}$$ $$\boxed{Q_{k+1} \equiv Q_k(2-AQ_k) \pmod{x^{2^{k+1}}}}$$

### Exponent

Let's learn to calculate $e^{P(x)}=Q(x)$. It should hold that $\ln Q = P$, thus: $$F(Q) = \ln Q - P$$ $$F'(Q) = Q^{-1}$$ $$\boxed{Q_{k+1} \equiv Q_k(1 + P - \ln Q_k) \pmod{x^{2^{k+1}}}}$$

### $k$-th power

Now we need to calculate $P^k(x)=Q$. This may be done via following formula: 
$$Q = \exp\left[k \ln P(x)\right]$$
Note though that you may correctly calculate logarithms and exponents only if you can find some initial $Q_0$. 

To find it you should calculate the logarithm or the exponent of constant coefficient of polynomial. 

But the only reasonable way to do it is if $P(0)=1$ for $Q = \ln P$ so $Q(0)=0$ and if $P(0)=0$ for $Q = e^P$ so $Q(0)=1$. 

Thus you may use formula above only if $P(0) = 1$. Otherwise if $P(x) = \alpha x^t T(x)$ where $T(0)=1$ you may write that: 
$$\boxed{P^k(x) = \alpha^kx^{kt} \exp[k \ln T(x)]}$$
Note that you also may calculate some $k$-th root of polynomial if you may calculate $\sqrt[k]{\alpha}$, for example for $\alpha=1$.

## Evaluation and Interpolation

## GCD and Resultants

Assume you're given polynomials $A(x) = a_0 + a_1 x + \dots + a_n x^n$ and $B(x) = b_0 + b_1 x + \dots + b_m x^m$.

Let $\lambda_0, \dots, \lambda_n$ are the roots of $A(x)$ and $\mu_0, \dots, \mu_m$ are the roots of $B(x)$ counted with their multiplicities.

You want to know if $A(x)$ and $B(x)$ have any roots in common. There are two interconnected ways to do that.

### Euclidean algorithm

Well, we already have an [article](https://cp-algorithms.com/algebra/euclid-algorithm.html) about it. For arbitrary euclidean domain you may write euclidean algorithm as easy as:

```
template<typename T>
T gcd(const T &a, const T &b) {
	return b == T(0) ? a : gcd(b, a % b);
}
```

It may be proven that for polynomials $A(x)$ and $B(x)$ it will work in $O(nm)$.

### Half-GCD approach

There's also a way to compute GCD in $O(n \log^2 n)$.

### Resultant

Let's calculate the value $A(\mu_0)\dots A(\mu_m)$. It will be equal to zero if and only if some $\mu_i$ is the root of $A(x)$.

For symmetry we may also multiply it with $b_m^n$ and rewrite the whole product in the following form:
$$\boxed{\mathcal{R}(A, B) = b_m^n\prod\limits_{j=0}^m A(\mu_j) = b_m^n a_m^n \prod\limits_{i=0}^n \prod\limits_{j=0}^m (\mu_j - \lambda_i)= (-1)^{mn}a_n^m \prod\limits_{i=0}^n B(\lambda_i)}$$

The value defined above is called resultant of polynomials $A(x)$ and $B(x)$. From the definition you may find the following properties:

1. $\mathcal R(A, B) = (-1)^{nm} \mathcal R(B, A)$.
2. $\mathcal R(A, B)= a_n^m b_m^n$ when $n=0$ or $m=0$. 
3. If $b_m=1$ then $\mathcal R(A - CB, B) = \mathcal R(A, B)$ for arbitrary polynomial $C(x)$ and $n,m \geq 1$.
4. From this follows $\mathcal R(A, B) = b_m^{\deg(A) - \deg(A-CB)}\mathcal R(A - CB, B)$ for arbitrary $A(x)$, $B(x)$, $C(x)$.

Miraculously it means that resultant of two polynomials is actually always from the same ring as their coefficients!

Also these properties allow us to calculate resultant alongside euclidean algorithm, which works in $O(nm)$.


```
template<typename T>
T resultant(poly<T> a, poly<T> b) {
	if(b.is_zero()) {
		return 0;
	} else if(b.deg() == 0) {
		return bpow(b.lead(), a.deg());
	} else {
		int pw = a.deg();
		a %= b;
		pw -= a.deg();
		base mul = bpow(b.lead(), pw) * base((b.deg() & a.deg() & 1) ? -1 : 1);
		base ans = resultant(b, a);
		return ans * mul;
	}
}
```

It is also possible to recalculate resultant in $O(n \log^2 n)$ via Half-GCD algorithm, which is left to reader as an exercise. 

## Problems

[CodeChef - RNG](https://www.codechef.com/problems/RNG)

[CodeForces - Basis Change](https://codeforces.com/gym/102129/problem/D)

[CodeForces - Permutant](https://codeforces.com/gym/102129/problem/G)

[CodeForces - Medium Hadron Collider](https://codeforces.com/gym/102129/problem/C)
