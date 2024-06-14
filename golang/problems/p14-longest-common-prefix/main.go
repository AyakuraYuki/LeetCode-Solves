// @lc app=leetcode id=14 lang=golang
//
// [14] Longest Common Prefix
//
// https://leetcode.com/problems/longest-common-prefix/description/
//
// algorithms
// Easy (44.1%)
// Total Accepted:    1.3M
// Total Submissions: 3M
package main

import "fmt"

func longestCommonPrefix(elements []string) (prefix string) {
	if len(elements) == 0 {
		return ""
	}
	if len(elements) == 1 {
		return elements[0]
	}

	minLength := len(elements[0])
	for _, s := range elements {
		if l := len(s); l < minLength {
			minLength = l
		}
	}

	isCommonPrefix := func(length int) bool {
		str0, count := elements[0][:length], len(elements)
		for i := 0; i < count; i++ {
			if elements[i][:length] != str0 {
				return false
			}
		}
		return true
	}

	low, high := 0, minLength
	for low < high {
		mid := (high-low+1)/2 + low
		if isCommonPrefix(mid) {
			low = mid
		} else {
			high = mid - 1
		}
	}

	return elements[0][:low]
}

func main() {
	cases := []struct {
		Strs []string
		Want string
	}{
		{[]string{"flower", "flow", "flight"}, "fl"},
		{[]string{"dog", "racecar", "car"}, ""},
	}
	for _, c := range cases {
		prefix := longestCommonPrefix(c.Strs)
		if prefix != c.Want {
			panic(fmt.Sprintf("want %s, got %s", c.Want, prefix))
		}
	}
}
