#include <bits/stdc++.h>
using namespace std;
const int INF=2000000000;
int N,M;
vector<string> G;
struct Q{int rs,cs,rt,ct,k;};
vector<Q> qs;
vector<int> best;
bool act(int r,int c,int m){
    char ch=G[r][c];
    return ch=='.'||(ch=='B'&&m==0)||(ch=='R'&&m==1);
}
void solve(int l,int r,vector<int>&ids){
    if(l>r||ids.empty()) return;
    int m=(l+r)/2,len=r-l+1,S=N*2*len;
    vector<int> mids;
    for(int i=0;i<N;i++)for(int md=0;md<2;md++) if(act(i,m,md)) mids.push_back(((m-l)*N+i)*2+md);
    vector<vector<int>> D(mids.size(),vector<int>(S,INF));
    vector<int> q(S);
    const int dr[4]={1,-1,0,0},dc[4]={0,0,1,-1};
    for(size_t x=0;x<mids.size();x++){
        auto&d=D[x];
        int h=0,t=0;
        q[t++]=mids[x];d[mids[x]]=0;
        while(h<t){
            int u=q[h++];
            int md=u&1,cell=u>>1,row=cell%N,col=cell/N+l;
            if(G[row][col]=='.'){
                int v=u^1;
                if(d[v]==INF){d[v]=d[u]+1;q[t++]=v;}
            }
            for(int k=0;k<4;k++){
                int nr=row+dr[k],nc=col+dc[k];
                if(nr<0||nr>=N||nc<l||nc>r||!act(nr,nc,md)) continue;
                int v=(((nc-l)*N+nr)*2)+md;
                if(d[v]==INF){d[v]=d[u]+1;q[t++]=v;}
            }
        }
    }
    vector<int> L,R;
    for(int id:ids){
        Q&e=qs[id];
        int sidx=((e.cs-l)*N+e.rs)*2;
        int t0=((e.ct-l)*N+e.rt)*2;
        char ch=G[e.rt][e.ct];
        for(size_t x=0;x<mids.size();x++){
            int ds=D[x][sidx];
            if(ds>=INF) continue;
            int bt=INF;
            if(ch!='R') bt=min(bt,D[x][t0]);
            if(ch!='B') bt=min(bt,D[x][t0+1]);
            if(bt<INF) best[id]=min(best[id],ds+bt);
        }
        int lo=min(e.cs,e.ct),hi=max(e.cs,e.ct);
        if(hi<m) L.push_back(id);
        else if(lo>m) R.push_back(id);
    }
    D.clear();D.shrink_to_fit();
    solve(l,m-1,L);
    solve(m+1,r,R);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin>>T;
    while(T--){
        int Qn; cin>>N>>M>>Qn;
        G.assign(N,"");
        for(auto&s:G) cin>>s;
        qs.resize(Qn);best.assign(Qn,INF);
        vector<int> ids(Qn);
        for(int i=0;i<Qn;i++){
            cin>>qs[i].rs>>qs[i].cs>>qs[i].rt>>qs[i].ct>>qs[i].k;
            ids[i]=i;
            if(qs[i].rs==qs[i].rt&&qs[i].cs==qs[i].ct) best[i]=0;
        }
        solve(0,M-1,ids);
        for(int i=0;i<Qn;i++) cout<<(best[i]<=qs[i].k?"YES":"NO")<<"\n";
    }
}