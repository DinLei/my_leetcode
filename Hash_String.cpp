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


