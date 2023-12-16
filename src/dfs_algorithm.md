# Depth-First Search (DFS) Algorithm

Depth-First Search (DFS) is a graph traversal algorithm that explores vertices and their edges by going as deep as possible before backtracking. It is used to visit all the vertices of a graph in a systematic manner.

## Algorithm Overview

1. Start from a source vertex.
2. Visit the source vertex and mark it as visited.
3. Explore an unvisited neighbor of the current vertex.
4. If an unvisited neighbor is found, repeat steps 2-3 for that neighbor.
5. If no unvisited neighbor is found, backtrack to the previous vertex.
6. Repeat steps 2-5 until all vertices are visited.

## Recursive DFS

The recursive version of DFS is implemented using a function that calls itself for each unvisited neighbor.

```
void dfs_recursive(const std::vector<std::vector<int>>& graph, int current, std::vector<bool>& visited) {
    // Mark the current vertex as visited
    visited[current] = true;
    std::cout << current << " ";

    // Explore all unvisited neighbors
    for (int neighbor : graph[current]) {
        if (!visited[neighbor]) {
            dfs_recursive(graph, neighbor, visited);
        }
    }
}

int main() {
    // Example graph represented as an adjacency list
    std::vector<std::vector<int>> graph = {
        {1, 2},
        {3},
        {4},
        {},
        {}
    };

    // Initialize visited array
    std::vector<bool> visited(graph.size(), false);

    // Example usage
    std::cout << "Recursive DFS starting from vertex 0:\n";
    dfs_recursive(graph, 0, visited);
    std::cout << "\n";

    return 0;
}
```
