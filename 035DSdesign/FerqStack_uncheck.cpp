#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include<queue>
#include<math.h>
using namespace std;
/*设计一个类似堆栈的数据结构，将元素推入堆栈，并从堆栈中弹出出现频率最高的元素。 
使用map（词频表）+最大次记录 注意stack的设计的时候，设计成每一个层都是一个链表，链表存对应词频的数
测试链接：https://leetcode.cn/problems/maximum-frequency-stack/ 
*/
class FerqStack
{
public:
    int maxferq;
    unordered_map<int,vector<int>> cntmap;//主结构
    unordered_map<int,int> m;//词频表
    FreqStack() {
        maxferq=0;
    }
    
    void push(int val) {
        if(m.find(val)!=m.end())//若不存在，find返回指向哈希表结尾的迭代器
        {
            m[val]++;
            if(m[val]>maxferq)
            {
                maxferq=m[val];
                cntmap.insert(pair<int,vector<int>>(m[val],vector<int>()));
                cntmap[m[val]].push_back(val);
            }
            else cntmap[m[val]].push_back(val);
        }
        else
        {
            m.insert(pair<int,int>(val,1));//当第一个数进入时记得特判，下行同
            if(maxferq==0) maxferq=1;
            if(cntmap.find(m[val])!=cntmap.end()) cntmap[m[val]].push_back(val);
            else 
            {
                cntmap.insert(pair<int,vector<int>>(m[val],vector<int>()));
                cntmap[m[val]].push_back(val);
            }
        }
    }
    
    int pop() {
        int to_pop=cntmap[maxferq].back();
        cntmap[maxferq].pop_back();
        if(cntmap[maxferq].empty())
        {
            cntmap.erase(maxferq);
            maxferq--;
        }
        if(--m[to_pop]==0) m.erase(to_pop);
        return to_pop;
    }
};