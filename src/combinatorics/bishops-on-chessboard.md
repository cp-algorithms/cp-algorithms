<!--?title Placing Bishops on a Chessboard -->

# Placing Bishops on a Chessboard

Find the number of ways to place $K$ bishops on an $N \times N$ chessboard so that no two bishops attack each other.

## Algorithm

This problem can be solved using dynamic programming.

Let's enumerate the diagonals of the chessboard as follows: black diagonals have odd indices, white diagonals have even indices, and the diagonals are numbered in non-decreasing order of the number of squares in them. Here is an example for a $5 \times 5$ chessboard.

$$\begin{matrix}
\bf{1} & 2 & \bf{5} & 6 & \bf{9} \\\
2 & \bf{5} & 6 & \bf{9} & 8 \\\
\bf{5} & 6 & \bf{9} & 8 & \bf{7} \\\
6 & \bf{9} & 8 & \bf{7} & 4 \\\
\bf{9} & 8 & \bf{7} & 4 & \bf{3} \\\
\end{matrix}$$

Let D[i][j] denote the number of ways to place j bishops on diagonals up to i which have the same color as diagonal i. Then $i = 1...2N-1$, $j = 0..K$.

We can calculate D[i][...] using only values D[i-2][...] (we subtract 2 because we consider diagonals of the same color as i). There are two ways to get D[i][j]. First, we can place all j bishops on previous diagonals; there are D[i-2][j] ways to do this. Second, we can place one bishop on diagonal i and j-1 bishops on previous diagonals. The number of ways to do this equals the number of squares in diagonal i minus (j-1), because each of j-1 bishops placed on previous diagonals will block one square on the current diagonal. The number of squares in diagonal i can be calculated as follows:

```cpp
int squares (int i) {
     if (i & 1)
          return i / 4 * 2 + 1;
     else
          return (i - 1) / 4 * 2 + 2;
}
```

The base case is simple: D[i][0] = 1, D[1][1] = 1.

Once we have calculated all values of D[i][j], the answer can be obtained as follows: consider all possible numbers of bishops placed on black diagonals $i=0..K$, with corresponding numbers of bishops on white diagonals $K-i$. The bishops placed on black and white diagonals never attack each other, so the placements can be done independently. The index of the last black diagonal is $2N-1$, the last white one - $2N-2$. For each i we add D[2N-1][i] * D[2N-2][K-i] to the answer.

## Implementation

```cpp
int squares (int i) {
    if (i & 1)
        return i / 4 * 2 + 1;
    else
        return (i - 1) / 4 * 2 + 2;
}
int n, k; // input data
if (k > 2*n-1) {
    cout << 0;
    return 0;
}

vector < vector<int> > d (n*2, vector<int> (k+2));
for (int i=0; i<n*2; ++i)
    d[i][0] = 1;
d[1][1] = 1;
for (int i=2; i<n*2; ++i)
    for (int j=1; j<=k; ++j)
        d[i][j] = d[i-2][j] + d[i-2][j-1] * (squares(i) - j + 1);

int ans = 0;
for (int i=0; i<=k; ++i)
    	ans += d[n*2-1][i] * d[n*2-2][k-i];
cout << ans;
```
