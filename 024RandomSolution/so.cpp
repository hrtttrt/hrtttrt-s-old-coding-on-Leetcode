//leetcode 215
/*给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。*/
#include <iostream>
#include<cstdlib>
#include<ctime>
const int N=25;
class Arr
{
    private:
        int arr[N];
        //int help[N];
        int first;
        int last;
        int length;
    public:
        void FillArray();
        int Partition(int l,int x,int r,int k);
        int Arrlength();
        void Swap(int a,int b);
        int FindKth(int l,int k,int r);
        void PrintArray();
};

int Arr::Arrlength()
{
    return length;
}

void Arr::FillArray()
{
    srand(time(nullptr));
    length=rand()%20;
    std::cout<<"length="<<length<<'\n';
    for(int i=0;i<length;i++)
    {
        arr[i]=rand()%20;
    }
}

int Arr::FindKth(int l,int k,int r)
{
    if(k==l||k==r) return arr[k];
    srand(time(nullptr));
    int x=l+rand()%(r-l+1);
    Partition(l,x,r,k);
    if(first<=k&&last>=k) return arr[last];
    else if(first>k) FindKth(l,k,first-1);
    else FindKth(last+1,k,r);
}

int Arr::Partition(int l,int x,int r,int k)//荷兰国旗问题
{
    int a=l;
    int b=r;
    int temp=arr[x];
    for(int i=a;i<=b;i++)
    {
        if(arr[i]<temp) 
        {
            Swap(i,a);
            a++;
        }
        else if(arr[i]==temp);
        else
        {
            Swap(i,b);
            b--;
            i--;
        }
    }
    first=a;
    last=b;
    return b;
}

void Arr::Swap(int a,int b)
{
    int temp=arr[a];
    arr[a]=arr[b];
    arr[b]=temp;
}

void Arr::PrintArray()
{
    for(int i=0;i<length;i++) std::cout<<arr[i]<<" ";
    std::cout<<'\n';
}

using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    Arr num;
    num.FillArray();
    num.PrintArray();
    int k;
    cin>>k;
    cout<<"the Kth num is "<<num.FindKth(0,k-1,num.Arrlength()-1)<<'\n';
}