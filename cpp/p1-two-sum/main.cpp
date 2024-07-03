//
// Created by 绫仓优希 on 2024-06-26.
//

/*
1. 两数之和

https://leetcode.cn/problems/two-sum/

给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

示例 1：
    输入：nums = [2,7,11,15], target = 9
    输出：[0,1]
    解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
示例 2：
    输入：nums = [3,2,4], target = 6
    输出：[1,2]
示例 3：
    输入：nums = [3,3], target = 6
    输出：[0,1]

提示：
  - 2 <= nums.length <= 104
  - -109 <= nums[i] <= 109
  - -109 <= target <= 109
  - 只会存在一个有效答案

进阶：你可以想出一个时间复杂度小于 O(n2) 的算法吗？
 */

#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        // 开一个map存储数字和索引，key是数值，value是这个数值出现的索引号
        unordered_map<int, int> map;
        // 遍历 nums 同时做计算
        for (int i = 0; i < nums.size(); ++i) {
            if (auto it = map.find(target - nums[i]); it != map.end()) {
                // 找到另一个加数，返回另一个加数和当前这个数的索引
                return {it->second, i};
            }
            // 找不到合适的另一个加数，把当前这个数放到map里暂存
            map[nums[i]] = i;
        }
        return {};
    }
};
