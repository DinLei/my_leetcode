// bit

/*136. 只出现一次的数字*/
/*
给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

说明：
你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？
*/
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ret = 0;
        for (auto e: nums) ret ^= e;
        return ret;
    }
};


/*剑指 Offer 15. 二进制中1的个数*/
class Solution {
public:
  // int hammingWeight(uint32_t n) {
  //   int sum = 0;
  //   while(n) {
  //     sum += (n & 1);
  //     n >>= 1;
  //   }
  //   return sum;
  // }

  int hammingWeight(uint32_t n) {
    int sum = 0;
    while( n ) {
      sum += 1;
      // n &= n - 1 ： 消去数字 n 最右边的 1 。
      n &= (n - 1);
    }
    return sum;
  }
};


/*134. 加油站*/
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