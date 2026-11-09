
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    long long r;
    cin >> n >> r;

    vector<long long> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    queue<long long> recharge;
    int charges = 2;
    bool possible = true;

    for (int i = 0; i < n; i++) {

        while (!recharge.empty() && recharge.front() <= a[i]) {
            recharge.pop();
            charges++;
        }

        if (charges == 0) {
            possible = false;
            continue;
        }

        charges--;

        long long readyTime = a[i] + r;

        if (!recharge.empty()) {
            readyTime = recharge.back() + r;
        }

        recharge.push(readyTime);
    }

    cout << (possible ? "YES" : "NO") << '\n';
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
