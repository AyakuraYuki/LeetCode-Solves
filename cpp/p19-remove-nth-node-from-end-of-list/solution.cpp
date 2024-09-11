//
// Created by 绫仓优希 on 2024-09-11.
//

/*
19. 删除链表的倒数第 N 个结点

https://leetcode.cn/problems/remove-nth-node-from-end-of-list/

给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

示例 1：
    （图片：puzzle-images/p19-remove-nth-node-from-end-of-list/remove_ex1.jpg）
    输入：head = [1,2,3,4,5], n = 2
    输出：[1,2,3,5]
示例 2：
    输入：head = [1], n = 1
    输出：[]
示例 3：
    输入：head = [1,2], n = 1
    输出：[1]

提示：
  * 链表中结点的数目为 sz
  * 1 <= sz <= 30
  * 0 <= Node.val <= 100
  * 1 <= n <= sz

进阶：你能尝试使用一趟扫描实现吗？

hint 1: Maintain two pointers and update one with a delay of n steps.
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

class Solution {
public:
    // 首先演示一个常规解，这个解法需要两次遍历，所以不是非常高效，但却是最容易想到的解法
    static ListNode *removeNthFromEnd(ListNode *head, const int n) {
        auto *dummy = new ListNode(0, head);
        // 获取全链长度（这里是第一次扫描）
        int len = 0;
        while (head) {
            ++len;
            head = head->next;
        }
        // 重新回到头部，做摘取节点的操作
        ListNode *cur = dummy;
        // 这里的第 len - n + 1 个节点就是需要删除的节点，i 初始化为 1 是因为 cur 取自哑节点 dummy，dummy 是 0 号节点
        // 这里是第二次扫描
        for (int i = 1; i < len - n + 1; ++i)
            cur = cur->next;
        // 把倒数第 n 个节点跳过
        cur->next = cur->next->next;
        ListNode *ans = dummy->next;
        delete dummy;
        return ans;
    }
};

// 基于栈的一种实现，使用了 C++ 的 stack 来完成，由出栈计数器实现移除指定节点
class StackSolution {
public:
    static ListNode *removeNthFromEnd(ListNode *head, const int n) {
        auto *dummy = new ListNode(0, head);
        stack<ListNode *> stk;
        ListNode *cur = dummy;
        while (cur) {
            stk.push(cur); // 注意这里会把哑节点存入栈底
            cur = cur->next;
        }
        for (int i = 0; i < n; ++i)
            stk.pop();
        ListNode *prev = stk.top(); // 栈弹出指定个数的节点后，此时的栈顶就是待摘除节点的前一个节点
        prev->next = prev->next->next; // 摘除节点
        ListNode *ans = dummy->next;
        delete dummy;
        return ans;
    }
};

// 基于栈的另一种实现，使用了方法栈来完成。这是一个只需要遍历一次的实现。
class FnStackSolution {
public:
    static ListNode *removeNthFromEnd(ListNode *head, const int n) {
        auto *dummy = new ListNode(0, head);
        dfs(dummy, dummy->next, n);
        return dummy->next;
    }

private:
    static int dfs(ListNode *prev, ListNode *cur, const int n) {
        if (cur == nullptr) return 1; // 终止符号
        const int cursor = dfs(cur, cur->next, n);
        if (cursor == n) prev->next = cur->next; // 找到目标节点，移除。注意，此时的 prev 是上一个栈的 cur。
        return cursor + 1;
    }
};

// 基于双指针的实现
class DoublePointerSolution {
public:
    static ListNode *removeNthFromEnd(ListNode *head, const int n) {
        auto *dummy = new ListNode(0, head);
        auto *front = head;
        auto *back = dummy;
        for (int i = 0; i < n; ++i) {
            front = front->next; // 提前移动
        }
        // 同时移动
        while (front) {
            front = front->next;
            back = back->next;
        }
        back->next = back->next->next;
        ListNode *ans = dummy->next;
        delete dummy;
        return ans;
    }
};

// 一种【取巧】的解决方案：偷偷加一个索引成员，结合方法栈解决
class IndexInRecursiveSolution {
public:
    ListNode *removeNthFromEnd(ListNode *head, const int n) {
        if (head == nullptr)
            return head;

        head->next = removeNthFromEnd(head->next, n);
        ++index;
        if (index == n) {
            auto *ans = head->next;
            delete head;
            return ans;
        }
        return head;
    }

private:
    int index = 0;
};
