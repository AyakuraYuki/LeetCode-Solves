//
// Created by 绫仓优希 on 2024-07-02.
//

/*
21. 合并两个有序链表

https://leetcode.cn/problems/merge-two-sorted-lists/

将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

示例 1：
    （图示：puzzle-images/p21-merge-two-sorted-lists/merge_ex1.jpg）
    输入：l1 = [1,2,4], l2 = [1,3,4]
    输出：[1,1,2,3,4,4]
示例 2：
    输入：l1 = [], l2 = []
    输出：[]
示例 3：
    输入：l1 = [], l2 = [0]
    输出：[0]

提示：
  * 两个链表的节点数目范围是 [0, 50]
  * -100 <= Node.val <= 100
  * l1 和 l2 均按 非递减顺序 排列
 */

#include <algorithm>
#include <vector>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {
    }

    explicit ListNode(const int x) : val(x), next(nullptr) {
    }

    ListNode(const int x, ListNode *next) : val(x), next(next) {
    }
};

// 递归解法
class Solution {
public:
    static ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        // 边界，处理 [], [] 或者 [], [0] 或者 [0], []
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;
        // 递归
        if (list1->val < list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }
        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
};

// 迭代解法，双迭代
// time: 0 ms (100%), rem: 17.82 MB (94.85%)
class IterSolution {
public:
    static ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        // 边界，处理 [], [] 或者 [], [0] 或者 [0], []
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;

        ListNode *prehead = new ListNode(-1);
        ListNode *prev = prehead;
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                prev->next = list1;
                list1 = list1->next;
            } else {
                prev->next = list2;
                list2 = list2->next;
            }
            prev = prev->next;
        }
        prev->next = list1 == nullptr ? list2 : list1;
        return prehead->next;
    }
};

// 重组法，读取所有数值，排序后重建链表
// time: 0 ms (100%), rem: 18.27 MB (5.23%)
class ReassembleSolution {
public:
    static ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        // 边界，处理 [], [] 或者 [], [0] 或者 [0], []
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;

        vector<int> vals;
        while (list1 != nullptr) {
            vals.push_back(list1->val);
            list1 = list1->next;
        }
        while (list2 != nullptr) {
            vals.push_back(list2->val);
            list2 = list2->next;
        }
        sort(vals.begin(), vals.end());
        auto *ret = new ListNode(vals[0]);
        ListNode *head = ret;
        for (int i = 1; i < vals.size(); ++i) {
            ret->next = new ListNode(vals[i]);
            ret = ret->next;
        }
        return head;
    }
};
