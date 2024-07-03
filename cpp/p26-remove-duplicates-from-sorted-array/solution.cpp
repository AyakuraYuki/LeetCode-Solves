//
// Created by 绫仓优希 on 2024-07-03.
//

/*
26. 删除有序数组中的重复项

https://leetcode.cn/problems/remove-duplicates-from-sorted-array/

给你一个 非严格递增排列 的数组 nums，请你【原地】删除重复出现的元素，使每个元素【只出现一次】，返回删除后数组的新长度。
元素的【相对顺序】应该保持【一致】。然后返回 nums 中唯一元素的个数。

考虑 nums 的唯一元素的数量为 k ，你需要做以下事情确保你的题解可以被通过：
  * 更改数组 nums ，使 nums 的前 k 个元素包含唯一元素，并按照它们最初在 nums 中出现的顺序排列。nums 的其余元素与 nums 的大小不重要。
  * 返回 k。

判题标准:
系统会用下面的代码来测试你的题解:

    int[] nums = [...]; // 输入数组
    int[] expectedNums = [...]; // 长度正确的期望答案

    int k = removeDuplicates(nums); // 调用

    assert k == expectedNums.length;
    for (int i = 0; i < k; i++) {
        assert nums[i] == expectedNums[i];
    }

如果所有断言都通过，那么您的题解将被通过。

示例 1：
    输入：nums = [1,1,2]
    输出：2, nums = [1,2,_]
    解释：函数应该返回新的长度 2 ，并且原数组 nums 的前两个元素被修改为 1, 2 。不需要考虑数组中超出新长度后面的元素。
示例 2：
    输入：nums = [0,0,1,1,1,2,2,3,3,4]
    输出：5, nums = [0,1,2,3,4]
    解释：函数应该返回新的长度 5 ， 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4 。不需要考虑数组中超出新长度后面的元素。


提示：
  * 1 <= nums.length <= 3 * 104
  * -104 <= nums[i] <= 104
  * nums 已按 非严格递增 排列

hint 1: In this problem, the key point to focus on is the input array being sorted. As far as duplicate elements are
        concerned, what is their positioning in the array when the given array is sorted? Look at the image below for
        the answer. If we know the position of one of the elements, do we also know the positioning of all the
        duplicate elements?
        (`puzzle-images/p26-remove-duplicates-from-sorted-array/hint_rem_dup.png`)
hint 2: We need to modify the array in-place and the size of the final array would potentially be smaller than the size
        of the input array. So, we ought to use a two-pointer approach here. One, that would keep track of the current
        element in the original array and another one for just the unique elements.
hint 3: Essentially, once an element is encountered, you simply need to bypass its duplicates and move on to the next
        unique element.
 */

#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    static int removeDuplicates(vector<int> &nums) {
        // 空列表断路
        if (nums.empty()) return 0;

        // 游标指向参考值，参考值的下一个位置会被替换成与参考值不同的值，在【非严格递增排序】的条件下，参考值的下一个位置会比参考值大
        int cursor = 0;
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (nums[i + 1] != nums[i]) {
                // 找到前后不一致的值，则把参考值的下一位赋值到 i+1 位置的数，然后游标指向下一位
                nums[cursor + 1] = nums[i + 1];
                ++cursor;
            }
        }
        return cursor + 1;
    }
};

// 双指针法
// time: 14ms (16.47%), rem: 22.65 MB (5.01%)
class DoublePtrSolution {
public:
    static int removeDuplicates(vector<int> &nums) {
        // 空列表断路
        if (nums.empty()) return 0;

        // 双指针，p 是前一个指针，q 是后一个指针
        int p = 0, q = 1;
        // 顺序扫描，而不是从两边向中间扫描
        while (q < nums.size()) {
            // 如果位置 q 的值不等于位置 p 的值，根据【非严格递增排序】的条件，可以知道后面的值一定大于前面的值
            // 那么可以把位置 q 的值放到位置 p+1，然后 p 进位到 p+1
            if (nums[p] != nums[q]) {
                // 这里的判断是因为如果数组中存在连续递增的部分，那么这部分的数值是不需要拷贝的
                if (q - p > 1) {
                    nums[p + 1] = nums[q];
                }
                ++p;
            }
            // 无论 p 有没有进位，q 都应该进位，去拿后面的值跟位置 p 的值对比
            ++q;
        }
        return p + 1;
    }
};

// 作为一款最慢的解决方案，它完美的利用了现有工具集的特性，来实现最费时也最浪费空间的解决办法
// time: 14ms (16.47%), rem: 22.65 MB (5.01%)
class SlowestSolution {
public:
    static int removeDuplicates(vector<int> &nums) {
        // 空列表断路
        if (nums.empty()) return 0;

        const unordered_set set(nums.begin(), nums.end());
        nums = vector(set.begin(), set.end());
        sort(nums.begin(), nums.end());
        return nums.size();
    }
};
