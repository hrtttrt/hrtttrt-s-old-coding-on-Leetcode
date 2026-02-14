#include<bits/stdc++.h>
using namespace std;
// 一、地图分析
// 你现在手里有一份大小为 n x n 的 网格 grid
// 上面的每个 单元格 都用 0 和 1 标记好了其中 0 代表海洋，1 代表陆地。
// 请你找出一个海洋单元格，这个海洋单元格到离它最近的陆地单元格的距离是最大的
// 并返回该距离。如果网格上只有陆地或者海洋，请返回 -1。
// 我们这里说的距离是「曼哈顿距离」（ Manhattan Distance）：
// (x0, y0) 和 (x1, y1) 这两个单元格之间的距离是 |x0 - x1| + |y0 - y1| 。
// 测试链接 : https://leetcode.cn/problems/as-far-from-land-as-possible/
class Solution {
public:
    vector<int> move={-1,0,1,0,-1};// 移动矩阵，0:上，1:右，2:下，3:左
    // (x,y)  i来到0位置 : x + move[i], y + move[i+1] -> x - 1, y
	// (x,y)  i来到1位置 : x + move[i], y + move[i+1] -> x, y + 1
	// (x,y)  i来到2位置 : x + move[i], y + move[i+1] -> x + 1, y
	// (x,y)  i来到3位置 : x + move[i], y + move[i+1] -> x, y - 1
        
    int maxDistance(vector<vector<int>>& grid) {
        int n=grid.size();
        vector<vector<int>> queue;
        queue.resize(n*n);
        for(int i=0;i<n;i++) queue[i].resize(2);
        vector<vector<bool>> visited;
        visited.resize(n);
        for(int i=0;i<n;i++) visited[i].resize(n);
        int l=0,r=0;//有效区域为l~r-1
        int sea=0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(grid[i][j]==1)
                {
                    visited[i][j]=true;
                    queue[r][0]=i;
                    queue[r++][1]=j;
                }
                else sea++;
            }
        }
        if(sea==0||sea==n*n) return -1;
        int m,level=0;
        while(l<r)
        {
            m=r-l;
            for(int i=0,x,y,nx,ny;i<m;i++)
            {
                x=queue[l][0];
                y=queue[l++][1];
                for(int j=0;j<4;j++)
                {
                    nx=x+move[j];
                    ny=y+move[j+1];
                    if(nx>=0&&nx<n&&ny>=0&&ny<n&&!visited[nx][ny])
                    {
                        visited[nx][ny]=true;
                        queue[r][0]=nx;
                        queue[r++][1]=ny;
                    }
                }
            }
            level++;
        }
        return level;
    }
};