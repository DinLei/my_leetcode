/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include <iostream>

class Solution {

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

public:
    int maxDepth(TreeNode* root) {
      int maxTreeDepth = 0;
      if (root == NULL) {
        return maxTreeDepth;
      }
      
      int maxLeftDepth = maxDepth(root->left) + 1;
      int maxRightDepth = maxDepth(root->right) + 1;

      return (maxLeftDepth > maxRightDepth) ? maxLeftDepth : maxRightDepth;
    }



};
