/**
 * Solves the Matrix Chain Multiplication (MCM) problem using dynamic programming (DP) partitioning.
 *
 * The MCM problem seeks the most efficient way to multiply a given sequence of matrices, minimizing the total number of scalar multiplications.
 * This implementation uses DP to partition the sequence at every possible position, recursively calculating the minimum cost for each subproblem.
 *
 * Key Concepts:
 * - The input is an array representing the dimensions of matrices such that the i-th matrix has dimensions arr[i-1] x arr[i].
 * - The DP table stores the minimum multiplication cost for every subarray (i, j).
 * - For each partition point k between i and j, the cost is calculated as:
 *   cost = dp[i][k] + dp[k+1][j] + arr[i-1] * arr[k] * arr[j]
 * - The minimum cost among all possible partitions is stored in dp[i][j].
 *
 * Usage:
 * - Call the function with the array of dimensions to get the minimum multiplication cost.
 * - Useful for optimizing matrix computations in scientific computing, graphics, and machine learning.
 *
 * Time Complexity: O(n^3), where n is the number of matrices.
 * Space Complexity: O(n^2), due to the DP table.
 *
 * Example:
 *   Input: arr = [10, 20, 30, 40, 30]
 *   Output: Minimum cost to multiply the chain of matrices.
 */