#include<bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)

void solve() {
    int n, r;
    cin >> n >> r;

    int x;

    bool check = true;
    int smoke_hp = 2*r;
    int start_recharge = INT_MAX;

    for (int i = 0; i < n; i++) {
        cin >> x;

        if (!check) continue;

        if (smoke_hp < 2*r) {
            smoke_hp = min(2*r, smoke_hp + x - start_recharge);
        }

        if (smoke_hp - r < 0) {
            check = false;
            continue;
        }

        smoke_hp -= r;
        start_recharge = x;
    }

    if (check) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    fastio;

    int tc;
    cin >> tc;

    while (tc--) {
        solve();
    }
}