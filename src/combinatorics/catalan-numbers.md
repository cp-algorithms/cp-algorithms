<!--?title Catalan Numbers and its Applications -->

# Catalan Numbers
Catalan numbers is a number sequence, which is found useful in a number of combinatorial problems, often involving recursively-defined objects.

This sequence was named after the Belgian mathematician [Catalana](https://en.wikipedia.org/wiki/Eug%C3%A8ne_Charles_Catalan), who lived in the 19th century. (In fact it was known before to Euler, who lived a century before Catalana).

The first few numbers Catalan numbers, $C_n$ (starting from zero):

 $1, 1, 2, 5, 14, 42, 132, 429, 1430, \ldots$

### Application in some Combinatorial problems

The Catalan number $C_n$ is the solution for

- Number of correct bracket sequence consisting of $n$ opening and $n$ closing brackets.
- The number of rooted full binary trees with $n + 1$ leaves (tops are not numbered). A rooted binary tree is full if every vertex has either two children or no children.
- The number of ways to completely parenthesize $n + 1$ factors.
- The number of triangulations of a convex polygon with $n + 2$ sides (i.e. the number of partitions of polygon into disjoint triangles by using the diagonals).
- The number of ways to connect the $2n$ points on a circle to form $n$ disjoint chords.
- The number of [non-isomorphic](https://en.wikipedia.org/wiki/Graph_isomorphism) full binary trees with $n$ internal nodes (i.e. nodes having at least one son).
- The number of monotonic lattice paths from point $(0, 0)$ to point $(n, n)$ in a square lattice of size $n \times n$, which do not pass above the main diagonal (i.e. connecting $(0, 0)$ to $(n, n)$).
- Number of permutations of length $n$ that can be [stack sorted](https://en.wikipedia.org/wiki/Stack-sortable_permutation) (i.e. it can be shown that the rearrangement is stack sorted if and only if there is no such index $i < j < k$, such that $a_k < a_i < a_j$ ).
- The number of [non-crossing partitions](https://en.wikipedia.org/wiki/Noncrossing_partition) of a set of $n$ elements.
- The number of ways to cover the ladder $1 \ldots n$ using $n$ rectangles (The ladder consists of $n$ columns, where $i^{th}$ column has a height $i$).


## Calculations

There are two formulas for the Catalan numbers: **Recursive and Analytical**. Since, we believe that all the mentioned above problems are equivalent (have the same solution), for the proof of the formulas below we will choose the task which it is easiest to do.

### Recursive formula
 $$C_0 = C_1 = 1$$
 $$C_n = \sum_{k = 0}^{n-1} C_k C_{n-1-k} , {n} \geq 2$$

The recurrence formula can be easily deduced from the problem of the correct bracket sequence.

The leftmost opening parenthesis $l$ corresponds to certain closing bracket $r$, which divides the sequence into 2 parts which in turn should be a correct sequence of brackets. Thus formula is also divided into 2 parts. If we denote $k = {r - l - 1}$, then for fixed $r$, there will be exactly $C_k C_{n-1-k}$ such bracket sequences. Summing this over all admissible $k's$, we get the recurrence relation on $C_n$.

You can also think it in this manner. By definition, $C_n$ denotes number of correct bracket sequences. Now, the sequence may be divided into 2 parts of length $k$ and ${n - k}$, each of which should be a correct bracket sequence. Example :

$( ) ( ( ) )$ can be divided into $( )$ and $( ( ) )$, but cannot be divided into $( ) ($ and $( ) )$. Again summing over all admissible $k's$, we get the recurrence relation on $C_n$.

#### C++ implementation <span class="toggle-code">Show/Hide</span>

```cpp
const int MOD = ....
const int MAX = ....
int catalan[MAX];
void init() {
    catalan[0] = catalan[1] = 1;
    for (int i=2; i<=n; i++) {
        catalan[i] = 0;
        for (int j=0; j < i; j++) {
            catalan[i] += (catalan[j] * catalan[i-j-1]) % MOD;
            if (catalan[i] >= MOD) {
                catalan[i] -= MOD;
            }
        }
    }
}
```

###Analytical formula
 $$C_n = \frac{1}{n + 1} C_{2n}^{n}$$

(here $C_{n}^{k}$ denotes the usual binomial coefficient, i.e. number of ways to select $k$ objects from set of $n$ objects).

The above formula can be easily concluded from the problem of the monotonic paths in square grid. The total number of  monotonic paths in the lattice size of $n \times n$ is given by $C_{2n}^{n}$.

Now we count the number of monotonic paths which cross the main diagonal. Consider such paths crossing the main diagonal and find the first edge in it which is above the diagonal. Reflect the path about the diagonal all the way, going after this edge. The result is always a monotonic path in the grid $(n - 1) \times (n + 1)$. On the other hand, any monotonic path in the lattice $(n - 1) \times (n + 1)$ must intersect the diagonal. Hence, we enumerated all monotonic paths crossing the main diagonal in the lattice $n \times n$.

The number of monotonic paths in the lattice $(n - 1) \times (n + 1)$ are $C_{2n}^{n-1}$ . Let us call such paths as "bad" paths. As a result, to obtain the number of monotonic paths which do not cross the main diagonal, we subtract the above "bad" paths, obtaining the formula:

 $$C_n = C_{2n}^{n} - C_{2n}^{n-1} = \frac{1}{n + 1} C_{2n}^{n} , {n} \geq 0$$

## Practice Problems
- [Codechef - PANSTACK](https://www.codechef.com/APRIL12/problems/PANSTACK/)
- [Spoj - Skyline](http://www.spoj.com/problems/SKYLINE/)
- [UVA - Safe Salutations](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=932)
- [Codeforces - How many trees?](http://codeforces.com/problemset/problem/9/D)
- [SPOJ - FUNPROB](http://www.spoj.com/problems/FUNPROB/)
