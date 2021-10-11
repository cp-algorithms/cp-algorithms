<!--?title Convex Hull construction -->
# Convex Hull construction

In this article we will discuss the problem of constructing a convex hull from a set of points.

Consider $N$ points given on a plane, and the objective is to generate a convex hull, i.e. the smallest
convex polygon that contains all the given points.

We will see the **Graham's scan** algorithm published in 1972 by Graham, and
also the **Monotone chain** algorithm published in 1979 by Andrew. Both
are $\mathcal{O}(N \log N)$, and are asymptotically optimal (as it is proven that there
is no algorithm asymptotically better), with the exception of a few problems where
parallel or online processing is involved.

## Graham Scan Algorithm
The algorithm first finds the bottom-most point $P_0$. If there are multiple points
with the same Y coordinate, the one with the smaller X coordinate is considered. This
step takes $\mathcal{O}(N)$ time.

Next, all the other points are sorted by polar angle in counterclockwise order.
If the polar angle between two points is the same, the nearest point is chosen instead.

Then we iterate through each point one by one, and make sure that the current
point and the two before it make a counterclockwise turn, otherwise the previous
point is discarded, since it would make a non-convex shape. If the three points are collinear,
you have a choice of whether to consider it part of the convex hull or not.
In this implementation we are choosing not to. Checking for clockwise or anticlockwise
nature can be done by checking the [orientation](./geometry/oriented-triangle-area.html).

We use a stack to store the points, and once we reach the original point $P_0$,
the algorithm is done and we return the stack containing all the points of the
convex hull in clockwise order.

### Implementation

```cpp graham_scan
struct pt {
    double x, y;
};

int orientation(pt a, pt b, pt c) {
    double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}

bool cw(pt a, pt b, pt c) { return orientation(a, b, c) < 0; }

pt p0;
bool cmp(pt a, pt b) {
    int o = orientation(p0, a, b);
    if (o == 0)
        return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
            < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
    return o < 0;
}

bool cmp_p0(pt a, pt b) {
    return a.y < b.y || (a.y == b.y && a.x < b.x);
}

void convex_hull(vector<pt>& a) {
    p0 = *min_element(a.begin(), a.end(), cmp_p0);
    sort(a.begin(), a.end(), &cmp);

    vector<pt> st;
    for (int i = 0; i < (int)a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i]))
            st.pop_back();
        st.push_back(a[i]);
    }

    a = st;
}
```

## Monotone chain Algorithm
The algorithm first finds the leftmost and rightmost points A and B. In the event multiple such points exist,
the lowest among the left (lowest Y-coordinate) is taken as A, and the highest among the right (highest Y-coordinate)
is taken as B. Clearly, A and B must both belong to the convex hull as they are the farthest away and they cannot be contained
by any line formed by a pair among the given points.

Now, draw a line through AB. This divides all the other points into two sets, S1 and S2, where S1 contains all the points
above the line connecting A and B, and S2 contains all the points below the line joining A and B. The points that lie on
the line joining A and B may belong to either set. The points A and B belong to both sets. Now the algorithm
constructs the upper set S1 and the lower set S2 and then combines them to obtain the answer. 

To get the upper set, we sort all points by the x-coordinate. For each point we check if either - the current point is the last point,
(which we defined as B), or if the orientation between the line between A and the current point and the line between the current point and B is clockwise. In those cases the 
current point belongs to the upper set S1. Checking for clockwise or anticlockwise nature can be done by checking the [orientation](./geometry/oriented-triangle-area.html).

If the given point belongs to the upper set, we check the angle made by the line connecting the second last point and the last point in the upper convex hull,
with the line connecting the last point in the upper convex hull and the current point. If the angle is not clockwise, we remove the most recent point added
to the upper convex hull as the current point will be able to contain the previous point once it is added to the convex
hull.

The same logic applies for the lower set S2. If either - the current point is B, or the orientation of the lines, formed by A and the 
current point and the current point and B, is counterclockwise - then it belongs to S2.

If the given point belongs to the lower set, we act similarly as for a point on the upper set except we check for a counterclockwise
orientation instead of a clockwise orientation. Thus, if the angle made by the line connecting the second last point and the last point in the lower convex hull,
with the line connecting the last point in the lower convex hull and the current point is not counterclockwise, we remove the most recent point added to the lower convex hull as the current point will be able to contain
the previous point once added to the hull.

The final convex hull is obtained from the union of the upper and lower convex hull, forming a clockwise hull, and the implementation is as follows.

### Implementation

```cpp monotone_chain
struct pt {
    double x, y;
};

bool cmp(pt a, pt b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull(vector<pt>& a) {
    if (a.size() == 1)
        return;

    sort(a.begin(), a.end(), &cmp);
    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)a.size(); i++) {
        if (i == a.size() - 1 || cw(p1, a[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
            while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    a.clear();
    for (int i = 0; i < (int)up.size(); i++)
        a.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        a.push_back(down[i]);
}
```

## Practice Problems

* [Kattis - Convex Hull](https://open.kattis.com/problems/convexhull)
* [Kattis - Keep the Parade Safe](https://open.kattis.com/problems/parade)
* [Timus 1185: Wall](http://acm.timus.ru/problem.aspx?space=1&num=1185)
* [Usaco 2014 January Contest, Gold - Cow Curling](http://usaco.org/index.php?page=viewproblem2&cpid=382)
