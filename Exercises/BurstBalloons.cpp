//
// Created by zhaohonghua on 10/18/20.
//

#include "header.h"

/*
Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note:

You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
Example:

Input: [3,1,5,8]
Output: 167
Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
             coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
 */

int dpHelper(vector<int>& nums, vector<vector<int>>& memo, int left, int right) {
    if(left+1 == right) return 0;

    if(memo[left][right] > 0) return memo[left][right];

    int ans = 0;
    for(int i = right-1; i >= left+1; --i) {
        ans = max(ans, nums[left]*nums[i]*nums[right] +
                       dpHelper(nums, memo, left, i) +
                       dpHelper(nums, memo, i, right));
    }
    memo[left][right] = ans;
    return ans;
}

int dp(vector<int>& nums) {
    vector<int> newNums(nums.size()+2);
    for(int i = 0; i < nums.size(); i++)
        newNums[i+1] = nums[i];
    newNums[0] = 1;
    newNums[newNums.size()-1] = 1;

    vector<vector<int>> memo(newNums.size(), vector<int>(newNums.size(), 0));

    return dpHelper(newNums, memo, 0, newNums.size()-1);
}

void backtrackingHelper(vector<int>& nums, int from, int curr, int& ans) {
    if(from >= nums.size()) {
        ans = max(ans, curr);
        return;
    }
    for(int i = from; i < nums.size(); i++) {
        int bonus = nums[i];
        bonus *= (i-1 < from)? 1 : nums[i-1];
        bonus *= (i+1 >= nums.size())? 1 : nums[i+1];

        curr += bonus;

        int numFrom = nums[i];

        for(int j = i-1; j >= from; j--)
            if(j >= 0)
                nums[j+1] = nums[j];
        nums[from] = numFrom;

        backtrackingHelper(nums, from+1, curr, ans);

        for(int j = from; j < i; j++)
            if(j >= 0)
                nums[j] = nums[j+1];
        nums[i] = numFrom;

        curr -= bonus;
    }
}

int backtrackingTimeExceed(vector<int>& nums) {
    int ans = INT_MIN;
    backtrackingHelper(nums, 0, 0, ans);
    return ans;
}


int maxCoins(vector<int>& nums) {
    return dp(nums);
}

