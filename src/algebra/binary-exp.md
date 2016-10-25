<!--?title Binary Exponentiation-->
#Binary Exponentiation

Raising `a` to the power of `b` is expressed naively as multiplication of `a` taken `b` times:
$a^{b} = a \cdot a \cdot \ldots \cdot a$.

However this approach is not practical for large `a` or `b`. **Binary exponentiation** is a
simple trick. We know from school that:

$$a^{b+c} = a^{b} \cdot a^{c} \qquad and \qquad a^{2b} = a^{b} \cdot a^{b} = (a^{b})^{2}$$

Let us then write `b` in binary system, for example:

$$3^{11} = 3^{1011_{2}} = 3^{8} \cdot 3^{2} \cdot 3^{1}$$

So we need only find sequence of squared numbers:

$3^{1} = 3$
$3^{2} = (3^{1})^{2} = 3 \cdot 3 = 9$
$3^{4} = (3^{2})^{2} = 9 \cdot 9 = 81$
$3^{8} = (3^{4})^{2} = 81 \cdot 81 = 6561$

And multiply three of them (skipping `3^{4}` because corresponding bit in `b` is zero):
$\quad 3^{11} = 6561 \cdot 9 \cdot 3 = 177147$

This approach has important applications in many tasks not related to arithmetics, since it
can be used with any operations having the property of **associativity**:

$$(X \cdot Y) \cdot Z = X \cdot (Y \cdot Z)$$

Most obviously this applies to modular multiplication, then to multiplication of matrices and
to other problems which we will discuss below. As another example - in Ancient Egypt the
same approach was used for simple multiplication (by summing up members of the sequence
`a`, `2a`, `4a`, `8a` according to binary representation of multiplier `b`) -
and it is still used inside CPUs of contemporary computers!

###Algorithm

The approach described above could be easily implemented with a single loop.

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
This approach builds the result starting from smallest degrees of `a`. If we use recursion
instead of loop we can work in "inverse" direction, starting from largest degrees and dividing
`b` in two at each step.

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
We can explain this last approach mathematically:
$a^{b} = (a^{b/2})^2 \quad$ for even `b`,
$a^{b} = (a^{(b-1)/2})^2 \cdot a \quad$ for odd `b`,
$a^{1} = a$.

## Practice Problems

* [Uva 1230 - MODEX](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3671)
* [Uva 374 - Big Mod](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=310)
