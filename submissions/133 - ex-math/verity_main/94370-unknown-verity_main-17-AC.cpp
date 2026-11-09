#include <bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("O3,unroll-loops")

typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvl;
typedef pair<ll, ll> pll;
typedef long double ld;

#define sp << " " <<
#define sz(x) (ll)(x.size())
#define debug(x) cout << x << endl

const ll BIG=1e18;
const ll MOD=1e9+7;
const ll INF=1e9;
const ll MOD1=998244353;
const ll MX=1e6+5;

ll x4[4]={-1, 1, 0, 0};
ll y4[4]={0, 0, -1, 1};

void solve() {
    ll n, k;
    cin >> n >> k;
    string v(k, '.');
    for (ll i=0; i<k; i++) {
        char c;
        cin >> c;
        v[i]=c;
    }
    string out(n, '.');
    for (ll i=0; i<k; i++) {
        string te(n, v[i]);
        cout << te << endl;
        string res;
        cin >> res;
        if (res=="CORRECT") {return;}
        for (ll j=0; j<n; j++) {
            if (res[j]!='_') out[j]=res[j];
        }
    }
    cout << out << endl;
    string res;
    cin >> res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll tc=1;
    cin >> tc;
    while (tc--) solve();
}