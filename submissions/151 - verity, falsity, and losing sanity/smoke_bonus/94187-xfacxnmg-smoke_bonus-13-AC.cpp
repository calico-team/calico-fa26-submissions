#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAX = 1e18;
const ll MOD = 1e9 + 7;
bool testcases = true;

void solve() {
    ll n, k; cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    sort(arr.begin(), arr.end());
    ll smokes = 1, t = 0;
    for (int i = 1; i < n; i++) {
        t += arr[i]-arr[i-1];
        smokes += t/k;
        t %= k;
        if (smokes >= 2) smokes = 2, t = 0;
        if (smokes <= 0) {
            cout << "NO" << endl;
            return;
        }
        smokes--;
    }
    cout << "YES" << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    if (testcases) cin >> t;
    for (int i = 1; i <= t; i++) solve();
    return 0;
}