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

## Operations

### Multiplication

The very core operation is the multiplication of two polynomials, that is, given polynomial $A$ and $B$: 
$$A = a_0 + a_1 x + \dots + a_n x^n$$
$$B = b_0 + b_1 x + \dots + b_m x^m$$ 
You have to compute polynomial $C = A \cdot B$: $$C = \sum\limits_{i=0}^n \sum\limits_{j=0}^m a_i b_j x^{i+j}  = c_0 + c_1 x + \dots + c_{n+m} x^{n+m}$$
It may be computed in $O(n \log n)$ via fast Fourier transform and almost all methods here will use it as subroutine.

Now let's assume that we implemented some class `polynomial` which supports basic operations: `+`, `-` and `*`.

### Calculating inverse series

If $A(0) \neq 0$ it is always possible for us to consider series $A^{-1}(x)$ such that $A^{-1} A = 1$. Unfortunately it's not a polynomial if $\deg A > 0$ but rather infinite series of form $A^{-1} = \sum\limits_{i=0}^\infty a_i'x^i$. It may be reasonable for us to calculate first $k$ coefficients of $A^{-1}$, that is, $A^{-1} \pmod{x^k}$. It may be done step by step by doubling the number of known coefficients:

1. Let's say that $A^{-1} \equiv B_k \pmod{x^{a}}$. That means that $A B_k \equiv 1 \pmod {x^{a}}$.
2. We will have to find $B_{k+1} \equiv B_k + x^{a}C \pmod{x^{2a}}$ such that $A B_{k+1} \equiv 1 \pmod{x^{2a}}$: $$A(B_k + x^{a}C) \equiv 1 \pmod{x^{2a}}$$
3. Note that since $A B_k \equiv 1 \pmod{x^{a}}$ it also holds that $A B_k \equiv 1 + x^a D \pmod{x^{2a}}$. Thus: $$x^a(D+AC) \equiv 0 \pmod{x^{2a}} \implies D \equiv -AC \pmod{x^a} \implies C \equiv -B_k D \pmod{x^a}$$
4. From this we obtain that:
$$x^a C \equiv -B_k x^a D  \equiv B_k(1-AB_k) \pmod{x^{2a}} \implies B_{k+1} \equiv B_k(2-AB_k) \pmod{x^{2a}}$$


### Newton's method

Let's generalize previous approach a bit. Assume you want to find $P(x)$ such that $F(P) = 0$ where $F$ is some given function which in turn may be written as $F(x) = \sum\limits_{i=0}^\infty f_i x^i$. 
