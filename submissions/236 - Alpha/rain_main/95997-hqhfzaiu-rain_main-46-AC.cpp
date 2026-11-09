#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<pair<int, int>> e, v;
        for (int i = 0; i < n; i++) {
            int x, y, z;
            char d;
            cin >> x >> y >> z >> d;
            if (d == 'E') e.push_back({x + y, x});
            else v.push_back({x + y, x});}
        sort(e.begin(), e.end());
        ll ans = (ll)n * k;
        for (auto [s, x] : v)
            ans -= upper_bound(e.begin(), e.end(), make_pair(s, x)) - lower_bound(e.begin(), e.end(), make_pair(s, x - k + 1));
        cout << ans << "\n";}}