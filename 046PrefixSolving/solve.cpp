#include<bits/stdc++.h>
using namespace std;
/*一、利用前缀和快速得到区域累加和
// 测试链接 : https://leetcode.cn/problems/range-sum-query-immutable/
*/
class NumArray {
public:
    int MAXN=10001;
    vector<int> sum;
    NumArray(vector<int>& nums) 
    {
        sum.resize(MAXN);
        for(int i=0;i<nums.size();i++)
        {
            sum[i+1]=sum[i]+nums[i];//sum[0]=0，目的是做到没有数时前缀和为0
        }
    }
    
    int sumRange(int left, int right) {
        return sum[right+1]-sum[left];
    }
};

/*二、 返回无序数组中累加和为给定值的最长子数组长度
// 给定一个无序数组arr, 其中元素可正、可负、可0
// 给定一个整数aim
// 求arr所有子数组中累加和为aim的最长子数组长度
// 测试链接 : https://www.nowcoder.com/practice/36fb0fd3c656480c92b569258a1223d5
*/
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    unordered_map<int,int> sum;
    int solve(vector<int>& nums,int aim)
    {
        int ans=INT_MIN;
        int cursum=0;
        sum.clear();//迎接下一个测试用例前先清理
        sum.insert(pair<int,int>(0,-1));
        for(int i=0;i<nums.size();i++)
        {
            cursum+=nums[i];
            if(sum.find(cursum-aim)!=sum.end()) ans=std::max(ans,i-sum.find(cursum-aim)->second);
            if(sum.find(cursum)==sum.end()) sum.insert(pair<int,int>(cursum,i));
        }
        return ans;
    }
};
int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    vector<int> nums;
    int length,aim;
    cin>>length>>aim;
    nums.resize(length);
    for(int t=0;t<length;t++)
    {
        cin>>nums[t];
    }
    Solution solution;
    cout<<solution.solve(nums,aim)<<'\n';
    return 0;
}