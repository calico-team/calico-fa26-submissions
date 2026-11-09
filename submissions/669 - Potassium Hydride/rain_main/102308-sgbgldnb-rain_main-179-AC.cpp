#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXV = 100005;
int bit[MAXV + 2];

void upd(int i, int v) {
    for (i++; i <= MAXV + 1; i += i & -i) bit[i] += v;
}
int qry(int i) {
    int s = 0;
    for (i++; i > 0; i -= i & -i) s += bit[i];
    return s;
}

struct Pt { ll x; int z; };        
struct Qr { ll l, r; int zq; int idx; };  
void countSide(const vector<Pt>& pts, const vector<Qr>& qs, vector<ll>& ans) {
    vector<tuple<ll, int, int, int>> ev;
    ev.reserve(2 * qs.size());
    for (const auto& q : qs) {
        ev.emplace_back(q.r, 1, q.zq, q.idx);
        ev.emplace_back(q.l - 1, -1, q.zq, q.idx);
    }
    sort(ev.begin(), ev.end());

    size_t p = 0;
    int inserted = 0;
    for (const auto& e : ev) {
        ll pos = get<0>(e);
        int sg = get<1>(e), zq = get<2>(e), idx = get<3>(e);
        while (p < pts.size() && pts[p].x <= pos) {
            upd(pts[p].z, 1);
            inserted++;
            p++;
        }
        ll c = inserted - qry(zq);   
        ans[idx] += sg * c;
    }
    for (size_t i = 0; i < p; i++) upd(pts[i].z, -1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        ll K;
        cin >> n >> K;

        vector<ll> X(n), Y(n);
        vector<int> Z(n);
        vector<char> D(n);
        for (int i = 0; i < n; i++) cin >> X[i] >> Y[i] >> Z[i] >> D[i];

       
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int a, int b) {
            ll sa = X[a] + Y[a], sb = X[b] + Y[b];
            if (sa != sb) return sa < sb;
            return X[a] < X[b];
        });

        vector<ll> shadow(n, 0);   

        size_t i = 0;
        while (i < (size_t)n) {
            size_t j = i;
            ll s = X[ord[i]] + Y[ord[i]];
            while (j < (size_t)n && X[ord[j]] + Y[ord[j]] == s) j++;

            vector<Pt> E, N;     
            vector<Qr> qE, qN;    
                                  
            for (size_t k = i; k < j; k++) {
                int id = ord[k];
                if (D[id] == 'E') {
                    E.push_back({X[id], Z[id]});
                    qE.push_back({X[id], X[id] + K - 1, Z[id], id});
                } else {
                    N.push_back({X[id], Z[id]});
                    qN.push_back({X[id] - K + 1, X[id], Z[id], id});
                }
            }

            countSide(N, qE, shadow);
            countSide(E, qN, shadow);

            i = j;
        }

        ll total = 0;
        for (int id = 0; id < n; id++) total += K - shadow[id];
        cout << total << "\n";
    }
    return 0;
}