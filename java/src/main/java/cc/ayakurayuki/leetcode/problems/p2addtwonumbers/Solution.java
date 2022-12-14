package cc.ayakurayuki.leetcode.problems.p2addtwonumbers;

/**
 * [2] <a href="https://leetcode.com/problems/add-two-numbers/description/">Add Two Numbers</a>
 *
 * @author Ayakura Yuki
 * @date Oct 30, 2018 20:16
 */
public class Solution {

  public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
    ListNode dummyHead = new ListNode(0);
    ListNode current = dummyHead;
    int carry = 0;
    while (l1 != null || l2 != null) {
      int x = (l1 != null) ? l1.val : 0;
      int y = (l2 != null) ? l2.val : 0;
      int sum = carry + x + y;
      carry = sum / 10;
      current.next = new ListNode(sum % 10);
      current = current.next;
      if (l1 != null) {
        l1 = l1.next;
      }
      if (l2 != null) {
        l2 = l2.next;
      }
    }
    if (carry > 0) {
      current.next = new ListNode(carry);
    }
    return dummyHead.next;
  }

}

/**
 * Definition for singly-linked list.
 */
class ListNode {

  int      val;
  ListNode next;

  ListNode(int x) {val = x;}

}
