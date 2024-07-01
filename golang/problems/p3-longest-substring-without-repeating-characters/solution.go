package p3_longest_substring_without_repeating_characters

func lengthOfLongestSubstring(s string) int {
	n := len(s)
	if n <= 1 {
		return n
	}
	var (
		mp    = make(map[uint8]int) // 字符最后出现位置
		ans   int                   // 最长不重复子串的长度
		left  int                   // 滑动左边界
		right int                   // 滑动右边界
	)
	for right = 0; right < n; right++ {
		if c, ok := mp[s[right]]; ok {
			ans = max(ans, right-left) // 更新最长不重复子串的长度
			left = max(left, c+1)      // 快速移动左边界
		}
		mp[s[right]] = right
	}
	return max(ans, right-left)
}
