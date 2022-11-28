package cc.ayakurayuki.leetcode.problems.p3longestsubstringwithoutrepeatingcharacters;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

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

/**
 * @author Ayakura Yuki
 * @date 2022/11/28-18:13
 */
public class Solution {

  public int lengthOfLongestSubstring(String s) {
    if (s == null || s.length() == 0) {
      return 0;
    }
    int maxLength = 0;
    Set<Character> uniqueCharacters = new HashSet<>();
    int uniqueCharactersLen;
    for (int start = 0, end = 0; end < s.length(); ) {
      if (uniqueCharacters.contains(s.charAt(end))) {
        uniqueCharacters.remove(s.charAt(start));
        start++;
      } else {
        uniqueCharacters.add(s.charAt(end));
        end++;
        uniqueCharactersLen = uniqueCharacters.size();
        if (maxLength < uniqueCharactersLen) {
          maxLength = uniqueCharactersLen;
        }
      }
    }
    return maxLength;
  }

  public static void main(String[] args) {
    var examples = List.of(
        "abcabcbb",
        "bbbbb",
        "pwwkew",
        "abcde"
    );
    for (var s : examples) {
      System.out.printf("index: %-5d example: %s%n", new Solution().lengthOfLongestSubstring(s), s);
    }
  }

}
