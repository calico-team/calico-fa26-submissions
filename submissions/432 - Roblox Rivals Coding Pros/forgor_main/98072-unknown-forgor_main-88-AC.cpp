#include "bits/stdc++.h"

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

constexpr int mm = 2e5 + 3;

int n, par[mm];
vector<int> adj[mm];
void dfs(int u, int p) {
    par[u] = p;
    for (int v : adj[u]) {
        if (par[v]) continue;
        dfs(v, u);
    }
}

void phase1() {
    cin >> n;
    
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    } 
    
    dfs(1, -1);
    
    par[1] = 0;
    for (int i = 2; i <= n; i++) par[1] ^= par[i];
    
    for (int i = 1; i <= n; i++) {
        cout << par[i] << " \n"[i==n];
    }
}

void phase2() {
    cin >> n;
    
    int a[n+3];
    int m = 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == -1) m = i;
        else if (i > 1) a[1] ^= a[i];
    }
    a[m] = a[1];
    
    for (int i = 2; i <= n; i++) {
        cout << i << ' ' << a[i] << '\n';
    }
}

void solve() {
    string phase;
    cin >> phase;
    if (phase == "FIRST") phase1();
    else phase2();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    int t = 1;
    // cin >> t;
    while (t--) solve();
} 
