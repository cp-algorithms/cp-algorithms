---
title: Main Page
---
# Algorithms for Competitive Programming

*The goal of this project is to translate the wonderful resource
[http://e-maxx.ru/algo](http://e-maxx.ru/algo) which provides descriptions of many algorithms
and data structures especially popular in field of competitive programming.
Moreover we want to improve the collected knowledge by extending the articles
and adding new articles to the collection.*

## Changelog

- January 16, 2022: Switched to the [MkDocs](https://www.mkdocs.org/) site generator with the [Material for MkDocs](https://squidfunk.github.io/mkdocs-material/) theme, which give the website a more modern look, brings a couple of new features (dark mode, better search, ...), makes the website more stable (in terms of rendering math formulas), and makes it easier to contribute.

Full list of updates: [Commit History](https://github.com/e-maxx-eng/e-maxx-eng/commits/master)

## Articles

### Algebra

- **Fundamentals**
    - [Binary Exponentiation](algebra/binary-exp.md)
    - [Euclidean algorithm for computing the greatest common divisor](algebra/euclid-algorithm.md)
    - [Extended Euclidean Algorithm](algebra/extended-euclid-algorithm.md)
    - [Linear Diophantine Equations](algebra/linear-diophantine-equation.md)
    - [Fibonacci Numbers](algebra/fibonacci-numbers.md)
- **Prime numbers**
    - [Sieve of Eratosthenes](algebra/sieve-of-eratosthenes.md)
    - [Linear Sieve](algebra/prime-sieve-linear.md)
    - [Primality tests](algebra/primality_tests.md)
    - [Integer factorization](algebra/factorization.md)
- **Number-theoretic functions**
    - [Euler's totient function](algebra/phi-function.md)
    - [Number of divisors / sum of divisors](algebra/divisors.md)
- **Modular arithmetic**
    - [Modular Inverse](algebra/module-inverse.md)
    - [Linear Congruence Equation](algebra/linear_congruence_equation.md)
    - [Chinese Remainder Theorem](algebra/chinese-remainder-theorem.md)
    - [Factorial modulo $p$](algebra/factorial-modulo.md)
    - [Discrete Log](algebra/discrete-log.md)
    - [Primitive Root](algebra/primitive-root.md)
    - [Discrete Root](algebra/discrete-root.md)
    - [Montgomery Multiplication](algebra/montgomery_multiplication.md)
- **Number systems**
    - [Balanced Ternary](algebra/balanced-ternary.md)
    - [Gray code](algebra/gray-code.md)
- **Miscellaneous**
    - [Enumerating submasks of a bitmask](algebra/all-submasks.md)
    - [Arbitrary-Precision Arithmetic](algebra/big-integer.md)
    - [Fast Fourier transform](algebra/fft.md)
    - [Operations on polynomials and series](algebra/polynomial.md)

### Data Structures

- **Fundamentals**
    - [Minimum Stack / Minimum Queue](data_structures/stack_queue_modification.md)
    - [Sparse Table](data_structures/sparse-table.md)
- **Trees**
    - [Disjoint Set Union](data_structures/disjoint_set_union.md)
    - [Fenwick Tree](data_structures/fenwick.md)
    - [Sqrt Decomposition](data_structures/sqrt_decomposition.md)
    - [Segment Tree](data_structures/segment_tree.md)
    - [Treap](data_structures/treap.md)
    - [Sqrt Tree](data_structures/sqrt-tree.md)
    - [Randomized Heap](data_structures/randomized_heap.md)
- **Advanced**
    - [Deleting from a data structure in O(T(n)log n)](data_structures/deleting_in_log_n.md)

### Dynamic Programming

- **DP optimizations**
    - [Divide and Conquer DP](dynamic_programming/divide-and-conquer-dp.md)
- **Tasks**
    - [Dynamic Programming on Broken Profile. Problem "Parquet"](dynamic_programming/profile-dynamics.md)
    - [Finding the largest zero submatrix](dynamic_programming/zero_matrix.md)

### String Processing

- **Fundamentals**
    - [String Hashing](string/string-hashing.md)
    - [Rabin-Karp for String Matching](string/rabin-karp.md)
    - [Prefix function - Knuth-Morris-Pratt](string/prefix-function.md)
    - [Z-function](string/z-function.md)
    - [Suffix Array](string/suffix-array.md)
    - [Aho-Corasick algorithm](string/aho_corasick.md)
- **Advanced**
    - [Suffix Tree](string/suffix-tree-ukkonen.md)
    - [Suffix Automaton](string/suffix-automaton.md)
    - [Lyndon factorization](string/lyndon_factorization.md)
- **Tasks**
    - [Expression parsing](string/expression_parsing.md)
    - [Manacher's Algorithm - Finding all sub-palindromes in O(N)](string/manacher.md)
    - [Finding repetitions](string/main_lorentz.md)

### Linear Algebra

- **Matrices**
    - [Gauss & System of Linear Equations](linear_algebra/linear-system-gauss.md)
    - [Gauss & Determinant](linear_algebra/determinant-gauss.md)
    - [Kraut & Determinant](linear_algebra/determinant-kraut.md)
    - [Rank of a matrix](linear_algebra/rank-matrix.md)

### Combinatorics

- **Fundamentals**
    - [Finding Power of Factorial Divisor](algebra/factorial-divisors.md)
    - [Binomial Coefficients](combinatorics/binomial-coefficients.md)
    - [Catalan Numbers](combinatorics/catalan-numbers.md)
- **Techniques**
    - [The Inclusion-Exclusion Principle](combinatorics/inclusion-exclusion.md)
    - [Burnside's lemma / Pólya enumeration theorem](combinatorics/burnside.md)
    - [Stars and bars](combinatorics/stars_and_bars.md)
    - [Generating all $K$-combinations](combinatorics/generating_combinations.md)
- **Tasks**
    - [Placing Bishops on a Chessboard](combinatorics/bishops-on-chessboard.md)
    - [Balanced bracket sequences](combinatorics/bracket_sequences.md)
    - [Counting labeled graphs](combinatorics/counting_labeled_graphs.md)

### Numerical Methods

- **Search**
    - [Ternary Search](num_methods/ternary_search.md)
    - [Newton's method for finding roots](num_methods/roots_newton.md)
- **Integration**
    - [Integration by Simpson's formula](num_methods/simpson-integration.md)

### Geometry

- **Elementary operations**
    - [Basic Geometry](geometry/basic-geometry.md)
    - [Finding the equation of a line for a segment](geometry/segment-to-line.md)
    - [Intersection Point of Lines](geometry/lines-intersection.md)
    - [Check if two segments intersect](geometry/check-segments-intersection.md)
    - [Intersection of Segments](geometry/segments-intersection.md)
    - [Circle-Line Intersection](geometry/circle-line-intersection.md)
    - [Circle-Circle Intersection](geometry/circle-circle-intersection.md)
    - [Common tangents to two circles](geometry/tangents-to-two-circles.md)
    - [Length of the union of segments](geometry/length-of-segments-union.md)
- **Polygons**
    - [Oriented area of a triangle](geometry/oriented-triangle-area.md)
    - [Area of simple polygon](geometry/area-of-simple-polygon.md)
    - [Check if points belong to the convex polygon in O(log N)](geometry/point-in-convex-polygon.md)
    - [Minkowski sum of convex polygons](geometry/minkowski.md)
    - [Pick's Theorem - area of lattice polygons](geometry/picks-theorem.md)
    - [Lattice points of non-lattice polygon](geometry/lattice-points.md)
- **Convex hull**
    - [Convex hull construction](geometry/convex-hull.md)
    - [Convex hull trick and Li Chao tree](geometry/convex_hull_trick.md)
- **Sweep-line**
    - [Search for a pair of intersecting segments](geometry/intersecting_segments.md)
    - [Point location in O(log N)](geometry/point-location.md)
- **Miscellaneous**
    - [Finding the nearest pair of points](geometry/nearest_points.md)
    - [Delaunay triangulation and Voronoi diagram](geometry/delaunay.md)
    - [Vertical decomposition](geometry/vertical_decomposition.md)
    - [Half-plane intersection - S&I Algorithm in O(Nlog N)](geometry/halfplane-intersection.md)

### Graphs

- **Graph traversal**
    - [Breadth First Search](graph/breadth-first-search.md)
    - [Depth First Search](graph/depth-first-search.md)
- **Connected components, bridges, articulations points**
    - [Finding Connected Components](graph/search-for-connected-components.md)
    - [Finding Bridges in O(N+M)](graph/bridge-searching.md)
    - [Finding Bridges Online](graph/bridge-searching-online.md)
    - [Finding Articulation Points in O(N+M)](graph/cutpoints.md)
    - [Strongly Connected Components and Condensation Graph](graph/strongly-connected-components.md)
    - [Strong Orientation](graph/strong-orientation.md)
- **Single-source shortest paths**
    - [Dijkstra - finding shortest paths from given vertex](graph/dijkstra.md)
    - [Dijkstra on sparse graphs](graph/dijkstra_sparse.md)
    - [Bellman-Ford - finding shortest paths with negative weights](graph/bellman_ford.md)
    - [0-1 BFS](graph/01_bfs.md)
    - [D´Esopo-Pape algorithm](graph/desopo_pape.md)
- **All-pairs shortest paths**
    - [Floyd-Warshall - finding all shortest paths](graph/all-pair-shortest-path-floyd-warshall.md)
    - [Number of paths of fixed length / Shortest paths of fixed length](graph/fixed_length_paths.md)
- **Spanning trees**
    - [Minimum Spanning Tree - Prim's Algorithm](graph/mst_prim.md)
    - [Minimum Spanning Tree - Kruskal](graph/mst_kruskal.md)
    - [Minimum Spanning Tree - Kruskal with Disjoint Set Union](graph/mst_kruskal_with_dsu.md)
    - [Second best Minimum Spanning Tree - Using Kruskal and Lowest Common Ancestor](graph/second_best_mst.md)
    - [Kirchhoff Theorem](graph/kirchhoff-theorem.md)
    - [Prüfer code](graph/pruefer_code.md)
- **Cycles**
    - [Checking a graph for acyclicity and finding a cycle in O(M)](graph/finding-cycle.md)
    - [Finding a Negative Cycle in the Graph](graph/finding-negative-cycle-in-graph.md)
    - [Eulerian Path](graph/euler_path.md)
- **Lowest common ancestor**
    - [Lowest Common Ancestor](graph/lca.md)
    - [Lowest Common Ancestor - Binary Lifting](graph/lca_binary_lifting.md)
    - [Lowest Common Ancestor - Farach-Colton and Bender algorithm](graph/lca_farachcoltonbender.md)
    - [Solve RMQ by finding LCA](graph/rmq_linear.md)
    - [Lowest Common Ancestor - Tarjan's off-line algorithm](graph/lca_tarjan.md)
- **Flows and related problems**
    - [Maximum flow - Ford-Fulkerson and Edmonds-Karp](graph/edmonds_karp.md)
    - [Maximum flow - Push-relabel algorithm](graph/push-relabel.md)
    - [Maximum flow - Push-relabel algorithm improved](graph/push-relabel-faster.md)
    - [Maximum flow - Dinic's algorithm](graph/dinic.md)
    - [Maximum flow - MPM algorithm](graph/mpm.md)
    - [Flows with demands](graph/flow_with_demands.md)
    - [Minimum-cost flow](graph/min_cost_flow.md)
    - [Assignment problem. Solution using min-cost-flow in O (N^5)](graph/Assignment-problem-min-flow.md)
- **Matchings and related problems**
    - [Bipartite Graph Check](graph/bipartite-check.md)
    - [Kuhn' Algorithm - Maximum Bipartite Matching](graph/kuhn_maximum_bipartite_matching.md)
- **Miscellaneous**
    - [Topological Sorting](graph/topological-sort.md)
    - [Edge connectivity / Vertex connectivity](graph/edge_vertex_connectivity.md)
    - [Tree painting](graph/tree_painting.md)
    - [2-SAT](graph/2SAT.md)
    - [Heavy-light decomposition](graph/hld.md)

### Miscellaneous

- **Sequences**
    - [RMQ task (Range Minimum Query - the smallest element in an interval)](sequences/rmq.md)
    - [Longest increasing subsequence](sequences/longest_increasing_subsequence.md)
    - [Search the subsegment with the maximum/minimum sum](others/maximum_average_segment.md)
    - [K-th order statistic in O(N)](sequences/k-th.md)
- **Game Theory**
    - [Games on arbitrary graphs](game_theory/games_on_graphs.md)
    - [Sprague-Grundy theorem. Nim](game_theory/sprague-grundy-nim.md)
- **Schedules**
    - [Scheduling jobs on one machine](schedules/schedule_one_machine.md)
    - [Scheduling jobs on two machines](schedules/schedule_two_machines.md)
    - [Optimal schedule of jobs given their deadlines and durations](schedules/schedule-with-completion-duration.md)
- **Miscellaneous**
    - [Josephus problem](others/josephus_problem.md)
    - [15 Puzzle Game: Existence Of The Solution](others/15-puzzle.md)
    - [The Stern-Brocot Tree and Farey Sequences](others/stern_brocot_tree_farey_sequences.md)

---

## Contributing

- [Information for contributors](contrib.md)
- [Test-Your-Page form](preview.md)
