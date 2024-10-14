---
tags:
  - Translated
e_maxx_link: simpson_integrating
---

# Integration by Simpson's formula

We are going to calculate the value of a definite integral

$$\int_a ^ b f (x) dx$$

The solution described here was published in one of the dissertations of **Thomas Simpson** in 1743.

## Simpson's formula

Let $n$ be some natural number. We divide the integration segment $[a, b]$ into $2n$ equal parts:

$$x_i = a + i h, ~~ i = 0 \ldots 2n,$$

$$h = \frac {b-a} {2n}.$$

Now we calculate the integral separately on each of the segments $[x_ {2i-2}, x_ {2i}]$, $i = 1 \ldots n$, and then add all the values.

So, suppose we consider the next segment $[x_ {2i-2}, x_ {2i}],  i = 1 \ldots n$. Replace the function $f(x)$ on it with a parabola $P(x)$ passing through 3 points $(x_ {2i-2}, x_ {2i-1}, x_ {2i})$. Such a parabola always exists and is unique; it can be found analytically.
For instance we could construct it using the Lagrange polynomial interpolation.
The only remaining thing left to do is to integrate this polynomial.
If you do this for a general function $f$, you receive a remarkably simple expression:

$$\int_{x_ {2i-2}} ^ {x_ {2i}} f (x) ~dx \approx \int_{x_ {2i-2}} ^ {x_ {2i}} P (x) ~dx = \left(f(x_{2i-2}) + 4f(x_{2i-1})+(f(x_{2i})\right)\frac {h} {3} $$

Adding these values over all segments, we obtain the final **Simpson's formula**:

$$\int_a ^ b f (x) dx \approx \left(f (x_0) + 4 f (x_1) + 2 f (x_2) + 4f(x_3) + 2 f(x_4) + \ldots + 4 f(x_{2N-1}) + f(x_{2N}) \right)\frac {h} {3} $$

## Error

The error in approximating an integral by Simpson's formula is

$$ -\tfrac{1}{90} \left(\tfrac{b-a}{2}\right)^5 f^{(4)}(\xi)$$

where $\xi$ is some number between $a$ and $b$.

The error is asymptotically proportional to $(b-a)^5$. However, the above derivations suggest an error proportional to $(b-a)^4$. Simpson's rule gains an extra order because the points at which the integrand is evaluated are distributed symmetrically in the interval $[a, b]$.

## Implementation

Here, $f(x)$ is some user-defined function.

```cpp
const int N = 1000 * 1000; // number of steps (already multiplied by 2)

double simpson_integration(double a, double b){
    double h = (b - a) / N;
    double s = f(a) + f(b); // a = x_0 and b = x_2n
    for (int i = 1; i <= N - 1; ++i) { // Refer to final Simpson's formula
        double x = a + h * i;
        s += f(x) * ((i & 1) ? 4 : 2);
    }
    s *= h / 3;
    return s;
}
```

## Practice Problems

* [Latin American Regionals 2012 - Environment Protection](https://matcomgrader.com/problem/9335/environment-protection/)
