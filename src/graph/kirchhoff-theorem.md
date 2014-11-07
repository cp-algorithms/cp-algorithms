<!--?title Kirchhoff theorem -->

# Kirchhoff theorem. Finding the number of spanning tree

`Problem`: Given a connected undirected graph. Multiple edges are allowed. Count the number of different spanning trees of the graph.

Kirchhoff proved the following formula in 1847.

## Kirchhoff theorem

Let `G` be the adjacency matrix of the graph. If there are multiple edges between nodes, then $G(u, v)$ is equal to the number of edges between $u$ and $v$. Let `A` be a diagonal matrix, such that $A(u, u)$ is equal to the degree of vertex u.

Let $R = A - G$, then according to Kirchhoff theorem, all the cofactors of this matrix are equal, and equal to the number of spanning trees of the graph. So, you can, delete the last row and last column of the matrix, and the absolute value of the determinant will be equal to the number of spanning trees.

The determinant of the matrix can be found in $O(N^3)$ by using the Gaussian elimination method.

The proof of this theorem is quite difficult and is not presented here.

## Relationship with Kirchhoff laws in electrical circuit

(this section is not yet translated)
