#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
const int MAXN = 1e18;

struct State{
    int l, r, v;
    State (int a, int b, int c) {
        l = a;
        r = b;
        v = c;
    }
    State () {}
};

struct snode {
    int l, r, v;
    snode *lc, *rc;
    void construct () {
        v = MAXN;
        if (l == r) return;
        lc = (snode*)(malloc(sizeof(snode)));
        rc = (snode*)(malloc(sizeof(snode)));
        lc -> l  = l;
        rc -> r = r;
        lc -> r = floor((l+r)/2.0);
        rc -> l = lc -> r + 1;
        lc -> construct();
        rc -> construct();
    }
    void reset() {
        v = MAXN;
        if ( l == r) return;
        lc -> reset();
        rc -> reset();
    }
    void printout (vector<int> &_T, int mx) {
        mx = min(mx, v);
        if (l == r) {
            _T[l] = mx;
            return;
        }
        lc -> printout(_T, mx);
        rc -> printout(_T, mx);
    }
    void update(int ll, int rr, int vv){
        if (ll == l && rr == r) {
            v = min(v, vv);
            return;
        }
        if (ll <= lc -> r ){
            lc -> update(ll, min(lc -> r, rr), vv);
        }
        if (rr >= rc -> l) {
            rc -> update(max(rc -> l, ll), rr, vv);
        }
    }
};

int N, M, Q;
bool _F;
vector<int> R, C, P;
vector<vector<int>> output;
vector<vector<State>> rg;
snode root;
int fdis(int p, int dy) {
    if (dy > p) return -1;
    return (int)floor(sqrt((ld)(p*p) - (ld)(dy*dy)));
}

void docase(){
    // assume N <= M;
    rg = vector<vector<State>>(N, vector<State>(0));
    root.l = 0;
    root.r = M-1;
    root.construct();
    for (int i = 0; i < Q; i++) {
        for (int j = 0; j < N; j++) {
            int x = fdis(P[i], abs(j - R[i]));
            if (x == -1) continue;
            rg[j].push_back(State(max(C[i] - x, 0ll), min(C[i] + x, M-1), i));
        }
    }
    output = vector<vector<int>>(N, vector<int>(M, 0));
    for (int i = 0; i < N; i ++) {
        rg[0].clear();
        root.reset();
        for (int j =0 ;j < Q; j++){
            int x = fdis(P[j], abs(i - R[j]));
            if (x == -1) continue;
            rg[0].push_back(State(max(C[j] - x, 0ll), min(C[j] + x, M-1), j));
            root.update(rg[0][0].l, rg[0][0].r, rg[0][0].v);
            rg[0].pop_back();
        }
        root.printout(output[i], MAXN);
        for (int j = 0; j < M; j++) {
            if (output[i][j] == MAXN) output[i][j] = 0;
            else {
                int p = P[output[i][j]], r = R[output[i][j]], c = C[output[i][j]];
                output[i][j] = p*p - (i-r)*(i-r) - (j-c)*(j-c) + 1ll;
            }
        }
    }
}

signed main(){
    cin.sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    for (int gay = 0 ; gay < tt; gay++){
        cin >> N >> M >> Q;
        R = C = P = vector<int>(Q);
        for (int j = Q-1; j >= 0; j--) {
            cin >> R[j] >> C[j] >> P[j];
        }
        _F = false;
        if (N > M) {
            std::swap(N, M);
            std::swap(R, C);
            _F = true;
        }
        docase();
        if (_F) {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    if (j > 0) cout << ' ';
                    cout << output[j][i];
                }
                cout << '\n';
            }
        }
        else {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++){
                    if (j > 0) cout << ' ';
                    cout << output[i][j];
                }
                cout << '\n';
            }
        }
    }
    return 0;
}