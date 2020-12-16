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
    if(head == nullptr || head->next == nullptr) return head;
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