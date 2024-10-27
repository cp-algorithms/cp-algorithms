#include <iostream>
#include <vector>
using namespace std;

// Function to find the candidate for majority element
int findCandidate(const vector<int>& nums) {
    int candidate = 0, count = 0;
    
    for (int num : nums) {
        if (count == 0) {
            candidate = num;  // Set candidate to current element
        }
        count += (num == candidate) ? 1 : -1;  // Increment count if it is the candidate, else decrement
    }
    
    return candidate;
}

// Function to check if the candidate is the majority element
bool isMajority(const vector<int>& nums, int candidate) {
    int count = 0;
    for (int num : nums) {
        if (num == candidate) {
            count++;
        }
    }
    return count > nums.size() / 2;
}

// Function to find the majority element
int findMajorityElement(const vector<int>& nums) {
    int candidate = findCandidate(nums);
    
    if (isMajority(nums, candidate)) {
        return candidate;
    } else {
        return -1;  // No majority element
    }
}

int main() {
    vector<int> nums = {3, 3, 4, 2, 4, 4, 2, 4, 4};

    int majorityElement = findMajorityElement(nums);

    if (majorityElement != -1) {
        cout << "The majority element is: " << majorityElement << endl;
    } else {
        cout << "No majority element found." << endl;
    }

    return 0;
}
