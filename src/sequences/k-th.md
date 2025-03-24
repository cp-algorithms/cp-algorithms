---
title: K-th order statistic in O(N)
tags:
  - Translated
e_maxx_link: kth_order_statistics
---
# $K$th order statistic in $O(N)$

Given an array $A$ of size $N$ and a number $K$. The problem is to find $K$-th largest number in the array, i.e., $K$-th order statistic.

The basic idea - to use the idea of quick sort algorithm. Actually, the algorithm is simple, it is more difficult to prove that it runs in an average of $O(N)$, in contrast to the quick sort.

## Implementation (not recursive)

```cpp
template <class T>
T order_statistics (std::vector<T> a, unsigned n, unsigned k)
{
    using std::swap;
    for (unsigned l=1, r=n; ; )
    {
        if (r <= l+1)
        {
            // the current part size is either 1 or 2, so it is easy to find the answer
            if (r == l+1 && a[r] < a[l])
                swap (a[l], a[r]);
            return a[k];
        }

        // ordering a[l], a[l+1], a[r]
        unsigned mid = (l + r) >> 1;
        swap (a[mid], a[l+1]);
        if (a[l] > a[r])
            swap (a[l], a[r]);
        if (a[l+1] > a[r])
            swap (a[l+1], a[r]);
        if (a[l] > a[l+1])
            swap (a[l], a[l+1]);

        // performing division
        // barrier is a[l + 1], i.e. median among a[l], a[l + 1], a[r]
        unsigned
            i = l+1,
            j = r;
        const T
            cur = a[l+1];
        for (;;)
        {
            while (a[++i] < cur) ;
            while (a[--j] > cur) ;
            if (i > j)
                break;
            swap (a[i], a[j]);
        }

        // inserting the barrier
        a[l+1] = a[j];
        a[j] = cur;
        
        // we continue to work in that part, which must contain the required element
        if (j >= k)
            r = j-1;
        if (j <= k)
            l = i;
    }
}
```

## Notes
* The randomized algorithm above is named [quickselect](https://en.wikipedia.org/wiki/Quickselect). You should do random shuffle on $A$ before calling it or use a random element as a barrier for it to run properly. There are also deterministic algorithms that solve the specified problem in linear time, such as [median of medians](https://en.wikipedia.org/wiki/Median_of_medians).
* A deterministic linear solution is implemented in C++ standard library as [std::nth_element](https://en.cppreference.com/w/cpp/algorithm/nth_element).
* Finding $K$ smallest elements can be reduced to finding $K$-th element with a linear overhead, as they're exactly the elements that are smaller than $K$-th.

## Practice Problems
- [Leetcode: Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/description/)
- [CODECHEF: Median](https://www.codechef.com/problems/CD1IT1)
