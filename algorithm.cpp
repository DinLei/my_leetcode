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