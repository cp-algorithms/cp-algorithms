int get_first(int v, int tl, int tr, int l, int r, int x) {
    if (r <= tl || tr <= l) return -1;
    if(t[v] <= x) return -1;
    
    if (tr - tl == 1) return tl;
    
    int tm = tl + (tr-tl)/2;
    int left = get_first(2*v, tl, tm, l, r, x);
    if(left != -1) return left;
    return get_first(2*v+1, tm, tr, l ,r, x);
}
