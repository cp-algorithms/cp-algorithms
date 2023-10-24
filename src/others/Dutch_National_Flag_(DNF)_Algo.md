
# Dutch National Flag Algorithm

The Dutch National Flag (DNF) algorithm, also known as the 3-way partition algorithm, is a powerful technique for efficiently sorting an array containing only three distinct elements without using additional memory space. This algorithm is often used in situations where you need to sort an array of integers with values 0, 1, and 2. The DNF algorithm is particularly valuable when you want to sort data with three distinct values while minimizing time and space complexity.

## The Dutch Flag Problem

The Dutch flag algorithm is named after a classic problem. Imagine you have a Dutch national flag consisting of three horizontal stripes: white, red, and blue, from top to bottom. The task is to arrange these colors in the correct order, such that all the white stripes are at the top, followed by the red stripes, and then the blue stripes at the bottom. This problem can be translated into sorting an array of 0s, 1s, and 2s, with 0 representing white, 1 representing red, and 2 representing blue.

## The Problem Statement

In the context of the Dutch National Flag algorithm, the problem is stated as follows: You are given an array that contains only the integers 0, 1, and 2. Your task is to sort this array so that all the 0s come first, followed by all the 1s, and then all the 2s. The challenge is to do this efficiently and in-place without using additional memory space or a sorting function.

## Brute Force and Inefficient Solutions

Before delving into the Dutch National Flag algorithm, it's essential to understand that the problem can be solved using traditional sorting algorithms like Merge Sort or Quick Sort. However, these algorithms have time complexities of O(NlogN) and often require extra memory for temporary storage. In interviews or competitive programming, these solutions would not be considered optimal.

## The Dutch National Flag Algorithm

The Dutch National Flag algorithm provides an efficient and elegant solution to this problem. It uses three pointers: 'low', 'mid', and 'high' to maintain the three regions in the array as required: 0s on the left, 1s in the middle, and 2s on the right. The algorithm iterates through the array, moving these pointers to reorganize the elements accordingly. Here are the main steps:

1. Initialize the three pointers: 'low', 'mid', and 'high'.
2. Use a while loop that continues as long as 'mid' is less than or equal to 'high'. This loop processes the elements within the array.
3. Inside the loop:
   - If the element at the 'mid' pointer is 0, swap it with the element at the 'low' pointer and increment both 'low' and 'mid'.
   - If the element at the 'mid' pointer is 1, leave it in place (no swap) and increment 'mid'.
   - If the element at the 'mid' pointer is 2, swap it with the element at the 'high' pointer and decrement 'high'.
4. Continue this process until 'mid' exceeds 'high'. At this point, the entire array is sorted with all the 0s on the left, followed by the 1s, and then the 2s on the right.
![image](https://github.com/shimmer12/cp-algorithms/assets/92056170/32906482-4f62-4c51-8d8d-fe6a0e279814)

![image](https://github.com/shimmer12/cp-algorithms/assets/92056170/fc9dc112-5d36-42f2-bb06-4347a371e00c)

$$\begin{array}{ccccccccccc}
  0 & 0 & 1 & 1 & 1 & ? & \dots & ? & 2 & 2 & 2 \\
  & & \uparrow & & & \uparrow && \uparrow && \\
  & & \text{low} & & & \text{mid} & & \text{high} & & &
\end{array}$$


```cpp
#include <vector>

void dutchFlagSort(std::vector<int>& nums) {
    int low = 0;
    int mid = 0;
    int high = nums.size() - 1;

    while (mid <= high) {
        if (nums[mid] == 0) {
            std::swap(nums[low], nums[mid]);
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else {
            std::swap(nums[mid], nums[high]);
            high--;
        }
    }
}
```

## Time and Space Complexity

The Dutch National Flag algorithm operates with O(N) time complexity, where N is the length of the input array. This efficiency results from processing each element one at a time in a single pass through the array. The algorithm minimizes unnecessary operations and transactions. The space complexity is O(1) as it uses only a constant amount of additional space to store the three pointers (low, mid, high), without requiring additional data structures or memory allocations.

In summary, the Dutch National Flag algorithm is a valuable tool for efficiently sorting an array with three distinct elements while minimizing time and space complexity. Understanding the thought process and intuition behind this algorithm can be a great advantage in interviews, competitive programming, and real-world applications where sorting three distinct values is a common requirement.

---
---
tags:
  - Original
---
