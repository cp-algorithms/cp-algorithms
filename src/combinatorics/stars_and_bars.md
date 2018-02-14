<!--?title Stars and bars -->
# Stars and bars

Stars and bars is a mathematical technique for solving certain combinatorial problems.
It occurs whenever you want to count the number of ways to group identical objects.

## Theorem

The number of ways to put $n$ identical objects into $k$ labeled boxes is
$$\binom{n + k - 1}{n}.$$

The proof involves turning the objects into stars and separating the boxes using bars (therefore the name).
E.g. we can represent with $\bigstar | \bigstar \bigstar |~| \bigstar \bigstar$ the following situation:
in the first box is one object, in the second box are two objects, the third one is empty and in the last box are two objects.
This is one way of dividing 5 objects into 4 boxes.

It should be pretty obvious, that every partition can be represented using $n$ stars and $k - 1$ bars and every stars and bars permutation using $n$ stars and $k - 1$ bars represents one partition.
Therefore the number of ways to divide $n$ identical objects into $k$ labeled boxes is the same number as there are permutations of $n$ stars and $k - 1$ bars.
The [Binomial Coefficient](./combinatorics/binomial-coefficients.html) gives us the desired formula.

## Number of non-negative integer sums

This problem is a direct application of the theorem.

You want to count the number of solution of the equation 
$$x_1 + x_2 + \dots + x_k = n$$
with $x_i \ge 0$.

Again we can represent a solution using stars and bars.
E.g. the solution $1 + 3 + 0 = 4$ for $n = 4$, $k = 3$ can be represented using $\bigstar | \bigstar \bigstar \bigstar |$.

It is easy to see, that this is exactly the stars an bars theorem.
Therefore the solution is $\binom{n + k - 1}{n}$.

## Number of lower-bound integer sums

This can easily be extended to integer sums with different lower bounds.
I.e. we want to count the number of solutions for  the equation
$$x_1 + x_2 + \dots + x_k = n$$
with $x_i \ge a_i$.

After substituting $x_i' := x_i - a_i$ we receive the modified equation
$$(x_1' + a_i) + (x_2' + a_i) + \dots + (x_k' + a_k) = n$$
$$\Leftrightarrow ~ ~ x_1' + x_2' + \dots + x_k' = n - a_1 - a_2 - \dots - a_k$$
with $x_i' \ge 0$.
So we have reduced the problem to the simpler case with $x_i' \ge 0$ and again can apply the stars and bars theorem.
