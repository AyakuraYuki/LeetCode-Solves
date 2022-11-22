package cc.ayakurayuki.leetcode.problems.p468validateipaddress

/**
 * [468. Validate IP Address](https://leetcode.com/problems/validate-ip-address/description/)
 *
 * Warning: class name must be changed to {@code Solution} before submit.
 *
 * @author Ayakura Yuki
 * @date Apr 04, 2019 14:22
 */
class KtSolution {
    fun validIPAddress(IP: String): String {
        val ipv4Regex = Regex("(([0-9])|([1-9]\\d)|([1]\\d{2})|(2(([0-4]\\d)|(5[0-5]))))(\\.(([0-9])|([1-9]\\d)|([1]\\d{2})|(2(([0-4]\\d)|(5[0-5]))))){3}")
        val ipv6Regex = Regex("(([\\da-fA-F]{1,4}):){7}([\\da-fA-F]{1,4})")
        return when {
            IP.matches(ipv4Regex) -> "IPv4"
            IP.matches(ipv6Regex) -> "IPv6"
            else -> "Neither"
        }
    }
}
