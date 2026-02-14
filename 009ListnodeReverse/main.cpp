#include <iostream>
using namespace std;
typedef struct node
{
    int val;
    struct node *next;
}ListNode;
ListNode* NewList(int length)
{
    ListNode* head = new ListNode;
    head->val = 1;
    head->next = NULL;
    ListNode* pre = head;

    for(int i=1;i<length;i++)
    {
        ListNode* p=new ListNode;
        p->val=i+1;
        pre->next=p;
        pre=p;
        p->next=NULL;
    }
    return head;
}
void PrintList(ListNode* head)
{
    ListNode* pre=head;
    while(pre!=NULL)
    {
        cout<<pre->val;
        pre=pre->next;
    };
    cout<<endl;
}
ListNode* ReverseList(ListNode* head)
{
    ListNode* pre=NULL;
    ListNode* cur=head;
    ListNode* next=head->next;
    while(cur!=NULL)
    {
        next=cur->next;
        cur->next=pre;
        pre=cur;
        cur=next;
    }
    return pre;
}
int main()
{
    ListNode* head=NewList(10);
    PrintList(head);
    ListNode* rehead=ReverseList(head);
    PrintList(rehead);
    return 0;
}