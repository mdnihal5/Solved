// problem link : https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/description/
// contest : leetcode weekly 426
// solution : https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/submissions/1467079675


#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1, m = edges2.size() + 1;
        vector<vector<int>> g1(n), g2(m);

        for (const auto& edge : edges1) {
            g1[edge[0]].push_back(edge[1]);
            g1[edge[1]].push_back(edge[0]);
        }
        for (const auto& edge : edges2) {
            g2[edge[0]].push_back(edge[1]);
            g2[edge[1]].push_back(edge[0]);
        }

        auto solve = [&](auto &graph) -> pair<vector<int>,vector<int>> {
            
            int n=graph.size();
            vector<int> e1(n),e2(n),o1(n),o2(n);
            
            auto dfs1=[&](int node,int par,auto &&dfs)->void{
                e1[node]=1;
                for(auto &child:graph[node]){
                    if(child==par) continue;
                    dfs(child,node,dfs);
                    e1[node]+=o1[child];
                    o1[node]+=e1[child];
                }
            };
            
            dfs1(0,0,dfs1);
            
            e2[0]=e1[0],o2[0]=o1[0];
            auto dfs2=[&](int node,int par,auto &&dfs)->void{
                  for(auto &child:graph[node]){
                      if(child==par) continue;
                      o2[child]=(e2[node]-o1[child])+o1[child];
                      e2[child]=(o2[node]-e1[child])+e1[child];
                      dfs(child,node,dfs);
                  }
            };
            dfs2(0,0,dfs2);
            
            return {e2,o2};
        };

        auto [x1, y1] = solve(g2);
        auto [x2,y2]=solve(g1);
        vector<int>ans;
        int mx=*max_element(y1.begin(),y1.end());
        for(int i=0;i<n;i++){
            ans.push_back(x2[i]+mx);
        }
        return ans;
    }
};
