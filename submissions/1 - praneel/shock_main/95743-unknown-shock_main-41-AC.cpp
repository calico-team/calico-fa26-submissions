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
    return gcd(a, b % a);
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

vector<vector<int>> nxt_col;

// dsu on each row
int find_free(int r, int c) {
    if(nxt_col[r][c] == c) return c;
    return nxt_col[r][c] = find_free(r, nxt_col[r][c]);
}
void solve() {
    int n, m, q ;
    cin >>n >> m>> q;

    vector<array<ll, 3>> qs(q);
    for(int i= 0; i < q; i++) {
        cin>> qs[i][0] >> qs[i][1] >>qs[i][2];
    }
    vector<vector<ll>> grid(n, vector<ll>(m, 0));
    nxt_col.assign(n, vector<int>(m + 1));
    for(int i =0; i< n; i++) {
        for(int j= 0; j <= m; j++) {
            nxt_col[i][j] = j;
        }
    }
    // go backwards
    for(int i = q - 1; i >=0; i--) {
        ll rr = qs[i][0];
        ll cc = qs[i][1];
        ll p = qs[i][2];
        ll p2 = p * p;
        //make it so iit never even goes out of bounds!?
        for(ll r = rr - p; r <= rr +p; r++) {
            ll dr = r - rr;
            ll rem = p2 - dr * dr;

            ll dc = sqrt(rem);
            while((dc + 1) * (dc + 1) <= rem) dc++;
            while(dc * dc >rem) dc--;
            int L = cc - dc;
            int R = cc + dc;
            int cur_c = find_free(r, L);
            while(cur_c <= R ) {
                ll dc_now = cur_c - cc;
                ll shk = p2 - (dr * dr + dc_now * dc_now) + 1;

                grid[r][cur_c] = shk;
                // mark this
                nxt_col[r][cur_c] = find_free(r, cur_c + 1);
                cur_c = nxt_col[r][cur_c];
            }
        }
    }
    for(int i= 0; i < n; i++) {
        for(int j =0; j <m; j++) {
            cout << grid[i][j] << (j == m - 1 ? "" : " ");
        }
        cout <<endl;
    }
}
int main() {
    fastio();

    int T;
    cin >> T;

    while(T--) {
        solve();
    }

    return 0;
}