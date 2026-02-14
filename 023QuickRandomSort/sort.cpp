#include <iostream>
#include<cstdlib>
#include<ctime>
const int N=25;
class Arr
{
    private:
        int arr[N];
        //int help[N];
        int length;
    public:
        void FillArray();
        void QuickSort(int l,int r);
        int Part1(int l,int x,int r);
        int Part2(int l,int x,int r);
        void PrintArray();
        int Arrlength();
        void Swap(int a,int b);
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

void Arr::PrintArray()
{
    for(int i=0;i<length;i++) std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
}

int Arr::Arrlength()
{
    return length;
}

void Arr::Swap(int a,int b)
{
    int temp=arr[a];
    arr[a]=arr[b];
    arr[b]=temp;
}

void Arr::QuickSort(int l,int r)
{
    if(l>=r) return;
    srand(time(nullptr));
    int x=l+rand()%(r-l+1);
    int index=Part2(l,x,r);
    QuickSort(l,index-1);
    QuickSort(index+1,r);
}

int Arr::Part1(int l,int x,int r) //返回一个下标，左边的数均小于等于
{
    int a=l;
    int temp=arr[x];
    Swap(x,r);
    for(int i=a;i<r;i++)
    {
        if(arr[i]<=temp)
        {
            Swap(i,a);
            a++;
        }
    }
    Swap(a,r);
    return a;
}

int Arr::Part2(int l,int x,int r)//荷兰国旗问题
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
    return b;
}

int main()
{
    Arr num1;
    //Arr num2;
    num1.FillArray();
    num1.PrintArray();
    num1.QuickSort(0,num1.Arrlength()-1);
    num1.PrintArray();
    /*num2.FillArray();
    num2.PrintArray();
    num2.QuickSort(0,num2.Arrlength()-1);
    num2.PrintArray();*/
    return 0;
}