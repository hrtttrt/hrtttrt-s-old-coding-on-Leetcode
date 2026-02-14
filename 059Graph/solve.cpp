#include<bits/stdc++.h>
using namespace std;
// 一、拓扑排序
// 邻接表建图（动态方式）
// 课程表II
// 现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1
// 给你一个数组 prerequisites ，其中 prerequisites[i] = [ai, bi]
// 表示在选修课程 ai 前 必须 先选修 bi
// 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1]
// 返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序
// 你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组
class Solution {
    public:
        vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
            vector<vector<int>> graph;
            graph.resize(numCourses);
            vector<int> indegree;
            indegree.resize(numCourses);
            int n=prerequisites.size();
            for(int i=0;i<n;i++)
            {
                graph[prerequisites[i][1]].push_back(prerequisites[i][0]);
                ++indegree[prerequisites[i][0]];
            }
            vector<int> queue;
            queue.resize(numCourses);
            int cnt=0,l=0,r=0,cur=0;
            for(int i=0;i<numCourses;i++)
            {
                if(indegree[i]==0) queue[r++]=i;
            }

            while(l<r)
            {
                ++cnt;
                cur=queue[l++];//队列弹出
                for(int next:graph[cur])
                {
                    if(--indegree[next]==0) queue[r++]=next;//入度为0入队
                }
            }
            vector<int> empty;
            return cnt==numCourses?queue:empty;
        }
    };