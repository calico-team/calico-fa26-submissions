#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin>>T;
    while(T--){
        int N,M,Q; cin>>N>>M>>Q;
        vector<string> g(N);
        for(int i=0;i<N;i++) cin>>g[i];

        auto active=[&](int r,int c,int mode){ char ch=g[r][c]; if(ch=='.')return true; if(ch=='R')return mode==1; return mode==0; };
        int total=N*M*2;
        auto id=[&](int r,int c,int m){return (r*M+c)*2+m;};

        vector<int> head(total,-1), to, nxt;
        int dr[]={1,-1,0,0}, dc[]={0,0,1,-1};
        for(int r=0;r<N;r++)for(int c=0;c<M;c++)for(int m=0;m<2;m++){
            if(!active(r,c,m)) continue;
            int u=id(r,c,m);
            if(g[r][c]=='.'){ to.push_back(id(r,c,1-m)); nxt.push_back(head[u]); head[u]=to.size()-1; }
            for(int k=0;k<4;k++){int nr=r+dr[k],nc=c+dc[k]; if(nr<0||nr>=N||nc<0||nc>=M)continue; if(active(nr,nc,m)){ to.push_back(id(nr,nc,m)); nxt.push_back(head[u]); head[u]=to.size()-1; }}
        }

       
        vector<int> qr1(Q),qc1(Q),qr2(Q),qc2(Q); vector<ll> qK(Q);
        for(int i=0;i<Q;i++) cin>>qr1[i]>>qc1[i]>>qr2[i]>>qc2[i]>>qK[i];

        map<int, vector<int>> byStart;
        for(int i=0;i<Q;i++) byStart[id(qr1[i],qc1[i],0)].push_back(i);

        vector<int> dist(total);
        vector<char> ans(Q);
        vector<int> qb(total);
        for(auto &kv : byStart){
            int s = kv.first;
            const auto &list = kv.second;
    
            fill(dist.begin(), dist.end(), -1);
            int qh=0, qt=0;
            qb[qt++]=s; dist[s]=0;
            while(qh<qt){
                int u=qb[qh++];
                for(int e=head[u]; e!=-1; e=nxt[e]){ int v=to[e]; if(dist[v]==-1){ dist[v]=dist[u]+1; qb[qt++]=v; } }
            }
            for(int idx : list){
                int t0=id(qr2[idx],qc2[idx],0), t1=id(qr2[idx],qc2[idx],1);
                int best=INT_MAX;
                if(dist[t0]!=-1) best=min(best, dist[t0]);
                if(dist[t1]!=-1) best=min(best, dist[t1]);
                ans[idx] = (best<=qK[idx] ? 1 : 0);
            }
        }
        for(int i=0;i<Q;i++) cout << (ans[i]?"YES":"NO") << "\n";
    }
    return 0;
}

