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

TBD

## Practice Problems

* [Uva 1230 - MODEX](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3671)
* [Uva 374 - Big Mod](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=310)
