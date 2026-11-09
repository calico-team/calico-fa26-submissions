#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


void solve() {
    ll n, k;
    cin >> n >> k;
    map<int, vector<int>> east, north;
    for (int i = 0; i < n; i++) {
        int x, y, z;
        char d;
        cin >> x >> y >> z >> d;
        if (d == 'E') {
            east[x+y].push_back(x);
        } else {
            north[x+y].push_back(x);
        }
    }

    ll ans = n*k;
    for (auto &p : north) {
        sort(p.second.begin(), p.second.end());
    }
    for (auto &p : east) {
        int sum = p.first;

        for (int x : p.second) {
            vector<int> &v = north[sum];
            ans -= lower_bound(v.begin(), v.end(), x+k) - lower_bound(v.begin(), v.end(), x);
        }
    }

    cout << ans << "\n";
    return;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); // NULL 0

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}