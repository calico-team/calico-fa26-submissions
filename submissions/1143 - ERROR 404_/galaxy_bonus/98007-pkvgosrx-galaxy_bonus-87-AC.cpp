#include <bits/stdc++.h>
using namespace std;

inline int id3(int r,int c,int mode,int N,int M){
    return (mode*N + r)*M + c;
}
inline bool active_cell(char ch,int mode){
    if(ch=='.') return true;
    if(mode==0) return ch=='B';
    return ch=='R';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin>>T)) return 0;
    while(T--){
        int N,M,Q;
        cin>>N>>M>>Q;
        vector<string> g(N);
        for(int i=0;i<N;++i) cin>>g[i];
        struct Qry{int rs,cs,re,ce;};
        vector<Qry> qs(Q);
        for(int i=0;i<Q;++i) cin>>qs[i].rs>>qs[i].cs>>qs[i].re>>qs[i].ce;

        int TOT = 2*N*M;
        vector<int> comp(TOT, -1);
        vector<int> st;
        st.reserve(TOT);
        const int dr[4]={1,-1,0,0};
        const int dc[4]={0,0,1,-1};
        int compCnt=0;

        for(int r=0;r<N;++r){
            for(int c=0;c<M;++c){
                for(int mode=0;mode<2;++mode){
                    if(!active_cell(g[r][c],mode)) continue;
                    int s=id3(r,c,mode,N,M);
                    if(comp[s]!=-1) continue;
                    // BFS for this component
                    st.clear();
                    st.push_back(s);
                    comp[s]=compCnt;
                    size_t head=0;
                    while(head<st.size()){
                        int cur=st[head++];
                        int md=cur/(N*M);
                        int rem=cur%(N*M);
                        int cr=rem/M, cc=rem%M;
                        // spin
                        if(g[cr][cc]=='.'){
                            int nid=id3(cr,cc,1-md,N,M);
                            if(comp[nid]==-1){comp[nid]=compCnt; st.push_back(nid);}
                        }
                        // moves
                        for(int k=0;k<4;++k){
                            int nr=cr+dr[k], nc=cc+dc[k];
                            if(nr<0||nr>=N||nc<0||nc>=M) continue;
                            if(!active_cell(g[nr][nc],md)) continue;
                            int nid=id3(nr,nc,md,N,M);
                            if(comp[nid]==-1){comp[nid]=compCnt; st.push_back(nid);}
                        }
                    }
                    compCnt++;
                }
            }
        }

        for(auto &q: qs){
            int cs = comp[id3(q.rs,q.cs,0,N,M)];
            bool ok=false;
            char ch = g[q.re][q.ce];
            if(ch=='.'){
                int c0=comp[id3(q.re,q.ce,0,N,M)];
                int c1=comp[id3(q.re,q.ce,1,N,M)];
                if(c0==cs || c1==cs) ok=true;
            }else if(ch=='B'){
                int c0=comp[id3(q.re,q.ce,0,N,M)];
                if(c0==cs) ok=true;
            }else{ // 'R'
                int c1=comp[id3(q.re,q.ce,1,N,M)];
                if(c1==cs) ok=true;
            }
            cout<<(ok?"YES\n":"NO\n");
        }
    }
    return 0;
}