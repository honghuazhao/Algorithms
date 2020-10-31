//
// Created by zhaohonghua on 10/31/20.
//
#include "header.h"
#include "catch.hpp"

/*
 * Output string is like: 1,3 2,1 3,2 4,0 5,0
 * Each pair of number like (1,3) is a node. Pair.first is the node val, pair.second is the children count
 * Pair.second 1: only has left child 2: only has right child 3: both have left and right child
 */
string serializeByBfs(TreeNode* root) {
    if(root == nullptr) return "";

    queue<TreeNode*> q;
    q.push(root);

    vector<string> nodeVec;
    while(!q.empty()) {
        TreeNode* n = q.front();
        q.pop();

        string str = to_string(n->val);
        int num = 0;

        if(n->left != nullptr) {
            q.push(n->left);
            num += 1;
        }
        if(n->right != nullptr) {
            q.push(n->right);
            num += 2;
        }

        str += ",";
        str += to_string(num);

        nodeVec.push_back(str);
    }

    string ans;
    for(int i = 0; i < nodeVec.size(); i++) {
        if(i != 0)
            ans += " ";
        ans += nodeVec[i];
    }
    return ans;
}

TreeNode* deserializeByBfs(string data) {
    if(data == "") return nullptr;

    vector<pair<int, int>> nodeVec;
    int pos = 0;
    while(pos < data.length()) {
        auto next = data.find(' ', pos);
        if(next == string::npos) {
            string tmp = data.substr(pos);
            auto t = tmp.find(',');
            nodeVec.push_back({stoi(tmp.substr(0, t)), stoi(tmp.substr(t+1))});
            break;
        }
        string tmp = data.substr(pos, next-pos);
        auto t = tmp.find(',');
        nodeVec.push_back({stoi(tmp.substr(0, t)), stoi(tmp.substr(t+1))});
        pos = next+1;
    }

    int i = 0;
    TreeNode* ans = nullptr;
    queue<pair<TreeNode*, int>> queueTree;
    queueTree.push({new TreeNode(nodeVec[i].first), nodeVec[i].second});
    i++;
    while(!queueTree.empty()) {
        auto n = queueTree.front();
        queueTree.pop();

        if(ans == nullptr)
            ans = n.first;
        if((n.second & 1) > 0) {
            TreeNode* next = new TreeNode(nodeVec[i].first);
            n.first->left = next;
            queueTree.push({next, nodeVec[i].second});
            i++;
        }
        if((n.second & 2) > 0) {
            TreeNode* next = new TreeNode(nodeVec[i].first);
            n.first->right = next;
            queueTree.push({next, nodeVec[i].second});
            i++;
        }
    }
    return ans;
}

/*
 * Output string is like 1(2(4)())(3()(5))
 * A node is like: nodeVal(subNode1)(subNode2) or only nodeVal if it's a leaf node
 */
string serializeByDfs(TreeNode* root) {
    if(root == nullptr)
        return "";
    string ans = to_string(root->val);
    if(root->left != nullptr || root->right != nullptr) {
        ans += "(";
        ans += serializeByDfs(root->left);
        ans += ")";

        ans += "(";
        ans += serializeByDfs(root->right);
        ans += ")";
    }

    return ans;
}

TreeNode* deserializeByDfsHelper(string& data, int& pos) {
    int start = pos;
    while(pos < data.length() && data[pos] != '(' && data[pos] != ')') pos++;
    if(start == pos) {
        return nullptr;
    }
    int val = stoi(data.substr(start, pos-start));
    TreeNode* root = new TreeNode(val);
    if(pos == data.length())
        return root;

    if(data[pos] == '(') {
        pos++;
        root->left = deserializeByDfsHelper(data, pos);
        pos++;

        pos++;
        root->right = deserializeByDfsHelper(data, pos);
        pos++;
    }

    return root;
}


TreeNode* deserializeByDfs(string data) {
    if(data == "") return nullptr;
    int pos = 0;
    return deserializeByDfsHelper(data, pos);
}

string serialize(TreeNode* root) {
    return serializeByDfs(root);
}

TreeNode* deserialize(string data) {
    return deserializeByDfs(data);
}


TEST_CASE( "LeetCode.297", "[Serialize and Deserialize Binary Tree]" ) {
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node5 = new TreeNode(5);
    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node3->right = node5;

    string serialized = serialize(node1);
    TreeNode* root = deserialize(serialized);

    REQUIRE( root->val == 1 );
    REQUIRE( root->left->val == 2 );
    REQUIRE( root->right->val == 3);
    REQUIRE( root->left->left->val == 4 );
    REQUIRE( root->left->right == nullptr );
    REQUIRE( root->right->left == nullptr );
    REQUIRE( root->right->right->val == 5 );
}