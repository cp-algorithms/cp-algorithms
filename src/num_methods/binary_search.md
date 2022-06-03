<!--?title Binary search -->
# Binary search

**Binary search** is a method that allows for quicker search of something by halving the search interval. Its most common application is searching values in sported arrays, however the halving idea is crucial in many other typical competitive programming tasks.

## Search in sorted arrays

The most typical problem that leads to the binary search is as follows. You're given a sorted array $a_0 \leq a_1 \leq \dots \leq a_{n-1}$, check if $k$ is present within the sequence. The simplest solution would be to check every element one by one and compare it with $k$ (a so-called linear search). This approach works in $O(n)$, but doesn't utilize the fact that the array is sorted.

Now assume that we know two indices $L < R$ such that $a_L \leq k \leq a_R$. Because the array is sorted, we can deduce that $k$ either occurs among $a_L, a_{L+1}, \dots, a_R$ or doesn't occur in the array at all. Now we can pick arbitrary index $M$ such that $L < M < R$ and check whether $k$ is less or greater than $a_M$. We have two possible cases:

1. $a_L \leq k \leq a_M$. In this case, we reduce the problem from $[L, R]$ to $[L, M]$;
1. $a_M \leq k \leq a_R$. In this case, we reduce the problem from $[L, R]$ to $[M, R]$.

When it is impossible to pick  $M$, that is, when $R = L + 1$, we can directly compare $k$ with $a_L$ and $a_R$. Otherwise we want to pick $M$ in such manner that it reduces to a single element as quickly as possible. For this, we pick it in such way that $M - L \approx R - M$, which is the case when $M \approx \frac{L+R}{2}$, then $M-L \approx \frac{R-L}{2} \approx R - M$.

Done this way, the current difference $R-L$ is halved on each step until it becomes $1$. So, if the process needs $h$ steps, it reduces the difference between $R$ and $L$ from $R-L$ to $\frac{R-L}{2^h} \approx 1$, giving us the equation $2^h \approx R-L$ for the number of steps $h$.

Taking $\log_2$ on both sides, we get $h \approx \log_2(R-L) \in O(\log n)$.

Logarithmic number of steps is drastically better than that of linear search. For example, for $n \approx 2^{20} \approx 10^6$ you'd need to make approximately a million operations for linear search, but only around $20$ operations with the binary search.

### Lower bound and upper bound

It is quite often that we need not to find the exact position of the element $k$ in the array, but rather find the position of the first element that is not less than $k$ (called the lower bound of $k$ in the array) or the position of the first element that is greater than $k$ (called the upper bound of $k$).

Together, lower and upper bounds produce a possibly empty half-interval of the array elements that are equal to $k$. To check whether $k$ is present in the array it's enough to find its lower bound and check if the corresponding element equates to $k$.

### Implementation

The explanation above provides a rough description of the algorithm idea rather than the strict instruction on how exactly it should be implemented. For the implementation details, we'd need to be more precise.

We will use the half-interval invariant, that is we will maintain a pair $L < R$ such that $a_L \leq k < a_R$. When $R = L+1$, we can deduce from definitions above that $R$ is the upper bound of $k$. It is convenient to initialize $R$ with past-the-end index, that is $R=n$ and $L$ with before-the-beginning index, that is $L=-1$. It is fine as long as we never evaluate $A_L$ and $a_R$ in our algorithm, formally treating it as $a_L = -\infty$ and $a_R = +\infty$.

Unlike segment invariant $a_L \leq k \leq a_R$ mentioned above, half-interval invariant doesn't require checks against both $a_L$ and $a_R$ in the end of the algorithm. Finally, to be specific about the value of $M$ we pick, we will stick with $M = \lfloor \frac{L+R}{2} \rfloor$.

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

During the execution of the algorithm, we never evaluate neither $a_L$ nor $a_R$, as $L < M < R$. In the end, $L$ will be the index of the last element that is not greater than $k$ (or $-1$ if there is no such element) and $R$ will be the index of the first element larger than $k$ (or $n$ if there is no such element).

## Search on arbitrary predicate

Let $f : \{0,1,\dots, n-1\} \mapsto \{0, 1\}$ be a boolean function defined on $0,1,\dots,n-1$ such that it is monotonous, that is

$$
f(0) \leq f(1) \leq \dots \leq f(n-1).
$$

The binary search finds the partition by $f(M) = k < a_M$, that is the index $L$ such that $f(L) = 0$ and $f(R)=f(L+1)=1$. Instead of $k < a_M$ we can use arbitrary predicate here as long as the property above stands. It is of particular use to us when computation of $f(k)$ is possible, but requires too much time to actually compute it for every possible value.

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

Such situation is quite typical when we're asked to compute some value, but for some reason we're only able to check whether this value is at least $i$. For example, you're given an array $a_1,\dots,a_n$ and you're asked to find the maximum floored average sum

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

!!! example "[NEERC 2006-2007. Hard Life](https://codeforces.com/gym/100532/problem/H)"
    You're given a graph $G = (V, E)$. Let $A$ be a subset of its vertices, then $f(A)$ is the number of pairs $i, j \in A$ such that there is an edge between $i$ and $j$. You need to find a subset $A$ such that the fraction $\frac{f(A)}{|A|}$ is the maximum possible.

??? hint "Solution"
    Let's try to check whether the answer is at least $\lambda$, that is whether there is $A \subset V$ such that

    $$f(A) \geq |A| \lambda$$