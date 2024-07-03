//
// Created by 绫仓优希 on 2024-07-03.
//

/*
27. 移除元素

https://leetcode.cn/problems/remove-element/

给你一个数组 nums 和一个值 val，你需要【原地】移除所有数值等于 val 的元素。元素的顺序可能发生改变。然后返回 nums 中与 val 不同的元素的数量。
假设 nums 中不等于 val 的元素数量为 k，要通过此题，您需要执行以下操作：
  - 更改 nums 数组，使 nums 的前 k 个元素包含不等于 val 的元素。nums 的其余元素和 nums 的大小并不重要。
  - 返回 k。

用户评测：
评测机将使用以下代码测试您的解决方案：

    int[] nums = [...]; // 输入数组
    int val = ...; // 要移除的值
    int[] expectedNums = [...]; // 长度正确的预期答案。
                                // 它以不等于 val 的值排序。

    int k = removeElement(nums, val); // 调用你的实现

    assert k == expectedNums.length;
    sort(nums, 0, k); // 排序 nums 的前 k 个元素
    for (int i = 0; i < actualLength; i++) {
        assert nums[i] == expectedNums[i];
    }

如果所有的断言都通过，你的解决方案将会通过。

示例 1：
    输入：nums = [3,2,2,3], val = 3
    输出：2, nums = [2,2,_,_]
    解释：你的函数函数应该返回 k = 2, 并且 nums 中的前两个元素均为 2。
        你在返回的 k 个元素之外留下了什么并不重要（因此它们并不计入评测）。
示例 2：
    输入：nums = [0,1,2,2,3,0,4,2], val = 2
    输出：5, nums = [0,1,4,0,3,_,_,_]
    解释：你的函数应该返回 k = 5，并且 nums 中的前五个元素为 0,0,1,3,4。
        注意这五个元素可以任意顺序返回。
        你在返回的 k 个元素之外留下了什么并不重要（因此它们并不计入评测）。

提示：
  - 0 <= nums.length <= 100
  - 0 <= nums[i] <= 50
  - 0 <= val <= 100

hint 1: The problem statement clearly asks us to modify the array in-place and it also says that the element beyond the
        new length of the array can be anything. Given an element, we need to remove all the occurrences of it from the
        array. We don't technically need to remove that element per-say, right?
hint 2: We can move all the occurrences of this element to the end of the array. Use two pointers!
        (`puzzle-images/p27-remove-element/hint_remove_element.png`)
hint 3: Yet another direction of thought is to consider the elements to be removed as non-existent. In a single pass,
        if we keep copying the visible elements in-place, that should also solve this problem for us.
 */

#include <vector>
using namespace std;

class Solution {
public:
    // 遍历重组新的数组：时间复杂度 O(n)，内存占用高，被移除的数值会用 0 在末尾填充
    static int removeElement(vector<int> &nums, const int val) {
        vector temp(nums.size(), 0);
        int counter = 0;
        for (const int num: nums) {
            if (num != val) temp[counter++] = num;
        }
        nums = temp;
        return counter;
    }

    // 不需要开新数组的遍历重组法，末尾会保留脏数据
    // 比如 [0,1,2,2,3,0,4,2] 删除 2，会变成 [0,1,3,0,4,0,4,2]
    static int another_remove_element(vector<int> &nums, const int val) {
        int cursor = 0;
        for (const int num: nums) {
            if (num != val) nums[cursor++] = num;
        }
        return cursor;
    }

    // 一种交换元素的双指针解法，会把需要删除的数值全部放到数组末尾
    // 比如 [0,1,2,2,3,0,4,2] 删除 2，会变成 [0,1,4,0,3,2,2,2]，因为本题不需要我们关注顺序，所以这个结果是可以接受的
    static int remove_element_double_ptr_swap_values(vector<int> &nums, const int val) {
        int j = nums.size() - 1;
        for (int i = 0; i <= j; ++i) {
            if (nums[i] == val) {
                swap(nums[i--], nums[j--]);
            }
        }
        return j + 1;
    }

    // 双指针的官解
    //
    // 如果左指针 left 指向的元素等于 val，此时将右指针 right 指向的元素复制到左指针 left 的位置，然后右指针 right 左移一位。
    // 如果赋值过来的元素恰好也等于 val，可以继续把右指针 right 指向的元素的值赋值过来（左指针 left 指向的等于 val 的元素的位置继续被覆盖），
    // 直到左指针指向的元素的值不等于 val 为止。
    //
    // 当左指针 left 和右指针 right 重合的时候，左右指针遍历完数组中所有的元素。
    // 这样的方法两个指针在最坏的情况下合起来只遍历了数组一次。与方法一不同的是，方法二避免了需要保留的元素的重复赋值操作。
    static int remove_element_solution_from_official(vector<int> &nums, const int val) {
        int left = 0;
        size_t right = nums.size();
        while (left < right) {
            if (nums[left] == val) {
                nums[left] = nums[right - 1];
                --right;
            } else {
                ++left;
            }
        }
        return left;
    }
};
