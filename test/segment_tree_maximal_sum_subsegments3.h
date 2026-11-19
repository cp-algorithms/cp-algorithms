data query(int v, int tl, int tr, int l, int r) {
    if (r <= tl || tr <= l) 
        return make_data(0);
    if (l <= tl && tr <= r) 
        return t[v];
    int tm = (tl + tr) / 2;
    return combine(query(v*2, tl, tm, l, r), 
                   query(v*2+1, tm, tr, l, r));
}
