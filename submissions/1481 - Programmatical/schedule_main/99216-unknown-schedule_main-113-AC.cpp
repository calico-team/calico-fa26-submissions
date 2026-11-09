#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<int> p, memo;

int depth(int i) {
    if (memo[i]) return memo[i];
    if (!p[i]) return memo[i] = 1;
    memo[i] = depth(p[i]) + 1;
    return memo[i];
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    p.assign(n + 1, 0), memo.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    vector<int> cnt(m + 1);
    for (int i = 1; i <= n; i++) {
        int d = depth(i);
        if (d <= m) cnt[d]++;
    }
    int ans = 0, tmp = 0;
    for (int i = 1; i <= m; i++) {
        tmp += cnt[i];
        int s = min(k, tmp);
        ans += s, tmp -= s;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
