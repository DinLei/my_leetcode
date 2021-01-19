/*==========================算法相关==========================*/
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


// 快速求幂
/*题目：快速求幂，取最后三位*/
// 基础版
// 取模运算法则
/*
(a + b) % p = (a % p + b % p) % p （1）
(a - b) % p = (a % p - b % p) % p （2）
(a * b) % p = (a % p * b % p) % p （3）
*/
long long normalPower(long long base, long long power){
    long long result = 1;
    for(int i = 1; i <= power; i ++){
        result = (result * base) % 1000;
    }
    return result % 1000;
}

// 优化版1
long long fastPower(long long base, long long power) {
    long long result = 1;
    while (power > 0) {
        if (power % 2 == 0) {
            //如果指数为偶数
            power = power / 2;//把指数缩小为一半
            base = base * base % 1000;//底数变大成原来的平方
        } else {
            //如果指数为奇数
            power = power - 1;//把指数减去1，使其变成一个偶数
            result = result * base % 1000;//此时记得要把指数为奇数时分离出来的底数的一次方收集好
            power = power / 2;//此时指数为偶数，可以继续执行操作
            base = base * base % 1000;
        }
    }
    return result;
}

// 优化版2
long long fastPower(long long base, long long power) {
    long long result = 1;
    while (power > 0) {
        if (power % 2 == 1) {
            result = result * base % 1000;
        }
        power = power / 2;
        base = (base * base) % 1000;
    }
    return result;
}

// 优化版3
long long fastPower(long long base, long long power) {
    long long result = 1;
    while (power > 0) {
        if (power & 1) {//此处等价于if(power%2==1)
            result = result * base % 1000;
        }
        power >>= 1;//此处等价于power=power/2
        base = (base * base) % 1000;
    }
    return result;
}


// 蓄水池采样
/*
假设需要采样的数量为 k
首先构建一个可容纳 k 个元素的数组，将序列的前 k 个元素放入数组中。
然后对于第 j（j > k）个元素开始，以 k / j 的概率来决定该元素是否被替换到数组中（数组中的k个元素被替换的概率是相同的）。 
当遍历完所有元素之后，数组中剩下的元素即为所需采取的样本。

证明：
定理：该算法保证每个元素以 k / n 的概率被选入蓄水池数组。

证明：首先，对于任意的 i，第 i 个元素进入蓄水池的概率为 k / i；而在蓄水池内每个元素被替换的概率为 1 / k; 
因此在第 i 轮第j个元素被替换的概率为 (k / i ) * (1 / k) = 1 / i。 接下来用数学归纳法来证明，当循环结束时每个元素进入蓄水池的概率为 k / n.

假设在 (i-1) 次迭代后，任意一个元素进入 蓄水池的概率为 k / (i-1)。有上面的结论，在第 i 次迭代时，该元素被替换的概率为 1 / i， 
那么其不被替换的概率则为 1 - 1/i = (i-1)/i；在第i 此迭代后，该元素在蓄水池内的概率为 k / (i-1) * (i-1)/i = k / i. 归纳部分结束。

因此当循环结束时，每个元素进入蓄水池的概率为 k / n. 命题得证。
*/

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

/** 
 * Reservoir Sampling Algorithm
 * 
 * Description: Randomly choose k elements from n elements ( n usually is large
 *              enough so that the full n elements may not fill into main memory)
 * Parameters:
 *      v - the original array with n elements
 *      n - the length of v
 *      k - the number of choosen elements
 * 
 * Returns:
 *      An array with k elements choosen from v
 *
 * Assert: 
 *      k <= n
 *
 */
vector<int> ReservoirSampling(vector<int> v, int n, int k) {

    assert(v.size() == n && k <= n);

    // init: fill the first k elems into reservoir
    vector<int> reservoirArray(v.begin(), v.begin() + k);

    int i = 0;
    int j = 0;
    // start from the (k+1)th element to replace
    for (i = k; i < n; ++ i) {
        j = rand() % (i + 1); // inclusive range [0, i]
        // 被替换的概率是 1 / i
        if (j < k) {
            reservoirArray[j] = v[i];
        }
    }

    return reservoirArray;
}

int main() {
    vector<int> v(100, 0);
    for (int i = 0; i < 100; ++ i) v[i] = i + 1;

    srand((unsigned int)time(NULL));
    // test algorithm RUN_COUNT times
    const int RUN_COUNT = 10000;
    int cnt[11] = {0};
    for (int k = 1; k <= RUN_COUNT; ++k) {
        cout << "Running Count " << k << endl;

        vector<int> samples = ReservoirSampling(v, 100, 10);

        for (size_t i = 0; i <samples.size(); ++i) {
            cout << samples[i] << " ";
            cnt[samples[i]] ++;
        }
        cout << endl;
    }

    // output frequency stats
    cout << "*************************" << endl;
    cout << "Frequency Stats" << endl;
    for (int num = 1; num < 11; ++ num) {
        cout << num << " : \t" << cnt[num] << endl;
    }
    cout << "*************************" << endl;

    return 0;
}