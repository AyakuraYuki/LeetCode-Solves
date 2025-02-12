//
// Created by 绫仓优希 on 2025-02-07.
//

/*
30. 串联所有单词的子串

https://leetcode.cn/problems/substring-with-concatenation-of-all-words/

给定一个字符串 s 和一个字符串数组 words。words 中所有字符串“长度相同”。

s 中的“串联子串”是指一个包含 words 中所有字符串以任意顺序排列连接起来的子串。

- 例如，如果 words = ["ab","cd","ef"]，那么 "abcdef"，"abefcd"，"cdabef"，"cdefab"，"efabcd" 和 "efcdab" 都是串联子串。
  "acdbef" 不是串联子串，因为他不是任何 words 排列的连接。

返回所有串联子串在 s 中的开始索引。你可以以“任意顺序”返回答案。

示例 1：
    输入：s = "barfoothefoobarman", words = ["foo","bar"]
    输出：[0,9]
    解释：
        因为 words.length == 2 同时 words[i].length == 3，连接的子字符串的长度必须为 6。
        子串 "barfoo" 开始位置是 0。它是 words 中以 ["bar","foo"] 顺序排列的连接。
        子串 "foobar" 开始位置是 9。它是 words 中以 ["foo","bar"] 顺序排列的连接。
        输出顺序无关紧要。返回 [9,0] 也是可以的。
示例 2：
    输入：s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
    输出：[]
    解释：
        因为 words.length == 4 并且 words[i].length == 4，所以串联子串的长度必须为 16。
        s 中没有子串长度为 16 并且等于 words 的任何顺序排列的连接。
        所以我们返回一个空数组。
示例 3：
    输入：s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
    输出：[6,9,12]
    解释：
        因为 words.length == 3 并且 words[i].length == 3，所以串联子串的长度必须为 9。
        子串 "foobarthe" 开始位置是 6。它是 words 中以 ["foo","bar","the"] 顺序排列的连接。
        子串 "barthefoo" 开始位置是 9。它是 words 中以 ["bar","the","foo"] 顺序排列的连接。
        子串 "thefoobar" 开始位置是 12。它是 words 中以 ["the","foo","bar"] 顺序排列的连接。

提示：
  * 1 <= s.length <= 104
  * 1 <= words.length <= 5000
  * 1 <= words[i].length <= 30
  * words[i] 和 s 由小写英文字母组成
 */

#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(const string& s, const vector<string>& words) {
        const int word_len = words[0].size(); // 单词长度
        const int word_count = words.size(); // 单词数量
        // required_len: 所需长度
        if (const int required_len = word_len * word_count; s.size() < required_len) { return {}; }

        unordered_map<string, int> required_map; // 记录每个单词所需要出现的次数
        for (const auto& word : words) required_map[word]++;

        vector<int> res;
        // 滑动窗口起点
        for (int i = 0; i < word_len; i++) {
            int left = i, right = i, count = 0;
            unordered_map<string, int> seen_map;
            // 外层循环控制窗口右边界，每次增长一个单词长度
            for (; right < s.size() - word_len + 1; right += word_len) {
                string right_str = s.substr(right, word_len);
                seen_map[right_str]++;
                count++;

                if (required_map.find(right_str) != required_map.end()) {
                    // 当前单词虽然是所需单词，但已经超过所需次数，需要缩减左窗口，直到单词数符合要求
                    while (seen_map[right_str] > required_map[right_str]) {
                        string left_str = s.substr(left, word_len);
                        seen_map[left_str]--;
                        count--;
                        left += word_len;
                    }
                } else {
                    // 当前单词不是所需单词，左指针跳到这里，重新开始向后滑动
                    seen_map.clear();
                    count = 0;
                    left = right + word_len;
                }

                // 如果当前窗口内的单词数等于 words 内的单词数，则找到一个结果
                if (count == word_count) res.push_back(left);
            }
        }

        return res;
    }
};

// Boyer-Moore 算法
// 参考：https://www.ruanyifeng.com/blog/2013/05/boyer-moore_string_search_algorithm.html
class BoyerMooreSolution {
public:
    vector<int> findSubstring(const string& s, const vector<string>& words) {
        const int n = s.size(), m = words.size(), w = words[0].size();
        const int mwl = n - w * m; // move window limitation
        vector<int> ans; // 结果集

        unordered_map<string, int> dict, cmp; // dict: 单词所需出现次数; cmp: 找到记录
        for (const auto& word : words) dict[word]++;

        if (dict.size() == 1) {
            // Boyer-Moore 算法在字典大小是 1 时退化，特殊处理
            const string target = views::join(words) | ranges::to<string>();
            for (int pos = 0; (pos = s.find(target, pos)) != string::npos; pos++) ans.push_back(pos);
            return ans;
        }

        for (const int start : views::iota(0, w)) {
            for (int i = start, j; i <= mwl; i += w) {
                for (j = i + w * (m - 1); j >= i; j -= w) {
                    // 这里的 j -= w 倒序匹配决定了亚线性的复杂度
                    string str = s.substr(j, w);
                    if (!dict.count(str) || dict[str] == cmp[str]) break;
                    cmp[str]++;
                    if (j == i) {
                        ans.push_back(j);
                        break;
                    }
                }
                i = j;
                cmp.clear();
            }
        }

        return ans;
    }
};

// ----------------------------------------------------------------------------------------------------

class ClassicBoyerMoore {
public:
    static int BM_Search(const char* text, const char* pattern) {
        const int n = strlen(text), m = strlen(pattern);
        if (m == 0) return 0; // 空模式

        int bad_char[256];
        preprocess_bad_char(pattern, m, bad_char);

        const auto good_suffix = new int[m];
        preprocess_good_suffix(pattern, m, good_suffix);

        int s = 0; // s 表示模式串相对于主串的当前对齐位置
        while (s <= n - m) {
            int j = m - 1;
            // 自右向左逐字符匹配
            while (j >= 0 && pattern[j] == text[s + j]) j--;
            if (j < 0) {
                // 找到匹配，返回匹配的起始位置
                delete[] good_suffix;
                return s;
            }
            // 根据坏字符规则：当前主串字符 text[s+j] 在模式串中最后出现的位置为 bad_char[text[s+j]]
            int shift_bad = j - bad_char[static_cast<unsigned char>(text[s + j])];
            // 根据好后缀规则：移动距离为 good_suffix[j]
            int shift_good = good_suffix[j];
            // 两种规则取较大者，并右移一位
            s += max(1, max(shift_bad, shift_good));
        }

        delete[] good_suffix;
        return -1; // 没有找到匹配
    }

private:
    // 坏字符的预处理
    static void preprocess_bad_char(const char* pattern, const int m, int bad_char[]) {
        // 初始化所有字符的最后出现位置为 -1
        for (int i = 0; i < 256; i++) bad_char[i] = -1;
        // 扫描模式串，记录每个字符最后一次出现的位置
        for (int i = 0; i < m; i++) bad_char[static_cast<unsigned char>(pattern[i])] = i;
    }

    // 构造好后缀
    static void preprocess_good_suffix(const char* pattern, const int m, int good_suffix[]) {
        const auto suffix = new int[m];
        compute_suffix(pattern, m, suffix);

        // 初始化所有位置的右移值为 m
        for (int i = 0; i < m; i++) good_suffix[i] = m;

        int j = 0;

        // 第一阶段：找到后缀也是模式串前缀的可能
        for (int i = m - 1; i >= 0; i--) {
            if (suffix[i] == i + 1) {
                // 对于所有位置的 j 从 0 到 m-1，如果尚未赋值，则更新
                for (; j < m - 1 - i; j++) {
                    if (good_suffix[j] == m)
                        good_suffix[j] = m - 1 - i;
                }
            }
        }

        // 第二阶段：对于其他位置，根据内部重复出现的好后缀调整
        for (int i = 0; i < m - 2; i++) good_suffix[m - 1 - suffix[i]] = m - 1 - i;

        delete[] suffix;
    }

    // 好后缀的预处理
    static void compute_suffix(const char* pattern, const int m, int suffix[]) {
        suffix[m - 1] = m; // 整个模式串总能匹配自己
        int g = m - 1, f = 0;
        for (int i = m - 2; i >= 0; i--) {
            if (i > g && suffix[i + m - 1 - f] < i - g)
                suffix[i] = suffix[i + m - 1 - f];
            else {
                if (i < g) g = i;
                f = i;
                while (g >= 0 && pattern[g] == pattern[g + m - 1 - f]) g--;
                suffix[i] = f - g;
            }
        }
    }
};

// ----------------------------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    auto res = Solution().findSubstring("barfoothefoobarman", {"foo", "bar"});
    auto step = 1;
}
