<!--?title Second best Minimum Spanning Tree -->
# Second best Minimum Spanning Tree

A Minimum Spanning Tree ($T$) is a tree for the given graph $G$ which spans over all vertices of the given graph and has the minimum weight sum of all the edges, from all the possible spanning trees.
A second best MST ($T'$) is a ST, but has second minimum weight sum of all the edges, from all the possible spanning trees of the graph $G$.

## Observation

Let $T$ be the Minimum Spanning Tree of a graph $G$.
Then one point to be noted is that the second best Minimum Spanning Tree differs from $T$ by only one edge replacement. (For a proof of this statement refer to problem 23-1 - part b [here](http://www-bcf.usc.edu/~shanghua/teaching/Spring2010/public_html/files/HW2_Solutions_A.pdf)).

So we need to find an edge $e_{new}$ which is in not in $T$, and replace it with an edge in $T$ (let it be $e_{old}$) such that the new graph $T' = (T \cup \\{e_{new}\\}) \setminus \\{e_{old}\\}$ is a spanning tree and the weight difference ($e_{new} - e_{old}$) is minimum.


## Using Kruskal's Algorithm

We can use Kruskal's algorithm to find the MST first, then we do the following to find a second best MST -

1. Sort the edges in $O(E \log E)$, then find a MST using Kruskal in $O(E)$.
2. For each edge in the MST (we will have $V-1$ edges in it) temporarily exclude it from the edge list so that it cannot be chosen.
3. Then, again try to find a MST in $O(E)$ using the remaining edges.
4. Do this for all the edges in MST, and take the best of all.

Note that we don’t need to sort the edges again in for Step 3.

So, the overall Time taken will be $O(E \log V + E + V E)$ = $O(V E)$.


## Modeling into a Lowest Common Ancestor(LCA) problem

Let, $\Delta|T| = T' - T = \infty$, which is the difference in the MST and the second best MST. Then we try to find an edge $E_{old}$ in MST and $E_{new}$ which is a non-MST edge and replace $E_{old}$ by $E_{new}$ to get our second best MST.

Let, $E_{new}$ = −1, and $E_{old}$ = −1.

Then, for every edge $e$ that is not on the MST, we do the following -

1. Add edge $e$ to the MST, creating a cycle.
2. Find $k$ the maximum weight edge in the cycle such that $k$ not equal to $e$.
3. Remove $k$ - temporarily.
4. Compute the change in the tree weight $\delta = weight(e) − weight(k)$.
5. If $\delta < \Delta|T|$ then $\Delta|T| = \delta$ and $E_{new} = e$ and $E_{old} = k$.

The new tree $T’$ is the one that results in from replacing $E_{old}$ by $E_{new}$ in $T$.

Now, The Time of the algorithm can be determined by the way we compute $k$, which is the maximum weight edge in step-2 of this algorithm. One way is to use Lowest Common Ancestor(LCA) to find it efficiently in $O(ElogV)$.

We will preprocess the LCA by rooting the tree(MST) and will also compute the maximum edge value for each node moving up to its LCA. This can be done using Binary Lifting Method for LCA.

For example -

![First and Second best MST](&imgroot&/first_and_second_mst.png)

*In the image left is the MST and right is the second best MST.*

![Second best MST explain](&imgroot&/second_mst_explain.png)

In the given graph suppose we root the MST at the vertex connecting edges with weight 8 and 5, and then run our algorithm by start picking the edges not in MST. Let the edge picked first be with weight 14(As an example), then there would be a cycle formed between the edges with weight 12–4–14.

Now we will find maximum weight edge in this cycle by finding the LCA($u$, $v$)(Let it be $p$) and making the maximum edge query from vertex ($p$ to $u$) and from ($p$ to $v$). Note - LCA($u$, $v$) can be equal to $u$ or $v$ also in some case.

In this example we will get edge with weight 12 as maximum edge weight in cycle, and then we will follow our algorithm’s next step to find $\delta$ and update $E_{new}$ and $E_{old}$. And, Finally at last $\delta$ will be minimised after taking all edges into consideration and we will replace $E_{old}$ by $E_{new}$ to get our Second MST, which is $T'$.


## References -
1. Competitive Programming-3, by Steven Halim
2. http://web.mit.edu/6.263/www/quiz1-f05-sol.pdf
3. Image Source - http://web.mit.edu/6.263/www/quiz1-f05-sol.pdf

