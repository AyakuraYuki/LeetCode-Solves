# -*- coding: utf-8 -*-

class Solution:
    """
    724. Find Pivot Index

    https://leetcode.com/problems/find-pivot-index/description/
    """

    def pivotIndex(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        _sum = sum(nums)
        _cursor = 0
        for i in range(0, len(nums)):
            if _sum - nums[i] == _cursor * 2:
                return i
            _cursor += nums[i]
        return -1
