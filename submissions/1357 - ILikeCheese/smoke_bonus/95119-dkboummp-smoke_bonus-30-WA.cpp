#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ll N, R; cin >> N >> R;
    vector<ll> A(N);
    for (ll i=0; i<N; i++) cin >> A[i];
    ll track = 2;
    ll time = 0;
    track-=1;
    for (ll i=1; i<N; i++) {
        ll passed = A[i] - A[i-1];
        time+=passed;
        if (time>=R) {
            track = min<long long>(2LL,track+time/R);
            time%=R;
        }
        track-=1;
        if (track<0) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
    return;
}

int main() {
    int t; cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}