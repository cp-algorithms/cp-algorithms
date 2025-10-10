# 📏 Longest Common Subsequence (LCS)

The Longest Common Subsequence (LCS) problem is a classic dynamic programming problem used to find the longest subsequence common to two (or more) sequences.

### 🎯 Goal

Find the longest sequence that can be obtained from both input sequences by deleting zero or more elements. The relative order of the remaining elements must be preserved.

### 💡 Dynamic Programming Approach

The solution relies on building a 2D table, $DP$, where:

* **$DP[i][j]$** stores the length of the LCS of the prefix of String 1 (length $i$) and the prefix of String 2 (length $j$).

The recurrence relation is:

1.  **If $S1[i] = S2[j]$:** The characters match, so the LCS length increases by 1 based on the solution for the previous characters.
    $$DP[i][j] = 1 + DP[i-1][j-1]$$

2.  **If $S1[i] \neq S2[j]$:** The characters don't match, so we take the maximum LCS length achieved by excluding either $S1[i]$ or $S2[j]$.
    $$DP[i][j] = \max(DP[i-1][j], DP[i][j-1])$$

### ⚙️ Complexity

| Operation | Complexity |
| :--- | :--- |
| **Time** | $O(m \cdot n)$ |
| **Space** | $O(m \cdot n)$ |

*where $m$ and $n$ are the lengths of the two sequences.*

### 🛠️ Applications

* **File Comparison:** The core algorithm used in the Unix `diff` utility.
* **Bioinformatics:** Comparing DNA and protein sequences.
* **Version Control:** Calculating differences between file versions in Git, etc.