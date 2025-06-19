//
// Created by 绫仓优希 on 25-6-19.
//

/*
31. 下一个排列

https://leetcode.cn/problems/next-permutation/

备注：字节一面背诵题

整数数组的一个 排列  就是将其所有成员以序列或线性顺序排列。

例如，arr = [1,2,3]，以下这些都可以视作 arr 的排列：[1,2,3]、[1,3,2]、[3,1,2]、[2,3,1]。
整数数组的“下一个排列”是指其整数的下一个字典序更大的排列。更正式地，如果数组的所有排列根据其字典顺序从小到大排列在一个容器中，
那么数组的“下一个排列”就是在这个有序容器中排在它后面的那个排列。如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的
排列（即，其元素按升序排列）。

- 例如，arr = [1,2,3] 的下一个排列是 [1,3,2]。
- 类似地，arr = [2,3,1] 的下一个排列是 [3,1,2]。
- 而 arr = [3,2,1] 的下一个排列是 [1,2,3] ，因为 [3,2,1] 不存在一个字典序更大的排列。

给你一个整数数组 nums，找出 nums 的下一个排列。

必须“原地”修改，只允许使用额外常数空间。

示例 1：
    输入：nums = [1,2,3]
    输出：[1,3,2]
示例 2：
    输入：nums = [3,2,1]
    输出：[1,2,3]
示例 3：
    输入：nums = [1,1,5]
    输出：[1,5,1]

提示：
  * 1 <= nums.length <= 100
  * 0 <= nums[i] <= 100
 */

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    /// 解题思路
    /// 全排列采用双指针逆序检索，发现右侧大于左侧，左右侧数值相互交换后即可得到新的排列
    /// 因为本题目只需要下一个排列结果，所以只需要交换一次就能拿到答案
    /// 最好的结果是第一组指针就找到可以交换的双方元素
    /// 最差的结果是，vec 全部元素按照完全倒序排列，则需要全部扫描后，才能走到反转 vec 的操作
    static void nextPermutation(vector<int>& nums) {
        for (int i = nums.size() - 1; i >= 0; i--) {
            for (int j = nums.size() - 1; j > i; j--) {
                if (nums[j] > nums[i]) {
                    swap(nums[j], nums[i]);
                    reverse(nums.begin() + i + 1, nums.end());
                    return;
                }
            }
        }
        reverse(nums.begin(), nums.end()); // 到这里了说明整个数组都是倒序了，反转一下便可
    }
};

class StdSolution {
public:
    /// STL全排列，没什么好说的
    static void nextPermutation(vector<int>& nums) {
        next_permutation(nums.begin(), nums.end());
    }
};

int main() {
    vector nums = {1, 2, 3};
    for (int i = 0; i < 10; ++i) {
        Solution::nextPermutation(nums);
        cout << nums[0] << nums[1] << nums[2] << endl;
    }
}
