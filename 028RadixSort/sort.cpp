#include <iostream>
#include<cstdlib>
#include<ctime>
const int N=25;
const int BASE=10;
class Arr
{
    private:
        int arr[N];
        int help[N];
        int cnts[BASE];
        int length;
    public:
        void FillArray();//不要复制这里的fillarray
        void PrintArray();
        int Arrlength();
        void RadixSort(int bits);
};

void Arr::FillArray()
{
    srand(time(nullptr));
    length=rand()%20;
    std::cout<<"length="<<length<<"\n";
    for(int i=0;i<length;i++)
    {
        arr[i]=rand()%10000;
    }
}

void Arr::PrintArray()
{
    for(int i=0;i<length;i++) std::cout<<arr[i]<<" ";
    std::cout<<"\n";
}

int Arr::Arrlength()
{
    return length;
}

void Arr::RadixSort(int bits)
{
    for(int offset=1;bits>0;offset*=BASE,bits--)
    {
        for(int i=0;i<BASE;i++) cnts[i]=0;
        for(int i=0;i<length;i++) cnts[(arr[i]/offset)%BASE]++; //统计该数位数频
        for(int i=1;i<BASE;i++) cnts[i]+=cnts[i-1];//转化为数位和形式
        for(int i=length-1;i>=0;i--) help[--cnts[(arr[i]/offset)%BASE]]=arr[i]; //填充辅助数组
        for(int i=0;i<length;i++) arr[i]=help[i];
    }
}

int main()
{
    Arr num;
    num.FillArray();
    num.PrintArray();
    num.RadixSort(4);
    num.PrintArray();
    return 0;
}