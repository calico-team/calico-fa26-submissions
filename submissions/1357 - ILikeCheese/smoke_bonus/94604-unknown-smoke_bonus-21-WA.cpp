#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ll N, R; cin >> N >> R;
    vector<ll> A(N), B(N,0);
    for (ll i=0; i<N; i++) cin >> A[i];
    for (ll i=1; i<N; i++) B[i] = A[i]-A[i-1];
    ll track = 2;
    ll time = 0;
    for (ll i=0; i<N; i++) {
        track-=1;
        time+=B[i];
        if (time>=R) {
            track = min<long long>(2,time/R);
            time=time-R;
        }
        if (track<=0) {
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