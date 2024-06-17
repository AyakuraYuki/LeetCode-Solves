package p14_longest_common_prefix

import (
	"testing"
)

func Test_longestCommonPrefix(t *testing.T) {
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
			t.Fatalf("want %s, got %s", c.Want, prefix)
		}
	}
}
