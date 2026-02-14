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
ListNode* FillList(ListNode* head)
{
    ListNode* cur=head;
    while(cur!=NULL)
    {
        cin>>cur->val;
        cur=cur->next;
    }
    cout<<"complete"<<endl;
    return head;
}
/*ListNode* MergeList(ListNode* list1,ListNode* list2)
{
    if(list1==NULL||list2==NULL) return list1==NULL?list2:list1;
    ListNode* pre1=new ListNode;
    ListNode* pre2=new ListNode;
    ListNode* cur1=list1;
    ListNode* cur2=list2;
    while(cur1!=NULL&&cur2!=NULL)
    {
        while(cur1->val>=(cur1->next)->val) cur1=cur1->next;
        while(cur2->val>=(cur2->next)->val) cur2=cur2->next;
        pre1=cur1;
        pre2=cur2;
        if(cur1->val<=cur2->val)
        {
            cur1=cur1->next;
            pre1->next=cur2;
        }
        else
        {
            cur2=cur2->next;
            pre2->next=cur1;
        }
    }
    return list1->val<=list2->val?list1:list2;
}*/
ListNode* GPTMerge(ListNode* list1, ListNode* list2)
{
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    ListNode* mergedHead = NULL;

    if (list1->val <= list2->val) {
        mergedHead = list1;
        list1 = list1->next;
    } else {
        mergedHead = list2;
        list2 = list2->next;
    }

    ListNode* current = mergedHead;

    while (list1 != NULL && list2 != NULL) {
        if (list1->val <= list2->val) {
            current->next = list1;
            list1 = list1->next;
        } else {
            current->next = list2;
            list2 = list2->next;
        }
        current = current->next;
    }

    if (list1 != NULL) current->next = list1;
    if (list2 != NULL) current->next = list2;

    return mergedHead;
}
int main()
{
    ListNode* out1=new ListNode;
    ListNode* out2=new ListNode;
    ListNode* head1=NewList(4);
    ListNode* head2=NewList(4);
    head1=FillList(head1);
    head2=FillList(head2);
    out2=MergeList(head1,head2);
    PrintList(out2);
    out1=GPTMerge(head1,head2);
    PrintList(out1);
    return 0;
}