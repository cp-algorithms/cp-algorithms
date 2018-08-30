<!--?title Fenwick Tree -->

# Fenwick Tree

Let, $f$ be some _reversible_ function and $A$ be an array of integers of length $N$.

Fenwick tree is a data structure which:

* calculates the value of function $f$ in the given range $[l; r]$ (i.e. $f(A_l, A_{l+1}, \dots, A_r)$) in $O(lg\ n)$ time;
* updates the value of an element of $A$ in $O(lg\ n)$ time;
* requires $O(N)$ memory, or in other words, exactly the same memory required for $A$;
* is easy to use and code, especially, in the case of multidimensional arrays.

> Fenwick tree is also called Binary Indexed Tree.

The most common application of Fenwick tree is _calculating the sum of a range_ (i.e. $f(A_1, A_2, \dots, A_k) = A_1 + A_2 + \dots + A_k$).

Fenwick tree was first described in a paper titled "A new data structure for cumulative frequency tables" (Peter M. Fenwick, 1994).

### Description

For the sake of simplicity, we will assume that function $f$ is just a *sum function*.

Given an array of integers $A[0 \dots N-1]$. Fenwick tree is an array $T[0 \dots N-1]$, where each of its elements is equal to the sum of elements of $A$ in some range $[g(i); i]$:

$$T_i = \sum_{j = g(i)}^{i}{A_j}$$

where $g$ is some function that satisfies $(g(i) \le i)$ and we will define it a bit later.

> **Note:** Fenwick tree presented here **does support** 0-based indexing (in case you were told that it does not support it).

Now we can write pseudo-code for the two operations mentioned above &mdash; get the sum of elements of $A$ in range $[0; r]$ and update some element $A_i$:

```python
def sum (int r):
    res = 0
    while (r >= 0):
        res += t[r]
        r = g(r) - 1
    return res

def inc (int i, int delta):
    for all j, where g(j) <= i <= j
        t[j] += delta
```

The function `sum` works as follows:

1. first, it adds the sum of the range $[g(r); r]$ (i.e. $T[r]$) to the `result`
2. then, it "jumps" to the range $[g(g(r)-1); g(r)-1]$, and adds this range's sum to the `result`
3. and so on, until it "jumps" from $[0; g(g( \dots g(r)-1 \dots -1)-1)]$ to $[g(-1); -1]$; that is where the `sum` function stops jumping.

The function `inc` works with the same analogy, but "jumps" in the direction of increasing indices:

1. sums of the ranges $[g(j); j]$ that satisfy the condition $g(j) \le i \le j$ are increased by `delta` , that is `t[j] += delta` .

It is obvious that complexity of both `sum` and `inc` do depend on the function $g$. We will define the function $g$ in such a way that both of the operations have a logarithmic complexity $O(lg N)$.

**Definition of $g(i)$.** Let us consider the least significant digit of $i$ in binary. If this digit is $0$, then let $g(i) = i$. Otherwise, the binary representation of $i$ will end with at least one $1$ bit. We will flip all these tailing $1$'s (so they become $0$'s) and define the result as a value of $g(i)$.

There exists a trivial solution for the non-trivial operation described above:

```
g(i) = i & (i+1)
```

where `&` is a logical AND operator. It is not hard to convince yourself that this solution does the same thing as the operation described above.

Now, we need to find a way to find all $j$'s, such that *g(j) <= i <= j*.

It is easy to see that we can find all such $j$'s by starting with $i$ and flipping the least significant zero bit. For example, for $i = 10$ we have:

```
j = 10, binary 0001010
j = 11, binary 0001011
j = 15, binary 0001111
j = 31, binary 0011111
j = 63, binary 0111111
...
```

Unsurprisingly, there also exists a simple way to do the above operation:

```
h(j) = j | (j+1)
```

where `|` is a logical OR operator.

### Implementation: finding sum in one-dimensional array

```cpp
struct FenwickTree {
    vector<int> bit; // binary indexed tree
    int n;

    void init(int n) {
        this->n = n;
        bit.assign(n, 0);
    }
    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r+1)) - 1)
            ret += bit[r];
        return ret;
    }
    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx+1))
            bit[idx] += delta;
    }
    int sum(int l, int r) {
        return sum(r) - sum(l-1);
    }
    void init(vector<int> a) {
        init(a.size());
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }
};
```

### Implementation: finding minimum of $[0; r]$ in one-dimensional array

It is obvious that there is no way of finding minimum of range $[l; r]$ using Fenwick tree, as Fenwick tree can only answer queries of type [0; r]. Additionally, each time a value is `update`'d, new value should be smaller than the current value (because, the $min$ function is not reversible). These, of course, are significant limitations.

```cpp
struct FenwickTreeMin {
    vector<int> bit;
    int n;
    const int INF = (int)1e9;
    void init (int n) {
        this->n = n;
        bit.assign (n, INF);
    }
    int getmin (int r) {
        int ret = INF;
        for (; r >= 0; r = (r & (r+1)) - 1)
            ret = min(ret, bit[r]);
        return ret;
    }
    void update (int idx, int val) {
        for (; idx < n; idx = idx | (idx+1))
            bit[idx] = min(bit[idx], val);
    }
    void init (vector<int> a) {
        init (a.size());
        for (size_t i = 0; i < a.size(); i++)
            update(i, a[i]);
    }
};
```

### Implementation: finding sum in two-dimensional array

As claimed before, it is easy to implement Fenwick Tree for multidimensional array.

```cpp
struct FenwickTree2D {
    vector <vector <int> > bit;
    int n, m;
    // init(...) { ... }
    int sum (int x, int y) {
        int ret = 0;
        for (int i = x; i >= 0; i = (i & (i+1)) - 1)
            for (int j = y; j >= 0; j = (j & (j+1)) - 1)
                ret += bit[i][j];
        return ret;
    }
    void add(int x, int y, int delta) {
        for (int i = x; i < n; i = i | (i+1))
            for (int j = y; j < m; j = j | (j+1))
                bit[i][j] += delta;
    }
};
```

## Practice Problems

* [UVA 12086 - Potentiometers](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3238)
* [LOJ 1112 - Curious Robin Hood](http://www.lightoj.com/volume_showproblem.php?problem=1112)
* [LOJ 1266 - Points in Rectangle](http://www.lightoj.com/volume_showproblem.php?problem=1266 "2D Fenwick Tree")
* [Codechef - SPREAD](http://www.codechef.com/problems/SPREAD)
* [SPOJ - CTRICK](http://www.spoj.com/problems/CTRICK/)
* [SPOJ - MATSUM](http://www.spoj.com/problems/MATSUM/)
* [SPOJ - DQUERY](http://www.spoj.com/problems/DQUERY/)
* [SPOJ - NKTEAM](http://www.spoj.com/problems/NKTEAM/)
* [SPOJ - YODANESS](http://www.spoj.com/problems/YODANESS/)
* [SRM 310 - FloatingMedian](https://community.topcoder.com/stat?c=problem_statement&pm=6551&rd=9990)
* [SPOJ - Ada and Behives](http://www.spoj.com/problems/ADABEHIVE/)
* [Hackerearth - Counting in Byteland](https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/counting-in-byteland/)
* [DevSkills - Shan and String](https://devskill.com/CodingProblems/ViewProblem/300)
* [Codeforces - Little Artem and Time Machine](http://codeforces.com/contest/669/problem/E)
* [Codeforces - Hanoi Factory](http://codeforces.com/contest/777/problem/E)
* [SPOJ - Tulip and Numbers](http://www.spoj.com/problems/TULIPNUM/)
* [SPOJ - SUMSUM](http://www.spoj.com/problems/SUMSUM/)
* [SPOJ - Sabir and Gifts](http://www.spoj.com/problems/SGIFT/)
* [SPOJ - The Permutation Game Again](http://www.spoj.com/problems/TPGA/)
* [SPOJ - Zig when you Zag](http://www.spoj.com/problems/ZIGZAG2/)
* [SPOJ - Cryon](http://www.spoj.com/problems/CRAYON/)
* [SPOJ - Weird Points](http://www.spoj.com/problems/DCEPC705/)
* [SPOJ - Its a Murder](http://www.spoj.com/problems/DCEPC206/)
* [SPOJ - Bored of Suffixes and Prefixes](http://www.spoj.com/problems/KOPC12G/)
* [SPOJ - Mega Inversions](http://www.spoj.com/problems/TRIPINV/)
* [Codeforces - Subsequences](http://codeforces.com/contest/597/problem/C)
* [Codeforces - Ball](http://codeforces.com/contest/12/problem/D)
* [GYM - The Kamphaeng Phet's Chedis](http://codeforces.com/gym/101047/problem/J)
* [Codeforces - Garlands](http://codeforces.com/contest/707/problem/E)
* [Codeforces - Inversions after Shuffle](http://codeforces.com/contest/749/problem/E)
* [GYM - Cairo Market](http://codeforces.com/problemset/gymProblem/101055/D)
* [Codeforces - Goodbye Souvenir](http://codeforces.com/contest/849/problem/E)
* [SPOJ - Ada and Species](http://www.spoj.com/problems/ADACABAA/)

### Other sources

* [Fenwick tree on Wikipedia](http://en.wikipedia.org/wiki/Fenwick_tree)  
* [Binary indexed trees tutorial on TopCoder](https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/)
