#include<bits/stdc++.h>
using namespace std;
typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
}TreeNode;
/*二叉搜索树定义如下：
1、节点的左子树只包含 小于 当前节点的数。
2、节点的右子树只包含 大于 当前节点的数。
3、所有左子树和右子树自身必须也是二叉搜索树。*/

//二叉搜索树lca见lca.cpp
/*1、判断是否是二叉搜索树
测试链接： https://leetcode.cn/problems/validate-binary-search-tree/
*/
class Solution //（抄来的）栈实现中序遍历，中序遍历时保持升序就一定是搜索二叉树
{  
public:  
    bool isValidBST(TreeNode* root) {  
        if (root== nullptr){  
            return true;  
        }  
        stack<TreeNode*> stk;  
        TreeNode* pre = nullptr;  
        while (root!= nullptr||!stk.empty()){  
            while (root!= nullptr){  
                stk.push(root);  
                root=root->left;  
            }  
            root=stk.top();  
            stk.pop();  
            if (pre!= nullptr && root->val <= pre->val){  
                return false;  
            }  
            pre = root;  
            root=root->right;  
        }  
        return true;  
    }  
};
/*左侧部分的最小最大值， 右侧部分的最小最大值 注意使用long类型，
因为和rmin比较的时候，不能用等号（搜索二叉树的定义），但是存在int最大值会干扰判断，所以要用long
*/
class Solution //递归方法
{
public:
    bool isValidBST(TreeNode* root) 
    {
        if(root==nullptr) //叶节点的子树满足：lmax很小，rmin很大，就能不破坏要求
        {
            max_val=LONG_MIN;
            min_val=LONG_MAX;
            return true;
        }
        bool lok=isValidBST(root->left);
        long lmax=max_val;
        long lmin=min_val;
        bool rok=isValidBST(root->right);
        long rmax=max_val;
        long rmin=min_val;
        max_val=std::max(static_cast<long>(root->val),std::max(lmax,rmax));//63-64逻辑核心，记得把root->val变成long
        min_val=std::min(static_cast<long>(root->val),std::min(lmin,rmin));//其实这里直接(long)(root->val)也行
        return lok&&rok&&root->val>lmax&&root->val<rmin;
    }
    long max_val,min_val;
};

/*2、修剪搜索二叉树
只要某个范围的数字 简单递归，分析到每一个节点的数字大小
测试链接：
*/
TreeNode* trimBST(TreeNode* root, int low, int high) 
    {
        if(root==nullptr) return nullptr;
        if(root->val<low) return trimBST(root->right,low,high);
        if(root->val>high) return trimBST(root->left,low,high);
        root->left=trimBST(root->left,low,high);
        root->right=trimBST(root->right,low,high);
        return root;
    }

