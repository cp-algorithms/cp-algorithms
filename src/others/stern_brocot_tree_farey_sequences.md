<!--?title The Stern-Brocot Tree and Farey Sequences -->

# The Stern-Brocot tree and Farey sequences

## Stern-Brocot tree

The Stern-Brocot tree is an elegant construction to represent the set of all positive fractions. It was independently discovered by German mathematician Moritz Stern in 1858 and by French watchmaker Achille Brocot in 1861. However, some sources attribute the discovery to ancient Greek mathematician Eratosthenes.

The construction starts at the zeroth iteration with the two fractions

$$
    \frac{0}{1}, \frac{1}{0}
$$

where it should be noted that the second quantity is not strictly a fraction, but it can be interpreted as an irreducible fraction representing infinity.

At every subsequent iteration, consider all adjacent fractions $\frac{a}{b}$ and $\frac{c}{d}$ and insert their [mediant](https://en.wikipedia.org/wiki/Mediant_(mathematics)) $\frac{a+c}{b+d}$ between them.

The first few iterations look like this:

$$
    \begin{array}{c}
    \dfrac{0}{1}, \dfrac{1}{1}, \dfrac{1}{0} \\\\\\\\
    \dfrac{0}{1}, \dfrac{1}{2}, \dfrac{1}{1}, \dfrac{2}{1}, \dfrac{1}{0} \\\\\\\\
    \dfrac{0}{1}, \dfrac{1}{3}, \dfrac{1}{2}, \dfrac{2}{3}, \dfrac{1}{1}, \dfrac{3}{2}, \dfrac{2}{1}, \dfrac{3}{1}, \dfrac{1}{0}
    \end{array}
$$

Continuing this process to infinity this covers *all* positive fractions. Additionally, all fractions will be *unique* and *irreducible*. Finally, the fractions will also appear in ascending order.

Before proving these properties, let us actually show a visualization of the Stern-Brocot tree, rather than the list representation. Every fraction in the tree has two children. Each child is the mediant of the closest ancestor on the left and closest ancestor to the right.

<center>![Stern-Brocot tree](https://upload.wikimedia.org/wikipedia/commons/thumb/3/37/SternBrocotTree.svg/1024px-SternBrocotTree.svg.png)</center>

## Proofs

**Ordering.** Proving ordering is simple. We note that the mediant of two fractions is always in-between the fractions

$$
    \frac{a}{b} \le \frac{a+c}{b+d} \le \frac{c}{d}
$$

given that

$$
    \frac{a}{b} \le \frac{c}{d}.
$$

The two inequalities can be easily shown by rewriting the fractions with common denominators.

As the ordering is ascending in the zeroth iteration, it will be maintained at every subsequent iteration.

**Irreducibility.** To prove this we will show that for any two adjacent fractions $\frac{a}{b}$ and $\frac{c}{d}$ we have that

$$
    bc - ad = 1.
$$

Recall that a Diophantine equation with two variables $ax+by=c$ has a solution iff $c$ is a multiple of $\gcd(a,b)$. In our case this implies that $\gcd(a,b) = \gcd(c,d) = 1$, which is what we want to show.

Clearly at the zeroth iteration $bc - ad = 1$. What remains to be shown is that mediants retain this property.

Assume our two adjacent fractions uphold $bc - ad = 1$, after the mediant is added to the list

$$
    \frac{a}{b}, \frac{a+c}{b+d}, \frac{c}{d}
$$

the new expressions become

$$\begin{align}
    b(a+c) - a(b+d) &= 1 \\\\
    c(b+d) - d(a+c) &= 1
\end{align}$$

which, using that $bc-ad=1$, can be easily shown to be true.

From this we see that the property is always maintained and thus all fractions are irreducible.

**The presence of all fractions.** This proof is closely related to locating a fraction in the Stern-Brocot tree. From the ordering property we have that left subtree of a fraction contains only fractions smaller than the parent fraction, and the right subtree contains only fractions larger than the parent fraction. This means we can search for a fraction by traversing the tree from the root, going left if the target is smaller than the fraction and going right if the target is larger.

Pick an arbitrary positive target fraction $\frac{x}{y}$. It is obviously between $\frac{0}{1}$ and $\frac{1}{0}$, so the only way for the fraction to not be in the tree is if it takes an infinite number of steps to get to it.

If that is the case we would at all iterations have

$$
    \frac{a}{b} \lt \frac{x}{y} \lt \frac{c}{d}
$$

which (using the fact than an integer $z \gt 0 \iff z \ge 1$) can be rewritten as

$$
\begin{align}
    bx - ay &\ge 1 \\\\
    cy - dx &\ge 1.
\end{align}
$$

Now multiply the first inequality by $c+d$ and the second with $a+b$ and add them to get

$$
    (c+d)(bx - ay) + (a+b)(cy - dx) \ge a+b+c+d.
$$

Expanding this and using the previously shown property $bc-ad=1$ we get that

$$
    x+y \ge a+b+c+d.
$$

And given that at every iteration at least one of $a,b,c,d$ will increase, the fraction searching process will contain no more than $x+y$ iterations. This contradicts the assumption that the path to $\frac{x}{y}$ was infinite and hence $\frac{x}{y}$ must be part of the tree.

## Tree Building Algorithm

To build any subtree of the Stern-Brocot tree, it suffices to know the left and right ancestor. On the first level, the left and right ancestors are $\frac{0}{1}$ and $\frac{1}{0}$ respectively. Using these, we calculate the mediant and proceed one level deeper, with the mediant replacing the right ancestor in the left subtree, and vice versa.

This pseudocode tries to build the entire infinite tree:

```cpp
void build(int a = 0, int b = 1, int c = 1, int d = 0, int level = 1) {
    int x = a + c, y = b + d;

    ... output the current fraction x/y at the current level in the tree
    
    build(a, b, x, y, level + 1);
    build(x, y, c, d, level + 1);
}
```

## Fraction Search Algorithm

The search algorithm was already described in the proof that all fractions appear in the tree, but we will repeat it here. The algorithm is a binary search algorithm. Initially we stand at the root of the tree and we compare our target with the current fraction. If they are the same we are done and stop the process. If our target is smaller we move to the left child, otherwise we move to the right child.

Here is an implementation that returns the path to a given fraction $\frac{x}{y}$ as a sequence of `'L'` and `'R'` characters, meaning traversal to the left and right child respectively. This sequence of characters uniquely defines all positive fractions and is called the Stern-Brocot number system.

```cpp
string find(int x, int y, int a = 0, int b = 1, int c = 1, int d = 0) {
    int m = a + c, n = b + d;
    if (x == m && y == n)
        return "";
    if (x*n < y*m)
        return 'L' + find(x, y, a, b, m, n);
    else
        return 'R' + find(x, y, m, n, c, d);
}
```

Irrational numbers in the Stern-Brocot number system corresponds to infinite sequences of characters. Along the endless path towards the irrational number the algorithm will find reduced fractions with gradually increasing denominators that provides increasingly better approximations of the irrational number. So by taking a prefix of the infinite sequence approximations with any desired precision can be achieved. This application is important in watch-making, which explains why the tree was discovered in that domain.

## Farey Sequence

The Farey sequence of order $n$ is the sorted sequence of fractions between $0$ and $1$ whose denominators do not exceed $n$.

The sequences are named after English geologist John Farey, who in 1816 conjectured that any fraction in a Farey sequence is the mediant of its neighbors. This was proven some time later by Cauchy, but independent of both of them, the mathematician Haros had come to almost the same conclusion in 1802.

The Farey sequences have many interesting properties on their own, but the connection to the Stern-Brocot tree is the most obvious. In fact, the Farey sequences can be obtained by trimming branches from the tree.

From the algorithm for building the Stern-Brocot tree, we get an algorithm for the Farey sequences. Start with the list of fractions $\frac{0}{1}, \frac{1}{0}$. At every subsequent iteration, insert the mediant only if the denominator does not exceed $n$. At some point the list will stop changing and the desired Farey sequence will have been found.

### Length of a Farey Sequence

A Farey sequence of order $n$ contains all elements of the Farey sequence of order $n-1$ as well as all irreducible fractions with denominator $n$, but the latter is just the totient $\varphi(n)$. So the length $L_n$ of the Farey sequence of order $n$ is

$$
    L_n = L_{n-1} + \varphi(n)
$$

or equivalently, by unraveling the recursion we get

$$
    L_n = 1 + \sum_{k=1}^n \varphi(k).
$$
