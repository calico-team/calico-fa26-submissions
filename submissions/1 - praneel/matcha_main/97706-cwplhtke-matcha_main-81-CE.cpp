#include <bits/stdc++.h>

#define endl '\n'
#define pb push_back
#define ll long long
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

using namespace std;

const ll MOD = 1e9 + 7;

// just keeping this here in case i need it later
ll gcd(ll a, ll b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}
void fastio() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
ll pw(ll b, ll e) {
    ll r = 1;
    b %= MOD;
    if(b < 0) b += MOD;

    while(e) {
        if(e&1) r = r * b % MOD;
        b = b * b % MOD;
        e >>= 1;
    }

    return r;
}
vector<pair<int,int>> a, b;
vector<int> x, y;
vector<char> side;
string out;

//set bits to cnt
inline void addv(int v, int d, int cnt[]) {
    while(v) {
        int h = __builtin_ctz(v);
        cnt[h] += d;
        v &= v - 1;
    }
}
int calc(int cnt[], int bit) {
    int res = 0;

    for(int i = bit - 1; i >= 0; i--) {
        if(cnt[i] == 0) continue;

        if(cnt[i] == 1) res |= 1 << i;
        else {
            res |= (1 << (i + 1)) - 1;
            break;
        }
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    a.assign(n, {0, 0});
    for(int i = 0; i < n; i++) cin >> a[i].first;
    for(int i = 0; i < n; i++) cin >> a[i].second;
    ll ans = 0;
    for(int bit = 29; bit >= 0; bit--) {
        int t = 1 << bit;
        int fx = 0;
        b.clear();
        x.clear();
        y.clear();
        for(auto &p : a) {
            int l = p.first, r = p.second;
            int bl = (l >> bit) & 1;
            int br = (r >> bit) & 1;//RIGHT HERE IS WHAT
            if(bl == br) {
                fx ^= bl;
                b.pb({l & (t - 1), r & (t - 1)});
            }
            else {
                x.pb(t - 1 - l);
                y.pb(r - t);
            }
        }
        int k = sz(x);
        if(k == 0) {
            ans |= (ll)fx << bit;
            swap(a, b);
            continue;
        }
        ans |= 1LL << bit; // works
        int q = 1 ^ fx;
        int cnt[30];
        memset(cnt, 0, sizeof(cnt));
        side.assign(k, 0);
        int p1 = 0;
        bool tie = false;
        // find initial choices
        for(int i = 0; i < k; i++) {
            if(y[i] > x[i]) side[i] = 1;
            else if(x[i] > y[i]) side[i] = 0;
            else {
                side[i] = 1;
                tie = true;
            }
            if(side[i]) p1++;
            addv(side[i] ? y[i] : x[i], 1, cnt);
        }

        int best;
        if((p1 & 1) == q || tie) {
            best = calc(cnt, bit); // works
        }
        else {
            best = -1;
            for(int i = 0; i < k; i++) {
                int oldv = side[i] ? y[i] : x[i];
                int newv = side[i] ? x[i] : y[i];
                addv(oldv, -1, cnt);
                addv(newv, 1, cnt);
                best = max(best, calc(cnt, bit));
                addv(newv, -1, cnt);
                addv(oldv, 1, cnt);
            }
        }
        bool suffix = ((k - q) & 1) != 0;
        if(suffix) b.pb({t - 1 - best, t - 1});
        else b.pb({0, best});
        swap(a, b);
    }
    cout << ans << endl;
}

int main() {
    fastio();

    it T;
    cin >> T;

    while(T--) {
        solve();
    }

    return 0;
}