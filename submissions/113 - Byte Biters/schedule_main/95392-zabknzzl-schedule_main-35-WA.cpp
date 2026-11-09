#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <cmath>
#include <deque>
using namespace std;

int main(){
    int t; cin >> t;
    while(t--){
        int n,m,k; cin >> n >> m >> k;
        vector<vector<int>> g(n+1);
        vector<int> indeg(n+1,0);
        for (int i = 1; i < n+1; i++){
            int x; cin >> x;
            if (x!=0){
                g[x].push_back(i);
                indeg[i]++;
            }
        }
        deque<int> q;
        for (int i = 1; i < n+1; i++){
            if (indeg[i]==0){
                q.push_back(i);
            }
        }

        int res = 0;
        int sem = 0;
        while (sem<m && !q.empty()){
            int qsize = q.size();
            int take = min(k,qsize);
            for (int i = 0; i < take; i++){
                int curr = q.front();
                q.pop_front();
                res++;

                for (auto&n: g[curr]){
                    indeg[n]--;
                    if(indeg[n]==0){
                        q.push_back(n);
                    }
                }
            }
            sem++;
        }
        cout << res << endl;
    }
    return 0;
}