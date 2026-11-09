// #define DEBUG
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf (int)1e18

void firsts(){
    int n;
    cin >> n;
    vector<int> adj[n + 1];
    for (int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<bool> visited(n + 1, false);

    queue<int> q;
    q.push(1);
    vector<int> par(n + 1, 0);

    while(q.size() > 0){
        int curr = q.front();
        q.pop();

        visited[curr] = true;

        for (auto i: adj[curr]){
            if (visited[i]) continue;
            par[i] = curr;
            q.push(i);
        }
    }

    for (int i = 2; i <= n; i++) par[1] = par[1] ^ par[i];

    for (int i = 1; i <= n; i++) cout << par[i] << " ";
    cout << "\n";
}

void seconds(){

    int n;
    cin >> n;

    vector<int> par(n + 1, 0);
    for (int i = 1; i <= n; i++ ) cin >> par[i];

    if (par[1] == -1){
        for (int i = 2; i <= n; i++) cout << par[i] << " " << i << "\n";
    }

    else {
        for (int i = 2; i <= n; i++) if (par[i] != -1) par[1] ^= par[i];
        for (int i = 2; i <= n; i++) if (par[i] == -1) cout << par[1] << " " << i << "\n";
        for (int i = 2; i <= n; i++) if (par[i] != -1) cout << par[i] << " " << i << "\n";
        
    }
}

int32_t main() {
	#ifdef DEBUG
    freopen("problemname.in", "r", stdin);
    // freopen("problemname.out", "w", stdout); 
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string teie;
    cin >> teie;

    if (teie == "FIRST"){
        firsts();
    }
    else{
        seconds();
    }
}