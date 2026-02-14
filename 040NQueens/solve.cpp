#include<bits/stdc++.h>
using namespace std; 
/*n 皇后问题 研究的是如何将 n 个皇后放置在 n × n 的棋盘上，并且使皇后彼此之间不能相互攻击。
给你一个整数 n ，返回 n 皇后问题 不同的解决方案的数量。
测试链接：https://leetcode.cn/problems/n-queens-ii/description/
*/

    int f(int limit,int col,int left,int right)
    {
        if(col==limit) return 1;
        int ans=0;
        int ban=col|left|right;
        int can=limit&(~ban);
        int place=0;
        while(can)
        {
            place=can&(-can);//获取棋盘最左边候选位置(二进制中最右的1),注意括号里是取负不是取反
            can=can^place;//除掉这个1
            ans+=f(limit,col|place,(left|place)>>1,(right|place)<<1);
        }
        return ans;
    }
    int totalNQueens(int n) 
    {
        if(n<1) return 0;
        int limit=(1<<n)-1;
        int ans=f(limit,0,0,0);
        return ans;
    }


int main()
{
    int n;
    cin>>n;
    int res=totalNQueens(n);
    cout<<res<<"/n";
}