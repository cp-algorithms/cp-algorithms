---
tags:
  - Translated
e_maxx_link: all_submask
---

# Bit operators

When finding solutions to problems, a very important factor is the simplicity and the execution time. Now, in this bitwise operations are very important and you can take advantage of them.

* ## Bit shift operators
### Multiplication and division by powers of 2

There are two operators for shifting bits.

**>>** One bit to the right. Which would be the same as a division by a power of two.

**<<** One bit to the left. And this would be a multiplication, equally by a power of two.

Let's see an example.

Let's say we have a number $N$, which. $N = 4$.

The binary representation of **4** is:

$4_2 = 100$

If we shift one bit to the left, then we would be adding a bit to the end, in this case a 0.

$4_2 << 1 = 100 << 1 = 1000$

$1000 = 8_2$ and clearly, $4 * 2 = 8$

So, for a division by two, it would be exactly the same, but using the operator $<<$.

$4_2 >> 1 = 100 >> 1 = 10$

In this case, we would remove one bit from the end, this is what is called the **least significant bit**, the rightmost bit of the representation.

Of course, the **most significant bit** is the leftmost bit.

And then, how could it carry out operations with other powers, greater than two?

Easy, you just have to remember the exponent of two, to create said power. In other words:

$4 = 2 ^ 2$, so to do multiplication or division operations with **4**, we must move **2 bits**.

$8 = 2 ^ 3$, so for **8** it would be **3 bits**. *And so on*.	


* ## Bitwise operators.

 	* **&** : The bitwise AND operator compares each bit of its first operand with the corresponding bit of its second operand. If both bits are 1, the corresponding result bit is set to 1. Otherwise, the corresponding result bit is set to 0.
 	
 	*  **|** : The bitwise inclusive OR operator compares each bit of its first operand with the corresponding bit of its second operand. If one of the two bits is 1, the corresponding result bit is set to 1. Otherwise, the corresponding result bit is set to 0.

	* **^** : The bitwise exclusive OR (XOR) operator compares each bit of its first operand with the corresponding bit of its second operand. If one bit is 0 and the other bit is 1, the corresponding result bit is set to 1. Otherwise, the corresponding result bit is set to 0.

Examples:

```
  11111111 11110000
& 00000000 01100011
  _________________
  00000000 01100000
```

```
  11111111 11110000
| 00000000 01100011
  _________________
  11111111 11110011
```

```
  11111111 11110000
^ 00000000 01100011
  _________________
  11111111 10010011
```

# Useful tricks.

## Check if a bit is on (to one)

The bit's value can be obtained by shifting the number to the right x times and then bit AND ( & ) on it:

``` cpp
bool check(int number, int bit) {
    return ((number >> bit) & 1);
}
```

## Change the state of a bit n to x

``` cpp
number ^= (-x ^ number) & (1 << n);
```

## Even or Odd

Function to know if a number is even or odd.

True if number is odd, false for number is even.

``` cpp
bool check(int number) {
    return (number & 1);
}
```

## Check if an integer is a power of 2

``` cpp
bool powerTwo = n && !(n & (n - 1));
```

## Brian Kernighan's algorithm.

The idea is to consider only the set bits of an integer by turning off its rightmost set bit (after counting it), so the next iteration of the loop considers the Next Rightmost bit.

The expression **n & (n-1)** can be used to turn off the rightmost set bit of a number **n**. This works like the expression **n-1** flips all bits after the rightmost set bit of n, including the rightmost set bit. Therefore, **n & (n-1)** returns the last flipped bit of **n**.

``` cpp
int countSetBits(int n)
{
    int count = 0;
 
    while (n)
    {
        n = n & (n - 1);
        count++;
    }
 
    return count;
}
```

# Submask Enumeration

## Enumerating all submasks of a given mask

Given a bitmask $m$, you want to efficiently iterate through all of its submasks, that is, masks $s$ in which only bits that were included in mask $m$ are set.

Consider the implementation of this algorithm, based on tricks with bit operations:

```cpp
int s = m;
while (s > 0) {
 ... you can use s ...
 s = (s-1) & m;
}
```

or, using a more compact `for` statement:

```cpp
for (int s=m; s; s=(s-1)&m)
 ... you can use s ...
```

In both variants of the code, the submask equal to zero will not be processed. We can either process it outside the loop, or use a less elegant design, for example:

```cpp
for (int s=m; ; s=(s-1)&m) {
 ... you can use s ...
 if (s==0)  break;
}
```

Let us examine why the above code visits all submasks of $m$, without repetition, and in descending order.

Suppose we have a current bitmask $s$, and we want to move on to the next bitmask. By subtracting from the mask $s$ one unit, we will remove the rightmost set bit and all bits to the right of it will become 1. Then we remove all the "extra" one bits that are not included in the mask $m$ and therefore can't be a part of a submask. We do this removal by using the bitwise operation `(s-1) & m`. As a result, we "cut" mask $s-1$ to determine the highest value that it can take, that is, the next submask after $s$ in descending order.

Thus, this algorithm generates all submasks of this mask in descending order, performing only two operations per iteration.

A special case is when $s = 0$. After executing $s-1$ we get a mask where all bits are set (bit representation of -1), and after `(s-1) & m` we will have that $s$ will be equal to $m$. Therefore, with the mask $s = 0$ be careful — if the loop does not end at zero, the algorithm may enter an infinite loop.

## Iterating through all masks with their submasks. Complexity $O(3^n)$

In many problems, especially those that use bitmask dynamic programming, you want to iterate through all bitmasks and for each mask, iterate through all of its submasks:

```cpp
for (int m=0; m<(1<<n); ++m)
	for (int s=m; s; s=(s-1)&m)
 ... s and m ...
```

Let's prove that the inner loop will execute a total of $O(3^n)$ iterations.

**First proof**: Consider the $i$-th bit. There are exactly three options for it:

1. it is not included in the mask $m$ (and therefore not included in submask $s$),
2. it is included in $m$, but not included in $s$, or
3. it is included in both $m$ and $s$.

As there are a total of $n$ bits, there will be $3^n$ different combinations.

**Second proof**: Note that if mask $m$ has $k$ enabled bits, then it will have $2^k$ submasks. As we have a total of $\binom{n}{k}$ masks with $k$ enabled bits (see [binomial coefficients](../combinatorics/binomial-coefficients.md)), then the total number of combinations for all masks will be:

$$\sum_{k=0}^n \binom{n}{k} \cdot 2^k$$

To calculate this number, note that the sum above is equal to the expansion of $(1+2)^n$ using the binomial theorem. Therefore, we have $3^n$ combinations, as we wanted to prove.

## Practice Problems

* [Atcoder - Close Group](https://atcoder.jp/contests/abc187/tasks/abc187_f)
* [Codeforces - Nuclear Fusion](http://codeforces.com/problemset/problem/71/E)
* [Codeforces - Sandy and Nuts](http://codeforces.com/problemset/problem/599/E)
* [Uva 1439 - Exclusive Access 2](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4185)
* [UVa 11825 - Hackers' Crackdown](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2925)
* [Codeforces - Raising Bacteria](https://codeforces.com/problemset/problem/579/A)
* [Codeforces - Fedor and New Game](https://codeforces.com/problemset/problem/467/B)
* [Codeforces - And Then There Were K](https://codeforces.com/problemset/problem/1527/A)
