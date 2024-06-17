package p2402_meeting_rooms_iii

import (
	"testing"
)

func Test_mostBooked(t *testing.T) {
	cases := []struct {
		n        int
		meetings [][]int
		want     int
	}{
		{2, [][]int{{0, 10}, {1, 5}, {2, 7}, {3, 4}}, 0},
		{3, [][]int{{1, 20}, {2, 10}, {3, 5}, {4, 9}, {6, 8}}, 1},
		{4, [][]int{{18, 19}, {3, 12}, {17, 19}, {2, 13}, {7, 10}}, 0},
	}
	for _, v := range cases {
		get := mostBooked(v.n, v.meetings)
		if get != v.want {
			t.Fatalf("get %d but want %d", get, v.want)
		}
	}
}
