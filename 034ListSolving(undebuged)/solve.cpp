#include <iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
using std::vector;
typedef struct node
{
    int val;
    struct node *next;
}ListNode;
class Linklist
{
    private:
        ListNode* head;
        int length;
        ListNode* tail;
        ListNode* lasthead=nullptr;
        ListNode* lasttail=nullptr;
        ListNode* nexthead=nullptr;
    public:
        void TeamReverse(int k)//每k个节点翻转链表
        {
            if(head==nullptr) return;
            nexthead=head;
            ListNode* first=head;
            ListNode* last=head;
            for(int i=1;i<k;i++)
            {
                last=later->next;
                if(last==nullptr) break;
            }
            while(last!=nullptr)
            {
                nexthead=last->next;
                lasthead=reverse(first,last);
                if(lasttail==nullptr) head=lasthead;
                lasttail=first;
                first=nexthead;
                last=nexthead;
                for(int i=1;i<k;i++)
                {
                    last=last->next;
                    if(last==nullptr) break;
                }
            }
        }
        ListNode* reverse(ListNode* first, ListNode* last)
        {
            if(first==nullptr||first==last) return first; 
            ListNode* pre=first;
            ListNode* cur=first->next;
            ListNode* later=first->next->next;
            while(cur!=last)
            {
                cur->next=pre;
                if(pre==first) pre->next=nexthead;
                pre=cur;
                cur=later;
                later=later->next;
            }
            cur->next=pre;
            return cur;
        }
        void Listsort()//时间O（n*logn），空间O（1），具有稳定性
        {
            if(head==nullptr||head->next==nullptr) return;
            int step=1;
            ListNode* curhead=head;
            lasttail=head;
            for(int i=1;i<=length;i++)
            {
                if(curhead->val<lasttail->val) curhead=lasttail;
                lasttail=lasttail->next;
            }
            ListNode* a=head;
            ListNode* b=head;
            ListNode* leftl=head;
            ListNode* rightl=head;
            for(;step<length;step<<=1)
            {
                lasttail=head;
                leftl=head;
                rightl=head->next;
                a=head;
                b=head;
                while(lasttail!=tail)
                {
                    b=leftl->next;
                    do
                    {
                        if(a->val<=b->val)
                      {
                        lasttail->next=a;
                        a=a->next;
                      }
                        else
                        {
                         lasttail->next=b;
                         b=b->next;
                        }
                        lasttail=lasttail->next;
                    }while ((a!=leftl->next&&b!=rightl->next)||lasttail==nullptr);
                    leftl=rightl->next;
                    rightl=leftl;
                    for(int i=1;i<step;i++)
                    {
                        leftl=leftl->next;
                        if(leftl==tail) break;
                    }
                    for(int i=1;i<step*2;i++)
                    {
                        rightl=rightl->next;
                        if(rightl==tail) break;
                    }
                }
            }
            head=curhead;
        }
};
