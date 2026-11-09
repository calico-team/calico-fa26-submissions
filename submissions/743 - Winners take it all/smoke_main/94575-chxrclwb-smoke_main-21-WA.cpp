#include "bits/stdc++.h"

using namespace std;

#define int long long

const int N = 2e5 + 10;
const int md = 1e9 + 7;
const int INF = 1e18;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int T = 1;
    cin >> T;
    while (T--) {
        int n, r;
        cin >> n >> r;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];

        string ans = "YES";
        int v1 = r, v2 = r;
        for (int i = 0; i < n; i++) {
            if (v1 < r && i > 0) {
                v1 += (a[i] - a[i - 1]);
                v2 += max(0ll, v1 - r);
                v1 = min(v1, r);
                v2 = min(v2, r);
            } else if (v2 < r && i > 0) {
                v2 += (a[i] - a[i - 1]);
                v2 = min(v2, r);
            }
            if (v1 == r) {
                v1 = 0;
            } else if (v2 == r) {
                v2 = 0;
            } else {
                ans = "NO";
                break;
            }
            // cout << v1 << " " << v2 << '\n';
        }

        cout << ans << '\n';
    }

    return 0;
}