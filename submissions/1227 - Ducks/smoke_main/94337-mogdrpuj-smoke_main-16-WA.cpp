#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;

#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

// Goes to stderr NOT stdout and only active with -DLOCAL. Ex: dbg(x) prints "x = value  ".
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << "  "
#define dbgln(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#define dbgln(x)
#endif

// To read file, call setIO("filename")
void setIO(const string& name = "") {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!name.empty()) {
        (void)!freopen((name + ".in").c_str(), "r", stdin);
        (void)!freopen((name + ".out").c_str(), "w", stdout);
    }
}

void solve() {
    int n, r;
    cin>>n>>r;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin>>a[i];
    }
    int n_charges = 2;
    bool fail = false;
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            if (n_charges < 2 && a[i] - a[i-1] >= r) { n_charges++; }
        }
        if (n_charges == 0) {
            fail = true;
            break;
        } else {
            n_charges--;
        }
    }
    if (fail) cout << "NO\n";
    else cout << "YES\n";
}

int main() {
    setIO();
    int T;
    cin>>T;
    while (T-- > 0)
        solve();
}
