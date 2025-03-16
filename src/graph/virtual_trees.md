---
title: Virtual Trees
tags:
    - Original
    
---

This article explores the concept of *virtual trees*, proves their key properties, describes an efficient algorithm for their construction, and then applies the method to solve a specific problem using dynamic programming (DP) on trees.

## Introduction

Many tree-related problems require working with a subset of vertices while preserving the tree structure induced by their pairwise lowest common ancestors (LCA). The concept of a *virtual tree* allows us to transition from the original tree $T$ with $N$ vertices to a substructure whose size linearly depends on the size of the selected set $X$. This significantly accelerates algorithms, particularly for DP computations.

## Definition of a Virtual Tree

Let $T$ be a given rooted tree, and $X$ be some subset of its vertices. A **virtual tree** $A(X)$ is defined as follows:

$$ A(X) = \{ \operatorname{lca}(x,y) \mid x,y \in X \},$$

where $\operatorname{lca}(x,y)$ denotes the lowest common ancestor of vertices $x$ and $y$ in tree $T$. In this tree, an edge is drawn between each pair of vertices if one of them is an ancestor of the other in $T$.

This definition ensures that the structure includes all vertices "important" for analyzing $X$ (i.e., all LCAs for pairs of vertices from $X$), and connectivity is inherited from the original tree.

## Key Properties and Their Proofs

### Property 1: Size Estimation

**Statement.**  
For any set $X$ of vertices of tree $T$, the following inequality holds:

$$
\vert A(X) \vert \le 2 \vert X \vert - 1.
$$

**Proof.**  
Let's choose a depth-first search (DFS) traversal order and consider the vertices of set $X$ arranged in traversal order: 

$$ x_1, x_2, \dots, x_m. $$

Denote

$$ l = \operatorname{lca}(x_1, x_2). $$

We need to prove the following lemma.

!!! note "Lemma 1. For any integer $n \ge 3$, if $\operatorname{lca}(x_1,x_n) \neq l$, then $\operatorname{lca}(x_1,x_n) = \operatorname{lca}(x_2,x_n).$"
    **Proof (by contradiction).**  
    Suppose that for some $n \ge 3$, both $\operatorname{lca}(x_1,x_n) \neq l$ and $\operatorname{lca}(x_1,x_n) \neq \operatorname{lca}(x_2,x_n)$ are true. Let $k = \operatorname{lca}(x_1,x_n)$.  
    If $k$ is an ancestor of $l$, then by definition both $\operatorname{lca}(x_1,x_n)$ and $\operatorname{lca}(x_2,x_n)$ equal $k$, which contradicts our assumption. Therefore, $k$ must be a descendant of $l$. But then in the DFS order, we would get the sequence $x_1, x_n, x_2$, which contradicts our chosen traversal order.  
    This contradiction completes the proof of the lemma.

Returning to the proof of the property, we note that according to the lemma, each LCA arising from sequential consideration of the vertices in $X$ equals either:
1. the vertex $x_1$ itself,
2. $\operatorname{lca}(x_1,x_2)$, or
3. $\operatorname{lca}(x_2,x_n)$ for some $n$.

Thus, we can recursively write:

$$
A(\{x_1,\dots,x_m\}) = A(\{x_2,\dots,x_m\}) \cup \{ x_1, \operatorname{lca}(x_1,x_2) \}.
$$

From this, it follows that

$$
\vert A(X) \vert \le \vert A(\{x_2,\dots,x_m\}) \vert + 2.
$$

Applying induction on the size of set $X$, we obtain the final estimate:

$$
\vert A(X) \vert \le 2 \vert X \vert - 1.
$$

Moreover, if tree $T$ is a perfect binary tree and $X$ consists of its leaves, the inequality is achieved exactly.

### Property 2: Representation through Sequential LCAs

**Statement.**  
Let the vertices of $X$ be ordered by DFS traversal order: $x_1, x_2, \dots, x_m$. Then

$$
A(X) = X \cup \{ \operatorname{lca}(x_i, x_{i+1}) \mid 1 \le i < m \}.
$$

**Proof.**  
We start with the recursive representation:

$$
A(\{x_1,\dots,x_m\}) = A(\{x_2,\dots,x_m\}) \cup \{ x_1, \operatorname{lca}(x_1,x_2) \}.
$$

Let's expand it recursively:

$$
\begin{aligned}
A(\{x_1,\dots,x_m\}) &= A(\{x_2,\dots,x_m\}) \cup \{ x_1, \operatorname{lca}(x_1,x_2) \} \\
&= A(\{x_3,\dots,x_m\}) \cup \{ x_1, \operatorname{lca}(x_1,x_2), x_2, \operatorname{lca}(x_2,x_3) \} \\
&\quad \vdots \\
&= \{ x_1, \operatorname{lca}(x_1,x_2), x_2, \dots, x_{m-1}, \operatorname{lca}(x_{m-1},x_m), x_m \}.
\end{aligned}
$$

Thus, we obtain the required representation.

## Construction of a Virtual Tree

Given a set of vertices $X$, the virtual tree $A(X)$ can be constructed in time

$$
O\left(|X| (\log |X| + \log N)\right),
$$

with preprocessing of the original tree $T$ in $O(N \log N)$ to ensure fast LCA queries.

**Main construction steps:**

1. **Preprocessing.**  
   Using depth-first search (DFS) or methods such as binary lifting or HLD, we compute entry times for vertices and LCAs for any two vertices.

2. **Vertex Sorting.**  
   We sort the vertices of set $X$ in the order of their appearance during DFS traversal (using entry times).

3. **Adding LCAs.**  
   For consecutive vertices $x_i$ and $x_{i+1}$, we compute $\operatorname{lca}(x_i,x_{i+1})$. The union of $X$ and these LCAs gives the set of vertices $A(X)$ (according to Property 2).

4. **Tree Construction.**  
   Having obtained the set of vertices $A(X)$ sorted by DFS order, we can traverse the sequence using a stack to restore the tree structure. During traversal, we maintain a stack whose top element is the current vertex, and if a new vertex is not a descendant of the vertex at the top of the stack, elements are "popped" until the corresponding ancestor is found, after which connecting occurs.

This algorithm guarantees that the virtual tree contains $O(|X|)$ vertices, allowing efficient application of DP.

## Application: Counting Subtrees in a Colored Tree

### Example [Problem](https://atcoder.jp/contests/abc340/tasks/abc340_g) Statement

Given a tree $T$ with $N$ vertices numbered from $1$ to $N$. Edge $i$ connects vertices $u[i]$ and $v[i]$. Each vertex $i$ is colored with color $A[i]$.  
It is necessary to find (modulo 998244353) the number of (non-empty) subsets $S$ of vertices of tree $T$ satisfying the condition:

- The induced graph $G[S]$ is a tree.
- All vertices of $G[S]$ with degree 1 have the same color.

### Main Solution Idea

The main idea is to break down the problem by colors. For each color $c$, we consider the set of vertices $X$ colored with $c$ and build a virtual tree for $X$. Then, on the resulting tree, we perform DP to count valid subtrees where all vertices with degree 1 have color $c$. The final answer is obtained by summing the results for all colors.

Thanks to the construction of the virtual tree, although the original tree contains $N$ vertices, each virtual tree for a specific color has size $O(|X|)$, which allows DP to be performed in an acceptable time.

We get that the total complexity of preprocessing and building virtual trees does not exceed $O(N \log N + \sum_{c \in C} (|X_c| (\log |X_c| + \log N)) = O(N \log N)$, where $C$ is the set of different vertex colors and $X_c$ is the set of vertices with color $c$.

### Solution Implementation

Below is the complete C++ code with comments describing the main components of the algorithm:

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;
const int LOGN = 20;
const int MOD = 998244353;

vector<int> g[MAXN];         // Adjacency list of the given graph
vector<int> ver[MAXN];       // For each color c, ver[c] stores vertices with color c
vector<int> virtual_g[MAXN];     // Adjacency list for the virtual tree
int col[MAXN];               // Color of each vertex
int tmr, n;                  // Global time counter and number of vertices
int up[LOGN][MAXN], dep[MAXN], tin[MAXN]; // For computing LCA and entry time

// DP arrays for dynamic programming on the virtual tree
int dp[MAXN][2], sum[MAXN];

// Preprocessing function: DFS to compute tin, up array, and dep
void dfs_precalc(int v, int p) {
    tin[v] = ++tmr;
    up[0][v] = p;
    dep[v] = dep[p] + 1;
    for (int i = 1; i < LOGN; ++i)
        up[i][v] = up[i - 1][up[i - 1][v]];
    for (auto to : g[v])
        if (to != p)
            dfs_precalc(to, v);
}

// Function to compute LCA using binary lifting
int getlca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = LOGN - 1; i >= 0; --i)
        if (dep[up[i][x]] >= dep[y])
            x = up[i][x];
    if (x == y) return x;
    for (int i = LOGN - 1; i >= 0; --i)
        if (up[i][x] != up[i][y]) {
            x = up[i][x];
            y = up[i][y];
        }
    return up[0][x];
}

// DFS on the virtual tree to perform DP.
// Parameter c — target color for which counting is performed.

void dfs_calc(int v, int p, int c, int &ans) {
    dp[v][0] = dp[v][1] = 0;
    sum[v] = 0;
    for(auto to : virtual_g[v]) {
        if(to == p) continue;
        dfs_calc(to, v, c, ans);
        // DP transitions: combining current state with result from subtree.
        int nxt0 = (dp[v][0] + sum[to]) % MOD;
        int nxt1 = ((dp[v][0] + dp[v][1]) * 1ll * sum[to] % MOD + dp[v][1]) % MOD;
        dp[v][0] = nxt0;
        dp[v][1] = nxt1;
    }
    sum[v] = (dp[v][0] + dp[v][1]) % MOD;
    if(col[v] == c) {
        // If the vertex has the target color, it can participate in a valid subtree.
        sum[v] = (sum[v] + 1) % MOD;
        ans = (ans + sum[v]) % MOD;
    } else {
        ans = (ans + dp[v][1]) % MOD;
    }
}

// Function to build a virtual tree for color c and perform DP.
void calc_virtual(int c, int &ans) {
    auto p = ver[c];
    if (p.empty()) return;
    // Sort vertices by entry time (tin) — DFS traversal order.
    sort(p.begin(), p.end(), [&](const int a, const int b) { return tin[a] < tin[b]; });
    vector<int> verstk = {1}; // Initialize stack with the root of tree T (vertex 1).
    virtual_g[1].clear();
    auto add = [&](int u, int v) {
        virtual_g[u].push_back(v);
        virtual_g[v].push_back(u);
    };
    // Process each vertex from set p, maintaining a stack to build the virtual tree.
    for (auto u : p) {
        if (u == 1) continue;
        int lca = getlca(u, verstk.back());
        if (lca != verstk.back()) {
            while (verstk.size() >= 2 && tin[lca] < tin[verstk[verstk.size() - 2]]) {
                add(verstk.back(), verstk[verstk.size() - 2]);
                verstk.pop_back();
            }
            if (verstk.size() >= 2 && tin[lca] != tin[verstk[verstk.size() - 2]]) {
                virtual_g[lca].clear();
                add(verstk.back(), lca);
                verstk.back() = lca;
            } else {
                add(verstk.back(), lca);
                verstk.pop_back();
            }
        }
        virtual_g[u].clear();
        verstk.push_back(u);
    }
    while (verstk.size() > 1) {
        add(verstk.back(), verstk[verstk.size() - 2]);
        verstk.pop_back();
    }
    // Perform DP on the virtual tree, starting from root 1.
    return dfs_calc(1, 0, c, ans);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    // Read colors and group vertices by color.
    for (int i = 1; i <= n; ++i) {
        cin >> col[i];
        ver[col[i]].push_back(i);
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs_precalc(1, 0);
    int ans = 0;
    // Process the corresponding virtual tree for each possible color.
    for (int i = 1; i <= n; ++i)
        calc_virtual(i, ans);
    cout << ans;
    return 0;
}
```

### Implementation Explanation

- **Preprocessing.**  
  The `dfs_precalc` function performs a depth-first traversal of tree $T$, computing entry time (`tin`), depth, and filling the binary lifting table `up` for fast LCA queries.

- **Computing LCA.**  
  The `getlca` function implements binary lifting for quickly finding the lowest common ancestor of two vertices.

- **Building the Virtual Tree.**  
  The `calc_virtual` function takes a color $c$, extracts the set of vertices `ver[c]`, sorts it by `tin`, and uses a stack to build the virtual tree. For each pair of consecutive vertices, the LCA is computed, corresponding to Property 2.

- **Dynamic Programming.**  
  The `dfs_calc` function traverses the virtual tree and combines the results from subtrees according to DP transitions. The DP states are calculated in such a way that the contribution of a vertex is accounted for if it has the target color, and only those subtrees where all leaves have the same color are counted.

- **Collecting the Result.**  
  The `main` function reads the input data, performs preprocessing, and then sums up the results for each color, outputting the final answer modulo 998244353.

## Conclusion

In this article, we have examined in detail the concept of a virtual tree, proved its main properties, described an efficient construction algorithm, and demonstrated the application of this technique to solve a DP problem on trees. The advantage of this approach is that it reduces the problem to working with a substructure of size $O(|X|)$, which significantly accelerates computations even with a large size of the original tree.

## Problems on Virtual Trees
1. [Leaf Color](https://atcoder.jp/contests/abc340/tasks/abc340_g) (problem from the article)
2. [Unique Occurrences](https://codeforces.com/contest/1681/problem/F)
3. [Yet Another Tree Problem](https://www.codechef.com/DEC21A/problems/YATP)
