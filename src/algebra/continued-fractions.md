<!--?title Continued fractions -->
# Continued fractions in competitive programming

**Continued fraction** is a representation of a real number as a specific convergent sequence of rational numbers. They are useful in competitive programming because they are easy to compute and can be efficiently used to find the best possible rational approximation of the underlying real number (among all numbers whose denominator doesn't exceed a given value).

Besides that, continued fractions are closely related to Euclidean algorithm which makes them useful in a bunch of number-theoretical problems.

## Continued fraction representation

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

!!! note "Different representations and representation length for rational numbers"

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
    Let $r_k = [a_0; a_1, \dots, a_{k-1}, a_k]$. The numbers $[a_0; a_1, \dots, a_{k-1}, t]$ for $1 \leq t \leq a_k$ are called **semiconvergents**.

!!! abstract "Definition"
    Complementary to convergents, we define the **residues** as $s_k = [a_k; a_{k+1}, a_{k+2}, \dots]$. Correspondingly, we will call an individual $s_k$ the $k$-th residue of $r$.

!!! note "Connection between residues and continued fraction representation"

    From the definitions above, $s_k \geq 1$ for $k \geq 1$.

    Let's treat $[a_0; a_1, \dots, a_k]$ as a formal algebraic expression and allow arbitrary real numbers instead of $a_i$, then, by definition,

    $$r = [a_0; a_1, \dots, a_{k-1}, s_k].$$

    In particular, $r = [s_0] = s_0$. On the other hand, we can express $s_k$ as

    $$s_k = [a_k; s_{k+1}] = a_k + \frac{1}{s_{k+1}},$$

    meaning that we can compute $a_k = \lfloor s_k \rfloor$ and $s_{k+1} = (s_k - a_k)^{-1}$ from $s_k$.

    The sequence $a_0, a_1, \dots$ is well-defined unless $s_k=a_k$ which only happens when $r$ is a rational number.

    Thus the continued fraction representation is uniquely defined for any irrational number $r$.

### Implementation

In the code snippets we will mostly assume finite continued fractions.

!!! note "Transition formulas"
    From $s_k$, the transition to $s_{k+1}$ looks like

    $$s_k =\left\lfloor s_k \right\rfloor + \frac{1}{s_{k+1}}.$$

    From this expression, the next residue $s_{k+1}$ is obtained as

    $$s_{k+1} = \left(s_k-\left\lfloor s_k\right\rfloor\right)^{-1}.$$

    For $s_k=\frac{p}{q}$ it means that

    $$
    s_{k+1} = \left(\frac{p}{q}-\left\lfloor \frac{p}{q} \right\rfloor\right)^{-1} = \frac{q}{p-q\cdot \lfloor \frac{p}{q} \rfloor} = \frac{q}{p \bmod q}.
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

## Key results

To provide some motivation for further study of continued fraction, we give some key facts now.

??? note "Recurrence"
    For the convergents $r_k = \frac{p_k}{q_k}$, the following recurrence stands, allowing their fast computation:
    
    $$\frac{p_k}{q_k}=\frac{a_k p_{k-1} + p_{k-2}}{a_k q_{k-1} + q_{k-2}},$$
    
    where $\frac{p_{-1}}{q_{-1}}=\frac{1}{0}$ and $\frac{p_{-2}}{q_{-2}}=\frac{0}{1}$.

??? note "Deviations"
    The deviation of $r_k = \frac{p_k}{q_k}$ from $r$ can be generally estimated as
    
    $$\left|\frac{p_k}{q_k}-r\right| \leq \frac{1}{q_k q_{k+1}} \leq \frac{1}{q_k^2}.$$
    
    Multiplying both sides with $q_k$, we obtain alternate estimation:
    
    $$|p_k - q_k r| \leq \frac{1}{q_{k+1}}.$$

    From the recurrence above it follows that $q_k$ grows at least as fast as Fibonacci numbers.

    On the picture below you may see the visualization of how convergents $r_k$ approach $r=\frac{1+\sqrt 5}{2}$:

    ![](https://upload.wikimedia.org/wikipedia/commons/b/b4/Golden_ration_convergents.svg)

    $r=\frac{1+\sqrt 5}{2}$ is depicted by blue dotted line. Odd convergents approach it from above and even convergents approach it from below.

??? note "Lattice hulls"
    Consider convex hulls of points above and below the line $y=rx$.
    
    Odd convergents $(q_k;p_k)$ are the vertices of the upper hull, while the even convergents $(q_k;p_k)$ are the vertices of the bottom hull.
    
    All integers vertices on the hulls are obtained as $(q;p)$ such that
    
    $$\frac{p}{q} = \frac{tp_{k-1} + p_{k-2}}{tq_{k-1} + q_{k-2}}$$
    
    for integer $0 \leq t \leq a_k$. In other words, the set of lattice points on the hulls corresponds to the set of semiconvergents.

    On the picture below, you may see the convergents and semiconvergents (intermediate gray points) of $r=\frac{9}{7}$.

    ![](https://upload.wikimedia.org/wikipedia/commons/9/92/Continued_convergents_geometry.svg)

??? note "Best approximations"
    Let $\frac{p}{q}$ be the fraction to minimize $\left|r-\frac{p}{q}\right|$ subject to $q \leq x$ for some $x$.
    
    Then $\frac{p}{q}$ is a semiconvergent of $r$.

The last fact allows to find the best rational approximations of $r$ by checking its semiconvergents.

Below you will find the further explanation and a bit of intuition and interpretation for these facts.

## Convergents

Let's take a closer look at the convergents that were defined earlier. For $r=[a_0, a_1, a_2, \dots]$, its convergents are

\begin{gather}
r_0=[a_0],\\r_1=[a_0, a_1],\\ \dots,\\ r_k=[a_0, a_1, \dots, a_k].
\end{gather}

Convergents are the core concept of continued fractions, so it is important to study their properties.

!!! note "Recurrence"
    For the number $r$, its $k$-th convergent $r_k = \frac{p_k}{q_k}$ can be computed as

    $$r_k = \frac{P_k(a_0,a_1,\dots,a_k)}{P_{k-1}(a_1,\dots,a_k)} = \frac{a_k p_{k-1} + p_{k-2}}{a_k q_{k-1} + q_{k-2}},$$

    where $P_k(a_0,\dots,a_k)$ is [the continuant](https://en.wikipedia.org/wiki/Continuant_(mathematics)), a multivariate polynomial defined as

    $$P_k(x_0,x_1,\dots,x_k) = \det \begin{bmatrix}
    x_k & 1 & 0 & \dots & 0 \\
    -1 & x_{k-1} & 1 & \dots & 0 \\
    0 & -1 & x_2 & . & \vdots \\
    \vdots & \vdots & . & \ddots & 1 \\
    0 & 0 & \dots & -1 & x_0
    \end{bmatrix}_{\textstyle .}$$

    Thus, $r_k$ is a weighted [mediant](https://en.wikipedia.org/wiki/Mediant_(mathematics)) of $r_{k-1}$ and $r_{k-2}$.

    Note that if $\gcd(a,b)=\gcd(c,d)=1$ then $\gcd(a+c,b+d)=1$ as well, hence for all convergents $r_k = \frac{p_k}{q_k}$, it holds that $\gcd(p_k, q_k)=1$.

??? hint "Detailed explanation"

    The numerator and the denominator of $r_k$ can be seen as multivariate polynomials of $a_0, a_1, \dots, a_k$:

    $$r_k = \frac{P_k(a_0, a_1, \dots, a_k)}{Q_k(a_0,a_1, \dots, a_k)}.$$

    From the definition of convergents,

    $$r_k = a_0 + \frac{1}{[a_1;a_2,\dots, a_k]}= a_0 + \frac{Q_{k-1}(a_1, \dots, a_k)}{P_{k-1}(a_1, \dots, a_k)} = \frac{a_0 P_{k-1}(a_1, \dots, a_k) + Q_{k-1}(a_1, \dots, a_k)}{P_{k-1}(a_1, \dots, a_k)}.$$

    From this follows $Q_k(a_0, \dots, a_k) = P_{k-1}(a_1, \dots, a_k)$. This yields the relation

    $$P_k(a_0, \dots, a_k) = a_0 P_{k-1}(a_1, \dots, a_k) + P_{k-2}(a_2, \dots, a_k).$$

    Initially, $r_0 = \frac{a_0}{1}$ and $r_1 = \frac{a_0 a_1 + 1}{a_1}$, thus

    $$\begin{align}P_0(a_0)&=a_0,\\ P_1(a_0, a_1) &= a_0 a_1 + 1.\end{align}$$

    For consistency, it is convenient to define $P_{-1} = 1$ and $P_{-2}=0$ and formally say that $r_{-1} = \frac{1}{0}$ and $r_{-2}=\frac{0}{1}$.

    From numerical analysis, it is known that the determinant of an arbitrary tridiagonal matrix

    $$T_k = \det \begin{bmatrix}
    a_0 & b_0 & 0 & \dots & 0 \\
    c_0 & a_1 & b_1 & \dots & 0 \\
    0 & c_1 & a_2 & . & \vdots \\
    \vdots & \vdots & . & \ddots & c_{k-1} \\
    0 & 0 & \dots & b_{k-1} & a_k
    \end{bmatrix}$$

    can be computed recursively as $T_k = a_k T_{k-1} - b_{k-1} c_{k-1} T_{k-2}$. Comparing it to $P_k$, we get a direct expression

    $$P_k = \det \begin{bmatrix}
    x_k & 1 & 0 & \dots & 0 \\
    -1 & x_{k-1} & 1 & \dots & 0 \\
    0 & -1 & x_2 & . & \vdots \\
    \vdots & \vdots & . & \ddots & 1 \\
    0 & 0 & \dots & -1 & x_0
    \end{bmatrix}_{\textstyle .}$$

    This polynomial is also known as [the continuant](https://en.wikipedia.org/wiki/Continuant_(mathematics)) due to its close relation with continued fraction. The continuant won't change if the sequence on the main diagonal is reversed. This yields an alternative formula to compute it:

    $$P_k(a_0, \dots, a_k) = a_k P_{k-1}(a_0, \dots, a_{k-1}) + P_{k-2}(a_0, \dots, a_{k-2}).$$

!!! note "Connection with the Stern-Brocot tree"
    [The Stern-Brocot tree](../others/stern_brocot_tree_farey_sequences.md) is a binary search tree that contains all the distinct positive rational numbers.

    The tree generally looks as follows:

    <figure>![](https://upload.wikimedia.org/wikipedia/commons/3/37/SternBrocotTree.svg)
    <figcaption>_[The image](https://commons.wikimedia.org/wiki/File:SternBrocotTree.svg) by [Aaron Rotenberg](https://commons.wikimedia.org/wiki/User:Aaron_Rotenberg) is licensed under [CC BY-SA 3.0](https://creativecommons.org/licenses/by-sa/3.0/deed.en)_</figcaption></figure>

    Fractions $\frac{0}{1}$ and $\frac{1}{0}$ are "virtually" kept on the left and right sides of the tree correspondingly.

    Then the fraction in a node is a mediant $\frac{a+c}{b+d}$ of two fractions $\frac{a}{b}$ and $\frac{c}{d}$ above it.

    From the $\frac{p_k}{q_k}=\frac{a_k p_{k-1} + p_{k-2}}{a_k q_{k-1} + q_{k-2}}$ recurrence we see that the continued fraction representation encodes the path to the fraction $\frac{p_k}{q_k}$ in the Stern-Brocot tree.

    To find $[a_0; a_1, \dots, a_{k}, 1]$ in a tree, one needs to move $a_0$ times to the right, $a_1$ times to the left, $a_2$ times to the right and so on, ignoring the last $1$.

    From this follows that the parent of $[a_0; a_1, \dots, a_k,1]$ is obtained by taking one step back in the last used direction.

    In other words, it is $[a_0; a_1, \dots, a_k-1,1]$ when $a_k > 1$ and $[a_0; a_1, \dots, a_{k-1}, 1]$ when $a_k = 1$.

    On the other hand, this also allows to derive that the children of $[a_0; a_1, \dots, a_k, 1]$ are $[a_0; a_1, \dots, a_k+1, 1]$ and $[a_0; a_1, \dots, a_k, 1, 1]$.

    There is an indexing of Stern-Brocot vertices that is consistent with this structure. Let's assign the root vertex an index $1$. Then for a vertex number $v$, index of its left child is obtained by changing leading bit of $v$ from $1$ to $10$ and for the right child, it's obtained by changing leading bit of $v$ from $1$ to $11$:

    <figure><img src="https://upload.wikimedia.org/wikipedia/commons/1/18/Stern-brocot-index.svg" width="500px"/></figure>

    In this indexing, the continued fraction representation of a rational number specifies the [run-length encoding](https://en.wikipedia.org/wiki/Run-length_encoding) of its binary index.

    For example, for $\frac{5}{2} = [2;2] = [2;1,1]$, its index is $1011_2$ and run-length encoding of it, if bits are considered in ascending order, is exactly $[2;1,1]$.

    Another example is $\frac{2}{5} = [0;2,2]=[0;2,1,1]$, which has index $1100_2$ and its run-length encoding is, indeed, $[0;2,2]$.

    
### Implementation

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

!!! note "Convergence rate"
    For the number $r$ and its $k$-th convergent $r_k=\frac{p_k}{q_k}$ the following formula stands:

    $$r_k = a_0 + \sum\limits_{i=1}^k \frac{(-1)^{i-1}}{q_i q_{i-1}}.$$

    In particular,

    $$r_k - r_{k-1} = \frac{(-1)^{k-1}}{q_k q_{k-1}}$$

    and

    $$\left| r-\frac{p_k}{q_k} \right| \leq \frac{1}{q_{k+1}q_k} \leq \frac{1}{q_k^2}.$$

    The latter inequality is due to the fact that $r_k$ and $r_{k+1}$ are generally located on different sides of $r$, thus

    $$|r-r_k| = |r_k-r_{k+1}|-|r-r_{k+1}| \leq |r_k - r_{k+1}|.$$

??? tip "Detailed explanation"

    To estimate $|r-r_k|$, we start by estimating the difference between adjacent convergents. By definition,

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

!!! note "Numbers as vectors"
    Let $\vec r_k = (q_k;p_k)$ for the convergent $r_k = \frac{p_k}{q_k}$. Then, the following recurrence holds:

    $$\vec r_k = a_k \vec r_{k-1} + \vec r_{k-2}.$$

    We additionally define $\vec r = (1;r)$. In these terms, each vector $(x;y)$ corresponds to the number that is equal to its slope coefficient $\frac{y}{x}$.

!!! note "Formulas for $a_k$ and $s_k$ in terms of convergents"
    With the notion of [pseudoscalar product](../geometry/basic-geometry.md) $(x_1;y_1) \times (x_2;y_2) = x_1 y_2 - x_2 y_1$, it can be shown (see the explanation below) that

    $$s_k = -\frac{\vec r_{k-2} \times \vec r}{\vec r_{k-1} \times \vec r} = \left|\frac{\vec r_{k-2} \times \vec r}{\vec r_{k-1} \times \vec r}\right|.$$

    The last equation is due to the fact that $r_{k-1}$ and $r_{k-2}$ lie on the different sides of $r$, thus pseudoscalar products of $\vec r_{k-1}$ and $\vec r_{k-2}$ with $\vec r$ have distinct signs.

    With $a_k = \lfloor s_k \rfloor$ in mind, formula for $\vec r_k$ now looks like

    $$\vec r_k = \vec r_{k-2} + \left\lfloor \left| \frac{\vec r \times \vec r_{k-2}}{\vec r \times \vec r_{k-1}}\right|\right\rfloor \vec r_{k-1}.$$

    Note that $\vec r_k \times r = (q;p) \times (1;r) = qr - p$, thus

    $$a_k = \left\lfloor \left| \frac{q_{k-1}r-p_{k-1}}{q_{k-2}r-p_{k-2}} \right| \right\rfloor.$$

??? hint "Explanation"
    As we have already noted, $a_k = \lfloor s_k \rfloor$, where $s_k = [a_k; a_{k+1}, a_{k+2}, \dots]$. On the other hand, from the convergent recurrence we derive that

    $$r = [a_0; a_1, \dots, a_{k-1}, s_k] = \frac{s_k p_{k-1} + p_{k-2}}{s_k q_{k-1} + q_{k-2}}.$$

    In vector form, it rewrites as

    $$\vec r \parallel s_k \vec r_{k-1} + \vec r_{k-2},$$

    meaning that $\vec r$ and $s_k \vec r_{k-1} + \vec r_{k-2}$ are collinear (that is, have the same slope coefficient). Taking the [pseudoscalar product](../geometry/basic-geometry.md) of both parts with $\vec r$, we get

    $$0 = s_k (\vec r_{k-1} \times \vec r) + (\vec r_{k-2} \times \vec r),$$

    which yields the final formula

    $$s_k = -\frac{\vec r_{k-2} \times \vec r}{\vec r_{k-1} \times \vec r}.$$

!!! example "Nose stretching"
    Each time you add $\vec r_{k-1}$ to the vector $\vec p$, the value of $\vec p \times \vec r$ is increased by $\vec r_{k-1} \times \vec r$.

    Thus, $a_k=\lfloor s_k \rfloor$ is the maximum integer number of $\vec r_{k-1}$ vectors that can be added to $\vec r_{k-2}$ without changing the sign of the cross product with $\vec r$.

    In other words, $a_k$ is the maximum integer number of times you can add $\vec r_{k-1}$ to $\vec r_{k-2}$ without crossing the line defined by $\vec r$:

    ![](https://upload.wikimedia.org/wikipedia/commons/9/92/Continued_convergents_geometry.svg)

    On the picture above, $\vec r_2 = (4;3)$ is obtained by repeatedly adding $\vec r_1 = (1;1)$ to $\vec r_0 = (1;0)$.

    When it is not possible to further add $\vec r_1$ to $\vec r_0$ without crossing the $y=rx$ line, we go to the other side and repeatedly add $\vec r_2$ to $\vec r_1$ to obtain $\vec r_3 = (9;7)$.

    This procedure generates exponentially longer vectors, that approach the line.

    For this property, the procedure of generating consequent convergent vectors was dubbed the **nose stretching algorithm** by Boris Delaunay.

!!! note "Klein polygons"

    If we look on the triangle drawn on points $\vec r_{k-2}$, $\vec r_{k}$ and $\vec 0$ we will notice that its doubled area is

    $$|\vec r_{k-2} \times \vec r_k| = |\vec r_{k-2} \times (\vec r_{k-2} + a_k \vec r_{k-1})| = a_k |\vec r_{k-2} \times \vec r_{k-1}| = a_k.$$

    Combined with the [Pick's theorem](../geometry/picks-theorem.md), it means that there are no lattice points strictly inside the triangle and the only lattice points on its border are $\vec 0$ and $\vec r_{k-2} + t \cdot \vec r_{k-1}$ for all integer $t$ such that $0 \leq t \leq a_k$. When joined for all possible $k$ it means that there are no integer points in the space between polygons formed by even-indexed and odd-indexed convergent vectors.

    This, in turn, means that $\vec r_k$ with odd coefficients form a convex hull of lattice points with $x \geq 0$ above the line $y=rx$, while $\vec r_k$ with even coefficients form a convex hull of lattice points with $x > 0$ below the line $y=rx$.


!!! abstract "Definition"

    These polygons are also known as **Klein polygons**, named after Felix Klein who first suggested this geometric interpretation to the continued fractions.

## Problem examples

Now that the most important facts and concepts were introduced, it is time to delve into specific problem examples.

!!! example "Convex hull under the line"
    Find the convex hull of lattice points $(x;y)$ such that $0 \leq x \leq N$ and $0 \leq y \leq rx$ for $r=[a_0;a_1,\dots,a_k]=\frac{p_k}{q_k}$.

!!! hint "Solution"
    If we were considering the unbounded set $0 \leq x$, the upper convex hull would be given by the line $y=rx$ itself.

    However, with additional constraint $x \leq N$ we'd need to eventually deviate from the line to maintain proper convex hull.

    Let $t = \lfloor \frac{N}{q_k}\rfloor$, then first $t$ lattice points on the hull after $(0;0)$ are $\alpha \cdot (q_k; p_k)$ for integer $1 \leq \alpha \leq t$.

    However $(t+1)(q_k; p_k)$ can't be next lattice point since $(t+1)q_k$ is greater than $N$.

    To get to the next lattice points in the hull, we should get to the point $(x;y)$ which diverges from $y=rx$ by the smallest margin, while maintaining $x \leq N$.

    Let $(x; y)$ be the last current point in the convex hull. Then the next point $(x'; y')$ is such that $x' \leq N$ and $(x'; y') - (x; y) = (\Delta x; \Delta y)$ is as close to the line $y=rx$ as possible. In other words, $(\Delta x; \Delta y)$ maximizes $r \Delta x - \Delta y$ subject to $\Delta x \leq N - x$ and $\Delta y \leq r \Delta x$.

    Points like that lie on the convex hull of lattice points below $y=rx$. In other words, $(\Delta x; \Delta y)$ must be a lower semiconvergent of $r$.

    That being said, $(\Delta x; \Delta y)$ is of form $(q_{i-1}; p_{i-1}) + t \cdot (q_i; p_i)$ for some odd number $i$ and $0 \leq t < a_i$.

    To find such $i$, we can traverse all possible $i$ starting from the largest one and use $t = \lfloor \frac{N-x-q_{i-1}}{q_i} \rfloor$ for $i$ such that $N-x-q_{i-1} \geq 0$.

    With $(\Delta x; \Delta y) = (q_{i-1}; p_{i-1}) + t \cdot (q_i; p_i)$, the condition $\Delta y \leq r \Delta x$ would be preserved by semiconvergent properties.

    And $t < a_i$ would hold because we already exhausted semiconvergents obtained from $i+2$, hence $x + q_{i-1} + a_i q_i = x+q_{i+1}$ is greater than $N$.

    Now that we know $(\Delta x; \Delta y)$, we may add it to $(x;y)$ for $k = \lfloor \frac{N-x}{\Delta x} \rfloor$ times before we exceed $N$, after which we would try the next semiconvergent.

    === "C++"
        ```cpp
        // returns [ah, ph, qh] such that points r[i]=(ph[i], qh[i]) constitute upper convex hull
        // of lattice points on 0 <= x <= N and 0 <= y <= r * x, where r = [a0; a1, a2, ...]
        // and there are ah[i]-1 integer points on the segment between r[i] and r[i+1]
        auto hull(auto a, int N) {
            auto [p, q] = convergents(a);
            int t = N / q.back();
            vector ah = {t};
            vector ph = {0, t*p.back()};
            vector qh = {0, t*q.back()};

            for(int i = q.size() - 1; i >= 0; i--) {
                if(i % 2) {
                    while(qh.back() + q[i - 1] <= N) {
                        t = (N - qh.back() - q[i - 1]) / q[i];
                        int dp = p[i - 1] + t * p[i];
                        int dq = q[i - 1] + t * q[i];
                        int k = (N - qh.back()) / dq;
                        ah.push_back(k);
                        ph.push_back(ph.back() + k * dp);
                        qh.push_back(qh.back() + k * dq);
                    }
                }
            }
            return make_tuple(ah, ph, qh);
        }
        ```
    === "Python"
        ```py
        # returns [ah, ph, qh] such that points r[i]=(ph[i], qh[i]) constitute upper convex hull
        # of lattice points on 0 <= x <= N and 0 <= y <= r * x, where r = [a0; a1, a2, ...]
        # and there are ah[i]-1 integer points on the segment between r[i] and r[i+1]
        def hull(a, N):
            p, q = convergents(a)
            t = N // q[-1]
            ah = [t]
            ph = [0, t*p[-1]]
            qh = [0, t*q[-1]]
            for i in reversed(range(len(q))):
                if i % 2 == 1:
                    while qh[-1] + q[i-1] <= N:
                        t = (N - qh[-1] - q[i-1]) // q[i]
                        dp = p[i-1] + t*p[i]
                        dq = q[i-1] + t*q[i]
                        k = (N - qh[-1]) // dq
                        ah.append(k)
                        ph.append(ph[-1] + k * dp)
                        qh.append(qh[-1] + k * dq)
            return ah, ph, qh
        ```

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
