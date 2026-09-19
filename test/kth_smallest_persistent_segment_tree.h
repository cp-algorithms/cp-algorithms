Vertex* build(int tl, int tr) {
    if (tr - tl == 1)
        return new Vertex(0);
    int tm = (tl + tr) / 2;
    return new Vertex(build(tl, tm), build(tm, tr));
}

Vertex* update(Vertex* v, int tl, int tr, int pos) {
    if (tr - tl == 1)
        return new Vertex(v->sum+1);
    int tm = (tl + tr) / 2;
    if (pos < tm)
        return new Vertex(update(v->l, tl, tm, pos), v->r);
    else
        return new Vertex(v->l, update(v->r, tm, tr, pos));
}

int find_kth(Vertex* vl, Vertex *vr, int tl, int tr, int k) {
    if (tr - tl == 1)
    	return tl;
    int tm = (tl + tr) / 2, left_count = vr->l->sum - vl->l->sum;
    if (left_count >= k)
    	return find_kth(vl->l, vr->l, tl, tm, k);
    return find_kth(vl->r, vr->r, tm, tr, k-left_count);
}
