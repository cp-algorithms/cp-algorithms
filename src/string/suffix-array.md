<!--?title Suffix Array-->
#Suffix Array

###What is a suffix?

Let $S$ be a string of length $N$. The $i^{th}$ suffix of $S$ is substring $S[i \ldots n - 1], i = 0 \ldots n - 1$.

###What is a suffix array?

As a data structure, it is widely used in areas such as data compression, bioinformatics and, 
in general, in any area that deals with strings and string matching problems, so, as you can see, 
it is of great importance to know efficient algorithms to construct a suffix array for a given string.

A **Suffix Array** will contain integers that represent the **starting indexes** of the all the suffixes of a given string, after the aforementioned suffixes are sorted.

###Example
Let $S\ =\ abaab$  
All suffixes are as follows  
$0.\ abaab$  
$1.\ baab$  
$2.\ aab$  
$3.\ ab$  
$4.\ b$  

After sorting these strings:  
$2.\ aab$  
$3.\ ab$  
$0.\ abaab$  
$4.\ b$  
$1.\ baaab$  

Suffix Array for $S$ will be $(2,\ 3,\ 0,\ 4,\ 1)$.  

###Construction Of Suffix Array

####$O(N^2\log{N})$ Approach

This is the most naive approach. Get all the suffixes and sort them using Quicksort or Mergesort simultaneously retaining their original indexes. Sorting takes $O(N\log{N})$ so how it is $O(N^2\log{N})$??.
What we miss here is comparison of two strings is not $O(1)$ in worst case it takes $O(N)$.
So the final complexity is $O(N^2\log{N})$. We can reduce this comparison from $O(N)$ to $O(1)$. Read further :).


####$O(N\log^2{N})$ Approach

We can reduce comparison of two strings from $O(N)$ to $O(1)$ using the fact that, given strings are not
random strings they are part of single string. **Each string has something in common with others.**  

Let's see how we can use this fact.
Let's sort the suffixes on basis of their first character and assign them rank.  
If two are equal rank for them will be same.  
  
$0.\ a|baab$  
$0.\ a|ab$  
$0.\ a|b$  
$1.\ b|aab$  
$1.\ b|$  

**Note:** '|' denotes sorting is based on left part of '|'.  

Now double the characters to take from each for sorting i.e. 2.  
When we take string of two chars we can have two parts first containing 1 char other containing 1.  
Let's compare $abaab$ with $baab$, based on the first part, that of 1 character we can say that $abaab$ will  
be always ranked above $baab$ so skip further comparison.  

Now compare $abaab$ with $aab$ based on first part both have same rank. Now we will compare their second half part,  
second half part of $abaab$ is only $b$ and for $aab$ be is $a$ for these we already know their ranks  
for $b$ (i.e. whole $baab$) is 1 and $a$ (i.e. whole $ab$) is 0.  
Hence $abaab$ will be ranked above $baab$.  

For the strings not having second part we will rank their second part highest i.e. -1
for example $b$ is not having $2^{nd}$ char so its rank tuple will be (1, -1).  

$0.\ aa|b$  
$1.\ ab|aab$  
$1.\ ab|$  
$2.\ b|$  
$2.\ ba|ab$

Now, in the next iteration, we sort 4-characters strings. This involves a lot of comparisons between different 4-characters strings.  
How do we compare two 4-characters strings? Well, we could compare them character by character. That would be up to 4 operations per comparison.  
But instead, we compare them by looking up the ranks of the two characters contained in them, using the rank table generated in the previous steps.  
That rank represents the lexicographic rank from the previous 2-charater sort, so if any given 4-character string has a higher rank than another 4-character string, then it must be lexicographically greater somewhere in the first two characters.  
Hence, if for two 4-characters string the rank is identical, they must be identical in the first two characters.  
In other words, two look-ups in the rank table are sufficient to compare all 4 characters of the two 4-characters strings.  

Similarly we can compare 8, 16, 32 $\ldots$ strings in at most two integer comparisons.  
i.e. $O(1)$ comparison.  

Following fully commented code will clarify more.  

###Implementation

C++ implementation <span class="toggle-code">Show/Hide</span>  

```cpp
#include bits/stdc++.h  
using namespace std;

// suffixRank is table hold the rank of each string on each iteration  
// suffixRank[i][j] denotes rank of jth suffix at ith iteration  

int suffixRank[20][int(1E6)];

// Example "abaab"  
// Suffix Array for this (2, 3, 0, 4, 1)  
// Create a tuple to store rank for each suffix  

struct myTuple {  
	int originalIndex;   // stores original index of suffix  
	int firstHalf;       // store rank for first half of suffix  
	int secondHalf;      // store rank for second half of suffix  
};


// function to compare two suffix in O(1)  
// first it checks whether first half chars of 'a' are equal to first half chars of b  
// if they compare second half  
// else compare decide on rank of first half  

int cmp(myTuple a, myTuple b) {  
	if(a.firstHalf == b.firstHalf) return a.secondHalf < b.secondHalf;  
	else return a.firstHalf < b.firstHalf;  
}

int main() {

    // Take input string
    // initialize size of string as N

    string s; cin >> s;
    int N = s.size();

    // Initialize suffix ranking on the basis of only single character
    // for single character ranks will be 'a' = 0, 'b' = 1, 'c' = 2 ... 'z' = 25

    for(int i = 0; i < N; ++i)
        suffixRank[0][i] = s[i] - 'a';

    // Create a tuple array for each suffix

    myTuple L[N];

    // Iterate log(n) times i.e. till when all the suffixes are sorted
    // 'stp' keeps the track of number of iteration
    // 'cnt' store length of suffix which is going to be compared

    // On each iteration we initialize tuple for each suffix array
    // with values computed from previous iteration

    for(int cnt = 1, stp = 1; cnt < N; cnt *= 2, ++stp) {

        for(int i = 0; i < N; ++i) {
            L[i].firstHalf = suffixRank[stp - 1][i];
            L[i].secondHalf = i + cnt < N ? suffixRank[stp - 1][i + cnt] : -1;
            L[i].originalIndex = i;
        }

        // On the basis of tuples obtained sort the tuple array

        sort(L, L + N, cmp);

        // Initialize rank for rank 0 suffix after sorting to its original index
        // in suffixRank array

        suffixRank[stp][L[0].originalIndex] = 0;

        for(int i = 1, currRank = 0; i < N; ++i) {

            // compare ith ranked suffix ( after sorting ) to (i - 1)th ranked suffix
            // if they are equal till now assign same rank to ith as that of (i - 1)th
            // else rank for ith will be currRank ( i.e. rank of (i - 1)th ) plus 1, i.e ( currRank + 1 )

            if(L[i - 1].firstHalf != L[i].firstHalf || L[i - 1].secondHalf != L[i].secondHalf)
                ++currRank;

            suffixRank[stp][L[i].originalIndex] = currRank;
        }

    }

    // Print suffix array

    for(int i = 0; i < N; ++i) cout << L[i].originalIndex << endl;

    return 0;
}
``` 

## Practice Problems

* [Uva 760 - DNA Sequencing](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=701)
* [Uva 1223 - Editor](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3664)

**Upcoming: $O(N\log(N))$ approach, $O(N)$ approach and LCP array**
