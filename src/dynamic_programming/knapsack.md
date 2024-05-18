---
tags:
  - Original
---

# Knapsack DP
Prerequisite knowledge: [Introduction to Dynamic Programming](https://cp-algorithms.com/dynamic_programming/intro-to-dp.html)

## Introduction
Before we talk about what "knapsack dp" is, let's look at the following example:

### [[USACO07 Dec] Charm Bracelet](https://www.acmicpc.net/problem/6144) 
There are $n$ distinguishable items and a knapsack of capacity $W$. Each item has 2 attributes, weight ($w_{i}$) and value ($v_{i}$). 
It is required to select a number of items to put into the knapsack such that the total weight does not exceed the capacity and the total value is maximized.

In the above example, since each object has only two possible states (taken or not taken),
correspoding to binary 0 and 1, this type of problem is called "0-1 knapsack problem".

## 0-1 Knapsack

### Explaination

The known conditions in the example are; the weight of $i^{th}$ item $w_{i}$, value of $i^{th}$ item $v_{i}$, and the total capacity of the knapsack {W}.

Set the dp state $f_{i, j}$ be the maximum total value the knapsack can carry with capacity $j$, when only the first $i$ items are considered.

Consider the state transfer. Assuming that all states of first $i-1$ items have been processed, for the $i^{th}$ item;
- When it is not put into the knapsack, the remaining capacity remains unchanged and total value does not change. Therefore, the maximum value in this case is $f_{i-1, j}$
- When it is put into the knapsack, the remaining capacity decreases by $w_{i}$ and the total value increases by $v_{i}$,
so the maximum value in this case is $f_{i-1, j-w_i} + v_i$

From this we can derive the state transfer equation:

$$f_{i, j} = \max(f_{i-1, j}, f_{i-1, j-w_i} + v_i)$$

Further, as $f_{i}$ is only dependent on $f_{i-1}$, we can remove the first dimension. We obtain:

$$f_{j} = \max(f_{j}, f_{j-w_i} + v_i)$$

**It is important to remember and understand this transfer equation, because most of the transfer equations for knapsack problems are derived on this basis.**

### Implementation

Another thing to note is that it is easy to write **erroneous code** like this

```.c++
for (int i = 1; i <= n; i++)
  for (int j = 0; j <= W-w[i]; j++)
    f[j + w[i]] = max(f[j + w[i]], f[j] + v[i]);
```

What is wrong with this code? The enumeration order is wrong.

Observing the code carefully, we can find that: for the currently processed item $i$ and the current state $f_{i,j}$, 
when $j\geqslant w_{i}$, $f_{i,j}$ will be affected by $f_{i,j-w_{i}}$. 
This is equivalent to being able to be put item $i$ into the backpack multiple times, which is not consistent with the question.
(In fact, this is exactly the solution to the complete knapsack problem)

To avoid this, we can change the order of enumeration from $W$ to $w_{i}$, so that the above error won't occour, because $f_{i, j}$ is always updated before $f_{i, j-w_i}$

Therefore, the actual code is

```.c++
for (int i = 1; i <= n; i++)
  for (int j = W; j >= w[i]; j--)
    f[j] = max(f[j], f[j - w[i]] + v[i]);
```
