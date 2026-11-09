#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        map<ll, pair<vector<ll>, vector<ll>>> drones;
        for (int i = 0; i < n; i++) {
            ll x, y, z; char dir; cin >> x >> y >> z >> dir;
            if (dir == 'E') drones[x + y].first.push_back(x);
            else drones[x + y].second.push_back(x);
        }
        ll res = n * k;
        for (auto i: drones) {
            vector<ll> north = i.second.second;
            sort(north.begin(), north.end());
            for (ll xe: i.second.first) {
                auto lo = upper_bound(north.begin(), north.end(), xe);
                auto hi = upper_bound(north.begin(), north.end(), xe + k - 1);
                res -= hi - lo;
            }
        }
        cout << res << endl;
    }
}
