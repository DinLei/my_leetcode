/*23. 合并K个升序链表*/
/*
给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。
*/
class Solution {
public:
  struct NodeCompare {
    bool operator()(ListNode* l, ListNode* r) {
      return l->val > r->val;
    }
  };

  ListNode* mergeKLists(vector<ListNode*>& lists) {
    ListNode* dummy = new ListNode();
    priority_queue<ListNode*, vector<ListNode*>, NodeCompare> pq;
    for(int i = 0; i < lists.size(); i++) {
      ListNode* tmp = lists[i];
      while(tmp != nullptr) {
        pq.push(tmp);
        tmp = tmp->next;
      }
    }

    ListNode* tmp = dummy;
    while(!pq.empty()) {
      tmp->next = pq.top();
      pq.pop();
      tmp = tmp->next;
    }
    tmp->next = nullptr;
    return dummy->next;
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
    for( ; old_tail->next != nullptr; n ++) {
      old_tail = old_tail->next;
    }
    old_tail->next = head;

    ListNode* new_tail = head;
    for(int i = 0; i < n - k % n - 1; i ++) {
      new_tail = new_tail->next;
    }
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
为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。注意，pos 仅仅是用于标识环的情况，并不会作为参数传递到函数中。
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

/*25. K 个一组翻转链表*/
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

