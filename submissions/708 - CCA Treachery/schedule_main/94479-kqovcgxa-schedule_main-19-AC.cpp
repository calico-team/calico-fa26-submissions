#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int next() {
    int temp; cin >> temp; return temp;
}
vector<int> lev {};
vector<vector<int>> adj {{}};
void dfs(int node, int level) {
    lev[level]++;
    for (int i : adj[node]) {
        dfs(i, level+1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int ttttt = next();
    while (ttttt--) {
        int n = next(), m = next(), k = next(); lev = {}; adj = {{}};
        vector<int> a {};
        for (int i=0; i<n; i++) { a.push_back(next()); }
        
        for (int i=0; i<n; i++) { adj.push_back({}); }
        for (int i=0; i<n; i++) {
            adj[a[i]].push_back(i+1);
        }
        for (int i=0; i<n; i++) { lev.push_back(0); }
        for (int i : adj[0]) {
            dfs(i, 0);
        }
        int ans = 0, curr = lev[0];
        for (int i=0; i<m; i++) {
            ans += min(curr, k);
            curr -= min(curr, k);
            if (i < n-1) {
                curr += lev[i+1];
            }
        }
        cout << ans << '\n';
    }

    return 0;
}