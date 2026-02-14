#include<bits/stdc++.h>
using namespace std;

//最大公约数与最小公倍数求法
//容易记错，一定要记得！！！
int Gcd(int a,int b)
{
    return b==0?a;Gcd(b,a%b);
}
long Lcm(int a,int b)
{
    return (long) a/Gcd(a,b)*b;
}


/*1、第N个神奇数字
一个正整数如果能被 a 或 b 整除，那么它是神奇的。
给定三个整数 n , a , b ，返回第 n 个神奇的数字。因为答案可能很大，所以返回答案 对 109 + 7 取模 后的值。
*/

    int Gcd(int a,int b)
{
    return b==0?a:Gcd(b,a%b);
}
long Lcm(int a,int b)
{
    return (long) a/Gcd(a,b)*b;
}

    int nthMagicalNumber(int n, int a, int b) 
    {
        long lcm=Lcm(a,b);
        long res=0;
        long mid=0;
        long l=1;
        long r=(long)std::min(a,b)*n; //显式转换，不然会溢出
        for(;l<=r;)//你老惦记着你那b递归干嘛
        {
            mid=(r-l)/2+l;
            if((mid/a+mid/b-mid/lcm)>=n)
            {
                res=mid;//这里已经记录，不用边界特判
                r=mid-1;
            }
            else l=mid+1;
        }
        return (int) (res%1000000007);
    }

//同余原理
// 计算 ((a + b) * (c - d) + (a * c - b * d)) % mod 的非负结果
	int f2(long a, long b, long c, long d, int mod) 
    {
		int o1 = (int) (a % mod); // a
		int o2 = (int) (b % mod); // b
		int o3 = (int) (c % mod); // c
		int o4 = (int) (d % mod); // d
		int o5 = (o1 + o2) % mod; // a + b
		int o6 = (o3 - o4 + mod) % mod; // c - d
		int o7 = (int) (((long) o1 * o3) % mod); // a * c
		int o8 = (int) (((long) o2 * o4) % mod); // b * d
		int o9 = (int) (((long) o5 * o6) % mod); // (a + b) * (c - d)
		int o10 = (o7 - o8 + mod) % mod; // (a * c - b * d)
		int ans = (o9 + o10) % mod; // ((a + b) * (c - d) + (a * c - b * d)) % mod
		return ans;
	}