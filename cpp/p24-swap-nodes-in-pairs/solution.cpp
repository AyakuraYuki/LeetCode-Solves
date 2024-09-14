//
// Created by 绫仓优希 on 2024-09-14.
//

/*
24. 两两交换链表中的节点

https://leetcode.cn/problems/swap-nodes-in-pairs/description/

给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。

示例 1：
    （图片：puzzle-images/p24-swap-nodes-in-pairs/swap_ex1.jpg）
    输入：head = [1,2,3,4]
    输出：[2,1,4,3]
示例 2：
    输入：head = []
    输出：[]
示例 3：
    输入：head = [1]
    输出：[1]

提示：
  * 链表中节点的数目在范围 [0, 100] 内
  * 0 <= Node.val <= 100
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
    static ListNode *swapPairs(ListNode *head) {
        auto *dummy = new ListNode(0, head);
        auto *cursor = dummy;
        // 结束条件是当前游标之后没有节点，或者只有一个节点
        while (cursor->next && cursor->next->next) {
            // 另当前游标后两个节点分别是 back 和 front
            auto *back = cursor->next;
            auto *front = cursor->next->next;
            // 因为顺序需要从 cursor->back->front 变成 cursor->front->back，所以要做如下的交换
            cursor->next = front;
            back->next = front->next;
            front->next = back;
            cursor = back;
        }
        auto *ans = dummy->next;
        delete dummy;
        return ans;
    }
};

// 递归法：小心爆仓炸栈
class RecursiveSolution {
public:
    static ListNode *swapPairs(ListNode *head) {
        if (!head || !head->next)
            return head;
        auto *new_head = head->next;
        head->next = swapPairs(new_head->next);
        new_head->next = head;
        return new_head;
    }
};

int main(int argc, char *argv[]) {
    RecursiveSolution::swapPairs(new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4)))));
}
