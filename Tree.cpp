/** 二叉搜索树 + 动态规划 */
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


/**
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

/*
105. 从前序与中序遍历序列构造二叉树
106. 从中序与后序遍历序列构造二叉树
*/

/*
根据一棵树的前序遍历与中序遍历构造二叉树。
*/
// 递归：关键是确定根的位置之后，左右子树元素个数相等
class Solution {
private:
    unordered_map<int, int> index;

public:
    TreeNode* myBuildTree(const vector<int>& preorder, const vector<int>& inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right) {
        if (preorder_left > preorder_right) {
            return nullptr;
        }
        
        // 前序遍历中的第一个节点就是根节点
        int preorder_root = preorder_left;
        // 在中序遍历中定位根节点
        int inorder_root = index[preorder[preorder_root]];
        
        // 先把根节点建立出来
        TreeNode* root = new TreeNode(preorder[preorder_root]);
        // 得到左子树中的节点数目
        int size_left_subtree = inorder_root - inorder_left;
        // 递归地构造左子树，并连接到根节点
        // 先序遍历中「从 左边界+1 开始的 size_left_subtree」个元素就对应了中序遍历中「从 左边界 开始到 根节点定位-1」的元素
        root->left = myBuildTree(preorder, inorder, preorder_left + 1, preorder_left + size_left_subtree, inorder_left, inorder_root - 1);
        // 递归地构造右子树，并连接到根节点
        // 先序遍历中「从 左边界+1+左子树节点数目 开始到 右边界」的元素就对应了中序遍历中「从 根节点定位+1 到 右边界」的元素
        root->right = myBuildTree(preorder, inorder, preorder_left + size_left_subtree + 1, preorder_right, inorder_root + 1, inorder_right);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        // 构造哈希映射，帮助我们快速定位根节点
        for (int i = 0; i < n; ++i) {
            index[inorder[i]] = i;
        }
        return myBuildTree(preorder, inorder, 0, n - 1, 0, n - 1);
    }
};

// 迭代
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (!preorder.size()) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(preorder[0]);
        stack<TreeNode*> stk;
        stk.push(root);
        int inorderIndex = 0;
        for (int i = 1; i < preorder.size(); ++i) {
            int preorderVal = preorder[i];
            TreeNode* node = stk.top();
            if (node->val != inorder[inorderIndex]) {
                node->left = new TreeNode(preorderVal);
                stk.push(node->left);
            }
            else {
                while (!stk.empty() && stk.top()->val == inorder[inorderIndex]) {
                    node = stk.top();
                    stk.pop();
                    ++inorderIndex;
                }
                node->right = new TreeNode(preorderVal);
                stk.push(node->right);
            }
        }
        return root;
    }
};

/*110. 平衡二叉树*/
/*
给定一个二叉树，判断它是否是高度平衡的二叉树。

本题中，一棵高度平衡二叉树定义为：一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1 。
*/
// 本题的关键是，在递归计算子树高度的时候，就递归的进行判断，如果不满足就返回-1
class Solution {
public:
  int height(TreeNode* root) {
    if (root == NULL) {
        return 0;
    } 
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if(leftHeight == -1 || rightHeight == -1 || abs(leftHeight-rightHeight) > 1)
      return -1;
    return max(leftHeight, rightHeight) + 1;
  }

  bool isBalanced(TreeNode* root) {
    if(root == NULL)
      return 1;
    return height(root) > 0;
  }
};

/*112. 路径总和*/
/*
给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。
*/
class Solution {
public:
  bool hasPathSum(TreeNode* root, int sum) {
    if( root == NULL )
      return false;
    if( root->left == NULL && root->right == NULL )
      return sum == root->val;
    return hasPathSum(root->left, sum-root->val) || hasPathSum(root->right, sum-root->val);
  }
};

/*114. 二叉树展开为链表*/
/*
给定一个二叉树，原地将它展开为一个单链表。
*/
//方法一：前序遍历和展开同步进行。关键是将父节点保存下来，左右子节点压栈，先右后左
// 树 和 链表 一样，只要想办法把指针指对了就行。指针对应信息序列内部会保存下来。
class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        auto stk = stack<TreeNode*>();
        stk.push(root);
        TreeNode *prev = nullptr;
        while (!stk.empty()) {
            TreeNode *curr = stk.top(); stk.pop();
            if (prev != nullptr) {
                prev->left = nullptr;
                prev->right = curr;
            }
            TreeNode *left = curr->left, *right = curr->right;
            if (right != nullptr) {
                stk.push(right);
            }
            if (left != nullptr) {
                stk.push(left);
            }
            prev = curr;
        }
    }
};

//方法二：寻找前驱节点。解题的关键是：左子树的最下最右的节点 新立为 右子树的父节点.
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode *curr = root;
        while (curr != nullptr) {
            if (curr->left != nullptr) {
                auto next = curr->left;
                auto predecessor = next;
                while (predecessor->right != nullptr) {
                    predecessor = predecessor->right;
                }
                predecessor->right = curr->right;
                curr->left = nullptr;
                curr->right = next;
            }
            curr = curr->right;
        }
    }
};

/*116. 填充每个节点的下一个右侧节点指针*/
/*
给定一个 完美二叉树 ，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。

初始状态下，所有 next 指针都被设置为 NULL。

进阶：
你只能使用常量级额外空间。
使用递归解题也符合要求，本题中递归程序占用的栈空间不算做额外的空间复杂度。
*/

// 方法一：层次遍历 O(n) + O(n)
// 方法二：使用已建立的 next 指针
class Solution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) {
            return root;
        } 
        // 从根节点开始
        Node* leftmost = root;
        
        while (leftmost->left != nullptr) {
            
            // 遍历这一层节点组织成的链表，为下一层的节点更新 next 指针
            Node* head = leftmost;
            
            while (head != nullptr) {
                // CONNECTION 1
                head->left->next = head->right;
                // CONNECTION 2
                if (head->next != nullptr) {
                    head->right->next = head->next->left;
                }
                // 指针向后移动
                head = head->next;
            }
            // 去下一层的最左的节点
            leftmost = leftmost->left;
        }
        
        return root;
    }
};
/*117. 填充每个节点的下一个右侧节点指针 II*/
// 注意引用的问题。如果子逻辑太多，考虑子逻辑拿出来做一个函数
class Solution {
public:
    void handle(Node* &last, Node* &p, Node* &nextStart) {
        if (last) {
            last->next = p;
        } 
        if (!nextStart) {
            nextStart = p;
        }
        last = p;
    }

    Node* connect(Node* root) {
        if (!root) {
            return nullptr;
        }
        Node *start = root;
        while (start) {
            Node *last = nullptr, *nextStart = nullptr;
            for (Node *p = start; p != nullptr; p = p->next) {
                if (p->left) {
                    handle(last, p->left, nextStart);
                }
                if (p->right) {
                    handle(last, p->right, nextStart);
                }
            }
            start = nextStart;
        }
        return root;
    }
};


/*124. 二叉树中的最大路径和*/
/*
和 543. 二叉树的直径 类似

给定一个非空二叉树，返回其最大路径和。
本题中，路径被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。该路径至少包含一个节点，且不一定经过根节点。
*/
class Solution {
private:
    int maxSum = INT_MIN;

public:
    int maxGain(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        
        // 递归计算左右子节点的最大贡献值
        // 只有在最大贡献值大于 0 时，才会选取对应子节点
        int leftGain = max(maxGain(node->left), 0);
        int rightGain = max(maxGain(node->right), 0);

        // 节点的最大路径和取决于该节点的值与该节点的左右子节点的最大贡献值
        int priceNewpath = node->val + leftGain + rightGain;

        // 更新答案
        maxSum = max(maxSum, priceNewpath);

        // 返回节点的最大贡献值
        return node->val + max(leftGain, rightGain);
    }

    int maxPathSum(TreeNode* root) {
        maxGain(root);
        return maxSum;
    }
};


/*剑指 Offer 33. 二叉搜索树的后序遍历序列*/
/*输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。如果是则返回 true，否则返回 false。假设输入的数组的任意两个数字都互不相同。*/
class Solution {
public:
  bool verifyPostorder(vector<int>& postorder) {
    return recur(postorder, 0, postorder.size() - 1);
  }

  bool recur(vector<int>& postorder, int i, int j) {
    if(i >= j) return true;
    int p = i;
    while(postorder[p] < postorder[j]) p ++;
    int m = p;
    while(postorder[p] > postorder[j]) p ++;
    return p == j && recur(postorder, i, m - 1) && recur(postorder, m, j - 1);
  }
};


/*236. 二叉树的最近公共祖先*/
/*
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
TreeNode* ans;
public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    dfs(root, p, q);
    return ans;
  }

  bool dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == NULL) return 0;
    bool lson = dfs(root->left, p, q);
    bool rson = dfs(root->right, p, q);
    if((lson && rson) || ((root == p || root == q) && (lson || rson)))
      ans = root;
    return lson || rson || (root == p || root == q);
  }
};

/*572. 另一个树的子树*/
/*
给定两个非空二叉树 s 和 t，检验 s 中是否包含和 t 具有相同结构和节点值的子树。s 的一个子树包括 s 的一个节点和这个节点的所有子孙。s 也可以看做它自身的一棵子树。
*/
class Solution {
public:
  // 对当前节点贪心搜索
  bool check(TreeNode* s, TreeNode* t) {
    if(!s && !t) return true;

    if((!s && t) || (s && !t) || s->val != t->val) 
      return false;
    
    return check(s->left, t->left) && check(s->right, t->right);
  }

  // 对s的每棵子树都要深入到s的每个节点进行判断
  bool dfs(TreeNode* s, TreeNode* t) {
    if(!s) return false;
    return check(s, t) || dfs(s->left, t) || dfs(s->right, t);
  }

  bool isSubtree(TreeNode* s, TreeNode* t) {
    return dfs(s, t);
  }
};


/*297. 二叉树的序列化与反序列化*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
      if (! root)
        return "";
      string ans = "";
      queue<TreeNode*> nQueue;
      nQueue.push(root);
      while (!nQueue.empty()) {
        TreeNode* next = nQueue.front();
        nQueue.pop();
        if (next) {
          ans += to_string(next->val);
          nQueue.push(next->left);
          nQueue.push(next->right);
        } else {
          ans += "#";
        }
        ans += ",";
      }
      int end = ans.length()-1;
      while (ans[end] == ',' || ans[end] == '#')
        end --;
      
      return ans.substr(0, end+1);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
      if(data == "") return nullptr;
      std::istringstream iss(data);
      string tmpVal;
      getline(iss, tmpVal, ',');
      TreeNode* root = new TreeNode(stoi(tmpVal));
      queue<TreeNode*> que;
      que.push(root);
      while(getline(iss, tmpVal, ',')) {
        TreeNode* node = que.front(); que.pop();
        if(tmpVal != "#") {
          node->left = new TreeNode(stoi(tmpVal));
          que.push(node->left);
        } else {
          node->left = nullptr;
        }

        if(getline(iss, tmpVal, ',')) {
          if(tmpVal != "#") {
            node->right = new TreeNode(stoi(tmpVal));
            que.push(node->right);
          } else {
            node->right = nullptr;
          }
        }
      }
      return root;
    } 
};


/*103. 二叉树的锯齿形层次遍历*/
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if( root == NULL )
            return {};
        vector<vector<int> > ans;
        deque<TreeNode*> que;
        que.push_back(root);
        bool direc = true;
        TreeNode* node;
        while( !que.empty() ) {
            int n = que.size();
            vector<int> layer;
            while( n -- > 0 ) {
                if( direc ) {
                    node = que.front();
                    que.pop_front();
                    if(node->left) que.push_back(node->left);
                    if(node->right) que.push_back(node->right);
                } else {
                    node = que.back();
                    que.pop_back();
                    if(node->right) que.push_front(node->right);
                    if(node->left) que.push_front(node->left);
                }
                layer.push_back(node->val);
            }

            direc = !direc;
            ans.push_back(layer);
        }
        return ans;
    }
};

/*958. 二叉树的完全性检验*/
class Solution {
public:
  bool isCompleteTree(TreeNode* root) {
    queue<TreeNode*> que;
    que.push(root);
    TreeNode* prev = root;
    while(!que.empty()) {
      TreeNode* curr = que.front(); que.pop();
      if(!prev && curr) return false;
      if(curr) {
        que.push(curr->left);
        que.push(curr->right);
      }
      prev = curr;
    }
    return true;
  }
};


/*226. 翻转二叉树*/
/*
翻转一棵二叉树。
*/
class Solution {
public:
  TreeNode* invertTree(TreeNode* root) {
    dfs(root);
    return root;
  }

  void dfs(TreeNode* root) {
    if(!root) return;
    TreeNode* tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    dfs(root->left);
    dfs(root->right);
  }
};
