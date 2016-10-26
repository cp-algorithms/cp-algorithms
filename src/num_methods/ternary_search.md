<!--?title Ternary Search and its Applications -->

# Ternary Search

##Formulation of the problem
We are given a function $f(x)$ which is unimodal on an interval $[l, r]$. By unimodal function, we mean one of two options. 

1. The function is strictly increasing first, then reaches a maximum (at one point or the whole segment), then it is strictly decreasing. 

2. The function initially strictly decreases, reaches a minimum, and then strictly increases. 

In the whole discussion, we will consider the first option, the second will be completely symmetrical to it.

Now, our task is to find the maximum of value of function $f(x)$ on the interval $[l, r]$.

##Algorithm
Consider any 2 points $m_1$, and $m_2$ in this segment such that $l < m_1 < m_2 < r$. We evaluate the function at $m_1$ and $m_2$ i.e. find the values of $f(m_1)$ and $f(m_2)$. Now, we get one of three options below:

- **$f(m_1) < f (m_2)$**

  The desired maximum can not be located on the left side, i.e. in the part $[l, m_1]$. This means that either both points $m_1$ and $m_2$ lie in the increasing part of the function or only $m_1$ lies in the increasing part of the function. In either case, we can conclude that maximum value of the function will not definitely lie in the left side. This reduces our search space to the segment $[m_1, r]$.

- **$f(m_1) > f(m_2)$** 

  This situation is similar to the previous one, up to symmetry. Now the desired maximum can not be located on the right side, i.e. in the part $[m_2, r]$. Now, the search space reduces to the segment $[l, m_2]$.

- **$f(m_1) = f(m_2)$**

  We can see that either both of these points are in the region of the maximum, or the left point is in the increasing region and the right point is in descending region (here essentially we used increasing/decreasing in strict sense). Thus, the search should be ideally conducted in $[m_1, m_2]$. But this case can be attributed to any of the previous two (in order to simplify the code). Sooner or later the length of the segment will be a little less than a predetermined constant, and the process can be stopped.

Thus, based on the comparison of the values in the two inner points, we find instead of the current segment $[l, r]$, a new segment $[l^\prime, r^\prime]$. Also, the length of the new segment is necessarily shorter than the previous one. Now, repeating all the above steps to this new segment, we again obtain a new, less strict segment.

Sooner or later, the length of the segment will be a little less than the pre-defined constants, accuracy, and the process can be stopped. This method is a numerical one. So we can assume that after stopping the algorithm, approximately that at all points of the segment $[l, r]$ reaches its maximum. Without loss of generality, we can consider the point of maximum to be $l$.

Till now, we didn't impose any restrictions on the choice of points $m_1$ and $m_2$. The process, of course, will depend on the rate of convergence (and error limits). The most common way is to choose the 2 points so that the segment $[l, r]$ is divided equally into 3 equal parts. Thus, we have

$$m_1 = l + \frac{(r - l)}{3}$$

$$m_2 = r - \frac{(r - l)}{3}$$ 

If the choice of $m_1$ and $m_2$ are closer to each other, the convergence rate will increase slightly.

###Run time analysis
$$T(n) = T({2n}/{3}) + 1 = \Theta(\log n)$$

It can visualised as follows: Every time after evaluating the function at 2 points $m_1$ and $m_2$, we are essentially ignoring about ${1 / 3}^{rd}$ length of the segment, either the left or right one. Thus search space is now on a length of ${2n}/{3}$ as compared to the original one. 

Apply [Master's Theorem](https://en.wikipedia.org/wiki/Master_theorem), we get the desired complexity.

###The case of the integer arguments
If the argument to function, $f(x)$ are integers, the segment $[l, r]$ also becomes discrete. Since we do not impose any restrictions on the choice of points $m_1$ and $m_2$, the correctness of the algorithm is not affected. You can still choose $m_1$ and $m_2$, so that they divided the segment $[l, r]$ into 3 approximately equal parts.

The difference can occur the stopping criterion of the algorithm. In this case, ternary search will have to stop, when $(r - l) < 3$. It is because in that case, we can no longer select the point $m_1$ and $m_2$ so varied and different from $l$ and $r$, (which divides the segment into 3 parts as well) and this can lead to infinite loops. So, the ternary search algorithm will stop when $(r - l < 3$ and the remaining number of candidate points will be $(l, l + 1, \ldots, r)$ which will necessarily be point of maxima for the function $f(x)$.

##Implemenation
```cpp
double ternary_search(double l, double r) {
	double eps = 1e-9;				//set the error limit here
	while(r - l > eps) {
		double m1 = l + (r - l) / 3;
		double m2 = r - (r - l) / 3;
		double x = eval(m1);		//evaluates the function at m1
		double y = eval(m2);		//evaluates the function at m2
		if (x < y) {
			l = x;
		}
		else {
			r = y;
		}
	}
	return eval(l);					//return the maximum of f(x) in [l, r]
}
```

Here **eps** is fact the absolute error response (not counting errors due to the inaccurate calculaton of the function).

Instead of the criterion $(r - l > eps)$, we can select a constant number of iterations as a stopping criterion. The number of iterations should be chosen to ensure the required accuracy. Typically, in most programming challenges the error limit is **${10}^{-6}$** and thus **$200 - 300$** iterations suffices. Also, in this case the number of iterations cease to depend on the value/ magnitude of $l$ and $r$, and are chosen only as per the desired relative error.

```cpp
double ternary_search(double l, double r) {
	int iterations = 200;
	for(int i = 1; i <= iterations; ++i) {
		double m1 = l + (r - l) / 3;
		double m2 = r - (r - l) / 3;
		double x = eval(m1);		//evaluates the function at m1
		double y = eval(m2);		//evaluates the function at m2
		if (x < y) {
			l = x;
		}
		else {
			r = y;
		}
	}
	return eval(l);					//return the maximum of f(x) in [l, r]
}
```

## Practice Problems
- [Codechef - Race time](https://www.codechef.com/problems/AMCS03)
- [Hackerearth - Rescuer](https://www.hackerearth.com/september-circuits/algorithm/rescuer-1/)
- [Spoj - Building Construction](http://www.spoj.com/problems/KOPC12A/)
- [Codeforces - Weakness and Poorness](http://codeforces.com/problemset/problem/578/C)
