#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include<queue>
#include<math.h>
using namespace std;

/*快速获得数据流的中位数的结构
用两个堆来管理数据，一个大根堆，存较小的数据，一个小根堆村较大的数据。
各自的堆要存一半，所以需要balance操作。当一边的size比另外一边大超过or等于2的时候，需要重新balance。这样，看两个头就可以获得中位数了。
测试链接：https://leetcode-cn.com/problems/find-median-from-data-stream
*/

class HeapMidFinder
{
private:
    priority_queue<int> maxheap;
    priority_queue<int,vector<int>,greater<int>> minheap;
public:
    void AddNum9(int num)
    {
        if(maxheap.empty()) maxheap.push(num);
        else if(num>=maxheap.top()) maxheap.push(num);
        else minheap.push(num);
        Balance(); 
    }
    void Balance()
    {
        if(maxheap.size()-minheap.size()==2)
        {
            minheap.push(maxheap.top());
            maxheap.pop();
        }
        if(minheap.size()-maxheap.size()==2)
        {
            maxheap.push(minheap.top());
            minheap.pop();
        }
    }
    int FindMid()
    {
        if(minheap.empty()) return maxheap.top();
        if(maxheap.size()==minheap.size()) return maxheap.top()+(minheap.top()-maxheap.top())/2.0;//结果为float
        else if(maxheap.size()>minheap.size()) return maxheap.top();
        else return minheap.top();
    }
};