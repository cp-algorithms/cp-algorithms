<!--?title Finding area of simple polygon in O(N) -->

# Finding area of simple polygon in $O(N)$

Let a simple polygon (i.e. without self intersection, not necessarily convex) be given. It is required to calculate its area given its vertices.

## Method 1

This is easy to do if we go through all edges and add trapezium areas bounded by each edge and x-axis. The area needs to be taken with sign so that the extra area will be reduced. Hence, the formula is as follows:

```
S += (X2-X1)*(Y1+Y2)/2
```

Code:

```
double sq (const vector <point> & fig)
{
    double res = 0;
    for (unsigned i = 0; i <fig.size (); i ++)
    {
        point
            p1 = i? fig [i-1]: fig.back (),
            p2 = fig [i];
        res + = (p1.x - p2.x) * (p1.y + p2.y);
    }
    return fabs (res) / 2;
}
```

## Method 2
We can choose a point $O$ arbitrarily, iterate over all edges adding the oriented area of the triangle formed by the edge and point $O$. Again, due to the sign of area, extra area will be reduced.

This method is better as it can be generalized to more complex cases (such as when some sides are arcs instead of straight lines)