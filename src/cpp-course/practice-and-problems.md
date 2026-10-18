---
title: Practice and Problems
tags:
  - Course
---

# Practice and Problems

Theory is essential, but solving problems is what truly builds intuition, speed, and problem-solving skills. This section provides a structured roadmap, curated resources, and practical advice for mastering C++ in competitive programming.

## Why Practice Matters

- **Reinforces concepts**: Applying theory to real problems solidifies understanding.
- **Builds pattern recognition**: You'll learn to identify standard problem types (two pointers, prefix sums, BFS/DFS, etc.).
- **Improves implementation speed**: Frequent coding builds muscle memory for STL, I/O, and debugging.
- **Teaches edge cases**: Real judges test boundary conditions you won't think of alone.
- **Develops debugging skills**: Reading errors, stress-testing, and fixing logic bugs are crucial.

## Structured Practice Roadmap

### Phase 1: Fundamentals (1–4 weeks)

Focus on syntax, control flow, arrays, vectors, functions, and basic logic.

**Recommended problems:**

1. [CSES - Weird Algorithm](https://cses.fi/problemset/task/1068) – Loops and simulation
2. [CSES - Missing Number](https://cses.fi/problemset/task/1083) – Arithmetic, sums
3. [CSES - Repetitions](https://cses.fi/problemset/task/1069) – String/array scanning
4. [Codeforces 4A - Watermelon](https://codeforces.com/problemset/problem/4/A) – Basic conditionals
5. [Codeforces 71A - Way Too Long Words](https://codeforces.com/problemset/problem/71/A) – String manipulation
6. [Codeforces 231A - Team](https://codeforces.com/problemset/problem/231/A) – Logic and counting
7. [CSES - Permutations](https://cses.fi/problemset/task/1070) – Constructive thinking

### Phase 2: Arrays, Sorting, Searching (4–8 weeks)

Master linear scans, sorting, binary search, prefix sums.

**Recommended problems:**

1. [CSES - Increasing Array](https://cses.fi/problemset/task/1094) – Greedy
2. [CSES - Two Sum](https://cses.fi/problemset/task/1640) – Hashing/binary search
3. [CSES - Maximum Subarray Sum](https://cses.fi/problemset/task/1643) – Kadane's algorithm
4. [CSES - Distinct Numbers](https://cses.fi/problemset/task/1621) – Sorting + set
5. [Codeforces 339B - Xenia and Ringroad](https://codeforces.com/problemset/problem/339/B) – Simulation
6. [Codeforces 136A - Presents](https://codeforces.com/problemset/problem/136/A) – Arrays
7. [Codeforces 580A - Kefa and First Steps](https://codeforces.com/problemset/problem/580A) – Subarrays

### Phase 3: STL and Data Structures (2–4 weeks)

Get comfortable with `vector`, `set`, `map`, `stack`, `queue`, `priority_queue`.

**Recommended problems:**

1. [CSES - Apartments](https://cses.fi/problemset/task/1084) – Two pointers
2. [CSES - Ferris Wheel](https://cses.fi/problemset/task/1090) – Greedy + sorting
3. [CSES - Playlist](https://cses.fi/problemset/task/1141) – Sliding window + map
4. [Codeforces 1A - Theatre Square](https://codeforces.com/problemset/problem/1A) – Math + ceiling
5. [Codeforces 977A - Wrong Subtraction](https://codeforces.com/problemset/problem/977A) – Loop
6. [Codeforces 4C - Registration System](https://codeforces.com/problemset/problem/4C) – `map`/`unordered_map`

### Phase 4: Basic Algorithms (Ongoing)

Introduce recursion, DFS/BFS intuition, prefix sums, two pointers more deeply.

**Recommended problems:**

1. [CSES - Subarray Sums I](https://cses.fi/problemset/task/1660) – Prefix sums + two pointers
2. [CSES - Subarray Distinct Values](https://cses.fi/problemset/task/2448) – Sliding window
3. [CSES - Nearest Smaller Values](https://cses.fi/problemset/task/1645) – Stack
4. [CSES - Restaurant Customers](https://cses.fi/problemset/task/1619) – Sorting + events
5. [Codeforces 313B - Ilya and Queries](https://codeforces.com/problemset/problem/313B) – Prefix sums

## Top Online Judges

| Platform | Focus | Difficulty Range | Notes |
|---|---|---|---|
| **[CSES Problem Set](https://cses.fi/problemset/)** | Fundamentals & algorithms | Easy–Hard | Exceptionally well-structured. Start here! Clear, short problems with editorials. |
| **[Codeforces](https://codeforces.com/)** | Contests + problemset | Div. 4 up to Div. 1 | Most active community. Great contests, ratings, and in-depth editorials. |
| **[AtCoder](https://atcoder.jp/)** | High-quality contests | Beginner–Advanced | Problems are very well-designed. Beginner contests (ABC) are perfect for learning. |
| **[CodeChef](https://www.codechef.com/)** | Long contests + practice | Easy–Hard | Good for consistent practice. Long Challenge is monthly. |
| **[SPOJ](https://www.spoj.com/)** | Classic problems | Easy–Very Hard | Massive archive of classical algorithmic problems. |
| **[UVa](https://onlinejudge.org/)** | Legacy classics | Easy–Hard | Excellent for IOI/ACM ICPC style problems. Many solutions online. |

## Effective Practice Strategies

### Solve Actively, Not Passively

- **Understand before coding**: Read carefully, identify constraints, think of approach.
- **Code from scratch**: Don't peek at solutions until truly stuck (spend 30–60 min trying).
- **Analyze solutions**: When stuck, read editorial/others' code. Understand *why*, not just *how*.
- **Implement again**: After reading solution, close it and code it yourself.
- **Upsolve**: After contests, solve problems you couldn't complete during contest time.

### Develop Good Habits

- **Use fast I/O**: Always include `ios_base::sync_with_stdio(false); cin.tie(NULL);`
- **Stress test**: For tricky logic, create small edge cases (n=0/1, duplicates, extremes).
- **Write clean code**: Use meaningful names, proper indentation, small functions.
- **Track progress**: Keep a list (notes/app) of solved problems and patterns learned.
- **Practice regularly**: Consistency > intensity. 30–90 min daily beats 8 hours once/month.
- **Time-box**: Don't grind one problem for 3 hours blindly—learn to recognize when to seek hints.

### Learn by Patterns

As you solve, categorize problems by technique:

- **Greedy**: Activity selection, interval covering
- **Two Pointers**: Pair sums, subarrays
- **Prefix Sums**: Range sums/queries
- **Sliding Window**: Longest substring with conditions
- **Hash Maps/Sets**: Frequency, distinct
- **Binary Search**: On array or on answer
- **DFS/BFS**: Graph traversals (learn later)
- **Dynamic Programming**: Knapsack, LIS (learn later)

Keeping a personal "cheat-sheet" of patterns accelerates learning.

## Debugging and Testing Tips

- **Read sample carefully**: Samples reveal exact I/O and edge behavior.
- **Print debugging**: Use `cerr` (tied off? `cerr.tie(NULL)` not needed, but `cerr` doesn't flush with `cout`; also can do `#ifdef DEBUG`).
- **Edge cases**: Test n=1, all same elements, negative numbers (if allowed), large values.
- **Integer types**: Watch for overflow—use `long long` liberally.
- **Constraints check**: Ensure your algorithm matches $n$ limits.
- **Compare with brute force**: For small cases, generate expected vs actual.

## Recommended Learning Path

1. **Complete this C++ course**: Introduction through STL Basics and Complexity.
2. **Solve CSES first 30–40 problems**: Builds rock-solid fundamentals.
3. **Do Codeforces Div. 4 contests**: Low-pressure, educational.
4. **Move to AtCoder ABC**: Excellent explanations and difficulty curve.
5. **Gradually tackle harder problems**: Increase difficulty only after comfort.
6. **Learn data structures/algorithms**: Explore graph, DP, etc. as needed.
7. **Participate regularly**: Contests build speed and resilience.

## Additional Resources

- **[Competitive Programmer's Handbook](https://cses.fi/book/book.pdf)** – Free, concise, covers core topics
- **[Codeforces EDU](https://codeforces.com/edu/course/2)** – Structured courses with practice
- **[USACO Guide](https://usaco.guide/)** – Comprehensive, well-organized roadmap
- **[CP-Algorithms](https://cp-algorithms.com/)** – This very site! Advanced algorithms explained clearly
- **[AtCoder Editorials](https://atcoder.jp/contests/)** – High-quality explanations

## Final Advice

- **Quality over quantity**: Solving 10 problems deeply teaches more than 100 superficially.
- **Embrace struggle**: Getting stuck is normal; it's where growth happens.
- **Stay consistent**: 20 focused minutes daily is better than sporadic marathons.
- **Join community**: Discuss approaches on Codeforces/Discord after solving.
- **Don't chase rating alone**: Focus on learning and problem-solving skills.
- **Have fun**: Curiosity and persistence matter more than innate talent.

**Remember:** Every expert was once a beginner. Keep practicing, stay patient, and enjoy the journey!

## Next Steps

Now that you've covered the fundamentals, explore the other sections of **cp-algorithms** (Algebra, Graphs, DP, etc.) as you encounter those topics in your practice.
