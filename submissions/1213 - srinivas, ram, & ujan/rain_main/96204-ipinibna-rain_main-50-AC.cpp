// Source: https://usaco.guide/general/io
//zenan li
#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
        int N, M; 
        cin >> N >> M;
        map<int, vector<int>> n, e;
        for(int i = 0; i < N; i++) {
                int x, y, z; 
                char dir; 
                cin >> x >> y >> z >> dir;
                if (dir == 'E') e[x + y].push_back(x);
                else n[x + y].push_back(x);
        }
        for(auto& p : e) sort(p.second.begin(), p.second.end());
        for(auto& p : n) sort(p.second.begin(), p.second.end());
        int tot = N * M;
        for(auto& p : e) {
                int u = p.first;
                vector<int> ev = p.second;
                if (!n.count(u)) continue;
                vector<int> nv = n[u];
                for(auto k : ev) {
                        auto it1 = lower_bound(nv.begin(), nv.end(), k) - nv.begin();
                        auto it2 = upper_bound(nv.begin(), nv.end(), k + M - 1) - nv.begin();
                        tot -= it2 - it1;
                }
        }
        cout << tot << "\n";
}

int32_t main() {
	int T; 
	cin >> T;
	while (T--) solve();
}
