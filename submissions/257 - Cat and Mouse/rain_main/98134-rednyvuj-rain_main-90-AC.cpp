#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using str = string;

#define int long long
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define fox(i,n) for(int i=0;i<(n);++i)

vector<pii> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};


signed main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<pair<int, int>> H, V;
        fox(i, n) {
            int x, y, z; cin>>x>>y>>z;
            char d; cin>>d;
            if (d == 'E') H.pb({x+y, x});
            else V.pb({x+y, x});
        }
        sort(all(H)); sort(all(V));
        vector<int> Hx, Hsum;
        for (auto [sum, xh] : H) {
            Hx.pb(xh); Hsum.pb(sum);
        }
        int cnt = 0;
        for (auto [sum, xv] : V) {
            int l = lower_bound(all(Hsum), sum) - Hsum.begin();
            int r = upper_bound(all(Hsum), sum) - Hsum.begin();
            int hi = lower_bound(Hx.begin()+l, Hx.begin()+r, xv) - Hx.begin();
            int lo = upper_bound(Hx.begin()+l, Hx.begin()+r, xv-k) - Hx.begin();
            cnt += (hi - lo);
        }
        cout << (long long)n*k - cnt << '\n';
    }

    return 0;
}


/*
z coord useless
only care about insersection where (x, y, t) is all equal
horizontal drones only ever intersect with vertical drones
let drone 1 be H, drone 2 be V: intersect at (x_2, y_1)
-> intersect iff (0 < x_2-x_1 == y_1-y_2 < K) 

sort bsearch

not possible to have >2 drones intersect at once

collect first, move second
*/