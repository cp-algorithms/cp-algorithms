<!--?title Modification of stack / queue for finding the minimum in $O(1)$ -->

# Modification of stack / queue for finding the minimum in $O(1)$

In this article we will consider three problems: 
first we will modify a stack in a way that allows up to find the smallest element of the stack in $O(1)$, then we will do the same thing with a queue, and finally we will use these data structures to find the minimum in all subsegments of a fixed length in an array in $O(n)$

## Stack modification

We want to make it possible to find the smallest element in a stack in $O(1)$ time, while maintaining the same asymptotic behavior for adding and removing elements from the stack.
Quick reminder, on a stack we only add and remove elements from the back.

To do this, we will no only store the elements in the stack, but we will store each one in pairs: the element itself and the minimum in the stack starting from this element and below.

```cpp
stack<pair<int, int>> st;
```

It is clear that finding the minimum in the whole stack consists of only taking the value of `stack.top().second`.

It is also obvious that adding or removing a new element to the stack can be done in constant time.

Implementation:

* Adding an element:
```cpp
int new_min = st.empty() ? new_elem : min(new_elem, st.top().second);
st.push({new_elem, new_min});
```

* Extracting / removing an element:
```cpp
int result = st.top().first;
st.pop();
```

* Finding the minimum:
```cpp
int minimum = st.top().second;
```

## Queue modification (method 1)

Now we want to achieve the same operations with a queue, i.e. we want to add elements at the end and remove them from the front.

Here we consider a simple method for modifying a queue.
It has a big disadvantage though, because the modified queue will actually not store all elements.

The key idea is to only store the items in the queue that are needed to determine the minimum.
Namely we will keep the queue in nondecreasing order (i.e. the smallest value will be stored in the head), and of course not in any arbitrary way, the actual minimum has to be always contained in the queue.
This way the smallest element will always be in the head of the queue.
Before adding a new element to the queue, it is enough to make a "cut":
we will remove all trailing elements of the queue that are larger than the new element, and afterwards add the new element to the queue. 
This way we don't break the order of the queue, and we will also not loose the current minimum if it is at any subsequent step a minimum. 
When we want to extract an element from the head, it actually might not be there (because we removed it previously while adding a smaller element). 
Therefore when deleting an element from a queue we need to know the value of the element.
If the head of the queue has the same value, we can safely remove it, otherwise we do nothing.

Consider the implementations of the above operations:

```cpp
deque<int> q;
```

* Finding the minimum:
k``cpp
int minimum = q.front();
```

* Adding an element:
```cpp
while (!q.empty() && q.back() > new_element)
    q.pop_back();
q.push_back(new_element);
```

* Extracting an element:
```cpp
if (!q.empty() && q.front() == remove_element)
    q.pop_front();
```

It is clear that on average all these operation only take $O(1)$ time (because every element can only be pushed and popped once).
