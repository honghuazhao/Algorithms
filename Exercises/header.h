//
// Created by zhaohonghua on 10/17/20.
//

#ifndef EXERCISES_HEADER_H
#define EXERCISES_HEADER_H

#include <cstdint>
#include <climits>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <iostream>
#include <random>
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

int findKthLargest(vector<int>& nums, int k);
int maxCoins(vector<int>& nums);

#endif //EXERCISES_HEADER_H
