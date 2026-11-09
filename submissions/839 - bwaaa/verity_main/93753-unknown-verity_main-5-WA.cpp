#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

template<typename T>
using minheap = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using maxheap = priority_queue<T>;
template<typename T>
using vec = vector<T>;

#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define ROF(i,a,b) for(int i = (a); i >= (b); --i)
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define rot(a, x) rotate(a.begin() + 1, a.begin() + 1 + x, a.end())
#define sz(x) (int)(x).size()

void solve() {
    ll n, k;
    cin >> n >> k;
    vec<char> a(k);
    for (ll i = 0; i < k; i++) cin >> a[i];

    string ans(n, '_');
    for (auto c : a) {
        for (ll i = 0; i < n; i++) cout << c;
        cout << endl;
        string res;
        cin >> res;
        for (ll i = 0; i < n; i++) {
            if (res[i] != '_') ans[i] = res[i];
        }
    }
    cout << ans << endl;
    string res;
    cin >> res;
    assert(res == "CORRECT");
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll tc = 1;
    cin >> tc;
    for (ll i = 1; i <= tc; i++) {
        solve();
        cout << '\n';
    }
}
