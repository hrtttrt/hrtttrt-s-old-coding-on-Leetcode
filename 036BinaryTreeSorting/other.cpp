#include<bits/stdc++.h>
using namespace std;
typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
}TreeNode;
/*收集累加和等于aim的所有路径
递归恢复现场(回溯) [[收集达标路径和]] 测试链接 给你二叉树的根节点 root 和一个整数目标和 targetSum 
找出所有 从根节点到叶子节点 路径总和等于给定目标和的路径。 
叶子节点 是指没有子节点的节点。 
*/
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) 
    {
        findSum(root,0,targetSum);
        return ans;
    }
    void findSum(TreeNode* root, int curSum, int targetSum)
    {
        if(root==nullptr) return;//记得检查空指针
        if(root->left==nullptr&&root->right==nullptr)
        {
            path.push_back(root->val);
            if((curSum+root->val)==targetSum)
            {
                ans.emplace_back(path);
            }
        }
        else
        {
            path.push_back(root->val);
            if(root->left!=nullptr) 
            {
                findSum(root->left,curSum+root->val,targetSum);
            }
            if(root->right!=nullptr) 
            {
                findSum(root->right,curSum+root->val,targetSum);
            }
        }
        path.pop_back();
    }
    vector<vector<int>> ans;
    vector<int> path;
};

/*平衡二叉树:是指该树所有节点的左右子树的深度相差不超过 1。
2、判断平衡二叉树
测试链接：https://leetcode.cn/problems/balanced-binary-tree/
*/
class Solution {
public:
    bool isBalanced(TreeNode* root) 
    {
        balance=true;
        int h=Height(root);
        return balance;
    }
    int Height(TreeNode* root)//递归法求子树深度
    {
        if(!balance||root==nullptr) return 0;//空节点深度为0；若不平衡，尽快返回，此时深度值不重要了
        int lh=Height(root->left);
        int rh=Height(root->right);
        if((std::max(lh,rh)-std::min(lh,rh))>1) balance=false;
        return std::max(lh,rh)+1;
    }
bool balance=true;
};

/*3、二叉树打家劫舍问题
[[打家劫舍系列问题]] 相邻节点（两个直接相连的）不能偷， 怎么拿到最大值 全局变量法就可以做 
动态规划，每个节点的不同状态（注意这个动态规划是从树底开始，一层一层往上返回的动态规划，而不是从上到下的动态规划）
测试链接： https://leetcode.cn/problems/house-robber-iii/
*/
class Solution {
public:
// 全局变量，完成了X子树的遍历，返回之后  
// yes变成，X子树在偷头节点的情况下，最大的收益  
int yes;  
// 全局变量，完成了X子树的遍历，返回之后  
// no变成，X子树在不偷头节点的情况下，最大的收益  
int no; 
    void best(TreeNode* root)
    {
        int y,n;
        if(root==nullptr)
        {
            y=0;
            n=0;
        }
        else
        {
            y=root->val;
            n=0;
            best(root->left);
            y+=no;// 如果选了自己，就+no（不要自己和自己直接相连的节点）  
            n+=std::max(yes,no);// 如果没选自己，就比较自己和自己相连的节点，选大还是不选大，选比较大的那个  
            best(root->right);
            y+=no;
            n+=std::max(yes,no);
        }
        // 更新数据，返回到上一层
        yes=y;
        no=n;
    }
    int rob(TreeNode* root) {
        yes=0;
        no=0;
        best(root);
        return std::max(yes,no);
    }
};