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
    if( !deq.empty() && deq.front() == i-k )
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
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n), right(n);
        
        stack<int> mono_stack;
        for (int i = 0; i < n; ++i) {
            while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
                mono_stack.pop();
            }
            left[i] = (mono_stack.empty() ? -1 : mono_stack.top());
            mono_stack.push(i);
        }

        mono_stack = stack<int>();
        for (int i = n - 1; i >= 0; --i) {
            while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
                mono_stack.pop();
            }
            right[i] = (mono_stack.empty() ? n : mono_stack.top());
            mono_stack.push(i);
        }
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
        }
        return ans;
    }
};


/*155. 最小栈*/
/*
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

push(x) —— 将元素 x 推入栈中。
pop() —— 删除栈顶的元素。
top() —— 获取栈顶元素。
getMin() —— 检索栈中的最小元素。
*/
class MinStack {
    stack<int> x_stack;
    stack<int> min_stack;
public:
    MinStack() {
        min_stack.push(INT_MAX);
    }
    
    void push(int x) {
        x_stack.push(x);
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


/*剑指 Offer 09. 用两个栈实现队列*/
class CQueue {
public:
  CQueue() {

  }
  
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