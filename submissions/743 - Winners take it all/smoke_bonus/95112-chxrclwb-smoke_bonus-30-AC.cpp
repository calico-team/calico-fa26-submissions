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
        int v1 = 0, v2 = 0;
        for (int i = 0; i < n; i++) {
            if (v1 <= a[i]) {
                v1 = max(a[i], v2) + r;
            } else if (v2 <= a[i]) {
                v2 = max(a[i], v1) + r;
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