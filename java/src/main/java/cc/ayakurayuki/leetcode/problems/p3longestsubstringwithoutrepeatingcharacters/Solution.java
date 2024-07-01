package cc.ayakurayuki.leetcode.problems.p3longestsubstringwithoutrepeatingcharacters;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * @author Ayakura Yuki
 * @date 2022/11/28-18:13
 */
public class Solution {

  public int lengthOfLongestSubstring(String s) {
    if (s == null || s.isEmpty()) {
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
