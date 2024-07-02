//
// Created by 绫仓优希 on 2024-06-26.
//

/*
468. 验证IP地址

https://leetcode.cn/problems/validate-ip-address/

给定一个字符串 queryIP。
如果是有效的 IPv4 地址，返回 "IPv4"；
如果是有效的 IPv6 地址，返回 "IPv6"；
如果不是上述类型的 IP 地址，返回 "Neither"。

有效的IPv4地址 是 “x1.x2.x3.x4” 形式的IP地址。
其中 0 <= xi <= 255 且 xi 不能包含 前导零。
例如: “192.168.1.1”、“192.168.1.0”为有效IPv4地址，“192.168.01.1”为无效IPv4地址；“192.168.1.00”、“192.168@1.1”为无效IPv4地址。

一个有效的IPv6地址 是一个格式为“x1:x2:x3:x4:x5:x6:x7:x8” 的IP地址，其中:
  * 1 <= xi.length <= 4
  * xi 是一个 十六进制字符串 ，可以包含数字、小写英文字母( 'a' 到 'f' )和大写英文字母( 'A' 到 'F' )。
  * 在 xi 中允许前导零。

例如 "2001:0db8:85a3:0000:0000:8a2e:0370:7334" 和 "2001:db8:85a3:0:0:8A2E:0370:7334" 是有效的 IPv6 地址，
而 "2001:0db8:85a3::8A2E:037j:7334" 和 "02001:0db8:85a3:0000:0000:8a2e:0370:7334" 是无效的 IPv6 地址。

示例 1：
    输入：queryIP = "172.16.254.1"
    输出："IPv4"
    解释：有效的 IPv4 地址，返回 "IPv4"
示例 2：
    输入：queryIP = "2001:0db8:85a3:0:0:8A2E:0370:7334"
    输出："IPv6"
    解释：有效的 IPv6 地址，返回 "IPv6"
示例 3：
    输入：queryIP = "256.256.256.256"
    输出："Neither"
    解释：既不是 IPv4 地址，又不是 IPv6 地址

提示：
  * queryIP 仅由英文字母，数字，字符 '.' 和 ':' 组成。
 */

#include <string>
using namespace std;

class Solution {
public:
    string validIPAddress(const string &query_ip) {
        if (query_ip.find('.') != string::npos) {
            return is_ipv4(query_ip) ? "IPv4" : "Neither";
        }
        if (query_ip.find(':') != string::npos) {
            return is_ipv6(query_ip) ? "IPv6" : "Neither";
        }
        return "Neither";
    }

private:
    static bool is_ipv4(const string &query_ip) {
        const size_t string_len = query_ip.size();
        size_t index = 0;
        int segment = 0;

        while (index < string_len) {
            int val = 0; // 某一部分的数值
            int digit = 0; // 某一部分的字符个数的计数器
            while (index < string_len) {
                const char *ch = &query_ip[index++];
                if (const int c = *ch - '0'; 0 <= c && c <= 9) {
                    val = val * 10 + c;
                    ++digit;
                    if (digit > 3) return false; // 字符个数超过 3 个，说明这个部分不是合法的 IPv4 组成部分
                } else if (*ch == '.') {
                    if (index == string_len) return false; // 末位是分隔符不符合 IPv4 的构成规则
                    break;
                } else {
                    return false; // 任何其他的字符，比如英文字母或者标点符号等等，都不符合 IPv4 的构成规则
                }
            }
            ++segment;
            if (digit > 1 && val / pow(10, digit - 1) < 1) return false;
            if (digit == 0 || val > 255) return false;
            if (index == string_len) return segment == 4;
        }

        return false;
    }

    static bool is_ipv6(const string &query_ip) {
        int index = 0, segment = 0;
        const size_t string_len = query_ip.size();
        while (index < string_len) {
            int digit = 0;
            while (index < string_len) {
                if (const char *ch = &query_ip[index++];
                    ('0' <= *ch && *ch <= '9') || ('A' <= *ch && *ch <= 'F') || ('a' <= *ch && *ch <= 'f')) {
                    ++digit;
                } else if (*ch == ':') {
                    if (index == string_len) return false;
                    break;
                } else return false;
            }
            ++segment;
            if (digit == 0 || digit > 4) return false;
            if (index == string_len) return segment == 8;
        }
        return false;
    }
};

class ScanSolution {
public:
    string Neither = "Neither";

    string validIPAddress(const string &query_ip) {
        if (query_ip.find('.') != string::npos) {
            // IPv4
            // 对于 IPv4 而言，它有 4 个部分，用 '.' 隔开。
            // 我们可以存储相邻两个 '.' 出现的位置作为 last 和 current，那么子串 query_ip[last+1..current-1] 就是一个部分，
            // 考虑到首个部分时，last = -1，考虑到末位时 current = query_ip.size()。
            // 一个部分需要满足：
            // 1. 长度在 [1, 3] 之间
            // 2. 应该由纯数字组成
            // 3. 这个部分的数值是否在 [0, 255] 之间
            // 4. 它是否不包含前导的 0。具体来说：
            //   1) 如果它是 0，那么这个部分只能包含一个 0，即 (current - 1) - (last + 1) + 1 = 1
            //   2) 如果它不是 0，那么这个部分不能以 0 开头，即 query_ip[last + 1] != '0'
            size_t last = -1;
            for (int i = 0; i < 4; ++i) {
                const size_t current = i == 3 ? query_ip.size() : query_ip.find('.', last + 1);
                if (current == string::npos) return Neither;
                if (current - last - 1 < 1 || current - last - 1 > 3) return Neither;
                int addr = 0;
                for (size_t j = last + 1; j < current; ++j) {
                    if (!isdigit(query_ip[j])) return Neither;
                    addr = addr * 10 + (query_ip[j] - '0');
                }
                if (addr > 255) return Neither;
                if (addr > 0 && query_ip[last + 1] == '0') return Neither;
                if (addr == 0 && current - last - 1 > 1) return Neither;
                last = current;
            }
            return "IPv4";
        } else {
            // IPv6
            //
            // 对于 IPv6 而言，它有 8 个部分，用 ':' 隔开。
            // 我们可以存储相邻两个 ':' 出现的位置作为 last 和 current，那么子串 query_ip[last+1..current-1] 就对应一个部分，
            // 一个部分需要满足：
            // 1. 长度是否在 [1, 4] 之间
            // 2. 是否只包含合法的十六进制字符 [0-9a-fA-F]+
            // 不满足这两个规则的，说明字符串不是有效的 IPv6 地址
            size_t last = -1;
            for (int i = 0; i < 8; ++i) {
                const size_t current = i == 7 ? query_ip.size() : query_ip.find(':', last + 1);
                if (current == string::npos) return Neither;
                if (current - last - 1 < 1 || current - last - 1 > 4) return Neither;
                for (size_t j = last + 1; j < current; ++j) {
                    if (!isdigit(query_ip[j])
                        && !('a' <= query_ip[j] && query_ip[j] <= 'f')
                        && !('A' <= query_ip[j] && query_ip[j] <= 'F')) {
                        return Neither;
                    }
                }
                last = current;
            }
            return "IPv6";
        }
    }
};
