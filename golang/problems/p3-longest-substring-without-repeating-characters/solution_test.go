package p3_longest_substring_without_repeating_characters

import "testing"

func Test_lengthOfLongestSubstring(t *testing.T) {
	cases := []struct {
		s    string
		want int
	}{
		{"abcabcbb", 3},
		{"bbbbb", 1},
		{"pwwkew", 3},
		{"qrsvbspk", 5},
		{"awabwcdefc", 7},
	}
	for _, v := range cases {
		t.Run(v.s, func(t *testing.T) {
			get := lengthOfLongestSubstring(v.s)
			if get != v.want {
				t.Fatalf("want %d but get %d", v.want, get)
			}
		})
	}
}
