namespace cc.ayakurayuki.leetcode.csharp.solution.P242ValidAnagram
{
    /// <summary>
    /// 242. Valid Anagram
    ///
    /// https://leetcode.com/problems/valid-anagram/description/
    /// </summary>
    public class Solution
    {
        public bool IsAnagram(string s, string t)
        {
            s = stringSort(s);
            t = stringSort(t);
            return s.Equals(t);
        }

        public static string stringSort(string str)
        {
            char[] ch = new char[512];
            ch = str.ToCharArray();
            Array.Sort(ch);
            return new string(ch);
        }

        static void Main(string[] args)
        {
            Console.WriteLine(new Solution().IsAnagram("anagram", "nagaram")); // True
            Console.WriteLine(new Solution().IsAnagram("rat", "car")); // False
        }
    }
}
