#include<bits/stdc++.h>
using namespace std;
int main()
{
    int x,y,cnt=0;
    for(int i=-8;i<=8;++i)
    {
        x=i>>2;
        y=(x+i)/4;
        if(x==y) ++cnt;
        else 
        {
            cout<<i<<'\n';
            cout<<x<<" "<<y<<'\n';
        }
    }
    cout<<cnt;
    return 0;
}