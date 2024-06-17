/*
3. 无重复字符的最长子串

https://leetcode.cn/problems/longest-substring-without-repeating-characters/

给定一个字符串 s，请你找出其中不含有重复字符的`最长`子串的长度。

示例 1：
	输入：s = "abcabcbb"
	输出：3
	解释：因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2：
	输入：s = "bbbbb"
	输出：1
	解释：因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3：
	输入：s = "pwwkew"
	输出：3
	解释：因为无重复字符的最长子串是 "wke"，所以其长度为 3。
         请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

提示：
  * 0 <= s.length <= 5 * 10^4
  * s 由英文字母、数字、符号和空格组成
*/

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
