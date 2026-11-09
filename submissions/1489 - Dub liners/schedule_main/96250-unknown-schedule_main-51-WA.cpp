// #define DEBUG
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf (int)1e18


void solve(){
    int n, m, k;
    cin >> n >> m >> k;

    map<int, vector<int>> father;

    priority_queue<pair<int, int>> pq;

    for (int i = 1; i <= n; i++){
        int a;
        cin >> a;
        father[a].push_back(i);
    }

    for (int i: father[0]){
        pq.push({father[i].size(), i});
    }

    int ans = 0;
    for (int i = 0; i < m; i++){
        int cnt = 0;
        vector<int> lols;
        while (cnt < k){
            if (pq.size() == 0) break;
            auto curr = pq.top();
            pq.pop();
            for (auto j: father[curr.second]) lols.push_back(j);
            // cout << curr.second << " ";
            cnt ++;
        }
        for (auto j: lols){
            pq.push({father[j].size(), j});
        }
        // cout << "\n";
        ans += cnt;
    }
    cout << ans << "\n";
}

int32_t main() {
	#ifdef DEBUG
    freopen("problemname.in", "r", stdin);
    // freopen("problemname.out", "w", stdout); 
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}