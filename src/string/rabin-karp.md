<!--?title Rabin-Karp Algorithm-->

# Rabin-Karp Algorithm for string matching in O(|S| + |T|)


This algorithm is based on the concept of hashing, so if you are not familiar with string hashing,  refer to the [string hashing](./string/string-hashing.html) article.

 
This algorithm was authored by Rabin and Karp in 1987.

Problem: Given two strings - a pattern $S$ and a text $T$, determine if the pattern appears in the text and if it does, enumerate all its
occurrences in $O(|S| + |T|)$ time.

Algorithm: Calculate the hash for the pattern $S$. Calculate hash values for all the prefixes of the text $T$. Now, we can compare a substring of length $|S|$ with $S$ in constant time using the calculated hashes. So, compare each substring of length $|S|$ with the pattern. This will take a total of $O(|T|)$ time. Hence the final complexity of the algorithm is $O(|T| + |S|)$:  $O(|S|)$ is required for calculating the hash of the pattern and $O(|T|)$ for comparing each substring of length $|S|$ with the pattern.


## Implementation
```cpp
string s, t; // input 

// calculate all powers of p 
const int p = 31; 
vector<unsigned long long> p_pow(max(s.length(), t.length())); 
p_pow[0] = 1; 
for (size_t i = 1; i < p_pow.size(); ++i) 
    p_pow[i] = p_pow[i-1] * p; 

// calculate hashes of all prefixes of text T 
vector<unsigned long long> h(t.length()); 
for (size_t i = 0; i < t.length(); i++) 
{ 
    h[i] = (t[i] - 'a' + 1) * p_pow[i]; 
    if (i) h[i] + = h[i - 1]; 
} 

// calculate the hash of the pattern S 
unsigned long long h_s = 0; 
for (size_t i = 0; i < s.length(); i++) 
    h_s += (s[i] - 'a' + 1) * p_pow[i]; 

// iterate over all substrings of T having length |S| and compare them
// with S 
for (size_t i = 0; i + s.length() - 1 < t.length(); i++) 
{ 
    unsigned long long cur_h = h[i + s.length () - 1]; 
    if (i) cur_h -= h [i - 1]; 

    // get the hashes multiplied to the same degree of p and compare them 
    if (cur_h == H_s * p_pow[i]) 
	    cout << i << ''; 
}
```

## Practice Problems

* [SPOJ - Pattern Find](http://www.spoj.com/problems/NAJPF/)
* [Codeforces - Good Substrings](http://codeforces.com/problemset/problem/271/D)

