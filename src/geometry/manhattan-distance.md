---
tags:
  - Original
---

# Manhattan Distance
	
## Definition
Consider we have some points on a plane, and define a distance from point $p$ to $q$ as being the sum of the difference between their $x$ and $y$ coordinates: 

$d(p,q) = |p.x - q.x| + |p.y - q.y|$

This is informally know as the [Manhattan distance, or taxicab geometry](https://en.wikipedia.org/wiki/Taxicab_geometry), because we can think of the points as being intersections in a well designed city, like manhattan, where you can only move on the streets, as shown in the image below:

This images show some of the smallest paths from one black point to the other, all of them with distance $12$.

There are some interseting tricks and algorithms that can be done with this distance, and we will show some of them here.

## Farthest pair of points in Manhattan Distance

Given $n$ points $P$, we want to find the pair of points $p,q$ that are farther apart, that is, maximize $d(p, q) = |p.x - q.x| + |p.y - q.y|$.

Let's think first in one dimension, so $y=0$. The main observation is that we can bruteforce if $|p.x - q.x|$ is equal to $p.x - q.x$ or $-p.x + q.x$, because if we "miss the sign" of the absolute value, we will get only a smaller value, so it can't affect the answer. More formally, we have that:

$|p.x - q.x| = max(p.x - q.x, -p.x + q.x)$

So for example, we can try to have $p$ such that $p.x$ has the plus sign, and then $q$ must have the negative sign. This way we want to find:
$max_{p, q \in P}(p.x + (-q.x)) = max_{p \in P}(p.x) + max_{q \in P}( - q.x )$.

Notice that we can extend this idea further for 2 (or more!) dimensions. For $d$ dimensions, we must bruteforce $2^d$ possible values of the signs. For example, if we are in $2$ dimensions and bruteforce that $p$ has both the plus signs we want to find: 

$max_{p, q \in P} (p.x + (-q.x)) + (p.y + (-q.y)) = max_{p \in P}(p.x + p.y) + max_{q \in P}(-q.x - q.y)$.

As we made $p$ and $q$ independent, it is now easy to find the $p$ and $q$ that maximize the expression. 

## Rotating the points and Chebyshev distance



## Manhattan Minimum Spanning Tree

The Manhattan MST problem consists of, given some points in the plane, find the edges that connect all the points and have a minimum total sum of weights. The weight of an edge that connects to points is their Manhattan distance. For simplicity, we assume that all points have different locations.
Here we show a way of finding the MST in $O(n\logn)$ by finding for each point its nearest neighbor in each octant, as represented by the image below. This will give us $O(n)$ candidate edges, which will guarantee that they contain the MST. The final step is then using some standard MST, for example, [Kruskal algorithm using disjoint set union](https://cp-algorithms.com/graph/mst_kruskal_with_dsu.html).

The algorithm show here was first presented in a paper from [H. Zhou, N. Shenoy, and W. Nichollos (2002)](https://ieeexplore.ieee.org/document/913303). There is also another know algorithm that uses a Divide and conquer approach by [J. Stolfi](https://www.academia.edu/15667173/On_computing_all_north_east_nearest_neighbors_in_the_L1_metric), which is also very interesting and only differ in the way they find the nearest neighbor in each octant.

First, let's understand why it is enough to consider only the nearest neighbor in each octant. The idea is to show that for a point s and any two other points $p$ and $q$ in the same octant, $dist(p, q) < max(dist(s, p), dist(s, q))$. This is important, because it shows that if there was a MST where $s$ is connected to both $p$ and $q$, we could erase one of these edges and add the edge $(p,q)$, which would decrease the total cost. To prove, we assume without loss of generality that $p$ and $q$ are in the octanct $R_1$, which is defined by: $x_s \leq x$ and $x_s - y_s > x -  y$, and then do some casework. The images below give some intuition on why this is true.

Therefore, the main question is how to find the nearest neighbor in each octant for every single of the $n$ points.

## Nearest Neighbor in each Octant in $O(n\logn)$

For simplicity we focus on the north-east octant. All other directions can be found with the same algorithm by rotating the input.
	
We will use a sweep-line approach. We process the points from south-west to north-east, that is, by non-decreasing $x + y$. We also keep a set of points which don't have their nearest neighbor yet. 

When we add a new point point $p$, for every point $s$ that has it in it's octant we can safely assign $p$ as the nearest neighbor. This is true because their distance is $d(p,s) = |x_p - x_s| + |y_p - y_s| = (x_p + y_p) - (x_s + y_s)$, because $p$ is in the north-east octant. As all the next points will not have a smaller value of $x + y$ because of the process order, $p$ is guaranteed to have the smaller distance. We can then remove all such points from the active set, and finally add $p$ to this set. 

The next question is how to efficiently find which points $s$ have $p$ in the north-east octant. That is, which points $s$ satisfy:

- $x_s \leq x_p$
- $x_p - y_p < x_s - y_s$

Because no points in the active set are in the R_1 of another, we also have that for two points $q_1$ and $q_2$ in the active set, $x_{q_1} \neq x_{q_2}$ and $x_{q_1} < x_{q_2} \implies x_{q_1} - y_{q_1} \leq x_{q_2} - y_{q_2}$.

This means that if we keep the active set ordered by $x$ the candidates $s$ are consecutively placed. We can then find the largest $x_s \leq x_p$ and process the points in decreasing order of $x$ until the second condition $x_p - y_p < x_s - y_s$ breaks (we can actually allow that $x_p - y_p = x_s - y_s$ and that deals with the case of points with equal coordinates). Notice that because we remove from the set right after processing, this will have an amortized complexity of $O(n \log(n))$.
	Now that we have the nearest point in the north-east direction, we rotate the points and repeat. It is possible to show that actually we also find this way the nearest point in the south-west direction, so we can repeat only 4 times, instead of 8.

In summary we:
- Sort the points by $x + y$ in non-decreasing order;
- For every point, we iterate over the active set starting with the point with the largest $x$ such that $x \leq x_p$, and we break the loop if  $x_p - y_p \geq x_s - y_s$. For every valid point $s$ we add the edge $(s,p, dist(s,p))$ in our list;
- We add the point $p$ to the active set;
- Rotate the points and repeat until we iterate over all the octants.
- Apply Kruskal algorithm in the list of edges to get the MST. 

Below you can find a implementation, based on the one from [KACTL](https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/ManhattanMST.h).

```{.cpp file=manhattan_mst.cpp}
vector<tuple<long long,int,int> > manhattan_mst_edges(vector<point> ps){
    vector<int> ids(ps.size());
    iota(ids.begin(), ids.end(), 0);
    vector<tuple<long long,int,int> > edges;
    for(int rot = 0; rot < 4; rot++){ // for every rotation
        sort(ids.begin(), ids.end(), [&](int i,int j){
            return (ps[i].x + ps[i].y) < (ps[j].x + ps[j].y);
        });
        map<int, int, greater<int> > active; // (xs, id)
        for(auto i : ids){
            for(auto it = active.lower_bound(ps[i].x); it != active.end();
            active.erase(it++)){
                int j = it->second;
                if(ps[i].x - ps[i].y > ps[j].x - ps[j].y)break;
                assert(ps[i].x >= ps[j].x && ps[i].y >= ps[j].y);
                edges.push_back({(ps[i].x - ps[j].x) + (ps[i].y - ps[j].y), i, j});
            }
            active[ps[i].x] = i;
        }
        for(auto &p : ps){ // rotate
            if(rot&1)p.x *= -1;
            else swap(p.x, p.y);
        }
    }
    return edges;
}
```
