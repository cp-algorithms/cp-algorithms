<!--?title 15 Puzzle Game: Existence Of The Solution -->

# 15 Puzzle Game: Existence Of The Solution

This game is played on a $4 \times 4$ board. On this board there are $15$ playing tiles numbered from 1 to 15. One cell is left empty (denoted by 0). You need to get the board to the position presented below by repeatedly moving one of the tiles to the free space:

$$\begin{matrix} 1 & 2 & 3 & 4 \\\\ 5 & 6 & 7 & 8 \\\\ 9 & 10 & 11 & 12 \\\\ 13 & 14 & 15 & 0 \end{matrix}$$

The game "15 Puzzle” was created by Noyes Chapman in 1880.

## Existence Of The Solution

Let's consider this problem: given a position on the board, determine whether a sequence of moves which leads to a solution exists.

Suppose we have some position on the board:

$$\begin{matrix} a_1 & a_2 & a_3 & a_4 \\\\ a_5 & a_6 & a_7 & a_8 \\\\ a_9 & a_{10} & a_{11} & a_{12} \\\\ a_{13} & a_{14} & a_{15} & a_{16} \end{matrix}$$

where one of the elements equals zero and indicates an empty cell $a_z  = 0$

Let’s consider the permutation:

$$a_1 a_2 ... a_{z-1} a_{z+1} ... a_{15} a_{16}$$

i.e. the permutation of numbers corresponding to the position on the board without a zero element

Let $N$ be the number of inversions in this permutation (i.e. the number of such elements $a_i$  and $a_j$  that $i < j$, but $a_i  > a_j$).

Suppose $K$ is an index of a row where the empty element is located (i.e. using our convention, $K = (z - 1) \div \ 4 + 1$).

Then, **the solution exists iff $N + K$ is even**.

## Implementation

The algorithm above can be illustrated with the following program code:

```cpp
int a[16];
for (int i=0; i<16; ++i)
    cin >> a[i];

int inv = 0;
for (int i=0; i<16; ++i)
    if (a[i])
        for (int j=0; j<i; ++j)
            if (a[j] > a[i])
                ++inv;
for (int i=0; i<16; ++i)
    if (a[i] == 0)
        inv += 1 + i / 4;

puts ((inv & 1) ? "No Solution" : "Solution Exists");
```

## Proof

In 1879 Johnson proved that if $N + K$ is odd, then the solution doesn’t exist, and in the same year Story proved that all positions when $N + K$ is even have a solution.

However, all these proofs were quite complex.

In 1999 Archer proposed a much simpler proof (you can download his article [here](http://www.cs.cmu.edu/afs/cs/academic/class/15859-f01/www/notes/15-puzzle.pdf)).

## Practice Problems

* [Hackerrank - N-puzzle](https://www.hackerrank.com/challenges/n-puzzle)
