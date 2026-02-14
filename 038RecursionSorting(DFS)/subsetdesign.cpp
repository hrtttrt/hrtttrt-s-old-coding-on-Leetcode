#include<bits/stdc++.h>
using namespace std; 
/*1、用递归逆序一个栈 时间O(n^2)
一个函数弹出栈底，但不改变栈的次序，
另一个函数通过获得每次的栈底，逆序
*/
class Solution
{
    public:
    int bottomOut(stack<int>& stk){  
    int ans = stk.top();  
    stk.pop();  
    if(stk.empty()){  
        return ans;  
    }else{  
        int last = bottomOut(stk);  
        stk.push(ans);  
        return last;  
    }  
}  
  
void reverse(stack<int>& stk){  
    if(stk.empty()){  
        return;  
    }else{  
        int num = bottomOut(stk);  
        reverse(stk);  
        stk.push(num);  
    }  
}
};

/*2、用递归排序一个栈 时间O(n^2)
求栈的深度
返回n层里的最大值（deep=0的时候，返回整数最小值）
返回n层里最大值的个数(计算时记得回复原状)
把k的最大值押入栈底 （先清到0层，然后根据有k个最大值，押入k个最大值，往上返回，返回遇到最大值的时候，不压入） 
*/
class Solution
{
    /*头文件：
    #include <stack>
    #include <algorithm>
    #include <climits>
    */
    public:
    void sort(stack<int>& stack) {
    int deep = deep(stack);
    while (deep > 0) {
        int max = findMax(stack, deep);
        int k = times(stack, deep, max);
        down(stack, deep, max, k);
        deep -= k;
    }
}

// 返回栈的深度，不改变栈的数据状况
int deep(stack<int>& stack) {
    if (stack.empty()) {
        return 0;
    }
    int num = stack.top();
    stack.pop();
    int depth = deep(stack) + 1;
    stack.push(num);
    return depth;
}

// 从栈当前的顶部开始，往下数deep层，返回这deep层里的最大值
int findMax(stack<int>& stack, int deep) {
    if (deep == 0) {
        return INT_MIN;
    }
    int num = stack.top();
    stack.pop();
    int restMax = findMax(stack, deep - 1);
    int maxValue = max(num, restMax);
    stack.push(num);
    return maxValue;
}

// 从栈当前的顶部开始，往下数deep层，已知最大值是max，返回max出现了几次，不改变栈的数据状况
int times(stack<int>& stack, int deep, int max) {
    if (deep == 0) {
        return 0;
    }
    int num = stack.top();
    stack.pop();
    int restTimes = times(stack, deep - 1, max);
    int count = restTimes + (num == max ? 1 : 0);
    stack.push(num);
    return count;
}

// 从栈当前的顶部开始，往下数deep层，已知最大值是max，出现了k次，把这k个最大值沉底，剩下的数据状况不变
void down(stack<int>& stack, int deep, int max, int k) {
    if (deep == 0) {
        for (int i = 0; i < k; ++i) {
            stack.push(max);
        }
    } else {
        int num = stack.top();
        stack.pop();
        down(stack, deep - 1, max, k);
        if (num != max) {
            stack.push(num);
        }
    }
}
};

/*3、打印n层汉诺塔问题的最优移动轨迹 时间O(2^n) 实际为2^n-1步
左中右三个杆，从最左移动到最右，任何时候不能大压小 抽象思维移动一个圆盘，两个圆盘的时候怎么弄，移动三个同理 
分4步：
1、f(i,from,to,other)
2、f(i-1,from,other)
3、f(1,from,to) (打印第1个可以从from 到 to 了)
4、f(i-1,other,ti)
*/
void hanoi(int n) {  
    if (n > 0) {  
       f(n, "左", "右", "中");  
    }  
}  
  
void f(int i, String from, String to, String other) {  
    if (i == 1) {  
       cout<<("移动圆盘 1 从 " + from + " 到 " + to)<<endl;  
    } else {  
       f(i - 1, from, other, to);  
       cout<<("移动圆盘 " + i + " 从 " + from + " 到 " + to)<<endl;  
       f(i - 1, other, to, from);  
    }  
}  
  
int main() {  
    int n = 3;  
    hanoi(n);
    return 0;  
}