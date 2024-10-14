---
tags:
  - Translated
e_maxx_link: sprague_grundy
---

# Sprague-Grundy theorem. Nim

## Introduction

This theorem describes the so-called **impartial** two-player game,
i.e. those in which the available moves and winning/losing depends only on the state of the game.
In other words, the only difference between the two players is that one of them moves first.

Additionally, we assume that the game has **perfect information**, i.e. no information is hidden from the players (they know the rules and the possible moves).

It is assumed that the game is **finite**, i.e. after a certain number of moves, one of the players will end up in a losing position — from which they can't move to another position.
On the other side, the player who set up this position for the opponent wins.
Understandably, there are no draws in this game.

Such games can be completely described by a *directed acyclic graph*: the vertices are game states and the edges are transitions (moves).
A vertex without outgoing edges is a losing vertex (a player who must make a move from this vertex loses).

Since there are no draws, we can classify all game states as either **winning** or **losing**.
Winning states are those from which there is a move that causes inevitable defeat of the other player, even with their best response.
Losing states are those from which all moves lead to winning states for the other player.
Summarizing, a state is winning if there is at least one transition to a losing state and is losing if there isn't at least one transition to a losing state.

Our task is to classify the states of a given game.

The theory of such games was independently developed by Roland Sprague in 1935 and Patrick Michael Grundy in 1939.

## Nim

This game obeys the restrictions described above.
Moreover, *any* perfect-information impartial two-player game can be reduced to the game of Nim.
Studying this game will allow us to solve all other similar games, but more on that later.

Historically this game was popular in ancient times.
Its origin is probably in China — or at least the game *Jianshizi* is very similar to it.
In Europe the earliest references to it are from the 16th century.
The name was given by Charles Bouton, who in 1901 published a full analysis of this game.

### Game description

There are several piles, each with several stones.
In a move a player can take any positive number of stones from any one pile and throw them away.
A player loses if they can't make a move, which happens when all the piles are empty.

The game state is unambiguously described by a multiset of positive integers.
A move consists of strictly decreasing a chosen integer (if it becomes zero, it is removed from the set).

### The solution

The solution by Charles L. Bouton looks like this:

**Theorem.**
The current player has a winning strategy if and only if the xor-sum of the pile sizes is non-zero.
The xor-sum of a sequence $a$ is $a_1 \oplus a_2 \oplus \ldots \oplus  a_n$, where $\oplus$ is the *bitwise exclusive or*.

**Proof.**
The key to the proof is the presence of a **symmetric strategy for the opponent**.
We show that a once in a position with the xor-sum equal to zero, the player won't be able to make it non-zero in the long term —
if they transition to a position with a non-zero xor-sum, the opponent will always have a move returning the xor-sum back to zero.

We will prove the theorem by mathematical induction.

For an empty Nim (where all the piles are empty i.e. the multiset is empty) the xor-sum is zero and the theorem is true.

Now suppose we are in a non-empty state.
Using the assumption of induction (and the acyclicity of the game) we assume that the theorem is proven for all states reachable from the current one.

Then the proof splits into two parts:
if for the current position the xor-sum $s = 0$, we have to prove that this state is losing, i.e. all reachable states have xor-sum $t \neq 0$.
If $s \neq 0$, we have to prove that there is a move leading to a state with $t = 0$.

*   Let $s = 0$ and let's consider any move.
    This move reduces the size of a pile $x$ to a size $y$.
    Using elementary properties of $\oplus$, we have
    
    \[ t = s \oplus x \oplus y = 0 \oplus x \oplus y = x \oplus y \]
    
    Since $y < x$, $y \oplus x$ can't be zero, so $t \neq 0$.
    That means any reachable state is a winning one (by the assumption of induction), so we are in a losing position.

*   Let $s \neq 0$.
    Consider the binary representation of the number $s$.
    Let $d$ be the index of its leading (biggest value) non-zero bit.
    Our move will be on a pile whose size's bit number $d$ is set (it must exist, otherwise the bit wouldn't be set in $s$).
    We will reduce its size $x$ to $y = x \oplus s$.
    All bits at positions greater than $d$ in $x$ and $y$ match and bit $d$ is set in $x$ but not set in $y$.
    Therefore, $y < x$, which is all we need for a move to be legal.
    Now we have:
    
    \[ t = s \oplus x \oplus y = s \oplus x \oplus (s \oplus x) = 0 \]
    
    This means we found a reachable losing state (by the assumption of induction) and the current state is winning.

**Corollary.**
Any state of Nim can be replaced by an equivalent state as long as the xor-sum doesn't change.
Moreover, when analyzing a Nim with several piles, we can replace it with a single pile of size $s$.

### Misère Game

In a **misère game**, the goal of the game is opposite, so the player who removes the last stick loses the game.
It turns out that the misère nim game can be optimally played almost like a standard nim game.
 The idea is to first play the misère game like the standard game, but change the strategy at the end of the game.
 The new strategy will be introduced in a situation where each heap would contain at most one stick after the next move.
In the standard game, we should choose a move after which there is an even number of heaps with one stick. However, in 
the misère game,we choose a move so that there is an odd number of heaps with one stick.
  This strategy works because a state where the strategy changes always appears in the game, and this state is a 
  winning state, because it contains exactly one heap that has more than one stick so the nim sum is not 0.

## The equivalence of impartial games and Nim (Sprague-Grundy theorem)

Now we will learn how to find, for any game state of any impartial game, a corresponding state of Nim.

### Lemma about Nim with increases

We consider the following modification to Nim: we also allow **adding stones to a chosen pile**.
The exact rules about how and when increasing is allowed **do not interest us**, however the rules should keep our game **acyclic**. In later sections, example games are considered.

**Lemma.**
The addition of increasing to Nim doesn't change how winning and losing states are determined.
In other words, increases are useless, and we don't have to use them in a winning strategy.

**Proof.**
Suppose a player added stones to a pile. Then his opponent can simply undo his move — decrease the number back to the previous value.
Since the game is acyclic, sooner or later the current player won't be able to use an increase move and will have to do the usual Nim move.

### Sprague-Grundy theorem

Let's consider a state $v$ of a two-player impartial game and let $v_i$ be the states reachable from it (where $i \in \{ 1, 2, \dots, k \} , k \ge 0$).
To this state, we can assign a fully equivalent game of Nim with one pile of size $x$.
The number $x$ is called the Grundy value or nim-value of state $v$.

Moreover, this number can be found in the following recursive way:

$$ x = \text{mex}\ \{ x_1, \ldots, x_k \}, $$

where $x_i$ is the Grundy value for state $v_i$ and the function $\text{mex}$ (*minimum excludant*) is the smallest non-negative integer not found in the given set.

Viewing the game as a graph, we can gradually calculate the Grundy values starting from vertices without outgoing edges.
Grundy value being equal to zero means a state is losing.

**Proof.**
We will use a proof by induction.

For vertices without a move, the value $x$ is the $\text{mex}$ of an empty set, which is zero.
That is correct, since an empty Nim is losing.

Now consider any other vertex $v$.
By induction, we assume the values $x_i$ corresponding to its reachable vertices are already calculated.

Let $p = \text{mex}\ \{ x_1, \ldots, x_k \}$.
Then we know that for any integer $i \in [0, p)$ there exists a reachable vertex with Grundy value $i$.
This means $v$ is **equivalent to a state of the game of Nim with increases with one pile of size $p$**.
In such a game we have transitions to piles of every size smaller than $p$ and possibly transitions to piles with sizes greater than $p$.
Therefore, $p$ is indeed the desired Grundy value for the currently considered state.

## Application of the theorem

Finally, we describe an algorithm to determine the win/loss outcome of a game, which is applicable to any impartial two-player game.

To calculate the Grundy value of a given state you need to:

* Get all possible transitions from this state

* Each transition can lead to a **sum of independent games** (one game in the degenerate case).
Calculate the Grundy value for each independent game and xor-sum them.
Of course xor does nothing if there is just one game.

* After we calculated Grundy values for each transition we find the state's value as the $\text{mex}$ of these numbers.

* If the value is zero, then the current state is losing, otherwise it is winning.

In comparison to the previous section, we take into account the fact that there can be transitions to combined games.
We consider them a Nim with pile sizes equal to the independent games' Grundy values.
We can xor-sum them just like usual Nim according to Bouton's theorem.

## Patterns in Grundy values

Very often when solving specific tasks using Grundy values, it may be beneficial to **study the table of the values** in search of patterns.

In many games, which may seem rather difficult for theoretical analysis,
the Grundy values turn out to be periodic or of an easily understandable form.
In the overwhelming majority of cases the observed pattern turns out to be true and can be proved by induction if desired.

However, Grundy values are far from *always* containing such regularities and even for some very simple games, the problem asking if those regularities exist is still open (e.g. "Grundy's game").

## Example games

### Crosses-crosses

**The rules.**
Consider a checkered strip of size $1 \times n$. In one move, the player must put one cross, but it is forbidden to put two crosses next to each other (in adjacent cells). As usual, the player without a valid move loses.

**The solution.**
When a player puts a cross in any cell, we can think of the strip being split into two independent parts:
to the left of the cross and to the right of it.
In this case, the cell with a cross, as well as its left and right neighbours are destroyed — nothing more can be put in them.
Therefore, if we number the cells from $1$ to $n$ then putting the cross in position $1 < i < n$ breaks the strip
into two strips of length $i-2$ and $n-i-1$ i.e. we go to the sum of games $i-2$ and $n-i-1$.
For the edge case of the cross being marked on position $1$ or $n$, we go to the game $n-2$.

Thus, the Grundy value $g(n)$ has the form:

$$g(n) = \text{mex} \Bigl( \{ g(n-2) \} \cup \{g(i-2) \oplus g(n-i-1) \mid 2 \leq i \leq n-1\} \Bigr) .$$

So we've got a $O(n^2)$ solution.

In fact, $g(n)$ has a period of length 34 starting with $n=52$.


## Practice Problems

- [KATTIS S-Nim](https://open.kattis.com/problems/snim)
- [CodeForces - Marbles (2018-2019 ACM-ICPC Brazil Subregional)](https://codeforces.com/gym/101908/problem/B)
- [KATTIS - Cuboid Slicing Game](https://open.kattis.com/problems/cuboidslicinggame)
- [HackerRank - Tower Breakers, Revisited!](https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/tower-breakers-2)
- [HackerRank - Tower Breakers, Again!](https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/tower-breakers-3/problem)
- [HackerRank - Chessboard Game, Again!](https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/a-chessboard-game)
- [Atcoder - ABC368F - Dividing Game](https://atcoder.jp/contests/abc368/tasks/abc368_f)