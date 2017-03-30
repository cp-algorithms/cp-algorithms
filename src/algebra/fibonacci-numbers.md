<!--?title Fibonacci numbers -->

# Fibonacci numbers

Fibonacci numbers are the numbers in a sequence defined as follows:

$$F_0 = 0, F_1 = 1, F_n = F_{n-1} + F_{n-2}$$

The first several elements of the sequence ([OEIS](http://oeis.org/A000045)) are:

$$0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...$$
## Properties

Fibonacci numbers possess a lot of interesting properties. Here are a few of them:

* Cassini's identity
  $$F_{n-1} F_{n+1} - F_n^2 = (-1)^n$$
* "Addition" rule
  $$F_{n+k} = F_k F_{n+1} + F_{k-1} F_n$$
* Applying the previous identity to the case of $n = k$, we get
  $$F_{2n} = F_n (F_{n+1} + F_{n-1})$$
* From this we can prove by induction that for any positive integer $k$
  $$F_{nk} \equiv 0 (mod F_n)$$
* The inverse is also true:
  If $F_m \equiv 0 (mod F_n)$, then $m \equiv 0 (mod n)$
* GCD identity:
  $$GCD(F_m, F_n) = F_{GCD(m, n)}$$
* Fibonacci numbers are the worst possible inputs for Euclidean algorithm (see Lame's theorem in [Euclidean algorithm](./algebra/euclid-algorithm.html))
