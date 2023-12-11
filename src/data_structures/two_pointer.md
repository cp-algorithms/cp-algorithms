# Two Pointer Algorithm

## Overview

The Two Pointer Algorithm is a technique used for efficiently solving problems with linear data structures like arrays or linked lists. It involves using two pointers to traverse the data structure and perform operations based on certain conditions.

## Basic Idea

The basic idea behind the Two Pointer Algorithm is to maintain two pointers that traverse the data structure in a way that reduces the time complexity. The pointers move towards each other or in a specific pattern based on the problem requirements.

## Algorithm Steps

1. **Initialize Pointers:**
   - Initialize two pointers, usually at the beginning or end of the data structure.

2. **Move Pointers:**
   - Move the pointers towards each other, closer or farther based on the problem requirements.
   - Update pointers based on specific conditions.

3. **Check Conditions:**
   - Check conditions at each step to determine if the solution is found or if the pointers need to be adjusted.

4. **Repeat:**
   - Repeat steps 2 and 3 until the pointers meet or fulfill the problem requirements.

## Common Use Cases

1. **Array Sum/Pair Sum:**
   - Finding pairs in a sorted/unsorted array that sum up to a given target.

2. **Search in a Sorted Array:**
   - Searching for a target element efficiently in a sorted array.

3. **Palindrome Check:**
   - Checking if a given string or array is a palindrome.

4. **Trapping Rain Water:**
   - Calculating the amount of water that can be trapped between bars in an elevation map.

## Example

### Two Sum Problem

```
int main() {
    // Example input vector
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    // Sorting the input vector
    std::sort(nums.begin(), nums.end());

    // Initializing two pointers
    int left = 0;
    int right = nums.size() - 1;

    // Two Pointer Algorithm
    while (left < right) {
        int currentSum = nums[left] + nums[right];

        if (currentSum == target) {
            // Solution found
            std::cout << "Pair found: [" << nums[left] << ", " << nums[right] << "]" << std::endl;
            return 0;
        } else if (currentSum < target) {
            // Move left pointer to the right
            ++left;
        } else {
            // Move right pointer to the left
            --right;
        }
    }

    // No solution found
    std::cout << "No pair found." << std::endl;

    return 0;
}

```