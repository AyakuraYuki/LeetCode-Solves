package p148_sort_list

import (
	"reflect"
	"testing"
)

var cases = []struct {
	input *ListNode
	want  *ListNode
}{
	{
		// [4, 2, 1, 3]
		&ListNode{
			4, &ListNode{
				2, &ListNode{
					1, &ListNode{
						3, nil}}}},
		// [1, 2, 3, 4]
		&ListNode{
			1, &ListNode{
				2, &ListNode{
					3, &ListNode{
						4, nil}}}},
	},
	{
		// [-1,5,3,4,0]
		&ListNode{
			-1, &ListNode{
				5, &ListNode{
					3, &ListNode{
						4, &ListNode{
							0, nil}}}}},
		// [-1,0,3,4,5]
		&ListNode{
			-1, &ListNode{
				0, &ListNode{
					3, &ListNode{
						4, &ListNode{
							5, nil}}}}},
	},
	{
		&ListNode{}, // []
		&ListNode{}, // []
	},
}

func Test_sortList(t *testing.T) {
	for _, v := range cases {
		get := sortList(v.input)
		if !reflect.DeepEqual(get, v.want) {
			t.Fatalf("want %v, but got %v", v.want, get)
		}
	}
}
