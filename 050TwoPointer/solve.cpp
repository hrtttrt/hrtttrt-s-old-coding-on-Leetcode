#include<bits/stdc++.h>
using namespace std;
// 一、寻找重复数        （快慢指针）
// 给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和 n）<-α（制造类链表环结构）
// 可知至少存在一个重复的整数。
// 假设 nums 只有 一个重复的整数 ，返回 这个重复的数 。
// 你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间。
// 测试链接 : https://leetcode.cn/problems/find-the-duplicate-number/
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int fast=nums[nums[0]],slow=nums[0]; //<-α
        while(nums[fast]!=nums[slow])
        {
            fast=nums[nums[fast]];
            slow=nums[slow];
        }
        fast=0;
        while(nums[fast]!=nums[slow])
        {
            fast=nums[fast];
            slow=nums[slow];
        }
        return nums[slow];
    }
};

// 二、接雨水
// 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水
// 测试链接 : https://leetcode.cn/problems/trapping-rain-water/
class Solution {
public:
    int trap(vector<int>& height) {
        int l=1,r=height.size()-2,lmax=height[0],rmax=height[height.size()-1],ans=0;
        while(l<=r)
        {
            if(lmax<=rmax)
            {
                ans+=max(0,lmax-height[l]);
                lmax=max(lmax,height[l++]);
            }
            else
            {
                ans+=max(0,rmax-height[r]);
                rmax=max(rmax,height[r--]);
            }
        }
        return ans;
    }
};

// 三、救生艇
// 给定数组 people
// people[i]表示第 i 个人的体重 ，船的数量不限，每艘船可以承载的最大重量为 limit
// 每艘船最多可同时载两人，但条件是这些人的重量之和最多为 limit
// 返回 承载所有人所需的最小船数
// 测试链接 : https://leetcode.cn/problems/boats-to-save-people/
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int l=0,r=people.size()-1,ans=0,sum=0;
        sort(people.begin(),people.end());
        while(l<=r)
        {
            sum=(l==r)?people[l]:people[l]+people[r];
            if(sum<=limit)
            {
                l++;
                r--;
            }
            else r--;
            ans++;
        }
        return ans;
    }
};

// 四、盛最多水的容器
// 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
// 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水
// 返回容器可以储存的最大水量
// 说明：你不能倾斜容器
// 测试链接 : https://leetcode.cn/problems/container-with-most-water/
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l=0,r=height.size()-1,ans=0;
        while(l<=r)
        {
            ans=max(ans,min(height[l],height[r])*(r-l));//这样一定不会错过最优解
            if(height[l]<=height[r]) l++;
            else r--;
        }
        return ans;
    }
};

// 五、供暖器   (同向指针)
// 冬季已经来临。 你的任务是设计一个有固定加热半径的供暖器向所有房屋供暖。
// 在加热器的加热半径范围内的每个房屋都可以获得供暖。
// 现在，给出位于一条水平线上的房屋 houses 和供暖器 heaters 的位置
// 请你找出并返回可以覆盖所有房屋的最小加热半径。
// 说明：所有供暖器都遵循你的半径标准，加热的半径也一样。
// 测试链接 : https://leetcode.cn/problems/heaters/
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int h1=0,h2=0,ans=0;
        sort(houses.begin(),houses.end());//记得排序
        sort(heaters.begin(),heaters.end());
        for(h1=0;h1<houses.size();h1++)
        {
                while(!best(houses,heaters,h1,h2))
                {
                    h2++;
                }
            ans=max(ans,abs(heaters[h2]-houses[h1]));
        }
        return ans;
    }
    bool best(vector<int>& houses, vector<int>& heaters,int h1,int h2)//判断当前供暖器对当前房子是否是优
    {
        return h2==heaters.size()-1||abs(heaters[h2+1]-houses[h1])>abs(heaters[h2]-houses[h1]);
    }
};

// 六、缺失的第一个正数 (重要)
// 给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。
// 请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。
// 测试链接 : https://leetcode.cn/problems/first-missing-positive/
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int l=0,r=nums.size()-1;//l左侧为有序区，r右侧为垃圾区
        while(l<=r)
        {
            if(nums[l]==l+1) l++;
            else if(nums[l]<=0) swap(nums,l,r--);
            else if(nums[l]>r+1) swap(nums,l,r--);
            else if(nums[nums[l]-1]==nums[l]) swap(nums,l,r--);
            else swap(nums,l,nums[l]-1);
        }
        return l+1;//返回有序区未出现的第一个正数
    }
    void swap(vector<int>& nums,int i,int j)
    {
        int temp;
        temp=nums[i];
        nums[i]=nums[j];
        nums[j]=temp;
    }
};