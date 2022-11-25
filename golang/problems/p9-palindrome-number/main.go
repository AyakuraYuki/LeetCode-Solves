/*
9. Palindrome Number

https://leetcode.com/problems/palindrome-number/

Given an integer `x`, return `true` if `x` is a palindrome, and `false` otherwise.

About palindrome:

An integer is a palindrome when it reads the same forward and backward.

For example, `121` is a palindrome while `123` is not.


Example 1:
-> 121
<- true
Explanation: 121 reads as 121 from left to right and from right to left.

Example 2:
-> -121
<- false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore, it is not a palindrome.

Example 3:
-> 10
<- false
Explanation: Reads 01 from right to left. Therefore, it is not a palindrome.

Constraints:
-231 <= x <= 231 - 1

Follow up: Could you solve it without converting the integer to a string?
*/

package main

import "fmt"

// region solve

// isPalindrome 取反计算再对比值
func isPalindrome(x int) bool {
	if x < 0 {
		return false
	}
	sum := 0
	origin := x
	for x > 0 {
		num := x % 10
		sum = sum*10 + num
		x /= 10
	}
	return sum == origin
}

// isPalindromeByFlip 根据回文特点，翻转对比
func isPalindromeByFlip(x int) bool {
	if x < 0 {
		return false
	}
	if x%10 == 0 && x != 0 {
		// 首尾不对称
		return false
	}
	rev := 0
	for x > rev {
		rev = rev*10 + x%10
		x /= 10
	}
	return x == rev || x == rev/10
}

// endregion

func main() {
	tests := []int{
		121, -121, 10, 1919191, 190098,
	}
	for _, test := range tests {
		fmt.Printf("test: %d, result: %v\n", test, isPalindromeByFlip(test))
	}
}
