---
tags:
  - Translated
e_maxx_link: pick_grid_theorem
---

# Pick's Theorem

A polygon without self-intersections is called lattice if all its vertices have integer coordinates in some 2D grid. Pick's theorem provides a way to compute the area of this polygon through the number of lattice points that are lying on the boundary and the number of lattice points that lie strictly inside the polygon.

## Formula

Given a certain lattice polygon with non-zero area.

We denote its area by $S$, the number of points with integer coordinates lying strictly inside the polygon by $I$ and the number of lattice points lying on polygon sides by $B$.

Then, the **Pick's formula** states:

$$S=I+\frac{B}{2}-1$$

In particular, if the values of $I$ and $B$ for a polygon are given, the area can be calculated in $O(1)$ without even knowing the vertices.

This formula was discovered and proven by Austrian mathematician Georg Alexander Pick in 1899.

## Proof

The proof is carried out in many stages: from simple polygons to arbitrary ones:

- A unit square: $S=1, I=0, B=4$, which satisfies the formula.

- An arbitrary non-degenerate rectangle with sides parallel to coordinate axes: Let $a$ and $b$ be the lengths of the sides of the rectangle. Then, $S=ab, I=(a-1)(b-1), B=2(a+b)$. On substituting, we see that the formula is true.

- A right triangle with legs parallel to the axes: To prove this, note that any such triangle can be obtained by cutting a rectangle by a diagonal. Denoting the number of integral points lying on the diagonal by $c$, it can be shown that Pick's formula holds for this triangle regardless of $c$.

- An arbitrary triangle: Note that any such triangle can be turned into a rectangle by attaching it to sides of right-angled triangles with legs parallel to the axes (you will not need more than 3 such triangles). From here, we can get the correct formula for any triangle.

- An arbitrary polygon: To prove this, triangulate it, i.e., divide it into triangles whose vertices have integer coordinates. Further, it is possible to prove that Pick's theorem retains its validity when a triangle is attached to a polygon along a shared edge. Thus, we have proven Pick's formula for an arbitrary polygon.

## Generalization to higher dimensions

Unfortunately, this simple and beautiful formula cannot be generalized to higher dimensions.

John Reeve demonstrated this by proposing a tetrahedron (**Reeve tetrahedron**) with following vertices in 1957:

$$A=(0,0,0),
B=(1,0,0),
C=(0,1,0),
D=(1,1,k),$$

where $k$ can be any natural number. Then for any $k$, the tetrahedron $ABCD$ does not contain an integer point inside it and has only $4$ points on its boundary, $A, B, C, D$. Thus, the volume and surface area may vary in spite of an unchanged number of points within and on the boundary. Therefore, Pick's theorem doesn't allow this kind of direct generalization.

There is, however, a higher-dimensional generalization using **Ehrhart polynomials**, but it is more complex and depends not only on points inside but also on the boundary of the polytope.

## Extra Resources
A few simple examples and a simple proof of Pick's theorem can be found [here](http://www.geometer.org/mathcircles/pick.pdf).
