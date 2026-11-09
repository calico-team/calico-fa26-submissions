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

void solve() {
    int n, r; cin >> n >> r;
    vi a(n);
    for (int& x : a) cin >> x;

    int cnt = 2;
    int recharge1 = -1, recharge2 = -1;
    bool good = true;
    for (int x : a) {
        if (recharge1 != -1 && recharge1 <= x) {
            ++cnt;
            recharge1 = -1;
        }
        if (recharge2 != -1 && recharge2 <= x) {
            ++cnt;
            recharge2 = -1;
        }

        good &= cnt-- > 0;
        if (recharge1 == -1) recharge1 = max(x+r, recharge2+r);
        else if (recharge2 == -1) recharge2 = max(x+r, recharge1+r);
    }

    cout << (good ? "YES\n" : "NO\n");
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1; cin >> t;
    while (t--) solve();
}
