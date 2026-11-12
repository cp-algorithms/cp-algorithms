void update(int v, int tl, int tr, int pos, int new_val) {
    if (tr - tl == 1) {
        t[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos < tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm, tr, pos, new_val);
        t[v] = t[v*2] + t[v*2+1];
    }
}
