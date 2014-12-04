<!--?title Length of the union of intervals on a line -->

# Length of the union of intervals on a line in $O(n\log n)$

Given $n$ segments on a line, each one by a pair of coordinates $(x_{2i}, x_{2i+1})$, find the length of their union.

The following algorithm was proposed by Klee in 1977. It works in $O(n\log n)$ and has been proved to be the asymptotically fastest.

## Solution

Store in an array $X$ the endpoints of all the segments sorted by its value, with the left end first if their values are equal, and wether it is a left end or a right end of a segment. Now go through the array keeping a counter $C$ of overlapping segments. If $C$ is non-zero, then add $x_i-x_{i-1}$ to the answer; if the current element is a left end we increase this counter, and otherwise we decrease it.

## Implementation

<pre><code>unsigned segments_union_measure (const vector <pair <int,int> > & a)
{
    unsigned n = a.size();
    vector <pair <int,bool> > x (n*2);
    for (unsigned i=0; i < n; i++)
    {
        x[i*2] = make_pair (a[i].first, false);
        x[i*2+1] = make_pair (a[i].second, true);
    }

    sort (x.begin(), x.end());

    unsigned result = 0;
    unsigned c = 0;
    for (unsigned i=0; i < n*2; i++)
    {
        if (c && i)
            result += unsigned (x[i].first - x[i-1].first);
        if (x[i].second)
            ++c;
        else
            --c;
    }
    return result;
}</code></pre>
