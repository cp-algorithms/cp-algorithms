---
tags:
  - Original
---

# Pell's Equation (Pell-Fermat Equation)

## Statement
We are given a natural number $d$. We need to find the smallest positive integer $x$ such that $x^{2} - d \cdot y^{2} = 1$ for some positive integer $y$.

Alternative formulation: We want to find all the possible solutions of the equation $x^{2} - d \cdot y^{2} = 1$.

## Solution
Here we will consider the case when $d$ is not a perfect square and $d>1$. The case when $d$ is a perfect square is trivial.
We can even assume that $d$ is square-free (i.e. it is not divisible by the square of any prime number) as we can absorb the factors of $d$ into $y$.

We can rewrite the equation as:

$$x^{2} - d y^{2} = (x + y \sqrt{d})(x - y \sqrt{d}) = 1$$

This factorization is important because it shows the connection to quadratic irrationals. The first part $(x + y \sqrt{d})$ is always greater than 1, and the second part $(x - y \sqrt{d})$ is always less than 1, since their product is 1.

The norm of an expression $u + v \sqrt{d}$ is defined as $N(u + v \sqrt{d}) = (u + v \sqrt{d})(u - v \sqrt{d}) = u^2 - d v^2$. The norm is multiplicative: $N(ab) = N(a)N(b)$. This property is crucial in the descent argument below.

We will prove that all solutions to Pell's equation are given by powers of the smallest non-trivial solution. Let's assume it to be the minimum possible $x_0 + y_0 \sqrt{d} > 1$. For such a solution, it also holds that $y_0 > 0$, and its $x_0 > 1$ is the smallest possible value for $x$.

## Method of Descent
Suppose there is a solution $u + v \cdot \sqrt{d}$ such that $u^{2} - d \cdot v^{2} = 1$ and is not a power of  $( x_{0} + \sqrt{d} \cdot y_{0} )$
Then it must lie between two powers of $( x_{0} + \sqrt{d} \cdot y_{0} )$. 
i.e, For some $n$,
$$
( x_{0} + \sqrt{d} \cdot y_{0} )^{n}  < u + v \cdot \sqrt{d} < ( x_{0} + \sqrt{d} \cdot y_{0} )^{n+1}
$$

Multiplying the above inequality by $( x_{0} - \sqrt{d} \cdot y_{0} )^{n}$,(which is $> 0$ and $< 1$) we get

$$
1 < (u + v \cdot \sqrt{d})( x_{0} - \sqrt{d} \cdot y_{0} )^{n} < ( x_{0} + \sqrt{d} \cdot y_{0} )
$$
Because both $(u + v \cdot \sqrt{d})$ and $( x_{0} - \sqrt{d} \cdot y_{0} )^{n}$ have norm $1$, their product is also a solution.
But this contradicts our assumption that $( x_{0} + \sqrt{d} \cdot y_{0} )$ is the smallest solution. Therefore, there is no solution between $( x_{0} + \sqrt{d} \cdot y_{0} )^{n}$ and $( x_{0} + \sqrt{d} \cdot y_{0} )^{n+1}$.

Hence, we conclude that all solutions are given by $( x_{0} + \sqrt{d} \cdot y_{0} )^{n}$ for some integer $n$.

## Finding the smallest positive solution
### Expressing the solution in terms of continued fractions
We can express the solution in terms of continued fractions. The continued fraction of $\sqrt{d}$ is periodic. Let's assume the continued fraction of $\sqrt{d}$ is $[a_0; \overline{a_1, a_2, \ldots, a_r}]$. The smallest positive solution is given by the convergent $[a_0; a_1, a_2, \ldots, a_r]$ where $r$ is the period of the continued fraction.

The convergents $p_n/q_n$ are the rational approximations to $\sqrt{d}$ obtained by truncating the continued fraction expansion at each stage. These convergents can be computed recursively. For Pell's equation, the convergent $(p_n, q_n)$ at the end of the period solves $p_n^2 - d q_n^2 = \pm 1$.

Check whether the convergent satisfies Pell's equation. If it does, then the convergent is the smallest positive solution.

Let's take an example to understand this by solving the equation $x^2 - 2 y^2 = 1$.
$\sqrt{2} = [1; \overline{2}] = 1 + 1/(2 + 1/(2 + 1/(2+ ...)))$. The convergents are $1/1, 3/2, 7/5, 17/12, 41/29, 99/70, \ldots$.
Now check for each convergent whether it satisfies Pell's equation. The smallest positive solution is $3/2$.

#### Integer-based continued fraction calculation
For integer-based calculation, see the [Quadratic irrationality section of the continued fractions article](https://cp-algorithms.com/algebra/continued-fractions.html). Here is a sample algorithm in Python:

```python
# Compute the continued fraction expansion of sqrt(n) using integer arithmetic
import math

def continued_fraction_sqrt(n):
    m0 = 0
    d0 = 1
    a0 = int(math.isqrt(n))
    period = []
    m, d, a = m0, d0, a0
    seen = set()
    while (m, d, a) not in seen:
        seen.add((m, d, a))
        m = d * a - m
        d = (n - m * m) // d
        a = (a0 + m) // d
        period.append(a)
    return [a0] + period

# Example: sqrt(7)
print(continued_fraction_sqrt(7))  # Output: [2, 1, 1, 1, 4]
```

This method avoids floating-point errors and is suitable for large $d$.

### Finding the solution using Chakravala method
The Chakravala method is an ancient Indian algorithm to solve Pell's equation. It is based on the Brahmagupta's identity of quadratic decomposition 
$(x_{1}^{2} - n \cdot y_{1}^{2}) \cdot (x_{2}^{2} - n \cdot y_{2}^{2}) = (x_{1} \cdot x_{2} + n \cdot y_{1} \cdot y_{2})^{2} - n \cdot (x_{1} \cdot y_{2} + x_{2} \cdot y_{1})^{2}$
$(x_{1}^{2} - n \cdot y_{1}^{2}) \cdot (x_{2}^{2} - n \cdot y_{2}^{2}) = (x_{1} \cdot x_{2} - n \cdot y_{1} \cdot y_{2})^{2} - n \cdot (x_{1} \cdot y_{2} - x_{2} \cdot y_{1})^{2}$

And Bhaskara's Lemma:
    If $x^{2} - n \cdot y^{2} = k$, then  $( \frac{ m \cdot x + n \cdot y }{k})^{2} - n \cdot ( \frac{ x + m \cdot y }{k})^{2} = \frac{m^2 - n}{k}$

Using above Brahmagupta's identity, If $(x_{1}, y_{1}, k_{1})$ and $(x_{2}, y_{2}, k_{2})$ satisfy $(x_{1}^{2} - y_1^{2}) \cdot (x_{2}^{2} - y_2^{2}) = k_{1} \cdot k_{2}$, then $(x_{1} \cdot x_{2} + n \cdot y_{1} \cdot y_{2}, x_{1} \cdot y_{2} + y_{1} \cdot x_{2}, k_{1} \cdot k_{2})$ is also a solution of $(x_{1} \cdot x_{2} + n \cdot y_{1} \cdot y_{2})^{2} - n \cdot (x_{1} \cdot y_{2} + x_{2} \cdot y_{1})^{2} = k_{1} \cdot k_{2}$

#### Steps
1. Initialization:Choose an initial solution $(p_{0}, q_{0}, m_{0})$ where $p_{0}$ and $q_{0}$ are co-prime such that $p_{0}^{2} - N \cdot q_{0}^{2} = m_{0}$. Typically, start with $p_{0} = \lfloor \sqrt N \rfloor$, $q_{0} = 1$, $m_{0} = p_0^2 - N$.
2. Key step: Find $x_{1}$ such that: $q_{0} \cdot x_{1} \equiv -p_{0} \pmod {\lvert m_{0}\rvert}$ and $\lvert x_{1}^2 - N \rvert$ is minimized.
    Update the triple $(p_{1}, q_{1}, m_{1}) = ( \frac{x_{1} \cdot p_{0} + N \cdot q_{0}}{\lvert m_{0} \rvert}, \frac{p_{0} + x_{1} \cdot q_{0}}{\lvert m_{0} \rvert}, \frac{x_1^{2} - N}{m_{0}})$.
3. Termination: When $m_{k}=1$, the values of $p_{k}$ and $q_{k}$ are the smallest positive solution of the Pell's equation.

##### Example
Let's solve the equation $x^{2} - 13 \cdot y^{2} = 1$ using Chakravala method.
1. Start with $(p_{0}, q_{0}, m_{0}) = (3, 1, -4)$ because $3^2 - 13 \cdot1^2 = -4$.

2. Find $x_{1}$ such that $x_{1} \equiv -3 \pmod {4}$ and $\lvert x_{1}^2 - 13 \rvert$ is minimized.
We get $x_{1} = 1$. Update the triple $(p_{1}, q_{1}, m_{1}) = ( \frac{1 \cdot 3 + 13 \cdot 1}{4}, \frac{3 + 1 \cdot 1}{4}, \frac{1^{2} - 13}{-4}) = (4, 1, 3)$.
3. Substituting $(p_{1}, q_{1}, k_{1}) = (4, 1, 3)$ in key step, we get $x_{2} \equiv -4 \pmod 3$ and minimize $\lvert x_{2}^2 - 13 \rvert$ i.e, $x_{2} = 2$. Update the triple $(p_{2}, q_{2}, m_{2}) = ( \frac{2 \cdot 4 + 13 \cdot 1}{3}, \frac{4 + 2 \cdot 1}{3}, \frac{2^{2} - 13}{-3}) = (7, 2, -3)$. 
4. Substituting $(p_{2}, q_{2}, m_{2}) = (7, 2, -3)$ in key step, we get $2 \cdot x_{3} \equiv -7 \pmod 3$ and minimize $\lvert x_{3}^2 - 13 \rvert$ i.e, $x_{3} = 4$. Update the triple $(p_{3}, q_{3}, m_{3}) = ( \frac{4 \cdot 7 + 13 \cdot 2}{3}, \frac{7 + 4 \cdot 2}{3}, \frac{4^{2} - 13}{-3}) = (18, 5, -1)$.
5. Substituting $(p_{3}, q_{3}, m_{3}) = (18, 5, -1)$ in key step, we get $5 \cdot x_{4} \equiv -18 \pmod 1$ and minimize $\lvert x_{4}^2 - 13 \rvert$ i.e, $x_{4} = 4$. Update the triple $(p_{4}, q_{4}, m_{4}) = ( \frac{4 \cdot 18 + 13 \cdot 5}{1}, \frac{18 + 4 \cdot 5}{1}, \frac{4^{2} - 13}{-1}) = (137, 38, -3)$.
6. Substituting $(p_{4}, q_{4}, m_{4}) = (137, 38, -3)$ in key step, we get $38 \cdot x_{5} \equiv -137 \pmod 3$ and minimize $\lvert x_{5}^2 - 13 \rvert$ i.e, $x_{5} = 2$. Update the triple $(p_{5}, q_{5}, m_{5}) = ( \frac{2 \cdot 137 + 13 \cdot 38}{3}, \frac{137 + 2 \cdot 38}{3}, \frac{2^{2} - 13}{-3}) = (256, 71, 3)$.
7. Substituting $(p_{5}, q_{5}, m_{5}) = (256, 71, 3)$ in key step, we get $71 \cdot x_{6} \equiv -256 \pmod 3$ and minimize $\lvert x_{6}^2 - 13 \rvert$ i.e, $x_{6} = 4$. Update the triple $(p_{6}, q_{6}, m_{6}) = ( \frac{4 \cdot 256 + 13 \cdot 71}{3}, \frac{256 + 4 \cdot 71}{3}, \frac{4^{2} - 13}{3}) = (649, 180, 1)$.

## Implementation
```cpp
bool isSquare(long long n) {
    long long sqrtN = (long long)sqrt(n);
    return sqrtN * sqrtN == n;
}

long long mod(long long a, long long b) {
    return (a % b + b) % b;
}

long long modInv(long long a, long long b) {
    long long b0 = b, x0 = 0, x1 = 1;
    if (b == 1) return 1;
    while (a > 1) {
        long long q = a / b;
        long long temp = b;
        b = a % b;
        a = temp;
        temp = x0;
        x0 = x1 - q * x0;
        x1 = temp;
    }
    if (x1 < 0) x1 += b0;
    return x1;
}


// Chakravala method for solving Pell's equation
pair<long long, long long> chakravala(int n) {
    // Check if n is a perfect square
    if (isSquare(n)) {
        throw invalid_argument("n is a perfect square. No solutions exist for Pell's equation.");
    }

    // Initial values
    double sqrt_n = sqrt(n);
    long long a = (long long)floor(sqrt_n); // Initial a
    long long b = 1;                 // Initial b
    long long k = a * a - n;         // Initial k
   
    int steps = 0; // Step counter for iterations

    // Repeat until k = 1
    while (k != 1) {
        long long absK = abs(k);

        // Find m such that k | (a + bm), and minimize |m^2 - n|
        long long m;
        if (absK == 1) {
            m = (long long)round(sqrt(n)); // round to nearest integer
        } else {
            long long r = mod(-a, absK);    // Negative of a mod(k) // (a + m*b)/|k|
            long long s = modInv(b, absK);     // Modular inverse of b mod(k)
            m = mod(r * s, absK);     // Compute m for (a + b*m) mod(k) = 0

            // Approximate value of m
            // m = m +  ((long long)floor((sqrt_n - m) / absK)) * absK;

            // Adjust m to ensure m < sqrt(n) < m + k
            while (m > sqrt(n)) m -= absK;
            while (m + absK < sqrt_n) m += absK;

            // Select closest value to n
            if (abs(m * m - n) > abs((m + absK) * (m + absK) - n)) {
                m = m + absK;
            }
        }

        // Print the current triple
        cout << "[a = " << a << ", b = " << b << ", k = " << k << "]" << endl;

        // Update a, b, k using the recurrence relations
        long long alpha = a;
        a = (m * a + n * b) / absK;
        b = (alpha + m * b) / absK;
        k = (m * m - n) / k;

        // Increment step counter
        steps++;
    }

    // Print final result
    cout << a << "^2 - " << n << " x " << b << "^2 = 1 in " << steps << " calculations." << endl;

    // Return the solution as a pair (a, b)
    return {a, b};
}

```

## References
- [Pell's equation - Wikipedia](https://en.wikipedia.org/wiki/Pell%27s_equation)
- [Periodic Continued Fractions](https://en.wikipedia.org/wiki/Periodic_continued_fraction)
- [Chakravala Method](http://publications.azimpremjifoundation.org/1630/1/3_The%20Chakravala%20Method.pdf)
- [Pythagorean triples and Pell's equations - Codeforces](https://codeforces.com/blog/entry/116313)

## Problems
- [Project Euler 66](https://projecteuler.net/problem=66)
- [Hackerrank ProjectEuler-066](https://www.hackerrank.com/contests/projecteuler/challenges/euler066/problem)
