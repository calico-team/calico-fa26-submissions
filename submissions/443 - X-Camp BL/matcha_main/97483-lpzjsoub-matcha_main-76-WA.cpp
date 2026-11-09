#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve() {
    int N;
    if (!(cin >> N)) return;
    vector<ll> L(N), R(N);
    for (int i = 0; i < N; ++i) cin >> L[i];
    for (int i = 0; i < N; ++i) cin >> R[i];
    ll curx = 0;
    ll tott = 0;
    for (int i = 0; i < N; ++i) {
        if (L[i] == R[i]) {
            curx ^= L[i];
        } else {
            ll diff = L[i] ^ R[i];
            int msb = 63 - __builtin_clzll(diff);
            ll mk = (1LL << (msb + 1)) - 1;
            tott |= mk;
            curx ^= (R[i] & ~mk);
        }
    }
    ll joy = curx | tott;
    cout << joy << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) solve();
    }
}
