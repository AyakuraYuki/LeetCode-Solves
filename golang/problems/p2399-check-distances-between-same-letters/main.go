package main

func checkDistances(s string, distance []int) bool {
	n := len(s)
	for cursor := 0; cursor < n; cursor++ {
		index := s[cursor] - 'a' // 当前字符在26个字母中的位置，从 0 开始数
		if distance[index] < 0 {
			continue // 跳过已经判断过的字符
		}
		nextCursor := cursor + distance[index] + 1 // 下一个当前字符应该出现的位置
		if nextCursor >= n || s[cursor] != s[nextCursor] {
			return false // 应该出现相同字符的位置是其他字符，不是匀整字符串
		}
		distance[index] = -1 // 已经判断过的字符标记跳过
	}
	return true // 遍历结束无异常，说明是匀整字符
}
