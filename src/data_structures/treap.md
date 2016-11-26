<!--?title Treap -->
# Treap (Cartesian tree)

Treap is a data structure which combines binary tree and binary heap (hence the name: tree + heap => Treap).

More specifically, treap is a data structure that stores pairs (X, Y) in a binary tree in such a way that it is a binary search tree by X and a binary heap by Y.
Assuming that all X and all Y are different, we can see that if some node of the tree contains values ($X_0$, $Y_0$), all nodes in the left subtree have $X < X_0$, all nodes in the right subtree have $X > X_0$, and all nodes in both left and right subtrees have $Y < Y_0$.

Treaps have been proposed by Siedel and Aragon in 1989.

## Advantages of such data organisation

In such implementation X values are the keys (and at same time the values stored in the treap), and Y values are called **priorities**. Without priorities, the treap would be a regular binary search tree by X, and one set of X values could correspond to a lot of different trees, some of them degenerate (for example, in the form of a linked list), and therefore extremely slow (the main operations would have $O(N)$ complexity).

At the same time, **priorities** allow to **uniquely** specify the tree that will be constructed (of course, it does not depend on the order in which values are added), which can be proven using corresponding theorem. Obviously, if you **choose the priorities randomly**, you will get non-degenerate trees on average, which will ensure $O(\log N)$ complexity for the main operations. Hence another name of this data structure - **randomized binary search tree**.

## Operations

A treap provides the following operations:

- **Insert(X,Y)** in $O(\log N)$.  
  Adds a new node to the tree. A variant is possible in priority Y is not passed as as a parameter but is chosen randomly instead (while ensuring that it's different from all other priorities in the tree).
- **Search (X)** in $O(\log N)$.  
  Looks for a node with the specified key value X. The implementation is the same as for an ordinary binary tree.
- **Erase (X)** in $O(\log N)$.  
  Looks for a node with the specified key value X and removes it from the tree.
- **Build ($X_1$, ..., $X_N$)** in $O(N)$.  
  Builds a tree from a list of values. This can be done in linear time (assuming that $X_1, ..., X_N$ are sorted), but we will not discuss this implementation here. We will use the simplest variant with serial calls of **Insert** operation, which has $O(N \log N)$ complexity.
- **Union ($T_1$, $T_2$)** in $O(M \log (N/M))$.  
  Merges two trees, assuming that all the elements are different. An implementation with the same asymptotic behavior is possible if duplicate elements should be removed during merge.
- **Intersect ($T_1$, $T_2$)** in $O(M \log (N/M))$.  
  Finds the intersection of two trees (i.e. their common elements). We will not consider the implementation of this operation here.

In  addition, due to the fact that a treap is a binary search tree, it can implement other operations, such as finding the K-th largest element or finding the index of an element.

## Implementation Description
In terms of implementation, each element contains the X, Y and pointers to the left (L) and right (R) son.
**Split** and **Merge** operations are required for implementation.

**Split(T,X)** - separates T tree on 2 parts - L and R trees (which are the returned values from operation). L contains all elements with key Xl < X, R contains all elements with key Xr >X. This operation is performed for the O (log N). The implementation is a quite simple - an obvious recursion.

**Merge(T1, T2)** - combines two subtrees T1 and T2, and returns the new tree. This operation is also performed for O (log N). It works under the assumption that the T1 and T2 have respective order (all X values in first tree **must be smaller** than X values in second tree). Thus, we need to combine these trees without reordering them by Y priorities. To do this, simply choose as the root a tree with the highest Y priority, and recursively calls itself from the other tree and the corresponding son of selected one.

Now, implementation of **Insert (X, Y)** is pretty obvious. First, we go down on the tree (as in a conventional binary tree search by X), but we should stop at the first element in which the priority value is less than the Y. We found a position where we will insert our element. Now, we call **Split (X)** on the found item (on the element along with all of its subtree). As the result of **Split** we will get L and R sons for new element which we are trying to add.

Also, implementation of **Erase (X)** is more understandable now. We go down on a tree (as in a normal binary search tree by X), seeking to delete the item during the way. When item found, we call a **Merge** operation on it sons - R and L trees, and after -paste result of Merge on a place of this item.

**Build** operation we will implement in a way with O(N log N) asymptotic by simply calling of **Insert** operation.

Finally, the **Union (T1, T2)** operation. Theoretically, its asymptotic behavior of O (M log (N / M)), but in practice it works very well, probably with a very small hidden constant. Suppose, without loss of generality, T1-> Y > T2-> Y, ie, T1 is the root of the root of the result. To get results, we need to combine trees T1-> L, T1-> R and T2 in 2 tree, so that they could be a sons of T1 tree. To do this, call the Split (T2, T1-> X), and we split T2 in the two part - L and R, which are then recursively combine sons of T1: Union (T1-> L, L) and Union (T1-> R, R), thus we will build the Left and Right subtrees of the result.

##Implementation

Let's make a realization, described above:
```
struct item {
	int key, prior;
	item * l, * r;
	item() { }
	item (int key, int prior) : key(key), prior(prior), l(NULL), r(NULL) { }
};
typedef item * pitem;

void split (pitem t, int key, pitem & l, pitem & r) {
	if (!t)
		l = r = NULL;
	else if (key < t->key)
		split (t->l, key, l, t->l),  r = t;
	else
		split (t->r, key, t->r, r),  l = t;
}

void insert (pitem & t, pitem it) {
	if (!t)
		t = it;
	else if (it->prior > t->prior)
		split (t, it->key, it->l, it->r),  t = it;
	else
		insert (it->key < t->key ? t->l : t->r, it);
}

void merge (pitem & t, pitem l, pitem r) {
	if (!l || !r)
		t = l ? l : r;
	else if (l->prior > r->prior)
		merge (l->r, l->r, r),  t = l;
	else
		merge (r->l, l, r->l),  t = r;
}

void erase (pitem & t, int key) {
	if (t->key == key)
		merge (t, t->l, t->r);
	else
		erase (key < t->key ? t->l : t->r, key);
}

pitem unite (pitem l, pitem r) {
	if (!l || !r)  return l ? l : r;
	if (l->prior < r->prior)  swap (l, r);
	pitem lt, rt;
	split (r, l->key, lt, rt);
	l->l = unite (l->l, lt);
	l->r = unite (l->r, rt);
	return l;
}
```

##Supporting of the size of subtrees

To extend the functionality of the Cartesian tree, it is often necessary for each node to store the number of nodes in its subtree - field `int cnt` in the item structure. For example, K-th largest element of tree can easily be found for O (log N), or, conversely, for the same asymptotic behavior item number can be found in the sorted list (the implementation of these operations will not be differ from their realization for conventional binary search tree).

When a tree changes (add or remove items, etc.), _cnt_ should be also updated accordingly for vertices. For that purposes we should create two functions - `cnt ()` - it will return the current value of _cnt_, or 0 if the node does not exist, and `upd_cnt ()`  - it will update the value _cnt_ for this vertex, with the condition - for her sons, L and R, the `cnt` has correctly updated. Then, of course, enough to add calls of `upd_cnt ()` to the end of each functions - insert, erase, split, merge - to keep the correct value of _cnt_.

```
int cnt (pitem t) {
	return t ? t->cnt : 0;
}

void upd_cnt (pitem t) {
	if (t)
		t->cnt = 1 + cnt(t->l) + cnt (t->r);
}
```

## Build a Treap for a O (N) in offline mode

TODO

## Implicit Treaps

Implicit Treap - is a simple modification of the conventional Cartesian tree, which, however, is a very powerful data structure. In fact, the implicit Treap can be perceived as an array, which can be implemented over the following procedures (all in O (log N) in the online mode):

- Inserting an element in the array in any position
- Removal of any element
- The amount of minimum / maximum on an arbitrary interval, etc.
- Addition, painting on a segment
- Coup (permutation of the elements in reverse order) in the interval

The key idea is that the key in this case will be **index** of the element inside array. But obviously, we will not store these _key_ values (otherwise, for example, when inserting an element operation would have had to change the key in O (N) vertices of the tree ).

Note that in this case the key to some vertices is actually the number of vertices less than it. 
Also note that the vertexes which are less than current can situated not only in left tree but also in the left subtrees in its ancestors. More precisely, the **implicit key** for some vertex t is the number of vertices cnt (T-> L) in the left subtree of this node plus a similar magnitude cnt (P-> L) +1 for each ancestor of the vertex P, provided that T is in the right subtree of P.

Now is more clearly how to quickly calculate the implicit key of current vertex. As in all operations, we arrive in any top when we goes down  on the tree so we can just accumulate this amount and transfer it to functions. If we go to the left subtree - accumulated amount does not change, and if we go to the right - it increases in the cnt (T-> L) +1.

We give new implementations for **Split** and **Merge** operations:

```
void merge (pitem & t, pitem l, pitem r) {
	if (!l || !r)
		t = l ? l : r;
	else if (l->prior > r->prior)
		merge (l->r, l->r, r),  t = l;
	else
		merge (r->l, l, r->l),  t = r;
	upd_cnt (t);
}

void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
	if (!t)
		return void( l = r = 0 );
	int cur_key = add + cnt(t->l); //implicit key
	if (key <= cur_key)
		split (t->l, l, t->l, key, add),  r = t;
	else
		split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
	upd_cnt (t);
}
```

Now we turn to the implementation of various additional operations on the implicit Cartesian trees:

- **Insert element**.
Suppose we need to insert an element at position _pos_. We divide Treap into two halves: a corresponding array [0..pos-1] and array [pos..sz]; it is enough for a split (T, T1, T2, pos). Then we can combine trees with a new vertex T1; it is enough for a merge (T1, T1, new_item) (it is easy to make sure that all of the preconditions are done). Finally, we combine the two trees T1 and T2 back into T - by a call of merge (T, T1, T2).
- **Delete an item**.
It is still easy: just find an item to delete, and then perform the merge to it sons, L and R,  and put a result of merge operation in a place of T. In fact, there is no difference between the removal of the implicit Cartesian tree and removal of the conventional Cartesian tree.
- **The amount / minimum**, etc. on the segment.
Firstly, create a vertex for each additional item field F in the structure to store the value of the goal function for this peek’s subtree. This field is easy to maintain - same operation like during the work with _cnt_ (we need 2 functions for getting and settings this value and we should update depended function - see above).
Secondly, we need to know how to respond to a request for an arbitrary interval [A; B]. 
For this we need to get a part of tree which are corresponded to the segment [A;B]. It is easy to understand that this is enough for first split(T, T1, T2, A), and then split (T2, T2, T3, B-A+ 1). As a result, T2 will consist of all the elements in the interval [A; B], and only of them. Therefore, response to the request will be in the field F of T2 tree. After the response to the request, tree need to be restored by call of a merge (T, T1, T2) and merge (T, T, T3).
- **Addition / painting on the segment**.
Here we act as in the previous paragraph, but instead of the field F will store a field called _add_ that will contain accumulation value for painting. Before carrying out any operations necessary to set this value correctly - ie, accordingly change T->L->add and T-> R-> add, and clean up _add_ in parent node. In this way we will achieve that after any changes to the tree all information will not be lost.
- **Flip on the segment**.
This item is almost similar to the previous - just add the field ‘bool rev’, which will be setted to true, when you want to make a flip in the subtree of the current node. The initialize operation is just little bit complicated - we swapping a sons of this node and set this flag for them.

**Implementation**. Let us give an example for the full realization of the implicit Cartesian tree with the coup on the segment. Here, for each vertex we store field called _value_ - the actual value of the item standing in the array at the current position. We also give the implementation of the function ‘output ()’, which displays an array that corresponds to the current state of the implicit Cartesian tree.

```
typedef struct item * pitem;
struct item {
	int prior, value, cnt;
	bool rev;
	pitem l, r;
};

int cnt (pitem it) {
	return it ? it->cnt : 0;
}

void upd_cnt (pitem it) {
	if (it)
		it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void push (pitem it) {
	if (it && it->rev) {
		it->rev = false;
		swap (it->l, it->r);
		if (it->l)  it->l->rev ^= true;
		if (it->r)  it->r->rev ^= true;
	}
}

void merge (pitem & t, pitem l, pitem r) {
	push (l);
	push (r);
	if (!l || !r)
		t = l ? l : r;
	else if (l->prior > r->prior)
		merge (l->r, l->r, r),  t = l;
	else
		merge (r->l, l, r->l),  t = r;
	upd_cnt (t);
}

void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
	if (!t)
		return void( l = r = 0 );
	push (t);
	int cur_key = add + cnt(t->l);
	if (key <= cur_key)
		split (t->l, l, t->l, key, add),  r = t;
	else
		split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
	upd_cnt (t);
}

void reverse (pitem t, int l, int r) {
	pitem t1, t2, t3;
	split (t, t1, t2, l);
	split (t2, t2, t3, r-l+1);
	t2->rev ^= true;
	merge (t, t1, t2);
	merge (t, t, t3);
}

void output (pitem t) {
	if (!t)  return;
	push (t);
	output (t->l);
	printf ("%d ", t->value);
	output (t->r);
}
```


