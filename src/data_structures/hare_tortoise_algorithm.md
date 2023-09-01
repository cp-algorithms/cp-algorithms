
---
tags:
  - Translated
e_maxx_link: hare_tortoise_algorithm
---

# Floyd's Linked List Cycle Finding Algorithm

Given a linked list where the starting point of that linked list is denoted by `head`, and there may or may not be a cycle present. For instance:

![[tortoise_hare_algo.png]]

Here we need to find out the point `C`, i.e the starting point of the cycle.

## Proposed algorithm
The algorithm is called `Floyd’s Cycle Algorithm or Tortoise n Hare algorithm`.
In order to figure out the starting point of the cycle, we need to figure out of the the cycle even exists or not.
So, it involved two steps:
1. Figure out the presence of the cycle.
2. Find out the starting point of the cycle.

### Step 1: Presence of the cycle
1. Take two pointers $slow$ and $fast$.
2. Both of them will point to head of the linked list initially.
3. $slow$ will move one step at a time.
4. $fast$ will move two steps at a time. (twice as speed as $slow$ pointer).
5. check if at any point they point to the same node before any one(or both) reach null.
6. if they point to any same node at any point of their journey, it would indicate that the cycle indeed exists in the linked list.
7. if we get null, it would indicate that the linked list has no cycle.

![[tortouse_hare_cycle_found.png]]

Now, that we have figured out that there is a cycle present in the linked list, for the next step we need to find out the starting point of cycle, i.e., `C.
### Step 2: Starting point of the cycle
1. Reset the $slow$ pointer to the `head` of the linked list.
2. Move both pointers one step at a time.
3. The point they will meet at will be the starting point of the cycle.

```java
// Presence of cycle
public boolean hasCycle(ListNode head) {
    ListNode slow = head;
    ListNode fast = head;

    while(slow !=null && fast != null && fast.next != null){
        slow = slow.next;
        fast = fast.next.next;
        if(slow==fast){
            return true;
        }
    }

    return false;
}
```

```java
// Assuming there is a cycle present and slow and fast are point to their meeting point
slow = head;
while(slow!=fast){
	slow = slow.next;
	fast = fast.next;
}

return slow; // the starting point of the cycle.
```

## Why does it work

### Step 1: Presence of the cycle
Since the pointer $fast$ is moving with twice as speed as $slow$, we can say that at any point of time, $fast$ would have covered twice as much distance as $slow$.
We can also deduce that the difference between the distance covered by both of these pointers is increasing by $1$. 
```
slow: 0 --> 1 --> 2 --> 3 --> 4 (distance covered)
fast: 0 --> 2 --> 4 --> 6 --> 8 (distance covered)
diff: 0 --> 1 --> 2 --> 3 --> 4 (difference between distance covered by both pointers)
```

So, if we assume that Length of cycle is: $L$, we can also say that there will be a point when the difference between $slow$ and $fast$ pointer will grow and reach $NXL$ where $N>0$ .

When both $slow$ and $fast$ are within cycle, and the difference between their covered lengths is $NXL$, then they are bound to point at same node, indicating the presence of cycle.

### Step 2: Starting point of the cycle

Lets try to calculate the distance covered by both of the pointers till they point they met within the cycle.

distance covered by slow = $slowDist$
distance covered by fast  = $fastDist$

$slowDist = a + xL + b$            $x\ge0$
$fastDist = a + yL + b$            $y\ge0$

![[tortoise_hare_proof.png]]

$a + yL + b = 2(a + xL + b)$

$a=(y-2x)L-b$   where $y-2x$ is an integer.

We know that $fast$ has already covered $b$, so, we can say that the distance $a$ is same as some multiple of length of the cycle.

# Problems:
- [Linked List Cycle (EASY)](https://leetcode.com/problems/linked-list-cycle/)
- [Find the Duplicate Number (Medium)](https://leetcode.com/problems/find-the-duplicate-number/)

