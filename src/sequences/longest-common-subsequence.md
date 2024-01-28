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

Solution using caching, or memoized solution is when additional space is used to store the result of the algorithm/program at a particular state, so that it can be used repeatedly without the need of doing calculation for that particular state again.

The recursive solution from above, the state is depended upon two numbers, index $x$ and $y$. Thus, we need 2-dimensional space to store the states.

For each, $x$ and $y$, we'll check if solution already exists or not. If it does, we'll use that solution. Also, we'll keep storing the solutions for new $x$ and $y$. Implementation goes as follow:

### Implementation

```cpp title="lcs_caching" linenums="1"
int longest_common_subsequence_caching(string text1, string text2) {
	int a = text1.size(), b = text2.size();
	space.resize(a, vector<int>(b, -1));

	function<int(int x, int y)> lcs = [&](int x, int y) -> int {
		if (x >= a || y >= b) return 0;

		if (space[x][y] != -1) return space[x][y];

		int length = 0;
		if (text1[x] == text1[y]) {
			length = 1 + lcs(x + 1, y + 1);
		} else length = max(lcs(x + 1, y), lcs(x, y + 1));

		return space[x][y] = length;
	};

	return lcs(0, 0);
}
```

## Solution using Dynamic Programming

The problem can also be solved using **Dynamic Programming**. Well, the caching solution from above is also considered as DP but is not pure DP.

This approach, which is also known as **Tabulated DP** is better than caching solution in some senses as follow:

* It is iterative and thus when you have large set of input (ie., length of strings provided is quite large), this approach would work faster than caching solution from above, which is based on recursive solution.

* This approach is also useful when you need the solution for given input on every state depending on $x$ and $y$, instead of just some subsets of state.

Based on how you write the _transition_ part of the solution, this DP approach can be of following two types:

- Pull DP
- Push DP

When using tabulated solution, we deal with base cases before starting to iterate for all the states ie., just before when loop starts. For this particular problem, base case is already set to zero, as we are initializing (resizing the empty space) the space with 0. The base case is when either when $text1$ is empty and thus

```cpp
for (int i = 0; i < text2.size(); i++) {
	space[0][i] = 0;
}
```

Or when $text2$ is empty and thus

```cpp
for (int i = 0; i < text1.size(); i++) {
	space[i][0] = 0;
}
```

or both $text1$ and $text2$ both are empty, ie., $space[0][0] = 0$

Lets see the implementation in both ways of tabulated solution.

## Pull DP

Pull DP is when, the solution for current state relies on the previous calculated state/s.


```cpp title="lcs_pull_dp" linenums="1"
int longest_common_subsequence_pulldp(string text1, string text2) {
	int a = text1.size(), b = text2.size();
	space.resize(a + 1, vector<int>(b + 1, 0));

	for (int i = 1; i <= a; i++) {
		for (int j = 1; j <= b; j++) {
			if (text1[i - 1] == text2[j - 1]) space[i][j] = space[i - 1][j - 1] + 1;
			else space[i][j] = max(space[i - 1][j], space[i][j - 1]);
		}
	}

	return space[a][b];
}
```

Here, lets focus on one part of the transition from above solution

$$space[i][j] = space[i - 1][j - 1] + 1;$$

We can see that the current state represented by $i$ and $j$ as current index for both the strings as $space[i][j]$, is dependent upon the previous already calculated state as $space[i - 1][j - 1]$

## Push DP

Push DP is when the solution for current state contributes to the future state/s of the solution.

```cpp title="lcs_push_dp" linenums="1"
int longest_common_subsequence_pushdp(string text1, string text2) {
	int a = text1.size(), b = text2.size();
	space.resize(a + 1, vector<int>(b + 1, 0));

	for (ll i = 0; i < a; i++) {
		for (ll j = 0; j < b; j++) {
			if (text1[i] == text2[j]) space[i + 1][j + 1] = space[i][j] + 1;
			else space[i + 1][j + 1] = max(space[i + 1][j], space[i][j + 1]);
		}
	}

	return space[a][b];
}
```

Here, lets focus on one part of the transition from above solution

$$space[i + 1][j + 1] = space[i][j] + 1;$$

We can see that the current state represented by $i$ and $j$ as current index for both the strings as $space[i][j]$, is contributing for the solution of upcoming state for $space[i + 1][j + 1]$

Push DP and Pull DP are not that much different from each other, you can decide for yourself which idea to solve tabulated DP clicks you.
