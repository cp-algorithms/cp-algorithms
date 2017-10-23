<!--?title Extended Euclidean Algorithm  -->

# Extended Euclidean Algorithm

While the [Euclidean algorithm](../algebra/euclid-algorithm.html) calculates only the greatest common divisor (GCD) of two integers $a$ and $b$, the extended version also finds a way to represent GCD in terms of $a$ and $b$, i.e. coefficients $x$ and $y$ for which:

$$a \cdot x + b \cdot y = {\rm gcd} (a, b)$$

## Algorithm

The changes to the original algorithm are very simple. All we need to do is to figure out how the coefficients $x$ and $y$ change during the transition from $(a, b)$ to $(b \mod a, a)$.

Let us assume we found the coefficients $(x_1, y_1)$ for $(b \mod a, a)$:

$$ (b \mod a) \cdot x_1 + a \cdot y_1 = g$$

and we want to find the pair $(x, y)$ for $(a, b)$:

$$ a \cdot x + b \cdot y = g$$

We can represent $b \mod a$ is:

$$ b \mod a = b - \left\lfloor \frac{b}{a} \right\rfloor \cdot a$$

Substituting this expression in the coefficient equation of $(x1, y1)$ gives:

$$ g = (b \mod a) \cdot x_1 + a \cdot y_1 = \left( b - \left\lfloor \frac{b}{a} \right\rfloor \cdot a \right) \cdot x_1 + a \cdot y_1$$

and finally:

$$ g = b \cdot x_1 + a \cdot \left( y_1 - \left\lfloor \frac{b}{a} \right\rfloor \cdot x_1 \right)$$

We found the values of $x$ and $y$:

$$ \cases{
x = y_1 - \left\lfloor \frac{b}{a} \right\rfloor \cdot x_1 \cr
y = x_1
} $$

## Implementation

```cpp
int gcd (int a, int b, int & x, int & y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
	int x1, y1;
	int d = gcd (b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}
```

The recursive function above returns the GCD and the values of coefficients to `x` and `y` (which are passed by reference to the function).

Base case for the recursion is $a = 0$, when the GCD equals $b$, so the coefficients $x$ and $y$ are $0$ and $1$, respectively. In all other cases the above formulas are used to re-calculate the coefficients on each iteration.

This implementation of extended Euclidean algorithm produces correct results for negative integers as well.

## References

- Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, Introduction to Algorithms (2005)

## Practice Problems

* [10104 - Euclid Problem](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1045)
* [GYM - (J) Once Upon A Time](http://codeforces.com/gym/100963)
* [UVA - 12775 - Gift Dilemma](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4628)
