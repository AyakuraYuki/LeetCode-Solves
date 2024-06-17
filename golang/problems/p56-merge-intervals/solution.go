/*
56. 合并区间

https://leetcode.cn/problems/merge-intervals/

以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

示例 1：
	输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
	输出：[[1,6],[8,10],[15,18]]
	解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
示例 2：
	输入：intervals = [[1,4],[4,5]]
	输出：[[1,5]]
	解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。

提示：
  * 1 <= intervals.length <= 104
  * intervals[i].length == 2
  * 0 <= starti <= endi <= 104
*/

package p56_merge_intervals

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
