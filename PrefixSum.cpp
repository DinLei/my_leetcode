// 使用 前缀和 技巧将问题由繁化简
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * @brief 2488. 统计中位数为 K 的子数组
 * 给你一个长度为 n 的数组 nums ，该数组由从 1 到 n 的 不同
 * 整数组成。另给你一个正整数 k 。

 * 统计并返回 nums 中的 中位数 等于 k 的非空子数组的数目。

 * 注意：
 * 数组的中位数是按 递增 顺序排列后位于 中间
 * 的那个元素，如果数组长度为偶数，则中位数是位于中间靠 左 的那个元素。
 * 例如，[2,3,1,4] 的中位数是 2 ，[8,4,3,5,1] 的中位数是 4 。
 * 子数组是数组中的一个连续部分。

 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/count-subarrays-with-median-k
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

// 【大神备注】子数组统计问题常用技巧：等价转换
class Solution {
public:
  int countSubarrays(vector<int> &nums, int k) {
    int kIdx = find(nums.begin(), nums.end(), k) - nums.begin();
    unordered_map<int, int> count{{0, 1}};
    // 奇数：
    // 左小 + 右小 = 左大 + 右大
    // 左小 - 左大 = 右大 - 右小
    // 偶数：(注意审题，偶数的中位数取“中间靠左”！)
    // 左小 + 右小 + self = 左大 + 右大
    // 左小 + 右小 = 左大 + 右大 - 1
    // 左小 - 左大 = 右大 - 右小 - 1
    for (int i = kIdx - 1, x = 0; i >= 0; i--) {
      x += (nums[i] < k) ? 1 : -1;
      count[x]++;
    }
    // count[0] 是 自身 为 一个 子集，自己是自己的中位数
    // count[1] 是 仅有两个元素，且 自身 是 中间靠左
    // 例如：k=1，子数组=[2,1]时，排序后为[1, 2]，1为中位数
    int ans = (count[0] + count[-1]);
    for (int i = kIdx + 1, x = 0; i < nums.size(); i++) {
      x += (nums[i] > k) ? 1 : -1;
      ans += (count[x] + count[x - 1]);
    }
    return ans;
  }
};

// 用数组取代map优化 hash处理的运行速度
class Solution {
public:
  int countSubarrays(vector<int> &nums, int k) {
    int pos = find(nums.begin(), nums.end(), k) - nums.begin();
    int n = nums.size(), cnt[n * 2];
    memset(cnt, 0, sizeof(cnt));
    cnt[n] = 1;
    for (int i = pos - 1, x = n; i >= 0; --i) { // 从 pos-1 开始累加 x
      x += nums[i] < k ? 1 : -1;
      ++cnt[x];
    }

    int ans = cnt[n] + cnt[n - 1];
    for (int i = pos + 1, x = n; i < n; ++i) { // 从 pos+1 开始累加 x
      x += nums[i] > k ? 1 : -1;
      ans += cnt[x] + cnt[x - 1];
    }
    return ans;
  }
};

// 作者：endlesscheng
// 链接：https://leetcode.cn/problems/count-subarrays-with-median-k/solution/deng-jie-zhuan-huan-pythonjavacgo-by-end-5w11/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

/**
 * @brief 面试题 17.05.  字母与数字
 * 给定一个放有字母和数字的数组，找到最长的子数组，且包含的字母和数字的个数相同。
 * 返回该子数组，若存在多个最长子数组，返回左端点下标值最小的子数组。若不存在这样的数组，返回一个空数组。
 * 示例 1:
 * 输入:
 * ["A","1","B","C","D","2","3","4","E","5","F","G","6","7","H","I","J","K","L","M"]
 * 输出: ["A","1","B","C","D","2","3","4","E","5","F","G","6","7"]
 */

// 注意：
// 1. 大神这里的数组代替hash map的做法
// 2. (c >> 6 & 1) * 2 - 1 解释
//    对于任意小写/大写英文字母字符，其 ASCII 码的二进制都形如
//       01xxxxxx
//    对于任意数字字符，其 ASCII 码的二进制都形如
//       0011xxxx

class Solution {
public:
  vector<string> findLongestSubarray(vector<string> &array) {
    int n = array.size(), begin = 0, end = 0, s = n, first[n * 2 + 1];
    memset(first, -1, sizeof(first));
    first[s] = 0; // s[0] = 0
    for (int i = 1; i <= n; ++i) {
      s += (array[i - 1][0] >> 6 & 1) * 2 - 1;
      int j = first[s];
      if (j < 0)
        first[s] = i;
      else if (i - j > end - begin)
        begin = j, end = i;
    }
    return {array.begin() + begin, array.begin() + end};
  }
};

// 作者：endlesscheng
// 链接：https://leetcode.cn/problems/find-longest-subarray-lcci/solution/tao-lu-qian-zhui-he-ha-xi-biao-xiao-chu-3mb11/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。