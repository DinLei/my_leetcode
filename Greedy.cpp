// 贪心算法
/*135. 分发糖果*/
/*
老师想给孩子们分发糖果，有 N 个孩子站成了一条直线，老师会根据每个孩子的表现，预先给他们评分。

你需要按照以下要求，帮助老师给这些孩子分发糖果：

每个孩子至少分配到 1 个糖果。
相邻的孩子中，评分高的孩子必须获得更多的糖果。
那么这样下来，老师至少需要准备多少颗糖果呢？
*/
class Solution {
public:
  int candy(vector<int>& ratings) {
    int n = ratings.size();
    
    vector<int> left(n, 1);

    for(int i = 1; i < n; i ++) {
      if(ratings[i] > ratings[i - 1]) {
        left[i] = left[i - 1] + 1;
      }
    }

    int count = left[n - 1];
    for(int j = n - 2; j >= 0; j --) {
      if(ratings[j] > ratings[j + 1]) {
        left[j] = max(left[j], left[j + 1] + 1);
      }
      count += left[j];
    }

    return count;
  }
};


/*牛课网：获得更多的奖金*/
/*
小明在越南旅游，参加了当地的娱乐活动。小明运气很好，拿到了大奖， 到了最后的拿奖金环节。小明发现桌子上放着一列红包，每个红包上写着奖金数额。
现在主持人给要求小明在这一列红包之间“切”2刀，将这一列红包“切”成3组，并且第一组的奖金之和等于最后一组奖金和（允许任意一组的红包集合是空）。最终第一组红包的奖金之和就是小明能拿到的总奖金。小明想知道最多能拿到的奖金是多少，你能帮他算算吗。
*/
#include <iostream>
#include <vector>
#include <string>
#include <limits.h>

using namespace std;

typedef long long LL;

LL split(int n, vector<int> nums) {
  if(n <= 1) return 0;
  int i = 0, j = n - 1;
  LL left = nums[i], right = nums[j], ans = 0;
  while(i < j) {
    if(left == right) {
      ans = max(ans, left);
      left += nums[++ i];
      right += nums[-- j];
    }
    else if(left < right)
      left += nums[++ i];
    else
      right += nums[-- j];
  }
  return ans;
}

int main() {
  int n, x;
  cin >> n;
  vector<int> nums;
  while(cin >> x) {
    nums.push_back(x);
  }
  LL ans = split(n, nums);
  cout << ans;
  return 0;
}


/*122. 买卖股票的最佳时机 II*/
/*
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {   
        int ans = 0;
        int n = prices.size();
        for (int i = 1; i < n; ++i) {
            ans += max(0, prices[i] - prices[i - 1]);
        }
        return ans;
    }
};

/*605. 种花问题*
/*
假设你有一个很长的花坛，一部分地块种植了花，另一部分却没有。可是，花卉不能种植在相邻的地块上，它们会争夺水源，两者都会死去。
给定一个花坛（表示为一个数组包含0和1，其中0表示没种植花，1表示种植了花），和一个数 n 。能否在不打破种植规则的情况下种入 n 朵花？能则返回True，不能则返回False。
*/
// 贪心问题找贪心点：比如这里连续3个0在一起，中间的0就能种花。依次遍历下去
class Solution {
public:
  bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    int i = 0, count = 0, size = flowerbed.size();
    while (i < size) {
      if (flowerbed[i] == 0 && (i == 0 || flowerbed[i - 1] == 0) && (i == size - 1 || flowerbed[i + 1] == 0)) {
          flowerbed[i] = 1;
          count++;
      }
      i++;
    }
    return count >= n;
  }
};


/**134. 加油站**/
/*
在一条环路上有 N 个加油站，其中第 i 个加油站有汽油 gas[i] 升。
你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。
如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1。

说明: 

如果题目有解，该答案即为唯一答案。
输入数组均为非空数组，且长度相同。
输入数组中的元素均为非负数。
*/
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int rest = 0, run = 0, start = 0;
    for (int i = 0; i < gas.size(); ++i){
        run += (gas[i] - cost[i]);
        rest += (gas[i] - cost[i]);
        if (run < 0){
            start = i + 1;
            run = 0;
        }
    }
    return rest < 0 ? -1: start;
}

/*加油问题变种*/
/*
一辆汽车加满油后可行驶n公里。旅途中有若干个加油站。设计一个有效算法，指出应
在哪些加油站停靠加油，使沿途加油次数最少。对于给定的n(n <= 5000)和k(k <= 1000)个加油站位置，编程计算最少加油次数。并证明算法能产生一个最优解。
要求：
输入：第一行有2个正整数n和k，表示汽车加满油后可行驶n公里，且旅途中有k个加油站。接下来的1 行中，有k+1 个整数，表示第k个加油站与第k-1 个加油站之间的距离。
第0 个加油站表示出发地，汽车已加满油。第k+1 个加油站表示目的地。
输出：输出编程计算出的最少加油次数。如果无法到达目的地，则输出”NoSolution”。

思路：
汽车行驶过程中，应走到自己能走到并且离自己最远的那个加油站，在那个加油站加油后再按照同样的方法贪心

具体算法：
先检测各加油站之间的距离，若发现其中有一个距离大于汽车加满油能跑的距离，则输出no solution
否则，对加油站间的距离进行逐个扫描，尽量选择往远处走，不能走了就让num++，最终统计出来的num便是最少的加油站数
*/
#include <iostream>
#include <stdio.h>
  
void greedy(int d[], int n, int k) {   
    int num = 0;   
    for(int i = 0; i <= k; i++) {   
        if(d[i] > n) {   
            printf("no solution\n");   
            return;   
        }   
    }   
    for(int i = 0, s = 0; i <= k; i ++) {   
        s += d[i];   
        if(s > n) {   
            num ++;   
            s = d[i];   
        }   
    }   
    printf("%d\n", num);   
}   
       
       
int main() {   
    int i, n, k;   
    int d[1000];   
    scanf("%d %d", &n, &k);   
    for(i = 0; i <= k; i++)   
        scanf("%d", &d[i]);   
    greedy(d, n, k);   
} 


/*55. 跳跃游戏*/
/*
给定一个非负整数数组，你最初位于数组的第一个位置。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
判断你是否能够到达最后一个位置。
*/
class Solution {
public:
  bool canJump(vector<int>& nums) {
    int rightMost = 0, n = nums.size();
    for(int i = 0; i < n; i ++) {
      if(i <= rightMost) {
        rightMost = max(rightMost, i + nums[i]);
        if(rightMost >= n - 1) return true;
      } // else break;
    }
    return false;
  }
};


/*45. 跳跃游戏 II*/
/*
给定一个非负整数数组，你最初位于数组的第一个位置。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
你的目标是使用最少的跳跃次数到达数组的最后一个位置。
*/ 
class Solution {
public:
  int jump(vector<int>& nums) {
    int rightMost = 0, n = nums.size(), end = 0, step = 0;
    for (int i = 0; i < n - 1; ++i) {
      if (i <= rightMost) {
        rightMost = max(rightMost, i + nums[i]);
        // 这里其实是代表至少到达第一个边界肯定没到达第二个边界
        if (i == end) {
          end = rightMost;
          ++ step;
        }
      }
    }
    return step;
  }
};


/*435. 无重叠区间*/
/*
给定一个区间的集合，找到需要移除区间的最小数量，使剩余区间互不重叠。

注意:
  1. 可以认为区间的终点总是大于它的起点。
  2. 区间 [1,2] 和 [2,3] 的边界相互“接触”，但没有相互重叠。
*/
class Solution {
public:
  int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    int n = intervals.size();
    if(n <= 1) return 0;
    sort(intervals.begin(), intervals.end(), [](vector<int>& l1, vector<int>& l2){return l1[1] < l2[1];});
    int total = 0, prev = intervals[0][1];
    for(int i = 1; i < n; i ++) {
      if(intervals[i][0] < prev) 
        total ++;
      else 
        prev = intervals[i][1];
    }
    return total;
  }
};
