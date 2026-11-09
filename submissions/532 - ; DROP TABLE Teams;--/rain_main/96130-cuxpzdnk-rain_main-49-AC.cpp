#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool compSum(pair<vector<ll>, char>& a, pair<vector<ll>, char>& b) {
    if (a.first[3] != b.first[3]) {
        return a.first[3] < b.first[3];
    }
    return a.first[0] < b.first[0];
}

void solve() {
    ll n,k; cin >> n >> k;
    vector<pair<vector<ll>,char>> drones;
    for (ll i = 0; i < n; i++){
        ll x,y,z,s; char d;
        cin >> x >> y >> z >> d;
        s = x + y;
        drones.push_back({{x,y,z,s},d});
    }
    sort(drones.begin(), drones.end(), compSum);
     ll blocked = 0;
    for (ll i = 0, j; i < n; i = j) {
        for (j = i; j < n && drones[j].first[3] == drones[i].first[3]; j++);
        ll r = i;
        ll cnt = 0;
        for (ll p = i; p < j; p++) {
            if (p < r) {
                if (drones[p].second == 'N') {
                    cnt--;
                }
            }
            else {
                r = p + 1; cnt = 0;
            }
            if (drones[p].second != 'E') {
                continue;
            }
            while (r < j && drones[r].first[0] <= drones[p].first[0] + k-1) {
                if (drones[r].second == 'N') {
                    cnt++;
                }
                r++;
            }
            blocked += cnt;
        }
    }
    cout << n*k - blocked << "\n";    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}