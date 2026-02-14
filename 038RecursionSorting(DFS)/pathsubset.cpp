#include<bits/stdc++.h>
using namespace std; 
/*1、返回字符串全部子序列，子序列要求去重 时间O(n*2^n)
测试链接：https://www.nowcoder.com/practice/92e6247998294f2c933906fdedbc6e6a
*/
class Solution {
public:
    
    std::unordered_set<string> uset;
    void f(string &s,int cur,vector<string> &ans,string path)
    {
        if(cur==s.length())
        {
            if(uset.find(path)==uset.end())
            {
                uset.insert(path);
                ans.push_back(path);
            }
        }
        else
        {
            path.push_back(s[cur]);
            f(s,cur+1,ans,path);
            path.pop_back();
            f(s,cur+1,ans,path);
        }
    }
    vector<string> generatePermutation(string s) 
    {
        std::vector<string> ans;
        string path="";
        f(s,0,ans,path);
        return ans;
    }
};

/*2、返回数组的所有组合，可以无视元素顺序 时间O(n*2^n)
比如输入：nums = [1,2,2]
输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
就返回一个数组的所有不同组合->每个相同数值的个数不一样->排序->递归遍历数组（要某一个数n个，然后接下来要下一个数m个） 
注意！把每个组合分析，减少枝干的数量
测试链接：https://leetcode.cn/problems/subsets-ii/
*/
class Solution {
public:
   
    int findnext(vector<int>& nums,int begin)
    {
        if(begin==nums.size()) return begin;
        while(begin<nums.size()-1&&nums[begin]==nums[begin+1]) begin++;
        return begin+1;//返回下一个数的起点
    }
    void f(vector<int>& nums,vector<vector<int>>& ans,int begin,int end)//记得数组传引用
    {
        if(begin==end) return;
        int n=ans.size();
        for(int i=0;i<n;i++)
        {
            vector<int> v=ans[i];//复制已有集合
            for(int j=begin;j<end;j++)//遍历单个数的每一种取数情况
            {
                v.push_back(nums[j]);
                ans.push_back(v);
            }
        }
        f(nums,ans,end,findnext(nums,end));
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) 
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        ans.emplace_back();
        f(nums,ans,0,findnext(nums,0));
        return ans;
    }
};

/* 3、返回没有重复值数组的全部排列 时间O(n!*n)
！！经典路径问题，调整均在原数组上，递归后需注意“回复原状”
解法是找到一个规律：如何按规律的罗列出所有的排列情况？
假设有三个数 需要不断的交换：每一次交换是一层 第一层：第一次交换（分多种情况）： 1 1 交换 1 2 交换 1 3 交换 2 2 交换 2 3 交换 
第二层以此类推 最终到底下，保存交换的结果，递归返回，换回来，最终获得全部结果 
==注意递归调用函数时的参数n，传的是当前的位置n+1（每一层都是一个数组的唯一一个位置），而不是迭代的位置==
测试连接：https://leetcode.cn/problems/permutations/
*/
class Solution {
public:
void Swap(vector<int>& nums,int i,int j)
{
    int temp=nums[i];
    nums[i]=nums[j];
    nums[j]=temp;
}
    void f(vector<int>& nums,vector<vector<int>>& ans,int i)
    {
        if(i==nums.size())
        {
            ans.push_back(nums);
        }
        else
        {
            for(int j=i;j<nums.size();j++)//初态是j=i，原态（未交换）在for循环第一步执行，不需要额外写
            {
                Swap(nums,i,j);
                f(nums,ans,i+1);
                Swap(nums,i,j);
            }
        }
    }

    vector<vector<int>> permute(vector<int>& nums) 
    {
        vector<vector<int>> ans;
        //f(nums,ans,0);
        f2(nums,ans,0);
        return ans;
    }
    unorder_set<int> uset;
};

/*4、返回可能有重复值数组的全部排列，排列要求去重。 时间O(n!*n)
保证每一个来到i位置的数都是不一样的。加多一个hashset
n, i 交换 nums[i] 在set不存在，才会尝试 
==注意set的位置，不是全局，是局部==
测试链接：https://leetcode.cn/problems/permutations-ii/
*/
class Solution {
public:
void Swap(vector<int>& nums,int i,int j)
{
    int temp=nums[i];
    nums[i]=nums[j];
    nums[j]=temp;
}
    void f2(vector<int>& nums,vector<vector<int>>& ans,int i)
    {
        if(i==nums.size())
        {
            ans.push_back(nums);
        }
        unordered_set<int> uset;//局部哈希set，用于去重
        else
        {
            for(int j=i;j<nums.size();j++)//初态是j=i，原态（未交换）在for循环第一步执行，不需要额外写
            {
                if(uset.find(nums[j])==uset.end())
                {
                    uset.insert(nums[j]);
                    Swap(nums,i,j);
                    f(nums,ans,i+1);
                    Swap(nums,i,j);
                }
            }
        }
    }

    vector<vector<int>> permute(vector<int>& nums) 
    {
        vector<vector<int>> ans;
        //f(nums,ans,0);
        f2(nums,ans,0);
        return ans;
    }
};

