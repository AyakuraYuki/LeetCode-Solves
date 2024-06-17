package p724_find_pivot_index

import "testing"

func Test_pivotIndex(t *testing.T) {
	cases := []struct {
		nums []int
		want int
	}{
		{[]int{1, 7, 3, 6, 5, 6}, 3},
		{[]int{1, 2, 3}, -1},
		{[]int{2, 1, -1}, 0},
	}
	for _, v := range cases {
		get := pivotIndex(v.nums)
		if get != v.want {
			t.Fatalf("input %v, got %d, but want %d", v.nums, get, v.want)
		}
	}
}
