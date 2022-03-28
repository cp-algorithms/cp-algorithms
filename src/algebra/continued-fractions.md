<!--?title Continued fractions -->
# Continued fractions in competitive programming

**Continued fraction** is a representation of a real number as a specific convergent sequence of rational numbers. They are useful in competitive programming because they are easy to compute and can be efficiently used to find the best possible rational approximation of the underlying real number (among all numbers whose denominator doesn't exceed a given value).

Besides that, continued fractions are closely related to Euclidean algorithm which makes them useful in a bunch of number-theoretical problems.

## Definitions

### Continued fraction representation

!!! abstract "Definition"

    Let $a_0, a_1, \dots, a_k \in \mathbb Z$ and $a_1, a_2, \dots, a_k \geq 1$. Then the expression

    $$r=a_0 + \frac{1}{a_1 + \frac{1}{\dots + \frac{1}{a_k}}},$$

    is called the **continued fraction representation** of the rational number $r$ and is denoted shortly as $r=[a_0;a_1,a_2,\dots,a_k]$.

??? example

    Let $r = \frac{5}{3}$. There are two ways to represent it as a continued fraction:

    $$
    \begin{align}
    r = [1;1,1,1] &= 1+\frac{1}{1+\frac{1}{1+\frac{1}{1}}},\\
    r = [1;1,2] &= 1+\frac{1}{1+\frac{1}{2}}.
    \end{align}
    $$

It can be proven that any rational number can be represented as a continued fraction in exactly $2$ ways:

$$r = [a_0;a_1,\dots,a_k,1] = [a_0;a_1,\dots,a_k+1].$$

Moreover, the length $k$ of such continued fraction is estimated as $k = O(\log \min(p, q))$ for $r=\frac{p}{q}$.

The reasoning behind this will be clear once we delve into the details of the continued fraction construction.

!!! abstract "Definition"

    Let $a_0,a_1,a_2, \dots$ be an integer sequence such that $a_1, a_2, \dots \geq 1$. Let $r_k = [a_0; a_1, \dots, a_k]$. Then the expression

    $$r = a_0 + \frac{1}{a_1 + \frac{1}{a_2+\dots}} = \lim\limits_{k \to \infty} r_k.$$

    is called the **continued fraction representation** of the irrational number $r$ and is denoted shortly as $r = [a_0;a_1,a_2,\dots]$.

!!! abstract "Definition"

    In the definition above, rational numbers $r_0, r_1, r_2, \dots$ are called the **convergents** of $r$.

    Correspondingly, individual $r_k = [a_0; a_1, \dots, a_k]$ is called the $k$-th **convergent** of $r$.

??? example

    Consider $r = [1; 1, 1, 1, \dots]$. It can be proven by induction that $r_k = \frac{F_{k+2}}{F_{k+1}}$, where $F_k$ is the Fibonacci sequence defined as $F_0 = 0$, $F_1 = 1$ and $F_{k} = F_{k-1} + F_{k-2}$. From the Binet's formula, it is known that

    $$r_k = \frac{\phi^{k+2} - \psi^{k+2}}{\phi^{k+1} - \psi^{k+1}},$$

    where $\phi = \frac{1+\sqrt{5}}{2} \approx 1.618$ is the golden ratio and $\psi = \frac{1-\sqrt{5}}{2} = -\frac{1}{\phi} \approx -0.618$. Thus,

    $$r = 1+\frac{1}{1+\frac{1}{1+\dots}}=\lim\limits_{k \to \infty} r_k = \phi = \frac{1+\sqrt{5}}{2}.$$

    Note that in this specific case, an alternative way to find $r$ would be to solve the equation

    $$r = 1+\frac{1}{r} \implies r^2 = r + 1. $$

!!! abstract "Definition"

    Complementary to convergents, we define the **residues** as $s_k = [a_k; a_{k+1}, a_{k+2}, \dots]$. Correspondingly, we will call an individual $s_k$ the $k$-th residue of $r$.

From the definitions above, one may conclude that $s_k \geq 1$ for $k \geq 1$. If we allow the last term in $[a_0; a_1, \dots, a_k]$ to be an arbitrary real number $s$ and treat it formally as an algebraic expression, the following equation will hold for any $k$:

$$r = [a_0; a_1, \dots, a_{k-1}, s_k],$$

in particular $r = [s_0] = s_0$. This, in turn, allows us to deduct that

$$s_k = [a_k; s_{k+1}] = a_k + \frac{1}{s_{k+1}} \implies a_k = \lfloor s_k \rfloor,$$

thus the sequence $a_0, a_1, \dots$ is uniquely defined for any irrational number $r$.

#### Implementation

In the code snippets we will mostly assume that we work with the finite continued fractions. Although continued fractions defined recursively, it is more efficient to construct them iteratively. From $s_k$, the transition looks like

$$s_k =\left\lfloor s_k \right\rfloor + \frac{1}{s_{k+1}}.$$

From this expression, the next residue $s_{k+1}$ is obtained as

$$s_{k+1} = \left(s_k-\left\lfloor s_k\right\rfloor\right)^{-1}.$$

For $s_k=\frac{p}{q}$ it means that

$$
s_{k+1} = \frac{q}{p-q\cdot \lfloor \frac{p}{q} \rfloor} = \frac{q}{p \bmod q}.
$$

Thus, computation of a continued fraction representation for $r=\frac{p}{q}$ follows the same steps as the Euclidean algorithm for $p$ and $q$.

=== "C++"
    ```cpp
    auto fraction(int p, int q) {
        vector<int> a;
        while(q) {
            a.push_back(p / q);
            tie(p, q) = make_pair(q, p % q);
        }
        return a;
    }
    ```
=== "Python"
    ```py
    def fraction(p, q):
        a = []
        while q:
            a.append(p // q)
            p, q = q, p % q
        return a
    ```


### Convergents

Let's take a closer look at the convergents that were defined earlier. For $r=[a_0, a_1, a_2, \dots]$, its convergents are

\begin{gather}
r_0=[a_0],\\r_1=[a_0, a_1],\\ \dots,\\ r_k=[a_0, a_1, \dots, a_k].
\end{gather}

It is important to understand how these rational numbers are constructed and how they relate with the underlying number $r$, as they're the main building blocks of everything else related to the continued fraction.

#### Key results

!!! note "Recurrence"
    For the convergents $r_k = \frac{p_k}{q_k}$, the following recurrence stands, allowing their computation:
    
    $$\frac{p_k}{q_k}=\frac{a_k p_{k-1} + p_{k-2}}{a_k q_{k-1} + q_{k-2}},$$
    
    where $\frac{p_{-1}}{q_{-1}}=\frac{1}{0}$ and $\frac{p_{-2}}{q_{-2}}=\frac{0}{1}$.

!!! note "Deviations"
    The deviation of $r_k = \frac{p_k}{q_k}$ from $r$ can be generally estimated as
    
    $$\left|\frac{p_k}{q_k}-r\right| \leq \frac{1}{q_k q_{k+1}} \leq \frac{1}{q_k^2}.$$
    
    Multiplying both sides with $q_k$, we obtain alternate estimation:
    
    $$|p_k - q_k r| \leq \frac{1}{q_{k+1}}.$$

On the picture below you may see the visualization of how convergents $r_k$ approach $r=\frac{1+\sqrt 5}{2}$:

![](https://upload.wikimedia.org/wikipedia/commons/b/b4/Golden_ration_convergents.svg)

$r=\frac{1+\sqrt 5}{2}$ is depicted by blue dotted line. Odd convergents approach it from above and even convergents approach it from below.

!!! note "Lattice hulls"
    Consider convex hulls of points above and below the line $y=rx$.
    
    Odd convergents $(q_k;p_k)$ are the vertices of the upper hull, while the even convergents $(q_k;p_k)$ are the vertices of the bottom hull.
    
    All integers vertices on the hulls are obtained as $(q;p)$ such that
    
    $$\frac{p}{q} = \frac{tp_{k-1} + p_{k-2}}{tq_{k-1} + q_{k-2}}$$
    
    for integer $0 \leq t \leq a_k$ and are called the **semi-convergents**.

On the picture below, you may see the convergents and semi-convergents (intermediate gray points) of $r=\frac{9}{7}$.

![](https://upload.wikimedia.org/wikipedia/commons/9/92/Continued_convergents_geometry.svg)

!!! note "Best approximations"
    Let $\frac{p}{q}$ be the fraction to minimize $\left|r-\frac{p}{q}\right|$ subject to $q \leq x$ for some $x$.
    
    Then $\frac{p}{q}$ is a semi-convergent of $r$.

The last fact allows to find the best rational approximations of $r$ by checking its semi-convergents.

#### Recurrent relations

The numerator and the denominator of $r_k$ are multivariate polynomials of $a_0, a_1, \dots, a_k$. These polynomials only depend on the number of variables $k$, thus it holds that

$$r_k = \frac{P_k(a_0, a_1, \dots, a_k)}{Q_k(a_0,a_1, \dots, a_k)}.$$

On the other hand,

$$r_k = a_0 + \frac{1}{[a_1,\dots, a_k]}= a_0 + \frac{Q_{k-1}(a_1, \dots, a_k)}{P_{k-1}(a_1, \dots, a_k)} = \frac{a_0 P_{k-1}(a_1, \dots, a_k) + Q_{k-1}(a_1, \dots, a_k)}{P_{k-1}(a_1, \dots, a_k)}.$$

This gives us the relation $Q_k(a_0, \dots, a_k) = P_{k-1}(a_1, \dots, a_k)$. Therefore, we can focus on the numerator polynomials, as the denominator polynomials can be derived from them. This leads us to the relation

$$P_k(a_0, \dots, a_k) = a_0 P_{k-1}(a_1, \dots, a_k) + P_{k-2}(a_2, \dots, a_k).$$

We already know that $r_0 = \frac{a_0}{1}$ and $r_1 = \frac{a_0 a_1 + 1}{a_1}$, which means that

$$\begin{align}P_0(a_0)&=a_0,\\ P_1(a_0, a_1) &= a_0 a_1 + 1.\end{align}$$

For consistency, it is convenient to define $P_{-1} = 1$ and $P_{-2}=0$, which implies starting points $r_{-1} = \frac{1}{0}$ and $r_{-2}=\frac{0}{1}$.

#### The continuant

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

This polynomial is also known as [the continuant](https://en.wikipedia.org/wiki/Continuant_(mathematics)) due to its close relation with continued fraction. Noteworthy, the determinant of such matrix won't change if the sequence on the main diagonal is reversed. This gives us an alternative formula to compute the continuant:

$$P_k(a_0, \dots, a_k) = a_k P_{k-1}(a_0, \dots, a_{k-1}) + P_{k-2}(a_0, \dots, a_{k-2}).$$

This representation is way more convenient, as it shows that $r_k = \frac{p_k}{q_k}$ can be computed as

$$r_k = \frac{a_k p_{k-1} + p_{k-2}}{a_k q_{k-1} + q_{k-2}}.$$

Thus, $r_k$ is a weighted [mediant](https://en.wikipedia.org/wiki/Mediant_(mathematics)) of $r_{k-1}$ and $r_{k-2}$.

#### Implementation

We will compute the convergents as a pair of sequences $p_{-2}, p_{-1}, p_0, p_1, \dots, p_k$ and $q_{-2}, q_{-1}, q_0, q_1, \dots, q_k$:

=== "C++"
    ```cpp
    auto convergents(vector<int> a) {
        vector<int> p = {0, 1};
        vector<int> q = {1, 0};
        for(auto it: a) {
            p.push_back(p[p.size() - 1] * it + p[p.size() - 2]);
            q.push_back(q[q.size() - 1] * it + q[q.size() - 2]);
        }
        return make_pair(p, q);
    }
    ```
=== "Python"
    ```py
    def convergents(a):
        p = [0, 1]
        q = [1, 0]
        for it in a:
            p.append(p[-1]*it + p[-2])
            q.append(q[-1]*it + q[-2])
        return p, q
    ```

## Convergence

_You can mostly skip this section if you're more interested in practical results._

Let's estimate the distance between $r_k$ and the underlying number $r$. To do this, we start by estimating the difference between adjacent convergents. By definition, it is given with the following formula:

$$\frac{p_k}{q_k} - \frac{p_{k-1}}{q_{k-1}} = \frac{p_k q_{k-1} - p_{k-1} q_k}{q_k q_{k-1}}.$$

Replacing $p_k$ and $q_k$ in the numerator with their recurrences, we get

$$\begin{align} p_k q_{k-1} - p_{k-1} q_k &= (a_k p_{k-1} + p_{k-2}) q_{k-1} - p_{k-1} (a_k q_{k-1} + q_{k-2})
\\&= p_{k-2} q_{k-1} - p_{k-1} q_{k-2},\end{align}$$

thus the numerator of $r_k - r_{k-1}$ is always the negated numerator of $r_{k-1} - r_{k-2}$. It, in turn, equals to $1$ for

$$r_1 - r_0=\left(a_0+\frac{1}{a_1}\right)-a_0=\frac{1}{a_1},$$

thus

$$r_k - r_{k-1} = \frac{(-1)^{k-1}}{q_k q_{k-1}}.$$

This yields an alternative representation of $r_k$ as a partial sum of infinite series:

$$r_k = (r_k - r_{k-1}) + \dots + (r_1 - r_0) + r_0
= a_0 + \sum\limits_{i=1}^k \frac{(-1)^{i-1}}{q_i q_{i-1}}.$$

From the recurrent relation it follows that $q_k$ monotonously increases at least as fast as Fibonacci numbers, thus

$$r = \lim\limits_{k \to \infty} r_k = a_0 + \sum\limits_{i=1}^\infty \frac{(-1)^{i-1}}{q_i q_{i-1}}$$

is always well-defined, as the underlying series always converge. Noteworthy, the residual series

$$r-r_k = \sum\limits_{i=k+1}^\infty \frac{(-1)^{i-1}}{q_i q_{i-1}}$$

has the same sign as $(-1)^k$ due to how fast $q_i q_{i-1}$ decreases. It means that even-indexed $r_k$ monotonously approach $r$ from below while odd-indexed $r_k$ monotonously approach it from above:

![](https://upload.wikimedia.org/wikipedia/commons/b/b4/Golden_ration_convergents.svg)

From this picture we can see that

$$|r-r_k| = |r_k - r_{k+1}| - |r-r_{k+1}| \leq |r_k - r_{k+1}|,$$

thus the distance between $r$ and $r_k$ is never larger than the distance between $r_k$ and $r_{k+1}$:

$$\left|r-\frac{p_k}{q_k}\right| \leq \frac{1}{q_k q_{k+1}} \leq \frac{1}{q_k^2}.$$

## Geometric interpretation

If convergents $r_0, r_1, \dots$ are treated as 2-dimensional vectors $\vec r_k=(q_k,p_k)$, the mediant formula above turns into

$$\vec r_k = a_k \vec r_{k-1} + \vec r_{k-2}.$$

To better understand the geometric meaning of $\vec r_k$ we need to look closer into the computation of $a_k$.

### Residues

As we have already noted, $a_k = \lfloor s_k \rfloor$, where $s_k = [a_k; a_{k+1}, a_{k+2}, \dots]$. We will get an explicit way to determine $a_k$ if we know how to compute $s_k$. On the other hand, if we formally substitute $s_k$ instead of $a_k$ into the expression for $k$-th convergent, we'll get

$$r = [a_0, a_1, \dots, a_{k-1}, s_k] = \frac{s_k p_{k-1} + p_{k-2}}{s_k q_{k-1} + q_{k-2}}.$$

From this, we obtain the explicit formula for $s_k$:

$$s_k = -\frac{q_{k-2} r - p_{k-2}}{q_{k-1} r - p_{k-1}} = -\frac{q_{k-2}}{q_{k-1}}\frac{r-r_{k-2}}{r-r_{k-1}},$$

or, introducing the vector $\vec r = (1, r)$ and using the notion of the pseudo-scalar product:

$$s_k = \left|\frac{\vec r_{k-2} \times \vec r}{\vec r_{k-1} \times \vec r}\right|.$$

Thus, the expression for $\vec r_k$ is given as

$$\vec r_k = \vec r_{k-2} + \left\lfloor \left| \frac{\vec r \times \vec r_{k-2}}{\vec r \times \vec r_{k-1}}\right|\right\rfloor \cdot \vec r_{k-1}.$$

Note that $\vec r_{k-1}$ and $\vec r_{k-2}$ generally lie on different sides of $\vec r$, thus $\vec r \times \vec r_{k-2}$ and $\vec r \times \vec r_{k-1}$ have different signs.

### Nose stretching

Geometrically, $a_k=\lfloor s_k \rfloor$ in the expression above is equal to the maximum integer number of $\vec r_{k-1}$ vectors that can be added to $\vec r_{k-2}$ in such a way that the resulting vector will still be on the same side from $\vec r$ as $\vec r_{k-2}$ is.

![](https://upload.wikimedia.org/wikipedia/commons/9/92/Continued_convergents_geometry.svg)

On the picture above you can see how $\vec r_2 = (4,3)$ is obtained by repeatedly adding $\vec r_1 = (1,1)$ to $\vec r_0 = (1, 0)$. When it is not possible to further add $\vec r_1$ to $\vec r_0$ without crossing the $y=rx$ line, we go to the other side and repeatedly add $\vec r_2$ to $\vec r_1$ to obtain $\vec r_3 = (9, 7)$ in a similar manner.

This procedure generates exponentially longer vectors, that approach closer and closer to $y=rx$ line, until one vector is finally collinear with it (when $r$ is rational). For this property, the procedure of generating consequent convergent vectors was dubbed the nose stretching algorithm by Boris Delaunay.

### Klein polygons

If we look on the triangle drawn on points $\vec r_{k-2}$, $\vec r_{k}$ and $\vec 0$ we will notice that its doubled area is

$$|\vec r_{k-2} \times \vec r_k| = a_k.$$

Combined with the [Pick's theorem](../geometry/picks-theorem.md), it means that there are no lattice points strictly inside the triangle and the only lattice points on its border are $\vec 0$ and $\vec r_{k-2} + t \cdot \vec r_{k-1}$ for all integer $t$ such that $0 \leq t \leq a_k$. When joined for all possible $k$ it means that there are no integer points in the space between polygons formed by even-indexed and odd-indexed convergent vectors.

This, in turn, means that $\vec r_k$ with odd coefficients form a convex hull of lattice points with $x \geq 0$ above the line $y=rx$, while $\vec r_k$ with even coefficients form a convex hull of lattice points with $x > 0$ below the line $y=rx$.


!!! abstract "Definition"

    These polygons are also known as **Klein polygons**, named after Felix Klein who first suggested this geometric interpretation to the continued fractions.


!!! abstract "Definition"

    The vectors $\vec r_{k-2} + t \cdot \vec r_{k-1}$ for $0 \leq t \leq a_k$ and corresponding fractions are called the **semi-convergents**.

Semi-convergent vectors are essentially _all_ lattice vectors on the border of their corresponding convex hulls.

## Problem examples

Now that the most important facts and concepts were introduced, it is time to delve into specific problem examples.

!!! example "[Timus - Crime and Punishment](https://acm.timus.ru/problem.aspx?space=1&num=1430)"

    You're given integer numbers $A$, $B$ and $N$. Find $x \geq 0$ and $y \geq 0$ such that $Ax + By \leq N$ and $Ax + By$ is the maximum possible.

    _Equivalent formulation:_ Given $A$, $B$, $C$ and $N$, find $x$ such that $0 \leq x \leq N$ and $\lfloor \frac{Ax+B}{C} \rfloor$ is the maximum possible.

??? hint "Solution"

    In the actual problem it holds that $1 \leq A, B, N \leq 2 \cdot 10^9$, so the problem can be solved in $O(\sqrt N)$.

    However, there is $O(\log N)$ solution with continued fractions.

    It is evident that one needs to find the maximum value of $\lfloor \frac{N-Ax}{B} \rfloor$ for $0 \leq x \leq \lfloor \frac{N}{A}\rfloor$.

    For our convenience, we will invert the direction of $x$, so that now we need to find the maximum value of $\lfloor \frac{Ax + \left(N \bmod A \right)}{B} \rfloor$ for $0 \leq x \leq \lfloor \frac{N}{A} \rfloor$.

    To treat it more generically, we will write a function that finds the maximum value of $\lfloor \frac{Ax+B}{C} \rfloor$ on $0 \leq x \leq N$:

    === "C++"
        ```cpp
        auto solve(int A, int B, int N) {
            return max_floor(A, N % A, B, N / A);
        }
        ```
    === "Python"
        ```py
        def solve(A, B, N):
            x, y = max_rem(A, N % A, B, N // A)
            return N // A - x, y
        ```

!!! example "[CodeChef - Euler Sum](https://www.codechef.com/problems/ES)"

    Compute $\sum\limits_{x=1}^N \lfloor ex \rfloor$, where $e = [2; 1, 2, 1, 1, 4, 1, 1, 6, 1, \dots, 1, 2n, 1, \dots]$ is the Euler's number and $N \leq 10^{4000}$.


!!! example "[Kattis - It's a Mod, Mod, Mod, Mod World](https://open.kattis.com/problems/itsamodmodmodmodworld)"

    Given $p$, $q$ and $n$, compute $\sum\limits_{i=1}^n [p \cdot i \bmod q]$.

The connection between $\bmod$ and $\lfloor \cdot \rfloor$ is given as $a \bmod b = a - \lfloor \frac{a}{b} \rfloor b$.

!!! example "[Library Checker - Sum of Floor of Linear](https://judge.yosupo.jp/problem/sum_of_floor_of_linear)"

    Given $N$, $M$, $A$ and $B$, compute $\sum\limits_{i=0}^{N-1} \lfloor \frac{A \cdot i + B}{M} \rfloor$.

This one is a bit more tricky. We'll discuss possible approaches to tackle it further below.
