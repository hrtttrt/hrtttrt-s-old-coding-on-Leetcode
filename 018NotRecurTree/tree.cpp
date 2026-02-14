#include <iostream>
using namespace std;
typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
}TreeNode;
typedef struct stack
{
    TreeNode* tree;
    struct stack *next;
}Stack;

Stack* Push(Stack* head,TreeNode* t)
{
    Stack* p=new Stack;
    p->tree=t;
    p->next=head;
    head=p;
    return head;
}
 
Stack* Pop(Stack* head)
{
    if(head==NULL) return nullptr;
    Stack* p=head;
    head=head->next;
    delete p;//释放内存
    return head;
}

TreeNode* NewTree(int arr[],int length,int index)
{
    if(index>=length||arr[index]==-1) return nullptr;
    TreeNode* p=new TreeNode;
    p->val=arr[index];
    p->left=NewTree(arr,length,2*index+1);
    p->right=NewTree(arr,length,2*index+2);
    return p;
}

void NRPreOrder(TreeNode* head)//非递归先序遍历
{
    TreeNode* cur=head;
    Stack* s=nullptr;
    s=Push(s,cur);
    while(s!=NULL)
    {
        cur=s->tree;
        s=Pop(s);
        cout<<(cur->val)<<" ";
        if(cur->right!=NULL) s=Push(s,cur->right);
        if(cur->left!=NULL) s=Push(s,cur->left);
    }
}

void NRInOrder(TreeNode* head)//非递归中序遍历
{
    TreeNode* cur=head;
    Stack* s=nullptr;
    //s=Push(s,cur);此处错误，导致根节点被重复压栈
    while(s!=NULL||cur!=NULL)
    {
        while(cur!=NULL)
        {
            s=Push(s,cur);
            cur=cur->left;
        }
        if(s!=NULL) 
        {
            cur=s->tree;
            s=Pop(s);
            cout<<cur->val<<" ";
            cur=cur->right;
        }
    }
}



void NRPosOrder2(TreeNode* head)//两个栈非递归后序
{
    TreeNode* cur=head;
    Stack* s=nullptr;
    Stack* collect=nullptr;
    s=Push(s,cur);
    while(s!=nullptr)
    {
        cur=s->tree;
        s=Pop(s);
        collect=Push(collect,cur);
        if(cur->left!=NULL) s=Push(s,cur->left);
        if(cur->right!=NULL) s=Push(s,cur->right);
    }
    while(collect!=nullptr)
    {
        cout<<collect->tree->val<<" ";
        collect=Pop(collect);
    }
}

void NRPosOrder1(TreeNode* head)//一个栈非递归后序
{
    TreeNode* cur=head;
    TreeNode* finish=nullptr;
    Stack* s=nullptr;
    s=Push(s,cur);
    while(s!=nullptr)
    {
        if(cur->left!=nullptr&&finish!=cur->left&&finish!=cur->right)//有未处理的左树
        {
            cur=cur->left;
            s=Push(s,cur);
        }
        else if(cur->right!=nullptr&&finish!=cur->right)//有未处理的右树
        {
            cur=cur->right;
            s=Push(s,cur);
        }
        else //左右树均处理完毕
        {
            cur=s->tree;
            s=Pop(s);
            cout<<cur->val<<" ";
            finish=cur;
            if(s!=nullptr) cur=s->tree;
        }
    }
}

int main()
{
    int length;
    cin>>length;
    int arr[length];
    for(int i=0;i<length;i++)
    {
        arr[i]=i+1;
    }
    TreeNode* head=NewTree(arr,length,0);
    NRPreOrder(head);
    cout<<endl;
    NRInOrder(head);
    cout<<endl;
    NRPosOrder1(head);
    cout<<endl;
    NRPosOrder2(head);
    cout<<endl;
    return 0;
}