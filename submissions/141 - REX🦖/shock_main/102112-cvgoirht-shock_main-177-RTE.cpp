#include<bits/stdc++.h>
using namespace std;

// ifstream fin("input.in");
// ofstream fout("prog.out");
// #define cin fin
// #define cout fout

const int N = 1e6 + 7, M = 1e3 + 7, O = 2e4 + 7;

vector < vector <int> > bg[N], ed[N];
#define int long long
vector <int> ans[N];
priority_queue <int> pq;

struct str {
    int p, r, c;
    int calc(int x, int y){
        return p * p - (r - x) * (r - x) - (c - y) * (c - y) + 1;
    }
}a[N];
bool f[N];

int n, m, q, r, c, p, t;
bool swp;

void solve(){

    swp = 0;
    cin >> n >> m >> q;
    if(n > m) swap(n, m), swp = 1;
    for(int i = 1; i <= n; i ++)
        ans[i].resize(m + 2);
    for(int i = 1; i <= n; i ++)
        bg[i].resize(m + 2), ed[i].resize(m + 2);

    for(int clk = 1; clk <= q; clk ++){
        cin >> r >> c >> p;
        if(swp) swap(r, c);
        r ++, c ++;
        for(int i = 1; i <= n; i ++){
            if(abs(r - i) > p) continue;
            int d = abs(r - i), s = p * p - d * d + 1;
            int sq = sqrt(s);
            if(sq * sq == s) sq --;
            int lb = c - sq, rb = c + sq;
            lb = max(lb, 1ll), rb = min(rb, m);
            // cout << i << ": s = " << s << ", range: " << lb << ' ' << rb << "\n";
            bg[i][lb].push_back(clk);
            if(rb < m) ed[i][rb + 1].push_back(clk);
        }
        a[clk] = {p, r, c};
    }

    for(int i = 1; i <= n; i ++){
        while(pq.size()) pq.pop();
        for(int clk = 1; clk <= q; clk ++) f[clk] = 0;
        for(int j = 1, clk = 0; j <= m; j ++){
            for(int to : bg[i][j]) pq.push(to), f[to] = 1;
            for(int to : ed[i][j]) f[to] = 0;
            while(pq.size() && !f[pq.top()]) pq.pop();
            if(pq.size()) clk = pq.top();
            if(clk) ans[i][j] = a[clk].calc(i, j);
            clk = 0;
        }
    }

    if(swp) swap(n, m);
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            if(!swp) cout << ans[i][j];
            else cout << ans[j][i];
            if(j < m) cout << ' ';
        }
        cout << '\n';
    }
    for(int i = 1; i <= n; i ++)
        bg[i].clear(), ed[i].clear(), ans[i].clear();

}

signed main(){

    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t --) solve();

    return 0;
}
