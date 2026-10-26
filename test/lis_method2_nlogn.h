int lis(vector<int> const& a) {
    vector<int> d;
    for (int x : a) {
        auto it = lower_bound(d.begin(), d.end(), x);
        if (it == d.end())
            d.push_back(x);
        else
            *it = x;
    }
    return d.size();
}
