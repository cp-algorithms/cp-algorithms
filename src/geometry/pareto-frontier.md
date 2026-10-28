
# Pareto Frontier / Skyline

The **Pareto frontier**, also called the **skyline**, is the set of
points that are not dominated by any other point. It is useful when
comparing objects by two or more criteria, such as maximizing quality
while minimizing cost.

In this article, we consider two-dimensional points and assume that
**larger coordinates are better**. Other conventions, such as minimizing
cost, can be handled by negating the corresponding coordinate.

## Definition

Let the input be a set of points (P = {(x_i, y_i)}).

A point (A = (x_A, y_A)) **dominates** a point (B = (x_B, y_B)) if

\[ x_A `\ge `{=tex}x_B,`\qquad `{=tex}y_A `\ge `{=tex}y_B \]

and at least one of these inequalities is strict.

A point belongs to the Pareto frontier if no other input point dominates
it. Points with identical coordinates are equivalent under this
definition; the algorithm below reports each distinct coordinate pair at
most once.

## Algorithm

For two dimensions, the frontier can be computed by sorting and a single
scan.

1.  Sort the points by decreasing (x). If two points have the same (x),
    sort them by decreasing (y).
2.  Scan the sorted points from left to right, keeping the largest
    (y)-coordinate seen so far.
3.  Keep a point only when its (y)-coordinate is strictly greater than
    every (y)-coordinate seen before it. Otherwise, a previously
    processed point has at least as large an (x)-coordinate and at least
    as large a (y)-coordinate, so the current point is dominated or is a
    duplicate.
4.  Skip duplicate coordinate pairs so each frontier point is reported
    once.

The tie-breaking rule for equal (x)-coordinates is important: processing
the largest (y) first ensures that points with the same (x) but smaller
(y) are correctly discarded.

## Implementation

``` cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Point {
    long long x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

vector<Point> pareto_frontier(vector<Point> points) {
    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        if (a.x != b.x)
            return a.x > b.x;
        return a.y > b.y;
    });

    vector<Point> frontier;
    long long best_y = 0;
    bool has_best = false;

    for (const Point& p : points) {
        // Equal coordinate pairs are reported only once.
        if (!frontier.empty() && frontier.back() == p)
            continue;

        if (!has_best || p.y > best_y) {
            frontier.push_back(p);
            best_y = p.y;
            has_best = true;
        }
    }

    return frontier;
}

int main() {
    vector<Point> points = {
        {1, 5}, {2, 4}, {3, 7}, {4, 3}, {2, 6}
    };

    vector<Point> frontier = pareto_frontier(points);

    for (const Point& p : frontier)
        cout << "(" << p.x << ", " << p.y << ") ";

    cout << '\n';
}
```

## Example

Consider the points

\[ (1,5), (2,4), (3,7), (4,3), (2,6). \]

After sorting by decreasing (x), and then decreasing (y), we get

\[ (4,3), (3,7), (2,6), (2,4), (1,5). \]

-   ((4,3)) is kept because it is the first point.
-   ((3,7)) is kept because (7 \> 3).
-   ((2,6)) is discarded because ((3,7)) dominates it.
-   ((2,4)) is discarded because a previously processed point has both
    coordinates at least as large.
-   ((1,5)) is discarded because ((3,7)) dominates it.

Therefore, the Pareto frontier is

\[ {(4,3), (3,7)}. \]

## Correctness

We prove that the algorithm reports exactly the non-dominated points.

The points are processed in decreasing order of (x), with decreasing (y)
for equal (x).

If a point (p) is discarded, then a previously processed point has an
(x)-coordinate at least as large as (p.x) and a (y)-coordinate at least
as large as (p.y). If either coordinate is strictly larger, that point
dominates (p). If both coordinates are equal, it is a duplicate, which
we intentionally report only once. Thus, no discarded distinct point
belongs to the frontier.

If a point (p) is kept, its (y)-coordinate is strictly larger than every
(y)-coordinate processed before it. Any point with a larger
(x)-coordinate has already been processed and therefore has a smaller
(y)-coordinate. Any point with a smaller (x)-coordinate cannot dominate
(p), because its (x)-coordinate is smaller. Points with equal (x) and
smaller (y) are also unable to dominate (p). Hence no other point
dominates (p), so it belongs to the frontier.

Therefore, the algorithm reports every distinct non-dominated point and
no dominated point.

## Complexity

Sorting takes (O(n `\log `{=tex}n)) time. The scan takes (O(n)) time, so
the total time complexity is (O(n `\log `{=tex}n)). The additional space
used for the sorted input and frontier is (O(n)).

## References

-   [Issue: Add Pareto Frontier /
    Skyline](https://github.com/cp-algorithms/cp-algorithms/issues/1729)
