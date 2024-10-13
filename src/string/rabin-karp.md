---
tags:
  - Translated
e_maxx_link: rabin_karp
---

# Rabin-Karp Algorithm for string matching

This algorithm is based on the concept of hashing, so if you are not familiar with string hashing, refer to the [string hashing](string-hashing.md) article.
This algorithm was authored by Rabin and Karp in 1987.

Problem: Given two strings - a length $m$ pattern to find in a length $n$ text, find all matches in $\Theta(m+n) = \Theta(n)$ average time.

The naive solution is to simply check all length $m$ substrings in the $n$ length text, but that would take $\Theta(mn)$ time.

The Rabin-Karp algorithm uses the concept of a "rolling hash". In it, a hash function is chosen in such a way that the hash of the first text substring of size $m$ is computed in $\Theta(m)$ time, but the computation of hashes of subsequent substrings of length $m$ is done in $O(1)$ per substring (hence the term "rolling"). Then, the hash of the pattern is compared to hashes of each text substring, and if they are the same then there is a match with high probability.

## The hash function

The trick is the special polynomial hash function, also known as a Rabin fingerprint. It is defined as 

$$h(S[i..j]) = S[i] x^{m-1} + S[i+1] x^{m-2} + \cdots + S[j-1] x + S[j]$$

This is a polynomial in variable $x$, and $x$ is chosen to be as large as the alphabet, so that we have a unique hash for every fixed-length substring. For example, for a string of bytes, we can take $x = 256$. However, the resulting hash value is large, so we work modulo a large prime $p$. This creates a small chance of hash collisions that needs to be handled. In the worst case of a hash collision every time, the performance degrades to $\Theta(nm)$. 

Now, to "roll" the hash forward,

$$h(S[i+1..j+1) = x \cdot h(S[i..j]) - S[i] x^m + S[j+1]$$

What we did is multiply all terms by $x$, then subtract off the $S[i]$ term, then add the new $S[j+1]$ term. This let us compute our next hash in constant time. 

## Implementation
```{.cpp file=rabin_karp}
vector<int> rabin_karp(string const& s, string const& t) {
    const int p = 31; 
    const int m = 1e9 + 9;
    int S = s.size(), T = t.size();

    vector<long long> p_pow(max(S, T)); 
    p_pow[0] = 1; 
    for (int i = 1; i < (int)p_pow.size(); i++) 
        p_pow[i] = (p_pow[i-1] * p) % m;

    vector<long long> h(T + 1, 0); 
    for (int i = 0; i < T; i++)
        h[i+1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m; 
    long long h_s = 0; 
    for (int i = 0; i < S; i++) 
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m; 

    vector<int> occurrences;
    for (int i = 0; i + S - 1 < T; i++) {
        long long cur_h = (h[i+S] + m - h[i]) % m;
        if (cur_h == h_s * p_pow[i] % m)
            occurrences.push_back(i);
    }
    return occurrences;
}
```

## Practice Problems

* [SPOJ - Pattern Find](http://www.spoj.com/problems/NAJPF/)
* [Codeforces - Good Substrings](http://codeforces.com/problemset/problem/271/D)
* [Codeforces - Palindromic characteristics](https://codeforces.com/problemset/problem/835/D)
* [Leetcode - Longest Duplicate Substring](https://leetcode.com/problems/longest-duplicate-substring/)

## Resources

* [Sleator - String matching algorithms](https://contest.cs.cmu.edu/295/s20/tutorials/strings.mark)
* CLRS 3ed, Ch 32.2
