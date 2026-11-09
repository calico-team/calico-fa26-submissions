#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vi east_x_coords[200005];

void solve() {
    int n, k; cin >> n >> k;
    // x, y, z, d
    vector<pii> north_coords, east_coords;
    rep(i, 0, n) {
        int x, y, z; char d;
        cin >> x >> y >> z >> d;
        
        if (d == 'N') {
            east_x_coords[x+y].clear();
            north_coords.emplace_back(x, y);
        }
        else {
            east_coords.emplace_back(x, y);
        }
    }

    sort(all(east_coords));
    for (auto [x, y] : east_coords) {
        east_x_coords[x+y].push_back(x);
    }

    int ans = k*n;
    for (auto [x, y] : north_coords) {
        auto upper = upper_bound(all(east_x_coords[x+y]), x);
        auto lower = upper_bound(all(east_x_coords[x+y]), x-k);
        ans -= upper - lower;
    }
    cout << ans << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1; cin >> t;
    while (t--) solve();
}
