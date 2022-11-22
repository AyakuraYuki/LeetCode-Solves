# -*- coding: utf-8 -*-

class Solution:
    """
    1. Two Sum

    https://leetcode.com/problems/two-sum/description/
    """

    def twoSum(self, nums, target):
        dictionary = {}
        for key, value in enumerate(nums):
            complement = target - value
            if complement in dictionary:
                return [dictionary.get(complement), key]
            dictionary[value] = key
