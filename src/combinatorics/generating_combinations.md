<!--?title Generating Combinations of N Elements-->

#Generating combinations of $N$ elements

## Combinations of $K$ chosen elements from $N$ elements in lexicographical order
Consider the problem - Given the natural numbers $N$ and $K$, consider a set of numbers from $1$ to $N$.
It is required to derive all subsets of cardinality $K$, in lexicographical order.

The algorithm for this is simple. The first combination will be ${1, 2, ..., K}$. Now let's see how
to find the combination that immediately follows this, lexicographically. To do so, we consider our
current combination, and find the rightmost element that has not yet reached its highest value. Once
finding this element, we increment it by $1$, and assign the lowest valid value to all subsequent
elements.

    bool next_combination (vector <int> & a, int n) {
      int k = (int) a.size ();
      for (int i = k - 1; i >= 0; --i)
        if( a[i] < n - k + i + 1 ) {
          ++a[i];
          for(int j = i + 1; j < k; ++j)
            a [j] = a [j-1] + 1;
          return true;
        }
      return false;
    }
    
In terms of performance, this algorithm is (on average) linear, if $K << N$ (that is, if $K!=N$ then 
the algorithm is $O(N)$). This can be determined by proving that $a[i] < n - k + i + 1$ is valid
for $\binom{n+1}{k}$ iterations in total.

## Combinations of $K$ elements out of $N$ elements ordered with changes to exactly one element
Consider the problem - Write all combinations of subsets of $N$ whose cardinality is $K$ in such
an order, that adjacent combinations differ exactly by one element.

In other words, this task requires the ordered generation of subsets of a given set such that 
adjacent subsets differ by only one element. This can be solved using the [Gray Code](https://e-maxx-eng.appspot.com/algebra/gray-code.html):
If we assign a bitmask to each subset, then by generating and iterating over these bitmasks with Gray codes, we can obtain our answer.

The task of generating $K$ cardinal combinations can also be solved using Gray Codes, in the following way -
Generate Gray Codes for numbers from $0$ to $2^N - 1$ and leave only those codes containing $K$ $1$s.
The surprising fact is that in the resulting sequence of $K$ set bits, any two neighbouring masks (including the
first and last mask - neighboring in a cyclic sense) - will differ exactly by two bits, which is our objective (remove
a number, add a number).

Let us prove this:

For the proof, we recall the fact that the sequence $G(N)$ (representing the $N$<sup>th</sup> Gray Code can 
be obtained as follows:

$G(N) = 0G(N-1) \cup 1G(N-1)$<sup>R</sup>

That is, consider the Gray Code sequence for $N-1$, and prefix $0$ before every term. And consider the 
inverted Gray Code sequence for $N-1$ (i.e bitwise compliment) and prefix a $1$ before every mask, and
concatenate these two sequences.

Now we may produce our proof.

First, we prove that the first and last masks differ exactly in two bits. To do this, it is sufficient to note
that the first mask of the sequence $G(N)$, will be of the form $N-K$ $0$s, followed by $K$ $1$s. (As,
the first bit is set as $0$, after which $(N-K-1)$ $0$s follow, after which $K$ set bits follow.)

Similarly, the last mask will be of the form $1$, then $(N-K-1)$ $0$s, then $K-1$ $1$s.

Now let us complete the proof using mathematical induction on the above recursive formula for $G(N)$.

Now, we must show that any two adjacent codes also differ exactly in two bits. This can be done by inspecting our
recursive formula for generating Gray Codes. Let us assume that both halves are true, (i.e. assume that $G(N-1)$
has been properly constructed). To prove the validity now in general, we just have to prove the validity of
the "gluing" part of the equation, that is the validity between the last term of the first sequence with the first term
of the second sequence. This is how the principle of mathematical induction is applied here.

The following is a naive implementation working by generating all $2^{n}$ possible subsets, and finding subsets of cardinality
$K$.

It's worth mentioning that a more efficient implementation exists that only resorts to bulding valid combinations and thus
works in $O(N* \binom{N}{K})$ however it is recursive in nature and for smaller values of $N$ it probably has a larger constant
than the previous solution.

The implementation is derived from the formula:

$G(N, K) = 0G(N-1, K) \cup 1G(N-1, K-1)$<sup>R</sup>

This formula is obtained by modifying the general equation to determine the Gray code, and works by selecting the
subsequence from appropriate elements.

Its implementation is as follows -
    
    bool ans [MAXN];
    
    void gen (int n, int k, int l, int r, bool rev, int old_n) {
        if (k>n || k<0) return;
        if (!n) {
            for(int i = 0; i < old_n; ++i)
                printf("%d", (int) ans[i]);
            puts("");
            return;
        }
        ans [rev?r:l] = false;
        gen(n-1, k, !rev? l+1:l, !rev? r:r-1, rev, old_n);
        ans [rev?r:l] = true;
        gen(n-1, k-1, !rev?l+1:l, !rev?r:r-1, !rev, old_n);
    }
