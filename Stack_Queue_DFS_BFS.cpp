// DFS
/**200. 岛屿数量*/
/*
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。
*/
class Solution {
public:
  int numIslands(vector<vector<char>>& grid) {
    int nrow = grid.size();
    if(nrow == 0)
      return 0;
    int ncol = grid[0].size();

    int ans = 0;
    for(int i = 0; i < nrow; i ++) {
      for(int j = 0; j < ncol; j ++) {
        if(grid[i][j] == '1') {
          ans ++;
          dfs(grid, i, j, nrow, ncol);
        }
      }
    }
    return ans;
  }

  void dfs(vector<vector<char>>& grid, int i, int j, int nrow, int ncol) {
    // 注意这里的判断条件，这边的5个if不能放到一起
    if(grid[i][j] != '1')
      return ;
    // 技巧：遍历过的就改变状态，任意值都可以
    grid[i][j] = '0';
    if(i > 0)
      dfs(grid, i-1, j, nrow, ncol);
    if(i < nrow - 1)
      dfs(grid, i+1, j, nrow, ncol);
    if(j > 0)
      dfs(grid, i, j-1, nrow, ncol);
    if(j < ncol - 1)
      dfs(grid, i, j+1, nrow, ncol);
  }
};

/**695. 岛屿的最大面积*/
class Solution {
private:
  // 技巧：将方向提前定好，后面直接for循环遍历
  int di[4] = {1, 0, -1, 0};
  int dj[4] = {0, -1, 0, 1};
public:
  int maxAreaOfIsland(vector<vector<int>>& grid) {
    int nrow = grid.size();
    if(nrow == 0)
      return 0;
    int ncol = grid[0].size();

    int ans = 0;
    for(int i = 0; i < nrow; i ++) {
      for(int j = 0; j < ncol; j ++) {
        ans = max(ans, dfs(grid, i, j, nrow, ncol));
      }
    }
    return ans;
  }

  int dfs(vector<vector<int>>& grid, int i, int j, int nrow, int ncol) {
    if(i < 0 || i == nrow || j < 0 || j == ncol || grid[i][j] != 1)
      return 0;
    // 遍历过的一定要改变状态
    grid[i][j] = 0;
    int area = 1;
    for(int x = 0; x < 4; x ++) {
      area += dfs(grid, i + di[x], j + dj[x], nrow, ncol);
    }
    return area;
  }
};


/*130. 被围绕的区域*/
/*
给定一个二维的矩阵，包含 'X' 和 'O'（字母 O）。
找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。

被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为 'X'。 任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被填充为 'X'。如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。
*/
class Solution {
public:
  int nr = 0, nc = 0;
  void solve(vector<vector<char>>& board) {
    nr = board.size();
    if( nr == 0 ) return ;
    nc = board[0].size();
    // 这道题目与岛屿统计不同点在于[边界&与边界相连]的'O'不会被填充，所以只从边界向内部开始深度遍历，
    // 边界相关的'O'先用其他字符填充代替
    for( int i = 0; i < nr; i ++ ) {
      dfs(board, i, 0);     // 每一行的最左边
      dfs(board, i, nc - 1);  // 每一行的最右边
    }
    for( int j = 1; j < nc - 1; j ++ ) {
      dfs(board, 0, j);     // 每一列的最上边
      dfs(board, nr - 1, j);  // 每一列的最下边
    }
    for( int i = 0; i < nr; i ++ ) {
      for( int j = 0; j < nc; j ++ ) {
        if( board[i][j] == 'O' )
          board[i][j] = 'X';
        else if( board[i][j] == 'A' )
          board[i][j] = 'O';
      }
    }
  }

  void dfs(vector<vector<char>>& board, int i, int j) {
    if( i < 0 || i >= nr || j < 0 || j >= nc || board[i][j] != 'O' )
      return ;
    board[i][j] = 'A';
    dfs(board, i + 1, j);
    dfs(board, i - 1, j);
    dfs(board, i, j + 1);
    dfs(board, i, j - 1);
  }
};


/*剑指 Offer 12. 矩阵中的路径*/
/*
请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一格开始，每一步可以在矩阵中向左、右、上、下移动一格。如果一条路径经过了矩阵的某一格，那么该路径不能再次进入该格子。例如，在下面的3×4的矩阵中包含一条字符串“bfce”的路径（路径中的字母用加粗标出）。

[["a","b","c","e"],
["s","f","c","s"],
["a","d","e","e"]]

但矩阵中不包含字符串“abfb”的路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入这个格子。
*/
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        rows = board.size();
        cols = board[0].size();
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(dfs(board, word, i, j, 0)) return true;
            }
        }
        return false;
    }
private:
    int rows, cols;
    bool dfs(vector<vector<char>>& board, string word, int i, int j, int k) {
        if(i >= rows || i < 0 || j >= cols || j < 0 || board[i][j] != word[k]) return false;
        if(k == word.size() - 1) return true;
        // 只要将遍历过的值临时改变就不会重复使用了
        board[i][j] = '\0';
        // 联合判断的写法技巧
        bool res = dfs(board, word, i + 1, j, k + 1) || dfs(board, word, i - 1, j, k + 1) || 
                      dfs(board, word, i, j + 1, k + 1) || dfs(board, word, i , j - 1, k + 1);
        board[i][j] = word[k];
        return res;
    }
};

/*239. 滑动窗口最大值*/
/*
给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

返回滑动窗口中的最大值。
*/
class Solution {
public:

  /*
    1. 使用双向队列快速进行首尾的删除
    2. 保证队列里至多k个元素，且按顺序保留最大的几个，小于就删除
    2.1 此举保证比较只会在滑动窗口内，且比较过的不会重复比较
    3. 技巧：队列中存的是索引值，只有存索引值才能保证数据是在滑动窗口之内
  */

  void clean_deq(deque<int>& deq, vector<int>& nums, int i, int k) {
  // void clean_deq(list<int>& deq, vector<int>& nums, int i, int k) {
    if( !deq.empty() && deq.front() == i - k )
      deq.pop_front();
    
    while( !deq.empty() && nums[i] > nums[deq.back()] ) 
      deq.pop_back();
  }

  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    if( n == 0 || k == 0 )
      return vector<int>{};
    else if( n == 1 || k == 1 )
      return vector<int>(begin(nums), end(nums));
    k = min(k, n);
    
    deque<int> deq;
    // list<int> deq;
    for( int i=0; i<k; i++ ) {
      clean_deq(deq, nums, i, k);
      deq.push_back(i);
    }
    vector<int> ans(n-k+1);
    ans[0] = nums[deq.front()];

    for(int i=k; i<n; i++ ) {
      clean_deq(deq, nums, i, k);
      deq.push_back(i);
      ans[i-k+1] = nums[deq.front()];
    }

    return ans;
  }
};

/*739. 每日温度*/
/*
请根据每日 气温 列表，重新生成一个列表。对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。如果气温在这之后都不会升高，请在该位置用 0 来代替。
*/
// 滑动窗口+单调栈+存索引，保留 位置+数值 信息
  vector<int> dailyTemperatures(vector<int>& T) {
    int tSize = T.size();
    vector<int> ans(tSize, 0);

    stack<int> stk;

    for( int i = 0; i < tSize; i ++ ) {
      while( !stk.empty() && T[i] > T[stk.top()] ) {
        ans[stk.top()] = i - stk.top();
        stk.pop();
      } 
      
      stk.push(i);
    }

    return ans;
  }

/*84. 柱状图中最大的矩形*/
/*
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
求在该柱状图中，能够勾勒出来的矩形的最大面积。
*/
// 单调栈，通过左右两个方向的单调栈，进行区间确定
// 空间换时间，时间复杂度从 O(N^2) -> O(N)
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n), right(n);
        // 单调栈记录的是小于当前高度的最大值的索引
        stack<int> mono_stack;
        for (int i = 0; i < n; ++ i) {
            while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
                mono_stack.pop();
            }
            left[i] = (mono_stack.empty() ? -1 : mono_stack.top());
            mono_stack.push(i);
        }

        mono_stack = stack<int>();
        for (int i = n - 1; i >= 0; -- i) {
            while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
                mono_stack.pop();
            }
            right[i] = (mono_stack.empty() ? n : mono_stack.top());
            mono_stack.push(i);
        }
        
        int ans = 0;
        for (int i = 0; i < n; ++ i) {
            ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
        }
        return ans;
    }
};

/*=============================================辅助栈、辅助队列=============================================*/
/*155. 最小栈*/
/*
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

push(x) —— 将元素 x 推入栈中。
pop() —— 删除栈顶的元素。
top() —— 获取栈顶元素。
getMin() —— 检索栈中的最小元素。
*/
// 辅助栈的技巧
class MinStack {
    stack<int> x_stack;
    stack<int> min_stack;
public:
    MinStack() {
        min_stack.push(INT_MAX);
    }
    
    void push(int x) {
        x_stack.push(x);
        // 最小栈永远只插入当前最小的元素
        min_stack.push(min(min_stack.top(), x));
    }
    
    void pop() {
        x_stack.pop();
        min_stack.pop();
    }
    
    int top() {
        return x_stack.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
};


/*剑指 Offer 59 - II. 队列的最大值*/
class MaxQueue {
public:
    MaxQueue() {

    }
    
    int max_value() {
      if(!max_que.empty())
        return max_que.front();
      return -1;
    }
    
    void push_back(int value) {
      dat_que.push(value);
      while(!max_que.empty() && max_que.back() < value)
        max_que.pop_back();
      max_que.push_back(value);
    }
    
    int pop_front() {
      if(dat_que.empty())
        return -1;
      int res = dat_que.front();
      dat_que.pop();
      if(res == max_que.front())
        max_que.pop_front();
      return res;
    }
private:
  queue<int> dat_que;
  deque<int> max_que;
};
/*========================================================================================================================*/


/*剑指 Offer 09. 用两个栈实现队列*/
class CQueue {
public:
  CQueue() {

  }
  
  // 队列先进先出，s1放先入的元素，如果要先出，就要把s1的元素pop & push进s2就行了
  void appendTail(int value) {
    s1.push(value);
  }
  
  int deleteHead() {
    int to_del = -1;
    if( s2.empty() ) {
      while( !s1.empty() ) {
        to_del = s1.top(); s1.pop();
        s2.push(to_del);
      }
    } 
    if( !s2.empty() ) {
      to_del = s2.top(); s2.pop();
    }
    return to_del;
  }
private:
  stack<int> s1, s2;
};


/*225. 用队列实现栈*/
/*
使用队列实现栈的下列操作：

push(x) -- 元素 x 入栈
pop() -- 移除栈顶元素
top() -- 获取栈顶元素
empty() -- 返回栈是否为空
注意:

你只能使用队列的基本操作-- 也就是 push to back, peek/pop from front, size, 和 is empty 这些操作是合法的。
你所使用的语言也许不支持队列。 你可以使用 list 或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。
你可以假设所有操作都是有效的（例如, 对一个空的栈不会调用 pop 或者 top 操作）。
*/
class MyStack {
public:
    queue<int> queue1;
    queue<int> queue2;

    /** Initialize your data structure here. */
    MyStack() {

    }

    /** Push element x onto stack. */
    void push(int x) {
        queue2.push(x);
        while (!queue1.empty()) {
            queue2.push(queue1.front());
            queue1.pop();
        }
        swap(queue1, queue2);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int r = queue1.front();
        queue1.pop();
        return r;
    }
    
    /** Get the top element. */
    int top() {
        int r = queue1.front();
        return r;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return queue1.empty();
    }
};


/*经典的N皇后*/
// 回溯算法
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        auto solutions = vector<vector<string>>();
        auto queens = vector<int>(n, -1);
        // 三个hash_set记录状态
        auto columns = unordered_set<int>();
        auto diagonals1 = unordered_set<int>();
        auto diagonals2 = unordered_set<int>();
        backtrack(solutions, queens, n, 0, columns, diagonals1, diagonals2);
        return solutions;
    }

    void backtrack(vector<vector<string>> &solutions, vector<int> &queens, int n, int row, unordered_set<int> &columns, unordered_set<int> &diagonals1, unordered_set<int> &diagonals2) {
        if (row == n) {
            vector<string> board = generateBoard(queens, n);
            solutions.push_back(board);
        } else {
            for (int i = 0; i < n; i++) {
                if (columns.find(i) != columns.end()) {
                    continue;
                }
                // 主对角线
                int diagonal1 = row - i;
                if (diagonals1.find(diagonal1) != diagonals1.end()) {
                    continue;
                }
                // 副对角线
                int diagonal2 = row + i;
                if (diagonals2.find(diagonal2) != diagonals2.end()) {
                    continue;
                }
                // 改变状态
                queens[row] = i;
                columns.insert(i);
                diagonals1.insert(diagonal1);
                diagonals2.insert(diagonal2);
                // 回溯
                backtrack(solutions, queens, n, row + 1, columns, diagonals1, diagonals2);
                // 撤回状态
                queens[row] = -1;
                columns.erase(i);
                diagonals1.erase(diagonal1);
                diagonals2.erase(diagonal2);
            }
        }
    }

    vector<string> generateBoard(vector<int> &queens, int n) {
        auto board = vector<string>();
        for (int i = 0; i < n; i++) {
            string row = string(n, '.');
            row[queens[i]] = 'Q';
            board.push_back(row);
        }
        return board;
    }
};


/*698. 划分为k个相等的子集*/
/*
给定一个整数数组  nums 和一个正整数 k，找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。

示例 1：
输入： nums = [4, 3, 2, 3, 5, 2, 1], k = 4
输出： True
说明： 有可能将其分成 4 个子集（5），（1,4），（2,3），（2,3）等于总和。
*/
class Solution {
public:
  bool canPartitionKSubsets(vector<int>& nums, int k) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if(sum % k != 0) return false;
    int target = sum / k;
    sort(nums.begin(), nums.end());
    int idx = nums.size() - 1;
    while(idx >= 0 && nums[idx] == target) {
      idx --; k --;
    }
    vector<int> groups(k, 0);
    return backTracking(groups, nums, idx, target);
  }

  bool backTracking(vector<int>& groups, vector<int>& nums, int idx, int target) {
    if(idx < 0) return true;
    int v = nums[idx --];
    for(int i = 0; i < groups.size(); i ++) {
      if(groups[i] + v <= target) {
        groups[i] += v;
        if(backTracking(groups, nums, idx, target)) return true;
        groups[i] -= v;
      }
      if(groups[i] == 0) break;
    }
    return false;
  }
};