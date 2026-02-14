#include<bits/stdc++.h>
using namespace std;

// 盈利计划(多维费用背包)
// 集团里有 n 名员工，他们可以完成各种各样的工作创造利润
// 第 i 种工作会产生 profit[i] 的利润，它要求 group[i] 名成员共同参与
// 如果成员参与了其中一项工作，就不能参与另一项工作
// 工作的任何至少产生 minProfit 利润的子集称为 盈利计划
// 并且工作的成员总数最多为 n
// 有多少种计划可以选择？因为答案很大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/profitable-schemes/
class Solution {
public:
	// i : 来到i号工作
	// r : 员工额度还有r人，如果r<=0说明已经没法再选择工作了
	// s : 利润还有s才能达标，如果s<=0说明之前的选择已经让利润达标了
	// 返回 : i.... r、s，有多少种方案
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        vector<vector<int>> dp;
        dp.resize(n+1);
        for(int i=0;i<=n;i++) dp[i].resize(minProfit+1);
        //为自上而下，i逐渐减小的dp，故先初始化最高层（i==profit.size(),没有工作了）
        for(int r=0;r<=n;r++) dp[r][0]=1;//此时利润为0，要求已满足
        int p1=0,p2=0;
        /*		尝试逻辑
        if (r <= 0) {
			return s == 0 ? 1 : 0;
		}
		if (i == g.length) {
			return s == 0 ? 1 : 0;
		}
		if (dp[i][r][s] != -1) {
			return dp[i][r][s];
		}
		int p1 = f2(g, p, i + 1, r, s, dp);
		int p2 = 0;
		if (g[i] <= r) {
			p2 = f2(g, p, i + 1, r - g[i], Math.max(0, s - p[i]), dp);
		}
		int ans = (p1 + p2) % mod;
		dp[i][r][s] = ans;
		return ans;
*/
        for(int i=group.size()-1;i>=0;i--)//位置依赖与空间优化版本
        {
            for(int r=n;r>=0;r--)
            {
                for(int s=minProfit;s>=0;s--)
                {
                    p1=dp[r][s];
                    p2=r>=group[i]?dp[r-group[i]][max(0,s-profit[i])]:0;
                    dp[r][s]=(p1+p2)%1000000007;
                }
            }
        }
        return dp[n][minProfit];
    }
};
