pair<int, int> t[4*MAXN];

pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
    if (a.first > b.first) 
        return a;
    if (b.first > a.first)
        return b;
    return make_pair(a.first, a.second + b.second);
}

void build(int a[], int v, int tl, int tr) {
    if (tr - tl == 1) {
        t[v] = make_pair(a[tl], 1);
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm, tr);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}

pair<int, int> get_max(int v, int tl, int tr, int l, int r) {
    if (r <= tl || tr <= l)
        return make_pair(-INF, 0);
    if (l <= tl && tr <= r)
        return t[v];
    int tm = (tl + tr) / 2;
    return combine(get_max(v*2, tl, tm, l, r), 
                   get_max(v*2+1, tm, tr, l, r));
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tr - tl == 1) {
        t[v] = make_pair(new_val, 1);
    } else {
        int tm = (tl + tr) / 2;
        if (pos < tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm, tr, pos, new_val);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}
