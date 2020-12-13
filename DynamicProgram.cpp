// 动态规划
/*
376. 摆动序列
level: 中等
如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为摆动序列。第一个差（如果存在的话）可能是正数或负数。少于两个元素的序列也是摆动序列。
*/
// 摆动序列分解成 向上摆动 + 向下摆动
class Solution {
public:
  int wiggleMaxLength(vector<int>& nums) {
    int down = 1, up = 1;
    for (int i = 1; i < nums.size(); i++) {
      if (nums[i] > nums[i - 1])
        up = down + 1;	// 冗余: max(up, down + 1);
      else if (nums[i] < nums[i - 1])
        down = up + 1;	// 冗余: max(down, up + 1);
    }
    return nums.size() == 0 ? 0 : max(down, up);
  }
};

/*
300. 最长上升子序列
level: 中等
给定一个无序的整数数组，找到其中最长上升子序列的长度。
*/
// 方法一: 动态规划
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n=(int)nums.size();
        if (n == 0) return 0;
        vector<int> dp(n, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};

// 方法二: 二分查找