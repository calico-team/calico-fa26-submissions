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
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool can_step(char ch, int col_state) {
    if(ch == '.') return true;
    // 0 = blue, 1 = red
    if(col_state == 0 && ch =='B') return true;
    if(col_state == 1 && ch == 'R') return true ;
    return false;
}
void solve() {
    int n, m, q ;
    cin >>n >> m>> q;

    vector<string> g(n);
    for(int i= 0; i < n; i++) {
        cin>> g[i];
    }
    // 2 layers for each cell
    int tot = n * m;
    vector<int> comp(2 * tot, -1);
    int cur_id = 0;

    // just bfs to label connected comps instead of coding dsu
    for(int st= 0; st < 2 * tot; st++) {
        if(comp[st] != -1) continue;

        int init_m = st / tot;
        int rem = st % tot;
        int ir = rem / m, ic = rem % m;

        // dont waste time
        if(!can_step(g[ir][ic], init_m)) continue ;

        cur_id++;
        queue<int> qq;
        qq.push(st);
        comp[st] = cur_id;
        while(!qq.empty()) {
            int u = qq.front();
            qq.pop();

            int md = u / tot;
            int cell = u % tot;
            int r = cell / m;
            int c = cell % m;

            // uhh idk
            if(g[r][c] == '.') {
                int oth = (1 - md) * tot + cell;
                if(comp[oth] == -1) {
                    comp[oth] = cur_id;
                    qq.push(oth);
                }
            }
            // try 4 neighbors in same color mode
            for(int d =0; d< 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if(nr >= 0 && nr <n && nc >=0 && nc < m) {
                    if(can_step(g[nr][nc], md)) {
                        int nxt_u = md * tot + nr * m + nc;
                        if(comp[nxt_u] == -1) {
                            comp[nxt_u] = cur_id;
                            qq.push(nxt_u);
                        }
                    }
                }
            }
        }
    }
    while(q--) {
        int r1, c1, r2, c2;
        cin >> r1>> c1 >> r2 >>c2;
        // start
        int u_st = 0 * tot + r1 * m + c1;

        // for end cell if its R we gotta arrive in red mode,
        int end_md = 0;
        if(g[r2][c2] == 'R') end_md = 1;

        int u_en = end_md * tot + r2 * m + c2;
        if(comp[u_st] != -1 && comp[u_st] == comp[u_en]) {
            cout << "YES" <<endl;
        }
        else {
            cout<< "NO" << endl;
        } // dude i dont know bro
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