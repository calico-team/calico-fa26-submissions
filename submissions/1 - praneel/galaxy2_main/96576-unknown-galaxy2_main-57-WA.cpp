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
const int oo = 1e8;

int n_rows, m_cols;
vector<string> grd;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool ok_cell(int md, int r, int c) {
    char ch = grd[r][c];
    if(ch == '.') return true;
    if(md == 0 && ch =='B') return true;
    if(md == 1 && ch == 'R') return true ;
    return false;
}
struct QItem {
    int sr, sc, tr, tc, id;
    ll k_lim;
};
vector<int> q_ans;
vector<int> dist_arr;
vector<int> bfs_q;

// divide and conquer
void rec_solve(int cl, int cr, vector<QItem> &qs) {
    if(cl > cr || sz(qs) == 0) return ;
    int mid = (cl + cr) / 2;
    int len = cr - cl + 1;
    int w = 2 * n_rows;
    // run bfs
    for(int md= 0; md < 2; md++) {
        for(int r =0; r < n_rows; r++) {
            if(!ok_cell(md, r, mid)) continue;
            int tot_st = len * w;
            for(int i= 0; i < tot_st; i++) {
                dist_arr[i] = oo;
            }
            int st_node = (mid - cl) * w + md * n_rows + r;
            dist_arr[st_node] = 0;
            int head = 0, tail = 0;
            bfs_q[tail++] = st_node;
            while(head < tail ) {
                int u = bfs_q[head++];
                int d_now = dist_arr[u];
                int c_off = u / w;
                int rem = u % w;
                int cur_m = rem / n_rows;
                int cur_r = rem % n_rows;
                int cur_c = cl + c_off;
                // 4 grid neighbors
                for(int dir =0; dir< 4; dir++) {
                    int nr = cur_r + dr[dir];
                    int nc = cur_c + dc[dir];
                    if(nr >= 0 && nr <n_rows && nc >= cl && nc <=cr) {
                        if(ok_cell(cur_m, nr, nc)) {
                            int v = (nc - cl) * w + cur_m * n_rows + nr;
                            if(dist_arr[v] == oo) {
                                dist_arr[v] = d_now + 1;
                                bfs_q[tail++] = v;
                            }
                        }
                    }
                }
                // switch color mode on '.'
                if(grd[cur_r][cur_c] == '.') {
                    int oth_m = 1 - cur_m;
                    int v = (cur_c - cl) * w + oth_m * n_rows + cur_r;
                    if(dist_arr[v] == oo) {
                        dist_arr[v] = d_now + 1;
                        bfs_q[tail++] = v;
                    }
                }
            }
            // lock in for this one bro wtf
            for(int i= 0; i < sz(qs); i++) {
                int qid = qs[i].id;
                // we can skip
                if(q_ans[qid]) continue ;
                int u_start = (qs[i].sc - cl) * w + 0 * n_rows + qs[i].sr;
                int d1 = dist_arr[u_start];
                if(d1 == oo) continue;
                // try ending in blue
                int u_end0 = (qs[i].tc - cl) * w + 0 * n_rows + qs[i].tr;
                int best_d = d1 + dist_arr[u_end0];
                // try ending in reds it
                char end_ch = grd[qs[i].tr][qs[i].tc];
                if(end_ch == '.' || end_ch =='R') {
                    int u_end1 = (qs[i].tc - cl) * w + 1 * n_rows + qs[i].tr;
                    best_d = min(best_d, d1 + dist_arr[u_end1]);
                }
                if(best_d <= qs[i].k_lim) {
                    q_ans[qid] = 1;
                }
            }
        }
    }
    vector<QItem> left_qs, right_qs;
    for(int i =0; i < sz(qs); i++) {
        if(q_ans[qs[i].id]) continue;

        if(qs[i].sc < mid && qs[i].tc <mid) {
            left_qs.pb(qs[i]);
        }
        else if(qs[i].sc > mid && qs[i].tc > mid) {
            right_qs.pb(qs[i]);
        }
    }
    if(cl < mid) rec_solve(cl, mid - 1, left_qs);
    if(mid < cr) rec_solve(mid + 1, cr, right_qs);
}

void solve() {
    int q ;
    cin >>n_rows >> m_cols>> q;
    grd.resize(n_rows);
    for(int i= 0; i < n_rows; i++) {
        cin>> grd[i];
    }
    vector<QItem> all_q(q);
    q_ans.assign(q, 0);
    for(int i =0; i< q; i++) {
        cin >> all_q[i].sr >>all_q[i].sc >> all_q[i].tr >> all_q[i].tc >> all_q[i].k_lim;
        all_q[i].id = i;
    }
    int max_states = m_cols * 2 * n_rows + 5;
    dist_arr.resize(max_states);
    bfs_q.resize(max_states);
    rec_solve(0, m_cols - 1, all_q);
    for(int i=0; i < q; i++) {
        if(q_ans[i] ) cout << "YES" <<endl;
        else cout<< "NO" << endl;
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