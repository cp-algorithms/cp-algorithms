<!--?title Continued fractions -->
# Continued fractions in competitive programming

**Continued fraction** is a way of representing arbitrary real number as a convergent sequence of rational numbers. What makes them important and useful in competitive programming is the fact that each consequent fraction is, in a way, the best possible approximation of the specified real number. Besides that, continued fractions are closely related to euclidean algorithm which makes them useful in a bunch of number-theoretical problems.

## Definitions

### Continued fractions representation

Any real number $r$ may be uniquely represented as $r = a_0 + \frac{1}{q_0}$ where $a_0 = \lfloor r \rfloor$ and $q_0$ is either infinite (meaning $r$ is an integer) or is a real number greater than $1$. Expanding it indefinitely, one obtains an infinite representation

$$r=a_0 + \frac{1}{a_1 + \frac{1}{a_2+\dots}}$$

Which is shortly denoted as $r=[a_0, a_1, \dots]$. For consistency, we will define infinity representation as $\infty = [\infty, \infty, \dots]$ and, therefore, rational numbers can be distinguished from irrational by the fact that their continued fraction representation always ends with a sequence of infinities. For example,

$$\frac{5}{3} = 1 + \frac{1}{1+\frac{1}{2+\frac{1}{\infty}}} = [1,1,2,\infty,\infty,\dots]$$

For shortness we will drop the infinite part in the expansion of rational numbers, thus $\frac{5}{3}=[1,1,2]$. Note that $[1,1,1,1]$ would represent the same rational number, but it can not be obtained through floor operation.

Generally, it can be proven that there is unique way to represent any irrational number as continued fraction and there are exactly two ways to represent any rational number, which are $[a_0, \dots, a_k]$ and $[a_0, \dots, a_k-1, 1]$. We will almost always stick to the first one, as it is consistent with the floor-defined fractions.

#### Implementation

In the code snippets we will mostly assume that we work with the finite continued fractions. Although they're defined recursively it will prove more useful to construct them iteratively. If we start with $r=\frac{p}{q}$, the transition looks like

$$r =\left\lfloor \frac p q \right\rfloor + \frac{1}{\left(\frac{p}{q}-\left\lfloor \frac{p}{q}\right\rfloor\right)^{-1}}$$

On the other hand, the denominator may be rewritten as

$$\frac{p}{q}-\left\lfloor \frac{p}{q}\right\rfloor = \frac{p-q\cdot \lfloor \frac{p}{q} \rfloor}{q} = \frac{p \bmod q}{q}$$

Therefore, computation of a continued fraction representation for $r=\frac{p}{q}$ follows the same steps the Euclid algorithm for $p$ and $q$ does.


```cpp
struct fraction {
    vector<int> a;
    
    fraction():a{0}{}
    
    // Assuming 0 <= p and 0 < q
    fraction(int p, int q) {
        while(q) {
            a.push_back(p / q);
            p %= q;
            swap(p, q);
        }
    }
}
```

### Convergents

Now that we defined both finite and infinite continued fraction representations, let's define convergent sequence which corresponds to real numbers. For the number $r=[a_0, a_1, a_2, \dots]$, its convergent sequence is defined as

$$r_0=[a_0],\\r_1=[a_0, a_1],\\ \dots,\\ r_k=[a_0, a_1, \dots, a_k].$$

It is very important to understand how these rational numbers are constructed and how do they relate with the underlying number $r$. For now, it is clear that the numerator and denominator of $r_k$ are polynomials of $a_0, a_1, \dots, a_k$. Moreover, this polynomials only depend on the number of variables $k$, that is

$$r_k = \frac{P_k(a_0, a_1, \dots, a_k)}{Q_k(a_0,a_1, \dots, a_k)}$$

On the other hand, it is clear that

$$r_k = a_0 + \frac{1}{[a_1,\dots, a_k]}=\frac{a_0 P_{k-1}(a_1, \dots, a_k) + Q_{k-1}(a_1, \dots, a_k)}{P_{k-1}(a_1, \dots, a_k)}$$

This gives us the relationship $Q_k(a_0, \dots, a_k) = P_{k-1}(a_1, \dots, a_k)$. Therefore, we can focus on the numerator polynomials, as the denominator polynomials can be derived from them. This leads us to the relationship

$$P_k(a_0, \dots, a_k) = a_0 P_{k-1}(a_1, \dots, a_k) + P_{k-2}(a_2, \dots, a_k)$$

We already know that $r_0 = \frac{a_0}{1}$ and $r_1 = \frac{a_0 a_1 + 1}{a_1}$, which means that

$$P_0(a_0)=a_0,\\ P_1(a_0, a_1) = a_0 a_1 + 1$$

For consistency with this rule it is also convenient to define $P_{-1} = 1$ and $P_{-2}=0$, which also implies implicit starting point $r_{-1} = \frac{1}{0}$.

#### Continuant

It is a well-known fact in numerical analysis that the determinant of an arbitrary tridiagonal matrix

$$T_k = \det \begin{bmatrix}
a_0 & b_0 & 0 & \dots & 0 \\
c_0 & a_1 & b_1 & \dots & 0 \\
0 & c_1 & a_2 & . & \vdots \\
\vdots & \vdots & . & \ddots & c_{k-1} \\
0 & 0 & \dots & b_{k-1} & a_k
\end{bmatrix}$$

can be computed recursively as $T_k = a_k T_{k-1} - b_{k-1} c_{k-1} T_{k-2}$. Applying this result to $P_k$ yields a direct expression

$$P_k = \det \begin{bmatrix}
x_k & 1 & 0 & \dots & 0 \\
-1 & x_{k-1} & 1 & \dots & 0 \\
0 & -1 & x_2 & . & \vdots \\
\vdots & \vdots & . & \ddots & 1 \\
0 & 0 & \dots & -1 & x_0
\end{bmatrix}$$

This polynomial is also known as [the continuant](https://en.wikipedia.org/wiki/Continuant_(mathematics)) due to its close relation with continued fraction. The determinant representation also immediately gives us the alternative formula for computing continuants as

$$P_k(a_0, \dots, a_k) = a_k P_{k-1}(a_0, \dots, a_{k-1}) + P_{k-2}(a_0, \dots, a_{k-2})$$

This formula is of extreme convenience to us, because it shows that the $r_k = \frac{p_k}{q_k}$, in fact, can be computed as

$$\frac{p_k}{q_k} = \frac{a_k p_{k-1} + p_{k-2}}{a_k q_{k-1} + q_{k-2}}$$

Meaning that $r_k$ is a weighted [mediant](https://en.wikipedia.org/wiki/Mediant_(mathematics)) of $r_{k-1}$ and $r_{k-2}$.
