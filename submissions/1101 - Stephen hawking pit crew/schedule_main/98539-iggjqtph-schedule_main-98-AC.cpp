#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main(){
    int x;
    cin >> x;
    for (int i=0; i<x; i++){
        int y, s, z;
        cin >> y >> s >> z;
        vector<vector<int>> adj(y+1);
        for(int j=1; j<=y; j++){
            int m;
            cin >> m;
            adj[m].push_back(j);
        }
        vector<int> v;  
        queue<int> q;
        q.push(0);
        while(!q.empty()){
            int f = q.front();
            q.pop();
            v.push_back(f);
            for(int k:adj[f]){
                q.push(k);
            }
        }
        vector<int> pri (y+1, 1);
        for(int kk=v.size()-1; kk>=1; kk--){
            for(int zz: adj[v[kk]]){
                pri[v[kk]]+= pri[zz];
            }
        }
        priority_queue<pair<int, int>> pq;
        for(int w:adj[0]){
            pq.push({pri[w], w});
        }
        int ans=0;
        for(int ii=0; ii<s; ii++){
            if(pq.empty()){
                break;
            }
            vector<int> vv;
            for(int jj=0; jj<z; jj++){
                if(pq.empty()){
                    break;
                }
                vv.push_back(pq.top().second);
                pq.pop();
            }
            ans+=vv.size();
            for(int q:vv){
                for(int r:adj[q]){
                    pq.push({pri[r], r});
                }
            }
        }
        cout << ans << endl;
    }

}