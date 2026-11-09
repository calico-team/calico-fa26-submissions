#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mx = 2e5;

void solve(){
    int n, k, x, y, z;
    char d;
    cin >> n >> k;
    int ans = n * k;
    vector<vector<int>> north(mx+1), east(mx+1);
    for(int i=0; i<n; i++){
        cin >> x >> y >> z >> d;
        (d == 'N' ? north : east)[x+y].push_back(x);
    }
    for(int i=1; i<=mx; i++) sort(north[i].begin(), north[i].end());
    for(int i=1; i<=mx; i++) for(int j : east[i]) ans -= distance(lower_bound(north[i].begin(), north[i].end(), j), upper_bound(north[i].begin(), north[i].end(), j+k-1));
    cout << ans << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) solve();
}