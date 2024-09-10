//
// Created by 绫仓优希 on 2024-06-26.
//

/*
2. 两数相加

https://leetcode.cn/problems/add-two-numbers/

给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例 1：
    （图片：puzzle-images/p2-add-two-numbers/addtwonumber1.jpg）
    输入：l1 = [2,4,3], l2 = [5,6,4]
    输出：[7,0,8]
    解释：342 + 465 = 807.
示例 2：
    输入：l1 = [0], l2 = [0]
    输出：[0]
示例 3：
    输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
    输出：[8,9,9,9,0,0,0,1]

提示：
  - 每个链表中的节点数在范围 [1, 100] 内
  - 0 <= Node.val <= 9
  - 题目数据保证列表表示的数字不含前导零
 */

// Definition for singly-linked list.
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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        // carry 记录了上一位数相加的进位数值
        int carry = 0;
        // 构造一个【假人】节点，用一个头节点指向 dummy 做填充逻辑
        ListNode *dummy = new ListNode(0), *head = dummy;
        // 双遍历，直到两个链表都遍历结束
        while (l1 || l2) {
            int sum = carry + (l1 ? l1->val : 0) + (l2 ? l2->val : 0); // 每进一位，计算这一位的两数之和
            carry = sum / 10; // 计算这一位之和需要进位加多少
            sum %= 10; // 拿到进位后这一位的个位数数值
            head->next = new ListNode(sum); // 将个位数值填入 head
            head = head->next; // head 进一位
            if (l1) {
                l1 = l1->next; // 如果 l1 还有值，l1 进一位
            }
            if (l2) {
                l2 = l2->next; // 如果 l2 还有值，l2 进一位
            }
        }
        if (carry > 0) head->next = new ListNode(carry); // 如果进位还有余数，追加到 head 的末尾
        return dummy->next; // dummy->next 记录了链表头，返回它而不要返回 dummy 本身，因为 dummy.val 是假人占位
    }
};
