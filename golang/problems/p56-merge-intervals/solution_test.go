package p56_merge_intervals

import (
	"reflect"
	"testing"
)

func Test_merge(t *testing.T) {
	cases := []struct {
		intervals [][]int
		want      [][]int
	}{
		{
			intervals: [][]int{{1, 3}, {2, 6}, {8, 10}, {15, 18}},
			want:      [][]int{{1, 6}, {8, 10}, {15, 18}},
		},
		{
			intervals: [][]int{{1, 4}, {4, 5}},
			want:      [][]int{{1, 5}},
		},
	}
	for _, v := range cases {
		get := merge(v.intervals)
		if !reflect.DeepEqual(get, v.want) {
			t.Fatalf("case want %v, but got %v", v.want, get)
		}
	}
}
