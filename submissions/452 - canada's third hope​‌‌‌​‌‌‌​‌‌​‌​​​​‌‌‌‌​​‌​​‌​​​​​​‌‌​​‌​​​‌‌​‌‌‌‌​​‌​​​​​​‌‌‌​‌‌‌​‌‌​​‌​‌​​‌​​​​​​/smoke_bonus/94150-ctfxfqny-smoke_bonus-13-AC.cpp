#include <iostream>
#include <queue>
using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")

#define ll long long
#define MAXN (ll)(1e5)

ll T, N, K, tot, a[MAXN + 1];
priority_queue<pair<ll, ll>> pq;

void solve() {
    cin >> N >> K;
    tot = 2;
    while (pq.size()) {
        pq.pop();
    }
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        pq.push({-a[i], -1});
    }
    while (pq.size()) {
        pair<ll, ll> cur = pq.top();
        pq.pop();
        if (cur.second == -1 && tot == 0) {
            cout << "NO" << '\n';
            return;
        }
        if (cur.second == -1) {
            tot--;
            if (tot == 1) {
                pq.push({cur.first - K, 1});
            }
        }
        else {
            tot++;
            if (tot < 2) {
                pq.push({cur.first - K, 1});
            }
        }
    }
    cout << "YES" << '\n';
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);

    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}