---
tags:
  - Puzzle
  - Graphs
  - Search
  - Translated
e_maxx_link: missionaries_and_cannibals
---

# Missionaries and Cannibals (3 and 3)

This file explains the classical **3 Missionaries and 3 Cannibals** river‑crossing puzzle, frames it as a graph/search problem, gives an efficient algorithm to decide solvability (and to produce an optimal sequence of moves), and provides a ready‑to‑compile C++ implementation that finds the shortest solution using BFS.

## Problem statement

There are 3 missionaries and 3 cannibals on the left bank of a river along with a boat that can carry one or two people. The goal is to move everyone to the right bank. At all times on **each bank**, if the number of cannibals present is greater than the number of missionaries (and there is at least one missionary), the cannibals will eat the missionaries — this is an illegal state and must be avoided. The boat cannot cross the river by itself; at least one person must be in the boat to move.

We want to determine whether there is a sequence of boat crossings that transfers all people to the right bank without ever creating an illegal state, and (if so) produce the shortest such sequence of moves.

## Modeling as a graph

Each **state** can be represented by a triple `(M_left, C_left, B)` where:

- `M_left` = number of missionaries on the left bank (0..3)
- `C_left` = number of cannibals on the left bank (0..3)
- `B` = boat side (0 = left, 1 = right)

The numbers on the right bank are implicitly `M_right = 3 - M_left` and `C_right = 3 - C_left`.

A state is **valid** iff for both banks the missionaries are not outnumbered by cannibals (unless there are zero missionaries on that bank):

```
(M_left == 0 || M_left >= C_left) &&
(M_right == 0 || M_right >= C_right)
```

An **edge** (legal move) between states corresponds to moving a boat load of people (1 or 2) from the current boat side to the opposite bank. The boat move can be one of these passenger combinations: `(1M)`, `(2M)`, `(1C)`, `(2C)`, `(1M,1C)`.

When the boat is on the left (`B = 0`), we subtract people from the left counts; when on the right (`B = 1`) we add people back to left counts (i.e. move them leftwards). After applying a move, we check whether the resulting state is valid.

This gives a directed graph of at most `4 * 4 * 2 = 32` states (many are invalid). The problem reduces to finding a path in this graph from the start state `(3,3,0)` to the target state `(0,0,1)`.

## Properties and algorithm

- Because every edge has equal cost (one boat crossing), a **Breadth‑First Search (BFS)** from the start state will find a shortest sequence of moves to the goal (if one exists).
- State space is tiny (≤32 states), so BFS runs in constant time in practice. The complexity in general is `O(|V| + |E|)` where `V` is number of valid states and `E` is number of legal transitions.
- We must *generate* neighbors by trying the allowed passenger combinations and rejecting resulting invalid states.

### Why BFS? (short justification)
BFS explores states by increasing number of crossings. The first time we reach the goal we have the minimum number of crossings. BFS is easy to implement, memory‑safe for this problem, and guaranteed optimal for unweighted edges.

## Implementation (C++)

The following implementation builds and searches the implicit graph on the fly with BFS. It prints the sequence of states and a human‑readable list of moves.

```cpp
#include <bits/stdc++.h>
using namespace std;

struct State {
    int m_left; // 0..3
    int c_left; // 0..3
    int boat;   // 0 = left, 1 = right
    bool operator==(State const &o) const {
        return m_left==o.m_left && c_left==o.c_left && boat==o.boat;
    }
};

struct StateHash {
    size_t operator()(State const &s) const noexcept {
        return s.m_left + 4 * s.c_left + 16 * s.boat; // small perfect-ish hash
    }
};

bool valid(const State &s) {
    int mL = s.m_left, cL = s.c_left;
    int mR = 3 - mL, cR = 3 - cL;
    if (mL < 0 || mL > 3 || cL < 0 || cL > 3) return false;
    if ( (mL > 0 && mL < cL) || (mR > 0 && mR < cR) ) return false;
    return true;
}

vector<pair<State,string>> neighbors(const State &s) {
    // passenger moves: (m, c)
    const vector<pair<int,int>> moves = {{2,0},{0,2},{1,0},{0,1},{1,1}};
    vector<pair<State,string>> res;
    for (auto [dm, dc] : moves) {
        State t = s;
        if (s.boat == 0) {
            // move from left -> right
            t.m_left -= dm;
            t.c_left -= dc;
            t.boat = 1;
        } else {
            // move from right -> left
            t.m_left += dm;
            t.c_left += dc;
            t.boat = 0;
        }
        if (!valid(t)) continue;
        // build a human readable description
        string desc;
        if (dm > 0) desc += to_string(dm) + string("M");
        if (dc > 0) {
            if (!desc.empty()) desc += "+";
            desc += to_string(dc) + string("C");
        }
        if (s.boat == 0)
            desc += " (left -> right)";
        else
            desc += " (right -> left)";
        res.push_back({t, desc});
    }
    return res;
}

int main(){
    State start{3,3,0};
    State goal{0,0,1};

    unordered_map<State, State, StateHash> parent;
    unordered_map<State, string, StateHash> parentMove;
    unordered_set<State, StateHash> visited;
    queue<State> q;

    visited.insert(start);
    q.push(start);

    bool found = false;
    while (!q.empty()) {
        State cur = q.front(); q.pop();
        if (cur == goal) { found = true; break; }
        for (auto &pr : neighbors(cur)) {
            State nxt = pr.first;
            string moveDesc = pr.second;
            if (visited.count(nxt)) continue;
            visited.insert(nxt);
            parent[nxt] = cur;
            parentMove[nxt] = moveDesc;
            q.push(nxt);
        }
    }

    if (!found) {
        cout << "No solution exists.\n";
        return 0;
    }

    // reconstruct path
    vector<State> path;
    vector<string> moves;
    State cur = goal;
    while (!(cur == start)) {
        path.push_back(cur);
        moves.push_back(parentMove[cur]);
        cur = parent[cur];
    }
    path.push_back(start);

    reverse(path.begin(), path.end());
    reverse(moves.begin(), moves.end());

    cout << "Solution in " << moves.size() << " boat crossings:\n";
    for (size_t i = 0; i < moves.size(); ++i) {
        State s = path[i];
        cout << i << ": Left (M=" << s.m_left << ", C=" << s.c_left << ")  |  Boat on " << (s.boat==0?"Left":"Right") << "\n";
        cout << "    Move: " << moves[i] << "\n";
    }
    // print final state
    State last = path.back();
    cout << moves.size() << ": Left (M=" << last.m_left << ", C=" << last.c_left << ")  |  Boat on " << (last.boat==0?"Left":"Right") << "\n";

    return 0;
}
```

## Example solution (conceptual)

One shortest sequence of moves (6 crossings) is:

1. Send 2 cannibals from left to right. (Left: M=3,C=1 | Right: M=0,C=2)
2. Send 1 cannibal back. (Left: M=3,C=2 | Right: M=0,C=1)
3. Send 2 missionaries to right. (Left: M=1,C=2 | Right: M=2,C=1)
4. Send 1 missionary and 1 cannibal back. (Left: M=2,C=3 | Right: M=1,C=0)
5. Send 2 missionaries to right. (Left: M=0,C=3 | Right: M=3,C=0)
6. Send 2 cannibals to right. (Left: M=0,C=1 | Right: M=3,C=2)

This description is conceptual; the provided program will print a correct shortest move list and exact states.

## Remarks and generalizations

- The same modeling works for different counts (e.g., `n` missionaries and `n` cannibals) and different boat capacities — replace constants and validate states accordingly. However the state space grows as `O(n^2)` (times 2 for the boat side), and the branching depends on allowed boat loads.
- For larger instances, BFS still finds the shortest solution but may need more memory; other techniques (bidirectional BFS, A*) can be used if needed.


---

*Prepared in the style of algorithmic graph puzzles: model the puzzle as states and transitions, then run a shortest-path search (BFS).*

