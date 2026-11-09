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
    int n, k; cin >> n >> k;
    vector<char> letters(k);
    for (char& c : letters)
        cin >> c;

    vector<char> ans(n);

    rep(i, 0, k) {
        string s(n, letters[i]);
        cout << s << endl << flush;
        string res; cin >> res;
        if (res == "CORRECT") return;
        rep(j, 0, n) {
            if (res[j] != '_')
                ans[j] = letters[i];
        }
    }

    string ans_str;
    for (char c : ans)
        ans_str += c;
    cout << ans_str << endl;
    string res; cin >> res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
