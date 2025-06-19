//
// Created by 绫仓优希 on 2024-09-14.
//

/*
25. K 个一组翻转链表

https://leetcode.cn/problems/reverse-nodes-in-k-group/

给你链表的头节点 head，每 k 个节点一组进行翻转，请你返回修改后的链表。
k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

示例 1：
    （图片：puzzle-images/p25-reverse-nodes-in-k-group/reverse_ex1.jpg）
    输入：head = [1,2,3,4,5], k = 2
    输出：[2,1,4,3,5]
示例 2：
    （图片：puzzle-images/p25-reverse-nodes-in-k-group/reverse_ex2.jpg）
    输入：head = [1,2,3,4,5], k = 3
    输出：[3,2,1,4,5]

提示：
  * 链表中的节点数目为 n
  * 1 <= k <= n <= 5000
  * 0 <= Node.val <= 1000

进阶：你可以设计一个只用 O(1) 额外内存空间的算法解决此问题吗？
 */

#include <stack>
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

// 暴力重组：利用栈进行分组翻转，对剩余不满足分组的节点，保留原顺序追加到重组后的链表末尾
// （自己解的）
class Solution {
public:
    static ListNode *reverseKGroup(ListNode *head, const int k) {
        auto *cursor = head;
        auto *dummy = new ListNode(0);
        auto *dummy_cursor = dummy;
        ListNode *step_holder = nullptr; // 断点
        stack<ListNode *> stk;
        int counter = 0;
        while (cursor) {
            stk.push(cursor);
            cursor = cursor->next;
            counter++;
            if (counter == k) {
                while (!stk.empty()) {
                    auto *node = stk.top();
                    stk.pop();
                    dummy_cursor->next = node;
                    node->next = nullptr;
                    dummy_cursor = node;
                }
                counter = 0; // 重置计数器
                step_holder = cursor; // 记录断点
            }
        }
        if (!stk.empty()) {
            dummy_cursor->next = step_holder;
        }
        auto *ans = dummy->next;
        delete dummy;
        return ans;
    }
};

class TheAnswerSolution {
public:
    // 翻转一个子链表，并且返回新的头尾
    pair<ListNode *, ListNode *> my_reverse(ListNode *head, ListNode *tail) {
        auto *prev = tail->next;
        auto *p = head;
        while (prev != tail) {
            auto *next = p->next;
            p->next = prev;
            prev = p;
            p = next;
        }
        return {tail, head};
    }

    ListNode *reverseKGroup(ListNode *head, int k) {
        auto *dummy = new ListNode(0);
        dummy->next = head;
        auto *cursor = dummy;

        while (head) {
            auto *tail = cursor;

            // 查看剩余部分长度是否大于等于 k
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (!tail)
                    return dummy->next;
            }

            auto *next = tail->next;

            // 这里是 C++17 的写法，等价于：
            // pair<ListNode *, ListNode *> result = my_reverse(head, tail);
            // head = result.first;
            // tail = result.second;
            tie(head, tail) = my_reverse(head, tail);

            // 把子链表重新接回原链表
            cursor->next = head;
            tail->next = next;
            cursor = tail;
            head = tail->next;
        }

        return dummy->next;
    }
};

int main(char* argv[]) {
    Solution::reverseKGroup(
        new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5))))),
        3
    );

    (new TheAnswerSolution())->reverseKGroup(
        new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5))))),
        3
    );
}
