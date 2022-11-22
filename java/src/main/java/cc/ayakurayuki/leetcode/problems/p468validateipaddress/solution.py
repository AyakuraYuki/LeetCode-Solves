class Solution(object):
  def validIPAddress(self, IP):
    """
    :type IP: str
    :rtype: str
    """
    if IP.count('.') == 3:
      arr = IP.split('.')
      if len(arr) != 4:
        return 'Neither'
      for x in arr:
        if len(x) > 1 and (x.startswith('0') or x.startswith('-')):
          return 'Neither'
        try:
          y = int(x)
          if not (0 <= y <= 255):
            return 'Neither'
        except Exception:
          return 'Neither'
      return 'IPv4'
    elif IP.count(':') == 7:
      arr = IP.split(':')
      if len(arr) != 8:
        return 'Neither'
      for x in arr:
        if len(x) > 4 or x.startswith('-'):
          return 'Neither'
        try:
          y = int(x, base=16)
        except Exception:
          return 'Neither'
      return 'IPv6'
    else:
      return 'Neither'


if __name__ == '__main__':
  print(Solution().validIPAddress('1e0.0.0.-0'))
