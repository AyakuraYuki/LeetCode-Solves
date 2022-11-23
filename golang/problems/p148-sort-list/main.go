/*
148. Sort List

https://leetcode.com/problems/sort-list/description/

Given the head of a linked list, returns the list after sorting it in ascending order.

Example 1:
Input: head = [4,2,1,3]
Output: [1,2,3,4]

Example 2:
Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]

Example 3:
Input: head = []
Output: []

Constraints:
- The number of nodes in the list is in the range [0, 5 * (10^4)]
- -10^5 <= Node.val <= 10^5

Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?
*/

package main

import "fmt"

// ListNode - Definition for singly-linked list.
type ListNode struct {
	Val  int
	Next *ListNode
}

// region solve

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

// endregion

func main() {
	examples := make([]*ListNode, 0)
	// Example 1: [4,2,1,3]
	examples = append(examples, &ListNode{
		Val: 4,
		Next: &ListNode{
			Val: 2,
			Next: &ListNode{
				Val: 1,
				Next: &ListNode{
					Val:  3,
					Next: nil,
				},
			},
		},
	})
	// Example 2: [-1,5,3,4,0]
	examples = append(examples, &ListNode{
		Val: -1,
		Next: &ListNode{
			Val: 5,
			Next: &ListNode{
				Val: 3,
				Next: &ListNode{
					Val: 4,
					Next: &ListNode{
						Val:  0,
						Next: nil,
					},
				},
			},
		},
	})
	// Example 3: []
	examples = append(examples, &ListNode{})

	// visualize
	for _, v := range examples {
		output := sortList(v)
		next := output.Next
		for {
			fmt.Println(fmt.Sprintf("val: %d", output.Val))
			if next != nil {
				output = next
				next = output.Next
			} else {
				break
			}
		}
		fmt.Println()
	}
}
