---
Tags:
  - Sorting
  - Algorithm
---

# Insertion Sort

Insertion Sort is a simple sorting algorithm that builds the final sorted array one item at a time. It is much less efficient on large lists than more advanced algorithms such as quicksort, heapsort, or merge sort. However, it has some advantages, such as its simplicity and efficiency for small datasets or nearly sorted arrays.

## Working

The Insertion Sort algorithm works by dividing the input array into two regions: the sorted region and the unsorted region. Initially, the sorted region contains only the first element of the array, and the unsorted region contains the rest of the elements.

1. Starting from the second element (index 1), the algorithm considers each element one at a time, moving from left to right.

2. For each element in the unsorted region, the algorithm compares it to the elements in the sorted region, moving from right to left.

3. If the current unsorted element is smaller (or larger, for descending order) than the elements in the sorted region, the algorithm shifts the elements in the sorted region to the right to make space for the current element.

4. The algorithm repeats this process, comparing and shifting elements, until it finds the correct position for the current element within the sorted region.

5. Once the correct position is found, the algorithm inserts the current element into the sorted region.

6. The algorithm continues this process for all elements in the unsorted region, gradually expanding the sorted region until the entire array is sorted.

## Pseudocode

Here is the pseudocode for the Insertion Sort algorithm:

```
for i from 1 to n-1:
key = arr[i]
j = i - 1
while j >= 0 and arr[j] > key:
arr[j + 1] = arr[j]
j = j - 1
arr[j + 1] = key

```
In this pseudocode:
- `arr` is the input array.
- `n` is the number of elements in the array.
- `key` represents the current element being considered.
- `j` is used to iterate through the sorted region.

The key steps of the algorithm include:
- Selecting the current element as `key`.
- Iterating through the sorted region, shifting elements as needed to find the correct position for `key`.
- Inserting `key` into its correct position in the sorted region.

## Implementation 

Here is a simple implementation of the Insertion Sort algorithm in C++:

```
#include <iostream>
using namespace std;

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = key;
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    insertionSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}

```

## Debugging

Lets debug the Insertion Sort algorithm to see how it sorts this array step by step.

#### Iteration 1:

- Compare the second element, 3, to the first element, 5.
- 3 is less than 5, so swap the two elements.

The array is now: `[3, 5, 2, 1, 4]`

#### Iteration 2:

- Compare the third element, 2, to the element to its left, 5.
- 2 is less than 5, so swap the two elements.

The array is now: `[3, 2, 5, 1, 4]`

- Now, compare 2 to 3.
- 2 is less than 3, so swap the two elements.

The array is now: `[2, 3, 5, 1, 4]`

#### Iteration 3:

- Compare the fourth element, 1, to the element to its left, 5.
- 1 is less than 5, so swap the two elements.

The array is now: `[2, 3, 1, 5, 4]`

- Now, compare 1 to 3.
- 1 is less than 3, so swap the two elements.

The array is now: `[2, 1, 3, 5, 4]`

- Continue comparing 1 to 2.
- 1 is less than 2, so swap the two elements.

The array is now: `[1, 2, 3, 5, 4]`

#### Iteration 4:

- Compare the fifth element, 4, to the element to its left, 5.
- 4 is less than 5, so swap the two elements.

The array is now: `[1, 2, 3, 4, 5]`

- The array is now sorted, so the algorithm terminates.

## Conclusion

Insertion Sort is an in-place sorting algorithm that efficiently builds the sorted array one element at a time. The debugging process helps us understand how the algorithm compares and swaps elements to achieve the final sorted result.


## Complexity
The insertion sort algorithm has the following time complexity:

- Worst-case: O(n^2)
- Average-case: O(n^2)
- Best-case: O(n)