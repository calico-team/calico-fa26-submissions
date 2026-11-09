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
void solve() {
    int n, m, k ;
    cin >>n >> m>> k;

    vector<int> p(n + 1);
    vector<vector<int>> ch(n + 1);

    for(int i= 1; i <= n; i++) {
        cin>> p[i];
        if(p[i] != 0) {
            ch[p[i]].pb(i);
        }
    }

    // chain is <= 1000 
    vector<int> ht(n + 1, 0);
    for(int i =1; i<= n; i++) {
        int cur = i;
        int d = 1;
        while(cur != 0 ) {
            if(ht[cur] >= d) break;
            ht[cur] = d;
            cur = p[cur];
            d ++;
        }
    }
    // greedy hey its me its verity
    priority_queue<pair<int, int>> pq;
    for(int i= 1; i <=n; i++) {
        if(p[i] ==0) {
            pq.push({ht[i], i});
        }
    }
    int ans = 0;
    for(int sem = 0; sem < m; sem++) {
        if(pq.empty()) break ;

        vector<int> picked;
        for(int j= 0; j < k; j++) {
            if(pq.empty() ) break;
            int u = pq.top().second;
            pq.pop();
            picked.pb(u);
        }
        ans += sz(picked);
        for(int i =0; i < sz(picked); i++) {
            int u = picked[i];
            for(int nxt : ch[u]) {
                pq.push({ht[nxt], nxt});
            }
        }
    }
    cout << ans <<endl;
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