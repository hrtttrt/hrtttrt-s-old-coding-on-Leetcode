#include<bits/stdc++.h>
using namespace std;

/*一、最强祝福力场 (未完成)
测试链接：https://leetcode.cn/problems/xepqZ5/
*/
class Solution {
public:
    int fieldOfGreatestBlessing(vector<vector<int>>& forceField) 
    {
        int n=forceField.size();
        vector<long> xs;
        vector<long> ys;
        xs.resize(2*n);
        ys.resize(2*n);
        for(int i=0,j=0,k=0;i<n;i++)
        {
            long x=forceField[i][0];
            long y=forceField[i][1];
            long r=forceField[i][2];
            xs[j++]=(x<<1)-r;
            xs[j++]=(x<<1)+r;
            ys[k++]=(y<<1)-r;
            ys[k++]=(y<<1)+r;
        }
        int xsize=Sort(xs);
        int ysize=Sort(ys);
        vector<vector<int>> diff;//差分数组
        diff.resize(xsize+2);
        for(int i=0;i<xsize;i++) diff[i].resize(ysize+2);
        for(int i=0,a,b,c,d;i<n;i++)
        {
            long x=forceField[i][0];
            long y=forceField[i][1];
            long r=forceField[i][2];
            a=rank(xs,(x<<1)-r+1,xsize);
            b=rank(xs,(x<<1)+r+1,xsize);
            c=rank(ys,(y<<1)-r+1,ysize);
            d=rank(ys,(y<<1)+r+1,ysize);
        }
    }
    int Sort(vector<long>& arr)
    {
        sort(arr.begin(),arr.end());
        int size=1;
        for(int i=1;i<arr.size();i++)
        {
            if(arr[i]!=arr[size-1]) arr[size++]=arr[i];//只有不同的才放进去
        }
        return size;
    }
    int rank(vector<long>& arr,long v,int size)
    {
        int l=0;
        int r=size-1;
        int m=0;
        int ans=0;
        while(l<=r)
        {
            m=l+(r-l)/2;
            if(arr[m]>v) 
            {
                ans=m;
                r=m-1;
            }
            else l=m+1;
        }
       return ans+1;//编号从一开始
    }
};

// 二、用邮票贴满网格图
// 给你一个 m * n 的二进制矩阵 grid
// 每个格子要么为 0 （空）要么为 1 （被占据）
// 给你邮票的尺寸为 stampHeight * stampWidth
// 我们想将邮票贴进二进制矩阵中，且满足以下 限制 和 要求 ：
// 覆盖所有空格子，不覆盖任何被占据的格子
// 可以放入任意数目的邮票，邮票可以相互有重叠部分
// 邮票不允许旋转，邮票必须完全在矩阵内
// 如果在满足上述要求的前提下，可以放入邮票，请返回 true ，否则返回 false
// 测试链接 : https://leetcode.cn/problems/stamping-the-grid/