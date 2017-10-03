<!--?title Newton's method for finding roots -->

# Newton's method for finding roots 

This is an iterative method invented by Isaac Newton around 1664. However, sometimes this method is called the Raphson method, since Raphson invented the same algorithm a few years after Newton, but his article was published much earlier.

The task is as follows. Given the following equation:

$$f(x) = 0$$

We want to solve the equation, more precisely, to find one of its roots (it is assumed that the root exists). It is assumed that $f(x)$ is continuous and differentiable on an interval $[a; b]$.

## Algorithm

The input parameters of the algorithm consist of not only the function $f(x)$ but also the initial approximation - some $x_0$, with which the algorithm starts.

Suppose we have already calculated $x_i$, calculate $x_{i+1}$ as follows. Draw the tangent to the graph of the function $f(x)$ at the point $x = x_i$, and find the point of intersection of this tangent with the $x$-axis. $x_{i+1}$ is set equal to the $x$-coordinateof the point found, and we repeat the whole process from the beginning.

It is not difficult to obtain the following formula:

$$ x_{i+1} = x_i - \frac {f(x_i)} {f^\prime(x_i)} $$

It is intuitively clear that if the function $f(x)$ is "good" (smooth), and $x_i$ is close enough to the root, then $x_{i+1}$ will be even closer to the desired root.

The rate of convergence is quadratic, which, conditionally speaking, means that the number of exact digits in the approximate value $x_i$ doubles with each iteration.

## Application for calculating the square root

## Practice Problems
- [UVa 10428 - The Roots](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1369)
