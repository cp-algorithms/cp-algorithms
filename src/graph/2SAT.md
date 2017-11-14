<!--?title 2-SAT -->

# 2 - SAT 

SAT (Boolean satisfiability problem) is the problem of assigning Boolean values to variables to satisfy a given Boolean formula.
The Boolean formula will usually be given in CNF (conjunctive normal form), which is a conjunction of multiple clauses, where each clause is a disjunction of literals (variables or negation of variables).
2-SAT (2-satisfiability) is a restriction of the SAT problem, in 2-SAT every clause has exactly two literals.
Here is an example of such a 2-SAT problem.
Find an assignment of $a, b, c$ such that the following formula is true:

$$(a \lor \lnot b) \land (\lnot a \lor b) \land (\lnot a \lor \lnot b) \land (a \lor c)$$

SAT is NP-complete, there is no known efficient solution known for it.
However 2SAT can be solved efficiently in $O(n + m)$ where $n$ is the number of variables and $m$ is the number of clauses.

## Algorithm:

First we need to convert the problem to a different form, the so-called implicative normal form.
Note that the expression $a \lor b$ is equivalent to $\lnot a \Rightarrow b \land \lnot b \Rightarrow a$ (if one of the two variables is false, then the other one must be true).

We now construct a directed graph of these implications:
for each variable $i$ there will be two vertices $v_i$ and $v_{\lnot i}$.
The edges will correspond to the implications.

Lets look at the example in 2-CNF form:

$$(a \lor \lnot b) \land (\lnot a \lor b) \land (\lnot a \lor \lnot b) \land (a \lor c)$$

The oriented graph will contain the following vertices and edges:

$$\begin{array}{ccc}
\lnot a \Rightarrow \lnot b & a \Rightarrow b & a \Rightarrow \lnot b & \lnot a \Rightarrow c\\\\
b \Rightarrow a & \lnot b \Rightarrow \lnot a & b \Rightarrow \lnot a & \lnot c \Rightarrow a\\\\
\end{array}$$

You can see the implication graph in the following image:

!["Implication Graph of 2-SAT example"](&imgroot&/2SAT.png)

It is worth paying attention to the property of the implication graph:
if there is an edge $a \Rightarrow b$, then there also is an edge $\lnot b \Rightarrow \lnot a$. 

Also note, that if $x$ is reachable from $\lnot x$, and $\lnot x$ is reachable from $x$, then the problem has no solution.
Whatever value we choose for $x$, it will always end in a contradiction - if $x$ will assigned $\text{true}$ then the implication tell us that $\lnot x$ should also be $\text{true}$ and visa versa.
It turns out, that this condition is not only necessary, but also sufficient.
We will prove this in a few paragraphs below.
First let us formulate the assignment criterion using graph theory.
Recall, if a vertex if reachable from a second one, and the second one is reachable from the first one, then these two vertices are in the same strongly connected component.
Therefore we can formulate the criterion for the existence of a solution as follows:

In order for this 2-SAT problem to have a solution, it is necessary and sufficient that for any variable $x$ the vertices $x$ and $\lnot x$ are in different components of the strong connection of the implication graph.

This criterion can be verified in $O(n + m)$ time by finding all strongly connected components.

The following image shows all strongly connected components for the example.
As we can check easily, neither of the four components contain a vertex $x$ and its negation $\lnot x$, therefore the example has a solution.
We will learn in the next paragraphs how to compute a valid assignment, but just for demonstration the solution $a = \text{false}, b = \text{false}, c = \text{true}$ is given.

!["Strongly Connected Components of the 2-SAT example"](&imgroot&/2SAT_SCC.png)

Now we construct the algorithm for finding the solution of the 2-SAT problem on the assumption that the solution exists.

Note that, in spite of the fact that the solution exists, it can happen that $\lnot x$ is reachable from $x$, or that (not simultaneously) $x$ is reachable from $\lnot x$.
In this case the choice of one value will lead to a contradiction, while the choice of the other will not.
Let's learn how to choose a value, such that we don't generate a contradiction.
Just note the by selecting a value, we need to start to explore the graph with DFS/BFS and mark all the values that follow from it, i.e. the vertices that are reachable in the graph of implications.
Accordingly for all already marked vertices there is no need to make any choice between $x$ and $\lnot x$, the value has already been chosen and fixed.
The following rules apply to untagged peaks.

The following is stated.
Let $\text{comp}[v]$ denote the number of strongly connected components to which the vertex $v$ belongs, and the numbers are ordered int the order of topological sorting of the strongly connected components in the component graph (that is, there are larger numbers in the topological sort order if there is a path from $v$ to $w$ than $\text{comp}[v] \le \text{comp}[w]).
Then, if $\text{comp}[x] \lt \text{comp}[\lnot x]$, then select the value of $\lnot x$, otherwise, i.e. $\text{comp}[x] < \text{comp}[\lnot x]$, then choose $x$.

Let us prove that with this choice of values we do not arrive at a contradiction.
Suppose, for definiteness, that the vertex $x$ is chosen (the case when the vertex $\lnot x$ is proven analogously.

Fist we prove that $x$ is not reachable by $\lnot x$.
Indeed, since the number of strongly connected component $\text{comp}[x]$ is greater than the index of the component $\text{comp}[\lnot x]$, this means that the connected component containing $x$ is located to the left of the connected component containing $\lnot x$, and the later can be reached by the first.

Secondly we prove that no vertex $y$ is reachable from $x$ is "bad", i.e. it is not correct that $y$ is reachable from $\lnot y$.
Let us prove this by contradiction.
Suppose that $y$ is reachable from $y$, then by the property of the implication graph, $\lnot y$ is reachable from $\lnot x$.
But, by assumption, $y$ is reachable from $y$.
Then we get that $x$ is reachable from $\lnot x$, which contradicts the condition as required.

So we have constructed an algorithm that finds the required values of variables under the assumption that for any variable $x$ the vertices $x$ and $\lnot x$ are in different strongly connected components.
Above showed the correctness of this algorithm.
Consequently we simultaneously proved the above criterion for the existence of a solution.

Now we can implement the entire algorithm.

We construct the graph of implications.
We find in this graph the strongly connected components in $O(n + m)$ time.
Let $\text{comp}[v]$ be the index of the strongly connected component to which the vertex $v$ belongs.
Let us verify that for each variable $x$ the vertices $x$ and $\lnot x$ belong to different components, i.e. $\text{comp}[x] \ne \text{comp}[\lnot x]$. 
If this condition is not met, then return "the solution does not exist".
If $\text{comp}[x] > \text{comp}[\lnot x]$, then the variable $x$ is set to true, otherwise false.

## Implementation:

Below is the implementation of the solution of the 2-SAT problem for the already constructed graph of implication $g$ and the inverse graph $g^\prime$ (in which the direction of each edge is reversed).

The program displays the numbers of the selected vertices, or the phrase "No solution".

```cpp
int n;
vector<vector<int>> g, gt;
vector<bool> used;
vector<int> order, comp;
vector<bool> assignment;

void dfs1(int v) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int u : gt[v]) {
        if (comp[u] == -1)
            dfs2(u, cl);
    }
}

bool solve_2SAT() {
    used.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (!used[i])
            dfs1(i);
    }

    comp.assign(n, -1);
    for (int i = 0, j = 0; i < n; ++i) {
        int v = order[n - i - 1];
        if (comp[v] == -1)
            dfs2(v, j++);
    }

    assignment.assign(n / 2, false);
    for (int i = 0; i < n; i += 2) {
        if (comp[i] == comp[i ^ 1])
            return false;
        assignment[i / 2] = comp[i] > comp[i + 1];
    }
    return true;
}
```
