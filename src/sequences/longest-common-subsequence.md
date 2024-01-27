# Longest Common Subsequence

Given two strings with of length $a$ and $b$ respectively, where $0 <= a, b <= n$. The task is to find the _length_ of **longest subsequence** which exists in both the strings.

**Subsequence** of a string is considered collection of characters from that string where some chars are deleted and relative ordering of characters are not changed.

## Solution using Recursion

Intution is, for the position $x$ and $y$ representing current index respectively for $text1$ and $text2$, we have two options:

- If $text1[x]$ matches $text2[y]$, we'll increase both x and y and will increment the _lcs_ length by 1.

- If it doesn't match, we'll take max result of one time incrementing current index for $text1$ and recursively calling the function, and one time incrementing current index for $text2$ and recursively calling the function.

### Implementation

```cpp title="lcs_recursion" linenums="1"
int longest_common_subsequence_recursion(string text1, string text2) {
	int a = text1.size(), b = text2.size();

	function<int(int x, int y)> get_lcs = [&](int x, int y) -> int {
		if (x >= a || y >= b) return 0;

		int length = 0;
		if (text1[x] == text1[y]) {
			length = 1 + get_lcs(x + 1, y + 1);
		} else length = max(get_lcs(x + 1, y), get_lcs(x, y + 1));

		return length;
	};

	return lcs(0, 0);
}
```

## Solution using Caching

Solution using caching, or memoized solution is when additional space is used to store the result of the algorithm/program at a particular stage, so that it can be used repeatedly without the need of doing calculation for that particular stage again.

## Solution using Dynamic Programming

### Pull DP

### Push DP

