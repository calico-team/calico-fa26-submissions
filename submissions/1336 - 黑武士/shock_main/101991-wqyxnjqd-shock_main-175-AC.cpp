#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin>>T;
    while(T--){
        int N,M,Q; cin>>N>>M>>Q;
        vector<ll> R(Q),C(Q),P(Q);
        for(int i=0;i<Q;i++) cin>>R[i]>>C[i]>>P[i];

       
        vector<vector<ll>> ans(N, vector<ll>(M,0));
      
        vector<vector<int>> nxt(N, vector<int>(M+1));
        for(int r=0;r<N;r++){ for(int c=0;c<=M;c++) nxt[r][c]=c; }
        function<int(int,int)> find = [&](int r,int c)->int{
            if(nxt[r][c]==c) return c;
            return nxt[r][c]=find(r,nxt[r][c]);
        };

       
        for(int qi=Q-1; qi>=0; qi--){
            ll Rr=R[qi], Cc=C[qi], Pp=P[qi];
            ll P2=Pp*Pp;
            int rlo=max(0LL, Rr-Pp), rhi=min((ll)N-1, Rr+Pp);
            for(int r=rlo; r<=rhi; r++){
                ll dr=r-Rr;
                ll rem = P2 - dr*dr;
                ll w = (ll)sqrt((long double)rem);
                while((w+1)*(w+1)<=rem) w++;
                while(w*w>rem) w--;
                int clo=max(0LL, Cc-w), chi=min((ll)M-1, Cc+w);
                if(clo>chi) continue;
                
                int c = find(r, clo);
                while(c <= chi){
                    
                    ll dc=c-Cc;
                    ll d2=dr*dr+dc*dc;
                    ans[r][c] = P2 - d2 + 1;
                    
                    nxt[r][c] = c+1;
                    c = find(r, c);
                }
            }
        }
        for(int r=0;r<N;r++){ for(int c=0;c<M;c++){ if(c)cout<<" "; cout<<ans[r][c]; } cout<<"\n"; }
    }
}

