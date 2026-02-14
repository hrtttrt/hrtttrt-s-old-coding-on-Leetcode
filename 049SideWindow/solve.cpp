#include<bits/stdc++.h>
using namespace std;

// 一、累加和大于等于target的最短子数组长度
// 给定一个含有 n 个正整数的数组和一个正整数 target
// 找到累加和 >= target 的长度最小的子数组并返回其长度
// 如果不存在符合条件的子数组返回0
// 测试链接 : https://leetcode.cn/problems/minimum-size-subarray-sum/
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) 
    {
        int sum=0;
        int ans=INT_MAX;
        for(int l=0,r=0;r<nums.size();r++)
        {
            sum+=nums[r];
            while(sum-nums[l]>=target)
            {
                sum-=nums[l];
                l++;
            }
            if(sum>=target) ans=min(ans,r-l+1);
        }
        return ans==INT_MAX?0:ans;
    }
};

// 二、无重复字符的最长子串
// 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
// s由英文字母、数字、符号和空格组成                                    <-所以要造数组（char范围是0~255）
// 测试链接 : https://leetcode.cn/problems/longest-substring-without-repeating-characters/
class Solution {
public:
    int lengthOfLongestSubstring(string s) 
    {
        int len=0;
        vector<int> cnt;
        cnt.resize(256);
        for(int r=0,l=0;r<s.length();r++)
        {
            if(cnt[s[r]]!=0) l=max(l,cnt[s[r]]);
            len=max(len,r-l+1);
            cnt[s[r]]=r+1;
        }
        return len;
    }
};

// 三、最小覆盖子串
// 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串
// s 和 t 由英文字母组成
// 如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
// 测试链接 : https://leetcode.cn/problems/minimum-window-substring/
class Solution {
public:
    string minWindow(string s, string t) 
    {
        if(s.length()<t.length()) return "";
        vector<int> cnt;
        cnt.resize(256);
        int len=INT_MAX;
        int start=-1;
        for(int i=0;i<t.length();i++)
        {
            cnt[t[i]]--;
        }
        int debt=t.length();
        for(int l=0,r=0;r<s.length();r++)
        {
            if(cnt[s[r]]++<0) //判断该字母“负债”情况,总要++，但是有负债时debt才--
            {
                debt--;
            }
            if(debt==0)
            {
                while(cnt[s[l]]>0) 
                {
                    cnt[s[l++]]--;
                }
                if(len>r-l+1)
                {
                    len=r-l+1;
                    start=l;
                }
            }
        }
        if(start==-1) return "";
        else return s.substr(start,len); //substr(起始位置，长度)
    }
};

// 四、加油站
// 在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。
// 你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升
// 你从其中的一个加油站出发，开始时油箱为空。
// 给定两个整数数组 gas 和 cost ，如果你可以按顺序绕环路行驶一周
// 则返回出发时加油站的编号，否则返回 -1
// 如果存在解，则 保证 它是 唯一 的。
// 测试链接 : https://leetcode.cn/problems/gas-station/


// 五、替换子串得到平衡字符串
// 有一个只含有 'Q', 'W', 'E', 'R' 四种字符，且长度为 n 的字符串。
// 假如在该字符串中，这四个字符都恰好出现 n/4 次，那么它就是一个「平衡字符串」。
// 给你一个这样的字符串 s，请通过「替换一个子串」的方式，使原字符串 s 变成一个「平衡字符串」。
// 你可以用和「待替换子串」长度相同的 任何 其他字符串来完成替换。
// 请返回待替换子串的最小可能长度。
// 如果原字符串自身就是一个平衡字符串，则返回 0。
// 测试链接 : https://leetcode.cn/problems/replace-the-substring-for-balanced-string/


// 六、K个不同整数的子数组
// 给定一个正整数数组 nums和一个整数 k，返回 nums 中 「好子数组」 的数目。
// 如果 nums 的某个子数组中不同整数的个数恰好为 k
// 则称 nums 的这个连续、不一定不同的子数组为 「好子数组 」。
// 例如，[1,2,3,1,2] 中有 3 个不同的整数：1，2，以及 3。
// 子数组 是数组的 连续 部分。
// 测试链接 : https://leetcode.cn/problems/subarrays-with-k-different-integers/


// 七、至少有K个重复字符的最长子串
// 给你一个字符串 s 和一个整数 k ，请你找出 s 中的最长子串
// 要求该子串中的每一字符出现次数都不少于 k 。返回这一子串的长度
// 如果不存在这样的子字符串，则返回 0。
// 测试链接 : https://leetcode.cn/problems/longest-substring-with-at-least-k-repeating-characters/