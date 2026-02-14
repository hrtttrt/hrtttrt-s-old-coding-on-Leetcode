#include <iostream>
#include<cstdlib>
#include<ctime>
const int N=25;
class Heap
{
    private:
        int arr[N];
        int size;
        int length;
    public:
    int Arrlength();
    void FillArray();
    void PrintArray();
    void Swap(int a,int b);
    void HeapSize();
    void HeapInsert(int k);
    void Heapify(int k);
    void HeapSort1();
};

int Heap::Arrlength()
{
    return length;
}

void Heap::FillArray()
{
    srand(time(nullptr));
    length=rand()%20;
    std::cout<<"length="<<length<<'\n';
    for(int i=0;i<length;i++)
    {
        arr[i]=rand()%20;
    }
}

void Heap::PrintArray()
{
    for(int i=0;i<length;i++) std::cout<<arr[i]<<" ";
    std::cout<<'\n';
}

void Heap::Swap(int a,int b)
{
    int temp=arr[a];
    arr[a]=arr[b];
    arr[b]=temp;
}

void Heap::HeapSize()
{
    size=length;
}

void Heap::Heapify(int k)
{
    int l=k*2+1;
    int best;
    while(l<size)
    {
        best=(l+1<size&&arr[l+1]>arr[l])?l+1:l;
        best=arr[best]>arr[k]?best:k;
        if(best==k) break;
        Swap(best,k);
        k=best;
        l=k*2+1; //记得更新左节点指引，否则会死循环
    }
}

void Heap::HeapInsert(int k)
{
    int father=(k-1)/2;
    while(arr[k]>arr[father])
    {
        Swap(k,father);
        k=father;
        father=(k-1)/2;
    }
}

void Heap::HeapSort1() //从底到顶
{
    for(int i=length-1;i>=0;i--) Heapify(i);
    while(size>1)
    {
        Swap(0,--size);
        Heapify(0);
    }
    size=length;
}

int main()
{
    Heap heap1;
    heap1.FillArray();
    heap1.HeapSize();
    heap1.PrintArray();
    heap1.HeapSort1();
    heap1.PrintArray();
    return 0;
}