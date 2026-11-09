#include <bits/stdc++.h>
using namespace std;
struct DSU {
    vector<int> p,sz;
    DSU(int n) {
        p.resize(n);
        sz.assign(n, 1);
        iota(p.begin(),p.end(), 0);
    }
    int find(int x) {
        while (p[x]!= x) {
            p[x]= p[p[x]];
            x =p[x];
        }
        return x;
    }
    void unite(int a, int b) {
        a = find(a);
        b =find(b);
        if(a== b) return;
        if (sz[a]< sz[b]) swap(a, b);
        p[b] =a;
        sz[a] +=sz[b];
    }
    bool same(int a, int b) {
        return find(a)== find(b);
    }
};
bool active(char tile, int mode) {
    return tile == '.'|| (mode == 0&& tile =='B') ||(mode ==1 &&tile == 'R');
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >>T;
    while (T--){
        int N, M,Q;
        cin >> N>>M >> Q;
        vector<string>g(N);
        for (int i =0;i < N; i++) {
            cin >> g[i];
        }
        DSU dsu(2 *N * M);
        auto id = [&](int r,int c, int mode) {
            return 2 * (r * M+c) + mode;
        };
        for (int r = 0; r < N; r++) {
            for (int c = 0; c< M;c++) {
                if(g[r][c]== '.') {
                    dsu.unite(
                        id(r, c, 0),
                        id(r, c, 1)
                    );
                }
                if (r +1< N) {
                    for(int mode =0; mode < 2; mode++) {
                        if (active(g[r][c], mode) &&
                            active(g[r +1][c], mode)){
                            dsu.unite(
                                id(r, c, mode),
                                id(r +1,c, mode)
                            );
                        }
                    }
                }
                if (c+ 1 < M) {
                    for (int mode =0; mode < 2; mode++) {
                        if(active(g[r][c], mode) &&
                            active(g[r][c + 1], mode)) {
                            dsu.unite(
                                id(r, c, mode),
                                id(r, c + 1, mode)
                            );
                        }
                    }
                }
            }
        }
        while (Q--) {
            int rs, cs, re, ce;
            cin >>rs >>cs >> re >>ce;
            int start= id(rs, cs, 0);
            int targetMode = (g[re][ce] =='R' ? 1 : 0);
            int target =id(re, ce, targetMode);
            cout<< (dsu.same(start, target) ? "YES" : "NO") <<'\n';
        }
    }
    return 0;
}
