#include <bits/stdc++.h>
using namespace std;
using ll=long long;
struct NextDSU {
    vector<int> p;
    NextDSU(int n):p(n+1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        int y=x;
        while(p[y]!=y) {
            y=p[y];
        }
        while(p[x]!=x) {
            int z=p[x];
            p[x]=y;
            x=z;
        }
        return y;
    }
    void erase(int x) {
        p[x]=find(x+1);
    }
};
struct Quake {
    int r, c, p;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--) {
        int N, M, Q;
        cin>>N>>M>>Q;
        vector<Quake> q(Q);
        for(auto &e:q) {
            cin>>e.r>>e.c>>e.p;
        }
        int V=N*M;
        vector<ll> ans(V, 0);
        NextDSU dsu(V);
        auto processRow=[&](int r, int c, int span, int p, int d) {
            int l=max(0, c-span);
            int rr=min(M-1, c+span);
            int L=r*M+l;
            int R=r*M+rr;
            int x=dsu.find(L);
            while(x<=R) {
                int col=x-r*M;
                ans[x]=
                1LL*p*p
                -1LL*d*d
                -1LL*(col-c)*(col-c)
                +1;
                dsu.erase(x);
                x=dsu.find(x);
            }
        };
        for(int id=Q-1; id>=0; id--) {
            int r=q[id].r;
            int c=q[id].c;
            int p=q[id].p;
            ll p2=1LL*p*p;
            int span=p;
            for(int d=0; d<=p; d++) {
                while(1LL*span*span+1LL*d*d>p2) {
                    span--;
                }
                processRow(r-d, c, span, p, d);
                if(d>0) {
                    processRow(r+d, c, span, p, d);
                }
            }
        }
        for(int r=0; r<N; r++) {
            for(int c=0; c<M; c++) {
                if(c) cout<<' ';
                cout<<ans[r*M+c];
            }
            cout<<'\n';
        }
    }
}