# The lowest common ancestor. Finding the O (1) preprocessing O (N) (algorithm Farah-Colton and Bender)

Let this tree of G. On input a request of the form (V1, V2), for each query you want to find their lowest common ancestor, i.e. a vertex V that lies on the path from the root to V1, the path from the root to V2, and from such vertices should choose the lower. In other words, the desired vertex V is the parent and V1, and V2, and among all such common ancestors selected the bottom. It is obvious that the least common ancestor of vertices V1 and V2 is their common ancestor that lies on a shortest path from V1 to V2. In particular, for example, if V1 is ancestor of V2, then V1 is their lowest common ancestor.

In English, this problem is called the problem of LCA - Least Common Ancestor.

The described algorithm Farah-Colton and Bender (Farach-Colton, Bender) is asymptotically optimal, and thus relatively simple (compared to other algorithms, for example, Gate-Vishkin).

## Algorithm

We use the classical reduction of the problem LCA the task of RMQ (minimum interval) (for more details see The lowest common ancestor. Finding O (sqrt (N)) and O (log N) with preprocessing O (N)). Learn now to solve the RMQ problem in this particular case, with a preprocessing of O (N) time and O (1) per query.

Note that the RMQ problem to which we have reduced the task of LCA is very specific: any two adjacent elements in the array differ exactly on the unit (since the elements of the array is nothing more than the height of the vertices visited in order of traversal, and we either go to the descendant, then the next item will be 1 more, or go to the ancestor, then the next item is 1 less). The actual algorithm Farah-Colton and Bender is precisely the solution of this problem of RMQ.

Denote by A the array over which you are running the RMQ queries, and N is the size of the array.

Construct the algorithm that solves the problem with a preprocessing $O (N log N)$ time and $O (1)$ on request.
It is easy to do:
create a so-called Sparse Table $T[l,i]$, where each element $T[l,i]$ is equal to the minimum of A on the interval [l; l+2i).
Obviously, $0 <= i <= \lceil \log N \rceil$, and therefore the size of the Sparse Table will be O (N log N). To build it as easily in O (N log N) by noting that T[l,i] = min (T[l,i-1], T[l+2i-1i-1]). Now how to answer each query RMQ in O (1)? Let the received query (l,r), then the answer is min (T[l,sz] T[r-2sz+1,sz]), where sz is the largest power of two not superior to r-l+1. Indeed, we would take a cut (l,r) and cover two segments of length 2sz - one starting in l and the other ending in r (and these segments overlap, which in this case does not prevent us). To really achieve asymptotic O (1) per query, we need to know the values of sz for all possible lengths from 1 to N.

Now let's describe, how to improve this algorithm asymptotics up to O (N).

Divide the array A into blocks of size K = 0.5 logTwo N. For each block, calculate the minimum element and its position (as to solve the problem of the LCA is important to us, not the minima, and their positions). Suppose B is an array of size N / K, composed of these minima in each block. Construct the array B Sparse Table, as described above, the size of the Sparse Table and the time of its construction will be equal:

$$\frac{N}{K}\log\left(\frac{N}{K}\right) = \frac{2N}{\log(N)} \log\left(\frac{2N}{\log(N)}\right) =$$
$$= \frac{2N}{\log(N)} \left(1 + \log\left(\frac{N}{\log(N)}\right)\right) \leq \frac{2N}{\log(N)} + 2N = O(N)$$

Now we just have to learn to quickly answer the query RMQ within each unit. In fact, if received query RMQ(l,r), if l and r are in different units, the answer is a minimum of the following values: low in the block l, starting with l to the end of the block, then at least in the blocks after l until r (not inclusive), and finally the low block r, from the beginning of the block, r. On request "low blocks" we can answer in O (1) using the Sparse Table, with only the RMQ queries inside blocks.

Here we will use the "+-1". Note that if the inside of each unit from each element to subtract the first element, then all blocks are uniquely determined by the sequence of length K-1 consisting of the numbers +-1. Consequently, the number of different blocks will be equal to:

$$2^{K-1} = 2^{0.5 \log(N) - 1} = 0.5 \sqrt{N}$$

Thus, the number of different blocks is O (sqrt (N)), and therefore we can know the results of RMQ inside all the different blocks in O (sqrt(N) KTwo) = O (sqrt(N) logTwo N) = O (N). From the point of view of implementation, we can for every block to characterize a bitmask of length K-1 (which, obviously, will fit in a standard int), and store predpochtenie RMQ in a array R[mask,l,r] of size O (sqrt(N) logTwo N).

So, we learned to predpochitaut results RMQ within each unit, as well as RMQ over by the blocks, all sums in O (N), and answer each query RMQ in O (1) - using only predisilone values in the worst case four: in block l, block r, and on the blocks between l and r inclusive.

## Implementation

In the beginning of the program specified the constant MAXN, LOG_MAXLIST and SQRT_MAXLIST determining the maximum number of vertices in the graph, which if necessary should be increased.

```cpp
const int MAXN = 100*1000;
const int MAXLIST = MAXN * 2;
const int LOG_MAXLIST = 18;
const int SQRT_MAXLIST = 447;
const int MAXBLOCKS = MAXLIST / ((LOG_MAXLIST+1)/2) + 1;

int n, root;
vector<int> g[MAXN];
int h[MAXN]; // vertex height
vector<int> a; // dfs list
int a_pos[MAXN]; // positions in the dfs list
int block; // block size = 0.5 A. log size()
int bt[MAXBLOCKS][LOG_MAXLIST+1]; // sparse table on blocks (relative minimum positions in blocks)
int bhash[MAXBLOCKS]; // block hashes
int brmq[SQRT_MAXLIST][LOG_MAXLIST/2][LOG_MAXLIST/2]; // rmq inside each block, indexed by block hash
int log2[2*MAXN]; // precalced logarithms (floored values)

// walk the graph
void dfs (int v, int curh) {
    h[v] = curh;
    a_pos[v] = (int)a.size();
    a.push_back(v);
    for (size_t i = 0; i < g[v].size(); ++i)
        if (h[g[v][i]] == -1) {
            dfs(g[v][i], curh + 1);
            a.push_back(v);
        }
}

int log (int n) {
    int res = 1;
    while (1 << res < n)
        res++;
    return res;
}

// compares two indices in a
inline int min_h (int i, int j) {
    return h[a[i]] < h[a[j]] ? i : j;
}

// O(N) preprocessing
void build_lca() {
    int sz = (int)a.size();
    block = (log(sz) + 1) / 2;
    int blocks = sz / block + (sz % block ? 1 : 0);

    // precalc in each block and build a sparse table
    memset(bt, 255, sizeof bt);
    for (int i = 0, bl = 0, j = 0; i < sz; ++i, ++j) {
        if (j == block)
            j = 0, ++bl;
        if (bt[bl][0] == -1 || min_h(i, bt[bl][0]) == i)
            bt[bl][0] = i;
    }
    for (int j = 1; j <= log(sz); ++j)
        for (int i = 0; i < blocks; ++i) {
            int ni = i + (1 << (j - 1));
            if (ni >= blocks)
                bt[i][j] = bt[i][j - 1];
            else
                bt[i][j] = min_h(bt[i][j - 1], bt[ni][j - 1]);
        }

    / calc hashes of blocks memset(bhash, 0, sizeof bhash);
    for (int i = 0, bl = 0, j = 0; i < sz || j < block; ++i, ++j) {
        if (j == block)
            j = 0, ++bl;
        if (j > 0 && (i >= sz || min_h(i - 1, i) == i - 1))
            bhash[bl] += 1 << (j - 1);
    }

    // precalc RMQ inside each unique block
    memset(brmq, 255, sizeof brmq);
    for (int i = 0; i < blocks; ++i) {
        int id = bhash[i];
        if (brmq[id][0][0] != -1)
            continue;
        for (int l = 0; l < block; ++l) {
            brmq[id][l][l] = l;
            for (int r = l + 1; r < block; ++r) {
                brmq[id][l][r] = brmq[id][l][r - 1];
                if (i * block + r < sz)
                    brmq[id][l][r] =
                        min_h(i * block + brmq[id][l][r], i * block + r) -
                        i * block;
            }
        }
    }

    // precalc logarithms
    for (int i = 0, j = 0; i < sz; ++i) {
        if (1 << (j + 1) <= i)
            ++j;
        log2[i] = j;
    }
}

// answers RMQ in block #bl [l;r] in O(1)
inline int lca_in_block (int bl, int l, int r) {
    return brmq[bhash[bl]][l][r] + bl * block;
}

// answers LCA in O(1)
int lca (int v1, int v2) {
    int l = a_pos[v1], r = a_pos[v2];
    if (l > r)
        swap(l, r);
    int bl = l / block, br = r / block;
    if (bl == br)
        return a[lca_in_block(bl, l % block, r % block)];
    int ans1 = lca_in_block(bl, l % block, block - 1);
    int ans2 = lca_in_block(br, 0, r % block);
    int ans = min_h(ans1, ans2);
    if (bl < br - 1) {
        int pw2 = log2[br - bl - 1];
        int ans3 = bt[bl + 1][pw2];
        int ans4 = bt[br - (1 << pw2)][pw2];
        ans = min_h(ans, min_h(ans3, ans4));
    }
    return a[ans];
}
```
