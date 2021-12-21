<!--?title Continued fractions -->
# Continued fractions in competitive programming

**Continued fraction** is a way of representing arbitrary real number as a convergent sequence of rational numbers. What makes them important and useful in competitive programming is the fact that each consequent fraction is, in a way, the best possible approximation of the specified real number. Besides that, continued fractions are closely related to Euclidean algorithm which makes them useful in a bunch of number-theoretical problems.

## Definitions

### Continued fraction representation

Any real number $r$ may be uniquely represented as $r = a_0 + \frac{1}{q_0}$ where $a_0 = \lfloor r \rfloor$ and $q_0$ is either infinite (meaning $r$ is an integer) or is a real number greater than $1$. Expanding it indefinitely, one obtains the so-called continued fraction representation

$$r=a_0 + \frac{1}{a_1 + \frac{1}{a_2+\dots}},$$

which is shortly denoted as $r=[a_0, a_1, \dots]$.For consistency, the representation of the infinity is defined here as $\infty = [\infty, \infty, \dots]$. Therefore, rational numbers can be distinguished from irrational by the fact that their continued fraction representation always ends with a sequence of infinities. For example,

$$\frac{5}{3} = 1 + \frac{1}{1+\frac{1}{2+\frac{1}{\infty}}} = [1,1,2,\infty,\infty,\dots].$$

We will drop the infinite part of the expansion of rational numbers for shortness, thus $\frac{5}{3}=[1,1,2]$.

Note that $[1,1,1,1]$, if treated as continued fraction, would also represent $\frac 5 3$. Generally, there is a unique way to represent any irrational number and there are exactly two ways to represent any rational number, which are $[a_0, \dots, a_k]$ and $[a_0, \dots, a_k-1, 1]$. We will stick to the first one, as it is consistent with the way continued fractions were defined for irrational numbers through flooring.

#### Implementation

In the code snippets we will mostly assume that we work with the finite continued fractions. Although continued fractions defined recursively it is more efficient to construct them iteratively. If we start with $r=\frac{p}{q}$, the transition looks like

$$r =\left\lfloor \frac p q \right\rfloor + \frac{1}{\left(\frac{p}{q}-\left\lfloor \frac{p}{q}\right\rfloor\right)^{-1}}.$$

The denominator part of this expression may be rewritten as

$$\left(\frac{p}{q}-\left\lfloor \frac{p}{q}\right\rfloor\right)^{-1} = \frac{q}{p-q\cdot \lfloor \frac{p}{q} \rfloor} = \frac{q}{p \bmod q}.$$

Thus, computation of a continued fraction representation for $r=\frac{p}{q}$ follows the same steps as the Euclidean algorithm for $p$ and $q$.


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
};
```

### Convergents

Now that both finite and infinite continued fraction representations are defined, let's define convergent sequence which corresponds the underlying real number. For the number $r=[a_0, a_1, a_2, \dots]$, its convergent sequence is defined as

$$r_0=[a_0],\\r_1=[a_0, a_1],\\ \dots,\\ r_k=[a_0, a_1, \dots, a_k].$$

Each individual rational number $r_k$ is called the convergent of $r$. It is important to understand how these rational numbers are constructed and how they relate with the underlying number $r$. The numerator and denominator of $r_k$ are polynomials of $a_0, a_1, \dots, a_k$. These polynomials only depend on the number of variables $k$, that is

$$r_k = \frac{P_k(a_0, a_1, \dots, a_k)}{Q_k(a_0,a_1, \dots, a_k)}.$$

On the other hand,

$$r_k = a_0 + \frac{1}{[a_1,\dots, a_k]}=\frac{a_0 P_{k-1}(a_1, \dots, a_k) + Q_{k-1}(a_1, \dots, a_k)}{P_{k-1}(a_1, \dots, a_k)}.$$

This gives us the relation $Q_k(a_0, \dots, a_k) = P_{k-1}(a_1, \dots, a_k)$. Therefore, we can focus on the numerator polynomials, as the denominator polynomials can be derived from them. This leads us to the relation

$$P_k(a_0, \dots, a_k) = a_0 P_{k-1}(a_1, \dots, a_k) + P_{k-2}(a_2, \dots, a_k).$$

We already know that $r_0 = \frac{a_0}{1}$ and $r_1 = \frac{a_0 a_1 + 1}{a_1}$, which means that

$$\begin{align}P_0(a_0)&=a_0,\\ P_1(a_0, a_1) &= a_0 a_1 + 1.\end{align}$$

For consistency, it is also convenient to define $P_{-1} = 1$ and $P_{-2}=0$, which implies starting points $r_{-1} = \frac{1}{0}$ and $r_{-2}=\frac{0}{1}$.

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
\end{bmatrix}_{\textstyle .}$$

This polynomial is also known as [the continuant](https://en.wikipedia.org/wiki/Continuant_(mathematics)) due to its close relation with continued fraction. Noteworthy, the determinant of such matrix won't change if the sequence on the main diagonal is reversed. This gives us the alternative formula to compute continuants:

$$P_k(a_0, \dots, a_k) = a_k P_{k-1}(a_0, \dots, a_{k-1}) + P_{k-2}(a_0, \dots, a_{k-2}).$$

This representation is way more convenient, as it shows that $r_k = \frac{p_k}{q_k}$ can be computed as

$$r_k = \frac{a_k p_{k-1} + p_{k-2}}{a_k q_{k-1} + q_{k-2}}.$$

Thus, $r_k$ is a weighted [mediant](https://en.wikipedia.org/wiki/Mediant_(mathematics)) of $r_{k-1}$ and $r_{k-2}$.

## Convergence

Let's estimate the distance between $r_k$ and the limit number $r$. The difference between adjacent convergents is given as

$$\frac{p_k}{q_k} - \frac{p_{k-1}}{q_{k-1}} = \frac{p_k q_{k-1} - p_{k-1} q_k}{q_k q_{k-1}}.$$

If $p_k$ and $q_k$ in the numerator are replaced with their corresponding recurrences, we get

$$\begin{align} p_k q_{k-1} - p_{k-1} q_k &= (a_k p_{k-1} + p_{k-2}) q_{k-1} - p_{k-1} (a_k q_{k-1} + q_{k-2})
\\&= p_{k-2} q_{k-1} - p_{k-1} q_{k-2},\end{align}$$

Which means that the numerator of $r_k - r_{k-1}$ is always the negated numerator of $r_{k-1} - r_{k-2}$. It's equal to $1$ for $a_1 - a_0$, thus

$$r_k - r_{k-1} = \frac{(-1)^{k-1}}{q_k q_{k-1}}.$$


This yields the alternative representation of $r_k$ as a partial sum of infinite series:

$$r_k = (r_k - r_{k-1}) + \dots + (r_1 - r_0) + r_0
= a_0 + \sum\limits_{i=1}^k \frac{(-1)^{i-1}}{q_i q_{i-1}}.$$

By definition, $q_k$ monotonically increases at least as fast as Fibonacci numbers, thus

$$r = \lim\limits_{k \to \infty} r_k = a_0 + \sum\limits_{i=1}^\infty \frac{(-1)^{i-1}}{q_i q_{i-1}}$$

is always well-defined. Noteworthy, the residual series

$$r-r_k = \sum\limits_{i=k+1}^\infty \frac{(-1)^{i-1}}{q_i q_{i-1}}$$

has the same sign as $(-1)^k$ due to how fast $q_i q_{i-1}$ decreases. It means that even-indexed $r_k$ monotonously approach $r$ from below while odd-indexed $r_k$ monotonously approach it from above:

<center>
![Convergence towards underlying number](https://codeforces.com/predownloaded/ca/8d/ca8d8835864ccccea90e458e3d8fa840a6143c13.gif)
</center>

From this picture we can see that, in fact, distance between $r$ and $r_k$ is never larger than the distance between $r_k$ and $r_{k+1}$, therefore

$$\left|r-\frac{p_k}{q_k}\right| \leq \frac{1}{q_k q_{k+1}} \leq \frac{1}{q_k^2}.$$

## Geometric interpretation

If convergents $r_0, r_1, \dots$ are treated as 2-dimensional vectors $\vec r_k=(q_k;p_k)$, the mediant formula above turns into

$$\vec r_k = a_k \vec r_{k-1} + \vec r_{k-2}.$$

To better understand geometric meaning of $\vec r_k$ we need to look closer into computation of $a_k$. Previously we investigated _convergents_ $r_k = [a_0, a_1, \dots, a_k]$. Let's now look on _residuals_ $s_k = [a_{k}, a_{k+1}, \dots]$. From their definition it holds that

$$s_k = a_{k} + \frac{1}{s_{k+1}}.$$

Starting with $s_0=r$, it is possible to derive similar recurrent formulas for $s_k=\frac{b_k}{c_k}$:

$$\frac{b_k}{c_k}=a_k + \frac{c_{k+1}}{b_{k+1}}.$$

Thus, $b_{k+1}=c_k$ and $c_{k+1} = b_k - c_k a_k = c_{k-1} - c_k a_k$. This expression looks very similar to the recurrence for $p_k$ and from the starting points $s_0=\frac{r}{1}$ and $s_1 = \frac{1}{r-a_0}$ we may derive the explicit continuant formula for $c_k$:

$$c_k = P_{k-1}(r-a_0, -a_1, \dots, -a_{k-1}).$$

Taking into consideration the continuant properties (which follow from its determinant definition)

$$\begin{align}
P_k(a_0, \dots, a_k) &= (-1)^{k+1} P_k(-a_0, \dots, -a_k),\\
P_k(a_0, \dots, a_k) &= a_0 P_{k-1}(a_1, \dots, a_k) + P_{k-2}(a_2, \dots, a_k),
\end{align}$$

we may rearrange the expression for $c_k$ in a much simpler manner:

$$c_k = (-1)^{k-1} (r q_{k-1} - p_{k-1}).$$

This gives us the final formula to calculate residual $s_k$ from convergents:

$$s_k = \left|\frac{rq_{k-2} - p_{k-2}}{rq_{k-1} - p_{k-1}}\right| = \frac{q_{k-2}}{q_{k-1}}\left|\frac{r - r_{k-2}}{r - r_{k-1}}\right|.$$

On the other hand, $a_k$ may be defined as $a_k = \lfloor s_k \rfloor$, thus we have more explicit expression for $a_k$ as well. But what is its geometric meaning in terms of $\vec r_{k-1}$ and $\vec r_{k-2}$?


### Nose stretching

From convergence section we know that the number $r$ always lies between numbers $r_{k-1}$ and $r_{k-2}$. For $\vec r_{k-1}$ and $\vec r_{k-2}$ it means that they are always on the opposite sides of the vector $\vec r = (1;r)$. This is due to $r_{k-1}=\frac{p_{k-1}}{q_{k-1}}$ and $r_{k-2}=\frac{p_{k-2}}{q_{k-2}}$ being slope coefficients of $\vec r_{k-1}$ and $\vec r_{k-2}$ correspondingly, while slope coefficient of $\vec r$ is exactly $r$.

Geometrically, $r q_{k-1} - p_{k-1}$ is equal to $\vec r_{k-1} \times \vec r$, that is, the cross product of $\vec r_{k-1}$ and $\vec r$. Thus, the explicit $\vec r$ formula is

$$\vec r = \vec r_{k-2} + \left \lfloor \left|\frac{\vec r_{k-2} \times \vec r}{\vec r_{k-1} \times \vec r} \right|\right \rfloor \cdot \vec r_{k-1}.$$

Geometrically, $a_k$ here is equal to the maximum integer number of $\vec r_{k-1}$ vectors that can be added to $\vec r_{k-2}$ in such a way that the resulting vector will still be on the same side from $\vec r$ as $\vec r_{k-2}$ is.

Noteworthy, $|\vec r_k \times \vec r_{k-1}| = |q_k p_{k-1} - q_{k-1} p_k| = 1$, as was established above. Combined with [Pick's theorem](https://cp-algorithms.com/geometry/picks-theorem.html) it means that there are no points with integer coordinates strictly within the parallelogram formed by $\vec r_{k}$ and $\vec r_{k-1}$. Combined for all possible $k$ it means that there are no integer points in the space between polygons formed by even-indexed and odd-indexed convergent vectors.
