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
    int n, k;
    cin >> n >> k;
    vector<char> a(k);
    rep(i, 0, k) cin >> a[i];

    string ans(n, '_');
    rep(i, 0, k) {
        string meow(n, a[i]);

        cout << meow << endl;
        
        string t;
        cin >> t;

        if (t == "CORRECT") return;

        rep(i, 0, n) {
            if (t[i] != '_') {
                ans[i] = t[i];
            }
        }
    }

    cout << ans << endl;
    string buf;
    cin >> buf;
    
    assert(buf == "CORRECT");
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int test = 1;
    cin >> test;
    for (int t = 0; t < test; t++) {
        solve();
    }
}