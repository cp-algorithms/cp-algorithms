<!--?title 15 Puzzle Game: Existence Of The Solution -->

# 15 Puzzle Game: Existence Of The Solution

This game is played on board, which size is 4×4 cells. On this board there are 15 playing tiles numbered from 1 to 15. One cell is left empty. It is required to come to position presented below by moving some tiles to the free space:

![some image description](http://e-maxx.ru/tex2png/cache/a20a65d11dd5382b08465279d9bef0ca.png)

The game "15 Puzzle” was created by Noyes Chapman in 1880.



## Existence Of The Solution



Let's consider this problem: given position on the board to determine whether exists such a sequence of moves, which leads to a solution.

Suppose, we have some position on the board:

![some image description](http://e-maxx.ru/tex2png/cache/a20a65d11dd5382b08465279d9bef0ca.png)

where one of the elements equals zero and indicates an empty cell $a_z  = 0$

Let’s consider the permutation:

![some image description](http://e-maxx.ru/tex2png/cache/37db640bfba4e1e8372e3098c8e0b1f1.png)

(i.e. the permutation of numbers corresponding to the position on the board, without a zeroth element)

Let $N$ be a quantity of inversions in this permutation (i.e. the quantity of such elements $a_i$  and $a_j$  that $i < j$, but $a_i  > a_j$).

Suppose $K$ is an index of a row where the empty element is located (i.e. in our indications $K = (z - 1) \ div \ 4 + 1$).

Then, **the solution exists iff $N + K$ is even**.



## Implementation



The algorithm above can be illustrated with the following program code:

````cpp
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
````


## Proof


In 1879 Johnson proved that if $N + K$ is odd, then the solution doesn’t exist, and in the same year Story proved that all positions when $N + K$ is even have a solution.

However, all these proofs were quite complex.

In 1999 Archer proposed much more simple proof (you can download his article [here](http://www.cs.cmu.edu/afs/cs/academic/class/15859-f01/www/notes/15-puzzle.pdf)).
