#include<iostream>
using namespace std;
int main()
{
    int a=78;
    for(int i=31;i>=0;i--)
    {
        cout<<((a&(1<<i))==0?"0":"1");
    }
    return 0;
}