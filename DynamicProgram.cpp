// 动态规划
// 子串是连续的，子序列是不连续的
/***************************************************************************************/

/*5. 最长回文子串*/
/*给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。*/
// 方法一：动态规划
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));
        string ans;
        for (int l = 0; l < n; ++l) {
            for (int i = 0; i + l < n; ++i) {
                int j = i + l;
                if (l == 0) {
                    dp[i][j] = 1;
                } else if (l == 1) {
                    dp[i][j] = (s[i] == s[j]);
                } else {
                    dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);
                }
                if (dp[i][j] && l + 1 > ans.size()) {
                    ans = s.substr(i, l + 1);
                }
            }
        }
        return ans;
    }
};
// 方向二：中心扩展
/**/
/*516. 最长回文子序列*/
int longestPalindromeSubseq(string s) {
    int n = s.size();
    // dp 数组全部初始化为 0
    vector<vector<int>> dp(n, vector<int>(n, 0));
    // base case
    for (int i = 0; i < n; i++)
        dp[i][i] = 1;
    // 反着遍历保证正确的状态转移
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            // 状态转移方程
            if (s[i] == s[j])
                dp[i][j] = dp[i + 1][j - 1] + 2;
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    }
    // 整个 s 的最长回文子串长度
    return dp[0][n - 1];
}

/*72. 编辑距离*/
/*
给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。

你可以对一个单词进行如下三种操作：

插入一个字符
删除一个字符
替换一个字符
*/
class Solution {
public:
    int minDistance(string word1, string word2) {
      int w1Size = word1.size();
      int w2Size = word2.size();

      int dp[w1Size+1][w2Size+1];
      for( int i = 0; i <= w1Size; i++ )
        dp[i][0] = i;
      for( int j = 0; j <= w2Size; j++ )
        dp[0][j] = j;

      for( int i = 1; i <= w1Size; i++ ) {
        for( int j = 1; j <= w2Size; j++ ) {
          if( word1[i-1] == word2[j-1] )
            dp[i][j] = dp[i-1][j-1];
          else {
            // int doReplace = dp[i-1][j-1] + 1;
            // int doInsert  = dp[i][j-1]   + 1;
            // int doDelete  = dp[i-1][j]   + 1; 
            // dp[i][j] = min( doReplace, min( doDelete, doInsert) );
            dp[i][j] = min( dp[i-1][j-1], min( dp[i][j-1], dp[i-1][j]) ) + 1;
          }
        }
      }

      return dp[w1Size][w2Size];
    }
};
/***************************************************************************************/

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

// 方法二: 二分查找。注：二分查找可以返回最长的上升序列
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = 1, n = (int)nums.size();
        if (n == 0) {
            return 0;
        }
        vector<int> d(n + 1, 0);
        d[len] = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] > d[len]) {
                d[++len] = nums[i];
            } else {
                int l = 1, r = len, pos = 0; // 如果找不到说明所有的数都比 nums[i] 大，此时要更新 d[1]，所以这里将 pos 设为 0
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (d[mid] < nums[i]) {
                        pos = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                d[pos + 1] = nums[i];
            }
        }
        return len;
    }
};

/*10. 正则表达式匹配*/
/*
给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。
*/
class Solution {
public:
  bool isMatch(string s, string p) {
    int n1 = s.size(), n2 = p.size();
    if(n1 != 0 && n2 == 0) return false;
    vector< vector<int> > dp(n1 + 1, vector(n2 + 1, 0));
    dp[0][0] = 1;
    auto match = [&s, &p](int i, int j) {
      if(i == 0)
        return false;
      if(p[j - 1] == '.')
        return true;
      return s[i - 1] == p[j - 1];
    };
    for(int i = 0; i <= n1; i ++) {
      for(int j = 1; j <= n2; j ++) {
        if(p[j - 1] == '*') {
          if(match(i, j - 1)) 
            dp[i][j] |= dp[i - 1][j];
          if(j >= 2)
            dp[i][j] |= dp[i][j - 2];
        } else {
          if(match(i, j)) 
            dp[i][j] |= dp[i - 1][j - 1];
        }
      }
    }
    return dp[n1][n2];
  }
};


/***************************************************************************************/
/*53. 最大子数组和*/
/*给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。*/
class Solution {
public:
  int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    // vector<int> dp(n); dp[0] = nums[0];
    // for(int i = 1; i < n; i ++) {
    //   dp[i] = max(nums[i], dp[i - 1] + nums[i]);
    // }
    // return *max_element(dp.begin(), dp.end());
    int ans = nums[0], sum = nums[0];
    for(int i = 1; i < n; i ++) {
      sum = max(nums[i], sum + nums[i]);
      ans = max(ans, sum);
    }
    return ans;
  }
};


/*152. 乘积最大子数组*/
/*给你一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。*/
class Solution {
public:
  int maxProduct(vector<int>& nums) {
    // vector<int> maxF(nums), minF(nums);
    // for(int i = 1; i < nums.size(); i ++) {
    //   maxF[i] = max(maxF[i - 1] * nums[i], max(nums[i], minF[i - 1] * nums[i]));
    //   minF[i] = min(minF[i - 1] * nums[i], min(nums[i], maxF[i - 1] * nums[i]));
    // }
    // return *max_element(maxF.begin(), maxF.end());
    int maxP = nums[0], minP = nums[0], ans = nums[0];
    for(int i = 1; i < nums.size(); i ++) {
      int mx = maxP, mn = minP;
      maxP = max(nums[i], max(nums[i] * mx, nums[i] * mn));
      minP = min(nums[i], min(nums[i] * mx, nums[i] * mn));
      ans = max(ans, maxP);
    }
    return ans;
  }
};
/***************************************************************************************/

/*32. 最长有效括号*/
/*给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。*/
/*我们定义 dp[i] 表示以下标 i 字符结尾的最长有效括号的长度。*/
class Solution {
public:
    int longestValidParentheses(string s) {
        int size = s.length();
        vector<int> dp(size, 0);

        int maxVal = 0;
        for(int i = 1; i < size; i++) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    dp[i] = 2;
                    if (i - 2 >= 0) {
                        dp[i] = dp[i] + dp[i - 2];
                    }
                } else if (dp[i - 1] > 0) {
                    if ((i - dp[i - 1] - 1) >= 0 && s[i - dp[i - 1] - 1] == '(') {
                        dp[i] = dp[i - 1] + 2;
                        if ((i - dp[i - 1] - 2) >= 0) {
                            dp[i] = dp[i] + dp[i - dp[i - 1] - 2];
                        }
                    }
                }
            }
            maxVal = max(maxVal, dp[i]);
        }
        return maxVal;
    }
};


/*120. 三角形最小路径和*/
/*
给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。

相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。
*/
class Solution {
public:
  int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    if(n == 0) return 0;
    vector< vector<int> > dp(n, vector(n, 0)); 
    dp[0][0] = triangle[0][0];
    for(int i = 1; i < n; i ++) {
      dp[i][0] = dp[i - 1][0] + triangle[i][0];
      for(int j = 1; j < i; j++) {
        dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
      }
      dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
    }
    return *min_element(dp[n - 1].begin(), dp[n - 1].end());
  }
};