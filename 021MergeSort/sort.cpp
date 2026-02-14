#include <iostream>
#include<cstdlib>
#include<ctime>
const int N=501;
class Arr
{
    private:
        int arr[N];
        int help[N];
        int length;
    public:
        void FillArray();
        void MergeSort(int l,int r);
        void NRMergeSort(int l,int r);
        void Merge(int l,int m,int r);
        void PrintArray();
        int Arrlength();
};

void Arr::FillArray()
{
    srand(time(nullptr));
    length=rand()%20;
    std::cout<<"length="<<length<<std::endl;
    for(int i=0;i<length;i++)
    {
        arr[i]=rand()%20;
    }
}

void Arr::MergeSort(int l,int r)
{
    if(l==r) return;
    int m=l+(r-l)/2;
    MergeSort(l,m);
    MergeSort(m+1,r);
    Merge(l,m,r);
}

void Arr::NRMergeSort(int l,int r)
{
    if(l==r) return;
    int step=1;
    while(step<r-l)
    {
        int i=0;
        while(i<r)
        {
            Merge(i,std::min(i+step-1,r),std::min(i+step*2-1,r));
            i=i+step*2;
        }
        step=step*2;
    }
}

void Arr::Merge(int l,int m,int r)
{
    int i=l;
    int a=l;
    int b=m+1;
    while (a<=m&&b<=r)
    {
        help[i++]=(arr[a]<=arr[b]?arr[a++]:arr[b++]);
    }
    while(a<=m) help[i++]=arr[a++];
    while(b<=r) help[i++]=arr[b++];
    for(int j=l;j<=r;j++) arr[j]=help[j];//Merge在递归中不断调用，不能用0和length表示左右边界
}

void Arr::PrintArray()
{
    for(int i=0;i<length;i++) std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
}

int Arr::Arrlength()
{
    return length;
}

int main()
{
    Arr num1;
    Arr num2;
    num1.FillArray();
    num1.PrintArray();
    num1.MergeSort(0,num1.Arrlength()-1);
    num1.PrintArray();
    num2.FillArray();
    num2.PrintArray();
    num2.NRMergeSort(0,num2.Arrlength()-1);
    num2.PrintArray();
    return 0;
}