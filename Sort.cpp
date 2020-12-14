// 排序
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

