#include <bits/stdc++.h>
using namespace std;
const int MAXN=200005,PS=30*200000+1000;
int ch[PS][2],cn[PS];
int tot,fr[PS],fc;
int newNode(){
    int x=fc?fr[--fc]:tot++;
    ch[x][0]=ch[x][1]=0;cn[x]=0;
    return x;
}
void resetTrie(){tot=2;fc=0;ch[1][0]=ch[1][1]=0;cn[1]=0;}
void ins(int x){
    int u=1;
    for(int b=29;b>=0;b--){
        int c=x>>b&1;
        if(!ch[u][c]) ch[u][c]=newNode();
        u=ch[u][c];cn[u]++;
    }
}
void del(int x){
    int u=1;
    for(int b=29;b>=0;b--){
        int c=x>>b&1;
        int v=ch[u][c];
        if(--cn[v]==0){ch[u][c]=0;fr[fc++]=v;}
        u=v;
    }
}
int mx(int k){
    int u=1,r=0;
    for(int b=29;b>=0;b--){
        int c=(k>>b&1)^1;
        if(ch[u][c]&&cn[ch[u][c]]>0){r|=1<<b;u=ch[u][c];}
        else u=ch[u][c^1];
    }
    return r;
}
int A[MAXN],V[MAXN],ans[MAXN],T[MAXN],root[MAXN],st[MAXN],onc[MAXN];
int hd[MAXN],nx[MAXN],qh[MAXN],qn[MAXN];
int main(){
    int TT; scanf("%d",&TT);
    while(TT--){
        int n; scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&A[i]);
        for(int i=1;i<=n;i++) scanf("%d",&V[i]);
        for(int i=1;i<=n;i++){st[i]=0;onc[i]=0;hd[i]=0;qh[i]=0;}
        vector<vector<int>> cycles;
        for(int i=1;i<=n;i++){
            if(st[i]) continue;
            int u=i;
            while(!st[u]){st[u]=i;u=A[u];}
            if(st[u]==i){
                vector<int> c;
                int v=u;
                do{c.push_back(v);onc[v]=1;v=A[v];}while(v!=u);
                cycles.push_back(c);
            }
            u=i;
            while(st[u]==i){st[u]=-1;u=A[u];}
        }
        for(int v=1;v<=n;v++) if(!onc[v]){nx[v]=hd[A[v]];hd[A[v]]=v;}
        for(int i=1;i<=n;i++){ans[i]=0;}
        for(auto&cy:cycles){
            for(int c:cy){
                resetTrie();
                int G=0;
                T[c]=0;root[c]=c;
                vector<array<int,3>> stk;
                stk.push_back({c,hd[c],0});
                while(!stk.empty()){
                    auto&f=stk.back();
                    int u=f[0];
                    int v=f[1];
                    if(v==0){
                        if(u!=c){
                            G^=V[u];
                            del(G);
                        }
                        stk.pop_back();
                        continue;
                    }
                    f[1]=nx[v];
                    ins(G);
                    G^=V[v];
                    T[v]=V[v]^T[u];root[v]=c;
                    ans[v]=mx(G);
                    stk.push_back({v,hd[v],0});
                }
            }
        }
        for(int v=1;v<=n;v++){qn[v]=qh[root[v]];qh[root[v]]=v;}
        for(auto&cy:cycles){
            int L=cy.size();
            vector<int> pre(2*L+1,0);
            for(int j=0;j<2*L;j++) pre[j+1]=pre[j]^V[cy[j%L]];
            int C=pre[L];
            resetTrie();
            for(int q=1;q<=L;q++) ins(pre[q]);
            for(int p=0;p<L;p++){
                if(p>0){del(pre[p]);ins(pre[p+L]);}
                int c=cy[p];
                for(int v=qh[c];v;v=qn[v]){
                    int key=T[v]^pre[p];
                    int r=max(mx(key),mx(key^C));
                    ans[v]=max(ans[v],r);
                }
            }
        }
        for(int i=1;i<=n;i++) printf("%d%c",ans[i],i==n?'\n':' ');
    }
}