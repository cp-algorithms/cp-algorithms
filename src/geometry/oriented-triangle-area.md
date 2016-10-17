<!--?title Oriented area of a triangle and predicate "clockwise" -->

# Oriented area of a triangle
Given three points $p_1$, $p_2$ and $p_3$, calculate an oriented (signed) area of a triangle formed by them. The sign of the area is determined in the following way: imagine you are standing in the plane at point $p_1$ and are facing $p_2$. You go to $p_2$ and if $p_3$ is to your right (then we say the three vectors turn "clockwise"), the sign of the area is positive, otherwise it is negative. If the three points are collinear, the area is zero.

Using this signed area, we can both get the regular unsigned area (as the absolute value of the signed area) and determine if the points lie clockwise or counterclockwise in their specified order (which is useful, for example, in convex hull algorithms).


## Calculation
We can use the fact that a determinant of a $2\times 2$ matrix is equal to a signed area of a parallelogram spanned by column (or row) vectors of the matrix. By dividing this area by two we get the area of a triangle that we are interested in. We will use $\vec{p_1p_2}$ and $\vec{p_2p_3}$ as the column vectors and calculate a $2\times 2$ determinant:
$$2S=\left|\begin{matrix}x_2-x_1 & x_3-x_2\\\\y_2-y_1 & y_3-y_2\end{matrix}\right|=(x_2-x_1)(y_3-y_2)-(x_3-x_2)(y_2-y_1)$$

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

## Practice Problems
* [Codechef - Chef and Polygons](https://www.codechef.com/problems/CHEFPOLY)