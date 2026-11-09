#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;

/** for blitz */
// ifstream cin("input.txt");
// ofstream cout("output.txt");

void solve() {
    int n; ll k;
    cin >> n >> k;

    /** Take in input. */
    vector<vi> drone(n, vi(4));
    rep(i, 0, n) {
        rep(j, 0, 3) cin >> drone[i][j];
        char buf;
        cin >> buf;
        if (buf == 'N') drone[i][3] = 1;
    }

    sort(all(drone));

    /** sweepline from right to left */
    ll ans = n * k;
    map<int, priority_queue<int>> up;

    for (int i = n-1; i >= 0; i--) {
        if (drone[i][3] == 1) {
            up[drone[i][0] + drone[i][1]].push(drone[i][0]);
        } else {
            while (!up[drone[i][0] + drone[i][1]].empty() && up[drone[i][0] + drone[i][1]].top() - drone[i][0] >= k) {
                up[drone[i][0] + drone[i][1]].pop();
            }
            ans -= up[drone[i][0] + drone[i][1]].size();
        }
    }

    cout << ans << endl;

}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int test = 1;
    cin >> test;
    for (int t = 0; t < test; t++) {
        solve();
    }
}