# KMP Algorithm (Knuth-Morris-Pratt)

## 📖 Overview

The **Knuth-Morris-Pratt (KMP)** algorithm is an efficient string matching algorithm that searches for occurrences of a "pattern" within a "text" in **O(n + m)** time complexity, where `n` is the length of the text and `m` is the length of the pattern.

The key innovation of KMP is that it **never re-examines** characters in the text that have already been matched, making it significantly more efficient than naive string matching approaches.

## 🧠 Key Concepts

### The Failure Function (LPS Array)
The heart of KMP is the **Longest Proper Prefix which is also Suffix (LPS)** array, also known as the failure function. For a pattern, it tells us the longest proper prefix of the pattern that is also a suffix.

**Example:**
- Pattern: `"ABABCABAB"`
- LPS:     `[0,0,1,2,0,1,2,3,4]`

### Why KMP Works
When a mismatch occurs, instead of starting over from the next character, KMP uses the LPS array to determine how many characters can be skipped, utilizing previously matched information.

## 🔧 Algorithm Steps

1. **Preprocessing**: Build the LPS array for the pattern
2. **Searching**: Use the LPS array to efficiently search through the text

## 💻 Implementation

### Basic KMP Implementation

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class KMP {
private:
    // Build the LPS (Longest Proper Prefix which is also Suffix) array
    vector<int> buildLPS(const string& pattern) {
        int m = pattern.length();
        vector<int> lps(m, 0);
        int len = 0;  // Length of previous longest prefix suffix
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

public:
    // Find all occurrences of pattern in text
    vector<int> search(const string& text, const string& pattern) {
        vector<int> result;
        int n = text.length();
        int m = pattern.length();
        
        if (m == 0) return result;
        
        // Build LPS array
        vector<int> lps = buildLPS(pattern);
        
        int i = 0;  // Index for text
        int j = 0;  // Index for pattern
        
        while (i < n) {
            if (pattern[j] == text[i]) {
                i++;
                j++;
            }
            
            if (j == m) {
                result.push_back(i - j);  // Found a match
                j = lps[j - 1];
            } else if (i < n && pattern[j] != text[i]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        
        return result;
    }
    
    // Print LPS array for educational purposes
    void printLPS(const string& pattern) {
        vector<int> lps = buildLPS(pattern);
        cout << "Pattern: " << pattern << endl;
        cout << "LPS:     [";
        for (int i = 0; i < lps.size(); i++) {
            cout << lps[i];
            if (i < lps.size() - 1) cout << ",";
        }
        cout << "]" << endl;
    }
};
```

### Enhanced Implementation with More Features

```cpp
class EnhancedKMP {
private:
    vector<int> lps;
    string pattern;
    
    void buildLPS() {
        int m = pattern.length();
        lps.assign(m, 0);
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
    }

public:
    EnhancedKMP(const string& pat) : pattern(pat) {
        buildLPS();
    }
    
    // Count total occurrences
    int countOccurrences(const string& text) {
        vector<int> matches = search(text);
        return matches.size();
    }
    
    // Find first occurrence (returns -1 if not found)
    int findFirst(const string& text) {
        vector<int> matches = search(text);
        return matches.empty() ? -1 : matches[0];
    }
    
    // Check if pattern exists in text
    bool exists(const string& text) {
        return findFirst(text) != -1;
    }
    
    // Search with detailed information
    vector<int> search(const string& text) {
        vector<int> result;
        int n = text.length();
        int m = pattern.length();
        
        if (m == 0 || n == 0) return result;
        
        int i = 0, j = 0;
        int comparisons = 0;  // For performance analysis
        
        while (i < n) {
            comparisons++;
            if (pattern[j] == text[i]) {
                i++;
                j++;
            }
            
            if (j == m) {
                result.push_back(i - j);
                j = lps[j - 1];
            } else if (i < n && pattern[j] != text[i]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        
        cout << "Total comparisons: " << comparisons << endl;
        return result;
    }
    
    // Get LPS array
    vector<int> getLPS() const {
        return lps;
    }
};
```

## 🎯 Example Usage and Testing

```cpp
int main() {
    // Basic usage
    KMP kmp;
    
    string text = "ABABDABACDABABCABCABCABABABCABAB";
    string pattern = "ABABCABAB";
    
    cout << "=== KMP String Matching Demo ===" << endl;
    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl << endl;
    
    // Show LPS construction
    kmp.printLPS(pattern);
    cout << endl;
    
    // Find all matches
    vector<int> matches = kmp.search(text, pattern);
    
    cout << "Matches found at positions: ";
    if (matches.empty()) {
        cout << "None" << endl;
    } else {
        for (int i = 0; i < matches.size(); i++) {
            cout << matches[i];
            if (i < matches.size() - 1) cout << ", ";
        }
        cout << endl;
    }
    
    // Enhanced features demo
    cout << "\n=== Enhanced Features Demo ===" << endl;
    EnhancedKMP enhanced(pattern);
    
    cout << "Pattern exists: " << (enhanced.exists(text) ? "Yes" : "No") << endl;
    cout << "First occurrence: " << enhanced.findFirst(text) << endl;
    cout << "Total occurrences: " << enhanced.countOccurrences(text) << endl;
    
    // Performance comparison
    cout << "\n=== Performance Analysis ===" << endl;
    enhanced.search(text);
    
    return 0;
}
```

## 📊 Complexity Analysis

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Preprocessing (LPS) | O(m) | O(m) |
| Searching | O(n) | O(1) extra |
| **Total** | **O(n + m)** | **O(m)** |

Where:
- `n` = length of text
- `m` = length of pattern

## 🔍 Step-by-Step Example

Let's trace through an example:

**Text:** `"ABABCABABABCABAB"`  
**Pattern:** `"ABABCABAB"`

### Step 1: Build LPS Array
```
Pattern: A B A B C A B A B
Index:   0 1 2 3 4 5 6 7 8
LPS:     0 0 1 2 0 1 2 3 4
```

### Step 2: Search Process
```
Text:    A B A B C A B A B A B C A B A B
Pattern: A B A B C A B A B
         ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑
         0 1 2 3 4 5 6 7 8 (Match found at position 0)

Text:    A B A B C A B A B A B C A B A B
Pattern:         A B A B C A B A B
                 ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑
                 5 6 7 8 9 10 11 12 13 (Match found at position 5)
```

## 🌟 Interesting Properties

### 1. **Periodicity Detection**
KMP can detect if a string has a repeating pattern:

```cpp
bool hasRepeatingPattern(const string& s) {
    int n = s.length();
    vector<int> lps = buildLPS(s);
    int period = n - lps[n-1];
    return (n % period == 0) && (period != n);
}
```

### 2. **String Rotation**
Check if one string is a rotation of another:

```cpp
bool isRotation(const string& s1, const string& s2) {
    if (s1.length() != s2.length()) return false;
    string doubled = s1 + s1;
    KMP kmp;
    return !kmp.search(doubled, s2).empty();
}
```

### 3. **Pattern Preprocessing for Multiple Searches**
When searching for the same pattern in multiple texts, preprocess once:

```cpp
class PreprocessedKMP {
    vector<int> lps;
    string pattern;
    
public:
    PreprocessedKMP(const string& pat) : pattern(pat) {
        // Build LPS once
        buildLPS();
    }
    
    // Search in multiple texts efficiently
    vector<int> searchInText(const string& text) {
        // Use precomputed LPS
        return search(text);
    }
};
```

## 🎓 Advanced Applications

1. **DNA Sequence Analysis**: Finding specific gene sequences
2. **Text Editors**: Find and replace operations
3. **Network Security**: Pattern matching in network packets
4. **Bioinformatics**: Protein sequence matching
5. **Compiler Design**: Lexical analysis and token recognition

## 🔧 Optimizations and Variants

### Memory-Optimized Version
For very large patterns, you might want to compute LPS on-the-fly:

```cpp
// Space-optimized version that doesn't store full LPS array
class MemoryOptimizedKMP {
    // Implementation that recomputes LPS values as needed
    // Trades time for space
};
```

### Multi-Pattern KMP (Aho-Corasick)
For searching multiple patterns simultaneously, consider the Aho-Corasick algorithm, which extends KMP concepts.

## 📚 Further Reading

- Original paper: "Fast Pattern Matching in Strings" by Knuth, Morris, and Pratt (1977)
- Related algorithms: Boyer-Moore, Rabin-Karp, Aho-Corasick
- Applications in computational biology and text processing

---

*This implementation provides a solid foundation for understanding and using the KMP algorithm. The code is educational, well-commented, and includes practical examples and optimizations.*
