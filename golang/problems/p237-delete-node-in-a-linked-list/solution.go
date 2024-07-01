package p237_delete_node_in_a_linked_list

type ListNode struct {
	Val  int
	Next *ListNode
}

// 实现删除的逻辑
func deleteNode(node *ListNode) {
	if node == nil || node.Next == nil {
		return
	}
	node.Val, node.Next = node.Next.Val, node.Next.Next
}
