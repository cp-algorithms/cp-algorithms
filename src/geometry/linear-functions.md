<!--?title Convex hull trick and Li Chao tree -->

# Convex hull trick and Li Chao tree

Consider following problem. There are $n$ cities. You want to travel from city $1$ to city $n$ by car. To do this you have to buy some gasoline. It is known that liter of gasoline costs $cost_k$ in $k^{th}$ city. Initially your fuel tank is empty and you spend one liter of gasoline per kilometer. Cities are located on the same line in ascending order with $k^{th}$ city having coordinate $x_k$. Also you have to pay $toll_k$ to enter $k^{th}$ city. Your task is to make the trip with minimum possible cost. It's obvious that solution can be calculated via dynamic programming

$$dp_i = toll_i+\min\limits_{j<i}(cost_j \cdot (x_i - x_j)+dp_j)$$

Naive approach will give you $O(n^2)$ complexity which can be improved to $O(n \log n)$ or $O(n \log [C \varepsilon^{-1}])$ where $C$ is largest possible $|x_i|$ and $\varepsilon$ is precision with which $x_i$ is considered ($\varepsilon = 1$ for integers which is usually the case). To do this one should note that problem can be reduced to adding linear functions $k \cdot x + b$ to the set and finding minimum value of function in some particular point $x$. There are two main approaches one can use here.

## Convex hull trick

Idea of this approach is to maintain lower convex hull of linear functions. Actually it would be a bit more convenient to consider it not as linear functions but as points $(k;b)$ on the plane such that we will have to find the point which has least dot product with given point $(x;1)$, that is, for this point $kx+b$ is minimized which is the same as initial problem. Such minimum will necessarily be on lower convex envelope of these points as can be seen below:

<center> ![lower convex hull](https://i.imgur.com/Qv91YDk.png) </center>

One have to keep points in convex hull alongside with normal vectors of edges of convex hull. When you have $(x;1)$ query you'll have to find normal vector closest to it in terms of angles between them, then optimum linear function will correspond to one of its endpoints. To see that one should note that points having same dot product with $(x;1)$ lie on same line which is orthogonal to $(x;1)$ so optimum linear function will be the one in which tangent to convex hull which is collinear with normal to $(x;1)$ touches the hull. This point can be found as one such that normals of edges lying to the left and to the right of it are headed in different sides of $(x;1)$.

This approach is useful when queries of adding linear functions are monotone in terms of $k$ or if we work offline, i.e. we may firstly add all linear functions and answer queries afterwards. When it comes to deal with online queries however, things will go tough and one will have to use some kind of set data structure to implement proper convex hull. Online approach will not be considered in this article due to its hardness and because second approach (which is Li Chao tree) allows to solve the problem way simpler. Worth mentioning that one can still use this approach in online without complications with sqrt-decomposition. That is, rebuild convex hull from scratch each $\sqrt n$ new lines. 

To implement this approach one should begin with some wrap for points class, here we suggest to use C++ complex number type.

```cpp
typedef int ftype;
typedef complex<ftype> point;
#define x real
#define y imag
 
ftype dot(point a, point b) {
	return (conj(a) * b).x();
}
 
ftype cross(point a, point b) {
	return (conj(a) * b).y();
}
```

Here we will assume that when linear functions are added, their $k$ only increases and we want to find minimum values. We will keep points in vector $hull$ and normal vectors in vector $vecs$. When we add new point, we have to look at the angle formed between last edge in convex hull and vector from last point in convex hull to new point. This angle have to be directed counter-clockwise, that is dot product of last normal vector in hull (directed inside hull) and vector from last point to new one has to be non-negative. While this isn't true, we should erase last point in convex hull alongside with corresponding edge.

```cpp
vector<point> hull, vecs;
 
void add_line(ftype k, ftype b) {
    point nw = {k, b};
    while(!vecs.empty() && dot(vecs.back(), nw - hull.back()) < 0) {
        hull.pop_back();
        vecs.pop_back();
    }
    if(!hull.empty()) {
        vecs.push_back(1i * (nw - hull.back()));
    }
    hull.push_back(nw);
}
 
```
Not to get minimum value in some point we will find first normal vector in convex hull to be directed counter-clockwise from $(x;1)$. Left endpoint of such edge will be the answer. To check if vector $a$ is directed counter-clockwise of vector $b$ we should check if their cross product $[a,b]$ is negative.
```cpp
int get(ftype x) {
    point query = {x, 1};
    auto it = lower_bound(begin(vecs), end(vecs), query, [](point a, point b) {
        return cross(a, b) < 0;
    });
    return dot(query, hull[it - begin(vecs)]);
}
```

## Li Chao tree

Assume you're given set of functions such that each two can intersect at most once. Let's keep in each vertex of segment tree some function in such way that if we go from root to the leaf, it will be guaranteed that among functions we met on the path will be the one giving minimum value in that leaf. Let's see how to construct it.

Assume we're in some vertex corresponding to half-segment $[l;r)$ and function $f_{old}$ is kept there and we add function $f_{new}$. Then intersection point will be either in $[l;m)$ or in $[m;r)$ where $m=\left\lfloor\tfrac{l+r}{2}\right\rfloor$. We can efficiently learn that comparing values of functions in points $l$ and $m$. If dominating function changes then it's in $[l;m)$ otherwise it's in $[m;r)$. Now for the half of segment where there is no intersection we pick lower function and write it in current vertex. You can see that it always be the one which is lower in point $m$. After that we recursively go to the other half of segment with the function which was upper one. As you can see this will keep correctness on the first half of segment and in the other one correctness will be maintained during the recursive call. Thus we can add functions and check the minimum value in the point in $O(\log [C\varepsilon^{-1}])$.

Here is the illustration of what's going on in the vertex when we add new function:

<center>![Li Chao Tree vertex](https://i.imgur.com/SgEADs7.png)</center>

Let's go to implementation now. Once again we will use complex numbers to keep linear functions.

```cpp
typedef int ftype;
typedef complex<ftype> point;
#define x real
#define y imag
 
ftype dot(point a, point b) {
    return (conj(a) * b).x();
}
 
ftype f(point a,  ftype x) {
    return dot(a, {x, 1});
}
```
We will keep functions in array $line$ and use binary indexing of segment tree. If you want to use it on large numbers or doubles, you should use dynamic segment tree. 
```cpp
const int maxn = 2e5;
 
point line[4 * maxn];
 
void add_line(point nw, int v = 1, int l = 0, int r = maxn) {
    int m = (l + r) / 2;
    bool lef = f(nw, l) < f(line[v], l);
    bool mid = f(nw, m) < f(line[v], m);
    if(mid) {
        swap(line[v], nw);
    }
    if(r - l == 1) {
        return;
    } else if(lef != mid) {
        add_line(nw, 2 * v, l, m);
    } else {
        add_line(nw, 2 * v + 1, m, r);
    }
}
```
Now to get minimum we simply choose minimum value along the path to point $x$.
```cpp
int get(int x, int v = 1, int l = 0, int r = maxn) {
    int m = (l + r) / 2;
    if(r - l == 1) {
        return f(ln[v], x);
    } else if(x < m) {
        return min(f(ln[v], x), get(x, 2 * v, l, m));
    } else {
        return min(f(ln[v], x), get(x, 2 * v + 1, m, r));
    }
}
```

## Problems

[CodeChef - Polynomials](https://www.codechef.com/NOV17/problems/POLY)
