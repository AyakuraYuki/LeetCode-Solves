package main

import (
	"testing"
)

var cases = []struct {
	nums []int
	want int
}{
	{[]int{1, 3, 8, 48, 10}, 3},
	//{[]int{3, 1, 5, 11, 13}, 1},
}

func Test_longestNiceSubarray(t *testing.T) {
	for _, v := range cases {
		get := longestNiceSubarray(v.nums)
		if get != v.want {
			t.Fatalf("want: %d, get: %d [nums: %v]", v.want, get, v.nums)
		}
	}
}

func Test_longestNiceSubarrayExhaustive(t *testing.T) {
	for _, v := range cases {
		get := longestNiceSubarrayExhaustive(v.nums)
		if get != v.want {
			t.Fatalf("want: %d, get: %d [nums: %v]", v.want, get, v.nums)
		}
	}
}
