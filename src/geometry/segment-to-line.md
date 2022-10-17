---
tags:
  - Translated
e_maxx_link: segment_to_line
---

# Finding the equation of a line for a segment

The task is: given the coordinates of the ends of a segment, construct a line passing through it.

We assume that the segment is non-degenerate, i.e. has a length greater than zero (otherwise, of course, infinitely many different lines pass through it).

### Two-dimensional case

Let the given segment be $PQ$ i.e. the known coordinates of its ends $P_x , P_y , Q_x , Q_y$ .

It is necessary to construct **the equation of a line in the plane** passing through this segment, i.e. find the coefficients $A , B , C$ in the equation of a line:

$$A x + B y + C = 0.$$

Note that for the required triples $(A, B, C)$ there are **infinitely many** solutions which describe the given segment:
you can multiply all three coefficients by an arbitrary non-zero number and get the same straight line.
Therefore, our task is to find one of these triples.

It is easy to verify (by substitution of these expressions and the coordinates of the points $P$ and $Q$ into the equation of a straight line) that the following set of coefficients fits:

$$\begin{align}
A &= P_y - Q_y, \\
B &= Q_x - P_x, \\
C &= - A P_x - B P_y.
\end{align}$$

### Integer case

An important advantage of this method of constructing a straight line is that if the coordinates of the ends were integer, then the coefficients obtained will also be **integer** . In some cases, this allows one to perform geometric operations without resorting to real numbers at all.

However, there is a small drawback: for the same straight line different triples of coefficients can be obtained.
To avoid this, but do not go away from the integer coefficients, you can apply the following technique, often called **rationing**. Find the [greatest common divisor](../algebra/euclid-algorithm.md) of numbers $| A | , | B | , | C |$ , we divide all three coefficients by it, and then we make the normalization of the sign: if $A <0$ or $A = 0, B <0$ then multiply all three coefficients by $-1$ .
As a result, we will come to the conclusion that for identical straight lines, identical triples of coefficients will be obtained, which makes it easy to check straight lines for equality.

### Real case

When working with real numbers, you should always be aware of errors.

The coefficients $A$ and $B$ will have the order of the original coordinates, the coefficient $C$ is of the order of the square of them. This may already be quite large numbers, and, for example, when we [intersect straight lines](lines-intersection.md), they will become even larger, which can lead to large rounding errors already when the coordinates of the end points are of order $10^3$.

Therefore, when working with real numbers, it is desirable to produce the so-called **normalization**, this is straightforward: namely, to make the coefficients such that $A ^ 2 + B ^ 2 = 1$ . To do this, calculate the number $Z$ :

$$Z = \sqrt{A ^ 2 + B ^ 2},$$

and divide all three coefficients $A , B , C$ by it.

Thus, the order of the coefficients $A$ and $B$ will not depend on the order of the input coordinates, and the coefficient $C$ will be of the same order as the input coordinates. In practice, this leads to a significant improvement in the accuracy of calculations.

Finally, we mention the **comparison** of straight lines - in fact, after such a normalization, for the same straight line, only two triples of coefficients can be obtained: up to multiplication by $-1$.
Accordingly, if we make an additional normalization taking into account the sign (if $A < -\varepsilon$  or $| A | < \varepsilon$, $B <- \varepsilon$ then multiply by $-1$ ), the resulting coefficients will be unique.

### Three-dimensional and multidimensional case

Already in the three-dimensional case there is **no simple equation** describing a straight line (it can be defined as the intersection of two planes, that is, a system of two equations, but this is an inconvenient method).

Consequently, in the three-dimensional and multidimensional cases we must use the **parametric method of defining a straight line** , i.e. as a point $p$ and a vector $v$ :

$$p + v t, ~~~ t \in \mathbb{R}.$$

Those. a straight line is all points that can be obtained from a point $p$ adding a vector $v$ with an arbitrary coefficient.

The **construction** of a straight line in a parametric form along the coordinates of the ends of a segment is trivial, we just take one end of the segment for the point $p$, and the vector from the first to the second end — for the vector $v$.
