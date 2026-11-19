int sum(int v, int tl, int tr, int l, int r) {
    if (r <= tl || tr <= l) return 0;  // no overlap
    if (l <= tl && tr <= r) return t[v];  // nested segment

    int tm = (tl + tr) / 2;
    // partial overlap
    return sum(v * 2, tl, tm, l, r)
            + sum(v * 2 + 1, tm, tr, l, r);
}
