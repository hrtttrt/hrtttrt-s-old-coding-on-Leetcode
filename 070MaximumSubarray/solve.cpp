#include<bits/stdc++.h>
using namespace std;

// 一、打家劫舍 IV  （二分答案法）
// 沿街有一排连续的房屋。每间房屋内都藏有一定的现金
// 现在有一位小偷计划从这些房屋中窃取现金
// 由于相邻的房屋装有相互连通的防盗系统，所以小偷不会窃取相邻的房屋
// 小偷的 窃取能力 定义为他在窃取过程中能从单间房屋中窃取的 最大金额
// 给你一个整数数组 nums 表示每间房屋存放的现金金额
// 第i间房屋中放有nums[i]的钱数
// 另给你一个整数k，表示小偷需要窃取至少 k 间房屋
// 返回小偷需要的最小窃取能力值
// 测试链接 : https://leetcode.cn/problems/house-robber-iv/
class Solution {
public:
    int minCapability(vector<int>& nums, int k) {
        int max=INT_MIN,min=INT_MAX;
        for(int i=0;i<nums.size();i++)
        {
            if(max<nums[i]) max=nums[i];
            if(min>nums[i]) min=nums[i];
        }
        int ans=max,l=min,r=max,m=0;
        while(l<=r)
        {
            m=(l+r)/2;
            if(bestrob(nums,m)>=k) 
            {
                ans=m;
                r=m-1;
            }
            else l=m+1;
        }
        return ans;
    }

    int bestrob(vector<int>& nums,int ability)//解决该“数量”问题的最简单方法
    {
        int ans=0;
        for(int i=0;i<nums.size();i++)
        {
            if(ability>=nums[i])
            {
                ans++;
                i++;
            }
        }
        return ans;
    }
};

// 二、子矩阵最大累加和问题
// 给定一个二维数组grid，找到其中子矩阵的最大累加和
// 返回拥有最大累加和的子矩阵左上角和右下角坐标
// 如果有多个子矩阵都有最大累加和，返回哪一个都可以
// 测试链接 : https://leetcode.cn/problems/max-submatrix-lcci/
class Solution {
public:
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
        vector<int> dp;
        int n=matrix.size();
        int m=matrix[0].size();
        dp.resize(m);
        int a=0,b=0,c=0,d=0,max=INT_MIN;
        for(int i=0;i<n;i++)
        {
            for(int k=0;k<m;k++) dp[k]=0;
            for(int j=i;j<n;j++)
            {
                for(int l=0,r=0,pre=INT_MIN;r<m;r++)
                {
                    dp[r]+=matrix[j][r];
                    if(pre>0) pre+=dp[r];
                    else 
                    {
                        pre=dp[r];
                        l=r;
                    }
                    if(max<pre)
                    {
                        max=pre;
                        a=i;
                        b=l;
                        c=j;
                        d=r;
                    }
                }
            }
        }
        vector<int> ans={a,b,c,d};
        return ans;
    }
};