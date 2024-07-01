package p14_longest_common_prefix

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
