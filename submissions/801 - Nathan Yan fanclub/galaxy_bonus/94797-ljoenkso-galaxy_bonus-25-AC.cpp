#include <bits/stdc++.h>
#define fore(v,l,r) for(ll v = (l); v < (r); v++)
#define sz(v) (v).size()
#define all(v) (v).begin(), (v).end()
#define pb push_back
using namespace std;
using ll = long long;
using vi = vector<ll>;
constexpr ll INF = 1e18;

struct DSU {
    vi dsu, sz;
    DSU(int n) {
        dsu.resize(n);
        iota(all(dsu),0);
        sz.resize(n,1);
    }

    int find(int n) {
        if(dsu[n] == n) return n;
        return dsu[n] = find(dsu[n]);
    }

    void merge(int u, int v) {
        u = find(u), v = find(v);
        if(u == v) return;
        if(sz[u]<sz[v]) swap(u,v);
        sz[u]+=sz[v]; dsu[v] = u;
    }

    bool chk(int a, int b) {
        return find(a) == find(b);
    }
};

void solve() {
    int N, M, Q; cin >> N >> M >> Q;
    vector<string> map(N);
    for(string& s : map) cin >> s;

    DSU reach(N*M);
    #define at(i, j) ((i)*M+(j))
    auto con = [&](char a, char b) -> bool {
        return a == b or a == '.' or b == '.';
    };

    fore(i,0,N) fore(j,0,M) {
        if(i>0 and con(map[i][j],map[i-1][j]))
            reach.merge(at(i,j), at(i-1,j));

        if(j>0 and con(map[i][j],map[i][j-1]))
            reach.merge(at(i,j), at(i,j-1));
    }

    fore(q,0,Q) {
        int i1, j1, i2, j2;
        cin >> i1 >> j1 >> i2 >> j2;

        cout << (reach.chk(at(i1,j1), at(i2,j2)) ? "YES\n" : "NO\n");
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}