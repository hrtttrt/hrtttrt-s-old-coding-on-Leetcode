#include<bits/stdc++.h>
using namespace std;

/*二、在二维字符数组中搜索可能的单词
// 给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words
// 返回所有二维网格上的单词。单词必须按照字母顺序，通过 相邻的单元格 内的字母构成
// 其中“相邻”单元格是那些水平相邻或垂直相邻的单元格
// 同一个单元格内的字母在一个单词中不允许被重复使用
// 1 <= m, n <= 12   
// 1 <= words.length <= 3 * 10^4
// 1 <= words[i].length <= 10
时间复杂度：O(m*n*4^L) 此处L=10
关键：前缀树大量剪枝，降低常数时间
// 测试链接 : https://leetcode.cn/problems/word-search-ii/
*/
class Solution {
public:
int MAXN=150001;
 vector<vector<int>> tree;
 vector<int> pass;
 vector<string> end;
 int cnt=1;
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) 
    {
        build(words);
        vector<string> ans;
        for(int i=0;i<board.size();i++)
        {
            for(int j=0;j<board[i].size();j++)
            {
                dfs(board,i,j,1,ans);
            }
        }
        treeclear();
        return ans;
    }

    int dfs(vector<vector<char>>& board,int i,int j,int t,vector<string>& ans) // t : 前缀树的编号
    {
        if(i<0||i>=board.size()||j<0||j>=board[i].size()||board[i][j]==0) return 0; // 越界 或者 走了回头路，直接返回0
        char tmp=board[i][j];
        int road=tmp-'a';//路的编号
        t=tree[t][road];
        if(pass[t]==0||t==0) return 0;
        int fix=0; // fix ：从当前i，j位置出发，一共收集到了几个字符串
        if(!end[t].empty())
        {
            fix++;
            ans.push_back(end[t]);
            end[t].clear();
        }
        // 把i，j位置的字符，改成0，后续的过程，是不可以再来到i，j位置的！
		board[i][j] = 0;
		fix += dfs(board, i - 1, j, t, ans);
		fix += dfs(board, i + 1, j, t, ans);
		fix += dfs(board, i, j - 1, t, ans);
		fix += dfs(board, i, j + 1, t, ans);
		pass[t] -= fix;
		board[i][j] = tmp;
		return fix;
    } 

    void build(vector<string>& words)
    {
        tree.resize(MAXN);
        for(int t=0;t<tree.size();t++) tree[t].resize(26);
        pass.resize(MAXN);
        end.resize(MAXN);
        int path;
        cnt=1;
        int cur=1;
        for(int j=0;j<words.size();j++)
        {
            cur=1;
            pass[cur]++;
            for(int i=0;i<words[j].length();i++)
            {
                path=words[j][i]-'a';
                if(tree[cur][path]==0) tree[cur][path]=++cnt;
                cur=tree[cur][path];
                pass[cur]++;
            }
            end[cur].assign(words[j]);
        }
    }

    void treeclear()
    {
        tree.clear();
        pass.clear();
        end.clear();
    }
};