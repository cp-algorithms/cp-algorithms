<!--?title Binary Exponentiation-->
# Binary Exponentiation

Binary exponentiation is a trick which allows to calculate $a^n$ using only $O(\log n)$ multiplications (instead of $O(n)$ multiplications required by naive approach). 

It also has important applications in many tasks unrelated to arithmetics, since it
can be used with any operations that have the property of **associativity**:

$$(X \cdot Y) \cdot Z = X \cdot (Y \cdot Z)$$

Most obviously this applies to modular multiplication, to multiplication of matrices and
to other problems which we will discuss below.

## Algorithm

Raising $a$ to the power of $n$ is expressed naively as multiplication by $a$ done $n - 1$ times:
$a^{n} = a \cdot a \cdot \ldots \cdot a$. However, this approach is not practical for large $a$ or $n$. 

Recall that
$a^{b+c} = a^b \cdot a^c$ and $a^{2b} = a^b \cdot a^b = (a^b)^2$.

Let's write $n$ in binary system, for example:

$$3^{11} = 3^{1011_{2}} = 3^{8} \cdot 3^{2} \cdot 3^{1}$$

So we only need to find the sequence of numbers in which each one is a square of the previous one:

$3^{1} = 3$

$3^{2} = (3^1)^2 = 3 \cdot 3 = 9$

$3^{4} = (3^2)^2 = 9 \cdot 9 = 81$

$3^{8} = (3^4)^2 = 81 \cdot 81 = 6561$

The get the final answer, we multiply three of them (skipping $3^4$ because corresponding bit in $n$ is zero):
$3^{11} = 6561 \cdot 9 \cdot 3 = 177147$.

The complexity of this algorithm is $O(\log n)$: there are $\log n$ powers of $a$ to be calculated, and at most $\log n$ multiplications are required to get the final answer from them.

A recursive approach expresses the same idea as a recursion: 

$a^n = (a^{n/2})^2$ for even $n$,
$a^n = (a^{(n-1)/2})^2 \cdot a$ for odd $n$,
$a^1 = a$.

## Implementation

The first approach described above can be implemented with a single loop.

**Non-recursive** approach in Python 3 <span class="toggle-code">Show/Hide</span>:
```python
def binpow(a, b):
    res = 1
    cur = a
    while b > 0:
	    if b & 1:
		    res *= cur
	    cur *= cur
	    b >>= 1
    return res
```
Approach in C++ <span class="toggle-code">Show/Hide</span>:
```cpp
long long binpow(long long a,long long b)
{
	long long res = 1;
	while (b){
		if (b & 1) res = res * a;
		a = (a * a);
		b >>= 1;
	}
	return res;
}
```
This approach builds the result starting from smallest degrees of $a$. If we use recursion
instead of loop we can work in "inverse" direction, starting from largest degrees and dividing
$b$ by two at each step.

**Recursive** approach in Python 3 <span class="toggle-code">Show/Hide</span>:
```python
def binpow(a, b):
    if b == 1:
	    return a
    res = binpow(a, b // 2)
    return res * res * (a if b % 2 != 0 else 1)
```
Approach in C++ <span class="toggle-code">Show/Hide</span>:
```cpp
long long binpow(long long a,long long b)
{
	if (b == 1) return a;
	long long res = binpow(a, b/2);
	if (b % 2) return res*res*a;
	else return res * res;
}
```

## Applications

### Effective computation of Fibonacci Numbers

**Problem:** Compute $n$-th Fibonacci number $F_n$.

**Solution:** For more details, see the [Fibonacci Sequence article](./algebra/fibonacci-numbers.html). We will only go through an overview of the algorithm. To compute the next Fibonacci number, only the two previous ones are needed, as $F_n = F_{n-1} + F_{n-2}$. We can build a $2 \times 2$ matrix that matches this transformation: the transition from $F_i$ and $F_{i+1}$ to $F_{i+1}$ and $F_{i+2}$. For example, applying this transformation to the pair $F_0$ and $F_1$ would change it into $F_1$ and $F_2$. Therefore, we can raise this transformation matrix to the $n$-th power to find $F_n$ in time complexity $O(\log n)$.

### Applying a permutation $k$ times

**Problem:** You are given a sequence of length $n$ and required to apply a given permutation $k$ times.

**Solution:** Simply apply the permutation using binary exponentiation. This would give you a time complexity of $O(n \log k)$.

(**Note:** This task can be solved more efficiently in linear time complexity by building the permutation graph and considering each cycle independently. You could then compute $k$ modulo the size of the cycle to find the final position for each number.)

### Fast application of a set of geometric operations to points

**Problem:** Given $n$ points $p_i$, you are required to apply $m$ transformations to each of these points multiple times (each transformation will have a number of repetitions). The transformation can be either a shift, a scaling or rotation around a given axis by a given angle.

**Solution:** Let's look at how the different types of transformations change the coordinates:

* Shift operation: adds a constant to each of the coordinates.
* Scaling operation: multiplies each of the coordinates by some constant.
* Rotation operation: each of the new coordinates can be represented as a linear combination of the old ones

As you can see, each of the transformations can be represented as a linear operation on the coordinates. Thus, a transformation can be written as a $4 \times 4$ matrix of the form:

$$\begin{pmatrix}
a_{11} & a_ {12} & a_ {13} & a_ {14} \\\
a_{21} & a_ {22} & a_ {23} & a_ {24} \\\
a_{31} & a_ {32} & a_ {33} & a_ {34} \\\
a_{41} & a_ {42} & a_ {43} & a_ {44} \\\
\end{pmatrix}$$

that, when multiplied by a vector with the old coordinates and an unit gives a new vector with the new coordinates and an unit:

$$\begin{pmatrix} x & y & z & 1 \end{pmatrix} \cdot
\begin{pmatrix}
a_{11} & a_ {12} & a_ {13} & a_ {14} \\\
a_{21} & a_ {22} & a_ {23} & a_ {24} \\\
a_{31} & a_ {32} & a_ {33} & a_ {34} \\\
a_{41} & a_ {42} & a_ {43} & a_ {44} \\\
\end{pmatrix}
 = \begin{pmatrix} x' & y' & z' & 1 \end{pmatrix}$$

(Why introduce a fictitious fourth coordinate, you ask? Without this, it would not be possible to implement the shift operation, as it requires us to add a constant to the coordinates. Without the fictitious coordinates, we would only be able to apply a linear combination to the coordinates, not being able to add a constant.)

Now, once every transformation is described as a matrix, the repetitions can be described by the transformation matrix raised to the number of repetitions (which can be found using binary exponentiation). This way, all operations can be applied to the $n$ points in a time complexity of $O(n \cdot m \cdot \log{repetitions})$.

If you couldn't figure out how to describe each operation as matrix, here are some examples:

* Shift operation: shift $x$ by $5$, $y$ by $7$ and $z$ by $9$.
$$\begin{pmatrix}
1 & 0 & 0 & 0 \\\
0 & 1 & 0 & 0 \\\
0 & 0 & 1 & 0 \\\
5 & 7 & 9 & 1 \\\
\end{pmatrix}$$

* Scaling operation: scale the $x$ coordinate by $10$ and the other two by $5$.
$$\begin{pmatrix}
10 & 0 & 0 & 0 \\\
0 & 5 & 0 & 0 \\\
0 & 0 & 5 & 0 \\\
0 & 0 & 0 & 1 \\\
\end{pmatrix}$$

* Rotation operation: rotate $\theta$ degrees over the $x$ coordinate following the right-hand rule (counter-clockwise direction).
$$\begin{pmatrix}
1 & 0 & 0 & 0 \\\
0 & \cos \theta & -\sin \theta & 0 \\\
0 & \sin \theta & \cos \theta & 0 \\\
0 & 0 & 0 & 1 \\\
\end{pmatrix}$$

### Number of paths of length $k$ in a graph

**Problem:** Given a directed unweighted graph of $n$ vertices, compute the number of paths of length $k$ from any vertex $u$ to any other vertex $v$.

**Solution:** This problem is considered in more detail in [a separate article](./graph/fixed_length_paths.html). The algorithm consists of raising the adjacency matrix $M$ of the graph (a matrix where $m_{ij} = 1$ if there is an edge from $i$ to $j$, or $0$ otherwise) to the $k$-th power. Now $m_{ij}$ will be the number of paths of length $k$ from $i$ to $j$. The time complexity of this solution is $O(n^3 \log k)$.

(**Note:** In that same article, another variation of this problem is considered: when the edges are weighted and it is required to find the minimum weight path containing exactly $k$ edges. As shown in that article, this problem is also solved by exponentiation of the adjacency matrix. The matrix would have the weight of the edge from $i$ to $j$, or $\infty$ if there is no such edge. Instead of the usual operation of multiplying two matrices, a modified one should be used: instead of multiplication, a sum is taken, and instead of a summation, a minimum is taken. That is, $result_{ij} = \min\limits_{1\ \leq\ k\ \leq\ n}(a_{ik} + b_{kj})$).

### Variation of binary exponentiation: multiplying two numbers modulo

**Problem:** Multiply two numbers $a$ and $b$ modulo $m$. $a$ and $b$ fit in the built-in data types, but their product is too big to fit in a 64-bit integer. The idea is to compute $a \cdot b \pmod m$ without using bignum arithmetics.

**Solution:** We simply apply the binary construction algorithm described above, only performing additions instead of multiplications. In other words, we have "expanded" the multiplication of two numbers to $O (\log m)$ operations of addition and multiplication by two (which, in essence, is an addition).

$$a \cdot b = \\left\\{\begin{array}{ll}
2 \times \left\lfloor{\frac{a}{2}}\right\rfloor \cdot b & \mbox{if }\ a\ is\ even \\\
2 \times \left\lfloor{\frac{a}{2}}\right\rfloor \cdot b + b & \mbox{if }\ a\ is\ odd \\\
\end{array}\\right.$$

(**Note:** You can solve this task in a different way by using floating-point operations. First compute the expression $\frac{a \cdot b}{m}$ using floating-point numbers and cast it to an unsigned integer $q$. Subtract $q \cdot m$ from $a \cdot b$ using unsigned integer arithmetics and take it modulo $m$ to find the answer. This solution looks rather unreliable, but it is very fast, and very easy to implement. See [here](https://cs.stackexchange.com/questions/77016/modular-multiplication) for more information.)

## Practice Problems

* [UVa 1230 - MODEX](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3671)
* [UVa 374 - Big Mod](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=310)
