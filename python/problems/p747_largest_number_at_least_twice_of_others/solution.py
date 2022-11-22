# -*- coding: utf-8 -*-

class Solution:
    """
    747. Largest Number At Least Twice of Others

    https://leetcode.com/problems/largest-number-at-least-twice-of-others/description/
    """

    def dominantIndex(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) is 1:
            return 0
        _set = set(nums)
        _max = max(_set)
        _index = nums.index(_max)
        _set.remove(_max)
        if len(_set) == 0:
            return _index
        _sec_max = max(_set)
        if _sec_max * 2 > _max:
            return -1
        return _index
