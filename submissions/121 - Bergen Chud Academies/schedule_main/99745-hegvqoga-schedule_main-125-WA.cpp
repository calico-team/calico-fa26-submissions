#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
const int N = 200010;
int a[N];
int t[N];
vector<vector<int>> graph(N);
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
        priority_queue<pii> q;
        for(int i = 1; i <= n; i++){
            if(indeg[i] == 0){
                q.push({1, i});
            }
        }
        int cnt = 0;
        int mintime = 1;
        while(!q.empty()){
            int cur = q.top().second;
            int curtime = q.top().first;
            if(curtime == mintime) cnt++;
            else{
                mintime = curtime;
                cnt = 1;
            }
            if(cnt == k+1){
                cnt = 1;
                mintime++;
                curtime++;
            }
            if(mintime == m+1) break;
            ans++;
            q.pop();
            for(auto i : graph[cur]){
                q.push({curtime+1, i});
            }
        }
        cout << ans << endl;
        for(int i = 1; i <= n; i++){
            graph[i].clear();
        }
    }
    return 0;
}