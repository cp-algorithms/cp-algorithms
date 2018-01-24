<!--?title Modification of stack / queue for finding the minimum in $O(1)$ -->

# Modification of stack / queue for finding the minimum in $O(1)$

In this article we will consider three problems: 
first we will modify a stack in a way that allows up to find the smallest element of the stack in $O(1)$, then we will do the same thing with a queue, and finally we will use these data structures to find the minimum in all subsegments of a fixed length in an array in $O(n)$

## Stack modification

We want to make it possible to find the smallest element in a stack in $O(1)$ time, while maintaining the same asymptotic behavior for adding and removing elements from the stack.

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

