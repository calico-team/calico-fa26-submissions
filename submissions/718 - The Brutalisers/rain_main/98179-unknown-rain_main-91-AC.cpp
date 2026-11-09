#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int N; ll K; cin >> N >> K;
        vector<ll> E, Nn;
        for (int i = 0; i < N; i++) {
            ll x, y, z; char d; cin >> x >> y >> z >> d;
            (d == 'E' ? E : Nn).push_back((x + y) << 18 | x);
        }
        sort(E.begin(), E.end());
        ll Ans = N * K;
        for (ll v : Nn) {
            ll s = v >> 18, x = v & ((1 << 18) - 1);
            Ans -= upper_bound(E.begin(), E.end(), v) - lower_bound(E.begin(), E.end(), s << 18 | max(0LL, x - K + 1));
        }
        cout << Ans << '\n';
    }
}