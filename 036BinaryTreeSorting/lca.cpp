#include<bits/stdc++.h>
using namespace std;
typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
}TreeNode;
//LCA:二叉树上寻找两个节点的最近公共祖先。

/*1、普通二叉树上寻找两个节点的最近公共祖先。
考虑 P 包含Q ，或 Q 包含 P
分了两树 ，核心想法是：遇到要找的节点，就返回不空（true）。然后一路返回合并，
如果返回的路上，没有遇到两个都是不空的情况，说明自己就是两个点的共同祖先（走最后一句的return）
如果都为不空，说明当前节点就是公共祖先，会返回当前节点。 有且仅切且一个节点会存在都不为空的情况
测试链接：https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
*/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
    if(root==nullptr||root==p||root==q) return root;
    TreeNode* l=lowestCommonAncestor(root->left,p,q);
    TreeNode* r=lowestCommonAncestor(root->right,p,q);
    if(l!=nullptr&&r!=nullptr) return root;
    if(l==nullptr&&r==nullptr) return nullptr;
    return l!=nullptr?l:r;
}

/*2、搜索二叉树上寻找两个节点的最近公共祖先。
二叉搜索树定义如下：
1、节点的左子树只包含 小于 当前节点的数。
2、节点的右子树只包含 大于 当前节点的数。
3、所有左子树和右子树自身必须也是二叉搜索树。
测试链接：https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/
*/
/*root从上到下  
如果先遇到了p，说明p是答案  
如果先遇到了q，说明q是答案  
如果root在p~q的值之间，不用管p和q谁大谁小，只要root在中间，那么此时的root就是答案  
如果root在p~q的值的左侧，那么root往右移动  
如果root在p~q的值的右侧，那么root往左移动
*/
TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q)//迭代写法
{
    TreeNode* cur=root;
    while(cur!=nullptr&&cur->val!=p->val&&cur->val!=q->val)
    {
        if(cur->val<std::max(p->val,q->val)&&cur->val>std::min(p->val,q->val)) break;
        cur=cur->val>std::max(p->val,q->val)?cur->left:cur->right;
    }
    return cur;
}
TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) //（抄来的）递归写法
{  
    if (root->val > max(p->val,q->val)){  
        return lowestCommonAncestor2(root->left,p,q);  
    } else if (root->val < min(p->val,q->val)){  
        return lowestCommonAncestor2(root->right,p,q);  
    } else{  
        return root;  
    }  
}