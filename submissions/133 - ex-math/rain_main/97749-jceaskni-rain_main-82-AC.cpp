#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve() {
    int n, k; cin >> n >> k;
    vector<vector<int>> E(2e5+1), N(2e5+1);
    for (int i=0; i<n; i++) {
        int x, y, z; cin >> x >> y >> z;
        char c; cin >> c;
        if (c=='N') N[x+y].push_back(x);
        else E[x+y].push_back(x);
    }
    int ans=n*k;
    for (int xy=0; xy<=2e5; xy++) {
        if (E[xy].empty()) continue;
        if (N[xy].empty()) continue;
        sort(E[xy].begin(), E[xy].end());
        sort(N[xy].begin(), N[xy].end());
        int jl=-1, jr=-1;
        for (int i=0; i<E[xy].size(); i++) {
            while (jr+1<N[xy].size() && N[xy][jr+1]<=E[xy][i]+(k-1)) jr++;
            while (jl+1<N[xy].size() && N[xy][jl+1]<E[xy][i]) jl++;
            // cerr << xy << " " << "(" << E[xy][i] << ", " << xy-E[xy][i] << ")\n";
            // for (int j=0; j<N[xy].size(); j++) {
            //     cerr << xy << " " << "(" << N[xy][j] << ", " << xy-N[xy][j] << ")\n";
            // }
            // cerr << jl << " to " << jr << "\n";
            // cerr << "----\n";
            ans-=jr-jl;
        }
    }
    cout << ans << "\n";    
}
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    // int t=1;
    while (t--) solve();
}
/*
-2 8 8 E
-1 2 1 N
0 0 3 E
*/