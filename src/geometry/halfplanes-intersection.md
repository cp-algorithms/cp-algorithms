<!--?title Half-planes intersection -->
# Half-planes intersection

In this article we will consider the pearl of geometric algorithms, half-planes intersection in $O(n \log n)$.

## Preliminary

### Concepts

Half-plane can defined as all points of the plane lying on the same side from some given line. Thus, if line is given by equation $Ax+By+C=0$, half-plane is the set of points given by $Ax+By+C \geq 0$. 

The other natural way to represent the half plane is by keeping some initial point $\mathbf{a}$ lying on the line and its normal vector $\mathbf{n}$ directed inside half-plane. In this terms equation of the half-plane will be $(\mathbf{r}-\mathbf{a})\cdot \mathbf{n} \geq 0$. Any convex polygon can be represented as finite intersection of half-planes, furthermore any convex set can be represented as infinite intersection of its [supporting half-planes](https://en.wikipedia.org/wiki/Supporting_hyperplane). 

<center>![Some example](https://i.imgur.com/5wCdigR.png)</center>

Intersection of half-planes though always convex, is not always convex polygon. It may be unbounded or it may be empty. In this article we will not consider case of unbounded intersection, instead we will add half-planes restricting the whole intersection inside the rectangle $[-\infty;+\infty]\times[-\infty;+\infty]$ where $\infty$ is not the actual infinity but some sufficiently large number.

So, problem we are dealing with is given $n$ half-planes with bounded intersection to find this intersection.

### Auxiliary

We'll use point class based on complex numbers and keep half-planes as pair of initial point $\mathbf{a}$ and normal $\mathbf{n}$ pointed inside half-plane.
```
typedef double ftype;
typedef complex<ftype> point;
#define x real
#define y imag

struct half {
    point n;
    point a;
};
```
We will also use small float $\varepsilon$ to check if two doubles are actually equal.
```
const ftype eps = 1e-9;

bool eq(point a, point b) {
    return norm(a - b) < eps;
}
bool leq(ftype a, ftype b) {
    return a < b || eq(a, b);
}
```
Next thing to include is dot product $\mathbf{a} \cdot \mathbf{b}$ and cross product $\mathbf{a} \times \mathbf{b}$.
```
point cmul(point a, point b) {
    return conj(a) * b;
}
ftype dot(point a, point b) {
    return cmul(a, b).x();
}
ftype cross(point a, point b) {
    return cmul(a, b).y();
}
```
## Algorithm
### Intersection approach
Unlike in convex hull, you can't guarantee that there is any line which will be actually presented in the intersection, since it may be empty at all. Thus if you will add new half-planes sorted by angle there may be such moment of time that you'll have to delete the very first half-plane you started with. There are several ways to approach it.

1. Build lower and upper envelopes of the intersection separately and intersect them. This way you won't bother about it at all.
2. Keep constructed part of convex hull in queue and erase not only back, but also front of queue when needed.
3. Duplicate the whole sorted list of half-planes and process it with the stack until you have repeating half-plane in it.

We will stick to the third approach as presumably easiest. 

### Sorting

First we'll sort half-planes by the angle of their normal and get rid of half-planes with codirected normals. We should do the following:

- Split whole plane in two parts (lower and upper) such that cross product of two vectors inside same half-plane defines their order.
```
int plane(point a) {
    return ftype(0) < a.y() || (a.y() == 0 && ftype(0) < a.x());
}
bool clock(point a, point b) {
    return make_pair(plane(a), cross(a, b)) < make_pair(plane(b), ftype(0));
}
```
- If normals are collinear and codirected we sort points by $\mathbf{a} \cdot \mathbf{n}$ meaning that half-plane with larger value implies stricter constraint.
```
bool collin(point a, point b) {
    return eq(0, cross(a, b));
}
bool codir(point a, point b) {
    return collin(a, b) && leq(0, dot(a, b));
}
bool operator < (half a, half b) {
    if(codir(a.n, b.n)) {
        return leq(dot(a.n, a.a), dot(b.n, b.a));
    } else {
        return clock(a.n, b.n);
    }
}
```
- Now we may sort our half-planes and get rid of half-planes with collinear and codirected normals.
```
vector<half> filter(vector<half> planes) {
    sort(begin(planes), end(planes));
    vector<half> ans;
    for(auto it = begin(planes); next(it) != end(planes); ++it) {
        if(!codir(it->n, next(it)->n)) {
            ans.push_back(*it);
        }
    }
    ans.push_back(planes.back());
    return ans;
}
```

### To pop or not to pop?
At each step of algorithm we'll erase values from the top when they're not needed anymore. Let's look on both cases.

- You don't have to delete stack top.

<center>![No delete](https://i.imgur.com/ohrei65.png)</center>

- You have to delete stack top.

<center> ![Delete](https://i.imgur.com/ynFFkta.png)</center>

The difference is that intersection of top half-plane and preceding one in the first case is above new line and below it in the second. But the second case is tricky, because while first case guarantees that intersection is still non-empty, second one may contradict this. It may happen if intersection of previous and new half-planes lies below top half-plane. Schematically it looks like this:

<center> ![Empty](https://i.imgur.com/ipR8yGK.png)</center>

Note that this case may also imply that new half-plane is collinear to preceding one.

## Applications
