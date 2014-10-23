<!--?title Linear Diophantine Equation-->
# Linear Diophantine Equation

A Linear Diophantine Equation (in two variables) is an equation of the general form:

$ax + by = c$

where $a$, $b$, $c$ are given integers, and $x$, $y$ are unknown integers.

In this article, we consider several classical problems on these equations:

* finding any solution
* obtaining all solutions
* finding number of solutions and the solutions themselves in a given interval
* finding a solution with the least amount of unknown

## The degenerate case

A degenerate case that need to be taken care of is when $a = b = 0$. It should be easy to see that we either have no solution or infinite number of solutions (depends on $c = 0$ or not). In the rest of this article, we will ignore this case.

## Finding a solution

To find one solution of the Diophantine equation with 2 unknowns, you can use the Extended Euclidean algorithm. First, assume that $a$ and $b$ are non-negative. When we apply Extended Euclidean algorithm for $a$ and $b$, we can find their greatest common divisor `g` and 2 numbers $x_g$ and $y_g$ such that:

$a x_g + b y_g = g$

If $c$ is divisible by $g = gcd(a, b)$, then the given Diophantine equation has a solution, otherwise it does not have any solution. The proof is straight-forward: a linear combination of two numbers should be divided by their common divisor.

Now supposed that $c$ is divisible by $g$, then we have:

$ a . x_g . (c / g) + b . y_g . (c / g) = c$

i.e. One of the solutions of Diophantine are:

$ x_0 = x_g . (c / g)$,
$ y_0 = y_g . (c / g)$.

The above idea still works when a or b or both of them are negative. We only need to change the sign of $x_0$ and $y_0$ when necessary.

Finally, we can implement this idea like following:

```cpp
int gcd(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd(b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}
```



