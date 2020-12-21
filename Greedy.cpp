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