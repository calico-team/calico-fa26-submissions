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
    vector<int> children(n, 0);
    for (int i = 1; i < n; i++){
        int a;
        cin >> a;
        adj[a].push_back(i);
        children[a]++;
    }
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({children[0], 0});
    int out = 0;
    for (int i = 0; i < m+1; i++){
        int a = 0;
        vector<pii> add;
        while (!q.empty() && a < k){
            a++;
            pii cur = q.top();
            q.pop();
            for (int j : adj[cur.s]){
                add.push_back({children[j], j});
            }
        }
        for (pii j : add){
            q.push(j);
        }
        out += a;
    }
    cout << out-1 << endl;
}

int main(){
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}