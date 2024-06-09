---
tags:
  - Original
---

# Knapsack problem
Prerequisite knowledge: [Introduction to Dynamic Programming](https://cp-algorithms.com/dynamic_programming/intro-to-dp.html)

## Introduction
Consider the following example:

### [[USACO07 Dec] Charm Bracelet](https://www.acmicpc.net/problem/6144) 
There are $n$ distinct items and a knapsack of capacity $W$. Each item has 2 attributes, weight ($w_{i}$) and value ($v_{i}$). 
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

## Complete Knapsack

The complete knapsack model is similar to the 0-1 knapsack, the only difference from the 0-1 knapsack is that an item can be selected an unlimited number of times instead of only once.

We can refer to the idea of 0-1 knapsack to define the state: $f_{i, j}$, the maximum value the knapsack can obtain using the first $i$ items with maximum capacity $j$.

It should be noted that although the state definition is similar to that of a 0-1 knapsack, its state transfer equation is different from that of a 0-1 knapsack.

### Explaination

The trivial approach is, for the first $i$ items, enumerate how many each item is to be taken. The time complexity of this is $O(n^3)$.

The state transfer function follows:

$$f_{i, j} = \max\limits_{k=0}^{\infty}(f_{i-1, j-k\cdot w_i} + k\cdot v_i)$$

It can be found that for $f_{i, j}$, it can just transfer through $f_{i, j-w_i}$. The state transfer equation becomes:

$$f_{i, j} = \max(f_{i-1, j},f_{i, j-w_i} + v_i)$$\

The reason this works is that when we transfer like this, $f_{i, j-w_i}$ has already been updated by $f_{i, j-2\cdot w_i}$ and so on.

Similar to the 0-1 knapsack, we can remove the first dimension to optimize the space complexity.

## Multiple Knapsack

Multiple knapsack is also a variant of 0-1 knapsack. The main difference is that there are $k_i$ of each item instead of just 1.

### Explaination

A very simple idea is: "choose each item $k_i$ times" is equivalent to "$k_i$ of the same item is selected one by one". Thus converting it to a 0-1 knapsack model, which can be described by the transition function:

$$f_{i, j} = \max_{k=0}^{k_i}(f_{i-1,j-k\cdot w_i} + k\cdot v_i)$$

The time complexity of this process is $O(W\sum\limits_{i=1}^{n}k_i)$

### Binary Grouping Optimization

We still consider converting the multiple knapsack model into a 0-1 knapsack model for optimization. The time complexity $O(Wn)$ can not be further optimized, so we focus on $O(\sum k_i)$.

Let $A_{i, j}$ denote the $j^{th}$ item split from the $i^{th}$ item. In the trivial approach discussed above, $A_{i, j}$ represents the same item for all $j \leq k_i$. The main reason for our low efficiency is that we are doing a lot of repetetive work. For example, consider selecting $A_{i, 1} and A_{i, 2}$, and selecting $A_{i, 3} and A_{i, 3}$. These two situations are completely equivalent. Thus optimizing the spiltting method will greatly reduces the time complexity.

The grouping is made more effiecent by using binary grouping.

Specifically, $A_{i, j}$ holds $2^j$ individual items ($j\in[0,\lfloor \log_2(k_i+1)\rfloor-1]$).If $k_i + 1$ is not an integer power of $2$, another bundle of size $k_i-2^{\lfloor \log_2(k_i+1)\rfloor-1}$ is used to make up for it.

Through the above splitting method, any sum of terms $\leq k_i$ will can be obtained by selecting a few $A_{i, j}$'s. After splitting each item in the described way, it is sufficient to use 0-1 knapsack method to solve it.

### Implementation

```c++
index = 0;
for (int i = 1; i <= n; i++) {
  int c = 1, p, h, k;
  cin >> p >> h >> k;
  while (k > c) {
    k -= c;
    list[++index].w = c * p;
    list[index].v = c * h;
    c *= 2;
  }
  list[++index].w = p * k;
  list[index].v = h * k;
}
```

## Mixed Knapsack

The mixed knapsack problem involves a combination of the three problems described above. That is, some items can only be taken once, some can be taken infinitely, and some can be taken atmost $k$ times.

The problem may seem daunting, but as long as you understand the core ideas of the previous knapsack problems and combine them together, you can do it. The pseudo code for the solution is as:

```c++
for (each item) {
  if (0-1 knapsack)
    Apply 0-1 knapsack code;
  else if (complete knapsack)
    Apply complete knapsack code;
  else if (multiple knapsack)
    Apply multiple knapsack code;
}
```

## Practise Problems

- [Atcoder: Knapsack-1](https://atcoder.jp/contests/dp/tasks/dp_d)
- [Atcoder: Knapsack-2](https://atcoder.jp/contests/dp/tasks/dp_e)
- [DMOJ: Knapsack-3](https://dmoj.ca/problem/knapsack)
- [DMOJ: Knapsack-4](https://dmoj.ca/problem/knapsack4)
