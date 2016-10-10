#Treap

Treap is a data structure which are combains binary tree and binary heap (that's why this structure called Treap => tree + heap).

In more strict way, Treap is a data structure that stores pair (X,Y) in a form of binary tree, so that it is a binary search tree by X and binary heap by Y.
Assuming that all X and all Y are different, we find that if a some tree element contains (X0, Y0), then all elements in the left subtree have X < X0 and all elements in right subtree have X > X0, and also left and right subtree have Y < Y0

Treap been proposed Siedel and Aragon in 1989.

##Advantages of such data organisation

In the application, which we are considering (we consider deramidy as a Treap) only X values are the keys (also at same time they are values stored in data structure) and Y values  are called **priorities**. If there were no **priorities**, it would be a normal binary tree by the X and a set of X could be correspond to a lot of trees, some of which are degenerate (eg, in the form of a chain), and therefore are extremely slow (the main operations would be carried out of O(N)).

At the same time, priorities allow you to uniquely specify the tree that will be build (of course, does not depend on the order of addition of components)(this is proved by the corresponding theorem). Now it is obvious that if you choose priorities accident, then, we will achieve the construction of degenerate trees in the average case, which will provide the asymptotic behaviour of O (log N) on average. Hence it is clear that the name of another data structure - a **randomized binary search tree**.

##Operations
So, Treap have next operations:
- **Insert(X,Y)** - operation will take in average O(log N).
  It performs the addition of a new element in the tree. The variant in which Y priority value is not transmitted function and chosen randomly (but bear in mind that it should not coincide with any other Y in the tree).
- **Search (X)** - it has O(log N) mark in average.
  Searches for an item with the specified key X. Implemented in exactly the same way as for an ordinary binary tree.
- **Erase (X)** - in average - O(log N).
  Searches for an item and remove it from the tree.
- **Build (X1, ... Xn)** - O(N).
  Build a tree from a list of values. This operation can be implemented in linear time (assuming that the values of X1, ... Xn sorted),
  but here, this implementation will not be discussed. Here will be used a simplified variant with serial calls of Insert operation.
- **Union (T1, T2)** - in average - O(Mlog(n/m)).
  It merges two trees, on the assumption that all the elements are different (however, this operation can be realized with the same asymptotic behavior, if the merger is necessary to remove duplicate entries).
- **Intersect (T1, T2)** - in average for O(log N).
  Finds the intersection of two trees (ie, their common elements). Here the implementation of this operation will not be considered.

In  addition, due to the fact that the Cartesian tree is a binary searching tree, some operation are applicable to it such as finding the K-th largest element, and, on the contrary, the searching of item number.

##Description of implementations 
In terms of implementation, each element contains the X, Y and pointers to the left (L) and right (R) son.
Split and Merge are required for implementation.

**Split(T,X)** - separates T tree on 2 parts - L and R trees (which are the returned values). L contains all elements with key < X, R contains all elements with larger key (X < key). This operation is performed for the O(logN). The implementation is a quite simple - an obvious recursion.

**Merge(T1, T2)** - combines two subtrees T1 and T2, and returns the new tree. This operation is also performed for O(logN). It works under the assumption that the T1 and T2 have respective order (all X values in first tree **must be smaller** that X values in second). Thus, we need to combine these trees without reordering by Y priorities. To do this, simply choose as the root of the tree, in which Y is fundamentally greater than others and recursively calls itself from the other tree and the corresponding son of selected one.

Now, implementation of **Insert (X, Y)** is pretty obvious. First, we go down on tree (as in a conventional X-binary tree search), but stop at the first element in which the priority value is less than the Y. We found a position where we will insert our element. Now, we call **Split (X)** on the found item (the element along with all of its subtree), and add the result of this function to this element (R and L trees)

Also, implementation of **Erase (X)** is understandable. We get down on a tree (as in a normal binary search tree for X), seeking to delete the item. When item found, we call a Merge operation on his R and L sons, and after just paste this result on a place of this item.

Operation **Build** implement for O(N log N) simply by successive calls of **Insert**.

Finally, the operation **Union (T1, T2)**. Theoretically, its asymptotic behavior of O (M log (N / M)), but in practice it works very well, probably with a very small hidden constant. Suppose, without loss of generality, T1-> Y > T2-> Y, ie, T1 is the root of the root of the result. To get results, we need to combine trees T1-> L, T1-> R and T2 in 2 tree, so that they could make a T1 sons. To do this, call the Split (T2, T1-> X), and we split T2 in the two part - L and R, which are then recursively combine sons T1: Union (T1-> L, L) and Union (T1-> R, R), thus we will build the left and right subtrees of the result.

##Realization

Lets make a realization of all above information:
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

##Supporting of the size of trees

To extend the functionality of the Cartesian tree, it is often necessary for each node to store the number of nodes in its subtree - field `int cnt` in the item structure. For example, it can easily be found for O (log N) K-th largest element of tree, or, conversely, for the same asymptotic behavior found an item number in the sorted list (the implementation of these operations will not be differ from their realization for conventional binary search tree).

When a tree change (add or remove items, etc.) we should vary accordingly cnt and some peaks. We create two functions - **cnt ()** - will return the current value of cnt, or 0 if the node does not exist, and **upd_cnt ()** - function will update the value cnt for this summit, with the condition that for her sons, L and R the cnt has correctly updated. Then, of course, enough to add calls of upd_cnt () function to the end of each functions - insert, erase, split, merge - to keep the correct value of cnt.

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

The key idea is that the key in this case will be **index** of the element inside array. But obviously, we will not keep these key values (otherwise, for example, when inserting an element operation would have had to change the key in O (N) tree tops).

Note that in this case the key to some peaks is actually the number of vertices less than it. 
Also note that the vertexes which are less than current can situated not only in left tree but also in the left subtrees its ancestors. More precisely, the **implicit key** for some vertex t is the number of vertices cnt (t-> l) in the left subtree of this node plus a similar magnitude cnt (p-> l) +1 for each ancestor of the vertex p, provided that t is in the right subtree of p.

Clearly now, how to quickly calculate the implicit key of current peak. As in all operations, we arrive in any top when we goes down  on the tree so we can just accumulate this amount, transferring it to functions. If we go to the left subtree - accumulated amount does not change, and if we go to the right - increases in the cnt (t-> l) +1.

We give new implementations for **Split** and **Merge** functions:

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
Suppose we need to insert an element at position pos. We divide Treap into two halves: a corresponding array [0..pos-1] and array [pos..sz]; it is enough for a split (t, t1, t2, pos). Then we can combine trees with a new vertex t1; it is enough for a merge (t1, t1, new_item) (it is easy to make sure that all the preconditions are made to merge). Finally, we combine the two trees t1 and t2 back into the tree t - calling merge (t, t1, t2).
- **Delete an item**.
It is still easy: just find an item to delete, and then perform the merge to his sons, L and R and put a result of merge operation in a place of t. In fact, the removal of the implicit Cartesian tree is different from the removal of the conventional Cartesian tree.
- **The amount / minimum, etc. on the segment**.
Firstly, create a vertex for each additional item field f in the structure to store the value of the goal function for the vertex of the subtree. This field is easy to maintain - we just need to update cnt (see above)
Secondly, we need to know how to respond to a request for an arbitrary interval [A; B]. 
For this we need to get a part of tree which are corresponded to the segment [A;B]. It is easy to understand that this is enough for first split (t, t1, t2, A), and then split (t2, t2, t3, B-A + 1). As a result, t2 will consist of all the elements in the interval [A; B], and only them. Therefore, response to the request will be in the field f of t2 tree. After the response to the request, tree need to be restored by call a merge (t, t1, t2) and merge (t, t, t3).
- **Addition / painting on the segment**.
Here we act as in the previous paragraph, but instead of the field f will store a field called ‘add’ that will contain a counter value for painting. Before carrying out any operations necessary to set this value correctly - ie, accordingly change t-l->add and t-> r-> add, and clean up it in parent node. In this way we will achieve that in any changes to the tree information will not be lost.
- **Flip on the segment**.
This item is almost similar to the previous - just add the field ‘bool rev’, which is set to true, when you want to make a flip in the subtree of the current node. The setting operation is just little bit primitive - we swapping a sons of this node and set this flag for them.

**Implementation**. Let us give an example for the full realization of the implicit Cartesian tree with the coup on the segment. Here, for each vertex we store field called ‘value’ - the actual value of the item standing in the array at the current position. We also give the implementation of the function ‘output ()’, which displays an array that corresponds to the current state of the implicit Cartesian tree.

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


