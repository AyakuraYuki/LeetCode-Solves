package main

import (
	"fmt"
	"testing"
)

func Test_numberOfWays(t *testing.T) {
	cases := []struct {
		startPos, endPos, k, want int
	}{
		{1, 2, 3, 3},
		{2, 5, 10, 0},
		{2, 5, 9, 84},
	}
	for _, v := range cases {
		get := numberOfWays(v.startPos, v.endPos, v.k)
		if get != v.want {
			t.Fatalf("want %d but get %d", v.want, get)
		}
	}
}

func Example_numberOfWaysBeforeOptimize() {
	fmt.Println(numberOfWaysBeforeOptimize(1, 2, 3))
	// Output:
	// [[1 0 0 0] [1 1 0 0] [1 2 1 0] [1 3 3 1]]
	// 3
}
