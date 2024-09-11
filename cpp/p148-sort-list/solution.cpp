//
// Created by 绫仓优希 on 2024-09-11.
//

/*
148. 排序链表

https://leetcode.cn/problems/sort-list/

给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

示例 1：
    （图片：puzzle-images/p148-sort-list/sort_list_1.jpg）
    输入：head = [4,2,1,3]
    输出：[1,2,3,4]
示例 2：
    （图片：puzzle-images/p148-sort-list/sort_list_2.jpg）
    输入：head = [-1,5,3,4,0]
    输出：[-1,0,3,4,5]
示例 3：
    输入：head = []
    输出：[]

提示：
  * 链表中节点的数目在范围 [0, 5 * 104] 内
  * -105 <= Node.val <= 105

进阶：你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
 */

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

class Solution {
public:
    ListNode *sortList(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return head;
        auto *slow = head, *fast = head, *pre = head;
        while (fast && fast->next) {
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        pre->next = nullptr;
        return merge(sortList(head), sortList(slow));
    }

private:
    ListNode *merge(ListNode *left, ListNode *right) {
        // 建立一个哑节点存储检查点
        auto *dummy = new ListNode(-1);
        // 建立一个游标以进行扫描
        auto *cursor = dummy;
        while (left && right) {
            // 对比和交换节点
            if (left->val < right->val) {
                cursor->next = left;
                left = left->next;
            } else {
                cursor->next = right;
                right = right->next;
            }
            cursor = cursor->next; // 移动到下一个节点
        }
        if (left) cursor->next = left;
        if (right) cursor->next = right;
        // 返回一个合并后的链表
        return dummy->next;
    }
};
