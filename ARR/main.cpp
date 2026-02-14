#include<iostream>
#include<array>
using namespace std;
int main()
{
    array<int,4> a1={1,2,3,4};
    array<int,4> a2={0,0,0,0};
    a2=a1;
    cout<<a2[3]<<endl;
    return 0;
}