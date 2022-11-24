/*
242. Valid Anagram

https://leetcode.com/problems/valid-anagram/submissions/

Given two strings `s` and `t`, return `true` if t is an anagram of `s`, and `false` otherwise.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

Example 1:
-> s = "anagram", t = "nagaram"
<- true

Example 2:
-> s = "rat", t = "car"
<- false

Constraints:

- 1 <= s.length, t.length <= 5 * 104
- `s` and `t` consist of lowercase English letters.

Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?
*/

package main

import (
	"sort"
	"strings"
)

// isAnagramSortSolution sorts both `s` and `t`, and compare strings to get result
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

// isAnagramCounterSolution uses rule "`s` and `t` consist of lowercase English letters.", not suitable to other cases.
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
