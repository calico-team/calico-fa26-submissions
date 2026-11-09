#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <set>
#include <map>
#include <stack>
#include <cstdio>
#include <unordered_map>
#include <map>
#include <numeric>
#include <utility>
#include <functional>
#include <string>
#include <list>
using namespace std;
typedef long long ll;




int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;cin>>t;

    while(t--){
        int n, m, k;cin>>n>>m>>k;

        vector<int> nums(n);

        for(int i = 0; i<n; i++){
            cin>>nums[i];
        }

        unordered_map<int, vector<int>> graph;
        vector<int> deg(n);

        for(int i = 0; i<n; i++){
            if(nums[i] != 0){
                graph[nums[i]-1].push_back(i);//0 is root
                deg[i]++;
            }
        }

        vector<int> depth(n, -1);//bigger depth is more closer to root
        
        function<int(int)> dfs = [&](int c)->int{
            if(depth[c] != -1) return depth[c];
            
            int maxdepth = 0;
            for(int next : graph[c]){
                int d = dfs(next);
                maxdepth = max(maxdepth, d);
            }

            depth[c] = 1+maxdepth;
            return depth[c];
        };


        vector<int> doing;

        for(int i = 0; i<n; i++){
            if(nums[i] == 0) doing.push_back(i);
        }

        vector<pair<int, int>> good;
        for(int i : doing){
            int height = dfs(i);
            good.push_back({height, i});
        }
        
        int res = 0;

        for(int i = 0; i<m; i++){
            
            sort(good.begin(), good.end(), [](auto a, auto b){return a.first>b.first;}); 
            vector<pair<int, int>> next;

            for(int j = 0, took = 0; j<good.size(); j++){
                if(took < k){
                    int cur = good[j].second;
                    res++;took++;

                    for(int nextcourse : graph[cur]){
                        next.push_back({depth[nextcourse], nextcourse});
                    }
                }else{
                    next.push_back(good[i]);
                }
            }

            swap(good, next);
        }

        cout<<res<<"\n";
    }

}