---
tags:
  - Translated
e_maxx_link: oriented_area
---

# Oriented area of a triangle

Given three points $p_1$, $p_2$ and $p_3$, calculate an oriented (signed) area of a triangle formed by them. The sign of the area is determined in the following way: imagine you are standing in the plane at point $p_1$ and are facing $p_2$. You go to $p_2$ and if $p_3$ is to your right (then we say the three vectors turn "clockwise"), the sign of the area is negative, otherwise it is positive. If the three points are collinear, the area is zero.

Using this signed area, we can both get the regular unsigned area (as the absolute value of the signed area) and determine if the points lie clockwise or counterclockwise in their specified order (which is useful, for example, in convex hull algorithms).


## Calculation
We can use the fact that a determinant of a $2\times 2$ matrix is equal to the signed area of a parallelogram spanned by column (or row) vectors of the matrix.
This is analog to the definition of the cross product in 2D (see [Basic Geometry](basic-geometry.md)).
By dividing this area by two we get the area of a triangle that we are interested in.
We will use $\vec{p_1p_2}$ and $\vec{p_2p_3}$ as the column vectors and calculate a $2\times 2$ determinant:

$$2S=\left|\begin{matrix}x_2-x_1 & x_3-x_2\\y_2-y_1 & y_3-y_2\end{matrix}\right|=(x_2-x_1)(y_3-y_2)-(x_3-x_2)(y_2-y_1)$$

## Implementation

```cpp
int signed_area_parallelogram(point2d p1, point2d p2, point2d p3) {
    return cross(p2 - p1, p3 - p2);
}

double triangle_area(point2d p1, point2d p2, point2d p3) {
    return abs(signed_area_parallelogram(p1, p2, p3)) / 2.0;
}

bool clockwise(point2d p1, point2d p2, point2d p3) {
    return signed_area_parallelogram(p1, p2, p3) < 0;
}

bool counter_clockwise(point2d p1, point2d p2, point2d p3) {
    return signed_area_parallelogram(p1, p2, p3) > 0;
}
```

## Practice Problems
* [Codechef - Chef and Polygons](https://www.codechef.com/problems/CHEFPOLY)
