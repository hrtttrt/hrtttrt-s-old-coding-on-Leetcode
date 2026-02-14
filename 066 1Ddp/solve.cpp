#include<bits/stdc++.h>
using namespace std;
// 一、最低票价
// 在一个火车旅行很受欢迎的国度，你提前一年计划了一些火车旅行
// 在接下来的一年里，你要旅行的日子将以一个名为 days 的数组给出
// 每一项是一个从 1 到 365 的整数
// 火车票有 三种不同的销售方式
// 一张 为期1天 的通行证售价为 costs[0] 美元
// 一张 为期7天 的通行证售价为 costs[1] 美元
// 一张 为期30天 的通行证售价为 costs[2] 美元
// 通行证允许数天无限制的旅行
// 例如，如果我们在第 2 天获得一张 为期 7 天 的通行证
// 那么我们可以连着旅行 7 天(第2~8天)
// 返回 你想要完成在给定的列表 days 中列出的每一天的旅行所需要的最低消费
// 测试链接 : https://leetcode.cn/problems/minimum-cost-for-tickets/
class Solution {
public:
    vector<int> dur={1,7,30};
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        vector<int> dp;
        dp.resize(days.size());
        for(int i=0;i<days.size();i++)
        {
            dp[i]=INT_MAX;
        }
        return f(days,costs,dp,0);
    }
    int f(vector<int>& days, vector<int>& costs,vector<int>& dp,int n)
    {
        if(n==days.size()) return 0;
        else if(dp[n]!=INT_MAX) return dp[n];
        else
        {
            int ans=INT_MAX;
            for(int j=0;j<3;j++)
            {
                int i=n;
                while(i<days.size()&&days[n]+dur[j]>days[i]) i++;//注意边界条件，i是第一个该方案无法覆盖的日期
                ans=min(ans,costs[j]+f(days,costs,dp,i));
            }
            dp[n]=ans;
            return ans;
        }
    }
};

// 二、解码方法
// 一条包含字母 A-Z 的消息通过以下映射进行了 编码 ：
// 'A' -> "1"
// 'B' -> "2"
// ...
// 'Z' -> "26"
// 要 解码 已编码的消息，所有数字必须基于上述映射的方法，反向映射回字母（可能有多种方法）
// 例如，"11106" 可以映射为："AAJF"、"KJF"
// 注意，消息不能分组为(1 11 06)，因为 "06" 不能映射为 "F"
// 这是由于 "6" 和 "06" 在映射中并不等价
// 给你一个只含数字的 非空 字符串 s ，请计算并返回 解码 方法的 总数
// 题目数据保证答案肯定是一个 32位 的整数
// 测试链接 : https://leetcode.cn/problems/decode-ways/
class Solution {
public:
    int numDecodings(string s) {
        vector<int> dp;
        dp.resize(s.length());
        for(int i=0;i<s.length();i++)
        {
            dp[i]=-1;
        }
        return f(s,dp,0);
    }
    int f(string s,vector<int>& dp,int n)
    {
        if(n==s.length()) return 1;
        else if(dp[n]!=-1) return dp[n];
        else
        {
            int ans;
            if(s[n]-'0'==0) ans=0;
            else
            {
                ans=f(s,dp,n+1);
                if(n<s.length()-1&&(s[n]-'0')*10+(s[n+1]-'0')<=26) ans+=f(s,dp,n+2);
            }
            dp[n]=ans;
            return ans;
        }
    }
};

// 三、解码方法 II
// 一条包含字母 A-Z 的消息通过以下的方式进行了 编码 ：
// 'A' -> "1"
// 'B' -> "2"
// ...
// 'Z' -> "26"
// 要 解码 一条已编码的消息，所有的数字都必须分组
// 然后按原来的编码方案反向映射回字母（可能存在多种方式）
// 例如，"11106" 可以映射为："AAJF"、"KJF"
// 注意，像 (1 11 06) 这样的分组是无效的，"06"不可以映射为'F'
// 除了上面描述的数字字母映射方案，编码消息中可能包含 '*' 字符
// 可以表示从 '1' 到 '9' 的任一数字（不包括 '0'）
// 例如，"1*" 可以表示 "11"、"12"、"13"、"14"、"15"、"16"、"17"、"18" 或 "19"
// 对 "1*" 进行解码，相当于解码该字符串可以表示的任何编码消息
// 给你一个字符串 s ，由数字和 '*' 字符组成，返回 解码 该字符串的方法 数目
// 由于答案数目可能非常大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/decode-ways-ii/
class Solution {
public:
    int numDecodings(string s) {
        vector<long> dp;
        dp.resize(s.length());
        for(int i=0;i<s.length();i++)
        {
            dp[i]=-1;
        }
        return (int)f(s,dp,0);
    }
    long f(string& s,vector<long>& dp,int n)//并非最优解
    {
        if(n==s.length()) return 1;
        else if(dp[n]!=-1) return dp[n];
        else
        {
            long ans;
            if(s[n]-'0'==0) ans=0;
            else
            {
                if(s[n]=='*')
                {
                    if(n==s.length()-1) ans=9;
                    else if(s[n+1]=='*') ans=f(s,dp,n+1)*9+f(s,dp,n+2)*15; //以0开头无法解码，故26-9
                    else 
                    {
                        ans=f(s,dp,n+1)*9;
                        if(s[n+1]-'0'<=6) ans+=f(s,dp,n+2)*2;
                        else ans+=f(s,dp,n+2);
                    }
                }
                else 
                {
                    ans=f(s,dp,n+1);
                    if(n==s.length()-1) ans=1;
                    else if(s[n]=='1'&&s[n+1]=='*') ans+=f(s,dp,n+2)*9;
                    else if(s[n]=='2'&&s[n+1]=='*') ans+=f(s,dp,n+2)*6;
                    else if(n<s.length()-1&&s[n+1]!='*'&&(s[n]-'0')*10+(s[n+1]-'0')<=26) ans+=f(s,dp,n+2);
                }
            }
            dp[n]=ans%1000000007;
            return ans%1000000007;
        }
    }
};


// 四、丑数 II
// 给你一个整数 n ，请你找出并返回第 n 个 丑数
// 丑数 就是只包含质因数 2、3 或 5 的正整数
// 测试链接 : https://leetcode.cn/problems/ugly-number-ii/
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> nums;
        nums.resize(n+1);
        nums[1]=1;
        int a,b,c;
        for(int i=2,i2=1,i3=1,i5=1;i<=n;i++)
        {
            a=nums[i2]*2;
            b=nums[i3]*3;
            c=nums[i5]*5;
            nums[i]=min(min(a,b),c);
            if(nums[i]==a) i2++;
            if(nums[i]==b) i3++;
            if(nums[i]==c) i5++;
        }
        return nums[n];
    }
};

// 最长有效括号
// 给你一个只包含 '(' 和 ')' 的字符串
// 找出最长有效（格式正确且连续）括号子串的长度。
// 测试链接 : https://leetcode.cn/problems/longest-valid-parentheses/


// 环绕字符串中唯一的子字符串
// 定义字符串 base 为一个 "abcdefghijklmnopqrstuvwxyz" 无限环绕的字符串
// 所以 base 看起来是这样的：
// "..zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd.."
// 给你一个字符串 s ，请你统计并返回 s 中有多少 不同非空子串 也在 base 中出现
// 测试链接 : https://leetcode.cn/problems/unique-substrings-in-wraparound-string/


// 不同的子序列 II
// 给定一个字符串 s，计算 s 的 不同非空子序列 的个数
// 因为结果可能很大，答案对 1000000007 取模
// 字符串的 子序列 是经由原字符串删除一些（也可能不删除）
// 字符但不改变剩余字符相对位置的一个新字符串
// 例如，"ace" 是 "abcde" 的一个子序列，但 "aec" 不是
// 测试链接 : https://leetcode.cn/problems/distinct-subsequences-ii/