#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int,int> pii;
#define f first
#define s second
void solve(){
    int n, m, k;
    cin >> n >> m >> k; n++;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++){
        int a;
        cin >> a;
        adj[a].push_back(i);
    }
    queue<int> q;
    vector<int> depth(n);
    depth[0] = 0;
    vector<int> td(1e5, 0);
    q.push(0);
    while (!q.empty()){
        int cur = q.front();
        td[depth[cur]]++;
        q.pop();
        for (int i : adj[cur]){
            q.push(i);
            depth[i] = depth[cur]+1;
        }
    }
    int ans = 0;
    int remaining = 0;
    for (int i = 0; i < m+1; i++){
        remaining += td[i];
        ans += min(remaining, k);
        remaining = max(0, remaining-k);
    }
    cout << ans-1 << endl;
}

int main(){
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}