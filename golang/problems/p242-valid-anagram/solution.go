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
