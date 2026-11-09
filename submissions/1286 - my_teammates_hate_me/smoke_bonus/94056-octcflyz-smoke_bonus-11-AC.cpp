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
    ll n, r;
    cin >> n >> r;

    vll a(n);
    rep(i, 0, n) cin >> a[i];

    vll t(2, 0);
    int ans = 0;
    rep(i, 0, n) {
        if (t[0] <= a[i]) {
            t[0] = max(a[i], t[1]) + r;
            sort(all(t));
            ans++;
        } else {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int test = 1;
    cin >> test;
    for (int t = 0; t < test; t++) {
        solve();
    }
}