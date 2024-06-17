/*
242. 有效的字母异位词

https://leetcode.cn/problems/valid-anagram/

给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。

注意：若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词。

示例 1:
	输入: s = "anagram", t = "nagaram"
	输出: true
示例 2:
	输入: s = "rat", t = "car"
	输出: false

提示:
  * 1 <= s.length, t.length <= 5 * 104
  * s 和 t 仅包含小写字母

进阶: 如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？
*/

package p242_valid_anagram

import (
	"sort"
	"strings"
)

// isAnagramSortSolution sorts both `s` and `t`, and compare strings to get result
// A universal solution but slowest because of String sorts.
func isAnagramSortSolution(s string, t string) bool {
	if len(s) != len(t) {
		return false
	}
	// sort
	sArr := strings.Split(s, "")
	sort.Strings(sArr)
	s = strings.Join(sArr, "")
	tArr := strings.Split(t, "")
	sort.Strings(tArr)
	t = strings.Join(tArr, "")
	return s == t
}

// isAnagramHashTableSolution uses hash table to count letters, compare counts to get result
// A universal solution. It is not the slowest solution, but the performance depends on the hash table implementation.
func isAnagramHashTableSolution(s string, t string) bool {
	if len(s) != len(t) {
		return false
	}
	sMap := make(map[uint8]int) // s[x] returns uint8, which is ASCII code
	tMap := make(map[uint8]int) // t[x] returns uint8, which is ASCII code
	for i := 0; i < len(s); i++ {
		sMap[s[i]]++
		tMap[t[i]]++
	}
	for i := 0; i < len(s); i++ {
		if sMap[s[i]] != tMap[s[i]] {
			return false
		}
	}
	return true
}

// isAnagramCounterSolution uses rule "`s` and `t` consist of lowercase English letters.".
// The fastest solution, but only supports lowercase English letters.
func isAnagramCounterSolution(s string, t string) bool {
	if len(s) != len(t) {
		return false
	}
	chars := make([]int, 26)
	for i := 0; i < len(s); i++ {
		chars[s[i]-'a']++
		chars[t[i]-'a']--
	}
	for _, c := range chars {
		if c != 0 {
			return false
		}
	}
	return true
}
