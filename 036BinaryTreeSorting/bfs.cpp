#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include<queue>
#include<math.h>
using namespace std;

typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
}TreeNode;
/*1、[[二叉树的层序遍历]] [[二叉树按层遍历并收集节点]]
测试连接：https://leetcode.cn/problems/binary-tree-level-order-traversal/
*/
vector<vector<int>> Improved_LevelOrder(TreeNode* root)
{
    vector<TreeNode*> num;
    vector<vector<int>> ans;
    int l=0;
    int r=1;
    int level=0;
    if(root!=nullptr)
    {
        num.push_back(root);
        while(l<r)
        {
            ans.emplace_back();//创造一个新vector<int>用来放数字
            for(int i=l;i<r;i++)
            {
                ans[level].push_back(num[i]->val);
                if(num[i]->left!=nullptr) num.push_back(num[i]->left);
                if(num[i]->right!=nullptr) num.push_back(num[i]->right);
            }
            level++;
            l=r;//自动清空，舍弃已处理过的数
            r=num.size();
        }
    }
    return ans;
}

/*2、[[二叉树的锯齿形层次遍历]] 从左往右->从右往左->从左往右 用数组模拟队列的方法做比较方便，因为可以一次处理一层
测试链接：https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal
*/
vector<vector<int>> zigzagLevelOrder(TreeNode* root)
{
    vector<TreeNode*> num;
    vector<vector<int>> ans;
    int l=0;
    int r=1;
    int level=0;
    if(root!=nullptr)
    {
        num.push_back(root);
        while(l<r)
        {
            ans.emplace_back();//创造一个新vector<int>用来放数字
            if(level%2==0)//双数层->，单数层<-
            {
                for(int i=l;i<r;i++) ans[level].push_back(num[i]->val);
            }
            else
            {
                for(int i=r-1;i>=l;i--) ans[level].push_back(num[i]->val);
            }
            for(int i=l;i<r;i++)
                {
                    if(num[i]->left!=nullptr) num.push_back(num[i]->left);
                    if(num[i]->right!=nullptr) num.push_back(num[i]->right);
                }
            level++;
            l=r;//自动清空，舍弃已处理过的数
            r=num.size();
        }
    }
    return ans;
}

/*3、[[二叉树最大特殊宽度]] 从左往右第一个不为null 可以把它看成完全二叉树，利用编号计算宽度
即每层第一个非空节点到最后一个非空节点的宽度
测试链接：https://leetcode.cn/problems/maximum-width-of-binary-tree/
*/
int widthOfBinaryTree(TreeNode* root)
{
    vector<pair<TreeNode*,unsigned long long>> tree;//利用数对将两个vector优化为一个，ull防溢出
    unsigned long long ans=1;
    unsigned long long l=0;
    unsigned long long r=1;
    if(root==nullptr) return 0;
    else
    {
        tree.push_back(pair<TreeNode*,unsigned long long>(root,1));
        while(l<r)
        {
            for(int i=l;i<r;i++)
            {
                if(tree[i].first->left!=nullptr) tree.emplace_back(tree[i].first->left,tree[i].second*2);//注意是tree[i].second而不是i
                if(tree[i].first->right!=nullptr) tree.emplace_back(tree[i].first->right,tree[i].second*2+1);
            }
            ans=std::max(ans,tree[r-1].second-tree[l].second+1);
            l=r;
            r=tree.size();
        }
    }
    return ans;
}

/*4、[[二叉树的最大深度]] [[返回一棵树的最大深度]] 
测试链接：https://leetcode.cn/problems/maximum-depth-of-binary-tree/
*/
int maxDepth(TreeNode* root)
{
    return root==nullptr?0:std::max(maxDepth(root->left),maxDepth(root->right))+1;//记得加一，因为当前头节点也算一层
}

/*5、碰到叶节点的最小深度 小心孩子为空对答案的干扰，弄成整数最大 [[二叉树的最小深度]]  注意要是判断是不是叶子结点
测试链接：https://leetcode.cn/problems/minimum-depth-of-binary-tree/
*/
 int minDepth(TreeNode* root)
{
    unsigned int temp=1u<<31;
    int ldeep=temp-1;//有符号最大整数，下同
    int rdeep=temp-1;
    if(root==nullptr) return 0;
    else if(root->left==nullptr&&root->right==nullptr) return 1;
    else
    {
        if(root->left!=nullptr) ldeep=minDepth(root->left)+1;
        if(root->right!=nullptr) rdeep=minDepth(root->right)+1;
    }
    return std::min(ldeep,rdeep);   
}