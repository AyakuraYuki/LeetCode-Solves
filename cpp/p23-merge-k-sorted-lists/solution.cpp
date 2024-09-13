//
// Created by 绫仓优希 on 2024-09-11.
//

/*
23. 合并 K 个升序链表

https://leetcode.cn/problems/merge-k-sorted-lists/

给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。

示例 1：
    输入：lists = [[1,4,5],[1,3,4],[2,6]]
    输出：[1,1,2,3,4,4,5,6]
    解释：链表数组如下：
        [
          1->4->5,
          1->3->4,
          2->6
        ]
        将它们合并到一个有序链表中得到。
        1->1->2->3->4->4->5->6
示例 2：
    输入：lists = []
    输出：[]
示例 3：
    输入：lists = [[]]
    输出：[]

提示：
  * k == lists.length
  * 0 <= k <= 10^4
  * 0 <= lists[i].length <= 500
  * -10^4 <= lists[i][j] <= 10^4
  * lists[i] 按 升序 排列
  * lists[i].length 的总和不超过 10^4
 */

#include <queue>
#include <vector>
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {
    }

    ListNode(int x) : val(x), next(nullptr) {
    }

    ListNode(int x, ListNode *next) : val(x), next(next) {
    }
};

// 暴力解 - 遍历 lists 进行两两合并，每次合并都会扫描 ans 链表，因此开销巨大
// （自己解的）
class Solution {
public:
    static ListNode *mergeKLists(const vector<ListNode *> &lists) {
        auto *ans = new ListNode(0);
        for (const auto list: lists) {
            ans->next = merge(ans->next, list);
        }
        return ans->next;
    }

private:
    static ListNode *merge(ListNode *left, ListNode *right) {
        if (!left || !right)
            return left ? left : right;

        auto *dummy = new ListNode(0);
        auto *cursor = dummy;
        while (left && right) {
            if (left->val < right->val) {
                cursor->next = left;
                left = left->next;
            } else {
                cursor->next = right;
                right = right->next;
            }
            cursor = cursor->next;
        }
        if (left) cursor->next = left;
        if (right) cursor->next = right;
        return dummy->next;
    }
};

// 分治法（Divide and Conquer）
// 将 k 个链表配对并将同一对中的链表合并
// 第一轮合并后，k 个链表被合并成 k/2 个链表，平均长度是 2n/k；然后是 k/4 个链表，k/8 个链表...
// 直到最后得到最终有序链表
class DACSolution {
public:
    static ListNode *mergeKLists(vector<ListNode *> &lists) {
        return dac_merge(lists, 0, lists.size() - 1);
    }

private:
    static ListNode *dac_merge(vector<ListNode *> &lists, const int l, const int r) {
        if (l == r) return lists[l];
        if (l > r) return nullptr;
        const int mid = (l + r) >> 1;
        return merge(dac_merge(lists, l, mid), dac_merge(lists, mid + 1, r));
    }

    static ListNode *merge(ListNode *left, ListNode *right) {
        if (!left || !right) return left ? left : right;
        auto *dummy = new ListNode(0);
        auto *cursor = dummy;
        while (left && right) {
            if (left->val < right->val) {
                cursor->next = left;
                left = left->next;
            } else {
                cursor->next = right;
                right = right->next;
            }
            cursor = cursor->next;
        }
        if (left) cursor->next = left;
        if (right) cursor->next = right;
        return dummy->next;
    }
};

// 优先队列合并
//
// 需要维护当前每个链表没有被合并的元素的头，k 个链表就最多有 k 个满足这样条件的元素，每次在这些元素里选取 val 最小的元素合并到 ans。
// 在选取最小元素的时候，可以用优先队列来优化过程。
class PriorityQueueSolution {
public:
    ListNode *mergeKLists(const vector<ListNode *> &lists) {
        for (const auto list: lists) {
            if (list) pq.push({list->val, list});
        }
        ListNode dummy, *cursor = &dummy;
        while (!pq.empty()) {
            const auto f = pq.top();
            pq.pop();
            cursor->next = f.ptr;
            cursor = cursor->next;
            if (f.ptr->next)
                pq.push({f.ptr->next->val, f.ptr->next});
        }
        return dummy.next;
    }

private:
    struct Status {
        int val;
        ListNode *ptr;

        bool operator<(const Status &rhs) const {
            return val > rhs.val;
        }
    };

    priority_queue<Status> pq;
};
