<!--?title Circle-Line Intersection -->

# Circle-Line Intersection

Given the coordinates of the center of a circle and it's radius, and the equation of a line, you're required to find the points of intersection.

## Solution

Instead of solving the resulting system of two equations, we will approach the problem geometrically, and due to this we get a more accurate solution from the point of view of numerical stability.

We assume, without loss of generality, that the circle is centered at the origin. If it's not, we translate it there and correct the $C$ constant in the line equation. So we have a circle centered at $(0,0)$ of radius $r$ and a line with equation $Ax+By+C=0$.

First we find the point $(x_0, y_0)$ on the line closest to the origin, which will be at a distance:

$$ d_0 = \frac{|C|}{\sqrt{A^2+B^2}} $$

Now, since the vector $(A, B)$ is perpendicular to the line, the coordinates of the point will be proportional to the coordinates of this vector. Since we know the distance of the point to the origin, we just need to normalize and scale the vector $(A, B)$, and we get:

$$ x_0 = - \frac{AC}{A^2 + B^2} $$
$$ y_0 = - \frac{BC}{A^2 + B^2} $$

The minus sign is not obvious, but substituting $x_0$ and $y_0$ in the equation of the line it's easily verified we get zero.

From this, we can determine the number of points in the intersection, and even find the solution when there is one or none. If the distance $d_0$ of the point to the origin is greater than the radius $r$ then the answer is **zero points**, if $d_0=r$ then the answer is **one point**, namely $(x_0, y_0)$, but if $d_0<r$ there are two points of intersection and we must find their coordinates.

So, we know that the point lies inside the circle, and we will find the two points of intersection, $(a_x,a_y)$ and $(b_x, b_y)$. These two points lie at the same distance $d$ from $(x_0, y_0)$, and this distance is easy to find:

$$ d = \sqrt{r^2 - \frac{C^2}{A^2 + B^2}} $$

Now, note that the vector $(-B, A)$ is collinear to the line, and thus we can add to the point $(x_0, y_0)$ the vector $(-B,A)$ normalized to the length $d$. So the equations of the two points of intersection are:

$$ m = \sqrt{\frac{d^2}{A^2 + B^2}} $$
$$ a_x = x_0 + B m $$
$$ a_y = y_0 - A m $$
$$ b_x = x_0 - B m $$
$$ b_y = y_0 + A m $$

If we had solved the first system of equation by algebraic methods, we would likely get an answer in a different form with a larger error. Therefore, the -geometric- method described here is more visual and more accurate.

## Implementation

As indicated at the outset, we assume that one of the circles is centered at the origin, and therefore the input to the program is the radius $r$ of the circle and the parameters $A$, $B$ and $C$ of the equation of the line.

<pre><code>double r, a, b, c; // given as input
double x0 = -a\*c/(a\*a+b\*b),  y0 = -b\*c/(a\*a+b\*b);
if (c\*c > r\*r\*(a\*a+b\*b)+EPS)
    puts ("no points");
else if (abs (c\*c - r\*r\*(a\*a+b\*b)) < EPS) {
    puts ("1 point");
    cout << x0 << ' ' << y0 << '\n';
}
else {
    double d = r\*r - c\*c/(a\*a+b\*b);
    double mult = sqrt (d / (a\*a+b\*b));
    double ax,ay,bx,by;
    ax = x0 + b \* mult;
    bx = x0 - b \* mult;
    ay = y0 - a \* mult;
    by = y0 + a \* mult;
    puts ("2 points");
    cout << ax << ' ' << ay << '\n' << bx << ' ' << by << '\n';
}</code></pre>
