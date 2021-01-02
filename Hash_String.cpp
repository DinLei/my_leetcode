/*220. 存在重复元素 III*/
/*
level: 中等
在整数数组 nums 中，是否存在两个下标 i 和 j，使得 nums [i] 和 nums [j] 的差的绝对值小于等于 t ，且满足 i 和 j 的差的绝对值也小于等于 ķ 。
如果存在则返回 true，不存在返回 false。
*/

// https://leetcode-cn.com/problems/contains-duplicate-iii/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-46/

/****剑指 Offer 48. 最长不含重复字符的子字符串*/
class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    int ans = 0, start = 0, i = 0;
    unordered_map<char, int> idx;
    for(i = 0; i < s.size(); i ++) {
      if(idx.find(s[i]) != idx.end()) {
        ans = max(ans, i - start);
        start = max(start, idx[s[i]] + 1);
      }
      idx[s[i]] = i;
    }
    return max(ans, i - start);
  }
};

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    int ans(0), start(0);
    vector<int> asc96(96, -1);
    for( int i = 0; i < s.size(); i ++ ) {
      int& tmp = asc96[s[i] - ' '];
      if( tmp >= start ) {
        ans = max( ans, i - start );
        start = tmp + 1;
      }
      tmp = i;
    }
    return max( ans, int(s.size()) - start );
  }
};


/*128. 最长连续序列*/
/*
给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
进阶：你可以设计并实现时间复杂度为 O(n) 的解决方案吗？
*/

// hash set做法
class Solution {
public:
  int longestConsecutive(vector<int>& nums) {
    unordered_set<int> set;
    for(auto x: nums) set.insert(x);
    int ans = 0;
    for(auto x: nums) {
      // 技巧：如果有比自己小一点的，那自己不查，让小的去查
      if(set.count(x - 1)) continue;
      int tmp = 1, v = x;
      while(set.count(++ v)) tmp ++;
      ans = max(ans, tmp);
    }
    return ans;
  }
};


/***76. 最小覆盖子串*/
/* 
这道题我也放在了Array_Matrix_Pointer.cpp里面了。
滴滴面试有一种变种: 
现有m种颜色的珠子，一串珠子手链，共n个珠子（n >= m）且这串珠子一定包含所有的颜色，
请找出包含这m个颜色的最小子珠串
*/
/*
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
注意：如果 s 中存在这样的子串，我们保证它是唯一的答案。
*/
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> map(128, 0);
        // 存放目标t需要的字符计数
        for(auto ch : t) ++map[ch];
        // 目标t的字符数量
        int counter = t.size();
        int begin = 0, end = 0;
        int head = 0;
        int len = INT_MAX;
        while(end < s.size()) {
            /* 右边加，当这个字符是滑动窗缺少的字符时，计数器减一 */
            if(map[s[end ++]] -- > 0) 
                -- counter;
            while(counter == 0) {
                if(end - begin < len) {
                    len = end - begin;
                    head = begin;
                }
                /* 左边减，当这个字符是滑动窗不缺也不富余的字符时，计数器加一 */
                if(map[s[begin ++]] ++ == 0) ++ counter;
            }
        }
        return len == INT_MAX ? "" : s.substr(head, len);
    }
};


/*牛课网：字符串变形*/
/*
对于一个给定的字符串，我们需要在线性(也就是O(n))的时间里对它做一些变形。首先这个字符串中包含着一些空格，就像"Hello World"一样，
然后我们要做的是把着个字符串中由空格隔开的单词反序，同时反转每个字符的大小写。比如"Hello World"变形后就变成了"wORLD hELLO"。
*/
class Transform {
public:
  string trans(string s, int n) {
    // write code here
    if(n < 1) return s;
    int p = n - 1;
    string ans;
    for(int i = n - 1; i >= 0; i --) {
      if(s[i] == ' ') {
        for(int j = i + 1; j <= p; j ++) ans += trans(s[j]);
        ans += ' ';
        p = i - 1;
      }
    }
    for(int j = 0; j <= p; j ++) ans += trans(s[j]);
    return ans;
  }
  
  char trans(char ch) {
    if('a' <= ch && ch <= 'z')
      return ch - 'a' + 'A';
    else
      return ch - 'A' + 'a';
  }
};



