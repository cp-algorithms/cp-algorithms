<!--?title Intersection Point of Lines-->

# Intersection Point of Lines

**Problem description.** Given two lines, represented by their coefficients $A_1, B_1, C_1$ and $A_2, B_2, C_2$. Find the intersection point of the lines, or state that the lines are parallel.

## Solution

If two lines are not parallel, then they have an intersection point. To find the intersection point, we need to solve the following system of linear equations:

$$ \cases{ A_1 x + B_1 y + C_1 = 0, \cr
A_2 x + B_2 y + C_2 = 0. } $$

Using Cramer's rule, we immediately find the solution for the system, which is also the point of intersection of the lines:

$$ x = - \frac{ \left|\matrix{C_1&B_1 \cr C_2&B_2}\right| }{ \left|\matrix{A_1&B_1 \cr A_2&B_2}\right| } = - \frac{ C_1 B_2 - C_2 B_1 }{ A_1 B_2 - A_2 B_1 }, $$
$$ y = - \frac{ \left|\matrix{A_1&C_1 \cr A_2&C_2}\right| }{ \left|\matrix{A_1&B_1 \cr A_2&B_2}\right| } = - \frac{ A_1 C_2 - A_2 C_1 }{ A_1 B_2 - A_2 B_1 }. $$

If the denominator is $0$, that is:

$$ \left|\matrix{A_1&B_1 \cr A_2&B_2}\right| = A_1 B_2 - A_2 B_1 = 0 $$

then either **(1)** the system has no solution (the lines are parallel and do not overlap) or **(2)** there are infinitely many solutions (the lines overlap). If it is required to distinguish between these two cases, we have to check if coefficients $C$ of the lines have the same proportionality as the coefficients $A$ and $B$. To do that we only have to check if the following determinants are $0$ (if so the lines overlap, otherwise they don't):

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
