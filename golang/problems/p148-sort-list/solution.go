/*
148. 排序链表

https://leetcode.cn/problems/sort-list/

给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

示例 1：
	（图片：sort_list_1.jpg）
	输入：head = [4,2,1,3]
	输出：[1,2,3,4]
示例 2：
	（图片：sort_list_2.jpg）
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

package p148_sort_list

// ListNode - Definition for singly-linked list.
type ListNode struct {
	Val  int
	Next *ListNode
}

// sortList uses QuickSort to solve the problem.
func sortList(head *ListNode) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	slow, fast, pre := head, head, head
	for fast != nil && fast.Next != nil {
		pre = slow
		slow = slow.Next
		fast = fast.Next.Next
	}
	pre.Next = nil
	return merge(sortList(head), sortList(slow))
}

// merge cannot use recursion
func merge(left *ListNode, right *ListNode) *ListNode {
	dummy := &ListNode{Val: -1}       // create a dummy linked list as checkpoint to store the step result
	cursor := dummy                   // use a cursor to solve every step
	for left != nil && right != nil { // compare and swap, step by step
		if left.Val < right.Val {
			cursor.Next = left
			left = left.Next
		} else {
			cursor.Next = right
			right = right.Next
		}
		cursor = cursor.Next // move cursor to next node
	}
	if left != nil {
		cursor.Next = left
	}
	if right != nil {
		cursor.Next = right
	}
	return dummy.Next // dummy.Next means the actual result, a sorted list
}
