// 分治
/*4. 寻找两个正序数组的中位数*/
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
      int lp2 = (n1 + n2 + 1)/2 - lp1;    // 数组2 左边的元素个数

      int L1 = (lp1 == 0) ? INT_MIN : nums1[lp1 - 1];
      int R1 = (lp1 == n1) ? INT_MAX : nums1[lp1];
      int L2 = (lp2 == 0) ? INT_MIN : nums2[lp2 - 1];
      int R2 = (lp2 == n2) ? INT_MAX : nums2[lp2];

      if( L1 > R2 )
        up = lp1 - 1;
      else if( L2 > R1 )
        low = lp1 + 1;
      else 
        return ((n1 + n2) % 2 == 0) ? (max(L1, L2) + min(R1, R2))/2.0 : max(L1, L2);
    }
    return 0;
  }
};


/*找两个有序数组的第K小元素*/
class Solution {
public:
    int findKthElm(vector<int>& nums1,vector<int>& nums2,int k){
        assert(1 <= k && k <= nums1.size() + nums2.size());
        int le = max(0, int(k - nums2.size())), ri = min(k, int(nums1.size()));
        while(le < ri){ 
            // m 是 数组1 的 右半部分 的 第一个数
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


/*215. 数组中的第K个最大元素*/
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
        for (int i = nums.size() - 1; i >= nums.size() - k + 1; -- i) {
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
        vector<int> ans(k + 2); ans.push_back(nums[idx]);
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

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> occurrences;
        for (auto& v : nums) {
            occurrences[v]++;
        }

        // pair 的第一个元素代表数组的值，第二个元素代表了该值出现的次数
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)> q(cmp);
        for (auto& [num, count] : occurrences) {
            if (q.size() == k) {
                if (q.top().second < count) {
                    q.pop();
                    q.emplace(num, count);
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


/*33. 搜索旋转排序数组*/
// 二分查找
class Solution {
public:
  int search(vector<int>& nums, int target) {
    int n = nums.size();
    int l = 0, r = n - 1;
    while(l <= r) {
      int m = (l + r) >> 1;
      if(nums[m] == target) return m;
      if(nums[m] >= nums[0]) {
        if(nums[0] <= target && target < nums[m])
          r = m - 1;
        else 
          l = m + 1;
      } else {
        if(nums[m] < target && target <= nums[n - 1])
          l = m + 1;
        else 
          r = m - 1;
      }
    }
    return -1;
  }
};