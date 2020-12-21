//DoubleIndex
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
            ++l;
        } else {
            --r;
        }
    }
    return ans;
  }

  int maxArea(vector<int>& height) {
    
    int l = 0, r = height.size()-1;
    int hl = height[l];
    int hr = height[r];
    int ans = (r - l) * min(hl, hr);

    while( l < r ) {
      while( hl <= hr && l < r  ) {
        ++ l;
        if( height[l] > hl ) {
          hl = height[l];
          ans = max( ans, (r - l) * min(hl, hr) );
        }
      }
      ans = max( ans, (r - l) * hr );
      // cout << "1# ans: " << ans << ", r: " << r << ", l: " << l << ", h: " << hr << endl;

      while( hr < hl && l < r  ) {
        -- r;
        if( height[r] > hr ) {
          hr = height[r];
          ans = max( ans, (r - l) * min(hl, hr) );
        }
      }
      ans = max( ans, (r - l) * hl );

      // cout << "2# ans: " << ans << ", r: " << r << ", l: " << l << ", h: " << hl << endl;
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

