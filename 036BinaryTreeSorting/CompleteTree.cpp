#include<bits/stdc++.h>
using namespace std;
typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
}TreeNode;
/*一、验证完全二叉树,定义：
在一棵 完全二叉树 中，除了最后一层外，所有层都被完全填满，并且最后一层中的所有节点都尽可能靠左。最后一层（第 h 层）中可以包含 1 到 2h 个节点。
验证原则：
1、有右无左 ❌
2、如果孩子不双全，那么孩子一定要是叶节点
测试链接：https://leetcode.cn/problems/check-completeness-of-a-binary-tree/
*/
bool isCompleteTree(TreeNode* root)
{
    vector<TreeNode*> v;
    int l=0;
    int r=1;
    bool leaf=false;
    TreeNode* cur=root;
    v.push_back(root);
    while(l<r)
    {
        cur=v[l++];
        if(cur->left==nullptr&&cur->right!=nullptr) return false;
        else if(leaf&&(cur->left!=nullptr||cur->right!=nullptr)) return false;
        else
        {
            if(cur->left!=nullptr) 
            {
                v.push_back(cur->left);
                r++;
            }
            if(cur->right!=nullptr) 
            {
                v.push_back(cur->right);
                r++;
            }
        }
        if(cur->left==nullptr||cur->right==nullptr) leaf=true;
    }
    return true;
}

/*2、一棵树一定是完全二叉树，求这棵完全二叉树的节点个数,时间复杂度小于O(n)，实际为O((logn)^2)
测试链接：https://leetcode.cn/problems/count-complete-tree-nodes/
*/

int Height(TreeNode* root,int level)//深度优先，利用完全二叉树性质扎到底
{
    TreeNode* cur=root;
    while(cur!=nullptr)
    {
        cur=cur->left;
        level++;
    }
    return level-1;
}
int count(TreeNode *cur, int level, int h)
{
    if(level==h) return 1;
    int curh=Height(cur->right,level+1);
    //66-67为核心：利用定义，若右树扎到最深，则左树满且高度为h-1；
    //若右树扎不到最深，则右树满且高度为h-2（右树最浅也要扎到h-1层）
    if(curh==h) return (1<<(h-level))+count(cur->right,level+1,h);
    else return (1<<(curh-level))+count(cur->left,level+1,h);
}
int countNodes(TreeNode* root)
{
    if(root==nullptr) return 0;
    int h=Height(root,1);//整棵树的总高度
    return count(root,1,h);
}