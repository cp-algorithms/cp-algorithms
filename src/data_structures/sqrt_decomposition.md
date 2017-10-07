<!--?title Sqrt Decomposition -->

# Sqrt Decomposition

Sqrt Decomposition is a method (or a data structure) that allows you to perform some common operations (finding sum of the elements of the sub-array, finding the minimal/maximal element, etc.) in $O(\sqrt n)$ operations, which is much faster than $O(n)$ for the trivial algorithm.

First we describe the data structure for one of the simplest applications of this idea, then show how to generalize it to solve some other problems, and finally look at a slightly different use of this idea: splitting the input requests into sqrt blocks.

## Sqrt-decomposition based data structure

Given an array $a[0 \dots n-1]$, implement a data structure that allows to find the sum of the elements $a[l \dots r]$ for arbitrary $l$ and $r$ in $O(\sqrt n)$ operations.

### Description

The basic idea of sqrt decomposition is preprocessing. We'll divide the array $a$ into blocks of length approximately $\sqrt n$, and for each block $i$ we'll precalculate the sum of elements in it $b[i]$.

We can assume that both the size of the block and the number of blocks are equal to $\sqrt n$ rounded up:

$$ s = \lceil \sqrt n \rceil $$

Then the array $a$ is divided into blocks in the following way:

$$ \underbrace{a[0], a[1], \dots, a[s-1]}\_{\text{b[0]}}, \underbrace{a[s], \dots, a[2s-1]}\_{\text{b[1]}}, \dots, \underbrace{a[(s-1) \cdot s], \dots, a[n]}\_{\text{b[s-1]}} $$

The last block may have fewer elements than the others (if $n$ not a multiple of $s$), it is not important to the discussion (as it can be handled easily).
Thus, for each block $k$, we know the sum of elements on it $b[k]$:

$$ b[k] = \sum\limits_{i=k\cdot s}^{\min {\(n-1,(k+1)\cdot s - 1}\)} a[i] $$

So, we have calculated the values of $b[k]$ (this required $O(n)$ operations). How can they help us to answer each query $[l; r]$ ?
Notice that if the interval $[l; r]$ is long enough, it will contain several whole blocks, and for those blocks we can find the sum of elements in them in a single operation. As a result, the interval $[l; r]$ will contain parts of only two blocks, and we'll have to calculate the sum of elements in these parts trivially.

Thus, in order to calculate the sum of elements on the interval $[l; r]$ we only need to sum the elements of the two "tails":
$[l\dots (k + 1)\cdot s-1]$ and $[p\cdot s\dots r]$ , and sum the values $b[i]$ in all the blocks from $k + 1$ to $p-1$:

$$ \sum\limits\_{i=l}^r a[i] = \sum\limits\_{i=l}^{(k+1) \cdot s-1} a[i] + \sum\limits\_{i=k+1}^{p-1} b[i] + \sum\limits\_{i=p\cdot s}^r a[i] $$

_Note: When $k = p$, i.e. $l$ and $r$ belong to the same block, the formula can't be applied, and the sum should be calculated trivially._

This approach allows us to significantly reduce the number of operations. Indeed, the size of each "tail" does not exceed the block length $s$, and the number of blocks in the sum does not exceed $s$. Since we have chosen $s \approx \sqrt n$, the total number of operations required to find the sum of elements on the interval $[l; r]$ is $O(\sqrt n)$.

### Implementation

Let's start with the simplest implementation:

```cpp
// input data
int n;
vector<int> a (n);
 
// preprocessing
int len = (int) sqrt (n + .0) + 1; // size of the block and the number of blocks
vector<int> b (len);
for (int i=0; i<n; ++i)
	b[i / len] += a[i];
 
// answering the queries
for (;;) {
	int l, r; 
  // read input data for the next query
	int sum = 0;
	for (int i=l; i<=r; )
		if (i % len == 0 && i + len - 1 <= r) {
			// if the whole block starting at i belongs to [l; r]
			sum += b[i / len];
			i += len;
		}
		else {
			sum += a[i];
			++i;
		}
}
```

This implementation has unresonably many division operations (which are much slower than other arithmetical operations). Instead, we can calculate the indices of the blocks $c_l$ and $c_r$ which contain indices $l$ and $r$, and loop through blocks $c_l+1 \dots c_r-1$ with separate processing of the "tails" in blocks $c_l$ and $c_r$. This approach corresponds to the last formula in the description, and makes the case $c_l = c_r$ a special case.

```cpp
int sum = 0;
int c_l = l / len,   c_r = r / len;
if (c_l == c_r)
	for (int i=l; i<=r; ++i)
		sum += a[i];
else {
	for (int i=l, end=(c_l+1)*len-1; i<=end; ++i)
		sum += a[i];
	for (int i=c_l+1; i<=c_r-1; ++i)
		sum += b[i];
	for (int i=c_r*len; i<=r; ++i)
		sum += a[i];
}
```
