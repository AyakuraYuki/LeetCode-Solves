# -*- coding: utf-8 -*-

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    """
    2. Add Two Numbers

    https://leetcode.com/problems/add-two-numbers/description/
    """

    def addTwoNumbers(self, l1, l2):
        dummy = ListNode(None)
        current = dummy
        carry = 0
        while l1 is not None or l2 is not None:
            x = l1.val if l1 is not None else 0
            y = l2.val if l2 is not None else 0
            _sum = carry + x + y
            carry = _sum // 10
            current.next = ListNode(_sum % 10)
            current = current.next
            if l1 is not None:
                l1 = l1.next
            if l2 is not None:
                l2 = l2.next
        if carry is 1:
            current.next = ListNode(carry)
        return dummy.next
