#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
using namespace std;
// const int MOD = 998'244'353;
// const int MOD = 1e9 + 7;

void solve() {
    int n, k; cin >> n >> k;

    unordered_map<int, vector<int>> freq; // [sum] = {x values}

    vector<array<int, 2>> up;
    for (int i = 0; i < n; i++) {
        int x, y, z; cin >> x >> y >> z;
        char d; cin >> d;

        if (d == 'E') freq[x + y].push_back(x);
        else up.push_back({x, y});
    }

    for (auto [a, b] : freq) sort(freq[a].begin(), freq[a].end());

    int ans = n * k;

    for (auto [x, y] : up) {
        if (freq.find(x + y) == freq.end()) continue;

        vector<int>& cur = freq[x + y];

        // for (auto v : cur) cout << v << " ";
        // cout << "\n";

        int low = 0, high = (int) cur.size() - 1;
        while (low < high) {
            auto mid = (low + high + 1) / 2;
            if (x - cur[mid] < 0) high = mid - 1;
            else low = mid;
        }

        if (x - cur[low] < 0) continue;
        int b = low;

        low = 0, high = (int) cur.size() - 1;
        while (low < high) {
            auto mid = (low + high) / 2;
            if (x - cur[mid] >= k) low = mid + 1;
            else high = mid;
        }

        if (x - cur[low] >= k) continue;

        // cout << x << " " << y << "\n";
        ans -= b - low + 1;
    }

    cout << ans << "\n";
}

signed main() {
    cin.sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--) solve();


    return 0;
}