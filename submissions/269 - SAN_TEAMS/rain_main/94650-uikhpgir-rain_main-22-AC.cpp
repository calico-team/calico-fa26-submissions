#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    ll t;
    cin >> t;
    while (t--) {
        ll n, k;
        cin >> n >> k;
        vector<pair<ll, ll>>E,N;
        for (ll i = 0; i < n; i++) {
            ll x, y, z;
            char d;
            cin >> x >> y >> z >> d;
            if (d == 'E') E.push_back({x + y, x});
            else N.push_back({x + y, x});
        }
        sort(N.begin(),N.end());
        ll ans = n * k;
        for (auto [s, x] : E) {
            ll val1;
            ll val2;
            ll l = -1, r = N.size();
            //FFFFFFFVVVVVVV....
            while (l + 1 < r) {
                ll mid = (l + r) / 2;
                if (N[mid].first < s || (N[mid].first == s && N[mid].second < x)) l = mid;
                else r = mid;
            }
            val1 = r;
            ll l1 = -1;
            ll r1 = N.size();
            while (l1 + 1 < r1) {
                ll mid = (l1 + r1) / 2;
                if (N[mid].first < s ||(N[mid].first == s && N[mid].second < x + k)) l1 = mid;
                else r1 = mid;
            }
            val2 = r1;
            ans -= val2 - val1;
        }
        cout << ans << '\n';
    }
}