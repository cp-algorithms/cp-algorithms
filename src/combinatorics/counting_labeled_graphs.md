---
tags:
  - Translated
e_maxx_link: counting_connected_graphs
---

# Counting labeled graphs

## Labeled graphs

Let the number of vertices in a graph be $n$.
We have to compute the number $G_n$ of labeled graphs with $n$ vertices (labeled means that the vertices are marked with the numbers from $1$ to $n$).
The edges of the graphs are considered undirected, and loops and multiple edges are forbidden.

We consider the set of all possible edges of the graph.
For each edge $(i, j)$ we can assume that $i < j$ (because the graph is undirected, and there are no loops).
Therefore the set of all edges has the cardinality $\binom{n}{2}$, i.e. $\frac{n(n-1)}{2}$.

Since any labeled graph is uniquely determined by its edges, the number of labeled graphs with $n$ vertices is equal to:

$$G_n = 2^{\frac{n(n-1)}{2}}$$

## Connected labeled graphs

Here, we additionally impose the restriction that the graph has to be connected.

Let's denote the required number of connected graphs with $n$ vertices as $C_n$.

We will first discuss how many **disconnected** graphs exists.
Then the number of connected graphs will be $G_n$ minus the number of disconnected graphs.
Even more, we will count the number of **disconnected, rooted graphs**.A rooted graph is a graph, where we emphasize one vertex by labeling it as root.
Obviously we have $n$ possibilities to root a graph with $n$ labeled vertices, therefore we will need to divide the number of disconnected rooted graphs by $n$ at the end to get the number of disconnected graphs.

The root vertex will appear in a connected component of size $1, \dots n-1$.
There are $k \binom{n}{k} C_k G_{n-k}$ graphs such that the root vertex is in a connected component with $k$ vertices (there are $\binom{n}{k}$ ways to choose $k$ vertices for the component, these are connected in one of $C_k$ ways, the root vertex can be any of the $k$ vertices, and the remainder $n-k$ vertices can be connected/disconnected in any way, which gives a factor of $G_{n-k}$).
Therefore the number of disconnected graphs with $n$ vertices is:

$$\frac{1}{n} \sum_{k=1}^{n-1} k \binom{n}{k} C_k G_{n-k}$$

And finally the number of connected graphs is:

$$C_n = G_n - \frac{1}{n} \sum_{k=1}^{n-1} k \binom{n}{k} C_k G_{n-k}$$

## Labeled graphs with $k$ connected components {data-toc-label="Labeled graphs with k connected components"}

Based on the formula from the previous section, we will learn how to count the number of labeled graphs with $n$ vertices and $k$ connected components.

This number can be computed using dynamic programming.
We will compute $D[i][j]$ - the number of labeled graphs with $i$ vertices and $j$ components - for each $i \le n$ and $j \le k$.

Let's discuss how to compute the next element $D[n][k]$ if we already know the previous values.
We use a common approach, we take the last vertex (index $n$).
This vertex belongs to some component.
If the size of this component be $s$, then there are $\binom{n-1}{s-1}$ ways to choose such a set of vertices, and $C_s$ ways to connect them.After removing this component from the graph we have $n-s$ remaining vertices with $k-1$ connected components.
Therefore we obtain the following recurrence relation:

$$D[n][k] = \sum_{s=1}^{n} \binom{n-1}{s-1} C_s D[n-s][k-1]$$
