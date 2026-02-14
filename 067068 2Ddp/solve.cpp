#include<bits/stdc++.h>
using namespace std;

// 一、最小路径和
// 给定一个包含非负整数的 m x n 网格 grid
// 请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
// 说明：每次只能向下或者向右移动一步。
// 测试链接 : https://leetcode.cn/problems/minimum-path-sum/
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        vector<int> dp;
        dp.resize(grid[0].size());// 严格位置依赖的动态规划 + 空间压缩技巧
        dp[0]=grid[0][0];
        for(int i=1;i<grid[0].size();i++) dp[i]=grid[0][i]+dp[i-1];
        for(int i=1;i<grid.size();i++)
        {
            dp[0]=grid[i][0]+dp[0];
            // i = 1，dp表变成想象中二维表的第1行的数据
			// i = 2，dp表变成想象中二维表的第2行的数据
			// i = 3，dp表变成想象中二维表的第3行的数据
			// ...
			// i = n-1，dp表变成想象中二维表的第n-1行的数据
            for(int j=1;j<grid[0].size();j++)
            {
                dp[j]=grid[i][j]+min(dp[j-1],dp[j]);
            }
        }
        return dp[grid[0].size()-1];
    }
};

// 最长公共子序列
// 给定两个字符串text1和text2
// 返回这两个字符串的最长 公共子序列 的长度
// 如果不存在公共子序列，返回0
// 两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列
// 测试链接 : https://leetcode.cn/problems/longest-common-subsequence/
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        string sa,sb;//sa为更短的字符串
        int n,m;//n为更短字符串的长度
        if(text1.length()<=text2.length())
        {
            sa=text1;
            sb=text2;
            n=text1.length();
            m=text2.length();
        }
        else 
        {
            sa=text2;
            sb=text1;
            n=text2.length();
            m=text1.length();
        }
        vector<int> dp;
        dp.resize(n+1);//dp数组下标范围为0~n
        int leftup=0,tmp;//leftup为假想dp表中当前格的左上角，tmp为当前格更新前的值
        for(int lenb=1;lenb<=m;lenb++)//0行0列都表示对应字符串长度为0的情况，不存在子序列
        {
            leftup=0;
            for(int lena=1;lena<=n;lena++)
            {
                tmp=dp[lena];
                if(sa[lena-1]==sb[lenb-1]) dp[lena]=leftup+1;
                else dp[lena]=max(dp[lena-1],dp[lena]);
                leftup=tmp;
            }
        }
        return dp[n];
    }
};

// 最长回文子序列
// 给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度
// 测试链接 : https://leetcode.cn/problems/longest-palindromic-subsequence/


// 节点数为n高度不大于m的二叉树个数
// 现在有n个节点，计算出有多少个不同结构的二叉树
// 满足节点个数为n且树的高度不超过m的方案
// 因为答案很大，所以答案需要模上1000000007后输出
// 测试链接 : https://www.nowcoder.com/practice/aaefe5896cce4204b276e213e725f3ea


// 矩阵中的最长递增路径
// 给定一个 m x n 整数矩阵 matrix ，找出其中 最长递增路径 的长度
// 对于每个单元格，你可以往上，下，左，右四个方向移动
// 你 不能 在 对角线 方向上移动或移动到 边界外（即不允许环绕）
// 测试链接 : https://leetcode.cn/problems/longest-increasing-path-in-a-matrix/


// 不同的子序列
// 给你两个字符串s和t ，统计并返回在s的子序列中t出现的个数
// 答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/distinct-subsequences/


// 编辑距离
// 给你两个单词 word1 和 word2
// 请返回将 word1 转换成 word2 所使用的最少代价
// 你可以对一个单词进行如下三种操作：
// 插入一个字符，代价a
// 删除一个字符，代价b
// 替换一个字符，代价c
// 测试链接 : https://leetcode.cn/problems/edit-distance/


// 交错字符串
// 给定三个字符串 s1、s2、s3
// 请帮忙验证s3是否由s1和s2交错组成
// 测试链接 : https://leetcode.cn/problems/interleaving-string/


// 有效涂色问题
// 给定n、m两个参数
// 一共有n个格子，每个格子可以涂上一种颜色，颜色在m种里选
// 当涂满n个格子，并且m种颜色都使用了，叫一种有效方法
// 求一共有多少种有效的涂色方法
// 1 <= n, m <= 5000
// 结果比较大请 % 1000000007 之后返回
// 对数器验证


// 删除至少几个字符可以变成另一个字符串的子串
// 给定两个字符串s1和s2
// 返回s1至少删除多少字符可以成为s2的子串
// 对数器验证