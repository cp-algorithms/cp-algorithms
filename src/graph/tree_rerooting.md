---
tags:
  - Original
---

# Tree Rerooting (All-Roots Dynamic Programming)

In many tree dynamic programming problems, the answer depends on the choice of the root.
If we can compute the dynamic programming solution for one fixed root in $O(n)$, we often can compute the solution for **all** roots in $O(n)$ as well.
This technique is known as **tree rerooting** (or **all-roots dynamic programming**).

Prerequisites: [Introduction to Dynamic Programming](../dynamic_programming/intro-to-dp.md), [Depth-first search on trees](../graph/depth-first-search.md).

Rerooting appears in problems like:

- Compute a value $ans[v]$ for every vertex $v$ as the root.
- Compute a value for every directed edge $(v \to p)$ (sometimes called **edge dynamic programming**).
- Compute “inside-subtree” and “outside-subtree” information for each vertex.

The key operation behind rerooting is:
for a node $v$ and one neighbor $u$, compute the combined contribution of **all neighbors of $v$ except $u$**.
Doing this naively can cost $O(\deg(v)^2)$ per vertex, which is too slow on high-degree nodes.

---

## Two Views of Rerooting

### View 1: “Move the Root Across an Edge”

Assume we have dynamic programming values for a rooted tree. If we change the root from $r$ to an adjacent vertex $v$,
then only the local parent/child relations around the edge $(r, v)$ change.
So if the dynamic programming transition is “local”, we can update the values when moving the root across one edge and traverse the tree with DFS,
rolling changes back when returning from recursion.

<figure style="text-align:center">
  <img src="../graph/tree_rerooting_reroot_step.jpg" alt="Rerooting step" width="520">
  <figcaption><em>Move the root across edge (p, v): only local parent/child directions change.</em></figcaption>
</figure>


However, we must avoid recomputing transitions by iterating over all children every time we move the root,
otherwise the complexity can degrade to roughly $O\!\left(\sum_v \binom{d_v}{2}\right)$ in the worst case (close to $O(n^2)$).

This is why efficient “exclude one neighbor” computations are central.

### View 2: Dynamic Programming on Directed Edges (Recommended)

A clean and common way to write rerooting is to store dynamic programming values on **directed edges**.

For every directed edge $(v \to p)$ define a value:

- $dp[v \to p]$ = the contribution of the component on the $v$-side when the edge $(v,p)$ is cut,
  computed “towards” $p$.

Then the answer for a root $v$ is just the combination of contributions from all neighbors:

$$
ans[v] = \text{AddVertex}\Bigl(\operatorname{Merge}_{u \in adj(v)} \text{ToVertex}(dp[u \to v], u, v),\ v\Bigr).
$$

This formulation leads to a standard **two-pass** algorithm:

1. Compute $dp[child \to parent]$ in a postorder (downward pass).
2. Compute $dp[parent \to child]$ in a preorder (upward pass), using prefix/suffix merges (or another “exclusive” method).

---

## Requirements for the Generic Template

We define a dynamic programming type `T` and the following operations:

- `merge(a, b)` — Associative combination (not necessarily commutative).
- `ID` — Identity element for `merge`.
- `to_vertex(x, from, to)` — Optional edge-dependent transform (often identity).
- `add_vertex(x, v)` — Optional inclusion of vertex $v$ into the result.

This covers most rerooting tasks: sums/products, max/min, counting, etc.

If `merge` is $O(1)$, the rerooting algorithm runs in $O(n)$ time.

### Notes

- The adjacency order is used for prefix/suffix; `merge` only needs to be associative.
- If you need edge weights, store them and use `to_vertex`.
- If you need to account for a vertex value, use `add_vertex`.

---

## Algorithm Using Prefix/Suffix Merges ($O(n)$)

Fix an arbitrary root (say vertex 0). Let:

- `down[v]` = result of the component “below” $v$ w.r.t. the fixed root (children only),
- `up[v]` = contribution coming into $v$ from its parent side,
- `ans[v]` = result for the whole tree when rooted at $v$.

For each vertex $v$, define the neighbor contributions toward $v$:

- From a child $u$: `to_vertex(down[u], u, v)`.
- From the parent: `up[v]`.

Now we want, for every neighbor $u$ of $v$, the merged value of **all neighbor contributions except the one from $u$**.

<figure style="text-align:center">
  <img src="../graph/tree_rerooting_excluding_neighbor.gif" alt="Prefix/suffix exclude one neighbor" width="600">
  <figcaption><em>Prefix/suffix merges let us compute the merge of all neighbors except one.</em></figcaption>
</figure>

We can compute it in $O(\deg(v))$ using prefix/suffix arrays:

- `pref[i]` = Merge of contributions of neighbors `0..i-1`.
- `suf[i]`  = Merge of contributions of neighbors `i..deg-1`.

Then for neighbor index `i`:

$$
\text{without_i} = merge(pref[i],\ suf[i+1]).
$$

This gives the value needed to compute `up[child]`.

### Two-Pass Computation

1. Choose an arbitrary root (e.g. 0) and compute `down[v]` in a postorder:
   for each vertex, merge contributions from children and apply `add_vertex`.

2. Compute `up[v]` and `ans[v]` in a preorder:
   build `contrib[]` for each neighbor, then use prefix/suffix to get the value excluding each neighbor.
   This gives the value to propagate to children and also the final `ans[v]`.

---

## Implementation

The following implementation is a reusable rerooting template for the model above.
You provide:

- `T` (dynamic programming type),
- `ID`,
- `merge(a,b)`,
- `add_vertex(x, v)`,
- `to_vertex(x, from, to)` (often identity).

It computes `down`, `up`, and `ans` for all vertices.

We define the `Rerooting` struct with the graph and DP operations:

```cpp
template <class T, class Merge, class AddVertex, class ToVertex>
struct Rerooting {
    int n;
    vector<vector<int>> g;

    T ID;
    Merge merge;
    AddVertex add_vertex;
    ToVertex to_vertex;

    vector<int> parent, order;
    vector<T> down, up, ans;

    Rerooting(int n, T ID, Merge merge, AddVertex add_vertex, ToVertex to_vertex)
        : n(n), g(n),
          ID(ID), merge(merge), add_vertex(add_vertex), to_vertex(to_vertex),
          parent(n, -1), down(n, ID), up(n, ID), ans(n, ID) {}

    void add_edge(int a, int b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }
    // ... build() method below
};
```

The `build()` method performs the two-pass computation. First, we build the parent array and traversal order:

```cpp
void build(int root = 0) {
    order.clear();
    fill(parent.begin(), parent.end(), -1);

    // Build parent[] and traversal order
    stack<int> st;
    st.push(root);
    parent[root] = root;
    while (!st.empty()) {
        int v = st.top();
        st.pop();
        order.push_back(v);
        for (int u : g[v]) if (u != parent[v]) {
            parent[u] = v;
            st.push(u);
        }
    }
```

Next, we compute `down[v]` in postorder (from leaves to root):

```cpp
    // Downward pass: compute down[v] from children only
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int v = order[i];
        T acc = ID;
        for (int u : g[v]) if (u != parent[v]) {
            acc = merge(acc, to_vertex(down[u], u, v));
        }
        down[v] = add_vertex(acc, v);
    }
```

Finally, we reroot using prefix/suffix merges to compute `up[]` and `ans[]`:

```cpp
    // Reroot: compute up[] and ans[] using prefix/suffix merges
    up[root] = ID;

    for (int v : order) {
        int deg = (int)g[v].size();
        vector<T> contrib(deg);

        for (int i = 0; i < deg; i++) {
            int u = g[v][i];
            if (u == parent[v]) contrib[i] = up[v];
            else                contrib[i] = to_vertex(down[u], u, v);
        }

        vector<T> pref(deg + 1, ID), suf(deg + 1, ID);
        for (int i = 0; i < deg; i++) pref[i + 1] = merge(pref[i], contrib[i]);
        for (int i = deg - 1; i >= 0; i--) suf[i] = merge(contrib[i], suf[i + 1]);

        ans[v] = add_vertex(pref[deg], v);

        for (int i = 0; i < deg; i++) {
            int u = g[v][i];
            if (u == parent[v]) continue;

            T without_u = merge(pref[i], suf[i + 1]);
            T v_towards_u = add_vertex(without_u, v);
            up[u] = to_vertex(v_towards_u, v, u);
        }
    }
}
```

**Usage example:**

```cpp
struct T { /* your DP state */ };
T ID = /* identity */;
auto merge = [&](const T& a, const T& b) -> T { /* ... */ };
auto add_vertex = [&](const T& x, int v) -> T { /* ... */ };
auto to_vertex = [&](const T& x, int from, int to) -> T { /* ... */ };

Rerooting<T, decltype(merge), decltype(add_vertex), decltype(to_vertex)>
    rr(n, ID, merge, add_vertex, to_vertex);

rr.add_edge(a, b);
rr.build(0);
// answers are in rr.ans[v]
```

---

## Applications

### Maximum Distance to Any Node (Tree Eccentricities)

For each node $x$, we want:

$$
ans[x] = \max_{y} dist(x, y).
$$

**Approach.** Compute the best depth inside each subtree with one DFS, then do a second DFS to propagate the best value from the parent side using the best and second-best child contributions.

A classical reroot solution uses two dynamic programming arrays:

- $f[x]$ = max distance from $x$ to any node in the subtree rooted at $x$,
- $g[x]$ = max distance from $x$ to any node outside that subtree,
- then $ans[x] = \max(f[x], g[x])$.

We can compute $f$ by a DFS using the transition:

$$
f[x] = 1 + \max_{c \in children(x)} f[c].
$$

To compute $g$ efficiently, we need, for each child $c$ of $x$, the best “sibling alternative” (the best subtree of $x$ excluding $c$).
One way is to store the largest and second largest child depths for every node (or equivalently compute an “exclude-one-child” maximum).
Then:

- if child $c$ is the one that gave the maximum for $f[x]$, use the second maximum,
- otherwise use the maximum.

This exactly matches the “two arrays / inside vs outside” technique.

Implementation idea:

- first DFS: compute `best1[x]`, `best2[x]` = top two values of `f[child] + 1`,
- second DFS: compute `g[child] = max(g[x] + 1, best_except_child + 1)`.

(You can also code it with the generic reroot template by letting `merge = max`.)

---

### Sum of Distances from Every Node

Compute for every vertex $v$:

$$
ans[v] = \sum_{u=0}^{n-1} dist(v,u).
$$

**Approach.** First compute `sz[v]` and `sub[v]` with one DFS, then reroot using the formula $ans[c] = ans[p] + n - 2\cdot sz[c]$ to propagate answers to children.

A standard two-step rerooting approach:

Root at 0 and compute:

- `sz[v]` = size of subtree of $v$,
- `sub[v]` = sum of distances from $v$ to nodes in its subtree.

Transitions:

$$
sz[v] = 1 + \sum_{c} sz[c]
$$

$$
sub[v] = \sum_{c}\bigl(sub[c] + sz[c]\bigr)
$$

because every node in child subtree is 1 farther from $v$ than from $c$.

Now reroot:
If we move root from parent $p$ to child $c$, then distances to nodes in $c$'s subtree decrease by 1,
and distances to all other nodes increase by 1:

$$
ans[c] = ans[p] - sz[c] + (n - sz[c]) = ans[p] + n - 2 \cdot sz[c].
$$

Compute `ans[0] = sub[0]` then DFS to propagate.

---

## Practice Problems

These are the most common reroot patterns:

1. [CSES — Tree Distances II](https://cses.fi/problemset/task/1133)
2. [Codeforces — 1187E “Tree Painting”](https://codeforces.com/problemset/problem/1187/E)
3. [Codeforces — 219D “Choosing Capital for Treeland”](https://codeforces.com/problemset/problem/219/D)
4. [Codeforces — 543D “Road Improvement”](https://codeforces.com/problemset/problem/543/D)
5. [AtCoder DP Contest — V “Subtree”](https://atcoder.jp/contests/dp/tasks/dp_v?lang=en)
6. [Library Checker — Tree Path Composite Sum](https://judge.yosupo.jp/problem/tree_path_composite_sum)

---

## Advanced Note: Queries with Changing Root

Sometimes queries ask for a value “result for $v$ when the tree is rooted at $r$”.
A common approach is:

- Precompute rerooting values for each directed edge $(u \to v)$,
- Combine it with [LCA](lca.md) / [binary lifting](lca_binary_lifting.md) to determine which neighbor of $v$ lies on the path to $r$,
  reducing each query to a constant number of precomputed directed-edge lookups.

(Only needed when the root changes per query.)
