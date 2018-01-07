<!--?title Convex hull trick and Li Chao tree -->

# Convex hull trick and Li Chao tree

Consider following problem. There are $n$ cities. You want to travel from city $1$ to city $n$ by car. To do this you have to buy some gasoline. It is known that liter of gasoline costs $cost_k$ in $k^{th}$ city. Initially your fuel tank is empty and you spend one liter of gasoline per kilometer. Cities are located on the same line in ascending order with $k^{th}$ city having coordinate $x_k$. Also you have to pay $toll_k$ to enter $k^{th}$ city. Your task is to make the trip with minimum possible cost. It's obvious that solution can be calculated via dynamic programming

$$dp_i = toll_i+\min\limits_{j<i}(cost_j \cdot (x_i - x_j)+dp_j)$$

Naive approach will give you $O(n^2)$ complexity which can be improved to $O(n \log n)$ or $O(n \log [C \varepsilon^{-1}])$ where $C$ is largest possible $|x_i|$ and $\varepsilon$ is precision with which $x_i$ is considered ($\varepsilon = 1$ for integers which is usually the case). To do this one should note that problem can be reduced to adding linear functions $k \cdot x + b$ to the set and finding minimum value of function in some particular point $x$. There are two main approaches one can use here.

## Convex hull trick

Idea of this approach is to maintain lower convex hull of linear functions. Actually it would be a bit more convenient to consider it not as linear functions but as points $(k, b)$ on the plane such that we will have to find the point which has least dot product with given point $(x,1)$, that is, for this point $kx+b$ is minimized which is the same as initial problem. Such minimum will necessarily be on lower convex envelope of these points as can be seen below. 

One have to keep points in convex hull alongside with normal vectors of edges of convex hull. When you have $(x,1)$ query you'll have to find normal vector closest to it in terms of angles between them, then optimum linear function will correspond to one of its endpoints. To see that one should note that points having same dot product with $(x,1)$ lie on same line which is orthogonal to $(x,1)$ so optimum linear function will be the one in which tangent to convex hull which is collinear with normal to $(x,1)$ touches the hull. This point can be found as one such that normals of edges lying to the left and to the right of it are headed in different sides of $(x,1)$.

![lower convex hull](&imgroot&/envelope.png)

This approach is useful when queries of adding linear functions are monotone in terms of $k$ or if we work offline, i.e. we may firstly add all linear functions and answer queries afterwards. When it comes to deal with online queries however, things will go tough and one will have to use some kind of set data structure to implement proper convex hull. Online approach will not be considered in this article due to its hardness and because second approach (which is Li Chao tree) allows to solve the problem way simpler. Worth mentioning that one can still use this approach in online without complications with sqrt-decomposition. That is, rebuild convex hull from scratch each $\sqrt n$ new lines. 

Below you can see the code for offline approach:

```cpp
int x;
```

## Li Chao tree

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
 
const int maxn = 2e5;
 
point ln[4 * maxn];
 
void add_line(point nw, int v = 1, int l = 0, int r = maxn) {
    int m = (l + r) / 2;
    bool lef = f(ln[v], l) < f(nw, l);
    bool mid = f(ln[v], m) < f(nw, m);
    if(mid) {
        swap(ln[v], nw);
    }
    if(r - l == 1) {
        return;
    } else if(lef != mid) {
        add_line(nw, 2 * v, l, m);
    } else {
        add_line(nw, 2 * v + 1, m, r);
    }
}
 
int get(int x, int v = 1, int l = 0, int r = maxn) {
    int m = (l + r) / 2;
    if(r - l == 1) {
        return f(ln[v], x);
    } else if(x < m) {
        return max(f(ln[v], x), get(x, 2 * v, l, m));
    } else {
        return max(f(ln[v], x), get(x, 2 * v + 1, m, r));
    }
}
```
