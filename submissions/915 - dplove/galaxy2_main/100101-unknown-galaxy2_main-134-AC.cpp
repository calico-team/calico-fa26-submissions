#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<climits>
#include<string>
#include<numeric>
#include<deque>
using namespace std;

#define int long long
#define vi vector<int>
#define pii pair<int,int>
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define all(x) x.begin(),x.end()
#define ull unsigned long long
#define vs vector<string>

const int INF = 1e18;
const int modx = 1e9 + 7;
const int maxn = 2e5 + 1;

int modadd(int a, int b, int m = modx){ return (a+b)%m; }
int modmultiply(int a, int b,int m = modx){ return (a*b)%m; }
int modsubtract(int a, int b,int m = modx){ return (a-b+m)%m; }

int binpow(int base, int expo, int m = modx){
    if(expo == 0) return 1;
    if(expo == 1) return base%m;

    int temp = binpow(base,expo/2,m);
    int extra = (expo & 1) ? base : 1;

    return modmultiply(modmultiply(temp,temp,m),extra,m);
}

int modinverse_prime(int b, int m = modx){
    return binpow(b,m-2,m);
}

struct Qry {
    int id, r1, c1, r2, c2, k;
};

int n, m, q;
vs g;
vi ans, d, qu;

bool val(int r, int c, int md) {
  if (md == 0) return g[r][c] == '.' || g[r][c] == 'B';
  return g[r][c] == '.' || g[r][c] == 'R';
}

int enc(int r, int c, int md, int L) {
  return (((c - L) * n + r) << 1) | md;
}

void dnc(int L, int R, const vector<Qry>& qrs) {
  if (qrs.empty()) return;

  int mid = (L + R) / 2;
  int tot = (R - L + 1) * n * 2;

  for (int rm = 0; rm < n; rm++) {
    for (int mm = 0; mm < 2; mm++) {
      if (!val(rm, mid, mm)) continue;

      fill(d.begin(), d.begin() + tot, -1);
      int hd = 0, tl = 0;
      int s = enc(rm, mid, mm, L);
      d[s] = 0;
      qu[tl++] = s;

                    while (hd < tl) {
              int u = qu[hd++];
              int cd = d[u];
              int md = u & 1;
              int tmp = u >> 1;
              int r = tmp % n;
              int c = tmp / n + L;

                if (r > 0 && val(r - 1, c, md)) {
                    int v = enc(r - 1, c, md, L);
                    if (d[v] == -1) { d[v] = cd + 1; qu[tl++] = v; }
                }
                if (r + 1 < n && val(r + 1, c, md)) {
                    int v = enc(r + 1, c, md, L);
                    if (d[v] == -1) { d[v] = cd + 1; qu[tl++] = v; }
                }
                if (c > L && val(r, c - 1, md)) {
                    int v = enc(r, c - 1, md, L);
                    if (d[v] == -1) { d[v] = cd + 1; qu[tl++] = v; }
                }
                if (c < R && val(r, c + 1, md)) {
                    int v = enc(r, c + 1, md, L);
                    if (d[v] == -1) { d[v] = cd + 1; qu[tl++] = v; }
                }
                if (g[r][c] == '.') {
                    int v = enc(r, c, 1 - md, L);
                    if (d[v] == -1) { d[v] = cd + 1; qu[tl++] = v; }
                }
            }

            for (auto& qry : qrs) {
                int ds = d[enc(qry.r1, qry.c1, 0, L)];
                if (ds == -1) continue;

                int de = INF;
                if (val(qry.r2, qry.c2, 0)) {
                    int d0 = d[enc(qry.r2, qry.c2, 0, L)];
                    if (d0 != -1) de = min(de, d0);
                }
                if (val(qry.r2, qry.c2, 1)) {
                    int d1 = d[enc(qry.r2, qry.c2, 1, L)];
                    if (d1 != -1) de = min(de, d1);
                }

                  if (de != INF) {
                      ans[qry.id] = min(ans[qry.id], ds + de);
                  }
            }
        }
    }

    vector<Qry> lq, rq;
    for (auto& qry : qrs) {
        int mn = min(qry.c1, qry.c2);
        int mx = max(qry.c1, qry.c2);
        if (mx < mid) lq.push_back(qry);
        else if (mn > mid) rq.push_back(qry);
    }

    if (L <= mid - 1 && !lq.empty()) dnc(L, mid - 1, lq);
    if (mid + 1 <= R && !rq.empty()) dnc(mid + 1, R, rq);
}

void solve(){
    cin >> n >> m >> q;
    g.resize(n);
    for (int i = 0; i < n; i++) cin >> g[i];

    vector<Qry> qrs(q);
    ans.assign(q, INF);

    for (int i = 0; i < q; i++) {
        qrs[i].id = i;
        cin >> qrs[i].r1 >> qrs[i].c1 >> qrs[i].r2 >> qrs[i].c2 >> qrs[i].k;
        if (qrs[i].r1 == qrs[i].r2 && qrs[i].c1 == qrs[i].c2) {
            ans[i] = 0;
        }
    }

    int sz = n * m * 2;
    d.resize(sz);
    qu.resize(sz);

    dnc(0, m - 1, qrs);

    for (int i = 0; i < q; i++) {
        if (ans[i] <= qrs[i].k) yes;
        else no;
    }
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; cin >> t;

    while(t--){
        solve();
    }
}