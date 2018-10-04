<!--?title Point location in O(log n) -->
<!--?imgroot &imgroot&-->
#Point location in O(log n)
Consider the following problem: you are given a [planar subdivision](https://en.wikipedia.org/wiki/Planar_straight-line_graph) without any vertices of degree one and zero, and a lot of queries.
Each query is a point, for which we should determine the face of the subdivision it belongs to.
We will answer each query in $O(\log n)$ offline.<br>
This problem may arise when you need to locate some points in a Voronoi diagram or in some simple polygon.

##Algorithm
Firstly, for each query point $p\ (x\_0, y\_0)$ we want to find such an edge that if the point belongs to any edge, the point lies on the edge we found, otherwise this edge must intersect the line $x = x\_0$ at some unique point $(x\_0, y)$ where $y < y\_0$ and this $y$ is maximum among all such edges.<br>
We will solve this problem offline using the scanline technique. Let's iterate over x-coordinates of query points and edges' endpoints in increasing order and keep a set of edges $s$. For each x-coordinate we will add some events beforehand. The events will be of four types: _add_, _remove_, _vertical_, _get_. For each edge with the same x-coordinates of the endpoints we will add one _vertical_ event for the corresponding x-coordinate. For each edge with different x-coordinates of the endpoints we will add one _add_ event for the minimum of x-coordinates of the endpoints and one _remove_ event for the maximum of x-coordinates of the endpoints. Finally, for each query point we will add one _get_ event for it's x-coordinate. For each x-coordinate we will sort the events by their types in order (_vertical_, _get_, _remove_, _add_). Let's keep a set $vs$ of vertical edges, which we will clear at the beginning of processing each x-coordinate. Now let's process the events for a fixed x-coordinate. If we got a _vertical_ event, we will simply insert the minimum y-coordinate of the corresponding edge's endpoints to $vs$. If we got a _remove_ or _add_ event, we will remove the corresponding edge from $s$ or add it to $s$. Finally, for each _get_ event we must check if the point lies on some vertical edge using an upper\_bound on $vs$. If the point doesn't lie on any vertical edges, we must find the answer for this query in $s$. To do this, we make an upper\_bound query on $s$ for the edge with its endpoints equal to the query point and decrement the returned iterator (if it was equal to $s.begin()$, there is no edge under the query point). In order to handle some degenerate cases, we must answer all _get_ events again after we processed all the events for this x-coordinate and choose the best of two answers.<br>
Now let's choose a comparator for the set $s$. This comparator should check if one edge doesn't lie above other for every x-coordinate they both cover. Suppose that we have two edges $(a, b)$ and $(c, d)$. Then the comparator is (in pseudocode):<br>
$val = sgn((b - a)\times(c - a)) + sgn((b - a)\times(d - a))$<br>
<b>if</b> $val \neq 0$<br>
<b>then return</b> $val > 0$<br>
$val = sgn((d - c)\times(a - c)) + sgn((d - c)\times(b - c))$<br>
<b>return</b> $val < 0$<br>
Now for every query we have the corresponding edge. How to find the face? If we couldn't find the edge it means that the point is in the outer face. If the point belongs to the edge we found, the face is not unique. Otherwise, there are two candidates &#8211; the faces that are bounded by this edge. How to check which one is the answer? Note that the edge is not vertical. Then the answer is the face that is above this edge. Let's find such a face for each non-vertical edge. Consider a counter-clockwise traversal of each face. If during this travelsal we increased x-coordinate while passing through the edge, then this face is the face we need to find for this edge.

##Notes
Actually, with some persistent trees this approach can be used to answer the queries online.

##Implementation
The following code is implemented for integers, but it can be easily modified to work with doubles.<br>
This implementation assumes that the subdivision is correctly stored inside [DCEL](https://en.wikipedia.org/wiki/Doubly_connected_edge_list) and the outer face is numbered $-1$.<br>
For each query a pair $(1, i)$ is returned if the point lies strictly inside the face number $i$, and a pair $(0, i)$ is returned if the point lies on the edge number $i$.
```cpp point-location
typedef long long ll;

inline bool ge(const ll & a, const ll & b){return a >= b;}
inline bool le(const ll & a, const ll & b){return a <= b;}
inline bool eq(const ll & a, const ll & b){return a == b;}
inline bool gt(const ll & a, const ll & b){return a > b;}
inline bool lt(const ll & a, const ll & b){return a < b;}

struct pt{
	ll x, y;
	pt(){}
	pt(ll _x, ll _y):x(_x), y(_y){}
	pt operator - (const pt & a)const{
		return pt(x - a.x, y - a.y);
	}
	ll dot(const pt & a)const{
		return x * a.x + y * a.y;
	}
	ll dot(const pt & a, const pt & b)const{
		return (a - *this).dot(b - *this);
	}
	ll cross(const pt & a)const{
		return x * a.y - y * a.x;
	}
	ll cross(const pt & a, const pt & b)const{
		return (a - *this).cross(b - *this);
	}
	bool operator == (const pt & a)const{
		return a.x == x && a.y == y;
	}
};

struct Edge{
	pt l, r;
};

inline int sgn(const ll & x){
	return le(x, 0) ? eq(x, 0) ? 0 : -1 : 1;
}

inline bool seg_cmp(const pt & a, const pt & b, const pt & c, const pt & d){
	int val = sgn(a.cross(b, c)) + sgn(a.cross(b, d));
	if(val != 0)
		return val > 0;
	val = sgn(c.cross(d, a)) + sgn(c.cross(d, b));
	return val < 0;
}

enum class QType{
	del = 2,
	add = 3,
	get = 1,
	vert = 0
};

struct Query{
	QType type;
	int pos;
	bool operator < (const Query & q)const{
		return (int)type < (int)q.type;
	}
};

vector<Edge*> scanline(vector<Edge*> planar, vector<pt> queries){
	vector<Edge*> ans(queries.size(), nullptr);
	auto s = set<decltype(pt::x), std::function<bool(const decltype(pt::x)&, const decltype(pt::x)&)> >(lt);
	for(pt p : queries)
		s.insert(p.x);
	for(Edge *e : planar){
		s.insert(e->l.x);
		s.insert(e->r.x);
	}
	int cid = 0;
	auto id = map<decltype(pt::x), int, std::function<bool(const decltype(pt::x)&, const decltype(pt::x)&)> >(lt);
	for(auto x : s)
		id[x] = cid++;
	auto t = set<Edge*, std::function<bool(const Edge*, const Edge*)> >([](const Edge* l, const Edge* r){return seg_cmp(l->l, l->r, r->l, r->r);});
	auto vert = set<pair<decltype(pt::x), int>, std::function<bool(const pair<decltype(pt::x), int>&, const pair<decltype(pt::x), int>&)> >([](const pair<decltype(pt::x), int> & l, const pair<decltype(pt::x), int> & r){if(!eq(l.first, r.first))return lt(l.first, r.first); return l.second < r.second;});
	vector<vector<Query> > qs(cid);
	for(int i = 0; i < (int)queries.size(); i++){
		int x = id[queries[i].x];
		qs[x].push_back(Query{QType::get, i});
	}
	for(int i = 0; i < (int)planar.size(); i++){
		int lx = id[planar[i]->l.x], rx = id[planar[i]->r.x];
		if(lx > rx){swap(lx, rx); swap(planar[i]->l, planar[i]->r);}
		if(lx == rx){
			qs[lx].push_back(Query{QType::vert, i});
		}
		else{
			qs[lx].push_back(Query{QType::add, i});
			qs[rx].push_back(Query{QType::del, i});
		}
	}
	for(int x = 0; x < cid; x++){
		sort(qs[x].begin(), qs[x].end());
		vert.clear();
		for(Query q : qs[x]){
			if(q.type == QType::del){
				t.erase(planar[q.pos]);
			}
			if(q.type == QType::vert){
				vert.insert(make_pair(min(planar[q.pos]->l.y, planar[q.pos]->r.y), q.pos));
			}
			if(q.type == QType::add){
				t.insert(planar[q.pos]);
			}
			if(q.type == QType::get){
				auto jt = vert.upper_bound(make_pair(queries[q.pos].y, planar.size()));
				if(jt != vert.begin()){
					--jt;
					int i = jt->second;
					if(ge(max(planar[i]->l.y, planar[i]->r.y), queries[q.pos].y)){
						ans[q.pos] = planar[i];
						continue;
					}
				}
				Edge* e = new Edge;
				e->l = e->r = queries[q.pos];
				auto it = t.upper_bound(e);
				if(it == t.begin())
					ans[q.pos] = nullptr;
				else
					ans[q.pos] = *(--it);
				delete e;
			}
		}
		for(Query q : qs[x]){
			if(q.type != QType::get)
				continue;
			if(ans[q.pos] != nullptr && eq(ans[q.pos]->l.x, ans[q.pos]->r.x))
				continue;
			Edge* e = new Edge;
			e->l = e->r = queries[q.pos];
			auto it = t.upper_bound(e);
			delete e;
			if(it == t.begin())
				e = nullptr;
			else
				e = *(--it);
			if(ans[q.pos] == nullptr){ans[q.pos] = e; continue;}
			if(e == nullptr)continue;
			if(e == ans[q.pos])continue;
			if(id[ans[q.pos]->r.x] == x){
				if(id[e->l.x] == x){
					if(gt(e->l.y, ans[q.pos]->r.y))
						ans[q.pos] = e;
				}
			}
			else ans[q.pos] = e;
		}
	}
	return ans;
}

struct DCEL{
    struct Edge{
        pt origin;
        Edge *nxt = nullptr;
        Edge *twin = nullptr;
        int face;
    };
    vector<Edge*> body;
};

vector<pair<int, int> > point_location(DCEL planar, vector<pt> queries){
	vector<pair<int, int> > ans(queries.size());
	vector<Edge*> planar2;
	map<intptr_t, int> pos;
	map<intptr_t, int> added_on;
	int n = planar.body.size();
	for(int i = 0; i < n; i++){
	    if(planar.body[i]->face > planar.body[i]->twin->face)
	        continue;
		Edge *e = new Edge;
		e->l = planar.body[i]->origin;
		e->r = planar.body[i]->twin->origin;
		added_on[(intptr_t)e] = i;
		pos[(intptr_t)e] = lt(planar.body[i]->origin.x, planar.body[i]->twin->origin.x) ? planar.body[i]->face : planar.body[i]->twin->face;
		planar2.push_back(e);
	}
	auto res = scanline(planar2, queries);
	for(int i = 0; i < (int)queries.size(); i++){
		if(res[i] == nullptr){
			ans[i] = make_pair(1, -1);
			continue;
		}
		pt p = queries[i];
		pt l = res[i]->l, r = res[i]->r;
		if(eq(p.cross(l, r), 0) && le(p.dot(l, r), 0)){
			ans[i] = make_pair(0, added_on[(intptr_t)res[i]]);
			continue;
		}
		ans[i] = make_pair(1, pos[(intptr_t)res[i]]);
	}
	for(auto e : planar2)
		delete e;
	return ans;
}
```

##Problems
[TIMUS1848 - Fly Hunt](http://acm.timus.ru/problem.aspx?space=1&num=1848&locale=en)
