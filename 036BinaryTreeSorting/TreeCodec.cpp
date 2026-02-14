#include<bits/stdc++.h>
using namespace std;
typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
}TreeNode;
/*1、二叉树的先序序列化和反序列化
后序类似；不存在中序的序列化，因为序列化的结果不唯一 [[序列化和反序列化 N 叉树]]
测试链接：https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/
*/
class Codec {
public:
    void encode(TreeNode* root,string &s)//引用字符串s
    {
        if(root==nullptr) s+="#,";
        else
        {
            s+=to_string(root->val)+",";
            encode(root->left,s);
            encode(root->right,s);
        }
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s;
        encode(root,s);
        return s;
    }
    TreeNode* decode(list<string> &dataArray)//list为双向链表
    {
        if(dataArray.front()=="#")
        {
            dataArray.erase(dataArray.begin());
            return nullptr;
        }
            TreeNode* root=new TreeNode(stoi(dataArray.front()));
            dataArray.erase(dataArray.begin());
            root->left=decode(dataArray);
            root->right=decode(dataArray);
            return root;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        list<string> dataArray;
        string str;
        for(auto ch:data)
        {
            if(ch==',')
            {
                dataArray.push_back(str);
                str.clear();
            }
            else str.push_back(ch);
        }
        if(!str.empty())//放最后一个
        {
            dataArray.push_back(str);
            str.clear();
        }
        return decode(dataArray);
    }
};

/*2、按层进行序列化和反序列化,继续使用队列进行序列化,注意特殊情况，头为空指针
测试链接：https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/
*/
class Codec {
public:
    void encode(TreeNode* root,string &s)//引用字符串s
    {
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            if(q.front()==nullptr) s+="#,";
            else
            {
                s+=to_string(q.front()->val)+",";
                q.push(q.front()->left);
                q.push(q.front()->right);
            }
            q.pop();
        }
    }
    TreeNode* decode(vector<string> &dataArray)
    {
        int index=0;
        TreeNode* root=GenerateNode(dataArray[index++]);
        if(root==nullptr) return nullptr;
        vector<TreeNode*> v;
        int l=0;
        int r=1;
        TreeNode* cur=root;
        v.push_back(root);
        while(l<r)
        {
            cur=v[l++];//一个个实节点构建
            cur->left=GenerateNode(dataArray[index++]);
            cur->right=GenerateNode(dataArray[index++]);
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
        return root;
    }
    TreeNode* GenerateNode(string str)
    {
        return str=="#"?nullptr:new TreeNode(stoi(str));
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s;
        encode(root,s);
        return s;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) //string->vector过程
    {
        vector<string> l;
        string s;
        for(auto ch:data)
        {
            if(ch==',')
            {
                l.push_back(s);
                s.clear();
            }
            else s.push_back(ch);
        }
        if(!s.empty())
        {
            l.push_back(s);
            s.clear();
        }
        return decode(l);
    }
};

/*3、[[从前序与中序遍历序列构造二叉树]]注意map写的时候引用传递，不然时间会超出
 测试链接 : https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/ 
*/
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
{
    if(preorder.empty()||inorder.empty()||preorder.size()!=inorder.size()) return nullptr;
    unordered_map<int,int> umap;
    for(int i=0;i<inorder.size();i++) umap.insert(pair<int,int>(inorder[i],i));
    return rebuildTree(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1,umap);
}
TreeNode* rebuildTree(vector<int>& preorder,int l1, int r1, vector<int>& inorder,int l2, int r2,unordered_map<int,int>& umap)
{
    if(l1>r1) return nullptr;//记得检查越界，164行同
    int k=umap[preorder[l1]];//利用中序寻找头，确定边界
    TreeNode* root=new TreeNode(preorder[l1]);
    if(l1==r1) return root;
    root->left=rebuildTree(preorder,l1+1,l1+(k-l2),inorder,l2,k-1,umap);//164-165为逻辑核心，递归
    root->right=rebuildTree(preorder,l1+(k-l2)+1,r1,inorder,k+1,r2,umap);
    return root;
}