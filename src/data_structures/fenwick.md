<!--?title Fenwick Tree -->

# Fenwick Tree

Let, $f$ be some _reversible_ function and $A$ be an array of integers of length $N$.

Fenwick tree is a data structure which:

* calculates the value of function $f$ in the given range $[l; r]$ (i.e. $f(A_l, A_{l+1}, \dots, A_r)$) in $O(\log n)$ time;
* updates the value of an element of $A$ in $O(\log n)$ time;
* requires $O(N)$ memory, or in other words, exactly the same memory required for $A$;
* is easy to use and code, especially, in the case of multidimensional arrays.

Fenwick tree is also called **Binary Indexed Tree**, or just **BIT** abbreviated.

The most common application of Fenwick tree is _calculating the sum of a range_ (i.e. $f(A_1, A_2, \dots, A_k) = A_1 + A_2 + \dots + A_k$).

Fenwick tree was first described in a paper titled "A new data structure for cumulative frequency tables" (Peter M. Fenwick, 1994).

## Description

### Overview

For the sake of simplicity, we will assume that function $f$ is just a *sum function*.

Given an array of integers $A[0 \dots N-1]$. Fenwick tree is an array $T[0 \dots N-1]$, where each of its elements is equal to the sum of elements of $A$ in some range $[g(i); i]$:

$$T_i = \sum_{j = g(i)}^{i}{A_j},$$
where $g$ is some function that satisfies $0 \le g(i) \le i$.
We will define the function in the next few paragraphs.

**Note:** The Fenwick tree presented here uses zero-based indexing.
Many people will actually use a version of the Fenwick tree that uses one-based indexing.
Therefore you will also find an alternative implementation using one-based indexing in the implementation section.
Both versions are equivalent in terms of time and memory complexity.

Now we can write some pseudo-code for the two operations mentioned above - get the sum of elements of $A$ in the range $[0; r]$ and update (increase) some element $A_i$:

```python
def sum(int r):
    res = 0
    while (r >= 0):
        res += t[r]
        r = g(r) - 1
    return res

def inc(int i, int delta):
    for all j, where g(j) <= i <= j
        t[j] += delta
```

The function `sum` works as follows:

1. first, it adds the sum of the range $[g(r); r]$ (i.e. $T[r]$) to the `result`
2. then, it "jumps" to the range $[g(g(r)-1); g(r)-1]$, and adds this range's sum to the `result`
3. and so on, until it "jumps" from $[0; g(g( \dots g(r)-1 \dots -1)-1)]$ to $[g(-1); -1]$; that is where the `sum` function stops jumping.

The function `inc` works with the same analogy, but "jumps" in the direction of increasing indices:

1. sums of the ranges $[g(j); j]$ that satisfy the condition $g(j) \le i \le j$ are increased by `delta` , that is `t[j] += delta`. Therefore we updated all elements in $T$ that corresponds to ranges in with $A_i$ lies.

It is obvious that the complexity of both `sum` and `inc` depend on the function $g$.
There are lots of ways to choose the function $g$, as long as $0 \le g(i) \le i$ for all $i$.
For instance the function $g(i) = i$ works, which results just in $T = A$, and therefore summation queries are slow.
We can also take the function $g(i) = 0$.
This will correspond to prefix sum arrays, which means that finding the sum of the range $[0; i]$ will only take constant time, but updates are slow.
The clever part of the Fenwick algorithm is, that there it uses a special definition of the function $g$ that can handle both operations in $O(\log N)$ time.

### Definition of $g(i)$

The computation of $g(i)$ is defined using the following simple operation:
we replace all trailing $1$ bits in the binary representation of $i$ with $0$ bits.

In other words, if the least significant digit of $i$ in binary is $0$, then $g(i) = i$.
And otherwise the least significant digit is a $1$, and we take this $1$ and all other trailing $1$s and flip them.

For instance we get

$$\begin{align}
g(11) = g(1011_2) = 1000_2 &= 8 \\\\
g(12) = g(1100_2) = 1100_2 &= 12 \\\\
g(13) = g(1101_2) = 1100_2 &= 12 \\\\
g(14) = g(1110_2) = 1110_2 &= 14 \\\\
g(15) = g(1111_2) = 0000_2 &= 0 \\\\
\end{align}$$

There exists a simple implementation using bitwise operations for the non-trivial operation described above:
$$g(i) = i ~\&~ (i+1),$$
where $\&$ is the logical AND operator. It is not hard to convince yourself that this solution does the same thing as the operation described above.

Now, we just need to find a way to iterate over all $j$'s, such that $g(j) \le i \le j$.

It is easy to see that we can find all such $j$'s by starting with $i$ and flipping the last unset bit.
We will call this operation $h(j)$.
For example, for $i = 10$ we have:

$$\begin{align}
10 &= 0001010_2 \\\\
h(10) = 11 &= 0001011_2 \\\\
h(11) = 15 &= 0001111_2 \\\\
h(15) = 31 &= 0011111_2 \\\\
h(31) = 63 &= 0111111_2 \\\\
\vdots &
\end{align}$$

Unsurprisingly, there also exists a simple way to perform $h$ using bitwise operations:
$$h(j) = j ~\|~ (j+1),$$
where $\|$ is the logical OR operator.

The following image shows a possible interpretation of the Fenwick tree as tree.
The nodes of the tree show the ranges they cover.

<center>![Binary Indexed Tree](&imgroot&/img/binary_indexed_tree.png)</center>

## Implementation

### Finding sum in one-dimensional array

Here we present an implementation of the Fenwick tree for sum queries and single updates.

The normal Fenwick tree can only answer sum queries of the type $[0; r]$ using `sum(int r)`, however we can also answer other queries of the type $[l; r]$ by computing two sums $[0; r]$ and $[0; l-1]$ and subtract them.
This is handled in the `sum(int l, int r)` method.

Also this implementation supports two constructors.
You can create a Fenwick tree initialized with zeros, or you can convert an existing array into the Fenwick form.

```cpp
struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};
```

### Finding minimum of $[0; r]$ in one-dimensional array

It is obvious that there is no easy way of finding minimum of range $[l; r]$ using Fenwick tree, as Fenwick tree can only answer queries of type $[0; r]$.
Additionally, each time a value is `update`'d, the new value has to be smaller than the current value (because the $min$ function is not reversible).
These, of course, are significant limitations.

```cpp
struct FenwickTreeMin {
    vector<int> bit;
    int n;
    const int INF = (int)1e9;

    FenwickTreeMin(int n) {
        this->n = n;
        bit.assign(n, INF);
    }

    FenwickTreeMin(vector<int> a) : FenwickTreeMin(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            update(i, a[i]);
    }

    int getmin(int r) {
        int ret = INF;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret = min(ret, bit[r]);
        return ret;
    }

    void update(int idx, int val) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] = min(bit[idx], val);
    }
};
```

Notice: it is possible to implement a Fenwick tree that can handle arbitrary minimum range queries and arbitrary updates.
The paper [Efficient Range Minimum Queries using Binary Indexed Trees](http://ioinformatics.org/oi/pdf/v9_2015_39_44.pdf) describes such an approach.
However with that approach you need to maintain a second binary indexed trees over the data, with a slightly different structure, since you one tree is not enough to store the values of all elements in the array.
The implementation is also a lot harder compared to the normal implementation for sums.

### Finding sum in two-dimensional array

As claimed before, it is very easy to implement Fenwick Tree for multidimensional array.

```cpp
struct FenwickTree2D {
    vector<vector<int>> bit;
    int n, m;

    // init(...) { ... }

    int sum(int x, int y) {
        int ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];
        return ret;
    }

    void add(int x, int y, int delta) {
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1))
                bit[i][j] += delta;
    }
};
```

### One-based indexing approach

For this approach we change the requirements and definition for $T[]$ and $g()$ a little bit.
We want $T[i]$ to store the sum of $[g(i)+1; i]$.
This changes the implementation a little bit, and allows for a similar nice definition for $g(i)$:

```python
def sum(int r):
    res = 0
    while (r > 0):
        res += t[r]
        r = g(r)
    return res

def increase(int i, int delta):
    for all j with g(j) < i <= j:
        t[j] += delta
```

The computation of $g(i)$ is defined as:
toggling of the last set $1$ bit in the binary representation of $i$.

$$\begin{align}
g(7) = g(111_2) = 110_2 &= 6 \\\\
g(6) = g(110_2) = 100_2 &= 4 \\\\
g(4) = g(100_2) = 000_2 &= 0 \\\\
\end{align}$$

The last set bit can be extracted using $i ~\&~ (-i)$, so the operation can be expressed as:
$$g(i) = i - (i ~\&~ (-i).$$

And it's not hard to see, that you need to change all values $T[j]$ in the sequence $i,~ h(i),~ h(h(i)),~ \dots$ when you want to update $A[j]$, where $h(i)$ is defined as:
$$h(i) = i + (i ~\&~ (-i)).$$

As you can see, the main benefit of this approach is that the binary operations complement each other very nicely.

The following implementation can be used like the other implementations, however it uses one-based indexing internally.

```cpp
struct FenwickTreeOneBasedIndexing {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTreeOneBasedIndexing(int n) {
        this->n = n + 1;
        bit.assign(n + 1, 0);
    }

    FenwickTreeOneBasedIndexing(vector<int> a)
        : FenwickTreeOneBasedIndexing(a.size()) {
        init(a.size());
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += delta;
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
* [Codeforces - Thor](https://codeforces.com/problemset/problem/704/A)
* [Latin American Regionals 2017 - Fundraising](http://matcomgrader.com/problem/9346/fundraising/)

### Other sources

* [Fenwick tree on Wikipedia](http://en.wikipedia.org/wiki/Fenwick_tree)
* [Binary indexed trees tutorial on TopCoder](https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/)
