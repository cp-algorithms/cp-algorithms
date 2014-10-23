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

To find one solution of the Diophantine equation with 2 unknowns, you can use the Extended Euclidean algorithm. First, assume that $a$ and $b$ are non-negative. When we apply Extended Euclidean algorithm for $a$ and $b$, we can find their greatest common divisor $g$ and 2 numbers $x_g$ and $y_g$ such that:

$a x_g + b y_g = g$

If $c$ is divisible by $g = gcd(a, b)$, then the given Diophantine equation has a solution, otherwise it does not have any solution. The proof is straight-forward: a linear combination of two numbers should be divided by their common divisor.

Now supposed that $c$ is divisible by $g$, then we have:

$ a . x_g . (c / g) + b . y_g . (c / g) = c$

i.e. One of the solutions of Diophantine are:

$ x_0 = x_g . (c / g)$,
$ y_0 = y_g . (c / g)$.

The above idea still works when $a$ or $b$ or both of them are negative. We only need to change the sign of $x_0$ and $y_0$ when necessary.

Finally, we can implement this idea like following (note that this piece of code does not take care of the case $a = b = 0$:

```
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

## Getting all solutions

From one solution $(x_0, y_0)$, we can obtain all the solutions of the given equation.

Let $g = gcd(a, b)$ and let $x_0, y_0$ be integers which satisfy the following:

$a . x_0 + b . y_0 = c$

Now, we should see that adding $b / g$ to $x_0$, and, at the same time subtracting $a / g$ from $y_0$ will not break the equality:

$a . (x_0 + b / g) + b . (y_0 - a / g) = a . x_0 + b . y_0 + a . b / g - b . a / g = c$

Obviously, this process can be repeated any number of times, i.e. all the number of the form:

$x = x_0 + k . b / g$
$y = y_0 - k . a / g$

are solutions of the given Diophantine equation.

Moreover, this is the set of all possible solutions of the given Diophantine equation.

## Finding the number of solutions and the solutions in a given interval

From previous section, it should be clear that if we don't impose any restrictions on the solutions, there would be infinte number of them. So in this section, we make some restrictions on the interval of $x$ and $y$, and we will try to count & enumerate all the solutions.

Let there be two intervals: $[min_x; max_x]$ and $[min_y; max_y]$ and let say we only want to find the solutions in these two intervals.

Note that if $a$ or $b$ is $0$, then the problem only has one solution. We don't consider this case here.

First, we can find a solution which have minimum value of $x$, such that $x \ge min_x$. To do this, we first find any solution of the Diophantine equation. Then, we shift this solution to get $x \ge min_x$ (using what we know about the set of all solutions in previous section). This can be done in $O(1)$. Denote this minimum value of $x$ by $lx_1$.

Similarly, we can find the maximum value of $x$ which satisfy $x \le max_x$. Denote this maximum value of $x$ by $rx_1$.

Similarly, we can find the minimum value of $y$ $(y \ge min_y)$ and maximum values of $y$ $(y \le max_y)$. Denote the corresponding values of $x$ by $lx_2$ and $rx_2$.

The final solution is all solutions with x in intersection of $[lx_1, rx_1]$ and $[lx_2, rx_2]$. Let denote this intersection by $[lx, rx]$.

Following is the code implementing this idea:

```cpp
void shift_solution (int & x, int & y, int a, int b, int cnt) {
	x += cnt * b;
	y -= cnt * a;
}
 
int find_all_solutions (int a, int b, int c, int minx, int maxx, int miny, int maxy) {
	int x, y, g;
	if (! find_any_solution (a, b, c, x, y, g))
		return 0;
	a /= g;  b /= g;
 
	int sign_a = a>0 ? +1 : -1;
	int sign_b = b>0 ? +1 : -1;
 
	shift_solution (x, y, a, b, (minx - x) / b);
	if (x < minx)
		shift_solution (x, y, a, b, sign_b);
	if (x > maxx)
		return 0;
	int lx1 = x;
 
	shift_solution (x, y, a, b, (maxx - x) / b);
	if (x > maxx)
		shift_solution (x, y, a, b, -sign_b);
	int rx1 = x;
 
	shift_solution (x, y, a, b, - (miny - y) / a);
	if (y < miny)
		shift_solution (x, y, a, b, -sign_a);
	if (y > maxy)
		return 0;
	int lx2 = x;
 
	shift_solution (x, y, a, b, - (maxy - y) / a);
	if (y > maxy)
		shift_solution (x, y, a, b, sign_a);
	int rx2 = x;
 
	if (lx2 > rx2)
		swap (lx2, rx2);
	int lx = max (lx1, lx2);
	int rx = min (rx1, rx2);
 
	return (rx - lx) / abs(b) + 1;
}
```

When we have $lx$ and $rx$, it is simple to enumerate through all the solutions. Just need to iterate through $x = lx + k . b$ and find the corresponding $y$ using the equation $a x + b y = c$.

## Find the solution with minimum value of $x + y$

Here, $x$ and $y$ also need to be given some restriction, otherwise, the answer may become negative infinity.

The idea is similar to previous section: We find any solution of the Diophantine equation, and then shift the solution to satisfy some conditions.

Finally, use the knowledge of the set of all solutions to find the minimum:

$x' = x + k . (b / g)$,

$y' = y - k . (a / g)$.

Note that $x + y$ change as follows:

$x' + y' = x + y + k . (b/g - a/g) = x + y + k . (b - a) / g$.

If $a < b$, we need to select smallest possible value of $k$. If $a > b$, we need to select the largest possible value of $k$. If $a = b$, all solution will have the same sum $x + y$.

## Problems in Online Judge

* [SGU 106](http://acm.sgu.ru/problem.php?contest=0&problem=106)
