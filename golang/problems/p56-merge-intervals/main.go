package main

import "sort"

func merge(intervals [][]int) [][]int {
	if len(intervals) == 0 {
		return make([][]int, 0)
	}
	sort.Slice(intervals, func(i, j int) bool {
		return intervals[i][0] < intervals[j][0]
	})
	merged := make([][]int, 0)
	m := 0
	for i := 0; i < len(intervals); i++ {
		left, right := intervals[i][0], intervals[i][1]
		if m = len(merged); m == 0 || merged[m-1][1] < left {
			merged = append(merged, []int{left, right})
		} else {
			merged[m-1][1] = max(merged[m-1][1], right)
		}
	}
	return merged
}
