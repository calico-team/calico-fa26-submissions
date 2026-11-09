#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
int  main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        ll k;
        cin >> n >> k;
        vector<pair<ll, ll>> e;           
        vector<pair<ll, ll>> nn;           
        for (int i = 0; i < n; i++) {
            ll x, y, z;
            char d;
            cin >> x >> y >> z >> d;
            if (d == 'E') e.push_back({x + y, x});
            else nn.push_back({x + y, x});
        }
        sort(e.begin(), e.end());

        ll covered = 0;
        for (auto& [s, x] : nn) {
            auto hi = upper_bound(e.begin(), e.end(), make_pair(s, x));
            auto lo = lower_bound(e.begin(), e.end(), make_pair(s, x - k + 1));
            covered += hi - lo;
        }
        cout << (ll)n * k - covered << "\n";
    }
    return 0;
}