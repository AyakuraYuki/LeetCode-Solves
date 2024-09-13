//
// Created by 绫仓优希 on 2024-07-03.
//

/*
28. 找出字符串中第一个匹配项的下标

https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/

给你两个字符串 haystack 和 needle，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。
如果 needle 不是 haystack 的一部分，则返回 -1。

示例 1：
    输入：haystack = "sadbutsad", needle = "sad"
    输出：0
    解释："sad" 在下标 0 和 6 处匹配。
        第一个匹配项的下标是 0 ，所以返回 0 。
示例 2：
    输入：haystack = "leetcode", needle = "leeto"
    输出：-1
    解释："leeto" 没有在 "leetcode" 中出现，所以返回 -1 。

提示：
  - 1 <= haystack.length, needle.length <= 104
  * haystack 和 needle 仅由小写英文字符组成
 */

#include <string>
#include <vector>
#include <__format/format_functions.h>
using namespace std;

class Solution {
public:
    // 滑动窗口：因为本题需要找出第一个匹配的下标，所以可以遍历 haystack，利用滑动窗口来找到第一个匹配的子串
    // 滑动窗口的大小取决于 needle 的长度，如果某一窗口的开头和结尾匹配了 needle 的开头和结尾，再去检查这个窗口是否完全匹配 needle
    // 匹配的过程中为了避免拷贝，尽可能的使用引用和视图。
    // （自己解的）
    static int strStr(const string &haystack, const string &needle) {
        const unsigned int needle_size = needle.size(), haystack_size = haystack.size();
        const char &needle_start = needle[0], &needle_end = needle[needle_size - 1];
        const string_view view(haystack); // 使用视图避免在对比子串时创建新子串
        for (int cursor = 0; cursor + needle_size <= haystack_size; ++cursor) {
            if (view[cursor] == needle_start && view[cursor + needle_size - 1] == needle_end) {
                if (view.substr(cursor, needle_size) == needle) {
                    return cursor;
                }
            }
        }
        return -1;
    }

    // 你就说标准库好不好用吧
    static int str_str_std(const string &haystack, const string &needle) {
        const size_t pos = haystack.find(needle);
        return pos == string::npos ? -1 : static_cast<int>(pos);
    }

    // 大名鼎鼎的 KMP 算法
    static int str_str_kmp(const string &haystack, const string &needle) {
        const unsigned int n = haystack.size(), m = needle.size();
        if (m == 0) return 0; // π(0) = 0

        // 初始化前缀函数的值
        vector pi(m, 0);
        // left 是前缀串开始的下标，right 表示后缀串开始的下标
        for (int left = 0, right = 1; right < m; ++right) {
            while (left > 0 && needle[left] != needle[right]) {
                left = pi[left - 1]; // 匹配不成功，回退 left，直到 left 归零
            }
            if (needle[left] == needle[right]) {
                ++left; // 匹配成功，找到了相同的前后缀，先让 left +1，此时的 left 是前缀长度
            }
            pi[right] = left; // 记录前缀长度，更新到 pi[right]
        }

        // j 是模式串中当前的位置，i 是文本串中当前的位置
        for (int i = 0, j = 0; i < n; ++i) {
            while (j > 0 && haystack[i] != needle[j]) {
                j = pi[j - 1]; // 如果模式串前缀匹配失败，回退模式串的位置，直到 j 归零
            }
            if (haystack[i] == needle[j]) {
                ++j; // 当前模式串的前缀匹配成功，j +1，继续匹配
            }
            if (j == m) {
                return i - m + 1; // 模式串完全匹配，返回匹配开始位置
            }
        }
        return -1;
    }
};
