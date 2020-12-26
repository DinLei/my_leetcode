//DoubleIndex
/*88. 合并两个有序数组*/
/*
给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。

说明：
初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
*/
class Solution {
public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int p1 = m - 1, p2 = n - 1;
    int p = m + n - 1;
    while ( (p1 >= 0) && (p2 >= 0) ) {
      nums1[p --] = (nums1[p1] < nums2[p2]) ? nums2[p2--] : nums1[p1--];
    }
    for(int i = 0; i <= p2; i ++) {
      nums1[i] = nums2[i];
    }
  }
};


/*76. 最小覆盖子串*/
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
            if(map[s[end ++]] -- > 0) -- counter;
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


/*26. 删除排序数组中的重复项*/
/*
给定一个排序数组，你需要在 原地 删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。
不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
*/
/*典型的双指针用法，注意与 189 原地 旋转数组 的方法做对比*/
class Solution {
public:
  int removeDuplicates(vector<int>& nums) {
    if(nums.size() <= 0)
      return 0;
    int i = 0, j = 1, n = nums.size();
    while(++i < n) {
      if(nums[i] != nums[i - 1]) {
        nums[j++] = nums[i];
      }
    }
    return j;
  }
};


/*75. 颜色分类*/
/*
给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

进阶：
你可以不使用代码库中的排序函数来解决这道题吗？
你能想出一个仅使用常数空间的一趟扫描算法吗？
*/
// 三指针：最前面填充0，中间i顺延填充1，最后的位置留给2
class Solution {
public:
  void sortColors(vector<int>& nums) {
    int size = nums.size();
    if(size < 2) return;
    int i = 0, zero = 0, two = size;
    while(i < two) {
      if(nums[i] == 0) swap(nums[zero ++], nums[i ++]);
      else if(nums[i] == 1) i ++;
      else swap(nums[-- two], nums[i]);
    }
  }
};


/*11. 盛最多水的容器*/
/*
给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0) 。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
*/
// 双指针
class Solution {
public:
  int maxArea2(vector<int>& height) {
    int l = 0, r = height.size() - 1;
    int ans = 0;
    while (l < r) {
        int area = min(height[l], height[r]) * (r - l);
        ans = max(ans, area);
        if (height[l] <= height[r]) {
            ++ l;
        } else {
            -- r;
        }
    }
    return ans;
  }
};


/*33. 搜索旋转排序数组*/
// 二分查找，注意区间特性
class Solution {
public:
  int search(vector<int>& nums, int target) {
    int n = nums.size();
    int l = 0, r = n - 1;
    while(l <= r) {
      int m = (l + r) >> 1;
      if(nums[m] == target) return m;
      if(nums[m] >= nums[0]) {
        if(nums[0] <= target && target < nums[m])
          r = m - 1;
        else 
          l = m + 1;
      } else {
        if(nums[m] < target && target <= nums[n - 1])
          l = m + 1;
        else 
          r = m - 1;
      }
    }
    return -1;
  }
};


/*189. 旋转数组*/
/*
给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数
要求使用空间复杂度为 O(1) 的 原地 算法。
*/
// 方法一：使用环状替换
// 注意这里使用count进行计数
class Solution {
public:
  void rotate(vector<int>& nums, int k) {
    int n = nums.size(), count = 0;
    k %= n;
    for(int i = 0; count < n; i ++) {
      int c = i, prev = nums[i];
      do {
        int j = (c + k) % n;
        int curr = nums[j];
        nums[j] = prev;
        prev = curr;
        c = j;
        count ++;
      } while(c != i);
    }
  }
};

// 方法二：使用反转
// 这个方法基于这个事实：当我们旋转数组 k 次， k%n 个尾部元素会被移动到头部，剩下的元素会被向后移动。
class Solution {
public:
  void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k %= n;
    reverse(nums, 0, n - 1);
    reverse(nums, 0, k - 1);
    reverse(nums, k, n - 1);
  }

  void reverse(vector<int>& nums, int start, int end) {
    while(start < end) {
      swap(nums[start ++], nums[end --]);
    }
  }
};


/*=====================构造排列组合并去重==================================================================================================*/
// 15题、16题都是二分查找，最重要的是学习如何对排列组合进行去重复
/*15. 三数之和*/
/*
给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。
*/
class Solution {
public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector< vector<int> > res;
    if(nums.size() < 3)
      return res;
    // 排序是遍历构造组合时的技巧
    sort(nums.begin(), nums.end());
    for(int i = 0; i < nums.size() - 2; i ++) {
      // 剪枝
      if(nums[i] > 0) return res;
      // 开始的时候，若是连着的两个相同，取后面的
      if(i > 0 && nums[i] == nums[i - 1])
        continue;
      int t = -1 * nums[i];
      int l = i + 1, r = nums.size() - 1;
      while(l < r) {
        // 寻找的时候，若是连着的两个相同，跳过
        if(l > i + 1 && nums[l] == nums[l - 1]) {
          l ++;
          continue;
        }  
        if(nums[l] + nums[r] > t)
          r --;
        else if(nums[l] + nums[r] < t)
          l ++;
        else {
          res.push_back({nums[i], nums[l], nums[r]});
          // 去重逻辑应该放在找到一个三元组之后
          while (r > l && nums[r] == nums[r - 1]) r --;
          while (r > l && nums[l] == nums[l + 1]) l ++;
          l ++; r --;
        }
      }
    }
    return res;
  }
};


/*16. 最接近的三数之和*/
/*
给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。
*/
class Solution {
public:
  int threeSumClosest(vector<int>& nums, int target) {
    long ans = INT_MAX;
    sort(nums.begin(), nums.end());

    // 根据差值的绝对值来更新答案
    auto update = [&](long cur) {
      if (abs(cur - target) < abs(ans - target)) {
        ans = cur;
      }
    };

    for(int i = 0; i < nums.size() - 2; i ++) {
      if(i > 0 && nums[i] == nums[i - 1])
        continue ;
      int l = i + 1, r = nums.size() - 1;
      while(l < r) {
        int sum3 = nums[i] + nums[l] + nums[r];
        if(sum3 == target)
          return target;
        update(sum3);
        if(sum3 < target) {
          while(l < r && nums[l] == nums[l + 1]) l ++;
          l ++;
        } else {
          while(r > l && nums[r] == nums[r - 1]) r --;
          r --;
        }
      }
    }
    return ans;
  }
};


/*46. 全排列*/
/*给定一个 没有重复 数字的序列，返回其所有可能的全排列。*/
class Solution {
public:
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    backtrace(res, nums, 0, (int)nums.size());
    return res;
  }

  void backtrace(vector<vector<int>>& res, vector<int>& nums, int first, int len) {
    if(first == len) {
      res.push_back(nums);
      return ;
    }
    for(int i = first; i < len; i ++) {
      swap(nums[first], nums[i]);
      backtrace(res, nums, first + 1, len);
      swap(nums[first], nums[i]);
    }
  }
};


/*47. 全排列 II*/
/*给定一个可包含重复数字的序列 nums，按任意顺序 返回所有不重复的全排列。*/
class Solution {
private:
vector<vector<int>> res;
vector<int> perm;
vector<int> visit;

public:
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    visit.resize(nums.size(), 0);
    sort(nums.begin(), nums.end());
    backTracking(nums, 0, nums.size());
    return res;
  }

  void backTracking(vector<int>& nums, int idx, int len) {
    if(idx == len) {
      res.push_back(perm); return;
    }
    for(int i = 0; i < len; i ++) {
      if(i > 0 && nums[i] == nums[i - 1] && !visit[i - 1]) continue;
      // 初始值是0，如果=0说明是第一次用到它
      if(!visit[i]) {
        visit[i] = 1;
        perm.push_back(nums[i]);
        backTracking(nums, idx + 1, len);
        visit[i] = 0;
        perm.pop_back();
      }
    }
  }
};

/*31. 下一个排列*/
/*
实现获取 下一个排列 的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。
如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。
必须 原地 修改，只允许使用额外常数空间。
*/
class Solution {
public:
  // 3 5 2 4 7 1 6 8
  void nextPermutation(vector<int>& nums) {
    int i = nums.size() - 2;
    // 从后往前找到第一个升序对
    while(i >= 0 && nums[i] >= nums[i + 1]) i --;
    if(i >= 0) {
      int j = nums.size() - 1;
      // 在 [i+1, end) 里找到比 nums[i] 大的 最小的数
      while(j >= 0 && nums[i] >= nums[j]) j --;
      swap(nums[i], nums[j]);
    }
    // [i+1, end) 做成正序 保证当前组合最小
    reverse(nums.begin() + i + 1, nums.end());
  }
};

/*============================================================================================================================================*/


/*【算法系列】-开根号*/
// 方法一: 二分查找法
double sqrt1(double num){   
    if(num < 0) {
      return -1;
    }
    double last = 0.0, low = 0;
    double mid;
    double up = (num >= 1 ? num : 1); 
    mid = (low + up) / 2; 
    do {
      if(mid * mid > num) {
        up = mid;
      } else {
        low = mid;
      }
      last = mid;
      mid = (up + low) / 2;        
    } while(abs(mid - last) > 1e-5);
  
    return mid;   
}

// 方法二: 牛顿迭代法
double sqrt2(double num) {
  if(num < 0) {
      return -1;
  }
  double a = 2;
  double b = num / a;
  while(abs(a - b) > 1e-5) {
      a = (a + b) / 2;
      b = num / a;
  }
  return a;
}

/*=========================================================================================================================================*/


/*剑指 Offer 29. 顺时针打印矩阵*/
/*输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。*/
class Solution {
public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int nrow = matrix.size();
    if(nrow == 0) return vector<int>();
    int ncol = matrix[0].size();
    if(ncol == 0) return vector<int>();
    int t = 0, b = nrow - 1, l = 0, r = ncol - 1, x = 0;
    vector<int> ans(nrow * ncol);
    while(1) {
      // 从左往右
      for(int i = l; i <= r; i ++) ans[x ++] = matrix[t][i];
      // 最上层遍历完，下移
      if(++ t > b) break;

      // 从上往下
      for(int i = t; i <= b; i ++) ans[x ++] = matrix[i][r];
      // 最右侧遍历完，左移
      if(l > -- r) break;

      // 从右往左
      for(int i = r; i >= l; i --) ans[x ++] = matrix[b][i];
      // 最下层遍历完，上移
      if(t > -- b) break;

      // 从下往上
      for(int i = b; i >= t; i --) ans[x ++] = matrix[i][l];
      // 最左侧遍历完，右移
      if(++ l > r) break;
    }
    return ans;
  }
};


/*41. 缺失的第一个正数 (287.寻找重复数 也用到了这一题的技巧，原地判重)*/
/*给你一个未排序的整数数组，请你找出其中没有出现的最小的正整数。*/
//对于一个长度为 N 的数组，其中没有出现的最小正整数只能在 [1, N+1] 中。这是因为如果 [1, N] 都出现了，那么答案是 N+1，否则答案是 [1, N] 中没有出现的最小正整数
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int& num: nums) {
            if (num <= 0) {
                num = n + 1;
            }
        }
        for (int i = 0; i < n; ++i) {
            int num = abs(nums[i]);
            if (num <= n) {
                nums[num - 1] = -abs(nums[num - 1]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0) {
                return i + 1;
            }
        }
        return n + 1;
    }
};


/*287.寻找重复数*/
/*给定一个包含 n + 1 个整数的数组 nums，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。假设只有一个重复的整数，找出这个重复的数。*/
class Solution {
public:
  int findDuplicate(vector<int>& nums) {
    for(int i = 0; i < nums.size(); i ++) {
      int x = abs(nums[i]);
      if(nums[x - 1] < 0)
        return x;
      else
        nums[x - 1] = -abs(nums[x - 1]);
    }
    return -1;
  }
};

// 方法二：置换
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[nums[i] - 1], nums[i]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;
    }
};


/***209. 长度最小的子数组*/
/*
给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。
*/
class Solution {
public:
  int minSubArrayLen(int s, vector<int>& nums) {
    int sum = 0, i = 0, ans = INT_MAX;
    for( int j = 0; j < nums.size(); j ++ ) {
      sum += nums[j];
      while( i <= j && sum >= s ) {
        ans = min( ans, (j - i + 1));
        sum -= nums[i];
        i ++;
      }
    }
    return (ans == INT_MAX) ? 0 : ans;
  }
};


/*166. 分数到小数*/
/*
给定两个整数，分别表示分数的分子 numerator 和分母 denominator，以 字符串形式返回小数 。
如果小数部分为循环小数，则将循环的部分括在括号内。
如果存在多个答案，只需返回 任意一个 。
对于所有给定的输入，保证 答案字符串的长度小于 104 。
*/
// 这道题目的关键用到一个数学定理：一个分数不是有限小数，就是无限循环小数
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) {
            return "0";
        }

        string res;
        bool isNegative = false;
        if (numerator > 0 && denominator < 0 || numerator < 0 && denominator > 0) {
            isNegative = true;
        }

        long num = labs(numerator);
        long denom = labs(denominator);
        long remainder = num;
        if (num >= denom) {
            remainder = num % denom;
            res += to_string(num / denom);
        }

        if (remainder == 0) {
            return isNegative ? "-" + res : res;
        }

        // No intergral part, put 0 in front
        if (remainder == labs(num)) {
            res += "0";
        }

        res += ".";
        unordered_map<int, int> rem2Pos;
        int index = res.size();

       // Loop until find recuring remainder not recuring digits in quotient 
        while (remainder && !rem2Pos.count(remainder)) {
            rem2Pos[remainder] = index++;
            // 技巧，小数部分的递归除法操作细节
            remainder *= 10;
            int digit = remainder / denom;
            remainder = remainder % denom;
            res += to_string(digit);
        }

        if (rem2Pos.count(remainder)) {
            res.insert(rem2Pos[remainder], "(");
            res.push_back(')');
        }

        return isNegative ? "-" + res : res;
    }
};

// 作者：jyj407
// 链接：https://leetcode-cn.com/problems/fraction-to-recurring-decimal/solution/zhong-gui-zhong-ju-xi-jie-kao-cha-ti-by-jyj407/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。


/*842. 将数组拆分成斐波那契序列*/
/*
给定一个数字字符串 S，比如 S = "123456579"，我们可以将它分成斐波那契式的序列 [123, 456, 579]。

形式上，斐波那契式序列是一个非负整数列表 F，且满足：

0 <= F[i] <= 2^31 - 1，（也就是说，每个整数都符合 32 位有符号整数类型）；
F.length >= 3；
对于所有的0 <= i < F.length - 2，都有 F[i] + F[i+1] = F[i+2] 成立。
另外，请注意，将字符串拆分成小块时，每个块的数字一定不要以零开头，除非这个块是数字 0 本身。

返回从 S 拆分出来的任意一组斐波那契式的序列块，如果不能拆分则返回 []。
*/
class Solution {
private:
  vector<int> ans;
public:
  vector<int> splitIntoFibonacci(string S) {
    backTracking(S, 0, 0, 0);
    return ans;
  }

  bool backTracking(string S, int idx, long long sum, long long prev) {
    if(idx >= S.size()) {
      return ans.size() >= 3;
    }
    long long curr = 0;
    for(int i = idx; i < S.size(); i ++) {
      // 可以是0本身，即 S[idx]=0, 但要排除0开头
      if(i > idx && S[idx] == '0') break;
      curr = curr * 10 + (S[i] - '0');
      // curr 需要等于前两个数的和
      if(curr > INT_MAX) break;
      if(ans.size() >= 2) {
        if(sum > curr) continue;
        else if(sum < curr) break;
      }
      ans.push_back(curr);
      if(backTracking(S, i + 1, prev + curr, curr)) 
        return true;
      ans.pop_back();
    }
    return false;
  }
};
