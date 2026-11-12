int query(int v, int tl, int tr, int l, int r, int x) {
    if (r <= tl || tr <= l)
        return INF;
    if (l <= tl && tr <= r) {
        vector<int>::iterator pos = lower_bound(t[v].begin(), t[v].end(), x);
        if (pos != t[v].end())
            return *pos;
        return INF;
    }
    int tm = (tl + tr) / 2;
    return min(query(v*2, tl, tm, l, r, x), 
               query(v*2+1, tm, tr, l, r, x));
}
