<!--?title Sqrt-decomposition -->

# Sqrt decomposition

Sqrt-decomposition is a method(or a data structure) that allows you to perform some common operations (summation of the elements of the sub-array, finding the min/max, etc) for $O(\sqrt n)$ that much faster than $O(n)$for the trivial algorithm.

First, we describe the data structure for one of the simplest applications of this idea, then show how to generalize it to solve some other problems, and finally look at some other use of this idea: splitting the input requests sqrt-blocks.

##Data structure sqrt-based decomposition

We pose the problem, given an array $a[0\dots n-1]$, implement a data structure that will be able to find the sum of the elements $a[l\dots r]$ for arbitrary $l$ and $r$ in $O(\sqrt n)$ time.

###Description

The basic idea of the sqrt-decomposition is that, we'll divide the array $a$ into blocks of length approximately $\sqrt n$, and in each block $i$ of length $\sqrt n$, we will store the sum in advance in $a[i]$.

We may assume $\sqrt n$ is rounded up to the ceil.

$$ s = \lceil \sqrt n \rceil $$

Then the array $a$ is divided into blocks like this

$$ \underbrace{a[0], a[1], ..., a[s-1]}\_{\text{b[0]}}, \underbrace{a[s], ..., a[2s-1]}\_{\text{b[1]}}, \underbrace{a[s*(s-1)], ..., a[n]}\_{\text{b[s-1]}} $$

Although the last unit may have lesser elements than $s$(if $n$ not a multiple of $s$), it is not important to the discussion(as it can be handled easily).
Thus, for each block $k$, we know the amount on it $b[k]$:

$$ b[k] = \sum\limits_{i=k\cdot s}^{min(n-1),(k+1)\cdot s - 1} a[i] $$

So, we can calculate the values of $b_k$ (this would be a $O(n)$ operation). How can they help us in the calculation of the request $(l, r)$ ?
We can observe that if the interval $(l ,r)$ is long, then it will contain several blocks as a whole, and for such units we can find out the answer in a single operation. As a result, the total length $(l, r)$ will only fall into two blocks partially, and these parts we have to calculate trivially.

And thus in order to calculate the sum of the segment $[l\dots r]$, it is required only to sum the elements of the two "tails":
$[l\dots (k + 1)\cdot s-1]$ and $[p\cdot s\dots r]$ , and sum the values $b[i]$ in all the blocks, starting from $k + 1$ and ending with $p-1$:

$$ \sum\limits\_{i=l}^r a[i] = \sum\limits\_{i=l}^{(k+1)s-1} a[i] + \sum\limits\_{i=k+1}^{p-1} b[i] + \sum\limits\_{i=p\cdot s}^r a[i] $$

_Note: When $k = p$, the formula gives incorrect results because in such a case, the request $(l, r)$ lies in a single block and can be calculated trivially._

Thus we have significantly reduced the number of operations. It is clear that the size of each of the "tails" clearly does not exceed the block length $s$, and also the number of blocks does not exceed $s$. Since, $s$ we have chosen is $\approx \sqrt n$, the total amount for the calculation for the interval $(l\dots r)$, we only need $O(\sqrt n)$ operations.
