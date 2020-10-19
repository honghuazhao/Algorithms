//
// Created by zhaohonghua on 10/17/20.
//
#include "header.h"

/*
Find the kth largest element in an unsorted array.
 Note that it is the kth largest element in the sorted order, not the kth distinct element.

Example 1:

Input: [3,2,1,5,6,4] and k = 2
Output: 5
Example 2:

Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4
 */

int findKthLargestHelper(vector<int>& nums, int start, int end, int k) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(start, end);

    int pivot = nums[distrib(gen)];
    int pivotCount = 0;
    int left = start-1;
    int right = end+1;
    for(int i = start; i < right; i++) {
        if (nums[i] == pivot) {
            pivotCount++;
        } else if(nums[i] < pivot) {
            left++;
            nums[left] = nums[i];
        } else {
            right--;
            swap(nums[right], nums[i]);
            i--;
        }
    }
    for(int i = left+1; i < right; i++) {
        nums[i] = pivot;
    }

    if(k > end - right + 1 && k <= end - right + 1 + pivotCount) {
        return pivot;
    } else if(k <= end - right + 1) {
        return findKthLargestHelper(nums, right, end, k);
    } else {
        return findKthLargestHelper(nums, start, left, k - (end - left));
    }
}

int findKthLargest(vector<int>& nums, int k) {
    return findKthLargestHelper(nums, 0, nums.size()-1, k);
}
