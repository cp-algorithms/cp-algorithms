<!--?title Intersection of two segments-->

#Intersection of two segments

Given two segments (they can degenerate into points), it is required to find their intersection: 

1. it can be empty (if the segments do not intersect)
2. it can be a single point
3. it can be a whole segment (if the segments overlap each other).

##Algorithm

We will work with segments as with straight lines: we construct the equations of the straight lines over the two segments, and check whether the lines are parallel. 

If the lines are not parallel, then everything is simple: we find their intersection point and check if it belongs to both segments (it's enough to verify that the point belongs to each segment in the projection on the $X$-axis and on the $Y$-axis separately). As a result, in this case the answer will be either 'empty' or the only one point will be found.

If the straight lines turn out to be parallel (this is also the case when one or both segments degenerate into points), it is necessary to check that both segments lie on one straight line (or, in the case when they both degenerate into a point, that this point coincides). If this is not the case, the answer is 'empty'. Otherwise, the answer is the intersection of two segments lying on one straight line, which is realized quite simply - you need to take the maximum from the left end and the minimum from the right end.

##Implementation

This is a complete implementation, including all the auxiliary functions for working with points and straight lines.

The main function here is the $\rm intersect$ function, which checks two segments passed to it, and if they intersect in at least one point, it returns $\rm true$, and the arguments $\rm left$ and $\rm right$ return the beginning and end of the intersection segment (in particular, when the answer is the only point, the beginning and end will be the same).

```cpp
const double EPS = 1E-9;
 
struct pt {
	double x, y;
 
	bool operator< (const pt & p) const {
		return x < p.x-EPS || abs(x-p.x) < EPS && y < p.y - EPS;
	}
};
 
struct line {
	double a, b, c;
 
	line() {}
	line (pt p, pt q) {
		a = p.y - q.y;
		b = q.x - p.x;
		c = - a * p.x - b * p.y;
		norm();
	}
 
	void norm() {
		double z = sqrt (a*a + b*b);
		if (abs(z) > EPS)
			a /= z,  b /= z,  c /= z;
	}
 
	double dist (pt p) const {
		return a * p.x + b * p.y + c;
	}
};
 
#define det(a,b,c,d)  (a*d-b*c)
 
inline bool betw (double l, double r, double x) {
	return min(l,r) <= x + EPS && x <= max(l,r) + EPS;
}
 
inline bool intersect_1d (double a, double b, double c, double d) {
	if (a > b)  swap (a, b);
	if (c > d)  swap (c, d);
	return max (a, c) <= min (b, d) + EPS;
}
 
bool intersect (pt a, pt b, pt c, pt d, pt & left, pt & right) {
	if (! intersect_1d (a.x, b.x, c.x, d.x) || ! intersect_1d (a.y, b.y, c.y, d.y))
		return false;
	line m (a, b);
	line n (c, d);
	double zn = det (m.a, m.b, n.a, n.b);
	if (abs (zn) < EPS) {
		if (abs (m.dist (c)) > EPS || abs (n.dist (a)) > EPS)
			return false;
		if (b < a)  swap (a, b);
		if (d < c)  swap (c, d);
		left = max (a, c);
		right = min (b, d);
		return true;
	}
	else {
		left.x = right.x = - det (m.c, m.b, n.c, n.b) / zn;
		left.y = right.y = - det (m.a, m.c, n.a, n.c) / zn;
		return betw (a.x, b.x, left.x)
			&& betw (a.y, b.y, left.y)
			&& betw (c.x, d.x, left.x)
			&& betw (c.y, d.y, left.y);
	}
}

```
