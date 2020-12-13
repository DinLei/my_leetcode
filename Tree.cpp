/* 二叉搜索树 + 动态规划 */
/*
96. 不同的二叉搜索树
level: 中等
label: 动态规划
给定一个整数 n，求以 1 ... n 为节点组成的二叉搜索树有多少种？
*/
class Solution {
public:
  int numTrees(int n) {
    vector<int> dp(n + 1, 0);
    dp[0] = 1; dp[1] = 1;
    for(int i = 2; i <= n; i ++)
      for(int j = 0; j < i; j ++)
        dp[i] += dp[j] * dp[i - j - 1];
    return dp[n];
  }
};


/*
95. 不同的二叉搜索树 II
level: 中等
label: 动态规划
给定一个整数 n，生成所有由 1 ... n 为节点所组成的 二叉搜索树 。
*/
class Solution {
public:
  vector<TreeNode*> generateTrees(int n) {
    if( n == 0 )
      return {};
    return construct_st(1, n);
  }

  vector<TreeNode*> construct_st(int l, int r) {
    if(l > r ) 
      return { nullptr };
    vector<TreeNode*> allTrees;
    for( int i = l; i <= r; i ++ ) {
      vector<TreeNode*> leftTrees = construct_st(l, i-1);
      vector<TreeNode*> rightTrees = construct_st(i+1, r);
      for( auto lt: leftTrees ) {
        for( auto rt: rightTrees ) {
          TreeNode* currTree = new TreeNode(i);
          currTree->left = lt;
          currTree->right = rt;
          allTrees.emplace_back(currTree);
        }
      }
    }
    return allTrees;
  }
};

/*递归+深度优先搜索*/
/*
98. 验证二叉搜索树
level: 中等
给定一个二叉树，判断其是否是一个有效的二叉搜索树。

假设一个二叉搜索树具有如下特征：

节点的左子树只包含小于当前节点的数。
节点的右子树只包含大于当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/validate-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
// 方法一：中序遍历——技巧: 二叉搜索树中序遍历可以返回升序序列
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> stack;
        long long inorder = (long long)INT_MIN - 1;

        while (!stack.empty() || root != nullptr) {
            while (root != nullptr) {
                stack.push(root);
                root = root -> left;
            }
            root = stack.top();
            stack.pop();
            // 如果中序遍历得到的节点的值小于等于前一个 inorder，说明不是二叉搜索树
            if (root -> val <= inorder) {
                return false;
            }
            inorder = root -> val;
            root = root -> right;
        }
        return true;
    }
};

// 方法二：递归调用——技巧: 二叉搜索树的根结点可以作为子树的上下确界
class Solution {
public:
    bool helper(TreeNode* root, long long lower, long long upper) {
        if (root == nullptr) {
            return true;
        }
        if (root -> val <= lower || root -> val >= upper) {
            return false;
        }
        return helper(root -> left, lower, root -> val) && helper(root -> right, root -> val, upper);
    }
    bool isValidBST(TreeNode* root) {
        return helper(root, LONG_MIN, LONG_MAX);
    }
};


/*99. 恢复二叉搜索树*/
/*

给你二叉搜索树的根节点 root ，该树中的两个节点被错误地交换。请在不改变其结构的情况下，恢复这棵树。

进阶：使用 O(n) 空间复杂度的解法很容易实现。你能想出一个只使用常数空间的解决方案吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/recover-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
class Solution {
public:
  void recoverTree(TreeNode* root) {
    stack<TreeNode*> stk;
    TreeNode* next = root, *e1 = nullptr, *e2 = nullptr, *last = nullptr;
    while(!stk.empty() || next) {
      if(next) {
        stk.push(next);
        next = next->left;
      } else {
        next = stk.top(); stk.pop();
        if(last && last->val > next->val) {
          e2 = next;
          if(e1 == nullptr) e1 = last;
          else break;
        }
        last = next; next = next->right;
      }
    }
    swap(e1->val, e2->val);
  }
};
