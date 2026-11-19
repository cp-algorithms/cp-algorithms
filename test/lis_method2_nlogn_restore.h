vector<int> lis(vector<int> const& a) {
    int n = a.size();
    vector<int> d, p(n);

    for (int i = 0; i < n; i++) {
        auto it = lower_bound(d.begin(), d.end(), a[i]);
        p[i] = it - d.begin();
        if (it == d.end())
            d.push_back(a[i]);
        else
            *it = a[i];
    }

    int l = d.size() - 1;
    vector<int> subseq;
    for (int i = n - 1; i >= 0 && l >= 0; i--) {
        if (p[i] == l) {
            subseq.push_back(a[i]);
            l--;
        }
    }
    reverse(subseq.begin(), subseq.end());
    return subseq;
}
