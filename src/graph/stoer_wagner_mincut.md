---
tags:
  - Translated
e_maxx_link: stoer_wagner_mincut
---

# Minimum cut - Stoer-Wagner algorithm

## Problem statement

Given an undirected weighted graph $G$ with $n$ vertices and $m$ edges. A cut $C$ is a non-empty proper subset of the vertices (effectively, a cut is a partition of the vertices into two non-empty sets: the ones belonging to $C$ and all the others). The weight of a cut is the sum of the weights of the edges crossing the cut, i.e. the edges that have exactly one endpoint in $C$:

$$ w(C) = \sum_{\substack{(v,u) \in E \\ u \in C,\ v \not\in C}} c(v,u), $$

where $E$ denotes the set of all edges of the graph $G$, and $c(v,u)$ is the weight of the edge $(v,u)$.

The task is to find a **cut of minimum weight**.

Sometimes this problem is called the "global minimum cut" — in contrast to the problem where a source vertex and a sink vertex are given, and we have to find a minimum cut $C$ containing the sink but not the source. The global minimum cut equals the minimum among the minimum-cost cuts over all possible source-sink pairs.

Although this problem can be solved with a maximum flow algorithm (by running it $O(n^2)$ times for all possible pairs of source and sink), below we describe a much simpler and faster algorithm, proposed by Mechthild Stoer and Frank Wagner in 1994.

In general, loops and multiple edges are allowed, although loops obviously do not influence the result in any way, and multiple edges can always be replaced by a single edge with their combined weight. Therefore, for simplicity, we will assume that the input graph contains no loops or multiple edges.

## Description of the algorithm

The **basic idea** of the algorithm is very simple. We iteratively repeat the following process: find the minimum cut between some pair of vertices $s$ and $t$, and then merge these two vertices into one (connecting their adjacency lists). Eventually, after $n-1$ iterations, the graph will be compressed into a single vertex and the process stops. After that, the answer is the minimum among all $n-1$ cuts found. Indeed, at every $i$-th stage, the found minimum cut $C_i$ between the vertices $s_i$ and $t_i$ either turns out to be the desired global minimum cut, or, on the contrary, it is disadvantageous to put $s_i$ and $t_i$ into different sets, so we do not worsen anything by merging these two vertices into one.

Thus we reduced the problem to the following one: for a given graph, find the **minimum cut between some, arbitrary, pair of vertices** $s$ and $t$. To solve this problem, the following, also iterative, process was proposed. We introduce a set of vertices $A$, which initially contains a single arbitrary vertex. At every step, we find the vertex **most strongly connected** to the set $A$, i.e. the vertex $v \not\in A$ for which the following quantity is maximal:

$$ w(v,A) = \sum_{\substack{(v,u) \in E \\ u \in A}} c(v,u) $$

(i.e. the sum of the weights of the edges with one endpoint at $v$ and the other in $A$ is maximal).

Again, this process terminates after $n-1$ iterations, when all vertices have moved into the set $A$ (incidentally, this process strongly resembles [Prim's algorithm](mst_prim.md)). Then, as the **Stoer-Wagner theorem** states, if we denote by $s$ and $t$ the last two vertices added to $A$, the minimum cut between the vertices $s$ and $t$ consists of a single vertex — $t$. The proof of this theorem will be given in the next section (as is often the case, by itself it does not contribute to the understanding of the algorithm in any way).

Thus the overall **scheme of the Stoer-Wagner algorithm** is as follows. The algorithm consists of $n-1$ phases. In every phase, the set $A$ is initially set to contain some vertex, and the starting weights $w(v,A)$ of the vertices are computed. Then $n-1$ iterations follow, in each of which the vertex $u$ with the largest value $w(v,A)$ is chosen and added to the set $A$, after which the values of $w$ for the remaining vertices are recalculated (for which, obviously, we have to go through all the edges in the adjacency list of the selected vertex $u$). After performing all the iterations, we record in $s$ and $t$ the last two added vertices, and the value $w(t,A \setminus t)$ can be taken as the cost of the found minimum cut between $s$ and $t$. Then we compare the found minimum cut with the current answer, and if it is smaller, we update the answer, and proceed to the next phase.

If we do not use any sophisticated data structures, the most critical part is finding the vertex with the largest value of $w$. If we do this in $O(n)$, then, given that there are $n-1$ phases with $n-1$ iterations each, the resulting **complexity of the algorithm** is $O(n^3)$.

If we use **Fibonacci heaps** for finding the vertex with the largest value of $w$ (which allow increasing the value of a key in $O(1)$ amortized and extracting the maximum in $O(\log n)$ amortized), then all operations related to the set $A$ in one phase are performed in $O(m + n \log n)$. The resulting complexity of the algorithm in this case is $O(n m + n^2 \log n)$.

## Proof of the Stoer-Wagner theorem

Let us recall the statement of this theorem. If we add all the vertices to the set $A$ one by one, every time adding the vertex most strongly connected to this set, then denote the second-to-last added vertex by $s$ and the last one by $t$. Then the minimum $s$-$t$ cut consists of a single vertex — $t$.

To prove it, consider an arbitrary $s$-$t$ cut $C$ and show that its weight cannot be less than the weight of the cut consisting of the single vertex $t$:

$$ w(\{t\}) \le w(C). $$

To do this, we prove the following fact. Let $A_v$ be the state of the set $A$ immediately before adding the vertex $v$. Let $C_v$ be the cut of the set $A_v \cup \{v\}$ induced by the cut $C$ (simply put, $C_v$ equals the intersection of these two sets of vertices). Further, a vertex $v$ is called active (with respect to the cut $C$) if the vertex $v$ and the previously added vertex belong to different parts of the cut $C$. Then, we claim, for any active vertex $v$ the following inequality holds:

$$ w(v,A_v) \le w(C_v). $$

In particular, $t$ is an active vertex (since the vertex added before it was $s$), and for $v = t$ this inequality turns into the statement of the theorem:

$$ w(t,A_t) = w(\{t\}) \le w(C_t) = w(C). $$

So, we will prove this inequality using mathematical induction.

For the first active vertex $v$ the inequality holds (moreover, it turns into an equality) — since all vertices of $A_v$ belong to one part of the cut, and $v$ belongs to the other.

Now suppose this inequality holds for all active vertices up to some vertex $v$; let us prove it for the next active vertex $u$. To do this, transform the left-hand side:

$$ w(u,A_u) \equiv w(u,A_v) + w(u,A_u \setminus A_v). $$

First, note that:

$$ w(u,A_v) \le w(v,A_v), $$

which follows from the fact that when the set $A$ was equal to $A_v$, the vertex added to it was precisely $v$ and not $u$, which means it had the largest value of $w$.

Further, since $w(v,A_v) \le w(C_v)$ by the induction hypothesis, we obtain:

$$ w(u,A_v) \le w(C_v), $$

from which we have:

$$ w(u,A_u) \le w(C_v) + w(u,A_u \setminus A_v). $$

Now note that the vertex $u$ and all vertices of $A_u \setminus A_v$ are in different parts of the cut $C$, so the quantity $w(u,A_u \setminus A_v)$ denotes the sum of the weights of the edges that are counted in $w(C_u)$ but were not yet counted in $w(C_v)$, from which we get:

$$ w(u,A_u) \le w(C_v) + w(u,A_u \setminus A_v) \le w(C_u), $$

as required.

We have proven the relation $w(v,A_v) \le w(C_v)$, and, as mentioned above, the whole theorem follows from it.

## Implementation

For the simplest and clearest implementation (with $O(n^3)$ complexity), the graph is represented as an adjacency matrix. The answer is stored in the variables `best_cost` and `best_cut` (the cost of the minimum cut and the vertices contained in it).

For every vertex, the array `exist` stores whether it still exists, or whether it has been merged with some other vertex. The list `v[i]` for every compressed vertex $i$ stores the numbers of the original vertices that were compressed into this vertex $i$.

The algorithm consists of $n-1$ phases (the loop over the variable `ph`). In every phase, all vertices are initially outside the set $A$, so the array `in_a` is filled with zeros, and the connectivities $w$ of all vertices are zero. In each of the $n-\mathrm{ph}$ iterations, the vertex `sel` with the largest value of $w$ is found. If this is the last iteration, the answer is updated if necessary, and the second-to-last `prev` and the last `sel` selected vertices are merged into one. If the iteration is not the last one, then `sel` is added to the set $A$, after which the weights of all the remaining vertices are recalculated.

Note that the algorithm "spoils" the graph `g` during its work, so if you still need it later, you have to save a copy of it before calling the function.

```{.cpp file=stoer_wagner_mincut}
const int MAXN = 500;
int n;
long long g[MAXN][MAXN];
long long best_cost = (1LL << 62);
vector<int> best_cut;

void mincut() {
    vector<int> v[MAXN];
    for (int i = 0; i < n; ++i)
        v[i].assign(1, i);
    long long w[MAXN];
    bool exist[MAXN], in_a[MAXN];
    memset(exist, true, sizeof exist);
    for (int ph = 0; ph < n - 1; ++ph) {
        memset(in_a, false, sizeof in_a);
        memset(w, 0, sizeof w);
        for (int it = 0, prev; it < n - ph; ++it) {
            int sel = -1;
            for (int i = 0; i < n; ++i)
                if (exist[i] && !in_a[i] && (sel == -1 || w[i] > w[sel]))
                    sel = i;
            if (it == n - ph - 1) {
                if (w[sel] < best_cost) {
                    best_cost = w[sel];
                    best_cut = v[sel];
                }
                v[prev].insert(v[prev].end(), v[sel].begin(), v[sel].end());
                for (int i = 0; i < n; ++i)
                    g[prev][i] = g[i][prev] += g[sel][i];
                exist[sel] = false;
            } else {
                in_a[sel] = true;
                for (int i = 0; i < n; ++i)
                    w[i] += g[sel][i];
                prev = sel;
            }
        }
    }
}
```

## Literature

- [Mechthild Stoer, Frank Wagner. A Simple Min-Cut Algorithm [1997]](https://doi.org/10.1145/258533.258594)
- [Kurt Mehlhorn, Christian Uhrig. The minimum cut algorithm of Stoer and Wagner [1995]](https://domino.mpi-inf.mpg.de/intranet/ag1/ag1publ.nsf/0/a594ac2b8911e869c12564b50067afe1?OpenDocument)
