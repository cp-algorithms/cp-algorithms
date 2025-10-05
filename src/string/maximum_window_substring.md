---
tags:
  - Sliding Window
  - Two Pointers
  - Hash Map
  - String
---

# Minimum Window Substring

The **Minimum Window Substring** is a classic **sliding window** problem that asks you to find the smallest substring in `s` containing all the characters of string `t` (including duplicates).  

This problem tests one’s ability to maintain dynamic character counts while expanding and contracting a window efficiently — an essential pattern in substring and subarray problems.

---

## 🧩 Problem Statement

Given two strings `s` and `t` of lengths `m` and `n` respectively, return the **minimum window substring** of `s` such that every character in `t` (including duplicates) is included in the window.  
If there is **no such substring**, return the empty string `""`.

It is guaranteed that the answer is unique.

---

### Example 1:
```
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
```

### Example 2:
```
Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.
```

### Example 3:
```
Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included, but s has only one 'a'.
```


---

## ⚙️ Constraints

- `m == s.length`
- `n == t.length`
- `1 <= m, n <= 10^5`
- `s` and `t` consist of uppercase and lowercase English letters.

---

## 🚀 Approach

The goal is to maintain a **window** over string `s` that always contains all characters of `t` — and shrink it whenever possible to find the smallest such window.

### Key Steps:
1. **Store frequency of characters** in `t` using a hash map.  
2. Use two pointers (`left` and `right`) to represent the current window in `s`.  
3. Expand the `right` pointer to include new characters until all characters in `t` are covered.  
4. Once valid, **move the `left` pointer** to shrink the window while maintaining validity.  
5. Keep track of the smallest valid window seen so far.

---

## 🧠 Algorithm

1. Initialize:
   - A frequency map `freqT` for characters in `t`.
   - A frequency map `window` for current characters in `s`.
   - Counters for how many characters are satisfied.
2. Move `right` pointer across `s`:
   - Include the current character in `window`.
   - If it matches the desired count in `t`, increment the `formed` counter.
3. When `formed == required` (all characters satisfied):
   - Try to shrink the window from the left.
   - Update the answer when a smaller valid window is found.
4. Continue until the end of `s`.

---

## ⏱️ Complexity Analysis

- **Time Complexity:** `O(m + n)`  
  Each character in `s` is visited at most twice — once when expanding and once when contracting the window.

- **Space Complexity:** `O(k)`  
  Where `k` is the number of distinct characters in `t`.

---

## 💻 Implementation

### C++ Solution

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (t.empty() || s.empty()) return "";

        // Dictionary which keeps a count of all the unique characters in t
        unordered_map<char, int> freqT, window;
        for (char c : t) freqT[c]++;

        int have = 0, need = freqT.size();
        int resLen = INT_MAX;
        int resL = 0, resR = 0;

        int l = 0;
        for (int r = 0; r < s.size(); r++) {
            char c = s[r];
            window[c]++;
            
            // If the current character added equals the desired count in t
            if (freqT.count(c) && window[c] == freqT[c])
                have++;

            // Try to contract the window from left until it ceases to be 'desirable'
            while (have == need) {
                // Update our result if this window is smaller
                if ((r - l + 1) < resLen) {
                    resL = l;
                    resR = r;
                    resLen = r - l + 1;
                }
                
                // The character at position l is no longer part of the window
                window[s[l]]--;
                if (freqT.count(s[l]) && window[s[l]] < freqT[s[l]])
                    have--;
                l++;
            }
        }
        
        return resLen == INT_MAX ? "" : s.substr(resL, resLen);
    }
};

// Test function
void testMinWindow() {
    Solution sol;
    
    // Test cases
    vector<pair<pair<string, string>, string>> testCases = {
        {{"ADOBECODEBANC", "ABC"}, "BANC"},
        {{"a", "a"}, "a"},
        {{"a", "aa"}, ""},
        {{"ab", "b"}, "b"},
        {{"bba", "ab"}, "ba"}
    };
    
    cout << "=== Minimum Window Substring Tests ===" << endl;
    
    for (int i = 0; i < testCases.size(); i++) {
        string s = testCases[i].first.first;
        string t = testCases[i].first.second;
        string expected = testCases[i].second;
        string result = sol.minWindow(s, t);
        
        cout << "Test " << (i + 1) << ":" << endl;
        cout << "  Input: s = \"" << s << "\", t = \"" << t << "\"" << endl;
        cout << "  Expected: \"" << expected << "\"" << endl;
        cout << "  Got: \"" << result << "\"" << endl;
        cout << "  Status: " << (result == expected ? "✓ PASS" : "✗ FAIL") << endl;
        cout << endl;
    }
}

int main() {
    testMinWindow();
    return 0;
}
```

### Python Solution

```python
def minWindow(s: str, t: str) -> str:
    """
    Find the minimum window substring containing all characters of t
    
    Args:
        s: Source string
        t: Target string containing characters to find
        
    Returns:
        Minimum window substring or empty string if no valid window exists
    """
    if not t or not s:
        return ""

    # Dictionary to keep count of all unique characters in t
    dict_t = {}
    for char in t:
        dict_t[char] = dict_t.get(char, 0) + 1

    required = len(dict_t)  # Number of unique characters in t
    
    # Left and right pointers
    l, r = 0, 0
    
    # formed is used to keep track of how many unique characters in the 
    # current window have the desired frequency
    formed = 0
    
    # Dictionary to keep count of characters in current window
    window_counts = {}
    
    # Answer tuple (window length, left, right)
    ans = float("inf"), None, None
    
    while r < len(s):
        # Add one character from the right to the window
        character = s[r]
        window_counts[character] = window_counts.get(character, 0) + 1
        
        # If the current character's count matches the desired count in t
        if character in dict_t and window_counts[character] == dict_t[character]:
            formed += 1
        
        # Try to contract the window from the left
        while l <= r and formed == required:
            character = s[l]
            
            # Save the smallest window until now
            if r - l + 1 < ans[0]:
                ans = (r - l + 1, l, r)
            
            # Remove from the left of our window
            window_counts[character] -= 1
            if character in dict_t and window_counts[character] < dict_t[character]:
                formed -= 1
            
            # Move the left pointer ahead for the next iteration
            l += 1    
        
        # Keep expanding the window by moving right pointer
        r += 1    
    
    return "" if ans[0] == float("inf") else s[ans[1] : ans[2] + 1]

# Test the function
if __name__ == "__main__":
    test_cases = [
        ("ADOBECODEBANC", "ABC", "BANC"),
        ("a", "a", "a"),
        ("a", "aa", ""),
        ("ab", "b", "b"),
        ("bba", "ab", "ba")
    ]
    
    print("=== Minimum Window Substring Tests (Python) ===")
    
    for i, (s, t, expected) in enumerate(test_cases, 1):
        result = minWindow(s, t)
        print(f"Test {i}:")
        print(f"  Input: s = '{s}', t = '{t}'")
        print(f"  Expected: '{expected}'")
        print(f"  Got: '{result}'")
        print(f"  Status: {'✓ PASS' if result == expected else '✗ FAIL'}")
        print()
```

---

## 🎯 Step-by-Step Example

Let's trace through the algorithm with `s = "ADOBECODEBANC"` and `t = "ABC"`:

### Initial Setup:
- `freqT = {'A': 1, 'B': 1, 'C': 1}`
- `need = 3` (unique characters in t)
- `have = 0` (characters satisfied)
- `window = {}` (current window character counts)

### Iteration Steps:

| Step | r | s[r] | window | have | Valid? | Action |
|------|---|------|--------|------|--------|--------|
| 1 | 0 | A | {A:1} | 1 | No | Expand |
| 2 | 1 | D | {A:1, D:1} | 1 | No | Expand |
| 3 | 2 | O | {A:1, D:1, O:1} | 1 | No | Expand |
| 4 | 3 | B | {A:1, D:1, O:1, B:1} | 2 | No | Expand |
| 5 | 4 | E | {A:1, D:1, O:1, B:1, E:1} | 2 | No | Expand |
| 6 | 5 | C | {A:1, D:1, O:1, B:1, E:1, C:1} | 3 | **Yes** | Contract |

When valid window found at step 6:
- Current window: "ADOBEC" (length 6)
- Start contracting from left...
- Continue until we find minimum window "BANC" (length 4)

---

## 🔗 Related Concepts

### 🪟 **Sliding Window Technique**
A powerful technique for solving substring/subarray problems efficiently by maintaining a window that expands and contracts based on certain conditions.

### 👥 **Two Pointer Technique**
Uses two pointers (left and right) to traverse the array/string, often used in conjunction with sliding window.

### 🗺️ **Hash Maps for Frequency Counting**
Essential for tracking character frequencies in both the target string and current window.

---

## 🧠 Practice Problems

Here are related problems to strengthen your sliding window skills:

### Easy:
- 🔗 [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
- 🔗 [Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)

### Medium:
- 🔗 [Permutation in String](https://leetcode.com/problems/permutation-in-string/)
- 🔗 [Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/)
- 🔗 [Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/)

### Hard:
- 🔗 [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)
- 🔗 [Minimum Window Subsequence](https://leetcode.com/problems/minimum-window-subsequence/)

---

## 📚 Additional Resources

- **LeetCode Problem**: [Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)
- **Time Complexity**: O(|s| + |t|)
- **Space Complexity**: O(|s| + |t|)
- **Difficulty**: Hard
- **Topics**: Sliding Window, Hash Table, String, Two Pointers

---

## 💡 Key Takeaways

1. **Sliding Window Pattern**: This problem is a classic example of the sliding window technique
2. **Character Frequency**: Use hash maps to efficiently track character counts
3. **Two Conditions**: Expand when window is invalid, contract when window is valid
4. **Optimization**: Each character is visited at most twice (once during expansion, once during contraction)
5. **Edge Cases**: Handle empty strings and impossible cases gracefully

---

*This algorithm is fundamental for understanding sliding window techniques and serves as a building block for many advanced string processing problems.*