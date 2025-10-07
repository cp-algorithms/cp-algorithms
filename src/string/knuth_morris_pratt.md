# Knuth–Morris–Pratt (KMP) String Matching Algorithm

The **KMP algorithm** is an efficient string-searching method used to find occurrences of a *pattern* within a *text*.  
Unlike the naive approach, KMP avoids re-checking characters that have already been matched, resulting in **O(n + m)** time complexity — where `n` is the length of the text and `m` is the length of the pattern.

---

## Concept

When a mismatch occurs, KMP uses a **preprocessed array (LPS – Longest Prefix Suffix)** to decide where to resume the search instead of starting from the beginning of the pattern again.

The **LPS array** tells us the longest prefix of the pattern that is also a suffix up to each position.

For example, if the pattern is:

```
A B A B A C
```

Then the LPS array is:

| Index | Character | LPS |
|:------:|:----------:|:---:|
| 0 | A | 0 |
| 1 | B | 0 |
| 2 | A | 1 |
| 3 | B | 2 |
| 4 | A | 3 |
| 5 | C | 0 |

So when a mismatch happens, KMP uses this LPS table to skip unnecessary comparisons.

---

## Steps of KMP

1. **Preprocess** the pattern to create the LPS array.  
2. **Scan** the text using the pattern and LPS array:
   - When characters match → move both indices.
   - When mismatch occurs → use LPS to skip to the next best possible match.

---

## Example

**Text:** `ABABDABACDABABCABAB`  
**Pattern:** `ABABCABAB`

KMP will find the pattern starting at **index 10** (0-based indexing).

---

## C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Compute LPS array
vector<int> computeLPS(const string &pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// KMP search
vector<int> KMPSearch(const string &text, const string &pattern) {
    vector<int> lps = computeLPS(pattern);
    vector<int> matches;
    int n = text.size(), m = pattern.size();
    int i = 0, j = 0;

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++; j++;
        }

        if (j == m) {
            matches.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }

    return matches;
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    vector<int> result = KMPSearch(text, pattern);

    cout << "Pattern found at indices: ";
    for (int idx : result) cout << idx << " ";
    cout << endl;
    return 0;
}
```

**Output:**
```
Pattern found at indices: 10
```

---

## Summary

- **Naive approach:** O(n × m)  
- **KMP algorithm:** O(n + m)  
- **Key idea:** Reuse previously matched information using the **LPS array**.

The KMP algorithm is widely used in text editors, compilers, and search tools for efficient pattern matching.

---

## Practice Problems

Here are some online resources to **practice KMP and string matching**:

- [GeeksforGeeks – KMP Algorithm](https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/)  
- [LeetCode – Implement strStr()](https://leetcode.com/problems/implement-strstr/)  
- [HackerRank – Pattern Matching](https://www.hackerrank.com/topics/string-matching)  
- [Codeforces – Search Problems](https://codeforces.com/problemset?tags=string+matching)  
- [SPOJ – Pattern Searching Problems](https://www.spoj.com/problems/tagging/)

These platforms provide problems ranging from beginner-friendly to competitive programming level.
