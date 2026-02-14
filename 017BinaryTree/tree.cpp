#include <iostream>
using namespace std;
typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
}TreeNode;
TreeNode* NewTree(int arr[],int length,int index)
{
    if(index>=length||arr[index]==-1) return nullptr;
    TreeNode* p=new TreeNode;
    p->val=arr[index];
    p->left=NewTree(arr,length,2*index+1);
    p->right=NewTree(arr,length,2*index+2);
    return p;
}
void PreOrder(TreeNode* head)
{
    if(head==NULL) return;
    cout<<head->val<<" ";
    PreOrder(head->left);
    PreOrder(head->right);
    return;
}
void InOrder(TreeNode* head)
{
    if(head==NULL) return;
    InOrder(head->left);
    cout<<head->val<<" ";
    InOrder(head->right);
    return;
}
void PosOrder(TreeNode* head)
{
    if(head==NULL) return;
    PosOrder(head->left);
    PosOrder(head->right);
    cout<<head->val<<" ";
    return;
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
    PreOrder(head);
    cout<<endl;
    InOrder(head);
    cout<<endl;
    PosOrder(head);
    return 0;
}