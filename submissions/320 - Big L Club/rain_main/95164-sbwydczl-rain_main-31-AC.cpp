#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int n, k; cin >> n >> k;
    int ans = n * k;

    int x; int y; int blank; char dir;
    map<int, vector<int> > east;
    vector<pair<int, int> > eastPairs;
    map<int, vector<int> > north;
    vector<pair<int, int> > northPairs;

    for (int i = 1; i <= n; i++) {
        cin >> x >> y >> blank >> dir;

        if (dir == 'E') {
            east[x + y].push_back(x);
            eastPairs.push_back({x, y});
        } else {
            north[x + y].push_back(x);
            northPairs.push_back({x, y});
        }
    }

    for (auto p: eastPairs) {
        for (int x: north[p.first + p.second]) {
            if (x - p.first < k && x > p.first) ans--;
        }
    }


    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T; cin >> T;
    while (T--) solve();
}