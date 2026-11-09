#include <bits/stdc++.h>
using namespace std;

void first(){
    int n, u, v;
    cin >> n;
    vector<vector<int>> adj(n+1);
    for(int i=1; i<n; i++){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> par(n+1);
    function<void(int)> dfs = [&](int r){
        for(int ch : adj[r]) if(ch != par[r]){
            par[ch] = r;
            par[1] ^= r;
            dfs(ch);
        }
    };
    dfs(1);
    for(int i=1; i<=n; i++) cout << par[i] << " \n"[i == n];
}

void second(){
    int n, idx = 0;
    cin >> n;
    vector<int> par(n+1);
    for(int i=1; i<=n; i++){
        cin >> par[i];
        if(par[i] == -1) idx = i, par[i] = 0;
    }
    for(int i=1; i<=n; i++) if(i != idx) par[idx] ^= par[i];
    for(int i=2; i<=n; i++) cout << par[i] << ' ' << i << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string run;
    cin >> run;
    if(run == "FIRST") first();
    else second();
}