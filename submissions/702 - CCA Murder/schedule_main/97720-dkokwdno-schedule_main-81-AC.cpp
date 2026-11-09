#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#include <utility>

void solve(){
    //ok so the idea is calc in reverse
    int n, m, k;
    cin>>n>>m>>k;
    vector<int> pre(n + 1);
    vector<int> dep(n + 1), cnt(n + 1);
    vector<vector<int>> adj(n + 1);
    queue<int> q;
    for(int i = 1; i <= n; i++){
        cin >> pre[i];
        if(pre[i]){
            adj[pre[i]].push_back(i);
            cnt[pre[i]]++;
        } else{
            dep[i] = 1;
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur =q.front();
        q.pop();
        for(int nxt : adj[cur]){
            dep[nxt] = dep[cur]+1;
            q.push(nxt);
        }
    }
    priority_queue<pair<int, int>> pq;
    for(int i=1; i <= n; i++){
        if(!cnt[i]){
            pq.push({dep[i], i});
        }
    }
    int ans = 0;
    vector<int> nxt;
    for(int sem = m; sem > 0 && pq.empty() == 0; sem--){
        nxt.clear();
        int used = 0;
        while(pq.empty() ==0 && used < k){
            int cur = pq.top().second;
            pq.pop();
            int p = pre[cur];
            if(dep[cur] > sem){
                if(p && --cnt[p] == 0){
                    pq.push({dep[p], p});
                }
                continue;
            }
            ans++; used++;
            if(p && --cnt[p] == 0){
                nxt.push_back(p);
            }
        }
        for(int cur : nxt){
            pq.push({dep[cur], cur});
        }
    }
    cout << ans << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}