<!--?title Intersection Point of Lines-->

# Intersection Point of Lines

You are given two lines, described as coefficients $A_1, B_1, C_1$ and $A_2, B_2, C_2$. Find the intersection point of the lines, or figure out that the lines are parallel.

## Solution

If two lines are not parallel, they intersect. To find their intersection point, we need to solve the following system of linear equations:

$$ \cases{ A_1 x + B_1 y + C_1 = 0, \cr
A_2 x + B_2 y + C_2 = 0. } $$

Using Cramer's rule, we immediately find the solution for the system, which will give us the required intersection point of the lines:

$$ x = - \frac{ \left|\matrix{C_1&B_1 \cr C_2&B_2}\right| }{ \left|\matrix{A_1&B_1 \cr A_2&B_2}\right| } = - \frac{ C_1 B_2 - C_2 B_1 }{ A_1 B_2 - A_2 B_1 }, $$
$$ y = - \frac{ \left|\matrix{A_1&C_1 \cr A_2&C_2}\right| }{ \left|\matrix{A_1&B_1 \cr A_2&B_2}\right| } = - \frac{ A_1 C_2 - A_2 C_1 }{ A_1 B_2 - A_2 B_1 }. $$

If the denominator equals $0$, i.e.

$$ \left|\matrix{A_1&B_1 \cr A_2&B_2}\right| = A_1 B_2 - A_2 B_1 = 0 $$

then either the system has no solutions (the lines are parallel and distinct) or there are infinitely many solutions (the lines overlap). If we need to distinguish these two cases, we have to check if coefficients $C$ are proportional with the same ratio as the coefficients $A$ and $B$. To do that we only have calculate the following determinants, and if they both equal $0$, the lines overlap:

$$ \left|\matrix{ A_1 & C_1 \cr A_2 & C_2 }\right|, \left|\matrix{ B_1 & C_1 \cr B_2 & C_2 }\right| $$

## Implementation

```cpp
struct pt {
	double x, y;
};

struct line {
	double a, b, c;
};

const double EPS = 1e-9;

double det (double a, double b, double c, double d) {
	return a * d - b * c;
}

bool intersect (line m, line n, pt & res) {
	double zn = det (m.a, m.b, n.a, n.b);
	if (abs (zn) < EPS)
		return false;
	res.x = - det (m.c, m.b, n.c, n.b) / zn;
	res.y = - det (m.a, m.c, n.a, n.c) / zn;
	return true;
}

bool parallel (line m, line n) {
	return abs (det (m.a, m.b, n.a, n.b)) < EPS;
}

bool equivalent (line m, line n) {
	return abs (det (m.a, m.b, n.a, n.b)) < EPS
		&& abs (det (m.a, m.c, n.a, n.c)) < EPS
		&& abs (det (m.b, m.c, n.b, n.c)) < EPS;
}
```
