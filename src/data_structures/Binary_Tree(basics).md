#Binary Tree

Trees: Unlike Arrays, Linked Lists, Stack and queues, which are linear data structures, trees are hierarchical data structures.
Tree Vocabulary: The topmost node is called root of the tree. The elements that are directly under an element are called its children. The element directly above something is called its parent. For example, ‘a’ is a child of ‘f’, and ‘f’ is the parent of ‘a’. Finally, elements with no children are called leaves.

          tree
          ----
           j    <-- root
         /   \
        f      k  
      /   \      \
     a     h      z    <-- leaves 


- Why Trees?
    1. One reason to use trees might be because you want to store information that naturally forms a hierarchy. For example, the file system on a computer:

              file system
              -----------
                   /    <-- root
                /      \
              ...       home
                    /          \
                 ugrad        course
                  /       /      |     \
                ...      cs101  cs112  cs113  

    2. Trees (with some ordering e.g., BST) provide moderate access/search (quicker than Linked List and slower than arrays).
    3. Trees provide moderate insertion/deletion (quicker than Arrays and slower than Unordered Linked Lists).
    4. Like Linked Lists and unlike Arrays, Trees don’t have an upper limit on number of nodes as nodes are linked using pointers.

- Main applications of trees include:
    1. Manipulate hierarchical data.
    2. Make information easy to search (see tree traversal).
    3. Manipulate sorted lists of data.
    4. As a workflow for compositing digital images for visual effects.
    5. Router algorithms
    6. Form of a multi-stage decision-making (see business chess).




- Binary Tree: A tree whose elements have at most 2 children is called a binary tree. Since each element in a binary tree can have only 2 children, we typically name them the left and right child.

  Binary Tree Representation in C: A tree is represented by a pointer to the topmost node in tree. If the tree is empty, then value of root is NULL.
  A Tree node contains following parts.
  1. Data
  2. Pointer to left child
  3. Pointer to right child

  In C, we can represent a tree node using structures. Below is an example of a tree node with an integer data.

- Sample Code: 

                    struct node  
                    { 
                      int data; 
                      struct node *left; 
                      struct node *right; 
                    };

  First Simple Tree in C
  Let us create a simple tree with 4 nodes in C. The created tree would be as following.

              tree
              ----
               1    <-- root
             /   \
            2     3  
           /   
          4

  

- Sample code:


                #include<stdio.h> 
                #include<stdlib.h> 
                struct node  
                { 
                    int data; 
                    struct node *left; 
                    struct node *right; 
                }; 
                  
                /* newNode() allocates a new node with the given data and NULL left and  
                right pointers. */
                struct node* newNode(int data) 
                { 
                // Allocate memory for new node  
                struct node* node = (struct node*)malloc(sizeof(struct node)); 
                  
                // Assign data to this node 
                node->data = data; 
                  
                // Initialize left and right children as NULL 
                node->left = NULL; 
                node->right = NULL; 
                return(node); 
                } 
                  
                  
                int main() 
                { 
                /*create root*/
                struct node *root = newNode(1);  
                /* following is the tree after above statement  
                  
                        1 
                    / \ 
                    NULL NULL  
                */
                  
                  
                root->left     = newNode(2); 
                root->right     = newNode(3); 
                /* 2 and 3 become left and right children of 1 
                        1 
                        / \ 
                        2     3 
                    / \ / \ 
                    NULL NULL NULL NULL 
                */
                  
                  
                root->left->left = newNode(4); 
                /* 4 becomes left child of 2 
                        1 
                    /     \ 
                    2         3 
                    / \     / \ 
                4 NULL NULL NULL 
                / \ 
                NULL NULL 
                */
                  
                getchar(); 
                return 0; 
                } 


- Summary: Tree is a hierarchical data structure. Main uses of trees include maintaining hierarchical data, providing moderate access and insert/delete operations. Binary trees are special cases of tree where every node has at most two children.

##Properties of Binary Tree

1) The maximum number of nodes at level ‘l’ of a binary tree is 2l.
Here level is number of nodes on path from root to the node (including root and node). Level of root is 0.
This can be proved by induction.
For root, l = 0, number of nodes = 20 = 1
Assume that maximum number of nodes on level ‘l’ is 2l
Since in Binary tree every node has at most 2 children, next level would have twice nodes, i.e. 2 * 2l

 
2) Maximum number of nodes in a binary tree of height ‘h’ is 2h – 1.
Here height of a tree is maximum number of nodes on root to leaf path. Height of a tree with single node is considered as 1.
This result can be derived from point 2 above. A tree has maximum nodes if all levels have maximum nodes. So maximum number of nodes in a binary tree of height h is 1 + 2 + 4 + .. + 2h-1. This is a simple geometric series with h terms and sum of this series is 2h – 1.
In some books, height of the root is considered as 0. In this convention, the above formula becomes 2h+1 – 1

 
3) In a Binary Tree with N nodes, minimum possible height or minimum number of levels is  ? Log2(N+1) ?  
This can be directly derived from point 2 above. If we consider the convention where height of a leaf node is considered as 0, then above formula for minimum possible height becomes   ? Log2(N+1) ? – 1

 
4) A Binary Tree with L leaves has at least   ? Log2L ? + 1   levels
A Binary tree has maximum number of leaves (and minimum number of levels) when all levels are fully filled. Let all leaves be at level l, then below is true for number of leaves L.




       L   <=  2l-1  [From Point 1]
       l =   ? Log2L ? + 1 
       where l is the minimum number of levels. 


 
5) In Binary tree where every node has 0 or 2 children, number of leaf nodes is always one more than nodes with two children.

           L = T + 1
        Where L = Number of leaf nodes
              T = Number of internal nodes with two children

##Types of Binary Tree
The following are common types of Binary Trees.

- Full Binary Tree A Binary Tree is a full binary tree if every node has 0 or 2 children. The following are the examples of a full binary tree. We can also say a full binary tree is a binary tree in which all nodes except leaf nodes have two children.

                   18
               /       \  
             15         30  
            /  \        /  \
          40    50    100   40

                       18
                     /    \   
                   15     20    
                  /  \       
                40    50   
              /   \
             30   50  

                     18
                  /     \  
                40       30  
                         /  \
                       100   40



In a Full Binary Tree, number of leaf nodes is the number of internal nodes plus 1
       L = I + 1
Where L = Number of leaf nodes, I = Number of internal nodes
See Handshaking Lemma and Tree for proof.



Complete Binary Tree: A Binary Tree is a complete Binary Tree if all the levels are completely filled except possibly the last level and the last level has all keys as left as possible



The following are examples of Complete Binary Trees

               18
           /       \  
         15         30  
        /  \        /  \
      40    50    100   40


               18
           /       \  
         15         30  
        /  \        /  \
      40    50    100   40
     /  \   /
    8   7  9 
Practical example of Complete Binary Tree is Binary Heap.



- Perfect Binary Tree A Binary tree is a Perfect Binary Tree in which all the internal nodes have two children and all leaf nodes are at the same level.
The following are the examples of Perfect Binary Trees.

                   18
               /       \  
             15         30  
            /  \        /  \
          40    50    100   40


                   18
               /       \  
             15         30  
A Perfect Binary Tree of height h (where height is the number of nodes on the path from the root to leaf) has 2h – 1 node.

An example of a Perfect binary tree is ancestors in the family. Keep a person at root, parents as children, parents of parents as their children.



- Balanced Binary Tree
A binary tree is balanced if the height of the tree is O(Log n) where n is the number of nodes. For Example, the AVL tree maintains O(Log n) height by making sure that the difference between the heights of the left and right subtrees is almost 1. Red-Black trees maintain O(Log n) height by making sure that the number of Black nodes on every root to leaf paths is the same and there are no adjacent red nodes. Balanced Binary Search trees are performance-wise good as they provide O(log n) time for search, insert and delete.



- A degenerate (or pathological) tree A Tree where every internal node has one child. Such trees are performance-wise same as linked list.

            10
            /
          20
           \
           30
            \
            40     


##Practice Problems
  - Hackerearth

      - [Mirror Image
      LEVEL: Very-Easy](https://www.hackerearth.com/practice/data-structures/trees/binary-and-nary-trees/practice-problems/algorithm/mirror-image-2/)

      - [Nodes in a subtree
      LEVEL: Easy](https://www.hackerearth.com/practice/data-structures/trees/binary-and-nary-trees/practice-problems/algorithm/magical-tree-1-e7f8cabd/)

      - [Directory Deletion
      LEVEL: Easy](https://www.hackerearth.com/practice/data-structures/trees/binary-and-nary-trees/practice-problems/algorithm/directory-deletion-71e793b8/)

      - [Mancunian And Colored Tree
      LEVEL: Easy](https://www.hackerearth.com/practice/data-structures/trees/binary-and-nary-trees/practice-problems/algorithm/mancunian-and-colored-tree/)

      - [Largest cycle in a tree
      LEVEL: Easy](https://www.hackerearth.com/practice/data-structures/trees/binary-and-nary-trees/practice-problems/approximate/largest-cycle-in-a-tree-9113b3ab/)

      - [Population outburst
      LEVEL: Medium](https://www.hackerearth.com/practice/data-structures/trees/binary-and-nary-trees/practice-problems/algorithm/population-outburst-7db5d39a/)

      - [Trump and gopiyas
      LEVEL: Hard](https://www.hackerearth.com/practice/data-structures/trees/binary-and-nary-trees/practice-problems/algorithm/count-the-tree/)

      - [Gandhi Tree March
      LEVEL: Hard](https://www.hackerearth.com/practice/data-structures/trees/binary-and-nary-trees/practice-problems/algorithm/gandhi-tree-march/)


## Source

  - [geeksforgeeks.org](https://www.geeksforgeeks.org/binary-tree-data-structure/)
 
  - [wikipedia.org](https://en.wikipedia.org/wiki/Binary_tree#Types_of_binary_trees)
