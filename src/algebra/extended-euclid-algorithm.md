<!--?title Extended Euclidean Algorithm  -->

# Extended Euclidean Algorithm

While the [euclidean algorithm](../algebra/euclid_algorithm.html) itself only calculates greatest commond divisor (GCD) of two integers $a$ and $b$, the extended version also finds coefficients $x$ and $y$ such that:

$$a \cdot x + b \cdot y = {\rm gcd} (a, b).$$

That is, besides finding the GCD itself, the extended algorithm also finds a way to represent GCD in terms of $a$ and $b$.

## Algorithm

The changes we have to make to the original algorithm are trivial. All we need to do is to observe how the coefficients change when the pairs change from $(a, b)$ to $(b\%a, a)$ (here, percent sign is the operator of taking the remainder).

Let us assume we found the coefficients $(x_1, y_1)$ for $(b\%a, a)$:

$$ (b \% a) \cdot x_1 + a \cdot y_1 = g, $$

and we want to find the pair $(x, y)$ for $(a, b)$:

$$ a \cdot x + b \cdot y = g. $$

Another way to represent $b \% a$ is:

$$ b \% a = b - \left\lfloor \frac{b}{a} \right\rfloor \cdot a. $$

Substituting the above in the coefficient equation of $(x1, y1)$ gives:

$$ g = (b \% a) \cdot x_1 + a \cdot y_1 = \left( b - \left\lfloor \frac{b}{a} \right\rfloor \cdot a \right) \cdot x_1 + a \cdot y_1, $$

and by manipulating it we finally get:

$$ g = b \cdot x_1 + a \cdot \left( y_1 - \left\lfloor \frac{b}{a} \right\rfloor \cdot x_1 \right). $$

We found the values of $x$ and $y$:

$$ \cases{
x = y_1 - \left\lfloor \frac{b}{a} \right\rfloor \cdot x_1, \cr
y = x_1.
} $$

## Implementation

```cpp
int gcd (int a, int b, int & x, int & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	int x1, y1;
	int d = gcd (b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}
```

The recursive function above still returns the GCD, and besides that finds and assigns the values of coefficients to `x` and `y` (which are passed by reference to the function).

Base case for the recursion is $a = 0$, when the GCD is $b$, and the coefficients $x$ and $y$ are $0$ and $1$, respectively. In all other cases the solution presented above is used, each time re-calculating the respective coefficients.

This implementation of extended Euclidean algorithm gives correct results for negative integers as well.

## References

- [Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, Introduction to Algorithms (2005)](http://e-maxx.ru/bookz/files/cormen.djvu)
