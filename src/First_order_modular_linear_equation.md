<!--?title Modular linear equation -->
#Modular linear equation of the first order#

##Formulation of the problem##

This equation is of the form:

$$a \cdot x = b \pmod n$$,

Where $a$, $b$ and $n$ are given integers and $x$ is an unknown integer.

It is required to find the value $x$ lying in the interval [0, n-1] (since on the entire number line, clearly, there can be infinitely many solutions that will differ from each other in $n \cdot k$ , where k - any integer). If the solution is not unique, then we will consider how to get all the solutions.

##Solution by finding the Reverse element##

Let us first consider a simpler case-when $a$ and $n$ are coprime(gcd(a, n) = 1) or relatively prime to each other. Then one can find the inverse of $a$, and multiplying both sides of the equation by inverse of $a$, we can get a unique solution.

$$x = b \cdot a ^ {- 1} \pmod n$$

Now consider the case when a and n not coprime(gcd(a, n) != 1). Then the solution will not always exist (for example, $2\cdot x = 1\pmod 4$ ).

Let $g = {\rm gcd (a, n)}$ i.e. Their greatest common divisor (which in this case is greater than one).

Then, if $b$ is not divisible by $g$, then there is no solution. In fact, for any $x$ the left side of the equation $(a\cdot x)\pmod n$ , is always divisible by $g$, while the right-hand side does not divisible by it, hence it follows that there are no solutions.

If $g$ divides $b$, then dividing both sides of the equation into this g(i.e., dividing $a$, $b$ and $n$ on $g$), we come to a new equation:

$$a^\prime\cdot x = b^\prime\pmod{n^\prime}$$

in which $a^\prime$ and $n^\prime$ will already be reatively prime, and we have already learned such an equation. We denote its solution in terms of $x^\prime$ .

It is clear that this $x^\prime$ will also be a solution of the original equation. However, if g > 1 , then it will not be the only solution. It can be shown that the original equation will have exactly g solutions, and they will look like:

$x_i = (x^\prime + i\cdot n^\prime) \pmod n$,

$i = 0\ldots(g-1)$

Summarizing, we can say that the number of solutions of the linear modular equation is equal to either $g = {\rm gcd (a, n)}$ , or zero.

##Solution with the Advanced Euclidean Algorithm##

We reduce our modular equation to the Diophantine equation as follows:

$$a \cdot x + n \cdot k = b$$,

Where $x$ and $k$ are unknown integers.

The method of solving this equation is described in the corresponding article Linear Diophantine equations of the second order , and it consists in the application of the Euclidean Extended Algorithm .

It also describes the method of obtaining all solutions of this equation from one solution found, and, incidentally, this method, when carefully considered, is absolutely equivalent to the method described in the preceding paragraph.

[Extended Euclidean Algorithm](https://e-maxx-eng.appspot.com/algebra/euclid-algorithm.html)

[Modular Inverse](https://e-maxx-eng.appspot.com/algebra/module-inverse.html)
