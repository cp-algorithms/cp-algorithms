# ✖️ Matrix Chain Multiplication (MCM)

The Matrix Chain Multiplication problem is not about performing the multiplication, but about finding the most **efficient parenthesization** (order) to multiply a chain of matrices. Matrix multiplication is associative, but the number of required scalar operations depends heavily on the grouping.

### 🎯 Goal

Given a sequence of matrices $\mathbf{A}_1, \mathbf{A}_2, \ldots, \mathbf{A}_n$, find an order of multiplication that minimizes the total number of scalar multiplications.

### 💡 Dynamic Programming Approach

The structure of the optimal solution has a split point, $k$, that divides the chain into two subproblems: $\mathbf{A}_i \cdots \mathbf{A}_k$ and $\mathbf{A}_{k+1} \cdots \mathbf{A}_j$.

* **$DP[i][j]$** stores the minimum number of scalar multiplications needed to compute the product $\mathbf{A}_i \times \cdots \times \mathbf{A}_j$.

The recurrence relation is:

$$DP[i][j] = \min_{i \leq k < j} \left( DP[i][k] + DP[k+1][j] + (\text{cost of multiplying } \mathbf{A}_i \cdots \mathbf{A}_k \text{ by } \mathbf{A}_{k+1} \cdots \mathbf{A}_j) \right)$$

The cost of the final multiplication is $p_{i-1} \cdot p_k \cdot p_j$, where $p$ is the array of matrix dimensions.

### ⚙️ Complexity

| Operation | Complexity |
| :--- | :--- |
| **Time** | $O(n^3)$ |
| **Space** | $O(n^2)$ |

*where $n$ is the number of matrices in the chain.*