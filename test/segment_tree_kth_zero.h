int find_kth(int v, int tl, int tr, int k) {
    if (k > t[v])
        return -1;
    if (tr - tl == 1)
        return tl;
    int tm = (tl + tr) / 2;
    if (t[v*2] >= k)
        return find_kth(v*2, tl, tm, k);
    else 
        return find_kth(v*2+1, tm, tr, k - t[v*2]);
}
