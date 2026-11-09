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

        vector<int> nums(n+1);

        vector<int> indeg(n+1);

        unordered_map<int, vector<int>> graph;

        for(int i = 1; i<=n; i++){
            cin>>nums[i];
            if(nums[i] != 0){
                graph[nums[i]].push_back(i);
                indeg[i]++;
            }
        }
        
        vector<int> heights(n+1);
        function<int(int)> height = [&](int cur){
            if(heights[cur] != 0)return heights[cur];
            int maxh = 0;
            for(int next : graph[cur]){
                maxh = max(maxh, height(next));
            }

            heights[cur] = 1+maxh;
            return heights[cur];
        };


        for(int i = 1; i<=n; i++){
            if(indeg[i] == 0){
                height(i);
            }
        }

        priority_queue<pair<int, int>> pq;

        for(int i = 1; i<=n; i++){
            if(indeg[i] == 0){
                pq.push({heights[i], i});
            }
        }
        int res = 0;

        for(int s = 0; s<m; s++){
            if(pq.empty())break;

            vector<int> took;
            int numtook = min(k, (int)(pq.size()));
            for(int i = 0; i<numtook; i++){
                took.push_back(pq.top().second);
                pq.pop();
            }

            res += numtook;

            for(int c : took){
                for(int next : graph[c]){
                    pq.push({heights[next], next});
                }
            }


        }

        cout<<res<<"\n";

    }

}