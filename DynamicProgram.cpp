// 动态规划
// 字符串相关的动态规划往往构建二维表进行递推
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
        // 这里通过显示定义距离l进行遍历控制
        for (int l = 0; l < n; ++ l) {
            for (int i = 0; i + l < n; ++ i) {
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
class Solution {
public:
  string longestPalindrome(string s) {
    int n = s.size();
    if(n <= 1) return s;
    else if(n == 2) return s[0] == s[1] ? s : s.substr(0, 1);
    int maxLen = -1, l, r;
    for(int i = 0; i < n; i ++) {
      int x = i - 1, y = i;
      while(x >= 0 && y < n && s[x] == s[y]) {
        x --; y ++;
      }
      ++ x; -- y;
      if(y - x > maxLen) {
        maxLen = y - x;
        l = x; r = y;
      }
      x = i - 1, y = i + 1;
      while(x >= 0 && y < n && s[x] == s[y]) {
        x --; y ++;
      }
      ++ x; -- y;
      if(y - x > maxLen) {
        maxLen = y - x;
        l = x; r = y;
      }
    }
    // cout << l << ", " << r << endl;
    return s.substr(l, maxLen + 1);
  }
};


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

/*1143. 最长公共子序列*/
/*
给定两个字符串 text1 和 text2，返回这两个字符串的最长公共子序列的长度。

一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。两个字符串的「公共子序列」是这两个字符串所共同拥有的子序列。

若这两个字符串没有公共子序列，则返回 0。
*/
class Solution {
public:
  int longestCommonSubsequence(string text1, string text2) {
    int n1 = text1.size(), n2 = text2.size();
    vector< vector<int> > dp(n1 + 1, vector(n2 + 1, 0));
    for(int i = 1; i <= n1; i ++) {
      for(int j = 1; j <= n2; j ++) {
        // printf("c1 = %c, c2 = %c\n", text1[i], text2[j]);
        if(text1[i - 1] == text2[j - 1])
          dp[i][j] = dp[i - 1][j - 1] + 1;
        else 
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        // printf("i = %d, j = %d, dp = %d\n", i, j, dp[i][j]);
      }
    }
    return dp[n1][n2];
  }
};


/**牛课网：最长公共子串*/
class Solution {
public:
    /**
     * longest common substring
     * @param str1 string字符串 the string
     * @param str2 string字符串 the string
     * @return string字符串
     */
    string LCS(string str1, string str2) {
        // write code here
        int len1 = str1.size();
        int len2 = str2.size();
        if(!len1 || !len2) return "-1";
        vector<int> dp(len2 + 1, 0);
        int start = 0;
        int last = 0;
        int maxNum = INT_MIN;
        for(int i = 1; i <= len1; i ++){
            last = 0; //  上一对字符匹配时候最长子串长度
            for(int j = 1; j <= len2; j ++){
                int tmp = dp[j];
                if(str1[i - 1] == str2[j - 1]){
                    dp[j] = last + 1;
                }
                else dp[j] = 0;
                last = tmp;
                if(maxNum < dp[j]){
                    start = i;
                    maxNum = dp[j];
                }
            }
        }
        if(maxNum == 0) return "-1";
        return str1.substr(start - maxNum, maxNum);
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
                int l = 1, r = len, pos = 0;  // 如果找不到说明所有的数都比 nums[i] 大，此时要更新 d[1]，所以这里将 pos 设为 0
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (d[mid] < nums[i]) {   // 目标：找到比nums[i]小的最大的数
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

/*674. 最长连续递增序列*/
/*给定一个未经排序的整数数组，找到最长且 连续递增的子序列，并返回该序列的长度。*/
class Solution {
public:
  int findLengthOfLCIS(vector<int>& nums) {
    int n = nums.size();
    if(n == 0) return 0;
    // vector<int> dp(n, 1);
    int dp = 1, ans = 1;
    for(int i = 1; i < n; i ++) {
      if(nums[i] > nums[i - 1]) {
        // dp[i] = dp[i - 1] + 1;
        dp += 1;
        // ans = max(dp[i], ans);
        ans = max(ans, dp);
      } else {
        dp = 1;
      }
    }
    return ans;
  }
};


/*673. 最长递增子序列的个数*/
/*
给定一个未排序的整数数组，找到最长递增子序列的个数。
*/
class Solution {
public:
  int findNumberOfLIS(vector<int>& nums) {

    int n = nums.size();
    if(n <= 0) return n;

    vector<int> dp(n, 1);
    vector<int> count(n, 1);

    for(int i = 1; i < n; i ++) {
      for(int j = 0; j < i; j ++) {
        if(nums[j] < nums[i]) {
          // 第一次找到
          if(dp[j] + 1 > dp[i]) {
            dp[i] = dp[j] + 1;
            count[i] = count[j];
          // 再次找到
          } else if(dp[j] + 1 == dp[i]) {
            count[i] += count[j];
          }
        }
      }
    }
    // 最后的返回值应该是所有最大长度的所有count的总和
    int max = *max_element(dp.begin(), dp.end());
    int res = 0;
    for(int i=0; i < n; i ++) {
      if(dp[i] == max) res += count[i];
    }

    return res;
  }
};


// 从Hash_String中拷贝过来，与上面的题做对比
/**128. 最长连续序列*/
/*
快手真题
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
      while(set.count(++ v)) ++ tmp;
      ans = max(ans, tmp);
    }
    return ans;
  }
};


/***************************************************************************************/

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
    // 我们用 f[i][j] 表示 s 的前 i 个字符与 p 中的前 j 个字符是否能够匹配
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
        // 当前字符串是 *
        if(p[j - 1] == '*') {
          // 和 * 前面的 字符 比较，如果匹配上，* 号做重复匹配用
          if(match(i, j - 1)) 
            dp[i][j] |= dp[i - 1][j];
          // 和 * 前面字符，取 前面的前面 的状态
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

/*44. 通配符匹配*/
/*
给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。

'?' 可以匹配任何单个字符。
'*' 可以匹配任意字符串（包括空字符串）。
两个字符串完全匹配才算匹配成功。

说明:
s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母，以及字符 ? 和 *。
*/
class Solution {
public:
  bool isMatch(string s, string p) {
    int n = s.size(), m = p.size();
    vector< vector<int> > dp(n + 1, vector(m + 1, 0) );
    dp[0][0] = 1;
    // 从0索引开始，连续的*号
    for(int i = 1; i <= m; i ++) {
      if(p[i - 1] == '*') dp[0][i] = true;
      else break;
    }
    for(int i = 1; i <= n; i ++) {
      for(int j = 1; j <= m; j ++) {
        if(p[j - 1] == '*')
          dp[i][j] = dp[i - 1][j] | dp[i][j - 1];
        else if(p[j - 1] == '?' || s[i - 1] == p[j - 1])
          dp[i][j] |= dp[i - 1][j - 1];
      }
    }
    return dp[n][m];
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


/**85. 最大矩形*/
/*给定一个仅包含 0 和 1 、大小为 rows x cols 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。*/
class Solution {
public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    int m = matrix.size();
    if(m == 0) return 0;
    int n = matrix[0].size();
    if(n == 0) return 0;
    int ans = 0;
    vector< vector<int> > dp(m, vector<int>(n, 0));

    for(int i = 0; i < m; i ++) {
      for(int j = 0; j < n; j ++) {
        if(matrix[i][j] == '1')
          dp[i][j] = (j == 0) ? 1 : dp[i][j - 1] + 1;
          int width = dp[i][j];
          for(int k = i; k >= 0; k --) {
            width = min(width, dp[k][j]);
            ans = max(ans, width * (i - k + 1));
          }
      }
    }
    return ans;
  }
};


/**221. 最大正方形*/
/*
在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1' 的最大正方形，并返回其面积。
*/
class Solution {
public:
  int maximalSquare(vector<vector<char>>& matrix) {
    // write code here
    int nrow = matrix.size();
    if(nrow == 0) return 0;
    int ncol = matrix[0].size();
    if(ncol == 0) return 0;
    int maxSide = 0;
    vector< vector<int> > dp(nrow, vector<int>(ncol, 0));

    for(int i = 0; i < nrow; i ++) {
      for(int j = 0; j < ncol; j ++) {
        if(matrix[i][j] == '1') {
          if(i == 0 || j == 0)
            dp[i][j] = 1;
          else {
            dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
          }
          maxSide = max(maxSide, dp[i][j]);
        }
      }
    }
    return maxSide * maxSide;
  }
};


// 32、91、offer46，注意状态的跳转 //
/***32. 最长有效括号*/
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
                    // s[i−dp[i−1]−1] 与 当前i的对称位置
                    if ((i - dp[i - 1] - 1) >= 0 && s[i - dp[i - 1] - 1] == '(') {
                        dp[i] = dp[i - 1] + 2;
                        // 值得注意的是，i - dp[i - 1] - 1i−dp[i−1]−1 和 ii 组成了有效括号对，这将是一段独立的有效括号序列，
                        // 如果之前的子序列是形如 (...)(...) 这种序列，那么当前位置的最长有效括号长度还需要加上这一段。所以：
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


/*91. 解码方法*/
/*
一条包含字母 A-Z 的消息通过以下方式进行了编码：
'A' -> 1
'B' -> 2
...
'Z' -> 26
给定一个只包含数字的非空字符串，请计算解码方法的总数。
题目数据保证答案肯定是一个 32 位的整数。
*/
int numDecodings(string s) {
    if (s[0] == '0') return 0;
    int pre = 1, curr = 1;//dp[-1] = dp[0] = 1
    for (int i = 1; i < s.size(); i++) {
        int tmp = curr;
        if (s[i] == '0')
            if (s[i - 1] == '1' || s[i - 1] == '2') curr = pre;
            else return 0;
        else if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] <= '6'))
            curr = curr + pre;
        pre = tmp;
    }
    return curr;
}

/*剑指 Offer 46. 把数字翻译成字符串*/
/*
给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成 “z”。一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。
*/
class Solution {
public:
  int translateNum(int num) {
    if(num == 0) return 1;
    int pre = 1, curr = 1;
    int lastNum = num % 10, currNum;
    num /= 10;
    while(num > 0) {
      currNum = num % 10;
      int tmp = curr;
      if(currNum == 1 || (currNum == 2 && lastNum <= 5))
        curr += pre;
      pre = tmp;
      lastNum = currNum;
      num /= 10;
    }
    return curr;
  }
};

/**121. 买卖股票的最佳时机*/
/*
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。

注意：你不能在买入股票前卖出股票。
*/
class Solution {
public:
  int maxProfit(vector<int>& prices) {
    if(prices.size() <= 1)
      return 0;
    int ans = 0, minVal = prices[0];
    for( int i = 1; i < prices.size(); i ++ ) {
      if( prices[i] < minVal ) {
        minVal = prices[i];
      } else {
        ans = max(ans, prices[i] - minVal);
      }
    }
    return ans;
  }
};

/*122. 买卖股票的最佳时机 II*/
/*
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int dp[n][2];
        dp[0][0] = 0, dp[0][1] = -prices[0];
        for (int i = 1; i < n; ++i) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        }
        return dp[n - 1][0];
    }
};
// 优化版
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int dp0 = 0, dp1 = -prices[0];
        for (int i = 1; i < n; ++i) {
            int newDp0 = max(dp0, dp1 + prices[i]);
            int newDp1 = max(dp1, dp0 - prices[i]);
            dp0 = newDp0;
            dp1 = newDp1;
        }
        return dp0;
    }
};


/*123. 买卖股票的最佳时机 III*/
/*
给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。
注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
*/
class Solution {
public:
  int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector< vector< vector<int> > > dp(n, vector(3, vector(2, 0)));
    dp[0][0][0] = 0;
    dp[0][0][1] = -prices[0];
    dp[0][1][0] = 0;
    dp[0][1][1] = -prices[0];
    dp[0][2][0] = 0;
    dp[0][2][1] = -prices[0];
    for(int i = 1; i < n; i ++) {
      dp[i][0][0] = dp[i - 1][0][0];

      dp[i][0][1] = max(-prices[i] + dp[i - 1][0][0], dp[i - 1][0][1]);
      dp[i][1][0] = max(prices[i] + dp[i - 1][0][1], dp[i - 1][1][0]);

      dp[i][1][1] = max(-prices[i] + dp[i - 1][1][0], dp[i - 1][1][1]);
      dp[i][2][0] = max(prices[i] + dp[i - 1][1][1], dp[i - 1][2][0]);
    }
    int a = dp[n - 1][0][0], b = dp[n - 1][1][0];
    return max(dp[n - 1][2][0], max(a, b));
  }
};


/*213. 打家劫舍 II*/
/*
你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。
给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，能够偷窃到的最高金额。
*/
class Solution {
public:
  int rob(vector<int>& nums) {
    int n = nums.size();
    if(n < 1) return 0;
    if(n == 1) return nums[0];
    if(n > 1 && n <= 3) return max(nums[0], nums[1]);
    return max(maxOneRound(nums, 0, n - 1), maxOneRound(nums, 1, n));
  }

  int maxOneRound(vector<int>& nums, int s, int e) {
    int first = nums[s], second = max(nums[s], nums[s + 1]), tmp;
    for(int i = s + 2; i < e; i ++) {
      tmp = second;
      second = max(second, first + nums[i]);
      first = tmp;
    }
    return second;
  }
};


/*279. 完全平方数*/
/*
给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。
*/
class Solution {
public:
  int numSquares(int n) {
    // dp[i] 定义为 构成 第i个数 最少需要的完全平方数
    vector<int> dp(n + 1, 0);
    for(int i = 1; i <= n; i ++) {
      // 最多有 i 个 1
      dp[i] = i;
      for(int j = 1; i - j * j >= 0; j ++) 
        dp[i] = min(dp[i], dp[i - j * j] + 1);
    }
    return dp[n];
  }
};


/*746. 使用最小花费爬楼梯*/
/*
数组的每个索引作为一个阶梯，第 i个阶梯对应着一个非负数的体力花费值 cost[i](索引从0开始)。
每当你爬上一个阶梯你都要花费对应的体力花费值，然后你可以选择继续爬一个阶梯或者爬两个阶梯。
您需要找到达到楼层顶部的最低花费。在开始时，你可以选择从索引为 0 或 1 的元素作为初始阶梯。
*/
class Solution {
public:
  int minCostClimbingStairs(vector<int>& cost) {
    vector<int> dp(cost.size());
    dp[0] = cost[0];
    dp[1] = cost[1];
    for (int i = 2; i < cost.size(); i++) {
      dp[i] = min(dp[i - 2], dp[i - 1]) + cost[i];
    }
    return min(dp[cost.size() - 2], dp[cost.size() - 1]);
  }
};

// 优化版
class Solution {
public:
  int minCostClimbingStairs(vector<int>& cost) {
    for (int i = 2; i < cost.size(); i++) {
      cost[i] = min(cost[i - 2], cost[i - 1]) + cost[i];
    }
    return min(cost[cost.size() - 2], cost[cost.size() - 1]);
  }
};


/*63. 不同路径 II*/
/*
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
网格中的障碍物和空位置分别用 1 和 0 来表示。
*/
//memo[i][j]的含义是：到达x = i, y = j的路径数目
void initMemo(vector<vector<int>>& obstacleGrid, vector<vector<int>>& memo)
{
    int row = obstacleGrid.size(), column = obstacleGrid[0].size();
    memo[0][0] = 1;

    //处理首行、首列的格子
    for(int j = 1; j < column; j++){ //处理首行
        if(!obstacleGrid[0][j]) //可到达
            memo[0][j] = memo[0][j - 1];
        else
            memo[0][j] = 0;
    }
    for(int i = 1; i < row; i++){ //处理首列
        if(!obstacleGrid[i][0]) //可到达
            memo[i][0] = memo[i - 1][0];
        else    
            memo[i][0] = 0;    
    }

    //处理非首行、非首列的格子
    for(int i = 1; i < row; i++){
        for(int j = 1; j < column; j++){
            if(!obstacleGrid[i][j]) //可到达
                memo[i][j] = memo[i - 1][j] + memo[i][j - 1]; 
            else    
                memo[i][j] = 0;    
        }
    }
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    if(obstacleGrid[0][0]) //起点是障碍，无路可走
        return 0;

    int row = obstacleGrid.size(), column = obstacleGrid[0].size();
    vector<vector<int> > memo(row, vector<int>(column, 0));
    //memo[i][j]的含义是：到达x = i, y = j的路径数目
    initMemo(obstacleGrid, memo);

    return memo[row - 1][column - 1]; 
}

//优化版: 滚动数组思想压缩空间复杂度
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int row = obstacleGrid.size(), column = obstacleGrid[0].size();
    // 因为每次递推都是由左至右、由上至下
    // 所以只要一维数组就够了（当前i的值为同一列上一行的值，i-1的值为同一行左边的值）
    vector<int> memo(column, 0);
    memo[0] = (obstacleGrid[0][0] == 0);

    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            if(obstacleGrid[i][j]){   // 有障碍
                memo[j] = 0;
                continue;
            }
            if(j >= 1)
                memo[j] += memo[j - 1];
        }
    }
    return memo[column - 1];
}


/*==================================背包问题======================================================*/
/**322. 零钱兑换*/
/*
给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。
你可以认为每种硬币的数量是无限的。
*/
// 完全背包问题
// 自下而上
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int Max = amount + 1;
        vector<int> dp(amount + 1, Max);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int j = 0; j < (int)coins.size(); ++j) {
                if (coins[j] <= i) {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
// 自上而下
class Solution {
    vector<int>count;
    int dp(vector<int>& coins, int rem) {
        if (rem < 0) return -1;
        if (rem == 0) return 0;
        if (count[rem - 1] != 0) return count[rem - 1];
        int Min = INT_MAX;
        for (int coin: coins) {
            int res = dp(coins, rem - coin);
            if (res >= 0 && res < Min) {
                Min = res + 1;
            }
        }
        count[rem - 1] = (Min == INT_MAX) ? -1 : Min;
        return count[rem - 1];
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount < 1) return 0;
        count.resize(amount);
        return dp(coins, amount);
    }
};


/*983. 最低票价*/
/*
在一个火车旅行很受欢迎的国度，你提前一年计划了一些火车旅行。在接下来的一年里，你要旅行的日子将以一个名为 days 的数组给出。每一项是一个从 1 到 365 的整数。

火车票有三种不同的销售方式：

一张为期一天的通行证售价为 costs[0] 美元；
一张为期七天的通行证售价为 costs[1] 美元；
一张为期三十天的通行证售价为 costs[2] 美元。
通行证允许数天无限制的旅行。 例如，如果我们在第 2 天获得一张为期 7 天的通行证，那么我们可以连着旅行 7 天：第 2 天、第 3 天、第 4 天、第 5 天、第 6 天、第 7 天和第 8 天。

返回你想要完成在给定的列表 days 中列出的每一天的旅行所需要的最低消费。
*/
// 通过 深度递归+内存记忆 来实现的
class Solution {
private:
  unordered_set<int> dayset;
  vector<int> memo;
public:
  int mincostTickets(vector<int>& days, vector<int>& costs) {
    memo.resize(366, -1); memo[0] = 0;
    for(auto x: days) dayset.insert(x);
    return dp(1, costs);
  }

  int dp(int start, vector<int>& costs) {
    if(start > 365) return 0;
    if(memo[start] >= 0) return memo[start];
    if(dayset.count(start)) 
      memo[start] = min(dp(start + 1, costs) + costs[0], 
                        min(dp(start + 7, costs) + costs[1],
                            dp(start + 30, costs) + costs[2]));
    else 
      memo[start] = dp(start + 1, costs);
    return memo[start];
  }
};


/**416. 分割等和子集*/
/*
给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

注意:
每个数组中的元素不会超过 100
数组的大小不会超过 200、
*/
// 动态规划除了明显递推关系式以外，还有背包问题：目标是多少，从已有的元素里能填充多少，是否填完、填完用料最少等
class Solution {
public:
  bool canPartition(vector<int>& nums) {
    int n = nums.size();
    if(n < 2) return false;
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if(sum & 1) return false;
    int target = sum / 2;
    int maxEle = *max_element(nums.begin(), nums.end());
    if(maxEle > target) return false;
    vector< vector<int> > dp(n, vector<int>(target + 1, 0));
    for(int i = 0; i < n; i ++) dp[i][0] = 1;
    for(int i = 1; i < n; i ++) {
      for(int j = target; j >= 0; j --) {
        if(j >= nums[i]) {
          dp[i][j] = dp[i - 1][j] | dp[i - 1][j - nums[i]];
        } else {
          dp[i][j] = dp[i - 1][j];
        }
      }
    }
    return dp[n - 1][target];
  }
};



/*494. 目标和*/
/*
给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。
返回可以使最终数组和为目标数 S 的所有添加符号的方法数。
*/
/*
1. 弄懂题意
第一步需要根据题意考虑输出的结构，在【416.分割等和子集】这道题中，要求的输出结果就是boolean值，因此我们定义的dp数组只需要记录T/F即可，但是这道题要求返回结果是方法数，那么我们dp数组需要记录的数据就是具体的方法数。

2. 定义状态
搞清楚需要输出的结果后，就可以来想办法画一个表格，也就是定义dp数组的含义。根据背包问题的经验，可以将dp[ i ][ j ]定义为从数组nums中 0 - i 的元素进行加减可以得到 j 的方法数量。

3. 状态转移方程
搞清楚状态以后，我们就可以根据状态去考虑如何根据子问题的转移从而得到整体的解。这道题的关键不是nums[i]的选与不选，而是nums[i]是加还是减，那么我们就可以将方程定义为：

dp[ i ][ j - nums[ i ] ] += dp[ i - 1 ][ j ]
dp[ i ][ j + nums[ i ] ] += dp[ i - 1 ][ j ]
可以理解为nums[i]这个元素我可以执行加，还可以执行减，那么我dp[i][j]可以向两个方向进行扩展。

4. 打表格，dp数组的定义
一般背包问题的定义都是dp[len][t+1]，这里的第二维根据题意需要变成2*t+1
*/
class Solution {
private:
  int ans;
public:
  int findTargetSumWays(vector<int>& nums, int S) {
    int n = nums.size();
    int range = accumulate(nums.begin(), nums.end(), 0);
    if(S > range) return 0;
    // 本题范围: [-range ~ 0 ~ range]
    vector< vector<int> > dp(n, vector<int>(2 * range + 1, 0));
    // 初始状态: (0, -nums[0]) 和 (0, nums[0])
    dp[0][range - nums[0]] = 1;
    dp[0][range + nums[0]] += 1;   // 这里 +=1 是 为了防止 nums[0]=0
    // 状态转移: 从父节点转移到两个子节点
    for(int i = 1; i < n; i ++) {
      for(int sum = -range; sum <= range; sum ++) {
        // 这个判断要求状态必须由合法的位置转移过去
        // 也就是从中间向两边扩散
        if(dp[i - 1][sum + range] > 0) {
          dp[i][sum + nums[i] + range] += dp[i - 1][sum + range];
          dp[i][sum - nums[i] + range] += dp[i - 1][sum + range];
        }
          // dp[i][sum] = dp[i - 1][sum + nums[i - 1] + range] + dp[i - 1][sum + nums[i + 1] + range];
      }
    }
    return dp[n - 1][range + S];
  }
};

/**剑指 Offer 14- I. 剪绳子*/
/*解法见Array_Matrix_Pointer.cpp*/
//{}

/*leetcode-1024 特别题：1024. 视频拼接*/
/*
你将会获得一系列视频片段，这些片段来自于一项持续时长为 T 秒的体育赛事。这些片段可能有所重叠，也可能长度不一。
视频片段 clips[i] 都用区间进行表示：开始于 clips[i][0] 并于 clips[i][1] 结束。我们甚至可以对这些片段自由地再剪辑，例如片段 [0, 7] 可以剪切成 [0, 1] + [1, 3] + [3, 7] 三部分。
我们需要将这些片段进行再剪辑，并将剪辑后的内容拼接成覆盖整个运动过程的片段（[0, T]）。返回所需片段的最小数目，如果无法完成该任务，则返回 -1 。
*/
/*
思路及解法：
比较容易想到的方法是动态规划，我们令 dp[i] 表示将区间 [0,i) 覆盖所需的最少子区间的数量。由于我们希望子区间的数目尽可能少，
因此可以将所有 dp[i] 的初始值设为一个大整数，并将 dp[0]（即空区间）的初始值设为 0。
我们可以枚举所有的子区间来依次计算出所有的 dp 值。我们首先枚举 i，同时对于任意一个子区间 [aj, bj)，若其满足 aj < i <= bj，
那么它就可以覆盖区间 [0, i) 的后半部分，而前半部分则可以用 dp[aj]对应的最优方法进行覆盖，因此我们可以用 dp[aj] + 1 来更新 dp[i]
*/
class Solution {
public:
  int videoStitching(vector<vector<int>>& clips, int T) {
    vector<int> dp(T + 1, INT_MAX - 1);
    dp[0] = 0;
    for(int i = 1; i <= T; i ++) {
      for(auto& x: clips) {
        if(x[0] < i && i <= x[1])
          dp[i] = min(dp[i], dp[x[0]] + 1);
      }
    } 
    return dp[T] == INT_MAX - 1 ? -1 : dp[T];
  }
};