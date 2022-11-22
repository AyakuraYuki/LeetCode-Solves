package cc.ayakurayuki.leetcode.problems.p468validateipaddress;

/**
 * [468] <a href="https://leetcode.com/problems/validate-ip-address/description/">Validate IP Address</a>
 *
 * @author Ayakura Yuki
 * @date Apr 04, 2019 14:22
 */
public class Solution {

  public String validIPAddress(String IP) {
    if (IP.indexOf('.') > 0) {
      return isIPv4(IP.toCharArray()) ? "IPv4" : "Neither";
    } else if (IP.indexOf(':') > 0) {
      return isIPv6(IP.toCharArray()) ? "IPv6" : "Neither";
    } else {
      return "Neither";
    }
  }

  private boolean isIPv4(char[] IP) {
    int index = 0;
    int segment = 0;
    while (index < IP.length) {
      int val = 0;
      int digit = 0;
      while (index < IP.length) {
        char ch = IP[index++];
        int c = ch - '0';
        if (c >= 0 && c <= 9) {
          val = val * 10 + c;
          digit++;
        } else if (ch == '.') {
          if (index == IP.length) {
            return false;
          }
          break;
        } else {
          return false;
        }
      }
      segment++;
      if (digit > 1 && val / Math.pow(10, digit - 1) < 1) {
        return false;
      }
      if (digit == 0 || val > 255) {
        return false;
      }
      if (index == IP.length) {
        return segment == 4;
      }
    }
    return false;
  }

  private boolean isIPv6(char[] IP) {
    int index = 0;
    int segment = 0;
    while (index < IP.length) {
      int digit = 0;
      while (index < IP.length) {
        char ch = IP[index++];
        if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f')) {
          digit++;
        } else if (ch == ':') {
          if (index == IP.length) {
            return false;
          }
          break;
        } else {
          return false;
        }
      }
      segment++;
      if (digit == 0 || digit > 4) {
        return false;
      }
      if (index == IP.length) {
        return segment == 8;
      }
    }
    return false;
  }

}
