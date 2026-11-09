#include <ext/pb_ds/assoc_container.hpp>
#include <bits/stdc++.h>
#include <cstring>
 
typedef long long ll;
using namespace std;
using namespace __gnu_pbds;
 
/*template<class T> 
using Tree=tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;*/

vector<int> adj[10001];
int cost[10001];

void dfs(int x, int p){
    cost[x]=0;
    for (int i: adj[x]){
        if (i==p) continue;
        dfs(i,x);
        cost[x]=max(cost[x],cost[i]+1);
    }
    return;
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt--){
        for (int i=0; i<=10000; i++) adj[i].clear();
        int n,m,k; cin >> n >> m >> k;
        bool orphan[n]; memset(orphan,0,sizeof(orphan));
        for (int i=1; i<=n; i++){
            int t; cin >> t;
            if (t!=0) adj[t].push_back(i);
            else orphan[i]=1;
        }
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        for (int i=1; i<=n; i++){
            if (orphan[i]){
                dfs(i,-1);
                pq.push({cost[i],i});
            }
        }
        int out=0;
        bool vis[n+1]; memset(vis,0,sizeof(vis));
        for (int i=0; i<m; i++){
            vector<int> take;
            for (int j=0; j<k; j++){
                if (pq.empty()) break;
                take.push_back(pq.top().second);
                vis[pq.top().second]=1;
                pq.pop();
            }
            out+=take.size();
            for (int j: take){
                for (int T: adj[j]){
                    if (vis[T]) continue;
                    pq.push({cost[T],T});
                }
            }
        }
        cout << out << "\n";
    }
}