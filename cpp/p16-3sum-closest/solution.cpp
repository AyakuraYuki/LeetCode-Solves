//
// Created by 绫仓优希 on 2024-09-10.
//

/*
16. 最接近的三数之和

https://leetcode.cn/problems/3sum-closest/

给你一个长度为 n 的整数数组 nums 和 一个目标值 target。请你从 nums 中选出三个整数，使它们的和与 target 最接近。
返回这三个数的和。
假定每组输入只存在恰好一个解。

示例 1：
    输入：nums = [-1,2,1,-4], target = 1
    输出：2
    解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2)。
示例 2：
    输入：nums = [0,0,0], target = 1
    输出：0
    解释：与 target 最接近的和是 0（0 + 0 + 0 = 0）。

提示：
  * 3 <= nums.length <= 1000
  * -1000 <= nums[i] <= 1000
  * -104 <= target <= 104

相关题目：
  * p15-3sum
 */

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    static int threeSumClosest(vector<int> &nums, const int target) {
        sort(nums.begin(), nums.end());
        const int n = static_cast<int>(nums.size());
        int l = 0, r = 0, ans = nums[0] + nums[1] + nums[2], sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            l = i + 1, r = n - 1;
            while (l < r) {
                sum = nums[i] + nums[l] + nums[r];
                if (abs(target - sum) < abs(target - ans))
                    ans = sum;
                if (sum > target)
                    --r;
                else if (sum < target)
                    ++l;
                else
                    return ans;
            }
        }
        return ans;
    }
};
