---
tags:
    - Original
---

# Binary search

**Binary search** is a method that allows for quicker search of something by splitting the search interval into two. Its most common application is searching values in sported arrays, however the splitting idea is crucial in many other typical tasks.

## Search in sorted arrays

The most typical problem that leads to the binary search is as follows. You're given a sorted array $A_0 \leq A_1 \leq \dots \leq A_{n-1}$, check if $k$ is present within the sequence. The simplest solution would be to check every element one by one and compare it with $k$ (a so-called linear search). This approach works in $O(n)$, but doesn't utilize the fact that the array is sorted.

<center>
<img src="https://upload.wikimedia.org/wikipedia/commons/8/83/Binary_Search_Depiction.svg" width="800px">
<br>
<i>Binary search of the value $7$ in an array</i>.
<br>
<i>The <a href="https://commons.wikimedia.org/wiki/File:Binary_Search_Depiction.svg">image</a> by [AlwaysAngry](https://commons.wikimedia.org/wiki/User:AlwaysAngry) is distributed under <a href="https://creativecommons.org/licenses/by-sa/4.0/deed.en">CC BY-SA 4.0</a></i> license.
</center>

Now assume that we know two indices $L < R$ such that $A_L \leq k \leq A_R$. Because the array is sorted, we can deduce that $k$ either occurs among $A_L, A_{L+1}, \dots, A_R$ or doesn't occur in the array at all. If we pick an arbitrary index $M$ such that $L < M < R$ and check whether $k$ is less or greater than $A_M$. We have two possible cases:

1. $A_L \leq k \leq A_M$. In this case, we reduce the problem from $[L, R]$ to $[L, M]$;
1. $A_M \leq k \leq A_R$. In this case, we reduce the problem from $[L, R]$ to $[M, R]$.

When it is impossible to pick  $M$, that is, when $R = L + 1$, we directly compare $k$ with $A_L$ and $A_R$. Otherwise we would want to pick $M$ in such manner that it reduces the active segment to a single element as quickly as possible _in the worst case_.

Since in the worst case we will always reduce to larger segment of $[L, M]$ and $[M, R]$. Thus, in the worst case scenario the reduction would be from $R-L$ to $\max(M-L, R-M)$. To minimize this value, we should pick $M \approx \frac{L+R}{2}$, then

$$
M-L \approx \frac{R-L}{2} \approx R-M.
$$

In other words, from the worst-case scenario perspective it is optimal to always pick $M$ in the middle of $[L, R]$ and split it in half. Thus, the active segment halves on each step until it becomes of size $1$. So, if the process needs $h$ steps, in the end it reduces the difference between $R$ and $L$ from $R-L$ to $\frac{R-L}{2^h} \approx 1$, giving us the equation $2^h \approx R-L$.

Taking $\log_2$ on both sides, we get $h \approx \log_2(R-L) \in O(\log n)$.

Logarithmic number of steps is drastically better than that of linear search. For example, for $n \approx 2^{20} \approx 10^6$ you'd need to make approximately a million operations for linear search, but only around $20$ operations with the binary search.

### Lower bound and upper bound

It is often convenient to find the position of the first element that is not less than $k$ (called the lower bound of $k$ in the array) or the position of the first element that is greater than $k$ (called the upper bound of $k$) rather than the exact position of the element.

Together, lower and upper bounds produce a possibly empty half-interval of the array elements that are equal to $k$. To check whether $k$ is present in the array it's enough to find its lower bound and check if the corresponding element equates to $k$.

### Implementation

The explanation above provides a rough description of the algorithm. For the implementation details, we'd need to be more precise.

We will maintain a pair $L < R$ such that $A_L \leq k < A_R$. Meaning that the active search interval is $[L, R)$. We use half-interval here instead of a segment $[L, R]$ as it turns out to require less corner case work.

When $R = L+1$, we can deduce from definitions above that $R$ is the upper bound of $k$. It is convenient to initialize $R$ with past-the-end index, that is $R=n$ and $L$ with before-the-beginning index, that is $L=-1$. It is fine as long as we never evaluate $A_L$ and $A_R$ in our algorithm directly, formally treating it as $A_L = -\infty$ and $A_R = +\infty$.

Finally, to be specific about the value of $M$ we pick, we will stick with $M = \lfloor \frac{L+R}{2} \rfloor$.

Then the implementation could look like this:

```cpp
... // a sorted array is stored as a[0], a[1], ..., a[n-1]
int l = -1, r = n;
while(r - l > 1) {
    int m = (l + r) / 2;
    if(k < a[m]) {
        r = m; // a[l] <= k < a[m] <= a[r]
    } else {
        l = m; // a[l] <= a[m] <= k < a[r]
    }
}
```

During the execution of the algorithm, we never evaluate neither $A_L$ nor $A_R$, as $L < M < R$. In the end, $L$ will be the index of the last element that is not greater than $k$ (or $-1$ if there is no such element) and $R$ will be the index of the first element larger than $k$ (or $n$ if there is no such element).

## Search on arbitrary predicate

Let $f : \{0,1,\dots, n-1\} \mapsto \{0, 1\}$ be a boolean function defined on $0,1,\dots,n-1$ such that it is monotonous, that is

$$
f(0) \leq f(1) \leq \dots \leq f(n-1).
$$

The binary search, the way it is described above, finds the partition of the array by the predicate $f(M)$, holding the boolean value of $k < A_M$ expression. In other words, binary search finds the unique index $L$ such that $f(L) = 0$ and $f(R)=f(L+1)=1$.

It is possible to use arbitrary monotonous predicate instead of $k < A_M$. It is particularly useful when the computation of $f(k)$ is requires too much time to actually compute it for every possible value.

```cpp
... // f(i) is a boolean function such that f(0) <= ... <= f(n-1)
int l = -1, r = n;
while(r - l > 1) {
    int m = (l + r) / 2;
    if(f(m)) {
        r = m; // 0 = f(l) < f(m) = 1
    } else {
        l = m; // 0 = f(m) < f(r) = 1
    }
}
```

### Binary search on the answer

Such situation often occurs when we're asked to compute some value, but we're only capable of checking whether this value is at least $i$. For example, you're given an array $a_1,\dots,a_n$ and you're asked to find the maximum floored average sum

$$
\left \lfloor \frac{a_l + a_{l+1} + \dots + a_r}{r-l+1} \right\rfloor
$$

among all possible pairs of $l,r$ such that $r-l \geq x$. One of simple ways to solve this problem is to check whether the answer is at least $\lambda$, that is if there is a pair $l, r$ such that the following is true:

$$
\frac{a_l + a_{l+1} + \dots + a_r}{r-l+1} \geq \lambda.
$$

Equivalently, it rewrites as

$$
(a_l - \lambda) + (a_{l+1} - \lambda) + \dots + (a_r - \lambda) \geq 0,
$$

so now we need to check whether there is a subarray of a new array $a_i - \lambda$ of length at least $x+1$ with non-negative sum, which is doable with some prefix sums.
