---
tags:
  - Translated
e_maxx_link: circle_line_intersection
---

# Circle-Line Intersection

Given the coordinates of the center of a circle and its radius, and the equation of a line, you're required to find the points of intersection.

## Solution

Instead of solving the system of two equations, we will approach the problem geometrically. This way we get a more accurate solution from the point of view of numerical stability.

We assume without loss of generality that the circle is centered at the origin. If it's not, we translate it there and correct the $C$ constant in the line equation. So we have a circle centered at $(0,0)$ of radius $r$ and a line with equation $Ax+By+C=0$.

Let's start by find the point on the line which is closest to the origin $(x_0, y_0)$. First, it has to be at a distance

$$ d_0 = \frac{|C|}{\sqrt{A^2+B^2}} $$

Second, since the vector $(A, B)$ is perpendicular to the line, the coordinates of the point must be proportional to the coordinates of this vector. Since we know the distance of the point to the origin, we just need to scale the vector $(A, B)$ to this length, and we'll get:

$$\begin{align}
x_0 &= - \frac{AC}{A^2 + B^2} \\
y_0 &= - \frac{BC}{A^2 + B^2} 
\end{align}$$

The minus signs are not obvious, but they can be easily verified by substituting $x_0$ and $y_0$ in the equation of the line.

At this stage we can determine the number of intersection points, and even find the solution when there is one or zero points. Indeed, if the distance from $(x_0, y_0)$ to the origin $d_0$ is greater than the radius $r$, the answer is **zero points**. If $d_0=r$, the answer is **one point** $(x_0, y_0)$. If $d_0<r$, there are two points of intersection, and now we have to find their coordinates.

So, we know that the point $(x_0, y_0)$ is inside the circle. The two points of intersection, $(a_x, a_y)$ and $(b_x, b_y)$, must belong to the line $Ax+By+C=0$ and must be at the same distance $d$ from $(x_0, y_0)$, and this distance is easy to find:

$$ d = \sqrt{r^2 - \frac{C^2}{A^2 + B^2}} $$

Note that the vector $(-B, A)$ is collinear to the line, and thus we can find the points in question by adding and subtracting  vector $(-B,A)$, scaled to the length $d$, to the point $(x_0, y_0)$. 

Finally, the equations of the two points of intersection are:

$$\begin{align}
m &= \sqrt{\frac{d^2}{A^2 + B^2}} \\
a_x &= x_0 + B \cdot m, a_y = y_0 - A \cdot m \\
b_x &= x_0 - B \cdot m, b_y = y_0 + A \cdot m
\end{align}$$

Had we solved the original system of equations using algebraic methods, we would likely get an answer in a different form with a larger error. The geometric method described here is more graphic and more accurate.

## Implementation

As indicated at the outset, we assume that the circle is centered at the origin, and therefore the input to the program is the radius $r$ of the circle and the parameters $A$, $B$ and $C$ of the equation of the line.

```cpp
double r, a, b, c; // given as input
double x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);
if (c*c > r*r*(a*a+b*b)+EPS)
    puts ("no points");
else if (abs (c*c - r*r*(a*a+b*b)) < EPS) {
    puts ("1 point");
    cout << x0 << ' ' << y0 << '\n';
}
else {
    double d = r*r - c*c/(a*a+b*b);
    double mult = sqrt (d / (a*a+b*b));
    double ax, ay, bx, by;
    ax = x0 + b * mult;
    bx = x0 - b * mult;
    ay = y0 - a * mult;
    by = y0 + a * mult;
    puts ("2 points");
    cout << ax << ' ' << ay << '\n' << bx << ' ' << by << '\n';
}
```

## Practice Problems

- [CODECHEF: ANDOOR](https://www.codechef.com/problems/ANDOOR)
