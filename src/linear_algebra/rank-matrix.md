<!--?title Rank of a matrix-->

#Finding the rank of a matrix

**The rank of a matrix** is the largest number of linearly independent rows/columns of the matrix. The rank is not only defined  for square matrices; let the matrix be rectangular and have size $N \times M$.

The rank of a matrix can also be defined as the largest order of any non-zero minor in the matrix.

Note that if the matrix is square and its determinant is non-zero, then the rank is $N$ ($=M$); otherwise it will be less. Generally, the rank of a matrix does not exceed $\min (N, M)$.

##Algorithm

You can search for the rank using [Gaussian elimination](https://cp-algorithms.com/linear_algebra/linear-system-gauss.html). We will perform the same operations as when solving the system or finding its determinant. But if at any step in the $i$-th column there are zero-rows among the rows not selected before, then we skip this step and decrease the rank by one (Initially, the rank is set equal to $\max (N, M)$). Otherwise, if we have found a row with a non-zero element in the $i$-th column at the $i$-th step, then we mark this row as a selected one and perform the usual operations of taking this row away from the rest.

##Implementation

    const double EPS = 1E-9;

    int rank = max(n,m);
    vector<char> line_used (n);
    for (int i=0; i<m; ++i) {
      int j;
      for (j=0; j<n; ++j)
        if (!line_used[j] && abs(a[j][i]) > EPS)
          break;
      if (j == n)
        --rank;
      else {
        line_used[j] = true;
        for (int p=i+1; p<m; ++p)
          a[j][p] /= a[j][i];
        for (int k=0; k<n; ++k)
          if (k != j && abs (a[k][i]) > EPS)
            for (int p=i+1; p<m; ++p)
              a[k][p] -= a[j][p] * a[k][i];
      }
    }
