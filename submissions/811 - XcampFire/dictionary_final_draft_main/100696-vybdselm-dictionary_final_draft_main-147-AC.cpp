#include<iostream>
#include<vector>
using namespace std;

const int MX=31*200005;
int ch[MX][2],cnt[MX],tot;

int newNode(){
    ch[tot][0]=ch[tot][1]=0;
    cnt[tot]=0;
    return tot++;
}

void ins(int r,int x,int d){
    int c=r;
    for(int b=29;b>=0;b--){
        int t=(x>>b)&1;
        if(!ch[c][t])ch[c][t]=newNode();
        c=ch[c][t];
        cnt[c]+=d;
    }
}

int qry(int r,int x){
    int c=r,res=0;
    for(int b=29;b>=0;b--){
        int t=(x>>b)&1;
        int o=ch[c][t^1];
        if(o&&cnt[o]>0){
            res|=1<<b;
            c=o;
        }else c=ch[c][t];
    }
    return res;
}

vector<int>solve(int N,vector<int>A,vector<int>V){
    for(int&a:A)a--;
    vector<int>st(N,0),onc(N,0),ans(N,0),up(N,0);
    vector<vector<int>>kids(N);
    for(int i=0;i<N;i++)kids[A[i]].push_back(i);
    vector<vector<int>>cycles;
    for(int i=0;i<N;i++){
        if(st[i])continue;
        vector<int>path;
        int x=i;
        while(!st[x]){
            st[x]=1;
            path.push_back(x);
            x=A[x];
        }
        if(st[x]==1){
            vector<int>cyc;
            int y=x;
            do{
                cyc.push_back(y);
                onc[y]=1;
                y=A[y];
            }while(y!=x);
            cycles.push_back(cyc);
        }
        for(int p:path)st[p]=2;
    }
    for(auto&cyc:cycles){
        int L=cyc.size();
        vector<int>P(L+1,0);
        for(int k=0;k<L;k++)P[k+1]=P[k]^V[cyc[k]];
        int C=P[L];
        tot=1;
        int rU=newNode(),rA=newNode();
        for(int k=0;k<L;k++)ins(rU,P[k],1);
        ins(rA,0,1);
        for(int j=0;j<L;j++){
            int r=cyc[j];
            ans[r]=max(qry(rU,P[j]),qry(rU,P[j]^C));
            vector<pair<int,bool>>s;
            for(int c:kids[r])if(!onc[c])s.push_back({c,false});
            while(!s.empty()){
                int x=s.back().first;
                bool done=s.back().second;
                s.pop_back();
                if(done){
                    ins(rA,up[x],-1);
                    continue;
                }
                up[x]=V[x]^(onc[A[x]]?0:up[A[x]]);
                int u=up[x];
                ans[x]=max(qry(rA,u),max(qry(rU,u^P[j]),qry(rU,u^P[j]^C)));
                ins(rA,u,1);
                s.push_back({x,true});
                for(int c:kids[x])s.push_back({c,false});
            }
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;cin>>T;
    while(T--){
        int N;cin>>N;
        vector<int>A(N),V(N);
        for(int&i:A)cin>>i;
        for(int&i:V)cin>>i;
        vector<int>ans=solve(N,A,V);
        for(int&i:ans)cout<<i<<' ';
        cout<<'\n';
    }
    return 0;
}