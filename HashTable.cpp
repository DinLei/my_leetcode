/*220. 存在重复元素 III*/
/*
level: 中等
在整数数组 nums 中，是否存在两个下标 i 和 j，使得 nums [i] 和 nums [j] 的差的绝对值小于等于 t ，且满足 i 和 j 的差的绝对值也小于等于 ķ 。
如果存在则返回 true，不存在返回 false。
*/

// https://leetcode-cn.com/problems/contains-duplicate-iii/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-46/

/*剑指 Offer 48. 最长不含重复字符的子字符串*/
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