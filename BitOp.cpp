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
