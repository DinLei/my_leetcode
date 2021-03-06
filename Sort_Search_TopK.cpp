// 排序：
// 其余更一般的排序算法：https://www.runoob.com/w3cnote/ten-sorting-algorithm.html 
/*分桶排序*/
class Solution {
public:
  vector<int> sortArray(vector<int>& nums) {
    int min_val = 500001, max_val = -500001, idx = 0;
    for(auto x: nums) {
      min_val = min(min_val, x);
      max_val = max(max_val, x);
    }
    vector<int> bins(max_val - min_val + 1, 0);
    for(auto x: nums) {
      bins[x - min_val] ++;
    }
    for(int x = min_val; x <= max_val; x ++) {
      int c = bins[x - min_val];
      while(c -- > 0) {
        nums[idx ++] = x;
      }
    }
    return nums;
  }
};

/*归并排序*/
class Solution {
    vector<int> tmp;
    void mergeSort(vector<int>& nums, int l, int r) {
        if (l >= r) return;
        int mid = (l + r) >> 1;
        mergeSort(nums, l, mid);
        mergeSort(nums, mid + 1, r);
        int i = l, j = mid + 1;
        int cnt = 0;
        while (i <= mid && j <= r) {
            if (nums[i] < nums[j]) {
                tmp[cnt++] = nums[i++];
            }
            else {
                tmp[cnt++] = nums[j++];
            }
        }
        while (i <= mid) {
            tmp[cnt++] = nums[i++];
        }
        while (j <= r) {
            tmp[cnt++] = nums[j++];
        }
        for (int i = 0; i < r - l + 1; ++i) {
            nums[i + l] = tmp[i];
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        tmp.resize((int)nums.size(), 0);
        mergeSort(nums, 0, (int)nums.size() - 1);
        return nums;
    }
};

/*快速排序1*/
class Solution {
    int partition(vector<int>& nums, int l, int r) {
        int pivot = nums[r];
        int i = l - 1;
        for (int j = l; j <= r - 1; ++j) {
            if (nums[j] <= pivot) {
                i = i + 1;
                swap(nums[i], nums[j]);
            }
        }
        swap(nums[i + 1], nums[r]);
        return i + 1;
    }
    int randomized_partition(vector<int>& nums, int l, int r) {
        int i = rand() % (r - l + 1) + l; // 随机选一个作为我们的主元
        swap(nums[r], nums[i]);
        return partition(nums, l, r);
    }
    void randomized_quicksort(vector<int>& nums, int l, int r) {
        if (l < r) {
            int pos = randomized_partition(nums, l, r);
            randomized_quicksort(nums, l, pos - 1);
            randomized_quicksort(nums, pos + 1, r);
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        srand((unsigned)time(NULL));
        randomized_quicksort(nums, 0, (int)nums.size() - 1);
        return nums;
    }
};
/*快速排序2*/
class Solution {
  void quicksort(vector<int>& nums, int l, int r) {
    if(l < r) {
      int pivot = nums[l], i = l, j = r;
      while(i < j) {
        while(i < j && nums[j] >= pivot) j --;
        if(i < j) nums[i ++] = nums[j];
        while(i < j && nums[i] < pivot) i ++;
        if(i < j) nums[j --] = nums[i];
      }
      nums[i] = pivot;
      quicksort(nums, l, i - 1);
      quicksort(nums, i + 1, r);
    }
  }
public:
  vector<int> sortArray(vector<int>& nums) {
    quicksort(nums, 0, nums.size() - 1);
    return nums;
  }
};

/*堆排序*/
class Solution {
    void maxHeapify(vector<int>& nums, int i, int len) {
        for (; (i << 1) + 1 <= len;) {
            int lson = (i << 1) + 1;
            int rson = (i << 1) + 2;
            int large;
            if (lson <= len && nums[lson] > nums[i]) {
                large = lson;
            } else {
                large = i;
            }
            if (rson <= len && nums[rson] > nums[large]) {
                large = rson;
            }
            if (large != i) {
                swap(nums[i], nums[large]);
                i = large;
            } else {
                break;
            }
        }
    }
    void buildMaxHeap(vector<int>& nums, int len) {
        for (int i = len / 2; i >= 0; --i) {
            maxHeapify(nums, i, len);
        }
    }
    void heapSort(vector<int>& nums) {
        int len = (int)nums.size() - 1;
        buildMaxHeap(nums, len);
        for (int i = len; i >= 1; --i) {
            swap(nums[i], nums[0]);
            len -= 1;
            maxHeapify(nums, 0, len);
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        heapSort(nums);
        return nums;
    }
};

/*===============================================================================*/

// 分治
/***4. 寻找两个正序数组的中位数*/
class Solution {
public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();

    if( n1 > n2 ) 
      return findMedianSortedArrays(nums2, nums1);

    if( n1 == 0 ) 
      return (n2 % 2 != 0) ? nums2[n2 / 2] : (nums2[n2 / 2 - 1] + nums2[n2 / 2]) / 2.0;

    int low = 0, up = n1;

    while( low <= up ) {
      // 如果总个数是偶数，那左右两边一样多；如果是奇数，那左边要多一个，那一个即为中位数
      int lp1 = (low + up) / 2;           // 数组1 左边的元素个数
      int lp2 = (n1 + n2 + 1) / 2 - lp1;    // 数组2 左边的元素个数

      int L1 = (lp1 == 0) ? INT_MIN : nums1[lp1 - 1];
      int R1 = (lp1 == n1) ? INT_MAX : nums1[lp1];
      int L2 = (lp2 == 0) ? INT_MIN : nums2[lp2 - 1];
      int R2 = (lp2 == n2) ? INT_MAX : nums2[lp2];

      if( L1 > R2 )
        up = lp1 - 1;
      else if( L2 > R1 )
        low = lp1 + 1;
      else 
        return ((n1 + n2) % 2 == 0) ? (max(L1, L2) + min(R1, R2)) / 2.0 : max(L1, L2);
    }
    return 0;
  }
};


/*找两个有序数组的第K小元素*/
class Solution {
public:
    int findKthElm(vector<int>& nums1, vector<int>& nums2, int k){
        assert(1 <= k && k <= nums1.size() + nums2.size());
        int le = max(0, int(k - nums2.size())), ri = min(k, int(nums1.size()));
        while(le < ri){ 
            // m 是 数组1 的 右半部分 的 第一个数，也就是左边部分元素的个数
            int m = (le + ri) >> 1;
            // k - m - 1 就是 数组2 的 左半部分 的 最后一个数
            if(nums2[k - m - 1] > nums1[m]) le = m + 1;
            else ri = m;
        }//循环结束时的位置le即为所求位置，第k小即为max(nums1[le-1]),nums2[k-le-1])，但是由于le可以为0、k,所以
        //le-1或者k-le-1可能不存在所以下面单独判断下
        int nums1LeftMax = (le == 0) ? INT_MIN : nums1[le - 1];
        int nums2LeftMax = (le == k) ? INT_MIN : nums2[k -le - 1];
        return max(nums1LeftMax, nums2LeftMax);
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n=nums1.size() + nums2.size();
        if(n & 1) {//两个数组长度和为奇数
            return findKthElm(nums1, nums2, (n>>1) + 1);
        } else {//为偶数
            return (findKthElm(nums1, nums2, n>>1) + findKthElm(nums1, nums2, (n>>1) + 1)) / 2.0;
        }
    }
};


/*剑指 Offer 40. 最小的k个数*/
/*改变说法: 给定数组和一个数m，求该数组中与m最近的k个数，这道题用堆也可以*/
class Solution {
public:
  vector<int> getLeastNumbers(vector<int>& arr, int k) {
    int n = arr.size();
    if(k == 0) return {};
    if(n == 0 || n <= k) return arr;
    divide(arr, 0, n - 1, k);
    vector<int> ans(k);
    for(int i = 0; i < k; i ++) ans[i] = arr[i];
    return ans;
  }

  int divide(vector<int>& arr, int l, int r, int k) {
    if(l == r) return l;
    int pivot = arr[l], i = l, j = r;
    while(i < j) {
      while(i < j && arr[j] >= pivot) j --;
      if(i < j) arr[i ++] = arr[j];
      while(i < j && arr[i] < pivot) i ++;
      if(i < j) arr[j --] = arr[i];
    } 
    arr[i] = pivot;
    int order = i - l + 1;
    if(order == k) return i;
    else if(order > k) return divide(arr, l, i - 1, k);
    else return divide(arr, i + 1, r, k - order);
  }
};

// 堆的作法
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int>vec(k, 0);
        if (k == 0) { // 排除 0 的情况
            return vec;
        }
        priority_queue<int> Q;
        for (int i = 0; i < k; ++i) {
            Q.push(arr[i]);
        }
        for (int i = k; i < (int)arr.size(); ++i) {
            if (Q.top() > arr[i]) {
                Q.pop();
                Q.push(arr[i]);
            }
        }
        for (int i = 0; i < k; ++i) {
            vec[i] = Q.top();
            Q.pop();
        }
        return vec;
    }
};


/****215. 数组中的第K个最大元素*/
/*在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。*/
// 分治的解法
class Solution {
public:
  int findKthLargest(vector<int>& nums, int k) {
    int n = nums.size();
    return find(nums, 0, n - 1, n - k + 1);
  }

  int find(vector<int>& nums, int l, int r, int k) {
    if(l == r) return nums[l];
    int pivot = nums[l];
    int i = l, j = r;
    while(i < j) {
      while(i < j && nums[j] >= pivot) j --;
      if(i < j) nums[i ++] = nums[j];
      while(i < j && nums[i] < pivot) i ++;
      if(i < j) nums[j --] = nums[i];
    }
    nums[i] = pivot; 
    int order = i - l + 1;
    if(order == k) return pivot;
    else if(order > k) return find(nums, l, i - 1, k);
    else return find(nums, i + 1, r, k - order);
  }
};

// 第k大的数，用大顶堆解法
class Solution {
public:
    void maxHeapify(vector<int>& a, int i, int heapSize) {
        int l = i * 2 + 1, r = i * 2 + 2, largest = i;
        if (l < heapSize && a[l] > a[largest]) {
            largest = l;
        } 
        if (r < heapSize && a[r] > a[largest]) {
            largest = r;
        }
        if (largest != i) {
            swap(a[i], a[largest]);
            maxHeapify(a, largest, heapSize);
        }
    }

    void buildMaxHeap(vector<int>& a, int heapSize) {
        for (int i = heapSize / 2; i >= 0; --i) {
            maxHeapify(a, i, heapSize);
        } 
    }

    int findKthLargest(vector<int>& nums, int k) {
        int heapSize = nums.size();
        buildMaxHeap(nums, heapSize);
        for (int i = heapSize - 1; i >= heapSize - k + 1; -- i) {
            swap(nums[0], nums[i]);
            -- heapSize;
            maxHeapify(nums, 0, heapSize);
        }
        return nums[0];
    }
};


/*
给定一个规则的list, 形如山峰（满足单峰，且峰值点有可能在端点）：[1,3,9,10,8,6,2]，可能存在重复值
请写出程序，返回第k大的数，
不使用内置排序程序
*/
class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
        int idx = searchPeakIndex(nums);
        int i = idx - 1, j = idx + 1, c = 1;
        vector<int> ans; ans.push_back(nums[idx]);
        while(i >= 0 && j <= nums.size() && c <= k) {
        	if(nums[i] > nums[j]) {
        		ans.push_back(nums[i]);
        		ans.push_back(nums[j]);
        	} else {
        		ans.push_back(nums[j]);
        		ans.push_back(nums[i]);
        	}
        	c += 2;
        }
        return ans[k - 1];
    }

    int searchPeakIndex(vector<int>& nums) {
    	int l = 0, r = nums.size() - 1;
    	if(nums[l] > nums[l + 1])
    		return l;
    	else if(nums[r] > nums[r - 1])
    		return r;
    	while(l <= r) {
    		int pivot = (l + r) >> 2;
    		if(nums[pivot - 1] < nums[pivot] && nums[pivot] > nums[pivot + 1])
    			return pivot;
    		if(nums[pivot - 1] < nums[pivot] && nums[pivot] < nums[pivot + 1])
    			l = pivot + 1;
    		else if((nums[pivot - 1] > nums[pivot] && nums[pivot] > nums[pivot + 1]))
    			r = pivot - 1;
    	}
    	return -1;
    }
};


/*347. 前 K 个高频元素*/
/*
给定一个非空的整数数组，返回其中出现频率前 k 高的元素。
*/
class Solution {
public:
    static bool cmp(pair<int, int>& m, pair<int, int>& n) {
        return m.second > n.second;
    }

    struct cmp2 {
    bool operator()(pair<int, int>& m, pair<int, int>& n) {
        return m.second > n.second;
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> occurrences;
        for (auto& v : nums) {
            occurrences[v]++;
        }

        // pair 的第一个元素代表数组的值，第二个元素代表了该值出现的次数
        // priority_queue<pair<int, int>, vector<pair<int, int>>, cmp2> q;
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)> q(cmp);
        for (auto& [num, count] : occurrences) {
            if (q.size() == k) {
                if (q.top().second < count) {
                    q.pop();
                    q.emplace(num, count);  // push
                }
            } else {
                q.emplace(num, count);
            }
        }
        vector<int> ret;
        while (!q.empty()) {
            ret.emplace_back(q.top().first);
            q.pop();
        }
        return ret;
    }
};


/*440. 字典序的第K小数字*/
/*
给定整数 n 和 k，找到 1 到 n 中字典序第 k 小的数字。
注意：1 ≤ k ≤ n ≤ 109。
*/
class Solution {
public:
  long getCount(long prefix, long n) {
    long curr = prefix;
    long next = curr + 1;
    long count = 0;
    // 数值字典树的层节点统计方法
    while( curr <= n ) {
      count += min(n + 1, next) - curr;
      // printf("curr=%d, next=%d, a_count=%d, t_count=%d\n", curr, next, min(n+1, next) - curr, count);
      curr *= 10;
      next *= 10;
    }
    return count;
  }

  int findKthNumber(int n, int k) {
    long pos = 1;
    long prefix = 1;
    while( pos < k ) {
      long count = getCount(prefix, n);
      // printf("n: %d, prefix: %d, count: %d \n", n, prefix, count);
      if( pos + count > k ) {
        // 说明在这个前缀树区间内
        prefix *= 10;   // 进入子树
        pos ++;
      } else {
        prefix ++;      // 进入下一个前缀
        pos += count;
      }
    }
    // cout << pos << ", " << prefix << endl;
    return static_cast<int>(prefix);
  }
};

/*386. 字典序排数*/
/*
给定一个整数 n, 返回从 1 到 n 的字典顺序。
例如，
给定 n =1 3，返回 [1,10,11,12,13,2,3,4,5,6,7,8,9] 。
请尽可能的优化算法的时间复杂度和空间复杂度。 输入的数据 n 小于等于 5,000,000。
*/
class Solution {
private:
  vector<int> ans;
public:
/*
  int bfs(int prefix, int n) {
    int curr = prefix, next = prefix + 1, count = 0;
    while(curr <= n) {
      int low = curr, up = min(n + 1, next);
      count += (up - low);
      while(low < up)
        ans.push_back(low ++);
      curr *= 10;
      next *= 10;
    }
    return count;
  }
  vector<int> lexicalOrder(int n) {
    int pos = 1, prefix = 1;
    while(pos <= n) {
      pos += bfs(prefix, n);
      prefix ++;
    }
    return ans;
  }
*/
  void dfs(int prefix, int n) {
    if(prefix > n) return ;
    ans.push_back(prefix);
    for(int i = 0; i <= 9; i ++) {
      dfs(prefix * 10 + i, n);
    }
  }

  vector<int> lexicalOrder(int n) {
    for (int i = 1; i <= 9; ++i) dfs(i, n);
    return ans;
  }
};


/****牛课网：请实现有重复数字的有序数组的二分查找。*/
/*
输出在数组中第一个大于等于查找值的位置，如果数组中不存在这样的数，则输出数组长度加一。
输出位置从0开始计算 
*/
class Solution {
public:
    /**
     * 二分查找
     * @param n int整型 数组长度
     * @param v int整型 查找值
     * @param a int整型vector 有序数组
     * @return int整型
     */
  // 这里其实是c++里面的lower_bound
  // lower_bound(起始地址，结束地址，要查找的数值) 返回的是待查找数值 第一次 出现的位置。
  // upper_bound(起始地址，结束地址，要查找的数值) 返回的是 第一个大于待查找数值 出现的位置。
  int upper_bound_(int n, int v, vector<int>& a) {
    // write code here
    if (a.back() < v) return n + 1;
    int l = 0, r = n, m = 0;
    while (l < r) {
        m = (l + r) >> 1;
        if (a[m] >= v) r = m;
        else l = m + 1;
    }
    // 循环结束一定是l == r >= v
    return l;
  }
};


/***34. 在排序数组中查找元素的第一个和最后一个位置*/
/*
给定一个按照升序排列的整数数组 nums，和一个目标值 target。
找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 target，返回 [-1, -1]。
*/
class Solution {
public:
  int extremeInsertionIndex(vector<int>& nums, int target, int left) {
    int l = 0, r = nums.size();
    while(l < r) {
      int m = (l + r) / 2;
      if(nums[m] > target || (left && nums[m] == target)) {
        r = m;
      } else {
        l = m + 1;
      }
    }
    return l;
  }

  vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> res = {-1, -1};
    int n = nums.size();
    if( n == 0 || nums[0] > target || nums[n - 1] < target) 
      return res;
    int l = extremeInsertionIndex(nums, target, true);
    if(l >= n || nums[l] != target)
      return res;
    res[0] = l;
    res[1] = extremeInsertionIndex(nums, target, false) - 1; 
    return res;
  }
};

