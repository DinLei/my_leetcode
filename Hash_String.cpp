#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/****剑指 Offer 48. 最长不含重复字符的子字符串*/
class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    int ans = 0, start = 0, i = 0;
    unordered_map<char, int> idx;
    for (; i < s.size(); i++) {
      if (idx.find(s[i]) != idx.end()) {
        ans = max(ans, i - start);
        start = max(start, idx[s[i]] + 1);
      }
      idx[s[i]] = i;
    }
    return max(ans, i - start);
  }
};

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    int ans(0), start(0);
    vector<int> asc96(96, -1);
    for (int i = 0; i < s.size(); i++) {
      int &tmp = asc96[s[i] - ' '];
      if (tmp >= start) {
        ans = max(ans, i - start);
        start = tmp + 1;
      }
      tmp = i;
    }
    return max(ans, int(s.size()) - start);
  }
};

/*128. 最长连续序列*/
/*
给定一个未排序的整数数组 nums
，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
进阶：你可以设计并实现时间复杂度为 O(n) 的解决方案吗？
*/

// hash set做法
class Solution {
public:
  int longestConsecutive(vector<int> &nums) {
    unordered_set<int> set;
    for (auto x : nums)
      set.insert(x);
    int ans = 0;
    for (auto x : nums) {
      // 技巧：如果有比自己小一点的，那自己不查，让小的去查
      if (set.count(x - 1))
        continue;
      int tmp = 1, v = x;
      while (set.count(++v))
        ++tmp;
      ans = max(ans, tmp);
    }
    return ans;
  }
};

/***76. 最小覆盖子串*/
/*
这道题我也放在了Array_Matrix_Pointer.cpp里面了。
滴滴面试有一种变种:
现有m种颜色的珠子，一串珠子手链，共n个珠子（n >=
m）且这串珠子一定包含所有的颜色， 请找出包含这m个颜色的最小子珠串
*/
/*
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s
中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。 注意：如果 s
中存在这样的子串，我们保证它是唯一的答案。
*/
class Solution {
public:
  string minWindow(string s, string t) {
    vector<int> map(128, 0);
    // 存放目标t需要的字符计数
    for (auto ch : t)
      ++map[ch];
    // 目标t的字符数量
    int counter = t.size();
    int begin = 0, end = 0;
    int head = 0;
    int len = INT_MAX;
    while (end < s.size()) {
      /* 右边加，当这个字符是滑动窗缺少的字符时，计数器减一 */
      if (map[s[end++]]-- > 0)
        --counter;
      while (counter == 0) {
        if (end - begin < len) {
          len = end - begin;
          head = begin;
        }
        /* 左边减，当这个字符是滑动窗不缺也不富余的字符时，计数器加一 */
        if (map[s[begin++]]++ == 0)
          ++counter;
      }
    }
    return len == INT_MAX ? "" : s.substr(head, len);
  }
};

/*牛课网：字符串变形*/
/*
对于一个给定的字符串，我们需要在线性(也就是O(n))的时间里对它做一些变形。首先这个字符串中包含着一些空格，就像"Hello
World"一样，
然后我们要做的是把着个字符串中由空格隔开的单词反序，同时反转每个字符的大小写。比如"Hello
World"变形后就变成了"wORLD hELLO"。
*/
class Transform {
public:
  string trans(string s, int n) {
    // write code here
    if (n < 1)
      return s;
    int p = n - 1;
    string ans;
    for (int i = n - 1; i >= 0; i--) {
      if (s[i] == ' ') {
        for (int j = i + 1; j <= p; j++)
          ans += trans(s[j]);
        ans += ' ';
        p = i - 1;
      }
    }
    for (int j = 0; j <= p; j++)
      ans += trans(s[j]);
    return ans;
  }

  char trans(char ch) {
    if ('a' <= ch && ch <= 'z')
      return ch - 'a' + 'A';
    else
      return ch - 'A' + 'a';
  }
};

/*
剑指 Offer 05. 替换空格
输入：s = "We are happy."
输出："We%20are%20happy."
*/
class Solution {
public:
  string replaceSpace(string s) {
    int len1 = s.length() - 1;
    for (int i = 0; i <= len1; i++) {
      if (s[i] == ' ') {
        s += "00";
      }
    }
    int len2 = s.length() - 1;
    if (len2 <= len1) {
      return s;
    }
    for (int i = len1; i >= 0; i--) {
      char c = s[i];
      if (c == ' ') {
        s[len2--] = '0';
        s[len2--] = '2';
        s[len2--] = '%';
      } else {
        s[len2--] = c;
      }
    }
    return s;
  }
};

// 分割题，对比 Array_Matrix_Pointer.cpp 里的 ‘842. 将数组拆分成斐波那契序列’
/*131. 分割回文串
给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。

返回 s 所有可能的分割方案。
*/
class Solution {
private:
  vector<vector<string>> ans;
  vector<string> path;

public:
  vector<vector<string>> partition(string s) {
    backTracking(s, 0);
    return ans;
  }

  void backTracking(string s, int s_idx) {
    if (s_idx >= s.size()) {
      ans.push_back(path);
      return;
    }
    for (int i = s_idx; i < s.size(); i++) {
      if (isPalindrome(s, s_idx, i)) {
        path.push_back(s.substr(s_idx, i - s_idx + 1));
      } else {
        continue;
      }
      backTracking(s, i + 1);
      path.pop_back();
    }
  }

  bool isPalindrome(string &s, int i, int j) {
    while (i < j) {
      if (s[i] != s[j])
        return false;
      i++;
      j--;
    }
    return true;
  }
};

/*牛课网：表达式求值
请写一个整数计算器，支持加减乘三种运算和括号。（中缀表达式计算）*/
/*
算法
1. 用栈保存各部分计算的和
2. 遍历表达式
3. 遇到数字时继续遍历求这个完整的数字的值
4. 遇到左括号时递归求这个括号里面的表达式的值
5.
遇到运算符时或者到表达式末尾时，就去计算上一个运算符并把计算结果push进栈，然后保存新的运算符
  a. 如果是+，不要计算，push进去
  b. 如果是-，push进去负的当前数
  c. 如果是×、÷，pop出一个运算数和当前数作计算
6. 最后把栈中的结果求和即可
*/
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   * 返回表达式的值
   * @param s string字符串 待计算的表达式
   * @return int整型
   */
  int solve(string s) {
    // write code here
    stack<int> stk;
    int sum = 0, number = 0, n = s.size();
    char sign = '+';
    for (int i = 0; i < n; i++) {
      char c = s[i];
      if (c == '(') {
        int j = i + 1;
        int countPar = 1;
        while (countPar > 0) {
          if (s[j] == '(')
            countPar++;
          if (s[j] == ')')
            countPar--;
          j++;
        }
        number = solve(s.substr(i + 1, j - i - 1));
        i = j - 1;
      }
      if (isdigit(c)) {
        number = number * 10 + c - '0';
      }
      if (!isdigit(c) || i == n - 1) {
        if (sign == '+')
          stk.push(number);
        else if (sign == '-')
          stk.push(-1 * number);
        else if (sign == '*') {
          int a = stk.top();
          stk.pop();
          stk.push(a * number);
        } else if (sign == '/') {
          int a = stk.top();
          stk.pop();
          stk.push(a / number);
        }
        number = 0;
        sign = c;
      }
    }
    while (!stk.empty()) {
      sum += stk.top();
      stk.pop();
    }
    return sum;
  }
};

/*数据结构基础知识：前缀表达式 转换 后缀表达式*/
#include <iostream>
#include <stack>
using namespace std;

/*
 根据中缀表达式 构造后缀表达式

 规则：从左到右开始扫描中缀表达式
  1. 遇到数字， 直接输出
  2. 遇到运算符
    a. 若为“(” 直接入栈
    b. 若为“)” 将符号栈中的元素依次出栈并输出, 直到 “(“, “(“只出栈, 不输出
    c. 若为其他符号, 将符号栈中的元素依次出栈并输出,
 直到遇到比当前符号优先级更低的符号或者”(“。 将当前符号入栈。
  3. 扫描完后, 将栈中剩余符号依次输出
*/

int isp(const char opt) {
  switch (opt) {
  case '#':
    return 0;
  case '(':
    return 1;
  case '+':
  case '-':
    return 3;
  case '*':
  case '/':
  case '%':
    return 5;
  case ')':
    return 6;
  default:
    return -1;
  }
}

void postfix_exp(string &infix, string &postfix) {
  stack<char> stk;
  int ind = 0, len = infix.length();
  if (len <= ind)
    return;
  char *tokens;
  while (ind < len) {
    char ch = infix.at(ind++);
    if (ch == ' ')
      continue;
    else if (isdigit(ch) || ch == '.' || (ch == '-' && ind == 0)) {
      postfix += ch;
    } else {
      if (ch == ')') {
        while (stk.top() != '(') {
          postfix += ' ';
          postfix += stk.top();
          stk.pop();
        }
        stk.pop();
      } else {
        while (!stk.empty() && ch != '(' && isp(stk.top()) >= isp(ch)) {
          postfix += ' ';
          postfix += stk.top();
          stk.pop();
        }
        if (ch != '(')
          postfix += ' ';
        stk.push(ch);
      }
    }
  }

  while (!stk.empty()) {
    postfix += ' ';
    postfix += stk.top();
    stk.pop();
  }
}

int main() {

  string infix1 = "1.2 + 2 * 3 * (4 + 5 * 6) * 7";
  cout << "中缀表达式: " << infix1 << endl;

  string postfix1;
  postfix_exp(infix1, postfix1);

  cout << "后缀表达式: " << postfix1 << endl;
  return 0;
}

/*6. Z 字形变换*/
/*
将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。
比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：
L   C   I   R
E T O E S I I G
E   D   H   N
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："LCIRETOESIIGEDHN"。
*/
class Solution {
public:
  string convert(string s, int numRows) {
    if (numRows == 1)
      return s;
    vector<string> tokens(numRows);
    int idx = 0, direc = 1;
    for (auto ch : s) {
      tokens[idx].push_back(ch);
      idx += direc;
      if (idx == 0 || idx == numRows - 1)
        direc *= -1;
    }
    string ans;
    for (int i = 0; i < numRows; i++)
      ans += tokens[i];
    return ans;
  }
};

/*28. 实现 strStr()*/
/*
实现 strStr() 函数。

给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle
字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。
*/
// 方法一：滑动窗口
// 时间复杂度：最坏时间复杂度为 O((N - L)L)，最优时间复杂度为 O(N)。
class Solution {
public:
  int strStr(string haystack, string needle) {
    int sl = haystack.size(), tl = needle.size();
    if (tl == 0)
      return 0;
    for (int i = 0; i < sl - tl + 1; i++) {
      if (haystack[i] == needle[0]) {
        int j = 1;
        while (j < tl && haystack[i + j] == needle[j])
          j++;
        if (j == tl)
          return i;
      }
    }
    return -1;
  }
};

// 方法二： Rabin Karp - 常数复杂度
class Solution {
public:
  int strStr(string haystack, string needle) {
    int sl = haystack.size(), tl = needle.size();
    if (tl > sl)
      return -1;
    int b = 26;
    // 设置数值上限可以用取模的方式，即用 h % modulus 来代替原本的哈希值。
    // 2^{31}
    long mod = 2 << 30;
    long h = 0, ref_h = 0;
    for (int i = 0; i < tl; i++) {
      h = (h * b + haystack[i] - 'a') % mod;
      ref_h = (ref_h * b + needle[i] - 'a') % mod;
    }
    if (h == ref_h)
      return 0;
    long bL = 1;
    for (int i = 1; i <= tl; i++)
      bL = (bL * b) % mod;
    for (int i = 1; i < sl - tl + 1; i++) {
      // 滚动哈希：常数时间生成哈希码
      h = (h * b - (haystack[i - 1] - 'a') * bL + haystack[i + tl - 1] - 'a') %
          mod;
      if (h == ref_h)
        return i;
    }
    return -1;
  }
};