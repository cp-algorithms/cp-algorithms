<!--?title Suffix tree. Ukkonen's algorithm-->

# Suffix Tree.Ukkonen's algorithm
This algorithm builds a suffix tree for a string $s$ of length $n$ in a time $O(n\log(k))$) where $k$ is the alphabet size (if it is regarded as a constant, the asymptotic behavior is obtained as $O(n)$).

The inputs to the algorithm are the string $s$ and its length $n$, which are transmitted in the form of global variables.

The main function ```build_tree``` builds a suffix tree. The suffix tree is stored as an array of structures $node$, where $node[0]$ is the root of suffix tree.

In order to simplify the code edges are stored in the same structures: for each vertex in its structure $node$ contains data about the edge that is part of its ancestor. In totality each node stores: $(l, r)$ defining the label $s[l..r-1]$ edges in an ancestor $par$- the top-ancestor,$link$- suffix link, $next$- the list of outgoing edges.

```cpp
string s;
int n;
 
struct node {
	int l, r, par, link;
	map<char,int> next;
 
	node (int l=0, int r=0, int par=-1)
		: l(l), r(r), par(par), link(-1) {}
	int len()  {  return r - l;  }
	int &get (char c) {
		if (!next.count(c))  next[c] = -1;
		return next[c];
	}
};
node t[MAXN];
int sz;
 
struct state {
	int v, pos;
	state (int v, int pos) : v(v), pos(pos)  {}
};
state ptr (0, 0);
 
state go (state st, int l, int r) {
	while (l < r)
		if (st.pos == t[st.v].len()) {
			st = state (t[st.v].get( s[l] ), 0);
			if (st.v == -1)  return st;
		}
		else {
			if (s[ t[st.v].l + st.pos ] != s[l])
				return state (-1, -1);
			if (r-l < t[st.v].len() - st.pos)
				return state (st.v, st.pos + r-l);
			l += t[st.v].len() - st.pos;
			st.pos = t[st.v].len();
		}
	return st;
}
 
int split (state st) {
	if (st.pos == t[st.v].len())
		return st.v;
	if (st.pos == 0)
		return t[st.v].par;
	node v = t[st.v];
	int id = sz++;
	t[id] = node (v.l, v.l+st.pos, v.par);
	t[v.par].get( s[v.l] ) = id;
	t[id].get( s[v.l+st.pos] ) = st.v;
	t[st.v].par = id;
	t[st.v].l += st.pos;
	return id;
}
 
int get_link (int v) {
	if (t[v].link != -1)  return t[v].link;
	if (t[v].par == -1)  return 0;
	int to = get_link (t[v].par);
	return t[v].link = split (go (state(to,t[to].len()), t[v].l + (t[v].par==0), t[v].r));
}
 
void tree_extend (int pos) {
	for(;;) {
		state nptr = go (ptr, pos, pos+1);
		if (nptr.v != -1) {
			ptr = nptr;
			return;
		}
 
		int mid = split (ptr);
		int leaf = sz++;
		t[leaf] = node (pos, n, mid);
		t[mid].get( s[pos] ) = leaf;
 
		ptr.v = get_link (mid);
		ptr.pos = t[ptr.v].len();
		if (!mid)  break;
	}
}
 
void build_tree() {
	sz = 1;
	for (int i=0; i<n; ++i)
		tree_extend (i);
}
```

###Compressed Implementation
This implementation was proposed by Ukkonen
```cpp
const int N=1000000,INF=1000000000;
string a;
int t[N][26],l[N],r[N],p[N],s[N],tv,tp,ts,la;
 
void ukkadd (int c) {
	suff:;
	if (r[tv]<tp) {
		if (t[tv][c]==-1) { t[tv][c]=ts;  l[ts]=la;
			p[ts++]=tv;  tv=s[tv];  tp=r[tv]+1;  goto suff; }
		tv=t[tv][c]; tp=l[tv];
	}
	if (tp==-1 || c==a[tp]-'a') tp++; else {
		l[ts+1]=la;  p[ts+1]=ts;
		l[ts]=l[tv];  r[ts]=tp-1;  p[ts]=p[tv];  t[ts][c]=ts+1;  t[ts][a[tp]-'a']=tv;
		l[tv]=tp;  p[tv]=ts;  t[p[ts]][a[l[ts]]-'a']=ts;  ts+=2;
		tv=s[p[ts-2]];  tp=l[ts-2];
		while (tp<=r[ts-2]) {  tv=t[tv][a[tp]-'a'];  tp+=r[tv]-l[tv]+1;}
		if (tp==r[ts-2]+1)  s[ts-2]=tv;  else s[ts-2]=ts; 
		tp=r[tv]-(tp-r[ts-2])+2;  goto suff;
	}
}
 
void build() {
	ts=2;
	tv=0;
	tp=0;
	fill(r,r+N,(int)a.size()-1);
	s[0]=1;
	l[0]=-1;
	r[0]=-1;
	l[1]=-1;
	r[1]=-1;
	memset (t, -1, sizeof t);
	fill(t[1],t[1]+26,0);
	for (la=0; la<(int)a.size(); ++la)
		ukkadd (a[la]-'a');
}
```

