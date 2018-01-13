<!--?title Sqrt Tree-->

# Sqrt Tree

Given an array $a$ that contains $n$ elements and the operation $\circ$ that satisfies associative property: $(x \circ y) \circ z = x \circ (y \circ z)$ is true for any $x$, $y$, $z$.

So, such operations as $\gcd$, $\min$, $\max$, $+$, $\text{and}$, $\text{or}$, $\text{xor}$, etc. satisfy these conditions.

Also we have some queries $q(l, r)$. For each query, we need to compute $a_l \circ a_{l+1} \circ \dots \circ a_r$.

Sqrt Tree can process such queries in $O(1)$ time with $O(n \cdot \log \log n)$ preprocessing time and $O(n \cdot \log \log n)$ memory.

# Description

## Building sqrt decomposition

Let's make a [sqrt decomposition](/data_structures/sqrt_decomposition.html). We divide our array in $\sqrt{n}$ blocks, each block has size $\sqrt{n}$. For each block, we compute:

1. Answers to the queries that lie in the block and begin at the beginning of the block ($\text{prefixOp}$)
2. Answers to the queries that lie in the block and end at the end of the block ($\text{suffixOp}$)

And we'll compute an additional array:

3. $\text{between}_{i, j}$ (for $i \le j$) - answer to the query that begins at the start of block $i$ and ends at the end of block $j$. Note that we have $\sqrt{n}$ blocks, so the size of this array will be $O(\sqrt{n}^2) = O(n)$.

Let's see the example.

Let $\circ$ be $+$ (we calculate sum on a segment) and we have the following array $a$:

`{1, 2, 3, 4, 5, 6, 7, 8, 9}`

It will be divided onto three blocks: `{1, 2, 3}`, `{4, 5, 6}` and `{7, 8, 9}`.

For first block $\text{prefixOp}$ is `{1, 3, 6}` and $\text{suffixOp}$ is `{6, 5, 3}`.

For second block $\text{prefixOp}$ is `{4, 9, 15}` and $\text{suffixOp}$ is `{15, 11, 6}`.

For third block $\text{prefixOp}$ is `{7, 15, 24}` and $\text{suffixOp}$ is `{24, 17, 9}`.

$\text{between}$ array is:

~~~~~
{
    {6, 21, 45},
    {0, 15, 39},
    {0, 0,  24}
}
~~~~~

(we assume that invalid elements where $i > j$ are filled with zeroes)

It's obvious to see that these arrays can be easily calculated in $O(n)$ time and memory.

We already can answer some queries using these arrays. If the query doesn't fit into one block, we can divide it onto three parts: suffix of a block, then some segment of contiguous blocks and then prefix of some block. We can answer a query by dividing it into three parts and taking our operation of some value from $\text{suffixOp}$, then some value from $\text{between}$, then some value from $\text{prefixOp}$.

But if we have queries that entirely fit into one block, we cannot process them using these three arrays. So, we need to do something.

## Making a tree

We cannot answer only the queries that entirely fit in one block. But what **if we build the same structure as described above for each block?** Yes, we can do it. And we do it recursively, until we reach the block size of $1$ or $2$. Answers for such blocks can be calculated easily in $O(1)$.

So, we get a tree. Each node of the tree represents some segment of the array. Node that represents array segment with size $k$ has $\sqrt{k}$ children -- for each block. Also each node contains the three arrays described above for the segment it contains. The root of the tree represents the entire array. Nodes with segment lengths $1$ or $2$ are leaves.

Also it's obvious that the height of this tree is $O(\log \log n)$, because if some vertex of the tree represents an array with length $k$, then its children have length $\sqrt{k}$. $\log(\sqrt{k}) = \frac{\log{k}}{2}$, so $\log k$ decreases two times every layer of the tree and so its height is $O(\log \log n)$. The time for building and memory usage will be $O(n \cdot \log \log n)$, because every element of the array appears exactly once on each layer of the tree.

Now we can answer the queries in $O(\log \log n)$. We can go down on the tree until we meet a segment with length $1$ or $2$ (answer for it can be calculated in $O(1)$ time) or meet the first segment in which our query doesn't fit entirely into one block. See the first section on how to answer the query in this case.

OK, now we can do $O(\log \log n)$ per query. Can it be done faster?

## Optimizing the query complexity

One of the most obvious optimization is to binary search the tree node we need. Using binary search, we can reach the $O(\log \log \log n)$ complexity per query. Can we do it even faster?

The answer is yes. Let's assume the following two things:

1. Each block size is a power of two.
2. All the blocks are equal on each layer.

To reach this, we can add some zero elements to our array so that its size becomes a power of two.

When we use this, some block sizes may become twice larger to be a power of two, but it still be $O(\sqrt{k})$ in size and we keep linear complexity for building the arrays in a segment.

Now, we can easily check if the query fits entirely into a block with size $2^k$. Let's write the ranges of the query, $l$ and $r$ (we use 0-indexation) in binary form. For instance, let's assume $k=4, l=39, r=46$. The binary representation of $l$ and $r$ is:

$l = 39_{10} = 100111_2$

$r = 46_{10} = 101110_2$

Remember that one layer contains segments of the equal size, and the block on one layer have also equal size (in our case, their size is $2^k = 2^4 = 16$. The blocks cover the array entirely, so the first block covers elements $(0 - 15)$ ($(000000_2 - 001111_2)$ in binary), the second one covers elements $(16 - 31)$ ($(010000_2 - 011111_2)$ in binary) and so on. We see that the indices of the positions covered by one block may differ only in $k$ (in our case, $4$) last bits. In our case $l$ and $r$ have equal bits except four lowest, so they lie in one block.

So, we need to check if nothing more that $k$ smallest bits differ (or $l\ \text{xor}\ r$ doesn't exceed $2^k-1$).

Using this observation, we can find a layer that is suitable to answer the query quickly. How to do this:

1. For each $i$ that doesn't exceed the array size, we find the highest bit that is equal to $1$. To do this quickly, we use DP and a precalculated array.

2. Now, for each $q(l, r)$ we find the highest bit of $l\ \text{xor}\ r$ and, using this information, it's easy to choose the layer on which we can process the query easily. We can also use a precalculated array here.

For more details, see the code below.

So, using this, we can answer the queries in $O(1)$ each. Hooray! :)

# Implementation

~~~~~
int op(int a, int b);

inline int log2Up(int n) {
    int res = 0;
    while ((1 << res) < n) {
        res++;
    }
    return res;
}

class SqrtTree {
    private:
        int n, lg;
        vector<int> v;
        vector<int> clz;
        vector<int> layers;
        vector<int> onLayer;
        vector< vector<int> > pref;
        vector< vector<int> > suf;
        vector< vector<int> > between;
        
        void build(int layer, int lBound, int rBound) {
            if (layer >= (int)layers.size()) {
                return;
            }
            int bSzLog = (layers[layer]+1) >> 1;
            int bCntLog = layers[layer] >> 1;
            int bSz = 1 << bSzLog;
            int bCnt = 0;
            for (int l = lBound; l < rBound; l += bSz) {
                bCnt++;
                int r = min(l + bSz, rBound);
                pref[layer][l] = v[l];
                for (int i = l+1; i < r; i++) {
                    pref[layer][i] = op(pref[layer][i-1], v[i]);
                }
                suf[layer][r-1] = v[r-1];
                for (int i = r-2; i >= l; i--) {
                    suf[layer][i] = op(v[i], suf[layer][i+1]);
                }
                build(layer+1, l, r);
            }
            for (int i = 0; i < bCnt; i++) {
                int ans = 0;
                for (int j = i; j < bCnt; j++) {
                    int add = suf[layer][lBound + (j << bSzLog)];
                    ans = (i == j) ? add : op(ans, add);
                    between[layer][lBound + (i << bCntLog) + j] = ans;
                }
            }
        }
    public:
        inline int query(int l, int r) {
            if (l == r) {
                return v[l];
            }
            if (l + 1 == r) {
                return op(v[l], v[r]);
            }
            int layer = onLayer[clz[l ^ r]];
            int bSzLog = (layers[layer]+1) >> 1;
            int bCntLog = layers[layer] >> 1;
            int lBound = (l >> layers[layer]) << layers[layer];
            int lBlock = ((l - lBound) >> bSzLog) + 1;
            int rBlock = ((r - lBound) >> bSzLog) - 1;
            int ans = suf[layer][l];
            if (lBlock <= rBlock) {
                ans = op(ans, between[layer][lBound + (lBlock << bCntLog) + rBlock]);
            }
            ans = op(ans, pref[layer][r]);
            return ans;
        }
        
        SqrtTree(const vector<int>& v)
            : n((int)v.size()), lg(log2Up(n)), v(v), clz(1 << lg), onLayer(lg+1) {
            clz[0] = 0;
            for (int i = 1; i < (int)clz.size(); i++) {
                clz[i] = clz[i >> 1] + 1;
            }
            int tlg = lg;
            while (tlg > 1) {
                onLayer[tlg] = (int)layers.size();
                layers.push_back(tlg);
                tlg = (tlg+1) >> 1;
            }
            for (int i = lg-1; i >= 0; i--) {
                onLayer[i] = max(onLayer[i], onLayer[i+1]);
            }
            pref.assign(layers.size(), vector<int>(n));
            suf.assign(layers.size(), vector<int>(n));
            between.assign(layers.size(), vector<int>(1 << lg));
            build(0, 0, n);
        }
};

~~~~~

# Problems

[CodeChef - SEGPROD](https://www.codechef.com/NOV17/problems/SEGPROD)
