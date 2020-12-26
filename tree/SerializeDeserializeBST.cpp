#include <iostream>
#include <stack>
#include <queue>

using namespace std;


class Codec {
public:
  
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };

  void insertValue(TreeNode* root, int value) {
    if (root == NULL) {
      root = new TreeNode(value);
    } else if (root->val > value) {
      if (root->left == NULL) {
        root->left = new TreeNode(value);
      } else {
        insertValue(root->left, value);
      }
    } else {
      if (root->right == NULL) {
        root->right = new TreeNode(value);
      } else {
        insertValue(root->right, value);
      }
    }
  }

  //广度优先遍历
  void broadOrder(TreeNode* root, string& ser){
    if (! root)
      return ;
    queue<TreeNode*> nQueue;
    nQueue.push(root);

    while (! nQueue.empty()) {
      TreeNode* next = nQueue.front();
      ser += to_string(next->val);
      nQueue.pop();
      if (next->left)
        nQueue.push(next->left);
      if (next->right)
        nQueue.push(next->right);
    }
    
  }

  void preOrder(TreeNode* root, string& ser) {
    if (root) {
      ser += to_string(root->val);
      preOrder(root->left, ser);
      preOrder(root->right, ser);
    }
  }

  void preOrderNoRescur(TreeNode* root, string& ser) {
    if (! root)
      return ;
    stack<TreeNode*> nStack;
    nStack.push(root);
    while (! nStack.empty()) {
      TreeNode* next = nStack.top();
      ser += to_string(next->val);
      nStack.pop();
      if (next->right) {
        nStack.push(next->right);
      }
      if (next->left) {
        nStack.push(next->left);
      }
    }
  }

    //前序非递归
  void preOrderNoRescur2(TreeNode *t){
    stack<TreeNode *> s;
    TreeNode *p = t;
  
    while (p != nullptr || !s.empty()) {
      if (p != nullptr) {
        cout << p->val << endl;//根
        s.push(p);
        p = p->left;//左
      } else {
        p = s.top();
        p = p->right;//右
        s.pop();
      }
    }
  }
 
  void inOrder(TreeNode* root, string& ser) {
    if (root) {
      inOrder(root->left, ser);
      ser += to_string(root->val);
      inOrder(root->right, ser);
    }
  }

  void inOrderNoRescur(TreeNode* root, string& ser) {
    stack<TreeNode*> nStack;
    TreeNode* next = root;
    while (next || !nStack.empty()) {
      if (next) {
        nStack.push(next);
        next = next->left;//左
      } else {
        next = nStack.top();
        nStack.pop();
        ser += to_string(next->val);//根
        next = next->right;//右
      }
    }
  }

  void posOrder(TreeNode* root, string& ser) {
    if (root) {
      posOrder(root->left, ser);
      posOrder(root->right, ser);
      ser += to_string(root->val);
    }
  }

  void posOrderNoRescur(TreeNode* root, string& ser) {
    if (! root)
      return ;
    stack<TreeNode*> nStack1, nStack2;
    nStack1.push(root);
    while (!nStack1.empty()) {
      TreeNode* pre = nStack1.top(); nStack1.pop();
      nStack2.push(pre);
      if (pre->left)
        nStack1.push(pre->left);
      if (pre->right) 
        nStack1.push(pre->right);
    }
    while (!nStack2.empty()) {
      TreeNode* next = nStack2.top();
      ser += to_string(next->val);
      nStack2.pop();
    }
  }

  void posOrderNoRescur2(TreeNode *t) {
    stack<TreeNode *> s;
    TreeNode *p = t;
    TreeNode *tmp = nullptr;
    //tmp 指针是为了保存节点上一次访问的状态
    while (p != nullptr || !s.empty()) {
      if (p != nullptr) {
        s.push(p);
        p = p->left;//左
      } else {
        //每次取栈顶元素
        //判断栈顶元素的右孩子是否为空，
        //如果不为空，查看之前访问的节点是不是该栈顶元素的右孩子
        p = s.top();
        if (p->right != nullptr && p->right != tmp) {
          p = p->right;//右
        } else {
          cout << p->val << endl;//根
          s.pop();
          //每次访问节点之后，需要将缓存上一次访问的节点，并且将指针置空
          tmp = p;
          p = nullptr;
        }
      }
    }
  }

  /* 
      Encodes a tree to a single string.
      你可以将以下二叉树：
         1
        / \
       2   3
          / \
         4   5
      序列化为 "[1,2,3,null,null,4,5]"
  */

  string serialize(TreeNode* root) {
    /*
      BF
    */
    string ans;
    if (! root)
      return "[]";
    ans = "[";
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
        ans += "null";
      }
      ans += ",";
    }
    int end = ans.length()-1;
    // while (ans[end] == ',' || ans[end] == '#')
    // while (ans[end] == ',' || ans[end] == 'n' || ans[end] == 'u' || ans[end] == 'l')
    //   end --;
    while ( !( ans[end] >= '0' && ans[end] <= '9') )
      end--;
    
    return ans.substr(0, end+1) + "]";
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    /*
      DeBF
    */
    int len = data.size();
    if (len <= 2)
      return NULL;

    vector<TreeNode*> nodes;
  /*
    string::size_type start = 1, index;
    do {
      index = data.find_first_of(',', start);
      if (index != string::npos) {
        string val = data.substr(start, index-start);
        // if (val == "#")
        if (val == "null")
          nodes.push_back(NULL);
        else {
          int nVal = atoi(val.c_str());
          TreeNode* node = new TreeNode(nVal);
          nodes.push_back(node);
        }
        start = index + 1;
      }
    } while (index != string::npos);

    string val = data.substr(start, len-1-start);
    int nVal = atoi(val.c_str());
    TreeNode* node = new TreeNode(nVal);
    nodes.push_back(node);
  */

    string word = "";
    for (int i = 1; i <= len - 2; i++){
      if (data[i] == ',') {
          TreeNode* tmp = NULL;
          if (word != "null") {
            int num = atoi(word.c_str());
            tmp = new TreeNode(num);
          }
          nodes.push_back(tmp);
          word = "";
      } else {
        word += data[i];
      }
    }
    if (word != "" && word != "null") {
        int num = atoi(word.c_str());
        TreeNode* tmp = new TreeNode(num);
        nodes.push_back(tmp);
    }

    int cnt = nodes.size();
    int q = 0, p = 1;

    while (p < cnt) {
      if (nodes[q] == NULL)
        q ++;
      else {
        if (p < cnt)
          nodes[q]->left = nodes[p];
        if (p+1 < cnt)
          nodes[q]->right = nodes[p+1];
        p += 2;
        q ++;
      }
    }
    
    return nodes[0];
  }

  void test() {
    TreeNode* tree = new TreeNode(10);
    insertValue(tree, 5);
    insertValue(tree, 25);
    insertValue(tree, 15);
    insertValue(tree, 30); 

    // string preSer = "";
    // preOrder(tree, preSer);
    // printf("before:%s\n", preSer.c_str());

    string bfs = serialize(tree);
    printf("bfs:%s\n", bfs.c_str());

    string bfs1 = "[1,2,3,null,null,4,5]";
    bfs1.length();
    printf("test:%s\n", bfs1.c_str());
    TreeNode* tn = deserialize(bfs1);

    string preS;
    preOrder(tn, preS);
    printf("pre:%s\n", preS.c_str());

    string bfs2 = serialize(tn);
    printf("bfs2:%s\n", bfs2.c_str());
  }
};


int main() {
  /* code */
  Codec codec;
  codec.test();

  return 0;
}

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));