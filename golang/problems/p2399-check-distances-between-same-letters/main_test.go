package main

import "testing"

func Test_checkDistances(t *testing.T) {
	cases := []struct {
		s        string
		distance []int
		want     bool
	}{
		{
			"abaccb",
			[]int{1, 3, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			true,
		},
		{
			"aa",
			[]int{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			false,
		},
	}
	for _, v := range cases {
		get := checkDistances(v.s, v.distance)
		if get != v.want {
			t.Fatalf("want %t but got %t", v.want, get)
		}
	}
}
