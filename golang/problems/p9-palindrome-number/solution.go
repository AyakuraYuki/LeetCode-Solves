package p9_palindrome_number

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
