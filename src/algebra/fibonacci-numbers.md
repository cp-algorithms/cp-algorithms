<!--?title Fibonacci Numbers -->

# Fibonacci Numbers

The Fibonacci sequence is defined as follows:

$$F_0 = 0, F_1 = 1, F_n = F_{n-1} + F_{n-2}$$

The first elements of the sequence ([OEIS A000045](http://oeis.org/A000045)) are:

$$0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...$$

## Properties

Fibonacci numbers possess a lot of interesting properties. Here are a few of them:

* Cassini's identity:
  $$F_{n-1} F_{n+1} - F_n^2 = (-1)^n$$

* The "addition" rule:
  $$F_{n+k} = F_k F_{n+1} + F_{k-1} F_n$$

* Applying the previous identity to the case $k = n$, we get:
  $$F_{2n} = F_n (F_{n+1} + F_{n-1})$$

* From this we can prove by induction that for any positive integer $k$,  $F_{nk}$ is multiple of $F_n$.

* The inverse is also true: if $F_m$ is multiple of $F_n$, then $m$ is multiple of $n$.

* GCD identity:
  $$GCD(F_m, F_n) = F_{GCD(m, n)}$$

* Fibonacci numbers are the worst possible inputs for Euclidean algorithm (see Lame's theorem in [Euclidean algorithm](./algebra/euclid-algorithm.html))

## Fibonacci Coding

We can use the sequence to encode positive integers into binary code words. According to Zeckendorf's theorem, any natural number $n$ can be uniquely represented as a sum of Fibonacci numbers:

$$N = F_{k_1} + F_{k_2} + \ldots + F_{k_r}$$

such that $k_1 \ge k_2 + 2,\ k_2 \ge k_3 + 2,\  \ldots,\  k_r \ge 2$ (i.e.: the representation cannot use two consecutive Fibonacci numbers).

It follows that any number can be uniquely encoded in the Fibonacci coding.
And we can describe this representation with binary codes $d_0 d_1 d_2 \dots d_s 1$, where $d_i$ is $1$ if $F_{i+2}$ is used in the representation.
The code will be appended by a $1$ do indicate the end of the code word.
Notice that this is the only occurrence where two consecutive 1-bits appear.

$$\begin{eqnarray}
1 &=& 1 &=& F_2 &=& (11)_F \\\
2 &=& 2 &=& F_3 &=& (011)_F \\\
6 &=& 5 + 1 &=& F_5 + F_2 &=& (10011)_F \\\
8 &=& 8 &=& F_6 &=& (000011)_F \\\
9 &=& 8 + 1 &=& F_6 + F_2 &=& (100011)_F \\\
19 &=& 13 + 5 + 1 &=& F_7 + F_5 + F_2 &=& (1001011)_F
\end{eqnarray}$$

The encoding of an integer $n$ can be done with a simple greedy algorithm:

1. Iterate through the Fibonacci numbers from the largest to the smallest until you find one less than or equal to $n$.

2. Suppose this number was $F_i$. Subtract $F_i$ from $n$ and put a $1$ in the $i-2$ position of the code word (indexing from 0 from the leftmost to the rightmost bit).

3. Repeat until there is no remainder.

4. Add a final $1$ to the codeword to indicate its end.

To decode a code word, first remove the final $1$. Then, if the $i$-th bit is set (indexing from 0 from the leftmost to the rightmost bit), sum $F_{i+2}$ to the number.

## Formulas for the n-th Fibonacci number

The $n$-th Fibonacci number can be easily found in $O(n)$ by computing the numbers one by one up to $n$. However, there are also faster ways, as we will see.

### Closed-form expression

There is a formula known as "Binet's formula", even though it was already known by Moivre:

$$F_n = \frac{\left(\frac{1 + \sqrt{5}}{2}\right)^n - \left(\frac{1 - \sqrt{5}}{2}\right)^n}{\sqrt{5}}$$

This formula is easy to prove by induction, but it can be deduced with the help of the concept of generating functions or by solving a functional equation.

You can immediately notice that the second term's absolute value is always less than $1$, and it also decreases very rapidly (exponentially). Hence the value of the first term alone is "almost" $F_n$. This can be written strictly as: 

$$F_n = \left[\frac{\left(\frac{1 + \sqrt{5}}{2}\right)^n}{\sqrt{5}}\right]$$

where the square brackets denote rounding to the nearest integer.

As these two formulas would require very high accuracy when working with fractional numbers, they are of little use in practical calculations.

### Matrix form

It is easy to prove the following relation:

$$\begin{pmatrix}F_{n-1} & F_{n} \cr\end{pmatrix} = \begin{pmatrix}F_{n-2} & F_{n-1} \cr\end{pmatrix} \cdot \begin{pmatrix}0 & 1 \cr 1 & 1 \cr\end{pmatrix}$$

Denoting $P \equiv \begin{pmatrix}0 & 1 \cr 1 & 1 \cr\end{pmatrix}$, we have:

$$\begin{pmatrix}F_n & F_{n+1} \cr\end{pmatrix} = \begin{pmatrix}F_0 & F_1 \cr\end{pmatrix} \cdot P^n$$

Thus, in order to find $F_n$, we must raise the matrix $P$ to $n$. This can be done in $O(\log n)$ (see [Binary exponentiation](./algebra/binary-exp.html)).

### Fast Doubling Method

Using above method we can find these equations:
$$ \begin{array}{rll}
                        F_{2k} &= F_k \left( 2F_{k+1} - F_{k} \right). \\\
                        F_{2k+1} &= F_{k+1}^2 + F_{k}^2.
\end{array}$$
Thus using above two equations Fibonacci numbers can be calculated easily by the following code:

```cpp
pair<int, int> fib (int n) {
    if (n == 0)
        return {0, 1};

    auto p = fib(n >> 1);
    int c = p.first * (2 * p.second - p.first);
    int d = p.first * p.first + p.second * p.second;
    if (n & 1)
        return {d, c + d};
    else
        return {c, d};
}
```
The above code returns $F_n$ and $F_{n+1}$ as a pair.

## Periodicity modulo p

Consider the Fibonacci sequence modulo $p$. We will prove the sequence is periodic and the period begins with $F_1 = 1$ (that is, the pre-period contains only $F_0$).

Let us prove this by contradiction. Consider the first $p^2 + 1$ pairs of Fibonacci numbers taken modulo $p$:

$$(F_1,\ F_2),\ (F_2,\ F_3),\ \ldots,\ (F_{p^2 + 1},\ F_{p^2 + 2})$$

There can only be $p$ different remainders modulo $p$, and at most $p^2$ different remainders, so there are at least two identical pairs among them. Thus the sequence is periodic.

We now choose two pairs of identical remainders with the smallest indices in the sequence. Let the pairs be $(F_a,\ F_{a + 1})$ and $(F_b,\ F_{b + 1})$. We will prove that $a = 1$. If this was false, there would be two previous pairs $(F_{a-1},\ F_a)$ and $(F_{b-1},\ F_b)$, which, by the property of Fibonacci numbers, would also be equal. However, this contradicts the fact that we had chosen pairs with the smallest indices, completing our proof.

## Practice Problems

* [SPOJ - Euclid Algorithm Revisited](http://www.spoj.com/problems/MAIN74/)
* [SPOJ - Fibonacci Sum](http://www.spoj.com/problems/FIBOSUM/)
* [HackerRank - Is Fibo](https://www.hackerrank.com/contests/codesprint5/challenges/is-fibo/problem)
* [Project Euler - Even Fibonacci numbers](https://www.hackerrank.com/contests/projecteuler/challenges/euler002/problem)
* [DMOJ - Fibonacci Sequence](https://dmoj.ca/problem/fibonacci)
* [DMOJ - Fibonacci Sequence (Harder)](https://dmoj.ca/problem/fibonacci2)

