void build(int a[], int v, int tl, int tr) {
    if (tr - tl == 1) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
}
