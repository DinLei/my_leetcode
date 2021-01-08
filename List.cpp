/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */


/**23. 合并K个升序链表*/
/*
给你一个链表数组，每个链表都已经按升序排列。
请你将所有链表合并到一个升序链表中，返回合并后的链表。
*/
// 用优先队列，小顶堆
// 总的时间代价即渐进时间复杂度为 O(kn * log k)
// 优先队列中的元素不超过 k 个，故渐进空间复杂度为 O(k)
class Solution {
public:
  struct Status {
    int val;
    ListNode* ptr;
    Status(int val, ListNode* ptr): val(val), ptr(ptr) {}
    bool operator < (const Status& rhs) const {
      return val > rhs.val;
    }
  };

  priority_queue<Status> q;

  ListNode* mergeKLists(vector<ListNode*>& lists) {
    for(auto node: lists) {
      if(node) q.push({node->val, node});
    }
    ListNode dummy, * tail = &dummy;
    while(!q.empty()) {
      Status s = q.top(); q.pop();
      tail->next = s.ptr; tail = tail->next;
      if(s.ptr->next) q.push({s.ptr->next->val, s.ptr->next});
    }
    return dummy.next;
  }
};


// 方法二：分治合并
class Solution {
public:
  ListNode* mergeTwoLists(ListNode *a, ListNode *b) {
    if ((!a) || (!b)) return a ? a : b;
    ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
    while (aPtr && bPtr) {
      if (aPtr->val < bPtr->val) {
        tail->next = aPtr; aPtr = aPtr->next;
      } else {
        tail->next = bPtr; bPtr = bPtr->next;
      }
      tail = tail->next;
    }
    tail->next = (aPtr ? aPtr : bPtr);
    return head.next;
  }

  ListNode* merge(vector <ListNode*> &lists, int l, int r) {
    if (l == r) return lists[l];
    if (l > r) return nullptr;
    int mid = (l + r) >> 1;
    return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
  }

  ListNode* mergeKLists(vector<ListNode*>& lists) {
    return merge(lists, 0, lists.size() - 1);
  }
};


/*19. 删除链表的倒数第N个节点*/
/*
level：中等
给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
*/
// 快慢指针
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* first = head;
        ListNode* second = dummy;
        for (int i = 0; i < n; ++i) {
            first = first->next;
        }
        while (first) {
            first = first->next;
            second = second->next;
        }
        second->next = second->next->next;
        ListNode* ans = dummy->next;
        delete dummy;
        return ans;
    }
};

/*24. 两两交换链表中的节点*/
class Solution {
public:
  /* 递归解法 */
  ListNode* swapPairs2(ListNode* head) {
    if(head == NULL ||head->next == NULL )
      return head;
    // nnext: next->next
    ListNode* nnext = head->next->next;
    // tnext: the next
    ListNode* tnext = head->next;

    // 两两交换
    tnext->next = head;
    head->next = swapPairs2(nnext);
    return tnext;
  }

  /* 迭代解法 */
  ListNode* swapPairs(ListNode* head) {
    ListNode* dummy = new ListNode(-1);
    dummy->next = head;
    ListNode* prev = dummy;
    while(head != NULL && head->next != NULL) {
      // 获取要交换的节点
      ListNode* tnext = head->next;
      ListNode* nnext = head->next->next;
      // 两两交换
      tnext->next = head;
      head->next = nnext;
      prev->next = tnext;
      // 维护到新状态
      prev = head;
      head = nnext;
    }
    return dummy->next;
  }
};


/*206. 反转链表*/
class Solution {
public:
  // 迭代
  ListNode* reverseList2(ListNode* head) {
    // 注意初始化一定要为null
    ListNode* prev = nullptr, *curr = head;
    while(curr) {
      ListNode* tmp = curr->next;
      curr->next = prev;
      prev = curr;
      curr = tmp;
    }
    return prev;
  }
  // 递归
  ListNode* reverseList(ListNode* head) {
    if(head == nullptr || head->next == nullptr)
      return head;
    ListNode* curr = reverseList(head->next);
    // 技巧
    head->next->next = head;
    head->next = nullptr;
    return curr;
  }
};


/**25. K 个一组翻转链表*/
class Solution {
public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* dummy = new ListNode();
    dummy->next = head;
    ListNode* prev = dummy, * end = dummy;

    while( end->next != NULL ) {
      for(int i = 0; i < k && end != NULL; i ++) 
        end = end->next;
      if(end == NULL) break;
      ListNode* start = prev->next, * next = end->next;
      end->next = NULL;   // 方便翻转子链表
      prev->next = reverseList(start);    
      start->next = next;

      prev = start; end = start;    // 更新到下一段的前驱位置
    }
    return dummy->next;
  }

  ListNode* reverseList(ListNode* head) {
    ListNode* prev = NULL;
    ListNode* curr = head;
    while(curr != NULL) {
      ListNode* next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    return prev;
  }
};


/*61. 旋转链表*/
/*
level: 中等
给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
*/
class Solution {
public:
  ListNode* rotateRight(ListNode* head, int k) {
    if(head == nullptr || head->next == nullptr)
      return head;
    ListNode* old_tail = head;
    int n = 1;
    // 找到当前list的最后一个节点
    for( ; old_tail->next != nullptr; n ++) {
      old_tail = old_tail->next;
    }
    old_tail->next = head;

    // 找到要切断的节点位置
    ListNode* new_tail = head;
    for(int i = 0; i < n - k % n - 1; i ++) {
      new_tail = new_tail->next;
    }

    // 新的头部节点
    ListNode* new_head = new_tail->next;
    new_tail->next = nullptr;

    return new_head;
  }
};


/*146. LRU 缓存机制*/
/*
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制 。
实现 LRUCache 类：

LRUCache(int capacity) 以正整数作为容量 capacity 初始化 LRU 缓存
int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
void put(int key, int value) 如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字-值」。当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。
*/
struct DLinkedNode {
  int key, value;
  DLinkedNode* prev;  // 前面的，较新的
  DLinkedNode* next;  // 后面的，较旧的
  DLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {};
  DLinkedNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {};
};

class LRUCache {
private:
  unordered_map<int, DLinkedNode*> cache;
  DLinkedNode* head;  // 头部，最新的，边界无实意
  DLinkedNode* tail;  // 尾部，最旧的，边界无实意
  int size;
  int capacity;
  
public:
  LRUCache(int _capacity): capacity(_capacity), size(0) {
    head = new DLinkedNode();
    tail = new DLinkedNode();
    head->next = tail;
    tail->prev = head;
  }
  
  int get(int key) {
    if(!cache.count(key))
      return -1;
    DLinkedNode* node = cache[key];
    moveToHead(node);
    return node->value;
  }
  
  void put(int key, int value) {
    if(!cache.count(key)) {
      DLinkedNode* node = new DLinkedNode(key, value);
      cache[key] = node;
      addToHead(node);
      size ++;
      if(size > capacity) {
        DLinkedNode* last = removeTail();
        cache.erase(last->key);
        delete last;
        size --;
      }
    } else {
      DLinkedNode* node = cache[key];
      node->value = value;
      moveToHead(node);
    }
  }

  void addToHead(DLinkedNode* node) {
    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
  }

  void removeNode(DLinkedNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void moveToHead(DLinkedNode* node) {
    removeNode(node);
    addToHead(node);
  }

  DLinkedNode* removeTail() {
    DLinkedNode* node = tail->prev;
    removeNode(node);
    return node;
  }
};

/*142. 环形链表 II*/
/*
给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。
注意，pos 仅仅是用于标识环的情况，并不会作为参数传递到函数中。
说明：不允许修改给定的链表。
*/
class Solution {
public:
  ListNode *detectCycle(ListNode *head) {
    ListNode* slow = head, * fast = head;
    int count = 0;
    while(fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
      if(slow == fast){
        count ++;
        break;
      }
    }
    if( count ) {
      fast = head;
      while(fast != slow) {
        fast = fast->next;
        slow = slow->next;
      }
      return fast;
    }
    return nullptr;
  }
};

/*160. 相交链表*/
/*
编写一个程序，找到两个单链表相交的起始节点。
*/
class Solution {
public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if(!headA && !headB) return nullptr;
    ListNode* l1 = headA, * l2 = headB;
    while(l1 != l2) {
      l1 = l1 == nullptr ? headB : l1->next;
      l2 = l2 == nullptr ? headA : l2->next;
    }
    return l1;
  }
};

/*234. 回文链表*/
class Solution {
public:
    ListNode* front;
    
    /*方法一：递归*/
    bool isPalindrome(ListNode* head) {
      front = head;
      ListNode* curr = head;
      return recursiveCheck(curr);
    }

    bool recursiveCheck(ListNode* curr) {
      if( curr != NULL ) {
        if( !recursiveCheck(curr->next) ) return false;
        if( curr->val != front->val ) return false;
        front = front->next;
      }
      return true;
    }

    /*方法二：栈*/
    bool isPalindrome2(ListNode* head) {
        if( head == NULL || head->next == NULL ) 
          return true;
        stack<int> stk;
        ListNode* front = head;
        while( head != NULL) {
            stk.push(head->val);
            head = head->next;
        }
        while( !stk.empty() ) {
            if( front->val == stk.top() ){
               stk.pop();
               front = front->next;
            } else {
               break;
            }
        }
        return stk.empty() || stk.size() == 1;
    }
};


/*83. 删除排序链表中的重复元素*/
/*给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。*/
class Solution {
public:
  ListNode* deleteDuplicates(ListNode* head) {
    ListNode* cur = head;
    while (cur != NULL && cur->next != NULL) {
      if (cur->val == cur->next->val) {
        cur->next = cur->next->next;
      } else {
        cur = cur->next;
      }
    }
    return head;
  }
};


/*剑指 Offer 36. 二叉搜索树与双向链表*/
/*
输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。
*/
// 迭代
class Solution {
public:
  Node* treeToDoublyList(Node* root) {
    if(root == NULL)
      return NULL;
    stack<Node*> stk; 
    Node* next = root, *p = new Node(0);
    Node* ans = p, * tmp;
    while( !stk.empty() || next ) {
      if( next ) {
        stk.push(next);
        next = next->left;
      } else {
        next = stk.top(); stk.pop();
        tmp = p;
        p->right = next;
        p = p->right;
        p->left = tmp;
        next = next->right;
      }
    }
    ans = ans->right;
    ans->left = p; p->right = ans;
    return ans;
  }
}
// 递归
class Solution {
private: 
  Node* head, *tail;
public:
  Node* treeToDoublyList(Node* root) {
    if(!root) {
      return nullptr;
    }

    inorder(root); // 构造出链表的所有结构，除了头连尾和尾连头的两个指针
    head -> left = tail; // 补上头连尾
    tail -> right = head; // 补上尾连头

    return head; // 返回头
  }
  void inorder(Node* root) {
    if(!root) {
      return;
    }

    inorder(root -> left); // 左

    if(!tail) {
      head = root; // 当tail还不存在，也就是root此时在整个BST的最左边的节点，这个节点就是head
    }
    else {
      tail -> right = root; // 前一个节点的right是当前节点
      root -> left = tail; // 当前节点的left是前一个节点
    }
    tail = root; // 将前一个节点更新为当前节点（所以到最后，tail就会挪到整个BST的最右边的节点，这个节点就是链表的尾节点）

    inorder(root -> right); // 右
  }
};



/*148. 排序链表*/
/*
给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

进阶：
你可以在 O(nlogn) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
*/
// 方法一：自顶向下归并排序
// 时间复杂度：O(nlogn)，其中 n 是链表的长度
// 空间复杂度：O(logn)， 其中 n 是链表的长度。空间复杂度主要取决于递归调用的栈空间。
  ListNode* sortList(ListNode* node) {
    if(!node || !node->next)
      return node;
    // 不想用split，可以初始化 fast = node->next;
    ListNode* slow = node, * fast = node, * split;
    while(fast && fast->next) {
      split = slow;
      slow = slow->next;
      fast = fast->next->next;
    }
    split->next = nullptr;
    ListNode* curr = node, * next = slow;
    curr = sortList(curr); next = sortList(next);
    return mergeTwoList(curr, next);
  }

  ListNode* mergeTwoList(ListNode* l1, ListNode* l2) {
    if(!l1) return l2;
    if(!l2) return l1;
    if(l1->val < l2->val) {
      l1->next = mergeTwoList(l1->next, l2);
      return l1;
    } else {
      l2->next = mergeTwoList(l1, l2->next);
      return l2;
    }
  }

/*
方法二：自底向上归并排序
时间复杂度：O(nlogn)，其中 n 是链表的长度。
空间复杂度：O(1)。
*/
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        // 求该链表的总长度
        int length = 0;
        ListNode* node = head;
        while (node != nullptr) {
            length++;
            node = node->next;
        }
        ListNode* dummyHead = new ListNode(0, head);
        for (int subLength = 1; subLength < length; subLength <<= 1) {
            ListNode* prev = dummyHead, *curr = dummyHead->next;
            while (curr != nullptr) {
                // 切割 第一部分 子数组
                ListNode* head1 = curr;
                for (int i = 1; i < subLength && curr->next != nullptr; i++) {
                    curr = curr->next;
                }
                // 切割 第二部分 子数组
                ListNode* head2 = curr->next;
                curr->next = nullptr;
                curr = head2;
                // 注意第二部分 子数组切割的判断条件
                for (int i = 1; i < subLength && curr != nullptr && curr->next != nullptr; i++) {
                    curr = curr->next;
                }
                // 开启第三第四...部分
                ListNode* next = nullptr;
                if (curr != nullptr) {
                    next = curr->next;
                    curr->next = nullptr;
                }
                // 合并前两个
                ListNode* merged = merge(head1, head2);
                // 更新prev到新指针
                prev->next = merged;
                while (prev->next != nullptr) {
                    prev = prev->next;
                }
                // 更新curr到新指针
                curr = next;
            }
        }
        return dummyHead->next;
    }
    // 合并双链表的非迭代写法
    ListNode* merge(ListNode* head1, ListNode* head2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* temp = dummyHead, *temp1 = head1, *temp2 = head2;
        while (temp1 != nullptr && temp2 != nullptr) {
            if (temp1->val <= temp2->val) {
                temp->next = temp1;
                temp1 = temp1->next;
            } else {
                temp->next = temp2;
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
        if (temp1 != nullptr) {
            temp->next = temp1;
        } else if (temp2 != nullptr) {
            temp->next = temp2;
        }
        return dummyHead->next;
    }
};
