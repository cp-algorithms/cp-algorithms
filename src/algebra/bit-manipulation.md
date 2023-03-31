# Binary number

A **binary number** is a number expressed in the base-2 numeral system or binary numeral system, a method of mathematical expression which uses only two symbols: typically "0" (zero) and "1" (one).

We are talking about a numerical system of great importance in technological development. Among some of the most outstanding applications are the representation of images and texts, in the field of electronics. With the combination of zeros and ones, any number can be represented on a decimal basis, making communication with electronic devices easier for humans. In addition to translating the different programming languages, to a common language where the computer understands.

**In this article I will not talk about how to convert to binary or decimal. There is a lot of information all over the internet on the subject.**

# Bit manipulation

When finding solutions to problems, a very important factor is the simplicity and the execution time. Now, in this bitwise operations are very important and you can take advantage of them.

# Bit operators

## Bit shift operators
### Multiplication and division by powers of 2

There are two operators for shifting bits.

$\gg$ One bit to the right. Which would be the same as a division by a power of two.

$\ll$ One bit to the left. And this would be a multiplication, equally by a power of two.

Let's see an example.

Let's say we have a number $N$, which. $N = 4$.

The binary representation of $4$ is:

$4 = 100_2$

If we shift one bit to the left, then we would be adding a bit to the end, in this case a 0.

$4 \ll 1 = 100_2 \ll 1 = 1000_2$

$1000_2 = 8$ and clearly, $4 * 2 = 8$

So, for a division by two, it would be exactly the same, but using the operator $<<$.

$4 \gg 1 = 100_2 \gg 1 = 10_2$

In this case, we would remove one bit from the end, this is what is called the **least significant bit**, the rightmost bit of the representation.

Of course, the **most significant bit** is the leftmost bit.

And then, how could it carry out operations with other powers, greater than two?

Easy, you just have to remember the exponent of two, to create said power. In other words:

$4 = 2 ^ 2$, so to do multiplication or division operations with **4**, we must move **2 bits**.

$8 = 2 ^ 3$, so for $8$ it would be **3 bits**. *And so on*.	


## Bitwise operators.

```
& : The bitwise AND operator compares each bit of its first operand with the corresponding bit of its second operand. 
    If both bits are 1, the corresponding result bit is set to 1. Otherwise, the corresponding result bit is set to 0.
 	
| : The bitwise inclusive OR operator compares each bit of its first operand with the corresponding bit of its second operand.
    If one of the two bits is 1, the corresponding result bit is set to 1. Otherwise, the corresponding result bit is set to 0.

^ : The bitwise exclusive OR (XOR) operator compares each bit of its first operand with the corresponding bit of its second operand.
    If one bit is 0 and the other bit is 1, the corresponding result bit is set to 1. Otherwise, the corresponding result bit is set to 0.
```

Examples:

```
n         = 01011000
n-1       = 01010111
--------------------
n & (n-1) = 01010000
```

```
n         = 01011000
n-1       = 01010111
--------------------
n | (n-1) = 01011111
```

```
n         = 01011000
n-1       = 01010111
--------------------
n ^ (n-1) = 00001111
```

# Useful tricks.

## A bit is set (1) or cleared (0)

The value of the $x$-th bit can be by shifting the number $x$ positions to the right, the $x$-th bit is the units place, therefore we can extract it by performing a bitwise & with 1

``` cpp
bool check(int number, int x) {
    return ((number >> x) & 1);
}
```

## Parity of a number

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

## Clear the most-right set bit

The expression **n & (n-1)** can be used to turn off the rightmost set bit of a number **n**. This works like the expression **n-1** flips all bits after the rightmost set bit of n, including the rightmost set bit. Therefore, **n & (n-1)** returns the last flipped bit of **n**.

For example, consider the number 52, which is 00110100 in binary, and has a total set of 3 bits.

```
1st iteration of the loop: n = 52

00110100    &               (n)
00110011                    (n-1)
~~~~~~~~
00110000
```

``` 
2nd iteration of the loop: n = 48
 
00110000    &               (n)
00101111                    (n-1)
~~~~~~~~
00100000
``` 
 
```
3rd iteration of the loop: n = 32
 
00100000    &               (n)
00011111                    (n-1)
~~~~~~~~
00000000                    (n = 0)
```

## Brian Kernighan's algorithm.

We can count the number of bits set with the above expression.

The idea is to consider only the set bits of an integer by turning off its rightmost set bit (after counting it), so the next iteration of the loop considers the Next Rightmost bit.

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

Additionally, there are also predefined functions in C++, to count the number of bits in a representation.

1. ```__builtin_popcount(number)``` number of bits set.
2. ```__builtin_ctz(number)``` number of bits cleared.

## Practice Problems

* [Codeforces - Raising Bacteria](https://codeforces.com/problemset/problem/579/A)
* [Codeforces - Fedor and New Game](https://codeforces.com/problemset/problem/467/B)
* [Codeforces - And Then There Were K](https://codeforces.com/problemset/problem/1527/A)
