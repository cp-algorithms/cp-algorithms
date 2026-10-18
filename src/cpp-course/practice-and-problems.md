---
title: Practice and Problems
tags:
  - Course
---

# Practice and Problems

Every other article in this course teaches a technique. This one teaches **how to learn the techniques** — the meta-skill that determines whether you spend six months going in circles or six months building a rating that reflects your actual ability. Competitive programming is unusual in that the raw material (problems, editorials, judges) is completely free and unlimited, yet most people who start never reach their potential. The reason is almost never intelligence. It is that they practice the wrong way: they solve problems without reflecting, look at editorials too early, avoid the discomfort of contest mode, and never target their specific weaknesses. This article is about avoiding those failure modes.

The roadmap below is not a schedule — it is a set of **mastery criteria** with concrete problem lists and debugging techniques behind each. Move through the phases as fast as you can honestly demonstrate the criteria, not on a calendar.

## Prerequisites

- The other articles in this course through [Algorithmic Complexity](algorithmic-complexity.md) — you cannot practice what you have not learned.
- A working C++ environment with `g++`, `-O2`, and the CP template.
- Accounts on [Codeforces](https://codeforces.com/) and [CSES](https://cses.fi/problemset/).

## The Two Modes of Practice

Almost all effective practice falls into one of two categories, and confusing them is the most common reason for stalled progress.

### Topic-focused practice

You pick **one technique** (prefix sums, binary search on the answer, monotonic stack) and solve 5–10 problems where it is the intended solution. The goal is **depth**: by the end, you should be able to implement the technique from memory in 5 minutes, recognize when it applies, and know its standard variations.

Where this practice lives:

- **CSES Problem Set** — the gold standard for topic-focused practice. Each section (Sorting and Searching, Dynamic Programming, Graph Algorithms) contains 20–30 problems sorted roughly by difficulty, all solvable with the section's technique. If you only use one resource, use this.
- **USACO Guide** — organized by topic with a difficulty rating per problem (Very Easy / Easy / Normal / Hard / Very Hard) that is more calibrated than raw problem ratings.
- **Codeforces EDU** — structured courses on specific techniques, with a mix of theory and practice.
- **CP-Algorithms** — this site; each algorithm article has a "Practice Problems" section at the bottom.

**The signature of good topic-focused practice:** you can feel the technique becoming reflexive. When you read a problem and think "this smells like prefix sums" before consciously reasoning, the technique has moved from working memory to long-term memory. That is the goal.

### Contest-mode practice

You sit down for **90 minutes to 2 hours**, read 5–8 mixed problems of unknown technique, and try to solve as many as you can under time pressure. The goal is **speed and judgment**: reading comprehension, problem classification, code implementation under stress, and — most importantly — knowing when to abandon a problem.

Where this practice lives:

- **Codeforces contests** — Div. 3 and Div. 4 weekly, Div. 2 twice a month, Div. 1 monthly. Rated and unrated.
- **AtCoder Beginner Contests (ABC)** — every Saturday, well-designed problems with an accessible difficulty curve.
- **Virtual contests** — Codeforces lets you replay any past contest as if it were live, with the original 2-hour timer. This is the single most underrated practice technique in CP.

**The signature of good contest-mode practice:** your rating rises (or at least your solve rate on problems at or below your level rises). The feedback is immediate and honest. You cannot fake it.

### Why you need both

Topic-focused practice without contests produces a contestant who can solve a specific technique on request but freezes on a mixed set. Contest-mode practice without topic-focus produces a contestant who can solve easy problems quickly but never learns the techniques that unlock hard problems. **Both, interleaved, is the only path that works.** A common ratio is 70% topic-focused during the week, 30% contests on weekends.

## The Four Phases: Mastery Criteria, Not Timeboxes

The original roadmap suggested "1–4 weeks" per phase. That advice is almost always wrong, because the phase duration depends entirely on prior programming background: a computer-science student can clear Phase 1 in a week; a total beginner may need three months. The right structure is a set of **mastery criteria** you can honestly test yourself against.

### Phase 1 — Fundamentals

**Mastery criteria (all must be true):**

- You can solve any problem in CSES "Introductory Problems" in **under 15 minutes**, with **zero WAs** on the first submission. There are 22 problems in that section; if you can go through them in a week with no failed submissions, you have mastered Phase 1.
- You can implement a loop with `for (int i = 0; i < n; ++i)` without thinking, and you never make off-by-one errors at boundaries (`i < n` vs `i <= n`, empty input, `n = 1`).
- You know that `10^5` is not `100000` and never write it in code.
- You can read 300 words of problem statement and correctly identify the input format, output format, and edge cases.

**Typical time to mastery:** 1–2 weeks for someone with prior programming experience, 6–12 weeks for a true beginner. Do not rush; the cost of shaky fundamentals is a permanent ceiling of ~1200 Codeforces.

**Problems** (each teaches a specific reflex):

| Problem | Teaches |
|---|---|
| [CSES — Weird Algorithm](https://cses.fi/problemset/task/1068) | Simulation, the `while (n != 1)` loop |
| [CSES — Missing Number](https://cses.fi/problemset/task/1083) | Sum of arithmetic sequence, reading large inputs efficiently |
| [CSES — Repetitions](https://cses.fi/problemset/task/1069) | Sequential scan, running counter |
| [CSES — Increasing Array](https://cses.fi/problemset/task/1094) | Greedy from left to right, **overflow** |
| [CSES — Permutations](https://cses.fi/problemset/task/1070) | Constructive thinking, the case-analysis discipline |
| [CSES — Two Sets](https://cses.fi/problemset/task/1092) | Parity reasoning, sum divisibility, **overflow in sums of 10^5 elements** |
| [Codeforces 4A — Watermelon](https://codeforces.com/problemset/problem/4/A) | Reading comprehension, edge cases (`w = 2` cannot be split) |
| [Codeforces 71A — Way Too Long Words](https://codeforces.com/problemset/problem/71/A) | String handling, `s.front()` / `s.back()` |
| [Codeforces 231A — Team](https://codeforces.com/problemset/problem/231/A) | Counting with a condition |

### Phase 2 — Arrays, Sorting, and Searching

**Mastery criteria:**

- You can solve any problem in CSES "Sorting and Searching" in **under 30 minutes**.
- You can implement `sort` with a custom comparator, `lower_bound`, `upper_bound`, and the `sort + unique + erase` deduplication without looking them up.
- You can convert a problem statement into a **sorted array + binary search** or **prefix sums + range query** in your head before writing code.
- You have solved at least 3 Codeforces Div. 2 A or B problems with **0 WAs** on first submission.

**Typical time:** 2–4 weeks.

**Problems:**

| Problem | Teaches |
|---|---|
| [CSES — Distinct Numbers](https://cses.fi/problemset/task/1621) | `sort + unique + erase`, and the "count distinct" reflex |
| [CSES — Apartments](https://cses.fi/problemset/task/1084) | Two-pointer on two sorted arrays |
| [CSES — Ferris Wheel](https://cses.fi/problemset/task/1090) | Greedy with two pointers |
| [CSES — Concert Tickets](https://cses.fi/problemset/task/1754) | `multiset` with `upper_bound` + `erase(iterator)` — the classic multiset pitfall |
| [CSES — Maximum Subarray Sum](https://cses.fi/problemset/task/1643) | Kadane's algorithm; the difference between \(O(n^2)\) naive and \(O(n)\) solution |
| [CSES — Two Sum](https://cses.fi/problemset/task/1640) | **Not** LeetCode's Two Sum — this is pair-sum: sort + two pointers, or map lookup |
| [CSES — Playlist](https://cses.fi/problemset/task/1141) | Sliding window + map, longest substring without repeating |
| [Codeforces 339B — Xenia and Ringroad](https://codeforces.com/problemset/problem/339/B) | Simulation with modular arithmetic, off-by-one |
| [Codeforces 580A — Kefa and First Steps](https://codeforces.com/problemset/problem/580/A) | Longest increasing consecutive segment |

### Phase 3 — STL and Data Structures

**Mastery criteria:**

- You can solve any problem in CSES "Data Structures" (the 20-ish problems there) in under 45 minutes.
- You have used `set`, `map`, `priority_queue`, `deque`, and `stack` each in at least one real problem.
- You know the **complexities of every STL operation you use** without looking them up — especially `set::lower_bound` vs `std::lower_bound` on a `set`.
- You can implement a monotonic stack or monotonic queue from scratch.
- You have solved at least 5 Div. 2 C problems (or equivalent).

**Typical time:** 3–6 weeks.

**Problems:**

| Problem | Teaches |
|---|---|
| [CSES — Traffic Lights](https://cses.fi/problemset/task/1163) | `set` for maintaining positions + `multiset` for maximum gaps |
| [CSES — Room Allocation](https://cses.fi/problemset/task/1164) | `priority_queue` with lazy deletion, sorting + greedy |
| [CSES — Nearest Smaller Values](https://cses.fi/problemset/task/1645) | Monotonic stack — the canonical template |
| [CSES — Sliding Window Median](https://cses.fi/problemset/task/1076) | Two heaps (one max-heap, one min-heap) + lazy deletion |
| [CSES — Josephus Problem II](https://cses.fi/problemset/task/1732) | Order statistics on a dynamic set — needs a Fenwick tree after the `set` TLEs |
| [Codeforces 4C — Registration System](https://codeforces.com/problemset/problem/4/C) | `map`/`unordered_map` frequency; the `operator[]` insert-on-read semantics |
| [Codeforces 1526B — I Hate 1111](https://codeforces.com/problemset/problem/1526/B) | Number theory + the observation that a small case suffices |
| [Codeforces 1366A — Shovels and Swords](https://codeforces.com/problemset/problem/1366/A) | Case analysis + the "when greedy fails" reasoning |

### Phase 4 — Basic Algorithms

The last phase **before** the "main" CP-Algorithms content (graphs, DP, strings, geometry — covered in later articles of this site).

**Mastery criteria:**

- You can solve any problem in CSES "Dynamic Programming" or CSES "Graph Algorithms" that does not require advanced techniques (e.g., no segment trees, no Dijkstra with lazy deletion, no union-find path compression). Basic recursion, memoization, BFS, and DFS suffice.
- You have implemented BFS and DFS both recursively and iteratively.
- You have solved at least 10 Div. 2 C and 2 Div. 2 D problems.
- Your Codeforces rating is at least ~1300 (or you can consistently solve Div. 2 A, B, C).

**Typical time:** 4–8 weeks.

**Problems:**

| Problem | Teaches |
|---|---|
| [CSES — Dice Combinations](https://cses.fi/problemset/task/1633) | The canonical 1D DP; memoization vs iterative |
| [CSES — Minimizing Coins](https://cses.fi/problemset/task/1634) | Unbounded knapsack, DP with `INF` sentinel |
| [CSES — Building Roads](https://cses.fi/problemset/task/1666) | Connected components via DFS; comparing recursive vs iterative |
| [CSES — Message Route](https://cses.fi/problemset/task/1667) | BFS on a graph with parent pointers for path reconstruction |
| [CSES — Building Teams](https://cses.fi/problemset/task/1668) | Bipartite checking via BFS; the coloring pattern |
| [CSES — Longest Flight Route](https://cses.fi/problemset/task/1680) | Topological sort + DP on DAG (longest path) |
| [Codeforces 1611E1 — Escape The Maze (easy)](https://codeforces.com/problemset/problem/1611/E1) | BFS on a tree, multi-source propagation |
| [Codeforces 1526C1 — Potions (easy)](https://codeforces.com/problemset/problem/1526/C1) | Greedy with priority queue; contrast with the DP formulation |

### When to move on

**Do not move to Phase N+1 until you can honestly check every box in Phase N.** The cost of moving early is that Phase N+1 problems are built on Phase N fluency; if you're still looking up `lower_bound` while solving a DP problem, you'll spend twice as long on each problem and never finish.

The one exception: if you've been stuck on a specific box for two weeks and you're not making progress, **move on anyway** and come back to it later. Sometimes a perspective from later material clarifies the earlier concept.

## How to Pick Problems

Random problem selection is inefficient. Three systematic approaches:

### Constraint-based selection

Read the constraints first, reverse-engineer the intended complexity, then pick the technique:

| Constraint | Likely technique |
|---|---|
| \(n \le 20\) | Brute force / bitmask DP / permutation enumeration |
| \(n \le 100\), \(m \le 100\) | Floyd–Warshall, \(O(n^3)\) DP, small graph algorithms |
| \(n \le 2000\) | \(O(n^2)\) DP or \(O(n^2 \log n)\) with care |
| \(n \le 10^5\) | \(O(n \log n)\): sorting, binary search, segment tree, Fenwick, heap |
| \(n \le 10^6\) | \(O(n)\): prefix sums, two pointers, monotonic stack |
| \(n \le 10^9\) | \(O(\log n)\) or \(O(\sqrt{n})\): number theory, matrix exponentiation |
| \(n \le 10^{18}\) | \(O(\log n)\): binary lifting, fast exponentiation, digit DP |

This table is not a lookup — it's a set of hints. Some \(n \le 10^5\) problems are solved by \(O(n)\) and some by \(O(n \sqrt{n})\). But when you're stuck, "what does the constraint tell me?" is usually enough to break the block.

### Topic-based selection

Pick a technique, then find 5–10 problems where it's the intended solution. Sources:

- The "Practice Problems" sections at the bottom of each CP-Algorithms article.
- CSES Problem Set sections (each is a topic).
- USACO Guide sections (each has 5–15 practice problems rated by difficulty).

### Rating-based selection

Pick a rating band **± 200 above your current rating**, and solve only problems in that band. Below the band, you're not learning. Above the band, you're stuck and frustrated. The band is where growth happens.

For Codeforces, if your rating is \(R\), the band is \([R - 100, R + 200]\). For CSES, the section's "Easy" problems are below the band; the "Hard" problems are above; pick the "Normal" ones.

### Do not do this

- **Don't solve 100 problems at your exact rating.** You need the challenge of \(R + 200\) to grow.
- **Don't random-select from the full problem archive.** This produces a mix of too-easy and too-hard problems, and you don't know which is which until you start.
- **Don't solve 100 problems you already know how to do.** If you can look at a problem and immediately write the solution, it's a speed drill (useful occasionally) but not practice.
- **Don't solve problems you don't understand the statement of.** If reading the problem twice doesn't tell you what's being asked, the problem is above your reading level, not your coding level.

## The Upsolve Loop — the Highest-ROI Habit

The single activity with the highest return on investment is **upsolving**: after a contest (or after failing a problem in practice), **solve the problems you couldn't solve during the contest**. This is where actual skill comes from. The contest is the diagnostic; the upsolve is the treatment.

### The four-step loop

1. **Understand the idea** — read the editorial (or someone else's solution) until you can explain the approach to someone else in plain words. **Do not look at code yet.**
2. **Implement from memory** — close the editorial. Open a blank file. Write the solution. If you can't remember the approach, that's the gap; re-read the editorial's *idea* section, not the code.
3. **Debug and verify** — submit. If WA, debug with edge cases. If TLE, think about complexity.
4. **Read the optimal solution** — after AC, look at the top 5 submissions on Codeforces for that problem. See if there's a cleaner, shorter, or faster way. Often there is.

The critical step is **step 2**. Reading an editorial and then copying the code produces zero skill. Closing the editorial and re-deriving the solution is what transfers the idea into your working memory.

### When to look at the editorial

The "30–60 minutes" rule from most tutorials is too rigid. The right time depends on the problem's difficulty relative to your rating:

| Problem rating vs. your rating | Time before editorial |
|---|---|
| Below your rating | **10 minutes.** You should solve these unaided. If you can't, you have a gap in fundamentals that requires targeted practice, not more time on this problem. |
| At your rating | **20–30 minutes.** This is your learning zone. Struggle is productive, but not for an hour. |
| 100–200 above your rating | **45–60 minutes.** Some struggle is expected; after an hour, look at a hint (not the full solution), then try for another 15 minutes. |
| 300+ above your rating | **10 minutes to read the problem, then skip.** These problems are for later. Save the link and come back when you're ready. |

The point of the time limit is not to be strict but to **avoid grinding on problems you're not equipped to solve**. A problem that's 400 points above your rating teaches you nothing because you can't internalize the solution's idea — it's too far from what you know. Save it, get stronger, come back.

## Stress Testing — the Debugging Method That Actually Works

Once you can implement a solution quickly, the bottleneck becomes **debugging**. The most effective technique is **stress testing**: generate random small inputs, compare your solution against a brute-force reference, and find the smallest input that produces a mismatch.

### The four-component model

Every stress test has four files:

1. **`gen.cpp`** — generates a random input (small \(n\), random values within the problem's constraints).
2. **`brute.cpp`** — a correct but inefficient solution (usually \(O(n^2)\) or \(O(2^n)\), fine for \(n \le 10\)).
3. **`sol.cpp`** — your solution, compiled with `-D_GLIBCXX_DEBUG -fsanitize=address,undefined`.
4. **`stress.sh`** — a shell loop that generates an input, runs both programs, and reports the first mismatch.

### The script

```bash
#!/bin/bash
# stress.sh — run from a directory containing gen, brute, sol

for i in $(seq 1 1000); do
    ./gen > input.txt
    ./brute < input.txt > out_brute.txt
    ./sol   < input.txt > out_sol.txt

    if ! diff -q out_brute.txt out_sol.txt > /dev/null; then
        echo "Mismatch on iteration $i"
        echo "Input:"
        cat input.txt
        echo "Brute:"
        cat out_brute.txt
        echo "Solution:"
        cat out_sol.txt
        exit 1
    fi

    if [ $((i % 100)) -eq 0 ]; then
        echo "Passed $i iterations"
    fi
done
echo "All 1000 iterations passed"
```

Compile the three programs with:

```bash
g++ -std=c++17 -O2 -o gen   gen.cpp
g++ -std=c++17 -O2 -o brute brute.cpp
g++ -std=c++17 -O2 -g -fsanitize=address,undefined -D_GLIBCXX_DEBUG -o sol sol.cpp
```

The `-fsanitize` and `_GLIBCXX_DEBUG` flags make out-of-bounds and undefined behavior fail loudly and immediately, instead of silently producing wrong answers or crashing hours later. They slow the solution by 2–5×, but you're stress testing small inputs anyway, so the slowdown doesn't matter.

### When stress testing helps

- **WA on a test but you don't know why.** Almost every time.
- **Suspected edge-case bug.** The generator can be designed to produce edge cases (empty, `n = 1`, all-equal, already-sorted, adversarial patterns).
- **Comparing two algorithms** — one you wrote and one you trust.

### When stress testing doesn't help

- **TLE.** Stress testing uses small inputs; complexity bugs won't show up. Analyze the algorithm or use the benchmark table from [Algorithmic Complexity](algorithmic-complexity.md).
- **Problem statement misunderstanding.** If your brute force implements the same wrong interpretation as your solution, both will "agree" and you'll never find the bug. Read the statement again carefully before stress testing.
- **Very large inputs.** Generate large test cases separately with a different script; the four-component loop is for small inputs only.

## Virtual Contests and Contest Strategy

A **virtual contest** is a replay of a past Codeforces contest under the original 2-hour time limit. You register as if you were participating live, you can see the standings of the original participants, and you get the same feedback loop: which problems were easy (many solves), which were hard (few), and where you should spend your time.

Virtual contests teach three things that regular practice cannot:

1. **Reading a mixed problem set quickly** — the ability to skim a problem statement and estimate its difficulty is a skill that transfers directly to real contests.
2. **Time allocation under pressure** — you learn what it feels like to be 40 minutes into a contest with 2 WAs and no AC.
3. **The emotional experience of contest day** — code that works at home bugs out at 2 PM on Saturday; you learn to stay calm under that specific stress.

### Contest-day strategy

- **First 5 minutes:** read **all** problems A–D. Do not start coding until you know the whole set. The problems are roughly sorted by difficulty, but not always.
- **Next 20–30 minutes:** solve A and B. These should be near-instant.
- **Next 30–45 minutes:** solve C. This is your learning zone; C is where most people improve.
- **Next 60 minutes:** attempt D. If you can't make progress in 20–30 minutes, **submit a partial** (if the problem allows) or **stop and upsolve**.
- **Last 10 minutes:** re-check your submissions — did you read the output format correctly? Does your solution handle `n = 1`?

The biggest mistake beginners make is **spending the whole contest on C**. If C is genuinely beyond you, submitting nothing on D means you lose the chance to upsolve D later with a clear head. **Solve fewer, learn more.**

### Speed drills

Occasionally (once per week), do a **speed drill**: take a problem you already know how to solve (e.g., a Div. 2 A from last week), and implement it from scratch in **under 10 minutes with zero WA**. The goal is not problem-solving; it's **coding muscle memory** for the STL idioms, the fast I/O template, and the edge-case reflexes. CP is partly a typing contest — if you can't type the solution as fast as you can think it, you lose points on speed alone.

## Rating Calibration

Codeforces ratings are the lingua franca of competitive programming. Here's what they actually mean:

| CF Rating | Name | Can do |
|---|---|---|
| Unrated | — | Solving CSES Introductory problems |
| 800–1000 | Newbie | Solve Div. 2 A reliably; basic loops and conditionals |
| 1000–1200 | Newbie | Solve Div. 2 A–B; string manipulation, simple sorting |
| 1200–1400 | Pupil | Solve Div. 2 B–C; basic prefix sums, two pointers |
| 1400–1600 | Specialist | Solve Div. 2 C; basic DP, BFS/DFS on trees |
| 1600–1800 | Expert | Solve Div. 2 D occasionally; segment trees, unions, basic DP on graphs |
| 1800–2000 | Expert | Solve Div. 2 D reliably; most standard algorithms |
| 2000–2200 | Candidate Master | Solve Div. 1 B; advanced DP, clever implementations |
| 2200–2400 | Master | Solve Div. 1 C; full algorithmic toolkit |
| 2400+ | Grandmaster | Solve Div. 1 D; the top ~1% of competitive programmers |

The **plateau at 1600–1800** is real and well-documented. Most people who get to Pupil reach Specialist quickly, then get stuck for months or years. The reason is almost always that they are doing the wrong kind of practice: solving more Div. 2 C problems they already can solve, rather than deliberately practicing harder techniques.

**Breaking the plateau requires:**

- Moving from "solve problems" to "study techniques" — the D and E problems of Div. 2 require specific algorithms (segment trees with lazy propagation, combinatorial DP on graphs, etc.) that you will not spontaneously invent.
- Upsolving every D and E from every contest you participate in.
- Reading other people's solutions and **understanding them fully** before moving on.
- Accepting that some problems are simply beyond you for now and moving on without shame.

### Cross-platform mapping (approximate)

| Codeforces | AtCoder | CSES difficulty |
|---|---|---|
| 800–1000 | ABC A–B | Introductory |
| 1200–1400 | ABC C–D | Sorting and Searching, easy problems |
| 1400–1600 | ABC D | Sorting and Searching, medium problems |
| 1600–1800 | ABC E | Data Structures |
| 1800–2000 | ABC F | Graph Algorithms, Dynamic Programming |

The mapping is approximate — AtCoder problems are often conceptually harder than their Codeforces counterparts at the same nominal rating, and CSES problems are often simpler than they look. Use this table as a starting point, not a guarantee.

## Judges Compared

| Judge | Best for | Problem quality | Community | When to use |
|---|---|---|---|---|
| **[CSES](https://cses.fi/problemset/)** | Topic-by-topic practice | Excellent — clean statements, clear constraints | Small (it's a static problem set) | Phase 1–4, every phase |
| **[Codeforces](https://codeforces.com/)** | Contests, mixed practice | Very good, occasional weak statements | Largest and most active | Weekly, throughout |
| **[AtCoder](https://atcoder.jp/)** | Well-structured contests | Excellent, especially for learning | Active | Weekly (ABC on Saturdays) |
| **[CodeChef](https://www.codechef.com/)** | Long contests, consistency | Good, sometimes variable | Active | Optional — useful for sustained practice |
| **[SPOJ](https://www.spoj.com/)** | Classical algorithms | Variable — many old problems with poor statements | Slower, older | For specific classical problems |
| **[USACO Guide](https://usaco.guide/)** | Structured learning | Very good, curated | Small but helpful | When you want a "textbook + practice" combination |
| **LeetCode** | Interview prep, **not** CP | Good for interviews, not for CP | Large | Avoid for CP-specific practice |

The single most important judge choice is **Codeforces for contests, CSES for topics**. Everything else is supplementary.

## Common Mistakes That Cost Rating

A checklist of the failures you will actually make:

1. **Not reading the problem statement carefully.** This is the #1 source of WAs across all levels. Before coding, write down: input format, output format, edge cases, and one worked example by hand. **Do not skim.**
2. **Ignoring the constraints.** \(n \le 10^5\) means \(O(n \log n)\) is required. If you start coding \(O(n^2)\), you will TLE, and you'll have wasted 30 minutes.
3. **Coding before designing.** If you open the file before you know what to write, you will code the wrong thing and have to start over. **Design on paper first**, for 5 minutes.
4. **Not testing on the sample.** Always run the sample cases before submitting. Even if you're confident.
5. **Not testing edge cases.** `n = 1`, all-equal input, already-sorted input, negative numbers, empty output. Every one of these has caused a WA for someone.
6. **Skipping upsolve.** Solving a problem in a contest is 30% of the learning; upsolving what you missed is the other 70%.
7. **Looking at the editorial too early.** Reading an editorial after 10 minutes trains you to expect the answer to appear. Reading it after 45 minutes trains you to actually think.
8. **Looking at the editorial too late.** Grinding on a problem 400 points above your rating for 2 hours is not "productive struggle"; it's wasted time.
9. **Not reading other people's code.** After AC, look at the top 5 submissions. There's always something to learn.
10. **Ignoring the "purple problem" phenomenon.** Some problems at 1800–2000 have weird, unimplementable solutions. Skip them; not every problem teaches you something useful.
11. **Skipping implementations.** Reading a solution and understanding it is not the same as implementing it. You need the typing practice.
12. **Practicing only one technique.** Doing 100 prefix-sum problems doesn't make you a better competitive programmer; it makes you a prefix-sum specialist. Rotate topics.
13. **Practicing only contests.** Contests don't teach new techniques; they only test existing ones. If you never read a new technique, you'll never learn one.
14. **Comparing to others too much.** Rating is relative. Your progress is absolute. Track your own problem-solving rate over time.
15. **Not sleeping before contests.** A tired brain loses 200–300 rating points. Real.
16. **Assuming TLE means "code too slow".** TLE can also mean "wrong algorithm" (an \(O(n^2)\) where \(O(n)\) is needed) or "wrong I/O" (`cin` without `sync_with_stdio(false)` on 10^6 inputs). Diagnose before optimizing.
17. **Submitting without compiling locally.** A trivial error — a missing `;`, a typo in a variable name — will get rejected. Compile, run the sample, *then* submit.
18. **Not learning from failure.** If you look at the editorial and then close it, you learned nothing. If you read it, understand it, close it, re-implement it, *then* submit — you learned it.
19. **Overfitting to your own bugs.** If a solution WAs on test 5, don't just patch test 5. Understand what test 5 represents; the bug affects other inputs too.
20. **Forgetting the `-O2` flag locally.** Your code TLEs on the judge but runs in 1 second on your machine. Compile with `-O2` locally to match the judge.

## Recommended Learning Path

A realistic timeline, calibrated for someone who has ~1–2 hours per day:

| Month | Focus |
|---|---|
| 1 | Finish the C++ course, complete CSES "Introductory Problems" |
| 2 | CSES "Sorting and Searching", start Div. 3 virtual contests |
| 3–4 | CSES "Data Structures", weekly Div. 2 and Div. 3 virtuals |
| 5–6 | CSES "Dynamic Programming" and "Graph Algorithms", start real contests |
| 7–12 | Start the "main" CP-Algorithms content (graphs, trees, strings, geometry), participate in every contest you can |

The **"main" CP-Algorithms content** in this course is covered in later articles; this article focused on the prerequisite path. Once you have solid Phase 4 mastery, the graph algorithms, dynamic programming, strings, and geometry sections are within reach.

The single most important habit to build in the first year is **upsolving**. It will feel like a chore. It is the only thing that works.

## Additional Resources

- **[Competitive Programmer's Handbook](https://cses.fi/book/book.pdf)** — free, concise, covers the core topics. The chapters on DP, graph algorithms, and range queries are especially good.
- **[USACO Guide](https://usaco.guide/)** — the best-structured roadmap for competitive programming. Every topic has a difficulty rating, curated problems, and short explanations.
- **[Codeforces EDU](https://codeforces.com/edu/course/2)** — video + text courses on specific techniques, with built-in practice.
- **[CP-Algorithms](https://cp-algorithms.com/)** — this very site. The theory is dense; combine with CSES practice.
- **[AtCoder Editorials](https://atcoder.jp/contests/)** — high-quality, well-illustrated explanations. Often clearer than Codeforces editorials.
- **[CSES Problem Set](https://cses.fi/problemset/)** — the best topic-by-topic practice set. Use this as your primary practice resource.

## Pitfalls Checklist

A summary of the mistakes that cost the most:

1. Practicing without upsolving.
2. Practicing only one technique.
3. Looking at editorials too early or too late.
4. Not stress testing WA solutions.
5. Not reading constraints before coding.
6. Not compiling with `-O2` locally.
7. Not testing edge cases.
8. Not looking at other people's solutions after AC.
9. Grinding on a problem far above your level.
10. Solving easy problems instead of challenging ones.
11. Ignoring the plateau at 1600–1800.
12. Comparing your rating to others instead of your past self.
13. Not participating in real contests.
14. Avoiding virtual contests.
15. Not using the `-D_GLIBCXX_DEBUG` flag while debugging.

## Key Takeaways

- **Two modes of practice: topic-focused (CSES) and contest-mode (Codeforces / AtCoder virtuals).** Both are required; neither alone works.
- **The four phases are mastery criteria, not timeboxes.** Move on when you can solve the phase's problem set in a set time with no WAs, not on a calendar.
- **The upsolve loop is the highest-ROI activity.** After every contest, solve the problems you couldn't solve in the contest, from memory, without looking at code.
- **Stress testing finds WA bugs that no amount of staring finds.** Generate small random inputs, compare against brute force.
- **Virtual contests teach what regular practice cannot:** reading a mixed set under time pressure, allocating time, and staying calm.
- **Rating calibration is real.** 1400 is Specialist; 1600 is Expert; 1800 is the plateau. Know where you are and what you need to reach the next level.
- **Codeforces for contests, CSES for topics.** Use the right tool for the right job.
- **Common mistakes are predictable and avoidable.** Read the statement carefully, test edge cases, compile with `-O2`, and never skip upsolve.

## Practice Problems (one per technique)

A reference set — one representative problem for each fundamental technique. If you can solve all of these unaided, you have a solid Phase 4 foundation.

| Technique | Problem |
|---|---|
| Simulation + overflow | [CSES — Increasing Array](https://cses.fi/problemset/task/1094) |
| Constructive / case analysis | [CSES — Permutations](https://cses.fi/problemset/task/1070) |
| Greedy + sorting | [CSES — Ferris Wheel](https://cses.fi/problemset/task/1090) |
| Two pointers | [CSES — Apartments](https://cses.fi/problemset/task/1084) |
| Sliding window + map | [CSES — Playlist](https://cses.fi/problemset/task/1141) |
| Prefix sums | [CSES — Subarray Sums I](https://cses.fi/problemset/task/1660) |
| Binary search on the answer | [CSES — Factory Machines](https://cses.fi/problemset/task/1620) |
| Sorting + binary search | [CSES — Sum of Two Values](https://cses.fi/problemset/task/1640) |
| Monotonic stack | [CSES — Nearest Smaller Values](https://cses.fi/problemset/task/1645) |
| Priority queue + greedy | [CSES — Room Allocation](https://cses.fi/problemset/task/1164) |
| Order statistics | [CSES — Josephus Problem II](https://cses.fi/problemset/task/1732) |
| DP (1D) | [CSES — Dice Combinations](https://cses.fi/problemset/task/1633) |
| DP (knapsack) | [CSES — Minimizing Coins](https://cses.fi/problemset/task/1634) |
| BFS on a graph | [CSES — Message Route](https://cses.fi/problemset/task/1667) |
| DFS + connected components | [CSES — Building Roads](https://cses.fi/problemset/task/1666) |
| Bipartite check | [CSES — Building Teams](https://cses.fi/problemset/task/1668) |
| Topological sort + DP | [CSES — Longest Flight Route](https://cses.fi/problemset/task/1680) |

## References

- **[Competitive Programmer's Handbook](https://cses.fi/book/book.pdf)** — Antti Laaksonen. The standard reference; chapters 1–5 cover the fundamentals in this article's scope.
- **[USACO Guide](https://usaco.guide/)** — the best-structured roadmap for competitive programming, with per-topic difficulty ratings.
- **[CP-Algorithms — Practice Problems](https://cp-algorithms.com/)** — this site; each article's "Practice Problems" section extends the roadmap above.
- **[Codeforces — Virtual Contests](https://codeforces.com/contests)** — the standard technique for contest-mode practice without waiting for a real contest.
- **[Errichto — How to Practice Competitive Programming](https://www.youtube.com/watch?v=y_ShxWrU4nY)** — a widely-recommended video on the meta-skills described in this article.

## Next Steps

You've now covered the fundamentals of C++ for competitive programming. The **main algorithmic content** — graph algorithms, dynamic programming, strings, geometry, advanced data structures — is in the other sections of this site. Work through them topic by topic, and apply the practice techniques from this article to each.

The single most important habit, repeated once more: **upsolve everything**.