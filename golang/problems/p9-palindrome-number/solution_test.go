package p9_palindrome_number

import (
	"testing"
)

func Test_isPalindromeByFlip(t *testing.T) {
	tests := []int{
		121, -121, 10, 1919191, 190098,
	}
	for _, test := range tests {
		t.Logf("test: %d, result: %v", test, isPalindromeByFlip(test))
	}
}
