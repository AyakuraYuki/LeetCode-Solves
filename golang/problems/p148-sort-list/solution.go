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
