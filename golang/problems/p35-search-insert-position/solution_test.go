package p35_search_insert_position

import "testing"

func Test_searchInsert(t *testing.T) {
	cases := []struct {
		Nums   []int
		Target int
		Want   int
	}{
		{[]int{1, 3, 5, 6}, 5, 2},
		{[]int{1, 3, 5, 6}, 2, 1},
		{[]int{1, 3, 5, 6}, 7, 4},
	}
	for _, v := range cases {
		get := searchInsert(v.Nums, v.Target)
		if get != v.Want {
			t.Fatalf("want %d but get %d", v.Want, get)
		}
	}
}
