/*
3. Longest Substring Without Repeating Characters

https://leetcode.com/problems/longest-substring-without-repeating-characters/

Given a string `s`, find the length of the longest substring without repeating characters.

Example 1:
Input: "abcabcbb"
Output: 3

Example 2:
Input: "bbbbb"
Output: 1

Example 3:
Input: "pwwkew"
Output: 3
Explanation: The anwser is "wke", with the length of 3.
Notice that the anwser must be a substring, "pwke" is a subsequence and not a substring.
*/

package main

import "fmt"

// region solve

func lengthOfLongestSubstring(s string) int {
	if s == "" {
		return 0
	}
	start, end, maxLength := 0, 0, 0
	uniqueCharacters := make(map[string]struct{})
	uniqueCharactersLen := 0
	for end < len(s) {
		if _, ok := uniqueCharacters[s[end:end+1]]; !ok {
			uniqueCharacters[s[end:end+1]] = struct{}{}
			end++
			uniqueCharactersLen = len(uniqueCharacters)
			if maxLength < uniqueCharactersLen {
				maxLength = uniqueCharactersLen
			}
		} else {
			delete(uniqueCharacters, s[start:start+1])
			start++
		}
	}
	return maxLength
}

// endregion

func main() {
	examples := make([]string, 0)
	examples = append(examples, "abcabcbb")
	examples = append(examples, "bbbbb")
	examples = append(examples, "pwwkew")
	examples = append(examples, "abcde")
	for _, s := range examples {
		fmt.Printf("index: %-5d example: %-s\n", lengthOfLongestSubstring(s), s)
	}
}
