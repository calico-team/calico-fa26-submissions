#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
const int N = 200010;
int a[N];
int h[N];
vector<vector<int>> graph(N);
void calch(int cur, int par){
    h[cur] = 1;
    for(auto i : graph[cur]){
        if(i == par) continue;
        calch(i, cur);
        h[cur] = max(h[cur], h[i]+1);
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while(T--){
        int n, m, k;
        cin >> n >> m >> k;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            if(a[i] != 0){
                graph[a[i]].pb(i);
            }
        }
        int ans = 0;
        vector<int> indeg(n+1);
        for(auto& i : indeg) i = 0;
        for(int i = 1; i <= n; i++){
            for(auto j : graph[i]){
                indeg[j]++;
            }
        }
        for(int i = 1; i <= n; i++){
            if(indeg[i] == 0){
                calch(i, -1);
            }
        }
        priority_queue<pii> q;
        for(int i = 1; i <= n; i++){
            if(indeg[i] == 0){
                q.push({h[i], i});
            }
        }
        for(int i = 1; i <= m && !q.empty(); i++){
            vector<int> used;
            while(used.size() < k && !q.empty()){
                used.pb(q.top().second);
                q.pop();
                ans++;
            }
            for(int j : used){
                for(int k : graph[j]) q.push({h[k], k});
            }
        }
        cout << ans << endl;
        for(int i = 1; i <= n; i++){
            graph[i].clear();
        }
    }
    return 0;
}