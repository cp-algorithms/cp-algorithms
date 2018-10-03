<!--?title Check if points belong to the convex polygon in O(log N) -->
<!--?imgroot &imgroot&-->
#Check if points belong to the convex polygon in O (log N)
Consider the following problem: you are given a convex polygon with integer vertices and a lot of queries.
Each query is a point, for which we should determine whether it lies inside or on the boundary of the polygon or not.
Suppose the polygon is ordered counter-clockwise. We will answer each query in $O(\log n)$ online.

##Algorithm
Let's pick the point with the smallest x-coordinate. If there are several of them, we pick the one with the smallest y-coordinate. Let's denote it as $p_0$.
Now all other points $p_1,\dots,p_n$ of the polygon are ordered by their polar angle from the chosen point (because the polygon is ordered counter-clockwise). If the point belongs to the polygon, it belongs to some triangle $p_0, p_i, p_{i + 1}$ (maybe more than one if it lies on the boundary of triangles). Consider the triangle $p_0, p_i, p_{i + 1}$ such that $p$ belongs to this triangle and $i$ is maximum among all such triangles. There are two cases: $p$ lies on the segment $(p_0, p_n)$ or not. In the second case $p_i$ is not counter-clockwise from $p$ with respect to $p_0$, and $p_{i + 1}$ is. In the first case all $p_i$ are not counter-clockwise from $p$ with respect to $p_0$. It means that me may binary search the point $p_i$ such that it is not counter-clockwise from $p$ with respect to $p_0$, and $i$ is maximum among all such points. Then if $i = n$ we have to check that $p$ lies on $(p_0, p_n)$, otherwise we have to check if $p$ is inside the triangle.<br>
Consider a query $p\ (x, y)$. Firstly, we must check if it lies between $p_1$ and $p_n$. It can be done by checking that the cross product $(p_1 - p_0)\times(p - p_0)$ is zero or has the same sign with $(p_1 - p_0)\times(p_n - p_0)$, and $(p_n - p_0)\times(p - p_0)$ is zero or has the same sign with $(p_n - p_0)\times(p_1 - p_0)$. Now we can binary search the last point from $p_1,\dots p_n$ which is not counter-clockwise from $p$ with respect to $p_0$. For a single point $p_i$ this condition can be checked by checking that $(p_i - p_0)\times(p - p_0) \le 0$. After we found such a point $p_i$, we must test if $p$ lies inside the triangle $p_0, p_i, p_{i + 1}$ or (if $i = n$) if it lies on the segment $(p_0, p_n)$. To test if it belongs to the triangle, we may simply check that $|(p_i - p_0)\times(p_{i + 1} - p_0)| = |(p_0 - p)\times(p_i - p)| + |(p_i - p)\times(p_{i + 1} - p)| + |(p_{i + 1} - p)\times(p_0 - p)|$.<br>
##Implementation
```cpp points_in_convex_polygon
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5 + 5;

struct pt{
	ll x, y;
	pt(){}
	pt(ll _x, ll _y):x(_x), y(_y){}
	pt operator + (const pt & p)const{return pt(x + p.x, y + p.y);}
	pt operator - (const pt & p)const{return pt(x - p.x, y - p.y);}
	ll cross(const pt & p)const{return x * p.y - y * p.x;}
	ll dot(const pt & p)const{return x * p.x + y * p.y;}
	ll cross(const pt & a, const pt & b)const{return (a - *this).cross(b - *this);}
	ll dot(const pt & a, const pt & b)const{return (a - *this).dot(b - *this);}
	ll sqrLen()const{
		return this->dot(*this);
	}
};

inline bool lexComp(const pt & l, const pt & r){
	return l.x < r.x || (l.x == r.x && l.y < r.y);
}

inline int sgn(ll val){
	return val > 0 ? 1 : (val == 0 ? 0 : -1);
}

pt seq[maxn];
int n;

inline int pointInTriangle(pt a, pt b, pt c, pt d){
	ll s1 = llabs(a.cross(b, c));
	ll s2 = llabs(d.cross(a, b)) + llabs(d.cross(b, c)) + llabs(d.cross(c, a));
	return s1 == s2;
}

int query(pt what){
	if(seq[0].cross(what) != 0 && sgn(seq[0].cross(what)) != sgn(seq[0].cross(seq[n - 1])))
		return 0;
	if(seq[n - 1].cross(what) != 0 && sgn(seq[n - 1].cross(what)) != sgn(seq[n - 1].cross(seq[0])))
		return 0;
	if(seq[0].cross(what) == 0){
		return seq[0].sqrLen() >= what.sqrLen();
	}
	int l = 0, r = n - 1;
	while(r - l > 1){
		int mid = (l + r)/2;
		int pos = mid;
		if(seq[pos].cross(what) >= 0)l = mid;
		else r = mid;
	}
	int pos = l;
	return pointInTriangle(seq[pos], seq[pos + 1], pt(0, 0), what);
}

void prepare(pt *p, pt *pn){
	n = pn - p;
	int pos = 0;
	for(int i = 1; i < n; i++){
		if(lexComp(p[i], p[pos]))
			pos = i;
	}
	rotate(p, p + pos, p + n);
	for(int i = 1; i < n; i++)seq[i - 1] = p[i] - p[0];
	--n;
}
```

##Problems
[SGU253 Theodore Roosevelt](https://codeforces.com/problemsets/acmsguru/problem/99999/253)
