int lis(vector<int> const& a) {
    vector<int> d;
    for (int x : a) {
        size_t l = 0;
        while (l < d.size() && d[l] < x)
            l++;
        if (l == d.size())
            d.push_back(x);
        else
            d[l] = x;
    }
    return d.size();
}
