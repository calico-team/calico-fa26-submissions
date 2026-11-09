#include <bits/stdc++.h>
using namespace std;
struct DSU {
    vector<int> p, sz;
    DSU(int n):p(n), sz(n, 1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        if(p[x]==x) return x;
        return p[x]=find(p[x]);
    }
    void unite(int a, int b) {
        a=find(a);
        b=find(b);
        if(a==b) return;
        if(sz[a]>sz[b]) swap(a, b);
        p[b]=a;
        sz[a]+=sz[b];
    }
    bool same(int a, int b) {
        return find(a)==find(b);
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--) {
        int N, M, Q;
        cin>>N>>M>>Q;
        vector<string> G(N);
        for(auto &s:G) cin>>s;
        int V=N*M;
        auto id=[&](int r, int c, int mode) {
            return mode*V+r*M+c;
        };
        auto active=[&](char ch, int mode) {
            if(ch=='.') return true;
            if(ch=='B') return mode==0;
            return mode==1;
        };
        DSU dsu(2*V);
        for(int r=0; r<N; r++) {
            for(int c=0; c<M; c++) {
                if(G[r][c]=='.') {
                    dsu.unite(id(r, c, 0), id(r, c, 1));
                }
            }
        }
        int dr[2]={1, 0};
        int dc[2]={0, 1};
        for(int r=0; r<N; r++) {
            for(int c=0; c<M; c++) {
                for(int d=0; d<2; d++) {
                    int nr=r+dr[d];
                    int nc=c+dc[d];
                    if(nr>=N||nc>=M) continue;
                    for(int mode=0; mode<2; mode++) {
                        if(active(G[r][c], mode)&&
                        active(G[nr][nc], mode)) {
                            dsu.unite(
                                id(r, c, mode),
                                id(nr, nc, mode)
                            );
                        }
                    }
                }
            }
        }
        while(Q--) {
            int rs, cs, re, ce;
            cin>>rs>>cs>>re>>ce;
            int start=id(rs, cs, 0);
            int target=id(re, ce, 0);
            cout<<(dsu.same(start, target)?"YES":"NO")<<'\n';
        }
    }
}