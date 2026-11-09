#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define all(x) x.begin(), x.end()

vector<vector<int>> children; 
vector<int> depths; 
int N, M, K; 

void dfs(int u, int d = -1) {
    if (d >= 0) depths[d]++; 

    if (d+1 < depths.size())
        for (int v : children[u]) {
            dfs(v, d+1);
        }
}

void solve() {
    cin >> N >> M >> K; 

    children.assign(N+1, {});
    depths.assign(min(M, N), 0);

    for (int i = 1; i <= N; i++) {
        int P; cin >> P; 
        children[P].push_back(i);
    }

    dfs(0);

    int ans = 0; 
    for (int d : depths) {
        ans += min(d, K); 
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; cin >> t; 
    while(t--)
        solve();
}