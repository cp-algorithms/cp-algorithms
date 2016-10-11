<!--?title Oriented area of a triangle and predicate "clockwise" -->

# Definition
We are given three points $p_1$, $p_2$ and $p_3$ and we would like to calculate an oriented (signed) area of a triangle formed by them. The sign of the area is determined like that: imagine you are standing in the plane at point $p_1$ and are facing $p_2$. You go to $p_2$ and if $p_3$ is to your right (then we say the three vectors turn "clockwise"), the sign of the area is positive. Otherwise it is negative (or the area is zero, if the three points are collinear).

Using this signed area, we can both trivially get the actual area (just take absolute value) and we can also use the sign to determine if the points lie clockwise or counterclockwise in their specified order (which is useful in convex hull algorithms for example).


## Calculation
We can use the fact that a determinant of a $2\times 2$ matrix is equal to a signed area of a parallelogram spanned by column (or row) vectors of the matrix. By dividing this area by two we obtain the area of a triangle that we are interested in. We will just use $\vec{p_1p_2}$ and $\vec{p_2p_3}$ as the column vectors and the rest is then trivial as a $2\times 2$ determinant is easy to calculate:
$$2S=\left|\begin{matrix}x2-x1 & x3-x2\\\\y2-y1 & y3-y2\end{matrix}\right|=(x2-x1)(y3-y2)-(x3-x2)(y2-y1)$$

## Implementation

	// twice the triangle's area
	int area_determinant (int x1, int y1, int x2, int y2, int x3, int y3) {
		return (x2 - x1) * (y3 - y2) - (x3 - x2) * (y2 - y1);
	}
	
	// unsigned area of the triangle
	double triangle_area (int x1, int y1, int x2, int y2, int x3, int y3) {
		return abs (area_determinant (x1, y1, x2, y2, x3, y3)) / 2.0;
	}

	// two predicates for angle orientation
	bool clockwise (int x1, int y1, int x2, int y2, int x3, int y3) {
		return area_determinant (x1, y1, x2, y2, x3, y3) < 0;
	}
	bool counter_clockwise (int x1, int y1, int x2, int y2, int x3, int y3) {
		return area_determinant (x1, y1, x2, y2, x3, y3) > 0;
	}
